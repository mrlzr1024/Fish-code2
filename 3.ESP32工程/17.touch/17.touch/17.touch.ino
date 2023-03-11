// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
int a = 0;
void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop()
{
  //Serial.println(touchRead(T0));  // get value using T0
  a = touchRead(T0);
  if (a <= 50) {
    Serial.println(a);  // get value using T0
    Serial.println("嗯♂，夜色");
  }
  delay(200);
}
