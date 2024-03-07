import os
import subprocess
from websocket_server import WebsocketServer
import asyncio
import json
import websockets
import threading
from .config import *



def new_client(client, server):
	print("New client connected and was given id %d" % client['id'])
	#server.send_message_to_all("Hey all, a new client has joined us")


def client_left(client, server):
	print("Client(%d) disconnected" % client['id'])


def message_received(client, server, message):
	# if len(message) > 200:``
	# 	message = message[:200]+'..'
	# print("Client(%d) said: %s" % (client['id'], message))
    try:
        WSmessages.append(json.loads(message))
    except:
        print("error message:", message)
    message=json.loads(message)
    if 'cmd' in message and message['cmd'] == 'start':
        if os.path.exists(message['path']):
            targetProcess = subprocess.Popen(["D:\\Project\\C++Project\\Task_SoftwareSecurity\\vvtapp\\injector\\x64\\Debug\\Injector.exe",message['path']], shell=True)    
            server.send_message(client, "start success")
            return

    message = "I got your message: {}".format(message)
    server.send_message(client, message)



def poll(server):
    server.set_fn_new_client(new_client)
    server.set_fn_client_left(client_left)
    server.set_fn_message_received(message_received)
    server.run_forever()

# run on new thread
def run(ip='localhost', port=8765):
    server = WebsocketServer(port = port)
    wsthread = threading.Thread(target=poll, args={server})
    wsthread.start()
    print("[INFO]Websocket server is running on: "+ip+":"+str(port))
    return server
