#ifndef reasoning_h
#define reasoning_h
struct bskl{
	int id;//֪ʶΨһid��
	int type;//֪ʶ���ͣ���alone��CNF�ͣ��������ͺͺ�ȡ�͡�
	union proof{//֤��ָ��
		int *id;
		struct klfunc *fc;
	};*pf;
	char *result;//������
	int probability;//���Ŷ�
	int risk;//���յȼ�
};
struct klfunc{
	int funcid;
	char *parameter;
};
#endif