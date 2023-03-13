#ifndef CHATSERVEICE_H
#define CHATSERVEICE_H

#include"json.hpp"
#include<unordered_map>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include<functional>
using json =nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

//处理消息的事件回调方法类型
using MsgHandler=std::function<void(const TcpConnectionPtr &conn,json &js,Timestamp)>;
class ChatServeice{
public:
    //获取单例对象的接口函数
    static ChatServeice* instance();
    void login(const TcpConnectionPtr &conn,json &js,Timestamp time);
    void reg(const TcpConnectionPtr &conn,json &js,Timestamp time);
    // 获取消息对应的处理器
    MsgHandler getHander(int msgid);
private:
    ChatServeice();
    //存储消息id和其对应的业务处理方法
    unordered_map<int,MsgHandler> _msgHandlerMap;
}

#endif