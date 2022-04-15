//
// TimeClient.cpp
//
// This sample demonstrates the DateTime class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include <iostream>
#include <sstream>

using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::DateTimeParser;

using Poco::Net::StreamSocket;
using Poco::Net::SocketStream;
using Poco::Net::SocketAddress;
using Poco::StreamCopier;
using Poco::Exception;

#include <iostream>
#include <string>

class ClientHandler {

private:
    std::string host;
    int port;

    // IP endpoint/socket address (consists of host addr and port #)
    SocketAddress socketAddr;

    // Interface to a TCP stream socket
    StreamSocket socket;

    // Stream for reading from / writing to a socket (accepts a socket)
    SocketStream stream;

public:
    ClientHandler(std::string h, int p) : host(h), port(p), socketAddr(h, p), socket(), stream(socket)
    {
        std::cout << "Host: " << host << "\tPort: " << port << std::endl;
    }


    bool connected()
    {
        std::cout << "Creating a connection with ["
                  << socketAddr.host().toString()
                  << "] through port [" << socketAddr.port() << "] ...";
        try {
            socket.connect(socketAddr);
            std::cout << "Success!" << std::endl;
        }
        catch(Poco::Exception err) {
            std::cout << std::endl;
            std::cout << "Socket connection error: [" << err.displayText() << "]" << std::endl;
            return false;
        }
        return true;
    }

    bool sendMessage()
    {
        std::cout << std::endl;

        try {
            std::string message;

            std::cout << "Enter a message to send to the server: ";
            std::cin >> message;

            if(message.compare("exit") != 0) {
                std::cout << "Sending the message \"" << message << "\" to the server!" << std::endl;
                socket.sendBytes(message.data(), message.size());
                return true;
            }
            else return false;
        }
        catch(Poco::Exception err) {
            std::cout << "Data send error: [" << err.displayText() << "]" << std::endl;
            return false;
        }
    }

    std::string reciveMessage()
    {
        std::string message;
        std::stringstream s;

        try
        {
            stream >> message;
            socket.shutdownReceive();
        }
        catch(Poco::Exception err)
        {
            s << "Data revice error: [" << err.displayText() << "]" << std::endl;
            message = s.str();
        }
        return message;
    }
};

int main(int argc, char** argv)
{
    int port = 9901;
    std::string hostname = "127.0.0.1";

    // Handle the server-client connection and recive some data
    ClientHandler handler(hostname, port);
    if (handler.connected())
       {
        std::cout << "Time from time_server: " << handler.reciveMessage() << std::endl;
       }
    return 0;
}
