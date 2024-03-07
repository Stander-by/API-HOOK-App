class ApiStack { 
    // 字段 
    title:string; 
    description:[];
    time:string;
    warnnings:[];
    param:[];
    api_return:string;
    // 构造函数
    constructor(title:string,description:[],time:string,warnnings:[],param:[],api_return:string) {
        this.title = title;
        this.description = description;
        this.time = time;
        this.warnnings = warnnings;
        this.param = param;
        this.api_return = api_return;
    }
}





export default ApiStack;