# made by LZR
import cv2 as cv
import numpy as np


def face_detect_demo(img):
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    # 分类器
    face_detect = cv.CascadeClassifier('D:/opencv/sources/data/haarcascades/haarcascade_upperbody.xml')
    face = face_detect.detectMultiScale(gray, 1.2, 2)
    # print(type(face))
    if type(face) == np.ndarray:
        for x, y, w, hw in face:
            cv.rectangle(img, (x, y), (x + w, y + hw), color=(0, 9, 250), thickness=5)
            if (x+w)/2 >img.shape[0]/2:
                cv.putText(img, f"left", (20, 60), cv.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (0, 233, 0), thickness=2)
                # print("left")
            elif (x+w)/2 <img.shape[0]/2:
                # print("right")
                cv.putText(img, f"right", (20, 60), cv.FONT_HERSHEY_SCRIPT_SIMPLEX, 1, (233, 0, 233), thickness=2)
    cv.imshow("..", img)


# ========================== #
# 看视频♂ 不停读取帧并显示：
'''1.打开：cv.VideoCapture(···) '···'为你设备摄像头的id，默认为0或-1就是(0)，如果引用usb可能会改变为1
   2.加速：cv.waitKey(1) 这里使用 waitKey 可以控制视频的播放速度，数值越小，播放速度越快
   3.cv.waitKey(1) & 0xFF == 27:这里等于 27 也即是说按下 ESC 键即可退出该窗口
   4.读取下一帧：video.read()
   5.光标复位：video.release()'''
video = cv.VideoCapture(0)
if video.isOpened():
    open, frame = video.read()
    print('ok')
else:
    open = False
while open:
    ret, frame = video.read()
    # 如果读到的帧数不为空，那么就继续读取，如果为空，就退出
    if frame is None:
        break
    if ret:
        face_detect_demo(frame)
        # 转换为灰度图
        # gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        # cv.imshow("video", frame)
        # 这里使用 waitKey 可以控制视频的播放速度，数值越小，播放速度越快
        # 这里等于 27 也即是说按下 ESC 键即可退出该窗口
        # cv.imshow("..", frame)
        if cv.waitKey(1) & 0xFF == 27:
            break
video.release()
cv.destroyAllWindows()

# ========================== #
