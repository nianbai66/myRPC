#pragma once

#include<semaphore.h>
#include<zookeeper/zookeeper.h>
#include<string>

//rpc服务方和调用方都是zookeeper的客户端，分别调用创造节点和获取节点的方法
class ZKclient{
public:
    ZKclient();
    ~ZKclient();
    //开启一个zk客户端
    void Start();
    //往zk服务端根据指定path放入一个node，没有path将创建path
    void Create(const char* path , const char* data ,int datalen,int state = 0);
    //根据路径获取节点的值
    std::string GetData(const char *path);
private:
    //zk的客户端句柄,代表客户端和服务端连接
    zhandle_t *m_zhandle;
};

