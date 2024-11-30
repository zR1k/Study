#include <iostream>
#include <boost/asio.hpp>
#include <set>
#include <memory>
#include <exception>
using namespace boost::asio::ip;
const int max_length = 1024;
typedef std::shared_ptr<tcp::socket> socket_ptr;
std::set<std::shared_ptr<std::thread> >thread_set;

void sessionn(socket_ptr sock){
    try{
        for(;;){
            char data[max_length];
            memset(data, 0, max_length);
            boost::system::error_code error;
            size_t length = boost::asio::read(*sock, boost::asio::buffer(data, max_length), error);
        }
    }catch(std::exception& e){
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
}

int main(){

}