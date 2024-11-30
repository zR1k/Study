#pragma once
#include <memory>
#include "boost/asio.hpp"
#include <iostream>

using namespace boost;
const int RECVSIZE = 1024;
class MsgNode{
public:
    MsgNode(const char* msa, int total_len): _total_len(total_len), _cur{

    }
private:
    int _total_len;
    char _msg[RECVSIZE];
    int _cur_len;
};

class Session{
public:
    Session(std::shared_ptr<asio::ip::tcp::socket> socket);
    void Connect(const asio::ip::tcp::endpoint& ep);
private:
    std::shared_ptr<asio::ip::tcp::socket> _socket;

};