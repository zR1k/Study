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
    shared_ptr<>  = make_shared<Session>(_ioc, this);
    Session* new_session = new Session(_ioc);
    _acceptor.async_accept(new_session->Socket(),
        std::bind(&Server::handle_accept, this, new_session, std::placeholders::_1));
}

void Server::handle_accept(Session* new_session, const boost::system::error_code& error){
    if(!error){
        new_session->Start();
    }
    else{
        delete new_session;
    }
    start_accept();
    
}