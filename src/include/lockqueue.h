#pragma once
#include<queue>
#include<thread>
#include<mutex>//对应linux下的pthread_mutex_t
#include<condition_variable>//对应linux下的pthread_condition_t

//异步写日志的日志队列
template<typename T>
class LockQueue
{
public:
    //多个worker线程都会写日志queue，
    void Push(const T &data){
            //多个工作线程写日志，加锁
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        //队列有消息了，唤醒那个io线程，
        m_condvariable.notify_one();//只有一个线程来io操作
    }

    //一个线程读日志queue
    T Pop(){
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_queue.empty())
        {
            //日志队列为空，线程进入wait状态
            m_condvariable.wait(lock);
        }
        
        //不为空时开始处理
        T data=m_queue.front();
        m_queue.pop();
        return data;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condvariable;
};