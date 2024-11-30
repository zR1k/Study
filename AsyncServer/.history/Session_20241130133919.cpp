#include "Session.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.saync_read_some(boost::asio::buffer(_data, max_length),
        boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}