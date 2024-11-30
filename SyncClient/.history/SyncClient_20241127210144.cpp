#include <boost/asio.hpp>

using namespace boost::asio::ip;

const int MAX_LENGTH = 1024;

int main(){
    try{

    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

    }
}