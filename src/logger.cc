#include"logger.h"
#include<time.h>
#include<iostream>
//获取单例对象时才创建：懒汉式单例模式，
//饿汉式单例模式：类加载时就创建对象，全局只有一个实例
Logger& Logger::GetInstance(){
    static Logger logger;
    return logger;
}

Logger::Logger(){

    //写日志线程
    std::thread writeLogtask([&](){
        for(;;){

            //获取当前时间
            time_t now = time(nullptr);
            tm* nowtm = localtime(&now);
            char filename[128];
            sprintf(filename , "%d-%d-%d",nowtm->tm_year+1900 , nowtm->tm_mon+1 , nowtm->tm_mday);

            //文件末尾追加读写，文件名为日期
            FILE* pf = fopen(filename , "a+");
            if(pf == nullptr){
                std::cout<<"logger file"<<filename<<" open error"<<std::endl;
                exit(EXIT_FAILURE);
            }
            //从消息队列读日志，写一个打开一次文件
            std::string msg = m_lockQueue.Pop();

            //加入时分秒
            char time_buf[128]={0};
            sprintf(time_buf,"%d:%d:%d => [%s] ",
                    nowtm->tm_hour,
                    nowtm->tm_min,
                    nowtm->tm_sec,
                    (m_loglevel==INFO?"info":"error"));
            msg.insert(0,time_buf);
            msg.append("\n");

            fputs(msg.c_str() , pf);
            fclose(pf);

        }

    });
    //分离线程，守护线程
    writeLogtask.detach();
}
//设置日志级别
void Logger::StLogLevel(LogLevel level){
    m_loglevel = level;
}
//log写入lockqueue缓冲区中
void Logger::Log(std::string msg){
    m_lockQueue.Push(msg);
}