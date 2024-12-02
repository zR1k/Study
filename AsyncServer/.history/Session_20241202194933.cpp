#include "Session.h"
#include "Server.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
            std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

void Session::handle_read(const boost::system::error_code& error, 
    size_t bytes_transferred, std::shared_ptr<Session> self){
   if(!error){
        std::cout << "Receive: " << _data << std::endl;
        Send(_data, bytes_transferred);
        memset(_data, 0, max_length);
        
   }
}

void Session:: handle_write(const boost::system::error_code& error, std::shared_ptr<Session> self){
     if(!error){
        std::lock_guard<std::mutex> lock(_send_lock);
        _send_que.pop();
        if(!_send_que.empty()){
            auto &msg = _send_que.front();
            boost::asio::async_write(_socket, boost::asio::buffer(msg->_data, max_length),
                std::bind(&Session::handle_write, this, std::placeholders::_1, shared_from_this()));
        }
    }
    else{
        std::cerr << "Error: " << error.message() << std::endl;
        _server->ClearSession(_uuid);
    }
}

void Session::Send(char* msg, int max_length){
    std::lock_guard<std::mutex> lock(_send_lock);
    bool pending = !_send_que.empty();
    _send_que.push(std::make_shared<MsgNode>(msg, max_length));
    if(!pending){
        boost::asio::async_write(_socket, boost::asio::buffer(msg, max_length),
            std::bind(&Session::handle_write, this, std::placeholders::_1, shared_from_this()));
    }
}
