#include "mprpccontroller.h"

//类的构造函数,默认false
MprpcController::MprpcController()
{
    m_failed=false;
    m_errtext="";
}

void MprpcController::Reset()
{
    m_failed=false;
    m_errtext="";
}

bool MprpcController::Failed()const
{
    return m_failed;
}

std::string MprpcController::ErrorText()const
{
    return m_errtext;
}
//出现错误，设置报错信息
void MprpcController::SetFailed(const std::string& reason)
{
    m_failed=true;
    m_errtext=reason;
}

void MprpcController::StartCancel(){}
bool MprpcController::IsCanceled()const{return false;}
void MprpcController::NotifyOnCancel(google::protobuf::Closure *callback){}