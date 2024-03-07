import subprocess
from flask import Flask
from flask import render_template, send_from_directory, request, redirect, url_for
import os
from flask_cors import CORS, cross_origin
import serverThread.websocketServer as websocketServer
import serverThread.pipeThread as pipeThread
from serverThread.config import *
# import signal
# import sys
# 全局变量 共享的文件夹路径 可以根据需求更改
DIRECTORY_PATH = ""
# 创建项目
app = Flask(__name__,static_url_path='/', static_folder='/')
CORS(app)
app.config['SECURE_KEY'] = 'askydiqyddiudhiudiwuhdhdyjqoijd'

targetProcess = None
targetThread = None
@app.route("/") 
def index():
    """共享文件主页"""
    #return render_template("index.html", files=get_files_data())
    return render_template("index.html")

@app.route("/download_file/<filename>")
def file_content(filename):
    """下载文件的URL"""
    if filename in os.listdir(DIRECTORY_PATH): # 如果需求下载文件存在
        # 发送文件 参数：文件夹路径，文件路径，文件名
        return send_from_directory(DIRECTORY_PATH, filename)
    else:
        # 否则返回错误页面
        return render_template("download_error.html", filename=filename)

@app.route("/upload_file", methods=['GET', 'POST'])
def upload():
    if request.method == "POST":
    	# 获取文件 拼接存储路径并保存
        upload_file = request.files.get("upload_file")
        upload_file.save(os.path.join(DIRECTORY_PATH, upload_file.filename))

		#  返回上传成功的模板
        return render_template("upload_ok.html", filename=upload_file.filename)

	# 上传的网页
    return render_template("upload.html")

@app.route("/messages")
def messages():
    Wserver.send_message_to_all("server send message")
    return WSmessages
    
    
@app.route("/pipe")
def pipe():
    global DllMsg_tosend
    DllMsg_tosend.append({"msg":"trigger"})
    return {"status": "success","tosen":DllMsg_tosend}


# def quit(signum, frame):
#     exitSignal=True
#     sys.exit(0)

if __name__ == '__main__':
    # 捕获ctrl+c，关闭所有线程并退出
    Wserver = websocketServer.run(port=8765)
    # signal.signal(signal.SIGINT, quit)
    pipeThread.run(Wserver)
    app.run(host="0.0.0.0", port="5000")