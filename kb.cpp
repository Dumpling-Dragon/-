//兄弟，存档我真的不是很会，这块你来实现吧 
//建议加个音乐？ 
#include"kb.h"
#define gwgs/*怪物种数*/ 8
#define ztzs/*状态种数*/ 8
#define bpl/*背包物品种数*/ 12
using namespace std;
string /*版本*/version="1.0.2",title="坑壁的大冒险"+version,/*所有玩家名称*/players[1000],/*玩家的完整名称（带拓展名）*/players1[1000];
int use1=0,/*玩家个数*/nop,/*回合*/hh;
//玩家 
string /*玩家名称*/name,/*玩家属性名称*/s[]={"等级","血量","攻击","防御","智慧","经验值"};
double /*玩家属性*/a[6],/*升级点数*/temp=1.2,/*最大生命值*/maxhealth,/*最大经验值*/maxexp;
//怪物 
string /*怪物特征*/t[]={"脆皮","体弱","破烂","智障","普通","肉盾","刺客","神装","学霸"},/*怪物名字*/u[gwgs]={"僵尸","骷髅","亡灵法师","邪恶灵魂","巨蟹","精灵","哥布林","宝箱怪"};
double /*所有怪物初始属性*/gw[gwgs][4]={/*僵尸*/{50,5,5,5},/*骷髅*/{35,8,5,5},/*亡灵法师*/{30,10,3,10},/*邪恶灵魂*/{25,10,0,15},/*巨蟹*/{100,5,20,3},/*精灵*/{50,5,5,10},/*哥布林*/{40,8,5,10},
										/*宝箱怪*/{80,8,8,5}},
		/*状态降低属性*/v[]={1,1,1,1},/*当前怪物属性*/gwa[6];
int /*怪物特点序号*/gwtd,/*怪物名字序号*/gwmz,/*怪物等级序号*/gwdj,/*逃跑值*/tp1;	
//背包&宝箱&商店 
string /*背包物品名称*/w[]={"金币","治疗药水","强效治疗药水","超级治疗药水","狂暴药水","护甲药水","机智药水","虚弱药水","破甲药水","脑残药水","毒气弹","燃烧瓶"},
		/*背包物品介绍*/js[12]={"坑壁大冒险的通用货币","回复10点生命值","回复20点生命值","回复30点生命值","攻击翻倍，持续5回合","防御翻倍，持续5回合","智慧翻倍，持续5回合",
								"敌人攻击减半，持续5回合","敌人防御减半，持续5回合","敌人智慧减半，持续5回合","使敌人持续6回合受到5点毒素伤害","使敌人持续3回合受到10点燃烧伤害"},
		/*箱子种类*/x[]={"木","木","木","铁","铁","金"};
int /*背包*/bp[bpl],/*购买价格*/buyprice[bpl]={0,10,20,30,50,50,50,50,50,50,50,50},/*出售价格*/sellprice[bpl]={0,5,10,15,20,20,20,20,20,20,20,20};

//状态 
string /*状态名字*/ztzw[ztzs]={"狂暴","护甲","机智","虚弱","破甲","脑残","中毒","燃烧"};/*玩家状态回合*/int zthh[ztzs],/*怪物状态回合*/gwzthh[ztzs];

bool /*物品是否能够使用*/okuse[12]={0,1,1,1,1,1,1,1,1,1,1,1},canuse[bpl]={0,1,1,1,0,0,0,0,0,0,0,0},/*是否在战斗中*/onfight=false;
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
void findfiles()/*查找文件中的存档*/{
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
double qz(double a)/*保留一位小数*/{
	return int((a+0.05)*10)/10.0;
}
void showcd(int page,int pages,bool isde){
	for(int i=0;i<9&&i+page*9<nop;i++)cout<<"["<<i+1<<"]\t"<<players[i+page*9]<<endl;
	if(page<pages)cout<<"[+]\t下一页\n";
	if(page)cout<<"[-]\t上一页\n";
	if(isde){
		cout<<"[n]\t创建新存档\n";
		if(nop)cout<<"[d]\t删除存档\n";
	}
	cout<<"-------------------------------------------------------------------------------\n\n";
}
void newcd(int page,int pages){
	ofstream fout;
	string cdname;
	while(true){
		cls;
		cout<<"请选择存档：\n-------------------------------------------------------------------------------\n";
		showcd(page,pages,true);
		cle;
		cout<<"请输入新存档名，直接按回车键撤销：\n";
		getline(cin,cdname);
		int aaa=0;
		if(cdname==""){
			dd(page);
			return;
		}
		for(int i=0;i<cdname.length();i++){
			if(cdname[i]>=32&&cdname[i]<=47)aaa++;//检测非法字符 
		}
		if(aaa){
			cout<<"提示：名称中含有非法字符，请重新输入。\n";
			pause;
			continue;
		}
  		aaa=0;
  		for(int i=0;i<nop;i++)
  			if(cdname==players[i])aaa++;
		if(aaa){
			cout<<"\n存档名重复，请删除重名存档或更改新存档名\n";
			pause;
			continue;
		}
		else break;
	}
	fout.close();
	fout.open(("C://players//"+cdname+".kbm").data(),ios::out);
	if(fout.good()){
		fout<<cdname<<"\n124 8836 916 916 916 36 100 100\n";
		fill(bp,bp+bpl,0);//fill函数的作用是：将一个区间的元素都赋予val值。函数参数：fill(vec.begin(), vec.end(), val); val为将要替换的值
		for(int i=0;i<bpl;i++)fout<<bp[i]*88+36<<" ";//初始化背包内容 
		fout.close();
		cout<<"\n成功创建存档！\n";
	}
	else{
		RED;
		cout<<"错误：存档创建失败！\n";
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
void deletecd(int page)/*删除存档*/{
	int pages=nop/10,bh;
	cls;
	cout<<"请输入要删除的存档编号：\n-------------------------------------------------------------------------------\n[0]\t返回\n";
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
		cout<<"请输入要删除的存档编号：\n-------------------------------------------------------------------------------\n[0]\t返回\n";
		showcd(page,pages,false);
		cout<<"你确定要删除 "<<players[page*9+bh-49]<<" 吗？此操作无法恢复。\n[1]是\t[2]否\n";
		xz=getch()-48;
		while(xz<1||xz>2)xz=getch()-48;
		if(xz==1){
			for(int i=0;i<10;i++){
				cls;
				cout<<"请按下10次 1 以删除存档,按其他键返回： "<<i;
				if(getch()-48!=1){
					dd(page);
					return;
				}
			}
			cls; 
			bool re=remove(("C://players//"+players1[page*9+bh-49]).data());
			if(!re)cout<<"成功删除存档！\n";
			else{
				RED;
				cout<<"错误：删除存档失败！\n";
				autocolor;
			}
			pause;
		}
		cls;
		dd(page);
	}
}
void dd(int page)/*读档*/{
	nop=0;
	findfiles();
	cls;
	double f;
	int j,cd,bh,pages=nop/10;
	string path,cdname;
	ifstream fin;
	cout<<"请选择存档：\n-------------------------------------------------------------------------------\n";
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
			cout<<"错误：存档读取失败！\n";
			autocolor;
			pause;
			dd(page);
			return;
		}
		getline(fin,name);
		if(name==""){
			cls;
			RED;
			cout<<"存档读取错误！\n错误名称：玩家名读取错误！\n";
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
void cd()/*存档*/{
	ofstream fout(("C://players//"+name+".kbm").data(),ios::out);//写入 
	if(fout.good()){//如果存档正常 
		fout<<name<<endl;
		for(int i=0;i<6;i++)fout<<a[i]*88+36<<" ";//玩家参数  
		fout<<endl<<maxhealth<<" "<<maxexp<<endl;//最大生命值，最大经验值 
		for(int i=0;i<bpl;i++)fout<<bp[i]*88+36<<" ";//背包物品存档 
	}
	else{
		RED;
		cls;
		cout<<"错误：存档保存失败！\n";
		pause;
		exit(1);//退出 
	}
}
void wj()/*显示玩家属性*/{
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
int use(int sf)/*使用物品*/{
	int xz;
	if(!canuse[sf]&&!onfight){
		cout<<"\n你不能在这里使用"<<w[sf]<<"。";
		wait;
		cls;
		return 1;
	}
	else if(okuse[sf]){
		cle;
		cout<<"\n你要使用"<<w[sf]<<"吗？\n[1]是\t[2]否\n";
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
				cout<<"\n你";
				autocolor;
				cout<<"使用了 "<<w[sf]<<" ,并回复了 "<<sf*10<<" 点生命值。\n";
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
					cout<<"\n你";
					autocolor;
					cout<<"使用了 "<<w[sf]<<" ,并获得了 ";
					GREEN;
					cout<<ztzw[sf-4];
					autocolor;
					cout<<" 效果。\n";
				}
				else cout<<"\n你不能在这里使用"<<w[sf]<<"。"<<endl;
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
					cout<<"你";
					autocolor;
					cout<<"向";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"丢了一瓶 "<<w[sf]<<" ,并使";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"获得了";
					RED;
					cout<<ztzw[sf-4];
					autocolor;
					cout<<"效果。\n";
				}
				else cout<<"你不能在这里使用"<<w[sf]<<"。"<<endl;
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
					cout<<"你";
					autocolor;
					cout<<"向";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"丢了一个毒气弹。\n";
					wait;
					cout<<"\n";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"中毒了！\n";
					wait;
				}
				else cout<<"你不能在这里使用"<<w[sf]<<"。"<<endl;
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
					cout<<"你";
					autocolor;
					cout<<"向";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"丢了一个燃烧瓶。\n";
					pause;
					cout<<"\n";
					RED;
					cout<<u[gwmz];
					autocolor;
					cout<<"烧起来了！\n";
					wait;
				}
				else cout<<"你不能在这里使用"<<w[sf]<<"。"<<endl;
			}
			cd();
			return 0;
		}
	}else{
		cout<<"\n你不能使用"<<w[sf]<<"。"<<endl;
		wait;
		cle;
	}
	cls;
	return 1;
}
int bbxs(int ii,int bp1[12],int page,int pages)/*显示背包中的物品*/{
	RG;
	cout<<"-------------------------------------------------------------------------------\n\t\t\t\t背包\n-------------------------------------------------------------------------------\n";
	cout<<"-------------------------------------------------------------------------------编号           名称    数量        描述\n-------------------------------------------------------------------------------\n";
	autocolor;
	cout<<"[0]            返回\n";
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
	//这个有点问题，你改一下 
	if(page){
		cout<<"[-]        上一页\n";
		ii++;
	}
	if(page<pages){
		cout<<"[+]        下一页\n";
		ii++;
	}
	RG;
	cout<<"-------------------------------------------------------------------------------\n\n";
	autocolor;
	return ii;
}
void bb(int nowpage)/*背包主函数*/{
	int i=0,items,pages=0;
	for(int j=0;j<bpl;j++)if(bp[j])pages++;
	pages/=10;
	//i+=pages*10;
	int ii=0,bp1[12],sf,len;
	fill(bp1,bp1+12,-1);
	use1=0;
	ii=bbxs(1,bp1,nowpage,pages);
	cle;
	cout<<"你要使用什么物品？\n";
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
void fh()/*复活*/{
	tp1=0;
	a[1]=maxhealth;
	a[5]-=int(a[5]*0.2);
	fill(zthh,zthh+8,0);
	fill(gwzthh,gwzthh+8,0);
	cd();
	cls;
	for(int i=0;i<3;i++){
		cout<<"\r复活中. . ."<<i+1;
		Sleep(1000);
	}
	cls;
	wj();
	cout<<"你已复活！";
	Sleep(1000);
	cout<<"\n损失了20%经验值。\n";
	Sleep(1000);
	cls;
}
void update()/*升级*/{
	while(a[5]>=maxexp){
		a[0]++;
		maxhealth=qz(maxhealth*temp);
		a[1]=maxhealth;
		for(int i=2;i<5;i++)a[i]=qz(a[i]*temp);
		a[5]-=maxexp;
		maxexp*=(temp+0.3);
	}
}
int tp(int ab)/*逃跑*/{
	srand((unsigned)time(NULL));
		int ss=a[4]+gwa[4];
		if(rand()%ss<=a[4]&&(tp1==1)){
			cout<<"\n逃跑成功！\n";
			wait;
			return 1;
		}
		else{
			cout<<"\n逃跑失败，你必须和它战斗。\n\n";
			tp1=3;
			wait;
			if(ab==1)vs();
			else return 0;
		}
} 
void gw1()/*显示怪物属性*/{
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
void vs()/*战斗主函数*/{
	onfight=true;
	hh=1;
	int xz,wj1,gw2,gold,exp,a2=a[2],a3=a[3],a4=a[4],gwpq1=gwa[2],gwpq2=gwa[3],gwpq3=gwa[4];
	double sh,hf;
	fill(gwzthh,gwzthh+8,0);
	cls;
	wj();
	gw1();
	cout<<"战斗开始！！\n";
	pause;
	cls;
	while(true){
		wj();
		gw1();
		cout<<"第";
		RG;
		cout<<hh;
		autocolor;
		cout<<"回合";
		Sleep(500);
		cle;
		cout<<"\r请做出行动:\n[1]攻击\t[2]逃跑\t[3]背包\n";
		xz=getch()-48;
		while(xz>3||xz<1)xz=getch()-48;
		//cout<<xz;
		//pause;
		if(xz==1){
			srand((unsigned)time(NULL));
			wj1=a[4];gw2=gwa[4];
			//判断玩家智慧
			if(zthh[2]>0&&zthh[5]==0)wj1=a[4]*2;
			else if(zthh[2]==0&&zthh[5]>0)wj1=a[4]/2;
			else wj1=a[4];
			//判断敌人智慧
			if(gwzthh[2]>0&&gwzthh[5]==0)gw2=gwa[4]*2;
			else if(gwzthh[2]==0&&gwzthh[5]>0)gw2=gwa[4]*2;
			else gw2=gwa[4];
			if(rand()%(wj1+gw2)<=wj1){
				srand((unsigned)time(NULL));
				//判断玩家攻击
				if(zthh[0]>0&&zthh[3]==0)a2=a[2]*2;
				else if(zthh[0]==0&&zthh[3]>0)a2=a[2]/2;
				else a2=a[2];
				//判断敌人防御
				if(gwzthh[1]>0&&gwzthh[4]==0)gwpq2=gwa[3]*2;
				else if(gwzthh[1]==0&&gwzthh[4]>0)gwpq2=gwa[3]/2;
				else gwpq2=gwa[2];
				//double gj=gwa[2]*((100+gwdj-1)/100.0)*v[1];
				sh=a2-a2*gwpq2/(gwpq2*1.0+50)+rand()%10/10.0;//计算伤害值 
				if(rand()%2)sh+=rand()%(int(a[0]/10)+1);
				else sh-=rand()%(int((a[0]+10)/5)+1);
				if(sh<0)sh=0;
				sh=qz(sh);
				gwa[1]-=sh;
				GREEN;
				cout<<"\n你";
				autocolor;
				cout<<"对";
				RED;
				cout<<u[gwmz];
				autocolor;
				cout<<"造成了";
				RG;
				cout<<sh;
				autocolor;
				cout<<"点伤害。\n";
				Sleep(500);
			}else{
				cout<<endl;
				RED;
				cout<<u[gwmz];
				autocolor;
				cout<<"闪避了";
				GREEN;
				cout<<"你";
				autocolor;
				cout<<"的攻击！\n";
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
			cout<<"受毒素的影响失去了7点生命值。\n";
			wait;
		}
		if(gwzthh[7]){
			gwa[1]-=10;
			cout<<endl;
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"受燃烧的影响失去了10点生命值。\n";
			wait;
		}
		if(gwa[1]<=0){
			srand((unsigned)time(NULL));
			gold=rand()%(int(a[0]+gwdj+5)+10)+10;
			gold*=1.3;//金币 倍数控制 
			if(rand()%2)gold+=rand()%int(a[0])/2;
			else gold-=rand()%int(a[0])/2;
			if(gwmz==gwgs-1)gold*=(a[0]+1);
			bp[0]+=gold;
			srand((unsigned)time(NULL));
			exp=rand()%(int(a[0]+gwdj+5)+10)+10;
			exp*=2+5;//经验倍数控制 
			if(rand()%2)exp+=rand()%int(a[0])/2;
			//else exp-=rand()%int(a[0])/2;
			if(gwmz==gwgs-1)exp*=(a[0]+1);
			a[5]+=exp;
			cd();
			cout<<"\n战斗胜利！";
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"被击败了！\n";
			wait;
			cout<<"\n你获得了"<<gold<<"金币。\n";
			wait;
			cout<<"\n你获得了"<<exp<<"点经验值。\n";
			wait;
			if(a[5]>=maxexp){
				update();
				cls;
				wj();
				cout<<"\n升级了！！\n";
				wait;
				return;
			}
			return;
		}
		srand((unsigned)time(NULL));
		wj1=a[4];gw2=gwa[4];
		//判断玩家智慧
		if(zthh[2]>0&&zthh[5]==0)wj1=a[4]*2;
		else if(zthh[2]==0&&zthh[5]>0)wj1=a[4]/2;
		else wj1=a[4];
		//判断敌人智慧
		if(gwzthh[2]>0&&gwzthh[5]==0)gw2=gwa[4]*2;
		else if(gwzthh[2]==0&&gwzthh[5]>0)gw2=gwa[4]*2;
		else gw2=gwa[4];
		if(rand()%(wj1+gw2*2)<=gw2*2){
			//判断怪物攻击力
			if(gwzthh[0]>0&&gwzthh[3]==0)gwpq1=gwa[2]*2;
			else if(gwzthh[0]==0&&gwzthh[3]>0)gwpq1=gwa[2]/2;
			else gwpq1=gwa[2];
			//判断玩家防御力
			if(zthh[1]>0&&zthh[4]==0)a2=a[2]*2;
			else if(zthh[1]==0&&zthh[4]>0)a2=a[2]/2;
			else a2=a[2];
			//计算伤害 
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
			cout<<"对";
			GREEN;
			cout<<"你";
			autocolor;
			cout<<"造成了";
			RB;
			cout<<sh;
			autocolor;
			cout<<"点伤害。\n";
			wait;
			if(zthh[6]){
					a[1]-=7;
					GREEN;
					cout<<"\n你";
					autocolor;
					cout<<"受毒素的影响失去了7点生命值。\n";
					wait;
				}
				if(zthh[7]){
					a[1]-=10;
					GREEN;
					cout<<"\n你";
					autocolor;
					cout<<"受燃烧的影响失去了10点生命值。\n";
					wait;
				}
			if(a[1]<=0){
				RED;
				cout<<"\n你被击败了！\n\n";
				autocolor;
				wait;
				fh();
				return;
			}
		}else{
			GREEN;
			cout<<"\n你";
			autocolor;
			cout<<"闪避了";
			RED;
			cout<<u[gwmz];
			autocolor;
			cout<<"的攻击！\n";
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
void guaiwu()/*随机抽取怪物函数*/{
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
	cout<<"你要和它战斗吗？\n[1]是\t[2]否\n";
	sf=getch()-48;
	while(sf>2||sf<1)sf=getch()-48;
	cout<<endl;
	if(sf==1)vs();
	else tp(1);
	cls;
}
void bx(int lx)/*宝箱事件*/{
	int sf,gs;
	cout<<"\n你要打开箱子吗??\n[1]打开\t[2]离开\n";
	sf=getch()-48;
	while(sf>2||sf<1)sf=getch()-48;
	if(sf==1){
		cls;
		cout<<"你打开了宝箱\n";
		Sleep(1000);
		srand((unsigned)time(NULL));
		int rand1=rand()%6;
		//rand1=0;/*测试*/ 
		if(rand1>1){
			srand((unsigned)time(NULL));
			sf=rand()%12;
			srand((unsigned)time(NULL));
			if(sf==0)gs=rand()%20+(lx+1)*10;
			else gs=rand()%(lx+1)+1;
			cout<<"\n宝箱里装着 "<<w[sf]<<"*"<<gs<<endl;
			bp[sf]+=gs;
			Sleep(1000);
			cout<<"\n你取走了箱子里的物品，扬长而去。\n";
			Sleep(1000);
			cls;
			return;
		}
		else{
			RED;
			cout<<"\n这个宝箱有诅咒！\n";
			Sleep(1000);
			srand((unsigned)time(NULL));
			int rand1=rand()%2;
			//rand1=1;/*测试*/ 
			switch(rand1){
				case 0:{
					srand((unsigned)time(NULL));
					int sh/*爆炸伤害*/=20+rand()%int(maxhealth)/2;
					RED;
					cout<<"\n宝箱里装着一个炸弹！当你打开宝箱时它被引爆了！\n";
					Sleep(1000);
					cout<<"\n受爆炸的影响你失去了"<<sh<<"点生命值。\n";
					a[1]-=sh;
					if(a[1]<=0){
						Sleep(1000);
						RED;
						cout<<"\n你被炸死了！\n";
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
					cout<<"\n这是一个宝箱怪！\n";
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
		cout<<"\n你离开了宝箱。\n";
		pause;
	}
	cls;
}
void sdxs(int gs,int item[],int fh)/*显示商店物品*/{
	cls;
	GB;
	cout<<"-------------------------------------------------------------------------------\n\t\t\t\t    商店";
	RG;
	cout<<"\t\t\t金币："<<bp[0];
	GB;
	cout<<"\n-------------------------------------------------------------------------------\n";
	cout<<"编号        名称       价格\n-------------------------------------------------------------------------------\n";
	if(fh)cout<<"[0]            离开\n";
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
void shop(int gs,int item[])/*商店主函数*/{
	int xz,bh;
	sdxs(gs,item,0);
	cle;
	cout<<"你要购买物品吗？\n[1]购买\t[2]离开\n";
	xz=getch()-48;
	while(xz>2||xz<1)xz=getch()-48;
	cls;
	if(xz==1){
		while(1){
			sdxs(gs,item,1);
			cle;
			cout<<"请输入要购买的物品编号：";
			bh=getch()-48;
			while(bh<0||bh>gs)bh=getch()-48;
			if(bh==0)return;
			else{
				if(buyprice[item[bh-1]]>bp[0]){
					cout<<"\n\n没钱！！！Σ(っ°Д°;)っ\n";
					wait; 
					continue;
				}else{
					cout<<"\n\n你要购买"<<w[item[bh-1]]<<"吗？\t价格：";
					RG;
					cout<<buyprice[item[bh-1]];
					autocolor;
					cout<<"\n[1]是\t[2]否\n";
					xz=getch()-48;
					while(xz<1||xz>2)xz=getch()-48;
					if(xz==1){
						bp[0]-=buyprice[item[bh-1]];
						bp[item[bh-1]]++;
						cout<<"\n你购买了"<<w[item[bh-1]]<<"。"<<endl;
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
void shijian()/*特殊事件*/{
	cls;
	srand(time(NULL));
	int rand1=rand()%3;
	//rand1=2;/*测试用*/
	if(rand1<2){
		GB;
		cout<<"你看见前方有一眼泉水。\n";
		autocolor;
		pause;
		GB;
		cout<<"\n你走过去，喝了一点泉水，顿时觉得精力旺盛。\n";
		autocolor;
		pause;
		GREEN;
		double h=rand()%(int(maxhealth/5))+rand()%10+5;
		if(h>maxhealth-a[1])h=maxhealth-a[1];
		a[1]+=h;
		cout<<"\n你回复了"<<h<<"点血量!\n";
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
		//rand2=3;/*测试用*/
		string s1[g]={"你看见前面有一个受伤的士兵。","前方跑来一个高大的骑士。","一个小女孩边走边哭。","一个青年忧心忡忡地坐在家门口。"},
				s2[g]={"士兵：我被一个僵尸打伤了，你能给我一瓶治疗药水吗？","骑士：我要上场杀敌！快给我一瓶狂暴药水！！","555555555~我考试又考砸了~你能给我一瓶护甲药水吗？不然我会被我粑粑打爆的！",
						"青年：明天就要考试了，我好怕考不过，你能给我一瓶机智药水吗？"},
				s3[g]={"是否要给他治疗药水？（你现在有 "+bp1+" 瓶治疗药水）\n[1]是\t[2]否","是否要给他狂暴药水？（你现在有 "+bp4+" 瓶狂暴药水）\n[1]是\t[2]否",
						"是否要给他护甲药水？（你现在有 "+bp5+" 瓶护甲药水）\n[1]是\t[2]否","是否要给他机智药水？（你现在有 "+bp6+" 瓶机智药水）\n[1]是\t[2]否"},
				s4[g]={"士兵","骑士","小女孩","青年"},s5[g]={"治疗","狂暴","护甲","机智"};
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
				cout<<"你没有足够的"<<s5[rand2]<<"药水。\n";
				pause;
				return;
			}
			bp[i[rand2]]--;
			int h=(rand()%2-1)*(rand()%int(a[0])+10)+50;
			bp[0]+=h;
			GB;
			cout<<"你将一瓶"<<s5[rand2]<<"药水递给了"<<s4[rand2]<<"。"<<endl;
			autocolor;
			pause;
			GB;
			cout<<s4[rand2]<<":太感谢你了！这是一点点报酬，请笑纳。\n";
			autocolor;
			pause;
			RG;
			cout<<"你获得了 "<<h<<" 金币！\n";
			autocolor;
			pause;
		}
		else{
			GB;
			cout<<"你鸟都没鸟这个"<<s4[rand2]<<",走开了。\n";
			autocolor;
			pause;
		}
	}
}
void aa()/*抽取事件主函数*/{
	while(true){
		memset(zthh,0,sizeof(zthh)); 
		cls;//清屏 
		onfight=false;
		wj();//玩家属性 
		cout<<"请做出行动：\n[1]探索\t[2]背包\t[3]退出游戏 [4]切换存档\n";
		cle;//
		int xd=getch()-48;//读入的为字符类型，减48以便直接用整形数据判断 
		while(xd<1||xd>4)xd=getch()-48;//如何玩家乱打（不是有效字符）则继续输入，直到有效 
		if(xd==1){
			cls;//清屏 
			cout<<"正在探索中";
			for(int i=0;i<3;i++){
				cout<<".";//点点点 
				Sleep(500);
			}
			cls;
			srand((unsigned)time(NULL));
			int rand1=rand()%10;
			//rand1=5;/*测试用*/
			//cin>>rand1;/*测试用*/ 
			if(rand1<4){//十分之四0.1.2.3 
				RED;
				cout<<"一只怪物正向你袭来！\n\n";
				autocolor;
				pause;
				cls;
				srand((unsigned)time(NULL));
				guaiwu();//怪物函数 
				cls;
			}//十分之二4.5 
			else if(rand1<6){//宝箱是3木2铁1金 
				srand((unsigned)time(NULL));
				int lx/*宝箱类型*/=rand()%6;//随机抽取 
				RG;
				cout<<"发现"<<x[rand()%6]<<"制箱子！\n";
				autocolor;
				pause;
				bx(lx);//宝箱函数，参数为箱子的类型 
			}
			else if(rand1<8){//十分之二6.7
				shijian();//随机事件 
			}
			else{//十分之二8.9
				GB;
				cout<<"你来到了一个商店。\n";
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
			cd();//进入商店函数 
		}
		else if (xd == 2) {//进入背包 
			cls;
			bb(0);
			cls;
		}
		else if (xd == 3) { //退出游戏 
			RED;
			cout << endl;
			cout << "真的要走了吗？" << endl;
			RG;
			cout << "[0]忍痛离开\t";
			GREEN;
			cout << "[1]再玩一会" << endl;
			xd = getch() - '0';
			while (xd < 0 || xd > 1) xd = getch() - '0';
			autocolor;
			cout << endl;
			if (!xd) {
				cout << "已保存存档，欢迎下次继续！" << endl;
				pause;
				return;
			} else {
				cout << "感谢你的支持！" << endl;
				wait;
				cls;
			}
		}
		else {
			GREEN;
			cout << "\n已保存游戏进度！\n\n";
			autocolor;
			pause; 
			dd(0);
		}
	}
}
void wms()/*显示作者(〃'▽'〃)*/
{
	RED;
	cout<<"小钟";
	GREEN;
	cout<<"和";
	RG;
	cout<<"饺子";
	autocolor;
}
void bang()//排行榜 
{
	RG;
	cout<<"-------------------------------------------------------------------------------\n";
	GB;
	cout<<"玩家排行榜"<<endl;
	cout<<"[1] 用户名：admin 等级：100"<<endl;
	cout<<"[2] 用户名：渣渣飞 等级：99"<<endl;
	cout<<"[3] 用户名: 古天乐 等级：98"<<endl;
}
void setnew()// 更新内容 
{
	cout<<endl;
	RG;
	cout<<"beta1.0.1更新内容"<<endl;
	cout<<"1.增加宝箱怪" <<endl;
	cout<<"2.修复了泉水恢复生命值错误的bug" <<endl;
	cout<<"3.增加排行榜" <<endl;
	cout<<"4.增加背景音乐（尚在测试）和颜色" <<endl;
	cout<<"5.选择选项再也不用辛苦地按回车啦\(^o^)/~" <<endl;
	cout<<"6.修复了随机事件的错误" <<endl;
	cout<<"7.应内测玩家要求，人道地调高了毒气瓶的伤害值" <<endl;
	cout<<"8.调高了经验和金币的掉落值，妈妈再也不怕我肝疼了" <<endl;
	cout<<"9.降低了探索和战斗等待时间，时间就是金钱！" <<endl;
	cout<<"10.修改了存档的文件格式，对存档进行了简单的加密（作弊可耻！）" <<endl;
	GB;
	cout<<endl; 
	cout<<"beta1.0.2更新内容（公测版）！！！！！"<<endl;
	cout<<"11.修复了金钱和经验实际获得数量和显示获得数量不一致的bug"<<endl;
	cout<<"12.增加了退出游戏选项（真正的全键盘操作！）\n";
	cout<<"13.隐藏和固定了存档路径，不会因EXE的移动需要手动存档，杜绝作弊\n";
	cout<<"14.增加了切换存档选项，避免重复退出进入游戏\n";//局长帮忙
	cout<<"15.然鹅还是发现作弊现象依然严重，于是手贱地把存档数据真·加密了下，"<<endl; 
	cout<<"16.为了满足大家的作弊欲望，推出了官方修改器QWQ(可以加QQ领取)"<<endl; 
	
}
void broad()//告示板 
{
	cout<<"\n特别鸣谢：201杨钧涛,105 陈建旭,201陈昊。201何晋熙（感谢合作）"<<endl;
	cout<<"作者QQ:1030082097"<<endl; 
	cout<<"背景音乐出了点问题，自己手动播放吧~^_^"<<endl; 
} 
BOOL SetConsoleColor(WORD wAttributes)  
{  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
    if (hConsole == INVALID_HANDLE_VALUE)  
        return FALSE;  
  
    return SetConsoleTextAttribute(hConsole, wAttributes);  
}  
int main()//主函数 
{  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	setwindow();
	CreateDirectory("C://players",NULL);
	cls;//清屏 
	RG; //亮黄色 
	cout<<"-------------------------------------------------------------------------------\n";
	GB;//天蓝色 
	cout<<"欢迎来到贪玩蓝月（呸）！\n";
	autocolor;
	cout<<"版本:"<<version<<"     制作者：";
	wms();//显示作者 
	broad();//告示 
	bang();//排行 
	setnew();//更新信息 
	RG;//亮黄色
	cout<<"\n-------------------------------------------------------------------------------\n";
	autocolor;
	pause;//等待 
	cls;//清屏 
	dd(0);//读档 
	wj();//玩家属性 
	pause;//等待 
	cls;//清屏 
	aa();//抽取事件主函数
}
/*开发笔记：
getch();#include "conio.h"
*/ 
//system("C:\\Users\\zzm10\\Desktop\\beta1.0\\1.wav");//playsound打死用不了，用这个凑合一下 
//使用rand（）函数产生随机数。（rand（）函数的头文件在<cstdlib>中）    还有srand 
