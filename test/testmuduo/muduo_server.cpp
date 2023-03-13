#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
/*
1.
*/
class ChatServer
{
public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg)
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //注册新用户连接&断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        //注册文件传输回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        //设置服务器线程数量 一个I/O线程 3个工作线程
        _server.setThreadNum(4);
    }
    void start()
    {
        _server.start();
    }

private:
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:pffline" << endl;
        }
    }
    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp time)
    {
        string buf =buffer->retrieveAllAsString();
        cout<<"recv data:"<<buf<<"time:"<<time.toString()<<endl;
        conn->send(buf);
    }
    TcpServer _server;
    EventLoop *_loop;
};

int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000); 
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();//等待新用户连接
    return 0;
}