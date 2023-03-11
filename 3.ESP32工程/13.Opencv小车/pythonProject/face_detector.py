# made by LZR
import urllib.request
import cv2
import numpy as np
import time
import tkinter  # GUI
import threading  # 多线程

import matplotlib.pyplot as plt

core_url = "http://192.168.137.253/"

main_url = core_url + 'jpg'
left_request = core_url + 'left?val='
right_request = core_url + 'right?val='
forward_request = core_url + 'up?val='
back_request = core_url + 'back?val='
stop_request = core_url + 'stop'
deviation_request = core_url + 'deviation?val='
tmp = 0
top = tkinter.Tk()
top.geometry('450x300')
top.geometry('+1000+300')
turn = tkinter.StringVar()
Speed = tkinter.StringVar()
deviation = tkinter.StringVar()
deviation.set(0)


# ====================================================================================================#
def face_detect_demo(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # 分类器
    face_detect = cv2.CascadeClassifier('D:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml')
    face = face_detect.detectMultiScale(gray, 1.2, 2)

    if type(face) == np.ndarray:
        for x, y, w, hw in face:
            cv2.rectangle(img, (x, y), (x + w, y + hw), color=(0, 9, 250), thickness=5)
            if (x+w)/2 >img.shape[0]/2:
                cv2.putText(img, f"left", (20, 60), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (0, 233, 0), thickness=2)
                # print("left")
            elif (x+w)/2 <img.shape[0]/2:
                # print("right")
                cv2.putText(img, f"right", (20, 60), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (233, 0, 233), thickness=2)
    cv2.imshow("..", img)


v = tkinter.StringVar()
turning = tkinter.Scale(top,
                        from_=1000,
                        resolution=10,
                        length=100,  # 设置像素
                        to=0,
                        # orient=tkinter.HORIZONTAL,  # 设置横向
                        variable=turn  # 绑定变量
                        )
speed = tkinter.Scale(top,
                      from_=1000,
                      resolution=10,
                      length=100,  # 设置像素
                      to=0,
                      # orient=tkinter.HORIZONTAL,  # 设置横向
                      variable=Speed  # 绑定变量
                      )
Deviation = tkinter.Scale(top,
                          from_=500,
                          resolution=10,
                          length=100,  # 设置像素
                          to=-500,
                          # orient=tkinter.HORIZONTAL,  # 设置横向
                          variable=deviation  # 绑定变量
                          )
# ====================================================================================================#

label_turn = tkinter.Label(top, bg='black', fg='white', text='转向速度')
label_speed = tkinter.Label(top, bg='black', fg='white', text='速度')
label_Dev = tkinter.Label(top, bg='black', fg='white', text='偏转(左)')
label_Dev2 = tkinter.Label(top, bg='black', fg='white', text='偏转(右)')

f = tkinter.Button(width=10, height=5, text='前进', command=lambda: urllib.request.urlopen(forward_request + Speed.get()))
r = tkinter.Button(width=10, height=5, text='向右', command=lambda: urllib.request.urlopen(right_request + turn.get()))
l = tkinter.Button(width=10, height=5, text='向左', command=lambda: urllib.request.urlopen(left_request + turn.get()))
b = tkinter.Button(width=10, height=5, text='后退', command=lambda: urllib.request.urlopen(back_request + Speed.get()))
d = tkinter.Button(width=10, height=5, text='偏转',
                   command=lambda: urllib.request.urlopen(deviation_request + deviation.get()))
s = tkinter.Button(width=10, height=5, text='停止', command=lambda: urllib.request.urlopen(stop_request))
light_on = tkinter.Button(text='开灯', command=lambda: urllib.request.urlopen(core_url + 'on'))
light_off = tkinter.Button(text='关灯', command=lambda: urllib.request.urlopen(core_url + 'off'))

f.grid(row=0, column=1)
r.grid(row=1, column=2)
l.grid(row=1, column=0)
s.grid(row=1, column=1)
b.grid(row=2, column=1)
d.grid(row=2, column=2)
# 负为偏向右
label_Dev.grid(row=0, column=9)
label_turn.grid(row=0, column=5)
label_speed.grid(row=0, column=7)
speed.grid(row=1, column=7)
turning.grid(row=1, column=5)
Deviation.grid(row=1, column=9)
light_off.grid(row=2, column=6)
light_on.grid(row=2, column=5)
label_Dev2.grid(row=2, column=9)


# ====================================================================================================#

def camera():
    global tmp
    while True:  # 反复刷新页面以到达视频效果
        last = time.time()
        imgResp = urllib.request.urlopen(
            main_url)  # 用于打开一个远程的url连接,并且向这个连接发出请求,获取响应结果。返回的结果是一个http响应对象,这个响应对象中记录了本次http访问的响应头和响应体
        imgNp = np.array(bytearray(imgResp.read()), dtype=np.uint8)  # 读出响应体并转化为uint8格式
        img = cv2.imdecode(imgNp, -1)  # 指定的内存缓存中读取数据，并把数据转换(解码)成图像格式
        cv2.putText(img, f"fps={tmp}", (20, 40), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (0, 233, 0), thickness=2)
        # cv2.imshow('test', img)
        face_detect_demo(img)
        new = time.time()
        fps = 1 // (new - last)
        tmp = fps
        if cv2.waitKey(1) == 0x27:
            urllib.request.urlopen(forward_request)
            # cv2.destroyAllWindows()
            break


another = threading.Thread(target=camera)
another.start()
top.mainloop()
