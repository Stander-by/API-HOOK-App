import {opCodeDescription,to32Hex,toMemorySize} from "./until";

function _lclose(info:any){
    return {
        "hFile": {
            "description": "操作句柄",
            "value": (info["hHeap"])
        },
        "return": {
            "description": "文件关闭句柄",
            "value": (info["return"])
        }
    }
}


function CloseHandle(info: any) {
    return {
        "hObject": {
            "description": "要关闭的文件句柄",
            "value": [(info["hFile"]), info["path"]]
        },
        "return": {
            "description": "执行结果",
            "value": (info["return"])
        }
    }
}

function CreateFileA(info: any){
    return {
        "lpFileName": {
            "description": "创建或打开的文件或设备的名称",
            "value": info["lpFileName"]
        },
        "dwDesiredAccess": {
            "description": "申请访问权限",
            "value": opCodeDescription(info["dwDesiredAccess"], "FileAccessMask")
        },
        "dwShareMode": {
            "description": "共享模式",
            "value":opCodeDescription(info["dwShareMode"], "FileFlagsAndAttributes")
        },
        "lpSecurityAttributes": {
            "description": "安全参数结构指针",
            "value": to32Hex(info["lpSecurityAttributes"])
        },
        "dwCreationDisposition": {
            "description": "文件打开方式",
            "value": opCodeDescription(info["dwCreationDisposition"], "FileCreationDisposition")
        },
        "dwFlagsAndAttributes": {
            "description": "设置文件参数",
            "value": opCodeDescription(info["dwFlagsAndAttributes"], "FileFlagsAndAttributes")
        },
        "hTemplate": {
            "description": "模板文件句柄",
            "value": to32Hex(info["hTemplateFile"])
        },
        "return": {
            "description": "文件句柄",
            "value": to32Hex(info["handle"])
        }
}
}

function OpenFile(info: any){
    return {
        "lpFileName": {
            "description": "文件名",
            "value": info["lpFileName"]
        },
        "lpReOpenBuff": {
            "description": "参数结构体指针",
            "value": to32Hex(info["lpReOpenBuff"])
        },

        "uStyle": {
            "description": "操作代码",
            "value": to32Hex(info["uStyle"])
        },
        "return": {
            "description": "操作句柄",
            "value": to32Hex(info["hFile"])
        }
}
}


function ReadFile(info: any){
    return {
        "hFile": {
            "description": "文件句柄",
            "value": [to32Hex(info["hFile"]), info["path"]]
        },
        "lpBuffer": {
            "description": "Buffer地址",
            "value": to32Hex(info["lpBuffer"]),
            "buffer": info.get("lpBufferValue", "")
        },
        "nNumberOfBytesToRead": {
            "description": "最大读取字节数",
            "value": toMemorySize(info["nNumberOfBytesToRead"])
        },
        "lpNumberOfBytesRead": {
            "description": "读取字节数的指针",
            "value": to32Hex(info["lpNumberOfBytesRead"])
        },
        "lpOverlapped": {
            "description": "指向OVERLAPPED参数的指针",
            "value": to32Hex(info["lpOverlapped"])
        },
        "return": {
            "description": "执行结果",
            "value": (info['return'])
        }
}
}

function WriteFile(info: any){

return {
    "hFile": {
        "description": "文件句柄",
        "value": [to32Hex(info["hFile"]), info["path"]]
    },
    "lpBuffer": {
        "description": "Buffer地址",
        "value": to32Hex(info["lpBuffer"]),
        "buffer": info.get("lpBufferValue", "")
    },
    "nNumberOfBytesToWrite": {
        "description": "最大写字节数",
        "value": toMemorySize(info["nNumberOfBytesToWrite"])
    },
    "lpNumberOfBytesWritten": {
        "description": "写字节数的指针",
        "value": to32Hex(info["lpNumberOfBytesWritten"])
    },
    "lpOverlapped": {
        "description": "指向OVERLAPPED参数的指针",
        "value": to32Hex(info["lpOverlapped"])
    },
    "return": {
        "description": "执行结果",
        "value": (info['return'])
    }

}
}


export { _lclose, CloseHandle, CreateFileA, OpenFile, ReadFile, WriteFile }