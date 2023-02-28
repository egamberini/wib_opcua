#ifndef __WIB_HH
#define __WIB_HH

#include "wib.pb.h"

#include <zmq.hpp>
#include <string>
#include <iostream>

class WIB_ZMQ {

public:

    WIB_ZMQ();
    ~WIB_ZMQ();

    void connect(const std::string &zmq_endpoint);

    template <class R, class C>
    bool send_command(const C &msg, R &repl, int timeout_ms = -1) {
    	// EG: with a REQ/REP pattern, after a socket.send, the next allowed operation is a socket.recv.
    	// In case the zmq_poll returns false, the method is returned, therefore a recv operation is not performed.
    	// This will cause socket.send to raise an exception at the next method call.

        wib::Command command;
        command.mutable_cmd()->PackFrom(msg);
        
        std::string cmd_str;
        command.SerializeToString(&cmd_str);
        
        zmq::message_t request(cmd_str.size());
        memcpy((void*)request.data(), cmd_str.c_str(), cmd_str.size());
        try {
            socket.send(request,zmq::send_flags::none);
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception caught in socket.send for endpoint " << m_zmq_endpoint << ": [" << e.what() << "]" << std::endl;
        }

        zmq_poll(&poller, 1, timeout_ms);
        
        zmq::message_t reply;
        try {
            auto rv = socket.recv(reply,zmq::recv_flags::none);
            if (rv.value() <= 0) {
                return false;
            }
        }
        catch (const std::exception &e) {
            std::cout << "Exception caught in socket.recv for endpoint " << m_zmq_endpoint << ": [" << e.what() << "]" << std::endl;
            return false;
        }
       	std::string reply_str(static_cast<char*>(reply.data()), reply.size());
       	repl.ParseFromString(reply_str);

       	return true;
    }
    
protected:
    
    zmq::context_t context;
    zmq::socket_t socket;
    zmq::pollitem_t poller;
    
private:
    std::string m_zmq_endpoint;
};

#endif

