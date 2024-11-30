#pragma once
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server{
public:
    Server(boost::asio::io_context& ioc, short port) : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)){
        StartAccept();
    }
private:
    void start
};