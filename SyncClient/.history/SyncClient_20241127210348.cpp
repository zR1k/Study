#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio::ip;

const int MAX_LENGTH = 1024;

int main(){
    try{
        //创建上下文服务
        boost::asio::io_context ioc;
        //构造一个endpoint对象
        tcp::endpoint ep(address::from_string("127.0.0.1"), 10086);
        //构造一个socket对象
        tcp::socket sock(ioc);
        boost::system::error_code ec = 
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

    }
}