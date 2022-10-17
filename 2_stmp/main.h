#ifndef _MAIN_H
#define _MAIN_H

#include<stdio.h>
#include <unistd.h>

#include"deal.h"

int csock;         //连接服务器套接字
int port;          //服务器端口
int port_recv;
int ret=0;         //返回值 

char email_recv[LEN_MAIL] = {0};        //目的邮箱
char email_send[LEN_MAIL] = {0};        //自己邮箱
char server_recv[LEN_TYPE] = {0};       //目的邮箱的SMTP服务器地址
char server_send[LEN_TYPE] = {0};       //自己邮箱的SMTP服务器地址
char buff_send[MAX_BUFF_SIZE] = {0};    //发送字符串缓冲区
char buff_recv[MAX_BUFF_SIZE] = {0};    //接收字符串缓冲区
char buff[LEN_CACHE] = { 0 };           //缓存

#endif