#include "derule.h"
#include "abuse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
extern char *rulep[20];
extern struct sys_config gv;
struct rulelink *rks=NULL;
char *cufile=NULL;
int culine;

int createrulelink(){//�ӹ����ļ�·�������д���������
	int i=0;
	int status;
	while(rulep[i]){
		status=createrulelink_f(rulep[i]);
		if(status==1){
			printf("�����ļ���ʧ�ܣ����⣺%s\n",rulep[i]);
		}
		if(i==19)
			break;
		i++;
	}
	return 0;
}
int getpath(char *path,char *file){
	char *p=NULL;
	if(file[0]=='$'){
		if(!(p=strstr(file,"\\"))){
			if(!(p=strstr(file,"/"))){
				return -1;
			}
		strcpy(path,gv.sv.rpath);
		strcat(path,p);
	}else{
		strcpy(path,file);
	}
	}
	return 0;
}
int createrulelink_f(char *file){ //�����ļ�
	char path[120]={0};
	char line[1024] = { 0 };
	char *data[10]={0};
	struct ruledata rd={0};
	FILE *fp;
	int status=0;
	culine=0;
	getpath(path,file);
	cufile=path;
	if(!(fp=fopen(path,"r"))){
		printf("ָ�������ļ�%s������\n",path);
		exit(1);
	}
	while (1){ //���������ļ�������ģʽ
		int i = 0;
		int j = 1;
		if(!fgets(line, 1023, fp))
			break;
		culine++;
		if(isignore(line[0])) //�ж������ַ��ǲ���ע�ͷ�
			break;
		data[0] = line;
		while (line[i]){ //�Կո�ָ�����10����
			if (line[i] == ' '){
				line[i] = '\0';
				data[j] = (char *)(line + i+1);
				j++;
			}
			i++;
			if (j == 10)
				break;
		}
		if(islegal(data,culine)){ //��֤����Ϸ���
			exit(0);
		}
		
		datatostruct(data,&rd); //�ӹ�������ȡ�����ݣ����ruledata�ṹ
		linetorules(&rd);//ʹ��ruledata���ݽṹ������ת���ɹ����壬���ص�rks��������
	}
	return 0;
}

int isame(struct iport *iport1, struct iport *iport2){
	if (iport1->sip == 0 ||
		iport2->sip == 0 ||
		iport1->sip == iport2->sip){
		if (iport1->sport == 0 ||
			iport2->sport == 0 ||
			iport2->sport == iport2->sport){
			if (iport1->dip == 0 ||
				iport2->dip == 0 ||
				iport1->sip == iport2->dip){
				if (iport1->dport == 0 ||
					iport2->dport == 0 ||
					iport2->dport == iport2->dport){
					return 1;
				}
			}
		}
	}
	return 0;
}
//�Աȵ�ַ�Ƿ����
int isame_both(struct iport *iport1, struct iport *iport2,int both){
	//���ߵ���������
	struct iport ipt = { 0 };
	if (!both){
		return isame(iport1, iport2);
	}
	//�ڶ�������˫��
	if (both == 2){
		ipt.sip = iport2->dip;
		ipt.sport = iport2->dport;
		ipt.dip = iport2->sip;
		ipt.dport = iport2->sport;
		return isame(iport1, iport2) || isame(iport1, &ipt)+2;
	}
	//��һ������˫��
	if (both == 1){
		ipt.sip = iport1->dip;
		ipt.sport = iport1->dport;
		ipt.dip = iport1->sip;
		ipt.dport = iport1->sport;
		return isame(iport1, iport2) || isame(&ipt, iport2)+1;
	}
	return 0;
}
int isignore(char c){
	int i = 0;
	while (gv.dr.ic[i] != '\0'){
		if (gv.dr.ic[i] == c)
			return 1;
		i++;
	}
	return 0;
}
int isip(char *ip){
	return 1;
}
int isport(char *port){
	return 1;
}
int isuniq(int id){
	return 1;
}
int isid(char *id){
	return 1;
}
int islegal(char *data[],int ln){
	int id=0;
	if (strcmp(data[0], "BSRule") != 0){
		printf("�����������﷨���󣬹���ͷӦΪBSRule���� %d ��\n",ln);
		return 1;
	}
	if (strcmp(data[1], "http") != 0 &&
		strcmp(data[1], "tcp") != 0 &&
		strcmp(data[1], "udp") != 0 &&
		strcmp(data[1], "tcp") != 0){
		printf("�����������﷨����Э�����ʹ����� %d ��\n",ln);
		return 2;
	}
	if (!isip(data[2]) || !isport(data[3])){
		printf("�����������﷨���󣬵�һ����IP��˿����ݴ����� %d ��\n",ln);
		return 3;
	}
	if (strcmp(data[4],"->")!=0 &&
		strcmp(data[4],"<-")!=0 &&
		strcmp(data[4],"<->")!=0 ){
			printf("�����������﷨��������������������� %d ��\n",ln);
			return 4;
	}
	if(!isip(data[5]) || !isport(data[6])){
		printf("�����������﷨���󣬵ڶ�����IP��˿����ݴ����� %d ��\n",ln);
		return 5;
	}
	if(!isid(data[8])){
		printf("�����������﷨���󣬹���ID�Ų��Ϸ����� %d ��\n",ln);
		return 8;
	}
	if(!isuniq(id)){
		id = atoi(data[8]);
		printf("�����������﷨���󣬹���ID�Ų�Ψһ���� %d ��\n",ln);
		return 8;
	}
	return 0;
}

//���ݽṹ�����������
int linetorule(struct rulelink *rk,struct ruledata *rd){
	struct rule *cu = { 0 };
	struct rule *prev = { 0 };
	//����rulelink�ṹ�����Ԥ����rule�ṹ��ָ��
	if(rd->pt==1){ //http
		if(rk->hlk==NULL){
			rk->hlk=(struct rule*)calloc(1,sizeof(struct rule));
			cu=rk->hlk;
		}else{
			cu=rk->hlk;
			while(cu!=NULL){
				prev=cu;
				cu=cu->next;
			}
			cu=(struct rule *)calloc(1,sizeof(struct rule));
			prev->next=cu;
		}
	}else if(rd->pt==2){ //tcp
		if(rk->tlk==NULL){
			rk->tlk=(struct rule*)calloc(1,sizeof(struct rule));
			cu=rk->tlk;
		}else{
			cu=rk->tlk;
			while(cu!=NULL){
				prev=cu;
				cu=cu->next;
			}
			cu=(struct rule *)calloc(1,sizeof(struct rule));
			prev->next=cu;
		}
	}else if(rd->pt==3){ //udp
		if(rk->ulk==NULL){
			rk->ulk=(struct rule*)calloc(1,sizeof(struct rule));
			cu=rk->ulk;
		}else{
			cu=rk->ulk;
			while(cu!=NULL){
				prev=cu;
				cu=cu->next;
			}
			cu=(struct rule *)calloc(1,sizeof(struct rule));
			prev->next=cu;
		}
	}else if(rd->pt==4){ //icmp
		if(rk->ilk==NULL){
			rk->ilk=(struct rule*)calloc(1,sizeof(struct rule));
			cu=rk->ilk;
		}else{
			cu=rk->ilk;
			while(cu!=NULL){
				prev=cu;
				cu=cu->next;
			}
			cu=(struct rule *)calloc(1,sizeof(struct rule));
			prev->next=cu;
		}
	}
	cu->type=rd->rt;
	linetofunc(cu->type,cu,rd);
	return 0;
}

//�ָ�������ַ���
int bpfuncline(char *line,char *p[]){
	int i = 0;
	int j = 0;
	while(line[i]!='}'&& j<=9){
		if(line[i]==';'){
			p[j]=(char*)(line+i+1);
			line[i]='\0';
			j++;
		}else if(line[i]=='{'){
			p[j]=(char*)(line+i+1);
			j++;
		}
		i++;
	}
	return j;
}

//�����Ӻ����ַ���
int opfunc(struct function *fc,struct rule *r,char *fl){ //���ݺ��������磺alert��"test");ת���ɺ����ṹ
	//������ʽ�ַ���
	char *v1=NULL;
	char *v2=NULL;
	char *p=NULL;
	if((p=strstr(fl,"++"))){
		p[0]='\0'; //�и�����ʽ����
		v1=fl;
		set_addself(r,fc,v1);
		return 1;
	}
	if((p=strstr(fl,"--"))){
		p[0]='\0';
		v1=fl;
		set_delself(r,fc,v1);
		return 2;
	}
	if((p=strstr(fl,">"))){
		p[0]='\0';
		v1=fl;
		v2=p+1;
		set_greater(r,fc,v1,v2);
		return 3;
	}
	if((p=strstr(fl,"<"))){
		p[0]='\0';
		v1=fl;
		v2=p+1;
		set_less(r,fc,v1,v2);
		return 4;
	}
	if((p=strstr(fl,"=="))){
		p[0]='\0';
		v1=fl;
		v2=p+2;
		set_equal(r,fc,v1,v2);
		return 5;
	}
	if((p=strstr(fl,"!="))){
		p[0]='\0';
		v1=fl;
		v2=p+2;
		set_unequal(r,fc,v1,v2);
		return 6;
	}
	set_function(r,fc,fl);
	return 0;
}
//���������������rule�ṹ
int linetofunc(int type,struct rule *r,struct ruledata *rd){
	int i=0;
	if(type==1){
		char *func[10]={0};
		struct rtime *p=NULL;
		int num=0;
		p=(struct rtime*)calloc(1,sizeof(struct rtime));
		r->tp.rt=p;
		p->name=rd->name;
		p->id=rd->id;
		num=bpfuncline(rd->func,func);
		for(i=0;i<num;i++){
			opfunc(&p->fn[i],r,func[i]);
		}
	}else if(type==2){
		struct rprocess *p=NULL;
		p=(struct rprocess *)calloc(10,sizeof(struct rprocess));//ÿ������֧��10���ӹ���
	}
	return 0;
}

int linetorules(struct ruledata *rd){
	struct rulelink *current=NULL;
	struct rulelink *prev=NULL;
	struct iport cip;
	int first=1;
	cip.sip=rd->sip;
	cip.dip=rd->dip;
	cip.sport=rd->sport;
	cip.dport=rd->dport;
	if(!rks){
		rks=(struct rulelink*)calloc(1,sizeof(struct rulelink));//�����ڴ棬��һ��rulelink
		first=0;
	}
	current=rks;
	
	while(current && first){
		if(rd->both){
			if(isame_both(&cip,(struct iport *)current,1)){ //�жϵ�ַ�Ƿ���ͬ
				current->both=1;
				break;
			}
		}else{
			if(isame(&cip,(struct iport *)current)){ //�жϵ�ַ�Ƿ���ͬ
				break;
			}
		}
		prev=current;
		current=current->next;
	}
	if(current==NULL){
		current=(struct rulelink*)calloc(1,sizeof(struct rulelink));//����һ��rulelink�ṹ
		prev->next=current;
	}
	current->sip = rd->sip;
	current->dip = rd->dip;
	current->sport = rd->sport;
	current->dport = rd->dport;
	current->both=rd->both;
	linetorule(current,rd);
	return 0;
}
int setiport(struct ruledata *rd,char *sip,char *dip,char *sport,char *dport){
	if(strcmp(sip,"any")==0)
		rd->sip=0;
	else
		rd->sip=inet_addr(sip);
	if(strcmp(dip,"any")==0)
		rd->dip=0;
	else
		rd->dip=inet_addr(dip);
	if(strcmp(sport,"any")==0)
		rd->sport=0;
	else
		rd->sport=atoi(sport);
	if(strcmp(dport,"any")==0)
		rd->dport=0;
	else
		rd->dport=atoi(dport);
}
//�ṹ���������ݣ���ȡ�������ruledata�ṹ
int datatostruct(char *data[],struct ruledata *rd){
	int i=0;
	char *bp[3]={0};
	if(data[1][0]=='h')
		rd->pt=1;
	else if(data[1][0]=='t')
		rd->pt=2;
	else if(data[1][0]=='u')
		rd->pt=3;
	else if(data[1][0]=='i')
		rd->pt=4;
	if(strcmp(data[4],"->")==0){
		setiport(rd,data[2],data[5],data[3],data[6]);
		rd->both=0;
	}else if(strcmp(data[4],"<-")==0){
		setiport(rd,data[3],data[6],data[2],data[5]);
		rd->both=0;
	}else{
		setiport(rd,data[2],data[5],data[3],data[6]);
		rd->both=1;
	}
	bp[0] = data[7];
	while(data[7][i]){
		if(data[7][i]=='_'){
			data[7][i]='\0';
			if (bp[1]==0)
				bp[1]=(char*)(data[7]+i+1);
			else
				bp[2]=(char*)(data[7]+i+1);
		}
		i++;
	}
	if (strcmp("process",bp[0])==0)
		rd->rt=2;
	else if(strcmp("time",bp[0])==0)
		rd->rt=1;
	if(bp[1]!=0)
		rd->name=bp[1];
	if(bp[2]!=0)
		rd->pid=atoi(bp[2]);
	rd->id=atoi(data[8]);
	rd->func=data[9];
	return 0;
}

void summary(){ //������й��������ܽ���Ϣ
}