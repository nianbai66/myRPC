#当前目录所有源文件名字，放到SRC_LIST里
aux_source_directory(. SRC_LIST)  

#生成mprpc动态库，用srclist的源文件编译构建      
#add_library(mprpc SHARED ${SRC_LIST})，muduo是.a静态库
add_library(mprpc ${SRC_LIST})

# 为mprpc设置依赖，需要注意muduo库的连接顺序，net是核心模块，其他都依赖这个，所以先连接net
#target_link_libraries(mprpc muduo_net muduo_base pthread)
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)