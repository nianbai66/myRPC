#pragma once

#include "mprpcconfig.h"

//mprpc框架的基础类，负责框架的一些初始化操作，使用单例模式设计
//src框架的代码cpp提供成一个动态库,和头文件提供

class MprpcApplication
{
public:
    //初始化
    static void Init(int argc,char **argv);
    //获取实例
    static MprpcApplication& GetInstance();
    
    //获取配置
    static MprpcConfig& GetConfig();
private:
    //Rpc服务的配置
    static MprpcConfig m_config;
    //构造函数
    MprpcApplication(){};
    MprpcApplication(const MprpcApplication&)=delete;
    MprpcApplication(MprpcApplication&&)=delete;
};