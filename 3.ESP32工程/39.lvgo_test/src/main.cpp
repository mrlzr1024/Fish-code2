

 #include <Arduino.h>
int freq = 50;      // 频率(20ms周期)
int channel = 0;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
int resolution = 8; // 分辨率
int led = 15;
 
int calculatePWM(int degree)
{ //0-180度
 //20ms周期，高电平0.5-2.5ms，对应0-180度角度
  const float deadZone = 6.4;//对应0.5ms（0.5ms/(20ms/256）) 舵机转动角度与占空比的关系：(角度/90+0.5)*1023/20
  const float max = 32;//对应2.5ms
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone);
}
 
void setup()
{
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution); // 设置通道
  ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
}
 
void loop()
{
  for (int d = 0; d <= 180; d += 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM
   
    Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
    delay(100);
  }  
  led = 4;
   ledcAttachPin(led, channel); 
  for (int d = 180; d >= 0; d -= 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM
    Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
    delay(100);
  }  

}

