# made by LZR
import socket

ip = "192.168.137.253"
cl = socket.socket()
cl.connect((ip, 10000))
print("连接中。。。。")
while True:
    mes = input("->").encode()
    cl.send(mes)
    print(f"已执行:{cl.recv(1024)}")
    if mes == b'quit':
        break
