# made by LZR
import tkinter
import socket
import threading
import urllib.request
import cv2
import numpy as np
import time

url = 'http://192.168.137.35/cam-hi.jpg'  # 改成ip地址+/cam-hi.jpg 每一时刻的照片
ip = "192.168.137.38"


def camera():
    while True:  # 反复刷新页面以到达视频效果
        last = time.time()
        imgResp = urllib.request.urlopen(
            url)  # 用于打开一个远程的url连接,并且向这个连接发出请求,获取响应结果。返回的结果是一个http响应对象,这个响应对象中记录了本次http访问的响应头和响应体
        imgNp = np.array(bytearray(imgResp.read()), dtype=np.uint8)  # 读出响应体并转化为uint8格式
        img = cv2.imdecode(imgNp, -1)  # 指定的内存缓存中读取数据，并把数据转换(解码)成图像格式
        img3 = cv2.flip(cv2.transpose(img), 1)
        cv2.imshow('test', img3)
        new = time.time()
        fps = 1 / (new - last)
        print("fps=", fps)
        if ord('q') == cv2.waitKey(1):
            cv2.destroyAllWindows()
            break


cl = socket.socket()
cl.connect((ip, 10000))
print("连接中。。。。")
top = tkinter.Tk()
top.geometry('200x100')
top.geometry('+1000+300')

b = tkinter.Button(text='前进', command=lambda: cl.send(b"b"))
l = tkinter.Button(text='向右', command=lambda: cl.send(b"l"))
r = tkinter.Button(text='向左', command=lambda: cl.send(b"r"))
f = tkinter.Button(text='后退', command=lambda: cl.send(b"f"))
s = tkinter.Button(text='停止', command=lambda: cl.send(b"s"))
# TODO:
xa = tkinter.Button(text='右', command=lambda: cl.send(b"xad"))
xr = tkinter.Button(text='左', command=lambda: cl.send(b"xre"))
ya = tkinter.Button(text='上', command=lambda: cl.send(b"yad"))
yr = tkinter.Button(text='下', command=lambda: cl.send(b"yre"))

b.grid(row=0, column=1)
l.grid(row=1, column=2)
r.grid(row=1, column=0)
f.grid(row=2, column=1)
s.grid(row=1, column=1)

xa.grid(row=0, column=4)
xr.grid(row=0, column=5)
ya.grid(row=1, column=4)
yr.grid(row=1, column=5)
another = threading.Thread(target=camera)
another.start()
top.mainloop()
# while True:
#     mes = input("->").encode()
#     cl.send(mes)
#     print(f"已执行:{cl.recv(1024)}")
#     if mes == b'quit':
#         break
