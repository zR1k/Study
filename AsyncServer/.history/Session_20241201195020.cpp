#include "Session.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
            std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

void Session::handle_read(const boost::system::error_code& error, 
    size_t bytes_transferred, std::shared_ptr<Session> self){
    if(!error){
        std::cout << "server received data is:" << _data << std::endl;
        boost::asio::async_write(_socket, boost::asio::buffer(_data, bytes_transferred),
            std::bind(&Session::handle_write, this, std::placeholders::_1, self));
    }
    else{
        std::cerr << "Error: " << error.message() << std::endl;
        delete this;
    }
}

void Session::handle_write(const boost::system::error_code& error, std::shared_ptr<Session> self){
    if(!error){
        memset(_data, 0, max_length);
        _socket.async_read_some(boost::asio::buffer(_data, max_length),
            std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2, self));
    }
    else{
        std::cerr << "Error: " << error.message() << std::endl;
        delete this;
    }
}
