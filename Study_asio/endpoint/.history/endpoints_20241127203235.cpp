#include "endpoint.h"
#include <boost/asio.hpp>
#include <iostream>
int client_end_point() {
    std::string raw_ip_address = "127.4.8.1";
    unsigned short port_num = 3333;
    boost::system::error_code ec;
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(raw_ip_address, ec);
    if (ec.value() != 0) {
        std::cout << "Failed to parse the IP address. Error code = " << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }
    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);
    return 0;
}

int server_end_point(){
    unsigned short port_num = 3333;
    boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();
    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);
    return 0;
}

int create_tcp_socket(){
    boost::asio::io_context ioc;
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();
    boost::asio::ip::tcp::socket sock(ioc);
    boost::system::error_code ec;
    sock.open(protocol, ec);
    if(ec.value() != 0){
        std::cout << "Failed to open the socket. Error code = " << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }
    return 0;
}

int create_acceptor_socket(){
    // boost::asio::io_context ios;
    // boost::asio::ip::tcp::acceptor acceptor(ios);
    // boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();
    // boost::system::error_code ec;
    // acceptor.open(protocol, ec);
    // if(ec.value() != 0){
    //     std::cout << "Failed to open the acceptor socket. Error code = " << ec.value() << ". Message: " << ec.message();
    //     return ec.value();
    boost::asio::io_context ios;
    boost::asio::ip::tcp::acceptor a(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3333));
    return 0;
}

int bind_acceptor_socket(){
    unsigned short port_num = 3333;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
    boost::asio::io_context ios;
    boost::asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
    boost::system::error_code ec;
    acceptor.bind(ep, ec);
    if(ec.value() != 0){
        std::cout << "Failed to bind the acceptor socket. Error code = " << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }
}

int connect_to_end(){
    std::string raw_ip_address = "192.168.1.124";
    unsigned short port_num = 3333;
    try{
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
        boost::asio::io_context ios;
        boost::asio::ip::tcp::socket sock(ios, ep.protocol());
        sock.connect(ep);

    } catch (boost::system::system_error &e) {
        std::cout << "Error occured! Error Code = " << e.code() << ". Message: " << e.what();
        return e.code().value();
    }
}

int dns_connect_to_end(){
    std::string host = "llfc.club";
    std::string port_num = "3333";
    boost::asio::io_context ios;
    boost::asio::ip::tcp::resolver::query resolver_query(host, port_num, boost::asio::ip::tcp::resolver::query::numeric_service);
    boost::asio::ip::tcp::resolver resolver(ios);
    try{
        boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);
        boost::asio::ip::tcp::socket sock(ios);
        boost::asio::connect(sock, it);

    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error Code = " << e.code() << ". Message: " << e.what();
        return e.code().value();
    }
}

int accept_new_connection(){
    const int BACKLOG_SIZE = 30;
    unsigned short port_num = 3333;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
    boost::asio::io_context ios;
    try{
        boost::asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
        acceptor.bind(ep);
        acceptor.listen(BACKLOG_SIZE);
        boost::asio::ip::tcp::socket sock(ios);
        acceptor.accept(sock);
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error Code = " << e.code() << ". Message: " << e.what();
        return e.code().value();
    }
}

void ues_const_buffer(){
    std::string buf = "hello world";
    boost::asio::const_buffer asio_buf(buf.c_str(), buf.length());
    std::vector<boost::asio::const_buffer> buffers_sqquence;
    buffers_sqquence.push_back(asio_buf);
}

void use_buffer_str(){
    boost::asio::const_buffers_1 output_buf = boost::asio::buffer("hello world");
}

void use_buffer_array(){
    const size_t BUF_SIZE_BYTES = 20;
    std::unique_ptr<char[]> buf(new char[BUF_SIZE_BYTES]);
    auto intput_buf = boost::asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE_BYTES);
}

void write_to_socket(boost::asio::ip::tcp::socket &sock){
    std::string buf = "hello world";
    std::size_t total_bytes_writen = 0;
    // 循环发送
    // writen_some()返回实际发送的字节数
    while(total_bytes_writen != buf.length()){
        total_bytes_writen += sock.write_some(boost::asio::buffer(buf.c_str() + total_bytes_writen, buf.length() - total_bytes_writen));
    }

}

int send_data_by_write_some(){
    std::string rwp_ip_address = "192.168.3.11";
    unsigned short port_num = 3333;
    try{
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(rwp_ip_address), port_num);
        boost::asio::io_context ios;
        boost::asio::ip::tcp::socket sock(ios, ep.protocol());
        sock.connect(ep);
        write_to_socket(sock);
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error Code = " << e.code() << ". Message: " << e.what();
        return e.code().value();
    }
    return 0;
}

int send_data_by_write_some(){
    std::string rwp_ip_address = "192.168.3.11";
    unsigned short port_num = 3333;
    try{
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(rwp_ip_address), port_num);
        boost::asio::io_context ios;
        boost::asio::ip::tcp::socket sock(ios, ep.protocol());
        sock.connect(ep);
        
    }catch(boost::system::system_error &e){
        std::cout << "Error occured! Error Code = " << e.code() << ". Message: " << e.what();
        return e.code().value();
    }
    return 0;
}