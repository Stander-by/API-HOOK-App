from asyncio import sleep
from base64 import encode
import threading
import win32file
import win32pipe
import pywintypes
import json
from .config import *
pid = 0
eventUID = 1
recv_pipe = 0
send_pipe = 0
Wserver=0

def getPid():
    global pid
    return pid


def recvThread():
    global recv_pipe,Wserver
    PIPE_NAME = r'\\.\pipe\d2p'
    PIPE_BUFFER_SIZE = 65535
    recv_pipe = win32pipe.CreateNamedPipe(PIPE_NAME,
                                          win32pipe.PIPE_ACCESS_DUPLEX,
                                          win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT | win32pipe.PIPE_READMODE_MESSAGE,
                                          win32pipe.PIPE_UNLIMITED_INSTANCES,
                                          PIPE_BUFFER_SIZE,
                                          PIPE_BUFFER_SIZE, win32pipe.NMPWAIT_WAIT_FOREVER, None)
    while True:
        try:
            win32pipe.ConnectNamedPipe(recv_pipe, None)
            print("[INFO]Pipe connected.")
            while True:
                try:
                    win32pipe.ConnectNamedPipe(recv_pipe, None)
                    data = win32file.ReadFile(
                        recv_pipe, PIPE_BUFFER_SIZE, None)
                    if data is None or len(data) < 2:
                        continue
                    rawstr = data[1].decode()
                    rawstr = rawstr.replace("\x00", "")
                    # rawstr = rawstr.replace("\\\\","\\")
                    rawjson = json.loads(rawstr)
                    print(rawjson)
                    Wserver.send_message_to_all(json.dumps(rawjson,ensure_ascii=False))

                except BaseException as e:
                    print("[INFO] Pipe disconnected, try to reconnect.")
                    break
        except BaseException as e:
            try:
                win32pipe.DisconnectNamedPipe(recv_pipe)
            except:
                continue


def sendThread():
    global send_pipe,Wserver
    PIPE_NAME = r'\\.\Pipe\p2d'
    PIPE_BUFFER_SIZE = 65535
    send_pipe = win32pipe.CreateNamedPipe(PIPE_NAME,
                                          win32pipe.PIPE_ACCESS_DUPLEX,
                                          win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT | win32pipe.PIPE_READMODE_MESSAGE,
                                          win32pipe.PIPE_UNLIMITED_INSTANCES,
                                          PIPE_BUFFER_SIZE,
                                          PIPE_BUFFER_SIZE, win32pipe.NMPWAIT_WAIT_FOREVER, None)
    while True:
        try:
            win32pipe.ConnectNamedPipe(send_pipe, None)
            #print("[INFO]Pipe connected.")
            while True:
                try:
                    #check if pipe is connected
                    win32pipe.PeekNamedPipe(send_pipe, 0)
                    sleep(1)
                    if len(DllMsg_tosend) > 0:
                        print("send msg:", DllMsg_tosend[0])
                        tosend_str = json.dumps(DllMsg_tosend[0]).encode()
                        win32file.WriteFile(send_pipe, tosend_str)
                        DllMsg_tosend.pop(0)
                        print("send msg done")

                except BaseException as e:
                    #print("[INFO] Pipe disconnected, try to reconnect.")
                    break
        except BaseException as e:
            try:
                win32pipe.DisconnectNamedPipe(send_pipe)
            except:
                continue


def run(WS):
    global Wserver
    Wserver=WS
    rt = threading.Thread(target=recvThread)
    rt.start()
    st = threading.Thread(target=sendThread)
    st.start()
    print("[INFO]Pipe server is running")
