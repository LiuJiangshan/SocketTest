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

void log(std::string log)
{
    std::cout<<log<<std::endl;
}
std::string getHttpHead(const char* domain)
{
    std::string head = "GET / HTTP/1.1\r\n";
    head.append("Host: ");
    head.append(domain);
    head.append("\r\n");
    head.append("baidu is sb");
    head.append("\r\n");
    head = "GET / HTTP/1.1\r\nHost: www.baidu.com:80\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: zh-CN,zh;q=0.9";
    return head;
}
#endif /* main_h */
