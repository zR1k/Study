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
    _send_node = std::make_shared<MsgNode>(buf.c_str(), buf.length());
this->_socket->async_write_some(asio::buffer(_send_node-_msg, _send_node->_total_len),);
}