#include "chatserver.hpp"
#include "chatserveice.hpp"
#include "json.hpp"
 
#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册新用户连接&断开回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 注册文件传输回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置服务器线程数量 一个I/O线程 3个工作线程
    _server.setThreadNum(4);
}
void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown(); // 释放socket
    }
}
//读写事件相关的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 解析json数据 反序列化
    json js = json::parse(buf);
    // 完全解耦网络模块和业务模块代码
    //如何解耦？ 1.面向接口   2.回调函数
    //  通过js["msgid"] 获取业务handler 传递三个参数 conn js time
    auto msgHandler=ChatServeice::instance()->getHander(js["msgid"].get<int>());
    msgHandler(conn,js,time);
     
}
