#pragma once
#include <memory>
#include "boost/asio.hpp"
#include <iostream>

using namespace boost;
const int RECVSIZE = 1024;
class MsgNode{
public:
    MsgNode(const char* msa, int totasl_len): _total_len(total_len){

    }
private:
    int _total_len;
    char _msg[RECVSIZE];
    
};

class Session{
public:
    Session(std::shared_ptr<asio::ip::tcp::socket> socket);
    void Connect(const asio::ip::tcp::endpoint& ep);
private:
    std::shared_ptr<asio::ip::tcp::socket> _socket;

};