#ifndef pdata_h
#define pdata_h
#include <time.h>
#include "pcap.h"
#include "sysconfig.h"
#include "bspcap.h"

struct tcp_stream{
	int ts;
};
union tyhead{
	struct head_icmp *hi; //icmpЭ��ؼ����ݽṹָ��
	struct head_tcp *ht;//ͬ�ϣ�tcpЭ��
	struct head_udp *hu;//ͬ�ϣ�udpЭ��
	struct head_http_request *hrq;//ͬ�ϣ�http����
	struct head_http_respon *hrs;//ͬ�ϣ�http��Ӧ
};
struct pdata{
	int type;//���ͣ�packet����stream
	union tyhead td;
};
struct packet{
	time_t time;//�������ݰ�ʱ��
	int protocol;//���ϲ�Э��
	union tyhead th;//
	char *data;
	int len;
};
struct stream{
	struct head_http_request *hrq;
	struct head_http_respon *hrs;
	struct tcp_stream *ts;//tcp���ṹ
};
union tydata{
	struct packet *pt;
	struct stream *sm;
};
struct head_http_requst{
	char *request;//http�����У�����������url��httpЭ��汾
	char *method;
	char *url;
	char *host;
	char *cookie;
	struct http_args **hargs;//http���������ά����ָ��
};

int start_packet(struct info *,u_char *);

int start_stream(struct tcp_stream *,time_t);

#endif