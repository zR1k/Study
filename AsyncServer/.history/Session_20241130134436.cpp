#include "Session.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
            std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2));
}

void Session::handle_read(const boost::system::error_code& error, 
    size_t bytes_transferred){
    if(!error){
        cout << "server reci"
    }
    else{
        std::cerr << "Error: " << error.message() << std::endl;
        delete this;
    }
}