import socket

ip = "192.168.137.251"
port = 8080
# 创建套接字，AF_INET代表使用的是IPV4,SOCK_DGRAM代表是tcp传输
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 连接服务端
s.connect((ip, port))
s.setblocking(False)
while 1:
    # data = input("请输入数据:")+'\n'
    # s.send(data.encode("utf-8"))
    # 接受数据会阻塞，1024表示接受的最大字节数1024，recv_data是返回的二进制内容，不会返回端口
    recv_data = s.recv(1024)
    print(recv_data.decode("utf-8"))
    # print("接收到：%s" % recv_data.decode("utf-8"))

