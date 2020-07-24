#include "neo/neo.hpp"
using namespace std;
#define n 20
int mp[n+5][n+5];
bool vis[n+5][n+5];
bool mark[n+5][n+5];
int out[n+5][n+5];
int unfind=0;
int main();
void Show(){
	unfind=0;
	for(int i=1;i<=n;i++){
		gotoxy(2,i+2);
		for(int j=1;j<=n;j++){
			if(!mark[i][j]&&mp[i][j]) unfind++;
			if(mark[i][j]) {setcolor(0xcf);printf("* ");setcolor(0x3f);continue;}
			if(!vis[i][j]) printf("□");
			else if(out[i][j]=='!') {printf("! "),MessageBox(GetConsoleWindow(),"点到雷了~","Failed",0);clrscr();main();mouse::CloseListen();exit(0);} 
			else if(out[i][j]==' ') printf("  ");
			else printf("%d ",out[i][j]);
		}
	}
}
const int flg[4][2]={{1,0},{0,1},{0,-1},{-1,0}};
void Clear(int i,int j){
	if(i<1||j<1||i>n||j>n||mp[i][j]||vis[i][j]) return;
	if(mp[i-1][j]+mp[i-1][j-1]+mp[i][j-1]+mp[i+1][j-1]+mp[i+1][j]+mp[i+1][j+1]+mp[i][j+1]+mp[i-1][j+1]){
		vis[i][j]=1;
		int x=mp[i-1][j]+mp[i-1][j-1]+mp[i][j-1]+mp[i+1][j-1]+mp[i+1][j]+mp[i+1][j+1]+mp[i][j+1]+mp[i-1][j+1];
		out[i][j]=x;
		if(x>1) return;
	}
	if(mp[i][j]==0&&mp[i-1][j]+mp[i-1][j-1]+mp[i][j-1]+mp[i+1][j-1]+mp[i+1][j]+mp[i+1][j+1]+mp[i][j+1]+mp[i-1][j+1]==0){vis[i][j]=1,out[i][j]=' ';
	for(int k=0;k<4;k++){
		Clear(i+flg[k][0],j+flg[k][1]);
	}}
}
void Click(int i,int j){
	if(mp[i][j]) out[i][j]='!';
	else {
		int x=mp[i-1][j]+mp[i-1][j-1]+mp[i][j-1]+mp[i+1][j-1]+mp[i+1][j]+mp[i+1][j+1]+mp[i][j+1]+mp[i-1][j+1];
		if(x==0) out[i][j]=' ',Clear(i,j);
		else out[i][j]=x;
	}
	vis[i][j]=1;
	Show();
}
void StartGame(){
	clrscr();
	setcolor(0x3f);
	for(int i=1;i<=n;i++){
		gotoxy(2,i+2);
		for(int j=1;j<=n;j++){
			mp[i][j]=(rand()&1)&&(rand()&1)&&(rand()&1)&&(rand()&1);
		}
	}
	Show();
	while(1){
		gotoxy(0,0);
		printf("当前鼠标坐标: [%d,%d]  还有 %d 个雷www",mouse::nowPos.X,mouse::nowPos.Y,unfind);
		if(IsLeftButtonDown()&&IsRightButtonDown()) mouse::CloseListen(),exit(0);
		if(IsLeftButtonDown()){
			Click(mouse::nowPos.Y-2,mouse::nowPos.X>>1);
			WaitForLeftButtonUp();
		}else if(IsRightButtonDown()){
			if(!vis[mouse::nowPos.Y-2][mouse::nowPos.X>>1]) mark[mouse::nowPos.Y-2][mouse::nowPos.X>>1]=1-mark[mouse::nowPos.Y-2][mouse::nowPos.X>>1]&1;
			Show();
			WaitForRightButtonUp();
		}
		Sleep(1);	
		if(unfind<=0){
			MessageBox(GetConsoleWindow(),"喵喵喵","Win!",0);
			return;
		}
	}
}
void menu(int x1,int x2){
	gotoxy(8,5);
	setcolor(x1);
	printf("开始游戏");
	setcolor(0x07);
	putchar(' ');
	setcolor(x2);
	printf("退出");
	setcolor(0x07);
}
int main(){
//	mouse::CloseListen();
//	system("mode con cols=32 lines=6");
//	std::thread MouseListenThread(mouse::MouseListen);
	memset(mp,0,sizeof(mp));
	memset(vis,0,sizeof(vis));
	memset(mark,0,sizeof(mark));
	memset(out,0,sizeof(out));
	unfind=0;
	srand(GetTickCount());
	gotoxy(0,0);
	setcolor(0x3f);
	printf("      By Level -1 / ezra        ");
	gotoxy(0,1);
	printf("     powered by NeoConsole      ");
	gotoxy(0,2);
	printf("                                ");
	gotoxy(0,3);
	setcolor(0x3f);
	printf("       MineSweeper! 扫雷!       ");
	menu(0xcf,0xcf);
	while(1){
		if(mouse::nowPos.Y==5){
			if(mouse::nowPos.X>=8&&mouse::nowPos.X<=15){
				menu(0xfc,0xcf);
				if(IsLeftButtonDown()){
					WaitForLeftButtonUp();
					StartGame();
					WaitForLeftButtonUp();
				}
			}else if(mouse::nowPos.X>=17&&mouse::nowPos.X<=21){
				menu(0xcf,0xfc);
				if(IsLeftButtonDown()){
					WaitForLeftButtonUp();
					mouse::CloseListen();
					return 0;
					WaitForLeftButtonUp();
				}
			}else menu(0xcf,0xcf);
		}else menu(0xcf,0xcf);
		WaitForLeftButtonUp();
		Sleep(1);	
	}
	mouse::CloseListen();
}
