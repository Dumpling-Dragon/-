//�ֵܣ��浵����Ĳ��Ǻܻᣬ�������ʵ�ְ� 
//����Ӹ����֣� 
#include"kb.h"
#define gwgs/*��������*/ 8
#define ztzs/*״̬����*/ 8
#define bpl/*������Ʒ����*/ 12
using namespace std;
string /*�汾*/version="1.0.2",title="�ӱڵĴ�ð��"+version,/*�����������*/players[1000],/*��ҵ��������ƣ�����չ����*/players1[1000];
int use1=0,/*��Ҹ���*/nop,/*�غ�*/hh;
//��� 
string /*�������*/name,/*�����������*/s[]={"�ȼ�","Ѫ��","����","����","�ǻ�","����ֵ"};
double /*�������*/a[6],/*��������*/temp=1.2,/*�������ֵ*/maxhealth,/*�����ֵ*/maxexp;
//���� 
string /*��������*/t[]={"��Ƥ","����","����","����","��ͨ","���","�̿�","��װ","ѧ��"},/*��������*/u[gwgs]={"��ʬ","����","���鷨ʦ","а�����","��з","����","�粼��","�����"};
double /*���й����ʼ����*/gw[gwgs][4]={/*��ʬ*/{50,5,5,5},/*����*/{35,8,5,5},/*���鷨ʦ*/{30,10,3,10},/*а�����*/{25,10,0,15},/*��з*/{100,5,20,3},/*����*/{50,5,5,10},/*�粼��*/{40,8,5,10},
										/*�����*/{80,8,8,5}},
		/*״̬��������*/v[]={1,1,1,1},/*��ǰ��������*/gwa[6];
int /*�����ص����*/gwtd,/*�����������*/gwmz,/*����ȼ����*/gwdj,/*����ֵ*/tp1;	
//����&����&�̵� 
string /*������Ʒ����*/w[]={"���","����ҩˮ","ǿЧ����ҩˮ","��������ҩˮ","��ҩˮ","����ҩˮ","����ҩˮ","����ҩˮ","�Ƽ�ҩˮ","�Բ�ҩˮ","������","ȼ��ƿ"},
		/*������Ʒ����*/js[12]={"�ӱڴ�ð�յ�ͨ�û���","�ظ�10������ֵ","�ظ�20������ֵ","�ظ�30������ֵ","��������������5�غ�","��������������5�غ�","�ǻ۷���������5�غ�",
								"���˹������룬����5�غ�","���˷������룬����5�غ�","�����ǻۼ��룬����5�غ�","ʹ���˳���6�غ��ܵ�5�㶾���˺�","ʹ���˳���3�غ��ܵ�10��ȼ���˺�"},
		/*��������*/x[]={"ľ","ľ","ľ","��","��","��"};
int /*����*/bp[bpl],/*����۸�*/buyprice[bpl]={0,10,20,30,50,50,50,50,50,50,50,50},/*���ۼ۸�*/sellprice[bpl]={0,5,10,15,20,20,20,20,20,20,20,20};

//״̬ 
string /*״̬����*/ztzw[ztzs]={"��","����","����","����","�Ƽ�","�Բ�","�ж�","ȼ��"};/*���״̬�غ�*/int zthh[ztzs],/*����״̬�غ�*/gwzthh[ztzs];

bool /*��Ʒ�Ƿ��ܹ�ʹ��*/okuse[12]={0,1,1,1,1,1,1,1,1,1,1,1},canuse[bpl]={0,1,1,1,0,0,0,0,0,0,0,0},/*�Ƿ���ս����*/onfight=false;
void vs();void wj();void gw1();void dd(int);void bang();void broad();void setnew(); 
void setwindow()
{
	HICON cwnd=(HICON)LoadImage(NULL,"kb.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE); 
   	HWND  hwnd=GetConsoleWindow();  
   	SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)cwnd);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rc;
    rc.Left = 0;
    rc.Top = 0;
    rc.Right = 80;
    rc.Bottom = 25;
    SetConsoleWindowInfo(hOut, TRUE, &rc);
	SetConsoleTitle(title.data());
}
void findfiles()/*�����ļ��еĴ浵*/{
	nop=0;
	const char *to_search="C:\\players\\*.kbm";
	long handle;
    struct _finddata_t fileinfo;
    handle=_findfirst(to_search,&fileinfo);
    if(handle==-1)return;
    string sname=fileinfo.name;
    players1[nop]=sname;
    players[nop++]=sname.substr(0,sname.find("."));
    while(!_findnext(handle,&fileinfo)){
    	sname=fileinfo.name;
    	players1[nop]=sname;
  		players[nop++]=sname.substr(0,sname.find("."));
	}
    _findclose(handle);
}
double qz(double a)/*����һλС��*/{
	return int((a+0.05)*10)/10.0;
}
void showcd(int page,int pages,bool isde){
	for(int i=0;i<9&&i+page*9<nop;i++)cout<<"["<<i+1<<"]\t"<<players[i+page*9]<<endl;
	if(page<pages)cout<<"[+]\t��һҳ\n";
	if(page)cout<<"[-]\t��һҳ\n";
	if(isde){
		cout<<"[n]\t�����´浵\n";
		if(nop)cout<<"[d]\tɾ���浵\n";
	}
	cout<<"-------------------------------------------------------------------------------\n\n";
}
void newcd(int page,int pages){
	ofstream fout;
	string cdname;
	while(true){
		cls;
		cout<<"��ѡ��浵��\n-------------------------------------------------------------------------------\n";
		showcd(page,pages,true);
		cle;
		cout<<"�������´浵����ֱ�Ӱ��س���������\n";
		getline(cin,cdname);
		int aaa=0;
		if(cdname==""){
			dd(page);
			return;
		}
		for(int i=0;i<cdname.length();i++){
			if(cdname[i]>=32&&cdname[i]<=47)aaa++;//���Ƿ��ַ� 
		}
		if(aaa){
			cout<<"��ʾ�������к��зǷ��ַ������������롣\n";
			pause;
			continue;
		}
  		aaa=0;
  		for(int i=0;i<nop;i++)
  			if(cdname==players[i])aaa++;
		if(aaa){
			cout<<"\n�浵���ظ�����ɾ�������浵������´浵��\n";
			pause;
			continue;
		}
		else break;
	}
	fout.close();
	fout.open(("C://players//"+cdname+".kbm").data(),ios::out);
	if(fout.good()){
		fout<<cdname<<"\n124 8836 916 916 916 36 100 100\n";
		fill(bp,bp+bpl,0);//fill�����������ǣ���һ�������Ԫ�ض�����valֵ������������fill(vec.begin(), vec.end(), val); valΪ��Ҫ�滻��ֵ
		for(int i=0;i<bpl;i++)fout<<bp[i]*88+36<<" ";//��ʼ���������� 
		fout.close();
		cout<<"\n�ɹ������浵��\n";
	}
	else{
		RED;
		cout<<"���󣺴浵����ʧ�ܣ�\n";
		autocolor;
		pause;
		dd(page);
		return;
	}
	pause;
	cls;
	dd(page);
	return;
}
void deletecd(int page)/*ɾ���浵*/{
	int pages=nop/10,bh;
	cls;
	cout<<"������Ҫɾ���Ĵ浵��ţ�\n-------------------------------------------------------------------------------\n[0]\t����\n";
	showcd(page,pages,false);
	bh=getch();
	cout<<endl;
	while((bh-48+page*9>nop&&bh!='+'&&bh!='-')||((bh<'0'||bh>'9')&&bh!='+'&&bh!='-')||(bh=='+'&&page>=pages)||(bh=='-'&&page==0))bh=getch();
	if(bh=='0'){
		dd(0);
		return;
	}
	else if(bh=='+'&&page<pages){
		deletecd(page+1);
		return;
	}
	else if(bh=='-'&&page){
		deletecd(page-1);
		return;
	}
	else{
		cls;
		int xz;
		cout<<"������Ҫɾ���Ĵ浵��ţ�\n-------------------------------------------------------------------------------\n[0]\t����\n";
		showcd(page,pages,false);
		cout<<"��ȷ��Ҫɾ�� "<<players[page*9+bh-49]<<" �𣿴˲����޷��ָ���\n[1]��\t[2]��\n";
		xz=getch()-48;
		while(xz<1||xz>2)xz=getch()-48;
		if(xz==1){
			for(int i=0;i<10;i++){
				cls;
				cout<<"�밴��10�� 1 ��ɾ���浵,�����������أ� "<<i;
				if(getch()-48!=1){
					dd(page);
					return;
				}
			}
			cls; 
			bool re=remove(("C://players//"+players1[page*9+bh-49]).data());
			if(!re)cout<<"�ɹ�ɾ���浵��\n";
			else{
				RED;
				cout<<"����ɾ���浵ʧ�ܣ�\n";
				autocolor;
			}
			pause;
		}
		cls;
		dd(page);
	}
}
void dd(int page)/*����*/{
	nop=0;
	findfiles();
	cls;
	double f;
	int j,cd,bh,pages=nop/10;
	string path,cdname;
	ifstream fin;
	cout<<"��ѡ��浵��\n-------------------------------------------------------------------------------\n";
	showcd(page,pages,true);
	cd=getch();
	while((cd-48+page*9>nop&&cd!='+'&&cd!='-'&&cd!='n'&&cd!='d')||((cd<'0'||cd>'9')&&cd!='+'&&cd!='-'&&cd!='n'&&cd!='d')||(cd=='+'&&page>=pages)||(cd=='-'&&page==0)||(cd=='d'&&nop==0))cd=getch();
	if(cd=='+'&&page<pages){
		cls;
		dd(page+1);
	}
	else if(cd=='-'&&page){
		cls;
		dd(page-1);
	}
	else if(cd-48+page*9<=nop){
		fin.open(("C:\\players\\"+players1[cd-49+page*9]).data());
		if(!fin.good()){
			cls;
			RED;
			cout<<"���󣺴浵��ȡʧ�ܣ�\n";
			autocolor;
			pause;
			dd(page);
			return;
		}
		getline(fin,name);
		if(name==""){
			cls;
			RED;
			cout<<"�浵��ȡ����\n�������ƣ��������ȡ����\n";
			autocolor;
			dd(page);
			return;
		}
		for(int ii=0;ii<6;ii++)
		{
			fin>>a[ii];
			a[ii]=(a[ii]-36)/88;
		}
		fin>>maxhealth>>maxexp;
		for(int ii=0;ii<bpl;ii++)
		{
			fin>>bp[ii];
			bp[ii]=(a[ii]-36)/88;
		}
	}
	else if(cd=='n')newcd(page,pages);
	else if(cd=='d')deletecd(0);
	cls;
}
void cd()/*�浵*/{
	ofstream fout(("C://players//"+name+".kbm").data(),ios::out);//д�� 
	if(fout.good()){//����浵���� 
		fout<<name<<endl;
		for(int i=0;i<6;i++)fout<<a[i]*88+36<<" ";//��Ҳ���  
		fout<<endl<<maxhealth<<" "<<maxexp<<endl;//�������ֵ�������ֵ 
		for(int i=0;i<bpl;i++)fout<<bp[i]*88+36<<" ";//������Ʒ�浵 
	}
	else{
		RED;
		cls;
		cout<<"���󣺴浵����ʧ�ܣ�\n";
		pause;
		exit(1);//�˳� 
	}
}
void wj()/*��ʾ�������*/{
	double zt[3];
	for(int i=0;i<3;i++){
		if(zthh[i]>0&&zthh[i+3]==0)zt[i]=2;
		else if(zthh[i]==0&&zthh[i+3]>0)zt[i]=0.5;
		else zt[i]=1;
	}
	maxhealth=qz(maxhealth);
	maxexp=(int)maxexp;
	RG;
	cout<<"-------------------------------------------------------------------------------\n"<<name<<endl;
	for(int i=0;i<6;i++){
		a[i]=qz(a[i]);
		if(i>1&&i<5)cout<<s[i]<<":"<<qz(a[i]*zt[i-2]);
		else cout<<s[i]<<":"<<a[i];
		//cout<<s[i]<<":"<<((i>1&&i<5)?qz(a[i]*zt[i-2]):a[i]);
		if(i==1)cout<<"/"<<maxhealth;
		if(i==5)cout<<"/"<<maxexp;
		//cout<<"***"<<a[i]<<endl;
		cout<<" ";
	}
	cout<<endl;
	for(int i=0;i<ztzs;i++){
		if(zthh[i]){
			if(i<3){
				GREEN;
			}else RED;
			cout<<ztzw[i]<<"["<<zthh[i]<<"]\t";
		}
	}
	RG;
	cout<<endl<<"-------------------------------------------------------------------------------\n";
	autocolor;
}
int use(int sf)/*ʹ����Ʒ*/{
	int xz;
	if(!canuse[sf]&&!onfight){
		cout<<"\n�㲻��������ʹ��"<<w[sf]<<"��";
		wait;
		cls;
		return 1;
	}
	else if(okuse[sf]){
		cle;
		cout<<"\n��Ҫʹ��"<<w[sf]<<"��\n[1]��\t[2]��\n";
 		xz=getch()-48;
 		while(xz<1||xz>2)xz=getch()-48;
		if(xz==1){
			if(sf>=1&&sf<=3){
				a[1]+=sf*10;
				if(a[1]>maxhealth)a[1]=maxhealth;
				cls;
				wj();
				if(onfight)gw1();
				GREEN;
				cout<<"\n��";
				autocolor;
				cout<<"ʹ���� "<<w[sf]<<" ,���ظ��� "<<sf*10<<" ������ֵ��\n";
				wait;
			}else if(sf>3&&sf<=6){
				autocolor;
				if(onfight){
					cls;
					zthh[sf-4]+=5;
					wj();
					if(sf==4)zthh[sf-4]++;
					gw1();
					GREEN;
					cout<<"\n��";
					autocolor;
					cout<<"ʹ���� "<<w[sf]<<" ,������� ";
					GREEN;
					cout<<ztzw[sf-4];
					autocolor;
					cout<<" Ч����\n";
				}
				else cout<<"\n�㲻��������ʹ��"<<w[sf]<<"��"<<endl;
				wait;
			}
			else if(sf>6&&sf<=9){
				autocolor;
				if(onfight){
					cls;
					gwzthh[sf-4]+=5;
					wj();
					if(sf==5)gwzthh[sf-4]++; 
					gw1();
					GREEN;
					cout<<"��";
					autocolor;
					cout<<"��";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"����һƿ "<<w[sf]<<" ,��ʹ";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"�����";
					RED;
					cout<<ztzw[sf-4];
					autocolor;
					cout<<"Ч����\n";
				}
				else cout<<"�㲻��������ʹ��"<<w[sf]<<"��"<<endl;
				wait;
			}
			else if(sf==10){
				autocolor;
				if(onfight){
					cls;
					wj();
					gwzthh[6]+=5;
					gw1();
					cout<<"\n";
					GREEN;
					cout<<"��";
					autocolor;
					cout<<"��";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"����һ����������\n";
					wait;
					cout<<"\n";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"�ж��ˣ�\n";
					wait;
				}
				else cout<<"�㲻��������ʹ��"<<w[sf]<<"��"<<endl;
				wait;
			}
			else if(sf==11){
				autocolor;
				if(onfight){
					cls;
					wj();
					gwzthh[7]+=3;
					gw1();
					cout<<"\n";
					GREEN;
					cout<<"��";
					autocolor;
					cout<<"��";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"����һ��ȼ��ƿ��\n";
					pause;
					cout<<"\n";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"�������ˣ�\n";
					wait;
				}
				else cout<<"�㲻��������ʹ��"<<w[sf]<<"��"<<endl;
			}
			cd();
			return 0;
		}
	}else{
		cout<<"\n�㲻��ʹ��"<<w[sf]<<"��"<<endl;
		wait;
		cle;
	}
	cls;
	return 1;
}
int bbxs(int ii,int bp1[12],int page,int pages)/*��ʾ�����е���Ʒ*/{
	RG;
	cout<<"-------------------------------------------------------------------------------\n\t\t\t\t����\n-------------------------------------------------------------------------------\n";
	cout<<"-------------------------------------------------------------------------------���           ����    ����        ����\n-------------------------------------------------------------------------------\n";
	autocolor;
	cout<<"[0]            ����\n";
	int i=page*10,j=0;
	while(j<10&&i<bpl){
		if(bp[i]){
			cout<<"["<<ii++<<"]";
			int ij=ii-1,len=0;
			while(ij/=10)len++;
			for(int jj=0;jj<(8-(w[i].length()/2))*2-len;jj++)cout<<' ';
			cout<<w[i]<<"\t"<<bp[i]<<"\t"<<js[i]<<endl;
			bp1[ii-1]=i;
			j++;
		}
		i++;
	}
	/*for(int i=page*10;i<i+10;i++){
		if(bp[i]){
			cout<<"["<<ii++<<"]";
			int ij=ii-1,len=0;
			while(ij/=10)len++;
			for(int jj=0;jj<(8-(w[i].length()/2))*2-len;jj++)cout<<" ";
			cout<<w[i]<<"\t"<<bp[i]<<"\t"<<js[i]<<endl;
			bp1[ii-1]=i;
		}
	}*/
	//����е����⣬���һ�� 
	if(page){
		cout<<"[-]        ��һҳ\n";
		ii++;
	}
	if(page<pages){
		cout<<"[+]        ��һҳ\n";
		ii++;
	}
	RG;
	cout<<"-------------------------------------------------------------------------------\n\n";
	autocolor;
	return ii;
}
void bb(int nowpage)/*����������*/{
	int i=0,items,pages=0;
	for(int j=0;j<bpl;j++)if(bp[j])pages++;
	pages/=10;
	//i+=pages*10;
	int ii=0,bp1[12],sf,len;
	fill(bp1,bp1+12,-1);
	use1=0;
	ii=bbxs(1,bp1,nowpage,pages);
	cle;
	cout<<"��Ҫʹ��ʲô��Ʒ��\n";
	sf=getch()-'0';
	while(((sf>ii||sf<0)&&sf+48!='+'&&sf+48!='-')||(sf+48=='+'&&nowpage>=pages)||(sf+48=='-'&&nowpage==0))sf=getch()-48;
	if(sf==0){
		use1=1;
		cls;
		return;
	}
	if(sf+48=='-'&&nowpage){
		cls;
		//bb(bbxs(1,bp1,--nowpage,pages),nowpage);
		bb(--nowpage);
	}
	else if(sf+48=='+'&&nowpage<pages){
		cls;
		//bb(bbxs(1,bp1,++nowpage,pages),nowpage);
		bb(++nowpage);
	}
	else if(use(bp1[sf])==1){
		bb(nowpage);
		cle;
		return;
	}
	else bp[bp1[sf]]--;
}
void fh()/*����*/{
	tp1=0;
	a[1]=maxhealth;
	a[5]-=int(a[5]*0.2);
	fill(zthh,zthh+8,0);
	fill(gwzthh,gwzthh+8,0);
	cd();
	cls;
	for(int i=0;i<3;i++){
		cout<<"\r������. . ."<<i+1;
		Sleep(1000);
	}
	cls;
	wj();
	cout<<"���Ѹ��";
	Sleep(1000);
	cout<<"\n��ʧ��20%����ֵ��\n";
	Sleep(1000);
	cls;
}
void update()/*����*/{
	while(a[5]>=maxexp){
		a[0]++;
		maxhealth=qz(maxhealth*temp);
		a[1]=maxhealth;
		for(int i=2;i<5;i++)a[i]=qz(a[i]*temp);
		a[5]-=maxexp;
		maxexp*=(temp+0.3);
	}
}
int tp(int ab)/*����*/{
	srand((unsigned)time(NULL));
		int ss=a[4]+gwa[4];
		if(rand()%ss<=a[4]&&(tp1==1)){
			cout<<"\n���ܳɹ���\n";
			wait;
			return 1;
		}
		else{
			cout<<"\n����ʧ�ܣ���������ս����\n\n";
			tp1=3;
			wait;
			if(ab==1)vs();
			else return 0;
		}
} 
void gw1()/*��ʾ��������*/{
	double zt[3];
	for(int i=0;i<3;i++){
		if(gwzthh[i]>0&&gwzthh[i+3]==0)zt[i]=2;
		else if(gwzthh[i]==0&&gwzthh[i+3]>0)zt[i]=0.5;
		else zt[i]=1;
	}
	RB;
	cout<<"-------------------------------------------------------------------------------\n";
	cout<<"["<<t[gwtd]<<"] "<<u[gwmz]<<endl;
	for(int i=0;i<5;i++){
		cout<<s[i]<<":"<<((i>1&&i<5)?qz(gwa[i]*zt[i-2]):gwa[i])<<" ";
		if(i==1)cout<<"\b/"<<gwa[5]<<" ";
	}
	cout<<endl;
    for(int i=0;i<ztzs;i++){
    	if(gwzthh[i]){
    		if(i<3){
    			GREEN;
			}else RED;
			cout<<ztzw[i]<<"["<<gwzthh[i]<<"]\t";
		}
	}
	RB;
	cout<<"\n-------------------------------------------------------------------------------\n\n";
	autocolor;
}
void vs()/*ս��������*/{
	onfight=true;
	hh=1;
	int xz,wj1,gw2,gold,exp,a2=a[2],a3=a[3],a4=a[4],gwpq1=gwa[2],gwpq2=gwa[3],gwpq3=gwa[4];
	double sh,hf;
	fill(gwzthh,gwzthh+8,0);
	cls;
	wj();
	gw1();
	cout<<"ս����ʼ����\n";
	pause;
	cls;
	while(true){
		wj();
		gw1();
		cout<<"��";
		RG;
		cout<<hh;
		autocolor;
		cout<<"�غ�";
		Sleep(500);
		cle;
		cout<<"\r�������ж�:\n[1]����\t[2]����\t[3]����\n";
		xz=getch()-48;
		while(xz>3||xz<1)xz=getch()-48;
		//cout<<xz;
		//pause;
		if(xz==1){
			srand((unsigned)time(NULL));
			wj1=a[4];gw2=gwa[4];
			//�ж�����ǻ�
			if(zthh[2]>0&&zthh[5]==0)wj1=a[4]*2;
			else if(zthh[2]==0&&zthh[5]>0)wj1=a[4]/2;
			else wj1=a[4];
			//�жϵ����ǻ�
			if(gwzthh[2]>0&&gwzthh[5]==0)gw2=gwa[4]*2;
			else if(gwzthh[2]==0&&gwzthh[5]>0)gw2=gwa[4]*2;
			else gw2=gwa[4];
			if(rand()%(wj1+gw2)<=wj1){
				srand((unsigned)time(NULL));
				//�ж���ҹ���
				if(zthh[0]>0&&zthh[3]==0)a2=a[2]*2;
				else if(zthh[0]==0&&zthh[3]>0)a2=a[2]/2;
				else a2=a[2];
				//�жϵ��˷���
				if(gwzthh[1]>0&&gwzthh[4]==0)gwpq2=gwa[3]*2;
				else if(gwzthh[1]==0&&gwzthh[4]>0)gwpq2=gwa[3]/2;
				else gwpq2=gwa[2];
				//double gj=gwa[2]*((100+gwdj-1)/100.0)*v[1];
				sh=a2-a2*gwpq2/(gwpq2*1.0+50)+rand()%10/10.0;//�����˺�ֵ 
				if(rand()%2)sh+=rand()%(int(a[0]/10)+1);
				else sh-=rand()%(int((a[0]+10)/5)+1);
				if(sh<0)sh=0;
				sh=qz(sh);
				gwa[1]-=sh;
				GREEN;
				cout<<"\n��";
				autocolor;
				cout<<"��";
				RED;
				cout<<u[gwmz];
				autocolor;
				cout<<"�����";
				RG;
				cout<<sh;
				autocolor;
				cout<<"���˺���\n";
				Sleep(500);
			}else{
				cout<<endl;
				RED;
				cout<<u[gwmz];
				autocolor;
				cout<<"������";
				GREEN;
				cout<<"��";
				autocolor;
				cout<<"�Ĺ�����\n";
				wait;
			}
		}else if(xz==2){
			if(tp(0))return;
		}
		else{
			cls;
			bb(0);
			if(use1)continue;
		}
		if(gwzthh[6]){
			gwa[1]-=7;
			cout<<endl;
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"�ܶ��ص�Ӱ��ʧȥ��7������ֵ��\n";
			wait;
		}
		if(gwzthh[7]){
			gwa[1]-=10;
			cout<<endl;
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"��ȼ�յ�Ӱ��ʧȥ��10������ֵ��\n";
			wait;
		}
		if(gwa[1]<=0){
			srand((unsigned)time(NULL));
			gold=rand()%(int(a[0]+gwdj+5)+10)+10;
			gold*=1.3;//��� �������� 
			if(rand()%2)gold+=rand()%int(a[0])/2;
			else gold-=rand()%int(a[0])/2;
			if(gwmz==gwgs-1)gold*=(a[0]+1);
			bp[0]+=gold;
			srand((unsigned)time(NULL));
			exp=rand()%(int(a[0]+gwdj+5)+10)+10;
			exp*=2+5;//���鱶������ 
			if(rand()%2)exp+=rand()%int(a[0])/2;
			//else exp-=rand()%int(a[0])/2;
			if(gwmz==gwgs-1)exp*=(a[0]+1);
			a[5]+=exp;
			cd();
			cout<<"\nս��ʤ����";
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"�������ˣ�\n";
			wait;
			cout<<"\n������"<<gold<<"��ҡ�\n";
			wait;
			cout<<"\n������"<<exp<<"�㾭��ֵ��\n";
			wait;
			if(a[5]>=maxexp){
				update();
				cls;
				wj();
				cout<<"\n�����ˣ���\n";
				wait;
				return;
			}
			return;
		}
		srand((unsigned)time(NULL));
		wj1=a[4];gw2=gwa[4];
		//�ж�����ǻ�
		if(zthh[2]>0&&zthh[5]==0)wj1=a[4]*2;
		else if(zthh[2]==0&&zthh[5]>0)wj1=a[4]/2;
		else wj1=a[4];
		//�жϵ����ǻ�
		if(gwzthh[2]>0&&gwzthh[5]==0)gw2=gwa[4]*2;
		else if(gwzthh[2]==0&&gwzthh[5]>0)gw2=gwa[4]*2;
		else gw2=gwa[4];
		if(rand()%(wj1+gw2*2)<=gw2*2){
			//�жϹ��﹥����
			if(gwzthh[0]>0&&gwzthh[3]==0)gwpq1=gwa[2]*2;
			else if(gwzthh[0]==0&&gwzthh[3]>0)gwpq1=gwa[2]/2;
			else gwpq1=gwa[2];
			//�ж���ҷ�����
			if(zthh[1]>0&&zthh[4]==0)a2=a[2]*2;
			else if(zthh[1]==0&&zthh[4]>0)a2=a[2]/2;
			else a2=a[2];
			//�����˺� 
			sh=gwpq1-gwpq1*a2/(a2*1.0+50)+rand()%10/10.0;
			if(rand()%2)sh+=rand()%(int((gwa[0]+10)/5+1));
			else sh-=rand()%(int((gwa[0]+10)/5+1));
			if(sh<0)sh=0;
			sh=qz(sh);
			a[1]-=sh;
			cout<<endl;
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"��";
			GREEN;
			cout<<"��";
			autocolor;
			cout<<"�����";
			RB;
			cout<<sh;
			autocolor;
			cout<<"���˺���\n";
			wait;
			if(zthh[6]){
					a[1]-=7;
					GREEN;
					cout<<"\n��";
					autocolor;
					cout<<"�ܶ��ص�Ӱ��ʧȥ��7������ֵ��\n";
					wait;
				}
				if(zthh[7]){
					a[1]-=10;
					GREEN;
					cout<<"\n��";
					autocolor;
					cout<<"��ȼ�յ�Ӱ��ʧȥ��10������ֵ��\n";
					wait;
				}
			if(a[1]<=0){
				RED;
				cout<<"\n�㱻�����ˣ�\n\n";
				autocolor;
				wait;
				fh();
				return;
			}
		}else{
			GREEN;
			cout<<"\n��";
			autocolor;
			cout<<"������";
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"�Ĺ�����\n";
			wait;
		}
		if(tp1>1)tp1--;
  		cls;
  		hh++;
  		for(int i=0;i<ztzs;i++){
  			if(zthh[i])zthh[i]--;
  			if(gwzthh[i])gwzthh[i]--;
		}
	}
}
void guaiwu()/*�����ȡ���ﺯ��*/{
	int sf;
	tp1=1;
	fill(gwzthh,gwzthh+8,0);
	fill(gwa,gwa+6,0);
	fill(v,v+4,1);
	srand(time(NULL));
	gwtd=rand()%9,gwmz=rand()%(gwgs-1),gwdj=a[0]+rand()%3;
	if(gwtd>4)v[gwtd-5]=1.25;
	else if(gwtd<4)v[gwtd]=0.75;
	gwa[5]=gw[gwmz][0];
	for(int i=1;i<gwdj;i++)gwa[5]*=temp;
	gwa[5]*=v[0];
	gwa[0]=gwdj;gwa[1]=gwa[5];
	for(int i=2;i<5;i++){
		gwa[i]=gw[gwmz][i-1];
		for(int j=1;j<gwdj;j++)gwa[i]*=temp;
		gwa[i]*=v[i-1];
	}
	for(int i=0;i<6;i++)gwa[i]=qz(gwa[i]);
	wj();
	gw1();
	cout<<"��Ҫ����ս����\n[1]��\t[2]��\n";
	sf=getch()-48;
	while(sf>2||sf<1)sf=getch()-48;
	cout<<endl;
	if(sf==1)vs();
	else tp(1);
	cls;
}
void bx(int lx)/*�����¼�*/{
	int sf,gs;
	cout<<"\n��Ҫ��������??\n[1]��\t[2]�뿪\n";
	sf=getch()-48;
	while(sf>2||sf<1)sf=getch()-48;
	if(sf==1){
		cls;
		cout<<"����˱���\n";
		Sleep(1000);
		srand((unsigned)time(NULL));
		int rand1=rand()%6;
		//rand1=0;/*����*/ 
		if(rand1>1){
			srand((unsigned)time(NULL));
			sf=rand()%12;
			srand((unsigned)time(NULL));
			if(sf==0)gs=rand()%20+(lx+1)*10;
			else gs=rand()%(lx+1)+1;
			cout<<"\n������װ�� "<<w[sf]<<"*"<<gs<<endl;
			bp[sf]+=gs;
			Sleep(1000);
			cout<<"\n��ȡ�������������Ʒ���ﳤ��ȥ��\n";
			Sleep(1000);
			cls;
			return;
		}
		else{
			RED;
			cout<<"\n������������䣡\n";
			Sleep(1000);
			srand((unsigned)time(NULL));
			int rand1=rand()%2;
			//rand1=1;/*����*/ 
			switch(rand1){
				case 0:{
					srand((unsigned)time(NULL));
					int sh/*��ը�˺�*/=20+rand()%int(maxhealth)/2;
					RED;
					cout<<"\n������װ��һ��ը��������򿪱���ʱ���������ˣ�\n";
					Sleep(1000);
					cout<<"\n�ܱ�ը��Ӱ����ʧȥ��"<<sh<<"������ֵ��\n";
					a[1]-=sh;
					if(a[1]<=0){
						Sleep(1000);
						RED;
						cout<<"\n�㱻ը���ˣ�\n";
						Sleep(1000);
						autocolor;
						cls;
						fh();
					}
					else{
						Sleep(1000);
						pause;
					}
					break;
				}
				case 1:{
					srand((unsigned)time(NULL));
					RED;
					cout<<"\n����һ������֣�\n";
					autocolor;
					wait;
					fill(gwzthh,gwzthh+8,0);
					fill(gwa,gwa+6,0);
					fill(v,v+4,1);
					srand((unsigned)time(NULL));
					gwtd=rand()%9,gwmz=7,gwdj=a[0]+rand()%3;
					if(gwtd>4)v[gwtd-5]=1.25;
					else if(gwtd<4)v[gwtd]=0.75;
					gwa[5]=gw[gwmz][0];
					for(int i=1;i<gwdj;i++)gwa[5]*=temp;
					gwa[5]*=v[0];
					gwa[0]=gwdj;gwa[1]=gwa[5];
					for(int i=2;i<5;i++){
						gwa[i]=gw[gwmz][i-1];
						for(int j=1;j<gwdj;j++)gwa[i]*=temp;
						gwa[i]*=v[i-1];
					}
					for(int i=0;i<6;i++)gwa[i]=qz(gwa[i]);
					cls;
					vs();
					break;
				}
			}
		}
	}else{
		cout<<"\n���뿪�˱��䡣\n";
		pause;
	}
	cls;
}
void sdxs(int gs,int item[],int fh)/*��ʾ�̵���Ʒ*/{
	cls;
	GB;
	cout<<"-------------------------------------------------------------------------------\n\t\t\t\t    �̵�";
	RG;
	cout<<"\t\t\t��ң�"<<bp[0];
	GB;
	cout<<"\n-------------------------------------------------------------------------------\n";
	cout<<"���        ����       �۸�\n-------------------------------------------------------------------------------\n";
	if(fh)cout<<"[0]            �뿪\n";
	for(int i=0;i<gs;i++){
		cout<<"["<<i+1<<"] ";
		int ii=i,len=1;
		while(ii/=10)len++;
		for(int j=0;j<(8-w[item[i]].length()/2)*2-len;j++)cout<<" ";
		cout<<w[item[i]]<<"\t";
		RG;
		cout<<buyprice[item[i]];
		GB;
		cout<<endl;
	}
	cout<<"-------------------------------------------------------------------------------\n";
	autocolor;
}
void shop(int gs,int item[])/*�̵�������*/{
	int xz,bh;
	sdxs(gs,item,0);
	cle;
	cout<<"��Ҫ������Ʒ��\n[1]����\t[2]�뿪\n";
	xz=getch()-48;
	while(xz>2||xz<1)xz=getch()-48;
	cls;
	if(xz==1){
		while(1){
			sdxs(gs,item,1);
			cle;
			cout<<"������Ҫ�������Ʒ��ţ�";
			bh=getch()-48;
			while(bh<0||bh>gs)bh=getch()-48;
			if(bh==0)return;
			else{
				if(buyprice[item[bh-1]]>bp[0]){
					cout<<"\n\nûǮ��������(�á㧥��;)��\n";
					wait; 
					continue;
				}else{
					cout<<"\n\n��Ҫ����"<<w[item[bh-1]]<<"��\t�۸�";
					RG;
					cout<<buyprice[item[bh-1]];
					autocolor;
					cout<<"\n[1]��\t[2]��\n";
					xz=getch()-48;
					while(xz<1||xz>2)xz=getch()-48;
					if(xz==1){
						bp[0]-=buyprice[item[bh-1]];
						bp[item[bh-1]]++;
						cout<<"\n�㹺����"<<w[item[bh-1]]<<"��"<<endl;
						Sleep(1000);
						for(int i=bh-1;i<gs-1;i++)item[i]=item[i+1];
						gs--;
						item[gs]=0;
						continue;
					}
				}
			}
		}
	}
}
void shijian()/*�����¼�*/{
	cls;
	srand(time(NULL));
	int rand1=rand()%3;
	//rand1=2;/*������*/
	if(rand1<2){
		GB;
		cout<<"�㿴��ǰ����һ��Ȫˮ��\n";
		autocolor;
		pause;
		GB;
		cout<<"\n���߹�ȥ������һ��Ȫˮ����ʱ���þ�����ʢ��\n";
		autocolor;
		pause;
		GREEN;
		double h=rand()%(int(maxhealth/5))+rand()%10+5;
		if(h>maxhealth-a[1])h=maxhealth-a[1];
		a[1]+=h;
		cout<<"\n��ظ���"<<h<<"��Ѫ��!\n";
		autocolor;
		pause;
		cls;
	}
	else{
		string bp1,bp4,bp5,bp6;
		int b1=bp[1],b4=bp[4],b5=bp[5],b6=bp[6];
		if(b1==0)bp1="0";
		if(b4==0)bp4="0";
		if(b5==0)bp5="0";
		if(b6==0)bp6="0";
		while(b1>0){
			bp1=char(b1%10+48)+bp1;
			b1/=10;
		}
		while(b4>0){
			bp4=char(b4%10+48)+bp4;
			b4/=10;
		}
		while(b5>0){
			bp5=char(b5%10+48)+bp5;
			b5/=10;
		}
		while(b6>0){
			bp6=char(b6%10+48)+bp6;
			b6/=10;
		}
		int sf;
		GB;
		srand(time(NULL)+666);
		const int g=4; 
		int rand2=rand()%g;
		//rand2=3;/*������*/
		string s1[g]={"�㿴��ǰ����һ�����˵�ʿ����","ǰ������һ���ߴ����ʿ��","һ��СŮ�����߱߿ޡ�","һ������������������ڼ��ſڡ�"},
				s2[g]={"ʿ�����ұ�һ����ʬ�����ˣ����ܸ���һƿ����ҩˮ��","��ʿ����Ҫ�ϳ�ɱ�У������һƿ��ҩˮ����","555555555~�ҿ����ֿ�����~���ܸ���һƿ����ҩˮ�𣿲�Ȼ�һᱻ�����δ򱬵ģ�",
						"���꣺�����Ҫ�����ˣ��Һ��¿����������ܸ���һƿ����ҩˮ��"},
				s3[g]={"�Ƿ�Ҫ��������ҩˮ������������ "+bp1+" ƿ����ҩˮ��\n[1]��\t[2]��","�Ƿ�Ҫ������ҩˮ������������ "+bp4+" ƿ��ҩˮ��\n[1]��\t[2]��",
						"�Ƿ�Ҫ��������ҩˮ������������ "+bp5+" ƿ����ҩˮ��\n[1]��\t[2]��","�Ƿ�Ҫ��������ҩˮ������������ "+bp6+" ƿ����ҩˮ��\n[1]��\t[2]��"},
				s4[g]={"ʿ��","��ʿ","СŮ��","����"},s5[g]={"����","��","����","����"};
		int i[g]={1,4,5,6};
		GB;
		cout<<s1[rand2]<<endl;
		autocolor;
		pause;
		GB;
		cout<<s2[rand2]<<endl;
		autocolor;
		pause;
		GB;
		cout<<s3[rand2]<<endl<<endl;
		autocolor;
		sf=getch()-48;
		while(cin.fail()||sf<1||sf>2)sf=getch()-48;
		cls;
		if(sf==1){
			if(bp[i[rand2]]==0){
				autocolor;
				cout<<"��û���㹻��"<<s5[rand2]<<"ҩˮ��\n";
				pause;
				return;
			}
			bp[i[rand2]]--;
			int h=(rand()%2-1)*(rand()%int(a[0])+10)+50;
			bp[0]+=h;
			GB;
			cout<<"�㽫һƿ"<<s5[rand2]<<"ҩˮ�ݸ���"<<s4[rand2]<<"��"<<endl;
			autocolor;
			pause;
			GB;
			cout<<s4[rand2]<<":̫��л���ˣ�����һ��㱨�꣬��Ц�ɡ�\n";
			autocolor;
			pause;
			RG;
			cout<<"������ "<<h<<" ��ң�\n";
			autocolor;
			pause;
		}
		else{
			GB;
			cout<<"����û�����"<<s4[rand2]<<",�߿��ˡ�\n";
			autocolor;
			pause;
		}
	}
}
void aa()/*��ȡ�¼�������*/{
	while(true){
		memset(zthh,0,sizeof(zthh)); 
		cls;//���� 
		onfight=false;
		wj();//������� 
		cout<<"�������ж���\n[1]̽��\t[2]����\t[3]�˳���Ϸ [4]�л��浵\n";
		cle;//
		int xd=getch()-48;//�����Ϊ�ַ����ͣ���48�Ա�ֱ�������������ж� 
		while(xd<1||xd>4)xd=getch()-48;//�������Ҵ򣨲�����Ч�ַ�����������룬ֱ����Ч 
		if(xd==1){
			cls;//���� 
			cout<<"����̽����";
			for(int i=0;i<3;i++){
				cout<<".";//���� 
				Sleep(500);
			}
			cls;
			srand((unsigned)time(NULL));
			int rand1=rand()%10;
			//rand1=5;/*������*/
			//cin>>rand1;/*������*/ 
			if(rand1<4){//ʮ��֮��0.1.2.3 
				RED;
				cout<<"һֻ����������Ϯ����\n\n";
				autocolor;
				pause;
				cls;
				srand((unsigned)time(NULL));
				guaiwu();//���ﺯ�� 
				cls;
			}//ʮ��֮��4.5 
			else if(rand1<6){//������3ľ2��1�� 
				srand((unsigned)time(NULL));
				int lx/*��������*/=rand()%6;//�����ȡ 
				RG;
				cout<<"����"<<x[rand()%6]<<"�����ӣ�\n";
				autocolor;
				pause;
				bx(lx);//���亯��������Ϊ���ӵ����� 
			}
			else if(rand1<8){//ʮ��֮��6.7
				shijian();//����¼� 
			}
			else{//ʮ��֮��8.9
				GB;
				cout<<"��������һ���̵ꡣ\n";
				autocolor;
				pause;
				int gs;
				cls;
				srand((unsigned)time(NULL));
				gs=rand()%3+3;
				int item[gs],allitem[bpl-1];
				memset(item,0,sizeof(item));
				for(int i=0;i<bpl-1;i++)allitem[i]=i+1;
				for(int i=0;i<bpl-1;i++){
					srand(time(NULL)+rand()%10*rand());
					int j=rand()%(bpl-1);
					swap(allitem[i],allitem[j]);
				}
				for(int i=0;i<gs;i++)item[i]=allitem[i];
				shop(gs,item);
			}
			cd();//�����̵꺯�� 
		}
		else if (xd == 2) {//���뱳�� 
			cls;
			bb(0);
			cls;
		}
		else if (xd == 3) { //�˳���Ϸ 
			RED;
			cout << endl;
			cout << "���Ҫ������" << endl;
			RG;
			cout << "[0]��ʹ�뿪\t";
			GREEN;
			cout << "[1]����һ��" << endl;
			xd = getch() - '0';
			while (xd < 0 || xd > 1) xd = getch() - '0';
			autocolor;
			cout << endl;
			if (!xd) {
				cout << "�ѱ���浵����ӭ�´μ�����" << endl;
				pause;
				return;
			} else {
				cout << "��л���֧�֣�" << endl;
				wait;
				cls;
			}
		}
		else {
			GREEN;
			cout << "\n�ѱ�����Ϸ���ȣ�\n\n";
			autocolor;
			pause; 
			dd(0);
		}
	}
}
void wms()/*��ʾ����(��'��'��)*/
{
	RED;
	cout<<"С��";
	GREEN;
	cout<<"��";
	RG;
	cout<<"����";
	autocolor;
}
void bang()//���а� 
{
	RG;
	cout<<"-------------------------------------------------------------------------------\n";
	GB;
	cout<<"������а�"<<endl;
	cout<<"[1] �û�����admin �ȼ���100"<<endl;
	cout<<"[2] �û����������� �ȼ���99"<<endl;
	cout<<"[3] �û���: ������ �ȼ���98"<<endl;
}
void setnew()// �������� 
{
	cout<<endl;
	RG;
	cout<<"beta1.0.1��������"<<endl;
	cout<<"1.���ӱ����" <<endl;
	cout<<"2.�޸���Ȫˮ�ָ�����ֵ�����bug" <<endl;
	cout<<"3.�������а�" <<endl;
	cout<<"4.���ӱ������֣����ڲ��ԣ�����ɫ" <<endl;
	cout<<"5.ѡ��ѡ����Ҳ��������ذ��س���\(^o^)/~" <<endl;
	cout<<"6.�޸�������¼��Ĵ���" <<endl;
	cout<<"7.Ӧ�ڲ����Ҫ���˵��ص����˶���ƿ���˺�ֵ" <<endl;
	cout<<"8.�����˾���ͽ�ҵĵ���ֵ��������Ҳ�����Ҹ�����" <<endl;
	cout<<"9.������̽����ս���ȴ�ʱ�䣬ʱ����ǽ�Ǯ��" <<endl;
	cout<<"10.�޸��˴浵���ļ���ʽ���Դ浵�����˼򵥵ļ��ܣ����׿ɳܣ���" <<endl;
	GB;
	cout<<endl; 
	cout<<"beta1.0.2�������ݣ�����棩����������"<<endl;
	cout<<"11.�޸��˽�Ǯ�;���ʵ�ʻ����������ʾ���������һ�µ�bug"<<endl;
	cout<<"12.�������˳���Ϸѡ�������ȫ���̲�������\n";
	cout<<"13.���غ͹̶��˴浵·����������EXE���ƶ���Ҫ�ֶ��浵���ž�����\n";
	cout<<"14.�������л��浵ѡ������ظ��˳�������Ϸ\n";//�ֳ���æ
	cout<<"15.Ȼ�컹�Ƿ�������������Ȼ���أ������ּ��ذѴ浵�����桤�������£�"<<endl; 
	cout<<"16.Ϊ�������ҵ������������Ƴ��˹ٷ��޸���QWQ(���Լ�QQ��ȡ)"<<endl; 
	
}
void broad()//��ʾ�� 
{
	cout<<"\n�ر���л��201�����,105 �½���,201��껡�201�ν�������л������"<<endl;
	cout<<"����QQ:1030082097"<<endl; 
	cout<<"�������ֳ��˵����⣬�Լ��ֶ����Ű�~^_^"<<endl; 
} 
BOOL SetConsoleColor(WORD wAttributes)  
{  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
    if (hConsole == INVALID_HANDLE_VALUE)  
        return FALSE;  
  
    return SetConsoleTextAttribute(hConsole, wAttributes);  
}  
int main()//������ 
{  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	setwindow();
	CreateDirectory("C://players",NULL);
	cls;//���� 
	RG; //����ɫ 
	cout<<"-------------------------------------------------------------------------------\n";
	GB;//����ɫ 
	cout<<"��ӭ����̰�����£��ޣ���\n";
	autocolor;
	cout<<"�汾:"<<version<<"     �����ߣ�";
	wms();//��ʾ���� 
	broad();//��ʾ 
	bang();//���� 
	setnew();//������Ϣ 
	RG;//����ɫ
	cout<<"\n-------------------------------------------------------------------------------\n";
	autocolor;
	pause;//�ȴ� 
	cls;//���� 
	dd(0);//���� 
	wj();//������� 
	pause;//�ȴ� 
	cls;//���� 
	aa();//��ȡ�¼�������
}
/*�����ʼǣ�
getch();#include "conio.h"
*/ 
//system("C:\\Users\\zzm10\\Desktop\\beta1.0\\1.wav");//playsound�����ò��ˣ�������պ�һ�� 
//ʹ��rand���������������������rand����������ͷ�ļ���<cstdlib>�У�    ����srand 
