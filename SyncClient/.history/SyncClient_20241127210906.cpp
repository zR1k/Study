#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio::ip;

const int MAX_LENGTH = 1024;

int main(){
    try{
        //创建上下文服务
        boost::asio::io_context ioc;
        //构造一个endpoint对象
        tcp::endpoint remote_ep(address::from_string("127.0.0.1"), 10086);
        //构造一个socket对象
        tcp::socket sock(ioc);
        boost::system::error_code error = boost::asio::error::host_not_found;
        sock.connect(remote_ep, error);
        if(error){
            std::cout << "connect failed! Error code = " << error.value() << ". Message: " << error.message() 
                      << std::endl;
            return 0;
        }
        std::cout << "Enter message: ";
        char request[MAX_LENGTH];
        std::cin.getline(request, MAX_LENGTH);
        std::size_t request_length = strlen(request);
        boost::asio::write(sock, boost::asio::buffer(request, request_length));

        char reply[MAX_LENGTH];
        std::size_t reply_lentg = boost::asio::read(sock, boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_lenth);
        std::cout << "\n";
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

    }
}