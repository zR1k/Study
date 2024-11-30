#pragma once
#include <memory>
#include "boost/asio.hpp"
#include <iostream>
#include <queue>

using namespace boost;
const int RECVSIZE = 1024;
class MsgNode{
public:
    MsgNode(const char* msg, int total_len): _total_len(total_len), _cur_len(0){
        _msg = new char[total_len];
        memcpy(_msg, msg, total_len);

    }

    MsgNode(int total_len): _total_len(total_len), _cur_len(0){
        _msg = new char[total_len];
    }

    ~MsgNode(){
        delete[] _msg;
    }
    int _total_len;
    char* _msg;
    int _cur_len;
};

class Session{
public:
    Session(std::shared_ptr<asio::ip::tcp::socket> socket);
    void Connect(const asio::ip::tcp::endpoint& ep);
    void WriteCallback(const boost::system::error_code& ec, std::size_t bytes_transferred, 
                        std::shared_ptr<MsgNode>);
    void WriteToSocket(const std::string buf);
    void WriteToSocket(const std::string& buf);
    void WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void WriteALLToSocket(const std::string& buf);
    void WriteALLCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void ReadFromSocket();
    void ReadCallBack(const boost::system::error_code& ec);
private:
    std::queue<std::shared_ptr<MsgNode> >_send_queue;
    std::shared_ptr<asio::ip::tcp::socket> _socket;
    std::shared_ptr<MsgNode> _send_node;
    bool _send_pending;
    bool _recv_pending;
};