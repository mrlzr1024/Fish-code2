import urllib.request
import cv2
import numpy as np
import time
import matplotlib.pyplot as plt

url = 'http://192.168.137.39/jpg'  # 改成ip地址+/cam-hi.jpg 每一时刻的照片
url1 = 'http://192.168.137.39/on'
# url = "http://192.168.137.35/cam"
tmp=0
while True:  # 反复刷新页面以到达视频效果
    last = time.time()
    imgResp = urllib.request.urlopen(
        url)  # 用于打开一个远程的url连接,并且向这个连接发出请求,获取响应结果。返回的结果是一个http响应对象,这个响应对象中记录了本次http访问的响应头和响应体
    imgNp = np.array(bytearray(imgResp.read()), dtype=np.uint8)  # 读出响应体并转化为uint8格式
    img = cv2.imdecode(imgNp, -1)  # 指定的内存缓存中读取数据，并把数据转换(解码)成图像格式
    cv2.putText(img, f"fps={tmp}", (20, 40), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (0, 233, 0), thickness=2)
    cv2.imshow('test', img)
    new = time.time()
    fps = 1 // (new - last)
    tmp=fps
    # print("fps=", fps)
    if cv2.waitKey(1)==27:
        urllib.request.urlopen(url1)
        print("send ON")
    if cv2.waitKey(1)=='q' :
        cv2.destroyAllWindows()
        break
    # if cv2.waitKey(0):
    #     imgResp1 = urllib.request.urlopen(
    #         url1)

