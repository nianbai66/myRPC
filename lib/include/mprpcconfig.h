#pragma once

#include<unordered_map>
#include<string>

//框架读取配置文件类,配置文件内容：rpcserverip,rpcserverport,zookeeperip,zookeeperport
class MprpcConfig
{
public:
    //负责解析加载配置文件
    void LoadConfigFile(const char *file);
    //查询配置项信息
    std::string Load(std::string const &key);
private:
    //ip和端口的键值对，不用以后每次都读文件
    std::unordered_map<std::string,std::string> m_configMap;
    //去掉字符串前后的空格
    void Trim(std::string &src_buf);
};