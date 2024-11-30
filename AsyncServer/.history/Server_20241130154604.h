#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"

using boost::asio::ip::tcp;

class Server{
public:
    Server(boost::asio::io_context& ioc, short port) : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)){

private:
    void start_accept();
    void handle_accept(Session* new_session, const boost::system::error_code& error);
    boost::asio::io_context& _ioc;
    tcp::acceptor _acceptor;
};