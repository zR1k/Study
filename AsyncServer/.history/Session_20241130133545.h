#pragma once
#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Session{
public:
    Session(boost::asio::io_context& ioc) : _socket(ioc){

    }
    tcp::socket& Socket(){
        return _socket;
    }

    void Start()
private:
    tcp::socket _socket;
    enum{max_length = 1024};
    char _data[max_length];
};