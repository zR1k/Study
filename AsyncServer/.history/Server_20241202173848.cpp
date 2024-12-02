#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"
#include "Server.h"
  
using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ioc, short port) 
    : _ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)){
        std::cout << "Server is running on port " << port << std::endl;
        start_accept();
}

void Server::start_accept(){
    std::shared_ptr<Session> new_session = std::make_shared<Session>(_ioc, this); 
    _acceptor.async_accept(new_session->Socket(),
        std::bind(&Server::handle_accept, this, new_session, std::placeholders::_1));
}

void Server::handle_accept(std::shared_ptr<Session> new_session, const boost::system::error_code& error){
    if(!error){
        new_session->Start();
        _sessions[new_session->GetUuID()] = new_session;
    }
    else{
        
    }
    start_accept();
    
}