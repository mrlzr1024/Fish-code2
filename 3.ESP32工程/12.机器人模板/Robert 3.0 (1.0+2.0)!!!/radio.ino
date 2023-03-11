/*
   @Author: your name
   @Date: 2022-03-06 11:45:31
 * @LastEditTime: 2022-03-20 09:05:52
 * @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \4.WIFI开关\My_switch\My_switch.ino
*/
/*
   @Author: your name
   @Date: 2022-03-02 20:09:03
   @LastEditTime: 2022-03-04 14:12:06
   @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \2.网络沙盒\wed_sabdbox.ino
*/
#include "camera.hpp"
const int output = 4;
//关键一----参数抓取：arg() —— 获取请求参数的值
//<!关键二---HTML----fetch()发出HTTP请求>
static  char FR_init[] = R"EOT(<html>
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
    <dir>
            <img loading="lazy" src="\cam" width="800" height="600">
            </dir>
            <section id="buttons">

                <div id="controls" class="control-container">
                  <table>
                  <!关键二-------fetch()发出HTTP请求>
                  <tr><td></td><td align="center"><button type="button" id="forward" onclick="window.stop(); fetch(document.location.origin+'/control?var=car&val=1'; document.getElementById('stream').src=document.location.origin+'/cam';;);">前进</button></td><td></td></tr>
                  <tr><td align="center"><button type="button" id="turnleft" onclick="window.stop(); fetch(document.location.origin+'/control?var=car&val=2');">向左</button></td><td align="center"></td>
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
</html>)EOT";

/*=============================================================================*/
/*=============================================================================*/

void Server_web() {
  /*=============================================================================*/
  server.on("/on",
            HTTP_GET,
            []
  { // Insert(FR_init,FR_on,626);
    server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("LED ON");
  });
  /*=============================================================================*/
  server.on("/off",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("LED OFF");
  });
  /*=============================================================================*/
  server.on("/left",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("left");
  });
  /*=============================================================================*/
  server.on("/right",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("right");
  });
  /*=============================================================================*/
  server.on("/up",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("forward");
  });
  /*=============================================================================*/
  server.on("/back",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("back");
  });
  /*=============================================================================*/
  server.on("/",
            HTTP_GET,
            []
  { server.setContentLength(sizeof(FR_init));
    server.send(200, "text/html");
    server.sendContent(FR_init, sizeof(FR_init));
    //digitalWrite(output, HIGH);
    Serial.println("OK");
  });
}
void setup()
{
  pinMode(output, OUTPUT);
  Camera_Init();

  //设置初始值为低电平
  digitalWrite(output, LOW);
  Server_web();
  server.begin();
}
void loop()
{Serial.print("var=");
  Serial.println(server.arg("var"));
  //关键一----参数抓取：arg() —— 获取请求参数的值
  //String arg(String name);
  Serial.print("val=");
  Serial.println(server.arg("val"));
  server.handleClient();
}
