import { opCodeDescription, to32Hex, toMemorySize, joinSocketAddr, socketList, checkReturn,join } from "./until";

function closesocket(info: any) {
    let res: { [key: string]: { [key: string]: string } } = {
        "s": {
            "description": "连接的套接字",
            "value": to32Hex(info["s"])
        },
        "return": {
            "description": "执行结果",
            "value": (info["status"])
        }

    }
    if ("errorCode" in info) {
        res["errorCode"] = {
            "description": "错误代码",
            "value": (info["errorCode"])
        }

    }
    return res
}

function connect(info: any) {
    let event: { [key: string]: { [key: string]: string } } = {
        "s": {
            "description": "连接的套接字",
            "value": to32Hex(info["s"])
        },
        "name": {
            "description": "套接字连接信息指针",
            "value": to32Hex(info["sockaddr"])
        },
        "namelen": {
            "description": "套接字连接信息长度",
            "value": toMemorySize(info["namelen"])
        }


    }

    if ("sa_family" in info) {
        event["sa_family"] = {
            "description": "连接地址族规范",
            "value": opCodeDescription(info["sa_family"], "SocketAf")
        }
        event["eventDescription"]["name"]["buffer"] = info["nameValue"]
        if ("sin_addr" in info) {
            event["sin_addr"] = {
                "description": "连接目标",
                "value": joinSocketAddr(info["sin_addr"], info["sin_port"])
            }
        }
        event["description"] = "套接字连接 {}".format(event["eventDescription"]["sin_addr"]["value"])
        socketList[info["s"]] = event["eventDescription"]["sin_addr"]["value"]


    }
    event = {
        "return": {
            "description": "执行结果",
            "value": (info["status"])
        }
    }
    if ("errorCode" in info) {
        event = {
            "errorCode": {
                "description": "错误代码",
                "value": (info["errorCode"])
            }
        }
    }
    return event
}

function recv(info: any) {
    //checkReturn
    let res: { [key: string]: { [key: string]: string } } = {
        "s": {
            "description": "连接的套接字",
            "value": to32Hex(info["s"])//, socketList.get(info["s"], "[UnKnown]")]
        },
        "buf": {
            "description": "缓冲区地址",
            "value": to32Hex(info["buf"]),
            "buffer": info.get('bufValue', "")
        },
        "len": {
            "description": "缓冲区长度",
            "value": toMemorySize(info["len"])
        },
        "flags": {
            "description": "函数执行参数标志",
            "value": to32Hex(info["flags"])
        },
        "return": {
            "description": "接受字节数",
            "value": checkReturn(info["status"])
        }
    }
    if ("errorCode" in info) {
        res["errorCode"] = {
            "description": "错误代码",
            "value": info["errorCode"]
        }
    }
    return res
}

function send(info: any) {
    let res: { [key: string]: { [key: string]: string } } = {
        "s": {
            "description": "连接的套接字",
            "value": to32Hex(info["s"])//, socketList.get(info["s"], "[UnKnown]")]
        },
        "buf": {
            "description": "缓冲区地址",
            "value": to32Hex(info["buf"]),
            "buffer": info.get('bufValue', "")
        },
        "len": {
            "description": "缓冲区长度",
            "value": toMemorySize(info["len"])
        },
        "flags": {
            "description": "函数执行参数标志",
            "value": to32Hex(info["flags"])
        },
        "return": {
            "description": "发送字节数",
            "value": checkReturn(info["status"])
        }
    }
    if ("errorCode" in info) {
        res["errorCode"] = {
            "description": "错误代码",
            "value": info["errorCode"]
        }
    }
    return res
}

function socket(info: any) {
    let res: { [key: string]: { [key: string]: string } } = {
        "af": {
            "description": "地址族规范",
            "value": opCodeDescription(info["af"], "SocketAf")
        },
        "type": {
            "description": "套接字的类型规范",
            "value": opCodeDescription(info["type"], "SocketType")
        },
        "protocol": {
            "description": "要使用的协议",
            "value": opCodeDescription(info["protocol"], "SocketProtocol")
        },
        "return": {
            "description": "socket描述符",
            "value": opCodeDescription(info["socket"], "SocketInfo")
        }
    }
    if ("errorCode" in info) {
        res["errorCode"] = {
            "description": "错误代码",
            "value": info["errorCode"]
        }
    }
    return res
}

function WSACleanup(info: any) {
    let res: { [key: string]: { [key: string]: string } } = {
        "return": {
            "description": "执行结果",
            "value": info["status"]
        }

    }
    if ("errorCode" in info) {
        res["errorCode"] = {
            "description": "错误代码",
            "value": info["errorCode"]
        }
        return res
    }
}

function WSAStartup(info:any){
    let res: { [key: string]: { [key: string]: string } } = {
        "wVersionRequired": {
            "description": "请求的套接字版本号",
            "value": [to32Hex(info["wVersionRequired"]), join(info["wVersionRequiredPrimary"],info["wVersionRequiredSecondary"])]
        },
        "wVersion": {
            "description": "返回的套接字版本号",
            "value": "[未返回]"
        },
        "lpWSAData": {
            "description": "套接字信息结构地址",
            "value": to32Hex(info["lpWSAData"], "NULL")
        },
        "return": {
            "description": "执行结果",
            "value": info["status"]
        }
    }
    return res
}