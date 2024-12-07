//本地服务发布成RPC服务的方法

#include<iostream>
#include<string>

#include"../friend.pb.h"//包含protobuf头文件
#include "mprpcapplication.h"
#include "rpcprovider.h"


//继承了RPC::UserServiceRpc,就封装成了一个RPC方法

class FriendService : public RPC::FriendServiceRpc{
public:
    //本地的获取好友列表方法
    std::vector<std::string> GetFriendList(uint32_t userid)
    {
        std::cout<<" do GetFriendList service!"<<std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("liu hong");
        vec.push_back("wang shuo");
        return vec;
    }

    /*
    重写基类UserServiceRpc的虚函数，框架调用这个重写的登录函数
    1.caller远程调用者发起远程调用请求Login(LoginRequest)=>muduo=>callee
    2.callee发现远程请求调用Login(LoginRequest)=>交付给下面这个重写的方法

    1.从LoginRequest获取参数的值
    2.执行本地Login方法，并获取返回值
    3.用上面的返回值填写LoginResponse
    4.一个回调，把LoginResonse发送给发起RPC服务的主机
    */
    void GetFriendList(::google::protobuf::RpcController* controller,
                       const ::RPC::GetFriendListRequest* request,
                       ::RPC::GetFriendListResponse* response,
                       ::google::protobuf::Closure* done){
        uint32_t userid=request->userid();
        std::vector<std::string> friendList=GetFriendList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(std::string name : friendList){
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }

};

// //框架发布rpc服务节点
// int main(int argc,char **argv){
//     //先调用框架的初始化操作 provider -i config.conf，从init方法读取配置服务，比如IP地址和端口号,
//     //从test.conf读取ip地址
//     MprpcApplication::Init(argc,argv);
//     //创建一个服务提供者
//     RpcProvider provider;
//     //把userservice对象发布到RPC服务提供者节点上,这个节点必须有个服务对象，可能是user服务or注册服务等，所以基类指针可以接收子类对象
//     //将这个服务得方法注册到一个表中
//     provider.NotifyService(new FriendService());

//     //启动一个rpc服务发布节点，run以后，进程进入阻塞状态，等待远程的rpc请求
//     //使用muduo网络库,绑定自己得连接，通信，回调函数
//     provider.Run();
    
//     return 0;


// }