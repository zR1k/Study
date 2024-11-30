#include <iostream>
#include <boost/asio.hpp>
#include <set>
using namespace boost::asio::ip;
const int max_length = 1024;
typedef std::shared_ptr<tcp::socket> socket_ptr;
std::set<std::shared_ptr<std::thread> >thread_set;

int main(){

}