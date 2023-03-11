#include "css.h"

char FR[] = R"rawliteral(<!DOCTYPE html>
<html>
<head>
<title>页面标题</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
* {
    box-sizing: border-box;
}
body {
    font-family: Arial;
    margin: 0;
}
.header {
    padding:142px;
    text-align: center;
    background: #1abc9c;
    color: white;
}
.header h1 {
    font-size: 40px;
}
.navbar {
    overflow: hidden;
    background-color: #333;
}
.navbar a {
    float: left;
    display: block;
    color: white;
    text-align: center;
    padding: 14px 20px;
    text-decoration: none;
}
.navbar a.right {
    float: right;
}
.navbar a:hover {
    background-color: #ddd;
    color: black;
}
.row {  
    display: -ms-flexbox;
    display: flex;
    -ms-flex-wrap: wrap;
    flex-wrap: wrap;
}
.side {
    -ms-flex: 30%; 
    flex: 30%;
    background-color: #f1f1f1;
    padding: 20px;
}
.main {   
    -ms-flex: 70%;
    flex: 70%;
    background-color: white;
    padding: 20px;
}
.fakeimg {
    background-color: #aaa;
    width: 100%;
    padding: 20px;
}
.footer {
    padding: 20px;
    text-align: center;
    background: #ddd;
}
@media screen and (max-width: 700px) {
    .row {   
        flex-direction: column;
    }
}
@media screen and (max-width: 400px) {
    .navbar a {
        float: none;
        width: 100%;
    }
}
</style>
</head>
<body>
<div class="header">
  <h1>智能手环</h1>
  <p>made by 32位 小组</p>
</div>

<div class="navbar">
  <a href="#">日期:0000-00-00</a>
  <a href="#">时间:00:00</a>
  <a href="#">步数:99999</a>
  <a href="#" class="right">心率:100</a>
</div>
<div class="row">
  <div class="side">
      <h2>关于我们</h2>
      <h5>我们的照片:</h5>
      <div class="fakeimg" style="height:200px;">
      <img src="https://ts1.cn.mm.bing.net/th/id/R-C.c24c0054588179b0d1f55965041eb480?rik=MGH4Lp%2bYZhKjxA&riu=http%3a%2f%2fi0.hdslb.com%2fbfs%2farchive%2f6b2f2eaa8dcba6c4c6b4c4a9adf1afb039504f62.jpg&ehk=h2ZZ%2bpu77lem8YBTNRapvStxovjFYMhiUcBqWL3F%2bnU%3d&risl=&pid=ImgRaw&r=0" width="300" height="170"></div>
      <p>关于我的介绍..</p>
      <h3>更多内容</h3>
      <div class="fakeimg" style="height:60px;">
      组长&&程序：梁芝瑞
      </div><br>
      <div class="fakeimg" style="height:60px;">组员&&美工：韦宋润</div><br>
      <div class="fakeimg" style="height:60px;">组员&&PCB：王宇航</div>
  </div>
  
</div>

<div class="footer">
  <h2>谢谢观看</h2>
</div>

</body>


</html>)rawliteral";

/*

<div class="main">
      <h2>标题</h2>
      <h5>副标题</h5>
      <div class="fakeimg" style="height:200px;">图像</div>
      <p>一些文本..</p>
      <p>菜鸟教程，学的不仅是技术，更是梦想！！！菜鸟教程，学的不仅是技术，更是梦想！！！菜鸟教程，学的不仅是技术，更是梦想！！！</p>
      <br>
      <h2>标题</h2>
      <h5>副标题</h5>
      <div class="fakeimg" style="height:200px;">图像</div>
      <p>一些文本..</p>
      <p>菜鸟教程，学的不仅是技术，更是梦想！！！菜鸟教程，学的不仅是技术，更是梦想！！！菜鸟教程，学的不仅是技术，更是梦想！！！</p>
  </div>



<script language="JavaScript">
 function myrefresh(){
 window.location.reload();
 }
 setTimeout('myrefresh()',5000); //指定5秒刷新一次
 </script>
*/
void Add(String da)
{
    //日期：1466
    //时间：1514
    //步数：1545
    //心率：1590
    int date = 1478 - 1;
    int hour = 1514 - 1;
    int Step = 1545 - 1;
    int heart = 1590 - 1;
    FR[date] = da[1];
    FR[date + 1] = da[2];
    FR[date + 2] = da[3];
    FR[date + 3] = da[4];
    //月
    FR[date + 5] = da[5];
    FR[date + 6] = da[6];
    //日
    FR[date + 8] = da[7];
    FR[date + 9] = da[8];

    //小时
    FR[hour] = da[9];
    FR[hour + 1] = da[10];
    //分钟
    FR[hour + 3] = da[11];
    FR[hour + 4] = da[12];
    //步数：1592（1591~1595）
    FR[Step] = da[13];
    FR[Step + 1] = da[14];
    FR[Step + 2] = da[15];
    FR[Step + 3] = da[16];
    FR[Step + 4] = da[17];
    //心率：1640
    FR[heart] = da[18];
    FR[heart + 1] = da[19];
    FR[heart + 2] = da[20];
}

