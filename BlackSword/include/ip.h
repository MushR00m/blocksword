#ifndef ip_h
#define ip_h
#include "sysconfig.h"

struct ipp{
	struct{
		unsigned char version:4; //�汾��
		unsigned char len:4; //ͷ����=version*len
	}vl;
	unsigned char tos;//tos,�������
	ushort lenght;//������
	ushort id;
	struct{
		ushort flag:3;
		ushort offset:13;
	}fos;
	unsigned char ttl; //����ʱ��
	unsigned char tp; //Э������
	ushort chsum;
	uint sip;
	uint dip;
};
#define ETHERNET 14
struct ipp* ip_getstruct(uchar *);//����ippָ��
int ip_gethlenght(struct ipp *);//����IP��ͷ��
struct tcpp * tcp_getstruct(struct ipp *);//��������ָ��
int ip_checksum(struct ipp *);//У����Ƿ���ȷ
#endif

