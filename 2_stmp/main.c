#include"main.h"

void main(int argc, char* argv[])
{

    while(1)
    {        
        printf("发件人：");
        get_recv_email(email_send); //1.1获取发送端邮箱， 确定邮箱服务器               
        ret = get_email_server(email_send, server_send, &port);    //1.2根据邮箱类型确定邮箱stmp服务器地址和端口号
        
        if(ret)
        {            
            break;
        }
        show_emails(email_send);  //list the emails        
    }    
    
    
    ret = get_sock_create(&csock, server_send, &port);//1.3创建套接字
    if(ret == FAILED)
    {
        exit(0);
    }

    //等待服务器回应
    get_server_back(&csock, buff_recv);    

    sprintf(buff_send, "HELO 126.com\r\n");
    //向服务器发送数据并等待服务器回应
    send_to_server_and_recv(csock, buff_send);

    //用户认证
    send_info_authlogin(csock, buff);

    //发送自己的用户名
    send_myself_email_name(csock, buff, email_send, server_send, &port);

    //发送自己的email密码
    send_myself_email_password(csock, buff);

    //发送发件人
    send_email_from_user(csock, email_send);

    //发送收件人
    send_email_to_user(csock, buff, email_recv, server_recv, &port_recv);

    //准备发送数据
    send_ready_to(csock);

    //发送
    send_text_to_some(csock, buff, email_send, email_recv);

    //关闭套接字
    close(csock);

    return ;
}