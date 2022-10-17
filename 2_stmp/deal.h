#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "base.h"
#include "check.h"


// a.debug打印
void printfDebug(char *info);

// 1.1. 获取email账号
int get_recv_email(char *email);

// 1.2 根据邮箱类型确定邮箱stmp服务器地址和端口号
int get_email_server(char *recv_email, char *email_server, int *port);

// 1.3 创建套接字，连接邮箱服务器
int get_sock_create(int *csock, char *email_server, int *port);

//等待服务器回应
int get_server_back(int *csock, char *buff_recv);

// 3. 向服务器发送数据并等待服务器回应
int send_to_server_and_recv(int csock, char *buff_send);

// 4.用户身份认证AUTH LOGIN 身份认证
int send_info_authlogin(int sock, char *buff);

// 5. 发送自己的用户名
int send_myself_email_name(int csock, char *buff, char *email_my, char *server_my, int *port_send);

// 6. 发送自己的邮箱密码或者授权码
int send_myself_email_password(int csock, char *buff);

// 7. 发送发件人
int send_email_from_user(int csock, char *email_send);

// 8. 发送收件人
int send_email_to_user(int csock, char *buff, char *email_recv, char *server_recv, int *port_recv);

// 9. 准备发送
int send_ready_to(int csock);

//10. 发送数据
int send_text_to_some(int csock, char* buff, char* email_send, char* email_recv);
