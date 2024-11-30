#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket){

}

void Session::Connect(const aiso::ip::tcp::endpointg)