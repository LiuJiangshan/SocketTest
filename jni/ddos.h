//
//  main.h
//  CAddTest
//
//  Created by yfn on 2018/5/9.
//  Copyright © 2018年 infeini. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <unistd.h>
#include <time.h>
#include <iostream>

#ifndef main_h
#define main_h

void log(std::string log) {
//    std::cout << log << std::endl;
}

std::string getHttpRequestData(const char *domain, const char *path) {
    std::string head = "GET ";
    head.append(path)
            .append(" HTTP/1.1\r\nHost: ")
            .append(domain)
            .append("\r\n\r\n");
    return head;
}

#endif /* main_h */
