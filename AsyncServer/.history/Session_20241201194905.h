#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using boost::asio::ip::tcp;

class Server;

class Session:public std::enable_shared_from_this<Session>{
public:
    Session(boost::asio::io_context& ioc, Server* server) : _socket(ioc), _server(server){
        boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
        _uuid = boost::uuids::to_string(a_uuid);
    }
    tcp::socket& Socket(){
        return _socket;
    }

    void Start();
    std::string& GetUuID(){
        return _uuid;
    }
private:
    void handle_read(const boost::system::error_code& error, 
        size_t bytes_transferred, std::shared_ptr<Session> self);
    void handle_write(const boost::system::error_code& error, std::shared_ptr<Session> self);
    tcp::socket _socket;
    enum{max_length = 1024};
    char _data[max_length];
    Server* _server;
    std::string _uuid;
};