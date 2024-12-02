#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <map>
#include "Session.h"

using boost::asio::ip::tcp;

class Server{
public:
    Server(boost::asio::io_context& ioc, short port);
    void ClearSession(std)
private:
    void start_accept();
    void handle_accept(std::shared_ptr<Session> new_session, const boost::system::error_code& error);
    boost::asio::io_context& _ioc;
    tcp::acceptor _acceptor;
    std::map<std::string, std::shared_ptr<Session>> _sessions;
};

