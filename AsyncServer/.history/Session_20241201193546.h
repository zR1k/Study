#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/uuid/uuid
using boost::asio::ip::tcp;

class Server;

class Session{
public:
    Session(boost::asio::io_context& ioc, Server* server) : _socket(ioc), _server(server){

    }
    tcp::socket& Socket(){
        return _socket;
    }

    void Start();
private:
    void handle_read(const boost::system::error_code& error, 
        size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);
    tcp::socket _socket;
    enum{max_length = 1024};
    char _data[max_length];
    Server* _server;
};