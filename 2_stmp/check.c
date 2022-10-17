#include "check.h"

// 1. 检查输入邮箱是否合法
int email_is_legal(char *pattern)
{
	int status, i;
	char buf[] = "^[a-zA-Z0-9_]+@[a-zA-Z0-9]+.[a-zA-Z0-9]+$";
	const char *pregexstr = buf;
	const char *ptext = pattern;
	regex_t oregex;
	int nerrcode = 0;
	char szerrmsg[1024] = {0};
	size_t unerrmsglen = 0;
	if ((nerrcode = regcomp(&oregex, pregexstr, REG_EXTENDED | REG_NOSUB)) == 0)
	{
		if ((nerrcode = regexec(&oregex, ptext, 0, NULL, 0)) == 0)
		{
			//printfLine("%s matches %s\n", ptext, pregexstr);
			regfree(&oregex);
			return EMAIL_STATUS_LEGAL;
		}
		return EMAIL_STATUS_NOTLE;
	}
}

// 2. 是否退出程序
int exit_the_pro(char *buf_exit)
{
	if (strcmp(buf_exit, "exit") == 0)
	{
		printf("exit--程序退出!\n");
		exit(0);
	}
	return EMAIL_STATUS_NOTLE;
}

// 3. 展示邮箱
void show_emails(char *recv_email)
{
	printf("\n仅支持：\n");
	printf("%s\n", EMAIL_WWW_QQ);
	printf("%s\n", EMAIL_WWW_SINA);
	printf("%s\n", EMAIL_WWW_163);
	printf("%s\n", EMAIL_WWW_GMAIL);
	printf("%s\n", EMAIL_WWW_139);
	printf("%s\n", EMAIL_WWW_SOHU);
	printf("输入：%s error!\n\n", recv_email);
}

// 4. 获得encode编码串
void encode_string_base64(char *buff, char *str, char *encbuff)
{
	sprintf(buff, "%s",str); 
	base64_encode(buff, encbuff, strlen(buff));
	memset(buff, 0x00, sizeof(buff));
	sprintf(buff, "%s\r\n", encbuff);
}
// 5. 获取发送主题和内容
void get_text(char *buff_subject, char *buff_content)
{
	printf("主题：");
	scanf("%s", buff_subject);

	int x;
	while (1)
	{
		printf("发送内容：\n选项 [1] 直接输入\n选项 [2] 文件\n");
		scanf("%d", &x);
		if (x == 1 || x == 2)
			break;
	}

	if (1 == x)
	{
		printf("输入：");
		scanf("%s", buff_content);
	}
	if (2 == x)
	{
		printf("路径：");
		char path[50] = {0};
		scanf("%s", path);

		FILE *fp = fopen(path, "r");
		int i = 0;
		if (fp == NULL) //打开文件失败
		{
			printf("File cannot open! ");
			return;
		}
		while (!feof(fp) || i == 511) //读文件，直到文件末尾
		{
			buff_content[i++] = fgetc(fp); //将文件内容附给flag
		}
		buff_content[i] = '\0';
	}
}
