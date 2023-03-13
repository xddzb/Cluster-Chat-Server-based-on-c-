#include "chatserveice.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>
using namespace muduo;
// 单例函数的接口函数
ChatServeice *ChatServeice::instance()
{
    static ChatServeice serveice;
    return serveice;
}
// 获取消息对应的处理器
MsgHandler ChatServeice::getHander(int msgid)
{
    // 记录错误日志 msgid没有对应的处理回调
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {
        //返回一个默认的处理器，空操作
        return [=](const TcpConnectionPtr &conn,json &js,Timestamp){
            LOG_ERROR<<"msgid:"<<msgid<<"can not find handler!";
        }
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}
// 注册消息以及对应的回调操作
ChatServeice::ChatServeice()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatServeice::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatServeice::reg, this, _1, _2, _3)});
}

// 登录业务
void ChatServeice::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
}

// 注册业务
void ChatServeice::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
}