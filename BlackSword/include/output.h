#ifndef output_h
#define output_h
struct note{
	int type; //�����Ϣ����
	char *time;
	int id;
	int protocol;//Э��
	char * msg;//alert��log����
	struct pdata *op;//���ݽṹָ��
};
#endif