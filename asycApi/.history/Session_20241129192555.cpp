#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket), _send_pending(false){

}

void Session::Connect(const asio::ip::tcp::endpoint& e){
    _socket->connect(e);
}

void Session::WriteCallback(const boost::system::error_code& ec, std::size_t bytes_transferred, 
    std::shared_ptr<MsgNode> msg_node){
    if(bytes_transferred + msg_node -> _cur_len < msg_node -> _total_len){
        _send_node -> _cur_len += bytes_transferred;
        this->_socket->async_write_some(asio::buffer(_send_node->_msg + _send_node->_cur_len, 
            _send_node->_total_len - _send_node->_cur_len),
            std::bind(&Session::WriteCallback, this, std::placeholders::_1, std::placeholders::_2));

    }
}

void Session::WriteToSocket(const std::string buf){
    _send_node = std::make_shared<MsgNode>(buf.c_str(), buf.length());
    this->_socket->async_write_some(asio::buffer(_send_node->_msg, _send_node->_total_len),
        std::bind(&Session::WriteCallback, this, std::placeholders::_1, std::placeholders::_2,
        _send_node));
}

void Session::WriteToSocket(const std::string& buf){
    _send_queue.emplace(new MsgNode(buf.c_str(), buf.length()));
    if(_send_pending){
        return;
    }
    this->_socket->async_write_some(asio::buffer(buf),
        std::bind(&Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2));
    _send
}
void Session::WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred){
    
}