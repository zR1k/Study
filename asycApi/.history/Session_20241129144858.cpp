#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket){

}

void Session::Connect(const asio::ip::tcp::endpoint& e){
    _socket->connect(e);
}

void Session::WriteCallback(const boost::system::error_code& ec, std::size_t bytes_transferred, 
    std::shared_ptr<MsgNode>){
        
}

void Session::WriteToSocket(const std::string buf){
    _send_node = make_shared<M
    this->_socket->async_write_some(asio::buffer(buf), 
        std::bind(&Session::WriteCallback, this, std::placeholders::_1, std::placeholders::_2, _send_node));
}