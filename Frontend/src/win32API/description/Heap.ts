import {opCodeDescription,to32Hex,toMemorySize} from "./until";

function HeapAlloc(info:any){
    return {
        "hHeap": {
            "description": "操作堆的句柄",
            "value": to32Hex(info["hHeap"])
        },
        "dwFlags": {
            "description": "申请选项",
            "value":opCodeDescription(info["dwFlags"],"HeapOptions")
        },
        "dwBytes":{
            "description": "要分配的字节数",
            "value":toMemorySize(info["dwBytes"])
        },
        "return":{
            "description":"分配内存块的指针",
            "value":to32Hex(info["address"])
        }
    }
}

function HeapCreate(info:any){
    return{
        "fIOptions": {
            "descrioption": "创建选项",
            "value": opCodeDescription(info["fIOption"],"HeapOptions")
        },
        "dwInitialSize": {
            "description": "堆的初始大小",
            "value": toMemorySize(info["dwInitialSize"]),
        },
        "dwMaximumSize": {
            "description": "堆的最大大小",
            "value": toMemorySize(info["dwMaximumSize"])
        },
        "return": {
            "description": "创建堆的句柄",
            "value": to32Hex(info["hHeap"])
        }
    }

}

function HeapDestroy(info:any){
    return{
        "hHeap": {
            "description": "要摧毁的堆的句柄",
            "value": to32Hex(info["hHeap"])
        },
        "return": {
            "description": "摧毁结果",
            "value": (info["return"])
        }
    }
}

function Heapfree(info:any){
    return{
        "hHeap": {
            "description": "操作堆的句柄",
            "value": to32Hex(info["hHeap"])
        },
        "dwFlags": {
            "description": "释放选项",
            "value": opCodeDescription(info["dwFlags"], "HeapOptions")
        },
        "lpMem": {
            "description": "释放地址",
            "value": to32Hex(info["lpMem"])
        },
        "return": {
            "description": "释放结果",
            "value": info["return"]
        }
    }
}