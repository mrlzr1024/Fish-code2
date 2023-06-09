/*
  程序： Tasks之间数据传递
        有多任务同时写入，或者数据大小超过cpu内存通道时，或者对共享资源的访问时候，需要有防范机制
        使用MUTEX对数据对Cirtical Section的内容进行保护
        可以想象成MUTEX就是一把锁

  公众号：孤独的二进制

  语法：
  SemaphoreHandle_t xHandler; 创建Handler
  xHandler = xSemaphoreCreateMutex(); 创建一个MUTEX 返回NULL，或者handler
  xSemaphoreGive(xHandler); 释放
  xSemaphoreTake(xHanlder, timeout); 指定时间内获取信号量 返回pdPASS, 或者pdFAIL

  理解方法：
  MUTEX的工作原理可以想象成
  共享的资源被锁在了一个箱子里，只有一把钥匙，有钥匙的任务才能对改资源进行访问
*/

// 养成良好习惯，被多进程和中断调用的变量使用 volatile 修饰符
volatile uint32_t inventory = 100; //总库存
volatile uint32_t retailCount = 0; //线下销售量
volatile uint32_t onlineCount = 0; //线上销售量

SemaphoreHandle_t xMutexInventory = NULL; //创建信号量Handler

TickType_t timeOut = 1000; //用于获取信号量的Timeout 1000 ticks


void retailTask(void *pvParam) {
  while (1) {

    // 在timeout的时间内如果能够获取就继续
    // 通俗一些：获取钥匙
    if (xSemaphoreTake(xMutexInventory, timeOut) == pdPASS) {
      //被MUTEX保护的内容叫做 Critical Section


      //以下实现了带有随机延迟的 inventory减1；
      //等效为 inventory--； retailCount++；
      uint32_t inv = inventory;
      for (int i; i < random(10, 100); i++) vTaskDelay(pdMS_TO_TICKS(i));
      if (inventory > 0) {
        inventory = inv - 1;
        retailCount++;

        //释放钥匙
        xSemaphoreGive(xMutexInventory);
      } else {
        //无法获取钥匙
      }


    };

    vTaskDelay(100); //老板要求慢一些，客户升级后，可以再加快速度
  }
}

void onlineTask(void *pvParam) {
  while (1) {

    // 在timeout的时间内如果能够获取二进制信号量就继续
    // 通俗一些：获取钥匙
    if (xSemaphoreTake(xMutexInventory, timeOut) == pdPASS) {
      //被MUTEX保护的内容叫做 Critical Section
      //以下实现了带有随机延迟的 inventory减1；
      //等效为 inventory--； retailCount++；
      uint32_t inv = inventory;
      for (int i; i < random(10, 100); i++) vTaskDelay(pdMS_TO_TICKS(i));
      if (inventory > 0) {
        inventory = inv - 1;
        onlineCount++;

        //释放钥匙
        xSemaphoreGive(xMutexInventory);
      } else {
        //无法获取钥匙
      }
    };

    vTaskDelay(100); //老板要求慢一些，客户升级后，可以再加快速度
  }
}


void showTask(void *pvParam) {
  while (1) {

    printf("Inventory : %d\n", inventory);
    printf("  Retail : %d, Online : %d\n", retailCount, onlineCount);


    if (inventory == 0 ) {
      uint32_t totalSales = retailCount + onlineCount;
      printf("-----SALES SUMMARY-----\n");
      printf("  Total Sales:  %d\n", totalSales);
      printf("  OverSales:  %d\n", 100 - totalSales);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  xMutexInventory = xSemaphoreCreateMutex(); //创建MUTEX

  if (xMutexInventory == NULL) {
    printf("No Enough Ram, Unable to Create Semaphore.");
  } else {
    xTaskCreate(onlineTask,
                "Online Channel",
                1024 * 4,
                NULL,
                1,
                NULL);
    xTaskCreate(retailTask,
                "Retail Channel",
                1024 * 4,
                NULL,
                1,
                NULL);
    xTaskCreate(showTask,
                "Display Inventory",
                1024 * 4,
                NULL,
                1,
                NULL);
  }

}

void loop() {
}
