import {opCodeDescription,to32Hex,toMemorySize} from "./until";

//ConverEqual ConvertDict
//Convert0r ConvertDict
//formatErrorCode

function RegCloseKey(info:any){
    return{
        "hKey": {
            "description": "操作键句柄",
            "value": opCodeDescription(info["hKey"], "RegeditHkey")
        },
        "return": {
            "description": "执行结果 [系统错误代码]",
            "value":info["status"] //formatErrorCode
        }
    }
}

function RegCreateKeyExA(info:any){
    return{
        "hKey": {
            "description": "主键名称",
            "value": opCodeDescription(info["hKey"], "RegeditHkey")
        },
        "lpSubKey": {
            "description": "子键名称",
            "value": info["lpSubKey"],
        },
        "Reserved": {
            "description": "备用（为0）",
            "value": to32Hex(info["Reserved"])
        },
        "lpClass": {
            "description": "用户定义类类型",
            "value": info["lpClass"]
        },
        "dwOptions": {
            "description": "创建参数",
            "value": opCodeDescription(info["dwOptions"], "RegeditOptions")
        },
        "samDesired": {
            "description": "申请访问权限",
            "value": opCodeDescription(info["samDesired"], "RegeditKeyAccess")
        },
        "lpSecurityAttributes": {
            "description": "安全参数结构指针",
            "value": to32Hex(info["lpSecurityAttributes"])
        },
        "phkResult": {
            "description": "返回操作句柄",
            "value": to32Hex(info["phkResult"])
        },
        "lpdwDisposition": {
            "description": "处置信息",
            "value": opCodeDescription(info["lpdwDisposition"], "RegeditDisposition")
        },
        "return": {
            "description": "执行结果 [系统错误代码]",
            "value": info["status"] //formatErrorCode
        }
    }
}

function RegOpenKeyExA(info:any){
    return{
        "hKey": {
            "description": "主键名称",
            "value": opCodeDescription(info["hKey"], "RegeditHkey")
        },
        "ulOptions": {
            "description": "创建参数",
            "value": opCodeDescription(info["ulOptions"], "RegeditOptions")
        },
        "samDesired": {
            "description": "申请访问权限",
            "value": opCodeDescription(info["samDesired"], "RegeditKeyAccess")
        },
        "phkResult": {
            "description": "返回操作句柄",
            "value": to32Hex(info["phkResult"])
        },
        "return": {
            "description": "执行结果 [系统错误代码]",
            "value": info["status"] //formatErrorcode
        }
    }
}

function RegQueryValueExA(info:any){
    let res={
        "hKey": {
            "description": "键值句柄",
            "value": opCodeDescription(info["hKey"], "RegeditHkey")
        },
        "lpValueName": {
            "description": "键名",
            "value": info["lpValueName"]
        },
        "lpReserved": {
            "description": "备用（NULL）",
            "value": to32Hex(info["lpReserved"])
        },
        "lpType": {
            "description": "键值类型指针",
            "value": to32Hex(info["lpType"])
        },
        "lpData": {
            "description": "键值内容",
            "value": to32Hex(info["lpData"]),
            "buffer": info.get("lpDataValue", "")
        },
        "lpcbData": {
            "description": "内容长度",
            "value": toMemorySize(info["lpcbData"])
        },
        "return": {
            "description": "执行结果",
            "value": (info["status"])
        }
    }
    if("lpTypeValue" in info){
        res["lpType"] = {
            "description": "键值类型指针",
            "value": opCodeDescription(info["lpTypeValue"], "RegeditType")
        }
    }
    return res
}

function RegSetValueExA(info:any){
    return{
        "hKey": {
            "description": "键值句柄",
            "value": opCodeDescription(info["hKey"], "RegeditHkey")
        },
        "lpValueName": {
            "description": "键名",
            "value": info["lpValueName"]
        },
        "Reserved": {
            "description": "备用（NULL）",
            "value": to32Hex(info["Reserved"])
        },
        "dwType": {
            "description": "键值类型",
            "value": opCodeDescription(info["dwType"], "RegeditType")
        },
        "lpData": {
            "description": "键值内容",
            "value": to32Hex(info["lpData"]),
            "buffer": info.get("lpDataValue", "")
        },
        "cbData": {
            "description": "内容长度",
            "value": toMemorySize(info["cbData"])
        },
        "return": {
            "description": "执行结果",
            "value": (info["status"]) //formaterrorcode
        }
    }
}