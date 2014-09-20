#ifndef derule_h
#define derule_h
#include "sysconfig.h"

struct variable_func{
	int id;//��ʶ�������
	int type;//��������
	union{
		char *str;
		int var;
	}value;
};

struct function{
	int fid;//����id��
	struct variable_func pt[2];//������������ͷָ��
};
struct variable_rule{
//	int id;
	int type;
	char name[24];
	union{
		char *str;
		int var;
	}value;
};
struct rprocess{ //����ʽ�����򼯺�����
	char *name;//�ӹ�����
	int id;//�ӹ���Ψһid��
	struct function fn[10];//�ӹ���������ͷָ��
	struct rprocess *next;//��һ�ӹ���ṹ
};
struct rtime{
	char *name;//time�͹�����
	int id;//����Ψһid��
	struct function fn[10];//time�ͺ������飬���֧��10�����ʽ
};

struct iport{
	uint sip;
	uint dip;
	ushort sport;
	ushort dport;
};
struct rulelink{
	uint  sip;//����Դip��ַ
	uint  dip;//����Ŀ��ip��ַ
	ushort sport;//����Դ�˿ڵ�ַ
	ushort dport;//����Ŀ��˿ڵ�ַ
	int both;
	struct rule *tlk;//���tcpЭ�������ͷָ��
	struct rule *ulk;//���udpЭ�������ͷָ��
	struct rule *ilk;//���icmpЭ�������ͷָ��
	struct rule *hlk;//���httpЭ�������ͷָ��
	struct rulelink *next;//��һ����ַ����ṹ��ָ��
};
struct ruledata{
	uchar pt;//protocol type
	uchar rt;//rule type
	uchar dt;//data direction
	uchar pid;//process of rule id
	int both;
	uint sip;
	uint dip;
	ushort sport;
	ushort dport;
	char *name;
	int id;
	char *func;
};

union tprule{
	struct rtime *rt;
	struct rprocess *rp;
};
struct rule{
	int type;//�������ͣ�time����process
	union tprule tp;//�����壬����typeָ��rrule��rprocess����ṹ,ÿ������֧��10���ӹ���
	struct variable_rule vb[10];//�����������ͷָ��
	struct rule *next;//��һ��ַ������
};
//function 
int createrulelink();//�ӹ����ļ�·�������д���������

int createrulelink_f(char *);//�����ļ�

int isame(struct iport *iport1,struct iport *iport2);//�ж�������ַ�Ƿ����
int isame_both(struct iport *iport1,struct iport *iport2,int);//�ж�������ַ�Ƿ����
int isignore(char);

int isip(char *);

int islegal(char *[],int);

int isport(char *);

int isuniq(int);

int linetorule(struct rulelink *,struct ruledata *);

int linetorules(struct ruledata *);

int linetofunc(int,struct rule *,struct ruledata *);

int datatostruct(char *[],struct ruledata *);

int bpfuncline(char *,char **);

void summary();//������й��������ܽ���Ϣ
#endif
