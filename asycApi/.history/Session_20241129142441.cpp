#include "Session.h"

Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket)
    : _socket(socket){

}

void Session::Connect(const asio::ip::tcp::endpoint& e){
    _socket->connect(e);
}

Session:: WriteCallback(const boost::system::error_code& ec, std::size_t bytes_transferred, 
        std::shared_ptr<MsgNode>){
                        
}