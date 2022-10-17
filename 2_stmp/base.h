#ifndef _BASE_H
#define _BASE_H

#include<stdio.h>
#include<string.h>

int base64_encode( const unsigned char * originChar, char * base64, int originlength );//base64编码
int base64_decode( const char * base64, unsigned char * originChar );//base64解码

#endif