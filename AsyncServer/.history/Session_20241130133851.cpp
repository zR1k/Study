#include "Session.h"
#include <iostream>

void Session::Start(){
    memset(_data, 0, max_length);
    _socket.saync_read_some()
}