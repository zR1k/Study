#pragma once
#include <memory>
#include "boost/asio.hpp"
#include <iostream>

using namespace boost;

class Session{
public:
    Session(std::shared_ptr<asio::ip::tcp::socket> socket);
    void 
};