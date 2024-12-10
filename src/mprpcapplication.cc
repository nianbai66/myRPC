#include"mprpcapplication.h"
#include<iostream>
#include<unistd.h>
#include<string>


MprpcConfig MprpcApplication::m_config;

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}
//实现成全局的方法
void ShowArgHelp()
{
    std::cout<<"format:command -i <configfile>"<<std::endl;
    
}
void MprpcApplication::Init(int argc,char **argv)
{
    if(argc<2)//参数不足
    {
        ShowArgHelp();//打印参数的配置说明
        exit(EXIT_FAILURE);
    }

    //使用getopt读取参数
    int c=0;
    std::string config_file;//配置选项
    while((c=getopt(argc,argv,"i:"))!=-1)           //getopt解析出命令行参数的-i，以及他的对应参数
    {
        switch (c)
        {
        case 'i'://指定选项，optarg 是 getopt 函数内部使用的一个全局变量，用于存储当前解析到的带有参数值的选项（在这里就是 -i 选项）所对应的参数值。
            config_file=optarg;                 //这里就是test.conf
            break;
        case '?'://出现了不想要的参数
            std::cout<<"invalid args"<<std::endl;
            
            ShowArgHelp();
            exit(EXIT_FAILURE);
        case ':':
            std::cout<<"need <configfile>"<<std::endl;
            
            ShowArgHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    //开始加载配置文件 加载IP，端口，zk的IP和端口
    m_config.LoadConfigFile(config_file.c_str());

    // std::cout<<"rpcserverip:"<<m_config.Load("rpcserverip")<<std::endl;
    // std::cout<<"rpcserverport:"<<m_config.Load("rpcserverport")<<std::endl;
    // std::cout<<"zookeeperip:"<<m_config.Load("zookeeperip")<<std::endl;
    // std::cout<<"zookeeperport:"<<m_config.Load("zookeeperport")<<std::endl;
    
}

MprpcConfig& MprpcApplication::GetConfig(){
    
    return m_config;        //返回配置项
}