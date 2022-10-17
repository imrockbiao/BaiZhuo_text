#include"deal.h"


//a.debug打印
void printfDebug(char* info)
{
    #ifdef DEBUG
    printfLine("%s",info);
    #endif
}


//1.1. 获取email账号
int get_recv_email(char* email)
{
    int ret = 1;
     while(1)
     {
        scanf("%s", email);
        ret = email_is_legal(email);
        exit_the_pro(email);
        if(ret == EMAIL_STATUS_NOTLE)
        {
            printf("邮箱格式错误!(输入 exit 结束程序)\n重新输入邮箱:");
            continue;
        }        
        else
            break;
     }
    return SUCCESS;
}

//1.2 根据邮箱类型确定邮箱stmp服务器地址和端口号
int get_email_server(char* email, char* email_server, int* port)
{
    int ret = FAILED;
    if(strlen(email)<=0)
    {
        return ret;
    }
    char buf_tmp[LEN_MAIL] = {0};
    for(int i = 0; i<LEN_MAIL; i++)
    {
        if(email[i] == '@')
        {
            i++;
            for(int j = 0; email[i+j]!='\0';j++)
            {
                buf_tmp[j] = email[i+j];
            }
            
            break;
        }
    }

    if(strcmp(buf_tmp, "qq.com") == 0)
    {
        strcpy(email_server,"smtp.qq.com");
        (*port) = PORT_QQ;
        printfDebug(EMAIL_WWW_QQ);ret = SUCCESS;
        printf("\n");
    }
    if(strcmp(buf_tmp, "sina.com") == 0 )
    {
        strcpy(email_server, "smtp.sina.com.cn");
        (*port) = PORT_SINA;
        printfDebug(EMAIL_WWW_SINA);ret = SUCCESS;
        printf("\n");
    }
    if(strcmp(buf_tmp, "163.com") == 0 )
    {
        strcpy(email_server, "smtp.163.com");       
        (*port) = PORT_163;
        printfDebug(EMAIL_WWW_163);ret = SUCCESS;
        printf("\n");
    }
    if(strcmp(buf_tmp, "gmail.com") == 0 )
    {
        strcpy(email_server, "smtp.163.com"); 
        (*port) = PORT_GMAIL;ret = SUCCESS;
        printfDebug(EMAIL_WWW_GMAIL);
        printf("\n");
    }
    if(strcmp(buf_tmp, "139.com") == 0 )
    {
        strcpy(email_server, "smtp.139.com"); 
        (*port) = PORT_139;ret = SUCCESS;
        printfDebug(EMAIL_WWW_139);
        printf("\n");
    }
    if(strcmp(buf_tmp, "sohu.com") == 0 )
    {
        strcpy(email_server, "smtp.sohu.com"); 
        (*port) = PORT_SOHU;ret = SUCCESS;
        printfDebug(EMAIL_WWW_SOHU);
        printf("\n");
    }
    return ret;

}

//1.3 创建套接字，连接邮箱服务器
int get_sock_create(int* csock, char* email_server, int* port)
{
    //创建套接字， 用于和邮箱服务器进行通信
    (*csock) = socket(AF_INET, SOCK_STREAM, 0);

    if ( (*csock)  < 0) {
		printf("cfd create failed\n");
		exit(0);
	}

    //准备
    struct sockaddr_in server_addr;
	struct hostent *server_addr_host;

    //根据邮箱域名获取邮箱服务器的IP地址
    server_addr_host = gethostbyname(email_server);
    if(server_addr_host ==NULL)
    {
        printf("server_addr_host failed!\n");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);
    server_addr.sin_addr.s_addr = (*(struct in_addr*)server_addr_host->h_addr_list[0]).s_addr;
	int ret = connect((*csock), (struct sockaddr *)&server_addr, sizeof(server_addr));
	
    if (ret < 0) {
		printfLine("connect server failed\n");
		exit(0);
	}
    printfDebug("创建套接字完毕\n");
    return SUCCESS;
}

//等待服务器回应
int get_server_back(int *csock, char* buff_recv)
{
    while (1) {
		int ret = recv(*csock, buff_recv, MAX_BUFF_SIZE, 0);
		if (ret < 0) {
			printf("recv error\n");
			continue;
		}

		printfDebug(buff_recv);
		break;
	}
    return SUCCESS;
}

//3. 向服务器发送数据并等待服务器回应
int send_to_server_and_recv(int csock, char* buff_send)
{

    printfDebug("开始向服务器发送数据");
    int ret = 0;
	char recvbuff[MAX_BUFF_SIZE] = { 0 };
	send(csock, buff_send, strlen(buff_send), 0);
	ret = recv(csock, recvbuff, MAX_BUFF_SIZE, 0);
    #ifdef DEBUG
	    printfLine("recvdata:len = %d\nrecv:[%s] \n", ret, recvbuff);
    #endif
    if (ret<0)
    {
        printf("收数据发生错误");
        exit(0);
    }
    
    //printfDebug("发送完成\n");  
    
    return ret;
    
}

//4.用户身份认证AUTH LOGIN 身份认证
int send_info_authlogin(int csock, char* buff)
{
    printfDebug("身份验证\n");

	sprintf(buff, "%s", "AUTH LOGIN\r\n");
	send_to_server_and_recv(csock, buff);

    printfDebug("完成验证\n");
	return 0;
}



//5. 发送自己的用户名
int send_myself_email_name(int csock, char* buff, char* email_send, char* server_send, int *port_send)
{
    printfDebug("向服务器发送自己的email邮箱\n");
	char encbuff[120] = { 0 };    
    encode_string_base64(buff, email_send,encbuff);//格式化buff，转化为base64
    send_to_server_and_recv(csock, buff);

    printfDebug("确定完毕\n");
	return 0;
}

//6. 发送自己的邮箱密码或者授权码
int send_myself_email_password(int csock, char* buff)
{
	char encbuff[120] = { 0 };
    char password[LEN_TYPE] = {0};
    
    printf("密码：");
    scanf("%s", password);
    encode_string_base64(buff, password,encbuff);//格式化buff，转化为base64

	// sprintf(buff, password);          //需要改成自己的密码，有的邮箱是需要填授权码不是登录用的密码
	// base64_encode(buff, encbuff, strlen(buff));
	// memset(buff, 0x00, sizeof(buff));
	// sprintf(buff, "%s\r\n", encbuff);
	int ret = send_to_server_and_recv(csock, buff);
	if (ret < 0) {
        //printfDebug("密码错误-----------\n");
		return -1;
	}

	return 0;
}

//7. 发送发件人
int send_email_from_user(int csock, char* email_send)
{
    char buff[320] = { 0 };
	int ret;
    printfDebug("发送发件人\n");
	sprintf(buff, "MAIL FROM: <%s>\r\n", email_send);
	ret = send_to_server_and_recv(csock, buff);
	if (ret < 0) {
		return -1;
	}
    printfDebug("发件人已发送\n");
	return 0;
}

//8. 发送收件人
int send_email_to_user(int csock, char* buff, char* email_recv, char* server_recv, int *port_recv)
{

    while(1)
    {      
        //通过用户输入，获取到发送端的邮箱，和端口号  
        printf("收件人：");
        //scanf("%s", email_recv);
        get_recv_email(email_recv); //1.1获取用户输入的邮箱， 确定邮箱服务器               
        int ret = get_email_server(email_recv, server_recv, port_recv);    //1.2根据邮箱类型确定邮箱stmp服务器地址和端口号
        
        if(ret)
        {            
            break;
        }

        show_emails(email_recv);  //list the emails        
    } 

	sprintf(buff, "RCPT TO: <%s>\r\n",email_recv);
	send_to_server_and_recv(csock, buff);
    printfDebug("收件人已发送\n");
	return 0;
}

//9. 准备发送
int send_ready_to(int csock)
{
    char buff[320] = { 0 };
	int ret;

	sprintf(buff, "DATA\r\n");
	ret = send_to_server_and_recv(csock, buff);
	if (ret < 0) {
		return -1;
	}

    printfDebug("准备好发送数据\n");
	return 0;
}

//10. 发送数据
int send_text_to_some(int csock, char* buff, char* email_send, char* email_recv)
{
    char buff_subject[MAX_BUFF_SIZE] = {0};
    char buff_content[MAX_BUFF_SIZE] = {0};

    get_text(buff_subject,buff_content);    

	sprintf(buff, "From: \"pc\"<%s>\r\n"        //发件人
		"To: \"con\"<%s>\r\n"             //收件人
		"Subject:%s\r\n\r\n"                 //主题
		"%s"                                   //正文, 以 \r\n.\r\n 结束
		"\r\n.\r\n",
        email_send,
        email_recv,
        buff_subject,
        buff_content
        );
	send_to_server_and_recv(csock, buff);
    printfDebug("发送完毕\n");
	return 0;
}

