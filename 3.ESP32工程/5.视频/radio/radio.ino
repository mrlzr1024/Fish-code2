/*
 * @Author: your name
 * @Date: 2022-03-06 11:45:31
 * @LastEditTime: 2022-03-08 18:16:18
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \4.WIFI开关\My_switch\My_switch.ino
 */
/*
 * @Author: your name
 * @Date: 2022-03-02 20:09:03
 * @LastEditTime: 2022-03-04 14:12:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \2.网络沙盒\wed_sabdbox.ino
 */
#include "camera.hpp"
const int output = 4;
//HTML框架修改位置：629(索引)
static  char FR_init[] = R"EOT(<html>
<head>
	<meta charset="utf-8">
	<title>菜鸟教程(runoob.com)</title>
	<!格式：居中>
	<style>
		html { font-family: Helvetica; 
				display: inline-block;
				text-align: center;}
		.button { background-color: #4CAF50; 
					border: none; 
					color: white;
					padding: 16px 40px;
					text-decoration: none; 
					font-size: 30px; 
					margin: 2px; 
					cursor: pointer;}
		.button2{background-color:#555555;
					border: none; 
					color: white;
					padding: 16px 40px;
					text-decoration: none; 
					font-size: 30px; 
					margin: 2px; 
					cursor: pointer;}
	</style>
</head>
<body>
<h1>ESP32网络服务器 </h1>
</body>
</html>)EOT";

/*=============================================================================*/
/*=============================================================================*/
static  char FR_on[] = R"EOT(
<iframe src="/jpg" width="600" height="300"></iframe>
|LZR|
<p>GPIO 14 - State " ON "</p>
<p>
<a href = "/off">
<button class = "button">ON</button>
</a>
</p>)EOT";

/*=============================================================================*/
/*=============================================================================*/
static  char FR_off[] = R"EOT(

<video id="myVideo" controls autoplay> 
<source id="mp4_src" src="/jpg" type="video/mp4">
</video>
<button onclick="myFunction()">点我</button>
<script>
function myFunction() {
	document.getElementById("mp4_src").src = "/cam";
	document.getElementById("myVideo").load();
}
</script>


|LZR|
<p>GPIO 14 - State " OFF "</p>
<p>
<a href = "/on">
<button class = "button">OFF</button>
</a>
</p>)EOT";
/*=============================================================================*/
/*=============================================================================*/
char C[1000];


//插入函数 A:主数组 B：从数组 in:要插入位置A的索引
int Insert( char* A,  char* B, int in) {
	int i=0;
	memset(C,0,sizeof(C));
	if (in > strlen(A)) {
		return 0;
	}
	for (int j=0; j <= in; j++) {
		C[j] = A[j];
	}
	for (int j = in+1; j <=in+ strlen(B); j++) {
		C[j] = B[j-in-1];
	}
	for (int j = in + strlen(B)+1; j <strlen(A) + 114; j++) {
		C[j] = A[j- strlen(B)];
	}
return 0;
}


void Server_web(){
    server.on("/on",
            HTTP_GET,
            []
            {
            Insert(FR_init,FR_on,626);
            server.setContentLength(sizeof(C));
            server.send(200, "text/html");
            server.sendContent(C, sizeof(C));
			//digitalWrite(output, HIGH);
            Serial.println("LED ON");});
    server.on("/off",
            HTTP_GET,
            []
            {
            Insert(FR_init,FR_off,626);
            server.setContentLength(sizeof(C));
            server.send(200, "text/html");
            server.sendContent(C, sizeof(C));
			//digitalWrite(output, LOW);
            Serial.println("LED OFF");});
}
void setup()
{
    Camera_Init();
	pinMode(output, OUTPUT);
    //设置初始值为低电平
    digitalWrite(output, LOW);
    Server_web();
    server.begin();
}
void loop()
{
    server.handleClient();
}
