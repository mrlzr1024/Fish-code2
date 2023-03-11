/*
  ESP32CAM Robot Car
  app_httpd.cpp (requires esp32cam-robot.ino)
  Based upon Espressif ESP32CAM Examples
  Uses TBA6612FNG H-Bridge Controller

  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

#include "dl_lib_matrix3d.h"
#include <esp32-hal-ledc.h>
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_camera.h"
#include "img_converters.h"
#include "Arduino.h"

// TB6612FNG H-Bridge Connections (both PWM inputs driven by GPIO 12)
#define MTR_PWM 12
#define LEFT_M0 15
#define LEFT_M1 14
#define RIGHT_M0 13
#define RIGHT_M1 2

// Define Speed variables
int speed = 255;
int noStop = 0;

// Setting Motor PWM properties
const int freq = 2000;
const int motorPWMChannnel = 8;
const int lresolution = 8;

volatile unsigned int motor_speed = 200;
volatile unsigned long previous_time = 0;
volatile unsigned long move_interval = 250;

// Placeholder for functions
void robot_setup();
void robot_stop();
void robot_fwd();
void robot_back();
void robot_left();
void robot_right();
uint8_t robo = 0;

typedef struct
{
  httpd_req_t *req;
  size_t len;
} jpg_chunking_t;

#define PART_BOUNDARY "123456789000000000000987654321"
static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *_STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

httpd_handle_t camera_httpd = NULL;

enum state
{
  fwd,
  rev,
  stp
};
state actstate = stp;

static esp_err_t cmd_handler(httpd_req_t *req)
{
  char *buf;
  size_t buf_len;
  char variable[32] = {
      0,
  };
  char value[32] = {
      0,
  };

  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1)
  {
    buf = (char *)malloc(buf_len);
    if (!buf)
    {
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
    {
      Serial.print("请求是：");
      Serial.println(buf);
      if (httpd_query_key_value(buf, "var", variable, sizeof(variable)) == ESP_OK &&
          httpd_query_key_value(buf, "val", value, sizeof(value)) == ESP_OK)
      {
      }
      else
      {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    }
    else
    {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  }
  else
  {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }

  int val = atoi(value);
  sensor_t *s = esp_camera_sensor_get();
  int res = 0;

  // Look at values within URL to determine function
  if (!strcmp(variable, "framesize"))
  {
    Serial.println("framesize");
    if (s->pixformat == PIXFORMAT_JPEG)
      res = s->set_framesize(s, (framesize_t)val);
  }
  else if (!strcmp(variable, "quality"))
  {
    Serial.println("quality");
    res = s->set_quality(s, val);
  }
  else if (!strcmp(variable, "flash"))
  {
    ledcWrite(7, val);
  }
  else if (!strcmp(variable, "flashoff"))
  {
    ledcWrite(7, val);
  }
  else if (!strcmp(variable, "speed"))
  {
    if (val > 255)
      val = 255;
    else if (val < 0)
      val = 0;
    speed = val;
    ledcWrite(8, speed);
  }
  else if (!strcmp(variable, "nostop"))
  {
    noStop = val;
  }
  else if (!strcmp(variable, "car"))
  {
    if (val == 1)
    {
      Serial.println("Forward");
      robot_fwd();
      robo = 1;
    }
    else if (val == 2)
    {
      Serial.println("TurnLeft");
      robot_left();
      robo = 1;
    }
    else if (val == 3)
    {
      Serial.println("Stop");
      robot_stop();
    }
    else if (val == 4)
    {
      Serial.println("TurnRight");
      robot_right();
      robo = 1;
    }
    else if (val == 5)
    {
      Serial.println("Backward");
      robot_back();
      robo = 1;
    }
    if (noStop != 1)
    {
    }
  }
  else
  {
    Serial.println("variable");
    res = -1;
  }

  if (res)
  {
    return httpd_resp_send_500(req);
  }

  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}

static esp_err_t status_handler(httpd_req_t *req)
{
  static char json_response[1024];

  sensor_t *s = esp_camera_sensor_get();
  char *p = json_response;
  *p++ = '{';

  p += sprintf(p, "\"framesize\":%u,", s->status.framesize);
  p += sprintf(p, "\"quality\":%u,", s->status.quality);
  *p++ = '}';
  *p++ = 0;
  httpd_resp_set_type(req, "application/json");
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, json_response, strlen(json_response));
}

static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width,initial-scale=1">
        <title>ESP32 CAM Robot</title>
        <style>
    </style>

    </head>
    <body>
            
            <section id="buttons">

                <div id="controls" class="control-container">
                  <table>
                  <tr><td></td><td align="center"><button type="button" id="forward" onclick="fetch(document.location.origin+'/control?var=car&val=1');">前进</button></td><td></td></tr>
                  <tr><td align="center"><button type="button" id="turnleft" onclick="fetch(document.location.origin+'/control?var=car&val=2');">向左</button></td><td align="center"></td>
					  <td align="center"><button type="button" id="turnright" onclick="fetch(document.location.origin+'/control?var=car&val=4');">向右</button></td></tr>
                  <tr><td></td><td align="center"><button type="button" id="backward" onclick="fetch(document.location.origin+'/control?var=car&val=5');">后台</button></td><td></td></tr>
                  <tr><td></td><td align="center"><button type="button" id="flash" onclick="fetch(document.location.origin+'/control?var=flash&val=1');">开灯</button></td><td></td></tr>
                  <tr><td></td><td align="center"><button type="button" id="flashoff" onclick="fetch(document.location.origin+'/control?var=flashoff&val=0');">关灯</button></td><td></td></tr>
                  </table>
                </div>
                <br>
                <div id="sliders" class="slider-container">
                  <table>
                  <tr><td>电机俗度:</td><td align="center" colspan="2"><input type="range" id="speed" min="0" max="255" value="200" onchange="try{fetch(document.location.origin+'/control?var=speed&val='+this.value);}catch(e){}"></td></tr>
                  <tr><td>视频质量:</td><td align="center" colspan="2"><input type="range" id="quality" min="10" max="63" value="10" onchange="try{fetch(document.location.origin+'/control?var=quality&val='+this.value);}catch(e){}"></td></tr>
                  <tr><td>视频大小:</td><td align="center" colspan="2"><input type="range" id="framesize" min="0" max="6" value="5" onchange="try{fetch(document.location.origin+'/control?var=framesize&val='+this.value);}catch(e){}"></td></tr>
                  </table>
                </div>
            </section>         
    </body>
</html>
)rawliteral";

static esp_err_t index_handler(httpd_req_t *req)
{
  // API to set the HTTP content type This API sets the 'Content Type' field of the response. The default content type is 'text/html'
  // API设置HTTP内容类型此API设置响应的“内容类型”字段。默认内容类型为“text/html”
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}

void startCameraServer()
{
  httpd_config_t config = HTTPD_DEFAULT_CONFIG(); //==================================================第零步：设置置基本的响应请求(回调函数)

  httpd_uri_t index_uri = {//设置响应内容类型，并上传HTML文件
                           .uri = "/",
                           .method = HTTP_GET,
                           .handler = index_handler, //设置响应内容类型，并上传HTML文件
                           .user_ctx = NULL};

  httpd_uri_t status_uri = {//设置json回应
                            .uri = "/status",
                            .method = HTTP_GET,
                            .handler = status_handler,
                            .user_ctx = NULL};

  httpd_uri_t cmd_uri = {//获取URL信息
                         .uri = "/control",
                         .method = HTTP_GET,
                         .handler = cmd_handler,
                         .user_ctx = NULL};

  Serial.printf("Starting web server on port: '%d'\n", config.server_port);
  if (httpd_start(&camera_httpd, &config) == ESP_OK)
  { //=============================================第一步：httpd_start() 配置,开始配置
    httpd_register_uri_handler(camera_httpd, &index_uri);
    httpd_register_uri_handler(camera_httpd, &cmd_uri);
    httpd_register_uri_handler(camera_httpd, &status_uri);
  }

  config.server_port += 1;
  config.ctrl_port += 1;
  Serial.printf("Starting stream server on port: '%d'\n", config.server_port);
}

unsigned int get_speed(unsigned int sp)
{
  return map(sp, 0, 100, 0, 255);
}
//管脚输出初始化============================================================================================================================//
void robot_setup()
{
  // Pins for Motor Controller
  pinMode(LEFT_M0, OUTPUT);
  pinMode(LEFT_M1, OUTPUT);
  pinMode(RIGHT_M0, OUTPUT);
  pinMode(RIGHT_M1, OUTPUT);

  // Make sure we are stopped
  robot_stop();

  // Motor uses PWM Channel 8
  ledcAttachPin(MTR_PWM, 8);
  ledcSetup(8, 2000, 8);
  ledcWrite(8, 130);
}

// 管脚输出=================================================================================================================================//

void update_speed()
{
  ledcWrite(motorPWMChannnel, get_speed(motor_speed));
}

void robot_stop()
{
  digitalWrite(LEFT_M0, LOW);
  digitalWrite(LEFT_M1, LOW);
  digitalWrite(RIGHT_M0, LOW);
  digitalWrite(RIGHT_M1, LOW);
}

void robot_fwd()
{
  digitalWrite(LEFT_M0, HIGH);
  digitalWrite(LEFT_M1, LOW);
  digitalWrite(RIGHT_M0, HIGH);
  digitalWrite(RIGHT_M1, LOW);
  move_interval = 250;
  previous_time = millis();
}

void robot_back()
{
  digitalWrite(LEFT_M0, LOW);
  digitalWrite(LEFT_M1, HIGH);
  digitalWrite(RIGHT_M0, LOW);
  digitalWrite(RIGHT_M1, HIGH);
  move_interval = 250;
  previous_time = millis();
}

void robot_right()
{
  digitalWrite(LEFT_M0, LOW);
  digitalWrite(LEFT_M1, HIGH);
  digitalWrite(RIGHT_M0, HIGH);
  digitalWrite(RIGHT_M1, LOW);
  move_interval = 100;
  previous_time = millis();
}

void robot_left()
{
  digitalWrite(LEFT_M0, HIGH);
  digitalWrite(LEFT_M1, LOW);
  digitalWrite(RIGHT_M0, LOW);
  digitalWrite(RIGHT_M1, HIGH);
  move_interval = 100;
  previous_time = millis();
}
