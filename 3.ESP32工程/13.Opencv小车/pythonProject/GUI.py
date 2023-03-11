# made by LZR
'''Scale为输出限定范围的数字区间，可以为之指定最大值，最小值及步距值等。
from_ 指定最小值
to指定最大值
（主要就是前两项）
resolution指定步长，默认是1
tickinterval设置刻度
orient设置横向(HORIZONTAL)和竖向(VERTICAL)'''

import tkinter

top = tkinter.Tk()
top.geometry('450x300')
top.geometry('+1000+300')
turn = tkinter.StringVar()
Speed = tkinter.StringVar()
deviation = tkinter.StringVar()
deviation.set(0)
# ====================================================================================================#
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
label_turn = tkinter.Label(top, bg='black', fg='white', text='转向速度')
label_speed = tkinter.Label(top, bg='black', fg='white', text='速度')
label_Dev = tkinter.Label(top, bg='black', fg='white', text='偏转')

# s1.pack()

f = tkinter.Button(width=10, height=5, text='前进', command=lambda: print("urllib.request.urlopen(forward_request"))
r = tkinter.Button(width=10, height=5, text='向右', command=lambda: print("urllib.request.urlopen(forward_request"))
l = tkinter.Button(width=10, height=5, text='向左', command=lambda: print("urllib.request.urlopen(forward_request"))
b = tkinter.Button(width=10, height=5, text='后退', command=lambda: print("urllib.request.urlopen(forward_request"))
s = tkinter.Button(width=10, height=5, text='停止', command=lambda: print("urllib.request.urlopen(forward_request"))
f.grid(row=0, column=1)
r.grid(row=1, column=2)
l.grid(row=1, column=0)
s.grid(row=1, column=1)
b.grid(row=2, column=1)

speed.grid(row=1, column=7)
turning.grid(row=1, column=5)
Deviation.grid(row=1, column=9)
label_turn.grid(row=0, column=5)
label_speed.grid(row=0, column=7)
label_Dev.grid(row=0, column=9)

print(type(Speed))
top.mainloop()
