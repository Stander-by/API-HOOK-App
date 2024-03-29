import { stringifyQuery } from "vue-router";

let opCode: {[key:string]: {[key:string]:string}}  = {
    "MessageBoxType": {
        0x00000002: "MB_ABORTRETRYIGNORE [中止/重试/忽略]",
        0x00000006: "MB_CANCELTRYCONTINUE [取消/重试/继续]",
        0x00004000: "MB_HELP [添加帮助按钮]",
        0x00000000: "MB_OK [确定]",
        0x00000001: "MB_OKCANCEL [确定/取消]",
        0x00000005: "MB_RETRYCANCEL [重试/取消]",
        0x00000004: "MB_YESNO [是/否]",
        0x00000003: "MB_YESNOCANCEL [是/否/取消]"
    },
    "MessageBoxReturn": {
        3: "IDABORT [中止]",
        2: "IDCANCEL [取消]",
        11: "IDCONTINUE [继续]",
        5: "IDIGNORE [忽略]",
        7: "IDNO [否]",
        1: "IDOK [确定]",
        4: "IDRETRY [重试]",
        10: "IDTRYAGAIN [重试]",
        6: "IDYES [是]"
    },
    "HeapOptions": {
        0x00040000: "HEAP_CREATE_ENABLE_EXECUTE [关闭数据执行保护]",
        0x00000004: "HEAP_GENERATE_EXCEPTIONS [调用失败时引发异常]",
        0x00000001: "HEAP_NO_SERIALIZE [不使用序列化访问]",
        0x00000008: "HEAP_ZERO_MEMORY [初始化为0]"
    },
    "FileAccessMask": {
        0x80000000: "GENERIC_READ [一般读权限]",
        0x40000000: "GENERIC_WRITE [一搬写权限]"
    },
    "FileShareMode": {
        0x00000000: "0 [阻止其它进程访问]",
        0x00000004: "FILE_SHARE_DELETE [允许删除访问权限]",
        0x00000001: "FILE_SHARE_READ [允许读取访问权限]",
        0x00000002: "FILE_SHARE_WRITE [允许写访问权限]"
    },
    "FileCreationDisposition": {
        2: "CREATE_ALWAYS [总是创建文件]",
        1: "CREATE_NEW [不存在时创建文件]",
        4: "OPEN_ALWAYS [总是打开文件]",
        3: "OPEN_EXISTING [文件存在时打开文件]",
        5: "TRUNCATE_EXISTING [文件存在时清空文件]"
    },
    "FileFlagsAndAttributes": {
        128: "FILE_ATTRIBUTE_NORMAL [无属性]",
    },
    "RegeditHkey": {
        0x80000000: "HKEY_CLASSES_ROOT",
        0x80000005: "HKEY_CURRENT_CONFIG",
        0x80000001: "HKEY_CURRENT_USER",
        0x80000002: "HKEY_LOCAL_MACHINE",
        0x80000003: "HKEY_USERS"
    },
    "RegeditOptions": {
        0x00000000: "REG_OPTION_NON_VOLATILE [此键不易失]",
        0x00000001: "REG_OPTION_VOLATILE [此键易失]",
        0x00000002: "REG_OPTION_CREATE_LINK [此键为符号链接]",
        0x00000004: "REG_OPTION_BACKUP_RESTORE [使用备份/恢复权限打开]",
        0x00000008: "REG_OPTION_OPEN_LINK [此键为符号链接]"
    },
    "RegeditKeyAccess": {
        0xF003F: "KEY_ALL_ACCESS [全部权限]",
        0x20019: "KEY_READ [读取键相关权限]",
        0x20006: "KEY_WRITE [写键相关权限]",
        0x0020: "KEY_CREATE_LINK [保留供系统使用]",
        0x0004: "KEY_CREATE_SUB_KEY [创建子项]",
        0x0008: "KEY_ENUMERATE_SUB_KEYS [枚举子项]",
        0x0010: "KEY_NOTIFY [请求更改通知]",
        0x0001: "KEY_QUERY_VALUE [查询值]",
        0x0002: "KEY_SET_VALUE [设置值]",
        0x0000: "NULL [继承父键]"
    },
    "RegeditDisposition": {
        0x00000000: "无处置信息",
        0x00000001: "REG_CREATED_NEW_KEY [键不存在并已创建]",
        0x00000002: "REG_OPENED_EXISTING_KEY [键存在并打开]"
    },
    "RegeditType": {
        0: "REG_NONE [无类型]",
        1: "REG_SZ [Unicode字符串]",
        2: "REG_EXPAND_SZ [含环境变量字符串]",
        3: "REG_BINARY [二进制类型]",
        4: "REG_DWORD [32位字符]",
        5: "REG_DWORD_BIG_ENDIAN [32位大端存储]",
        6: "REG_LINK [含符号字符串]",
        7: "REG_MULTI_SZ [多个字符串]",
        11: "REG_QWORD [64位数字]",
    },
    "SocketAf": {
        0: "AF_UNSPEC [地址族未指定]",
        2: "AF_INET [IPV4]",
        23: "AF_INET6 [IPV6]"
    },
    "SocketType": {
        1: "SOCK_STREAM",
        2: "SOCK_DGRAM",
        3: "SOCK_RAW",
        4: "SOCK_RDM",
        5: "SOCK_SEQPACKET",
    },
    "SocketProtocol": {
        0: "[未指定]",
        1: "ICMP",
        2: "IGMP",
        6: "TCP",
        17: "UDP",
        58: "ICMPV6",
        113: "PGM"
    },
    "SocketInfo": {
        0xffffffff: "INVALID_SOCKET [无效套接字]"
    }
}
let socketList:{[key:string]:string}={

}
function opCodeDescription(code:string,index:string){
    if(index in opCode){
        if(code in opCode[index]){
            return opCode[index][code];
        }
        else{
            return "未知";
        }
    }
    return "未知";
}


function to32Hex(value: { toString: (arg0: number) => string; }) {
    return "0x" + ("00000000" + value.toString(16)).slice(-8);
}

function toMemorySize(value: number) {
    if (value < 1024) {
        return value + "B";
    }
    if (value < 1024 * 1024) {
        return (value / 1024).toFixed(2) + "KB";
    }
    if (value < 1024 * 1024 * 1024) {
        return (value / 1024 / 1024).toFixed(2) + "MB";
    }
    return (value / 1024 / 1024 / 1024).toFixed(2) + "GB";
}

function Clock(){

}

function joinSocketAddr(code:string,index:string){
    return code;
}

function checkReturn(code:string){

}

function join(){

}
export  {opCodeDescription,to32Hex,toMemorySize,joinSocketAddr,socketList,checkReturn,join}
