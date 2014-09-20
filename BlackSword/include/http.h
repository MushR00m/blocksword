#ifndef http_h
#define http_h
#include "sysconfig.h"
typedef struct{ //�ַ����ṹ
	char *str;
	int lenght;
}str,*pstr;

typedef struct{ //�����ṹ
	str name[10]; //������
	str value[10];//����ֵ
	int l;
}args,*pargs;

struct http_request{
	char *sip;
	char *dip;
	ushort sport;
	ushort dport;
	int method;
	str request;//���������ݾ�
	str post;
	args httpargs;//�������
	str host;
	char *referer;
	char *agent;
	char *cookie;
	int lenght;
};

struct http_response{
	int code;//״̬����
	char desc[10];//����
	char *location;//��ת
	char *server;//������
};
char *http_getline(char *);
int http_getrequest(uchar *,struct http_request *);
int http_getresponse(uchar *,struct http_response *);
int http_getmethod(char *);
int http_geturllen(char *);
int http_getvalue(char *, int *);
int http_isargs(struct http_request *);
int http_setarg(char *, struct http_request *);
int http_setresponse(char *, struct http_response *);
int search_c(char *, char);
int strlen_h(char *);
int strsearch_fl(char *, char *, int);
int strtoks(char *, char, int, int *);
#endif
