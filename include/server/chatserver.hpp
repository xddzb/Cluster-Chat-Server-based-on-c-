#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;


class ChatServer
{
public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);

    void start();

private:
    void onConnection(const TcpConnectionPtr &);
    void onMessage(const TcpConnectionPtr &,
                   Buffer *,
                   Timestamp);
    TcpServer _server;//muduo库 实现服务器功能的类对象
    EventLoop *_loop;//指向事件循环对象的指针
};

#endif