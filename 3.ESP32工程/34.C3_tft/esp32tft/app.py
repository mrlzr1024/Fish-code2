from flask import Flask, Response, request, render_template
from werkzeug.utils import secure_filename
import os

app = Flask(__name__)

# 设置图片保存文件夹
UPLOAD_FOLDER = 'photo'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# 设置允许上传的文件格式
ALLOW_EXTENSIONS = ['png', 'jpg', 'jpeg']


# 查看图片
@app.route("/<imageId>.png")
def get_frame(imageId):
    # 图片上传保存的路径
    with open(fr'E:/1.咸鱼先生的单片机开发文件/3.ESP32工程/34.C3_tft/esp32tft/show/{imageId}.png', 'rb') as f:
        print("ok")
        image = f.read()
        resp = Response(image, mimetype="image/png")
        return resp


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)
