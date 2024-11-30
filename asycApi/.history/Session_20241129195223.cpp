#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket), _send_pending(false), _recv_pending(false){

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
    _send_pending = true;
}
void Session::WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred){
    if(ec.value() != 0){
        std::cout << "Error: " << ec.message() << std::endl;
        return;
    }
    
    auto & send_data = _send_queue.front();
    send_data->_cur_len += bytes_transferred;
    if(send_data->_cur_len < send_data->_total_len){
        this->_socket->async_write_some(asio::buffer(send_data->_msg + send_data->_cur_len,
            send_data->_total_len - send_data->_cur_len),
            std::bind(&Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2));
        return ;
    }
    _send_queue.pop();
    if(!_send_queue.empty()){
        auto& send_data = _send_queue.front();
        this->_socket->async_write_some(asio::buffer(send_data->_msg, send_data->_total_len),
            std::bind(&Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2));
    }
    else{
        _send_pending = false;
    }
}

void Session::WriteALLToSocket(const std::string& buf){
    _send_queue.emplace(new MsgNode(buf.c_str(), buf.length()));
    if(_send_pending){
        return ;
    }

    this->_socket->async_send(asio::buffer(buf),
        std::bind(&Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2));
    _send_pending = true;   
    
}
void Session::WriteALLCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred){ 
    if(ec.value() != 0){
        std::cout << "Error: " << ec.message() << std::endl;
        return;
    }

    _send_queue.pop();
    if(_send_queue.empty()){
        _send_pending = false;
        return;
    }
    auto & send_data = _send_queue.front();
    this->_socket->async_send(asio::buffer(send_data->_msg, send_data->_total_len),
        std::bind(&Session::WriteALLCallBack, this, std::placeholders::_1, std::placeholders::_2));
}

void Session::ReadFromSocket(){
    if(_recv_pending){
        return;
    }
    _recv_node = std::make_shared<MsgNode>(RECVSIZE);
    _socket->async_read_some,(asio::)
}

void Session::ReadCallBack(const boost::system::error_code& ec){
    if(ec.value() != 0){
        std::cout << "Error: " << ec.message() << std::endl;
        return;
    }
    std::cout << "Recv: " << _recv_buf << std::endl;
    ReadFromSocket();
}