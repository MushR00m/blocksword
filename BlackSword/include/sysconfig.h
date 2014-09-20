#ifndef sysconfig_h
#define sysconfig_h
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
#define LOCAL_IP "BSLocal_ip"
#define LOCAL_MASK "BSLocal_mask"
#define LOCAL_PATH "BSLocal_Path"
#define INSPERCT_HTTP "BSInsperct_http"
#define INSPERCT_TCP "BSInsperct_tcp"
#define INSPERCT_UDP "BSInsperct_udp"
#define INSPERCT_ICMP "BSInsperct_icmp"
#define AUDIT_ALERT "BSAudit_alert"
#define AUDIT_LOG "BSAudit_log"
#define DYNAMIC_MODULE "BSDynamic_module"
#define DECODE_STREAM "BSDecode_stream"
#define IGNORE_IP "BSIgnore_ip"
#define IGNORE_PORT "BSIgnore_port"
#define DYNAMIC_FILE "BSDynamic_file"
#define RULE_FILE "BSRule_file"
#define RULE_IGNORE_CHAR "BSRule_ignore_char"
#define RULE_IGNORE_IP "BSRule_ignore_ip"
#define RULE_IGNORE_PORT "BSRule_ignore_port"
#define RULE_DECODE_MSG1 "BSRule_decode_msg1"
#define RULE_DECODE_MSG2 "BSRule_decode_msg2"
#define RULE_DECODE_MSG3 "BSRule_decode_msg3"
#define OUT_TYPE "BSOut_type"
#define ABUSER_ALERT "BSAbuser_alert"
#define ABUSER_LOG "BSAbuser_log"
#define REASON_ALERT "BSReason_alert"
#define REASON_LOG "BSReason_log"
#define ABUSER_ALERT_FORMAT "BSAbuser_alert_format"
#define REASON_ALERT_FORMAT "BSReason_alert_format"
#define ABUSER_LOG_FORMAT "BSAbuser_log_format"
#define REASON_LOG_FORMAT "BSReason_log_format"


struct sys_variable{
	uint ip; //��ʾ����ip��ַ��ipaddr��һ��ip��ַ�ṹ
	uint mask;//��ʾ�������룬����ʶ������ip
	char *rpath;//ϵͳ��·��
	int bhttp;//�Ƿ����httpЭ��
	int btcp;//�Ƿ����tcpЭ��
	int budp;//�Ƿ����udpЭ��
	int bicmp;//�Ƿ����icmpЭ��
	int alert;//�Ƿ����������Ϣ
	int log;//�Ƿ������¼��Ϣ
	int dym;//�Ƿ�֧�ֶ�̬ģ�����
};
struct decode_data{
	int stream;//�Ƿ���������
	uint igip[10];//����ip���� ,���֧��10��
	ushort igport[10];//����port����,���֧��10��
};

struct dynamic_module {
	char *mpath;//ģ��·��
	struct mvariable *mv;//ģ�����ñ���
	struct dynamic_module *next;//��һģ��ָ��
};
struct mvariable{
	char **mvname;//ģ�������
	char **mvvalue;//ģ�����ֵ
};
struct decode_rule{
	char ic[10];//���Է�����
	uint igip[10];
	ushort igport[10];
	char *msg1;//Ԥ������Ϣ1
	char *msg2;//ͬ��
	char *msg3;//ͬ��
};
struct out_print{
	int type;//���������ʽ
	char *abalert;//���ü��澯��־·��
	char *ablog;//���ü���¼��־·��
	char *realert;//����澯·��
	char *relog;//�����¼·��
	char *abaformat;//���ø澯�����ʽ
	char *ablformat;//���ü�¼�����ʽ
	char *reaformat;//�����������ʽ
	char *relformat;//�����¼�����ʽ
};

struct global_variable {
	void *gvp; //����ָ��
	struct global_variable *next;//��һ�������ṹָ��
};
struct sys_config{
	struct sys_variable sv; //ϵͳ����ָ��
	struct global_variable gv;//ȫ�ֱ���ָ��
	struct decode_data dd;//���ݽ�����(Ԥ����ģ��)ָ��
	struct dynamic_module dm;//��̬ģ��ָ��
	struct decode_rule dr;//���������ָ��
	struct out_print op;//����ṹָ��
};

int sysconfig(char *);
int lineto(char *,int);
#endif
