#set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST userservice.cc ../user.pb.cc ../friend.pb.cc)
#通过list的源文件创建可执行文件provider
add_executable(provider ${SRC_LIST})
#需要连接的库：mprpc（自己写得框架静态库）和protobuf库链接到provider
target_link_libraries(provider mprpc protobuf)