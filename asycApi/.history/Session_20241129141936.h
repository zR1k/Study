#pragma once
#include <memory>
#include "boost/asio.hpp"
#include <iostream>

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
private:
    int _total_len;
    char* _msg;
    int _cur_len;
};

class Session{
public:
    Session(std::shared_ptr<asio::ip::tcp::socket> socket);
    void Connect(const asio::ip::tcp::endpoint& ep);
private:
    std::shared_ptr<asio::ip::tcp::socket> _socket;
    std::shared_ptr<
};