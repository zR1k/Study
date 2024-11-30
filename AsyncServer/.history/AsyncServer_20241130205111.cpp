#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"
#include "Server.h"
int main(){
    try{
        boost::asio::io_context ioc;
        Server server(ioc, 10086);
        ioc.run();

    }catch(std::exe)
}