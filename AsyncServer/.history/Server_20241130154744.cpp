#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"
#include "Server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ioc, short port) 
    : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)){

}