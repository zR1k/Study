#include "Session.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.saync_read_some(boost::asio::buffer(_data, max_length),
            std::bin(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2));
}