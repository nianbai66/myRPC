# myRPC
# 介绍
本项目是一个集群分布式网络通信框架，基于C++、protobuf、zookeeper、muduo库开发

直接运行autobuild.sh（已加上可执行权限）执行来生成可执行文件。

成功生成后先启动zookeeper服务端，再进入bin目录，先启动服务器再启动客户端即可测试。

# 项目开发主要涉及
RPC远程过程调用原理以及实现

Protobuf数据序列化和反序列化协议

ZooKeeper分布式一致性协调服务应用以及编程

网络库编程

conf配置文件读取

异步日志模块

CMake构建项目集成编译环境

github管理项目

# 库准备
protoc，本地版本为3.12.4，ubuntu22使用`sudo apt-get install protobuf-compiler libprotobuf-dev`安装默认就是这个版本

boost，sudo apt-get install libboost-dev libboost-test-dev libboost-all-dev

muduo，[https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980](https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980)

# 项目结构
bin：可执行文件和配置文件

build：项目编译文件

lib：项目库文件

src：源文件

test：测试代码

example：框架使用示例

CMakeLists.txt：顶层的cmake文件

README.md：项目自述文件

autobuild.sh：一键编译脚本
