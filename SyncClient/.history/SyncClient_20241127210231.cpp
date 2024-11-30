#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio::ip;

const int MAX_LENGTH = 1024;

int main(){
    try{
        //创建上下文服务
        boost::asio::io_context ioc;
        //创建一个tcp的socket
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

    }
}