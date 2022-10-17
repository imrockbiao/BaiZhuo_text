#ifndef _CHECK_H
#define _CHECK_H

#include<stdio.h>
#include<sys/types.h>
#include<regex.h>
#include<string.h>
#include<stdlib.h>

#include"base.h"

#define printfLine                          \
    printf("%s %-3d:", __FILE__, __LINE__); \
    printf

#define MAX_BUFF_SIZE 512
#define LEN_TYPE 20
#define LEN_MAIL 20
#define LEN_CACHE 50

#define SUCCESS 1
#define FAILED 0

#define PORT_QQ 25
#define PORT_SINA 25
#define PORT_163 25
#define PORT_GMAIL 587
#define PORT_139 25
#define PORT_SOHU 25

#define EMAIL_WWW_QQ       "www.qq.com"
#define EMAIL_WWW_SINA     "www.sina.com.cn"
#define EMAIL_WWW_163      "www.163.com"
#define EMAIL_WWW_GMAIL    "www.gmail.com"
#define EMAIL_WWW_139      "www.139.com"
#define EMAIL_WWW_SOHU     "www.sohu.com"

#define EMAIL_STATUS_LEGAL 0    //邮箱格式正确
#define EMAIL_STATUS_NOTLE 1    //邮箱格式错误

//1. 检查输入邮箱是否合法
int email_is_legal(char *email_name);

//2. 是否退出程序
int exit_the_pro(char *buf_exit);

//3. 展示邮箱
void show_emails(char * recv_email);

//4. 获得encode编码串
void encode_string_base64(char *buff, char* str, char* encbuff);

//5. 获取发送主题和内容
void get_text(char* buff_subject,char* buff_content);

#endif