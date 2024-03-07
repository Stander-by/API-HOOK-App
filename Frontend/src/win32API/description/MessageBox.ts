import {opCodeDescription,to32Hex,toMemorySize} from "./until";
 
function MessageBoxA(info:any){
    return{
        "hWnd": {
            "description": "父窗口句柄",
            "value": to32Hex(info['hWnd'])
        },
        "lpText": {
            "description": "弹窗标题",
            "value": info['lpText']
        },
        "lpCaption": {
            "description": "弹窗内容",
            "value": info['lpCaption']
        },
        "uType": {
            "description": "弹窗样式选项（部分解析）",
            "value": opCodeDescription(info['uType'],'MessageBoxType')
        },
        "return": {
            "description": "按下的按钮",
            "value": opCodeDescription(info['return'], 'MessageBoxReturn')
        }
    }
}