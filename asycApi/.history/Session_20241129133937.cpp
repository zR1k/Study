#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket){
}