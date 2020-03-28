#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

#define Rint register int 
const int N = 20;
const int M = 20;
const int MaxSpeed = 4;
const int PipeLength = 7;
const int Delay = 500;
const int MaxPressTimesInOneTurn = 3;
int map[N+5][M+5];
bool die;

/*
    id  type
    -1  wall
     0  air 
*/

struct Bird{
    int speed,height,score,round;
    Bird () {speed = score = round = 0; height = N>>1;}
    ~Bird () {}
}bird;

void init(){
    srand(time(NULL)); //地图id (强行) 
    bird.height = N>>1;//鸟的初始高度为总高度一半 
    for(Rint i = 1;i<=M;++i)
        map[1][i] = map[N][i] = -1;//天花板和地板填充障碍物
}

void printGame(){
    string output;
    if(bird.height > N || bird.height < 0) {die = 1;return ;}
    for(Rint i = 1;i<=N;++i){
        for(Rint j = 1;j<=M;++j){
            if(j == 1 && bird.height == i){
                output+="++";if(map[i][j] == -1) die = 1;
                continue;
            }
            switch (map[i][j]){
            case -1:
                output += "##";
                break;
            default:
                output += "  ";
                break;
            }
        }
        output += (i!=N)?"\n":"";
    }
    puts(output.c_str());
}

void generatePipe(){
    int pipeTop = rand() % (N-PipeLength-1) + 2; // 1~20随机数作为管子顶部 ,好像不能到20吧,不然没路了 那就1~20-PipeLength
    for(Rint i = 1;i<pipeTop;++i) map[i][M] = -1;
    for(Rint i = pipeTop + PipeLength;i<N;++i) map[i][M] = -1;
}

void getKbhit(){
    int t = clock();
    while(clock() < t+Delay){
        if(kbhit()){
            getch();
            bird.speed = max(bird.speed+2,2);
            bird.height -= 1;
            printGame();
        }
    }
}

void runGame(){
    bird.score ++,bird.round ++;
    bird.speed -= 1;
    bird.speed = ((bird.speed > MaxSpeed) ? (MaxSpeed) : (bird.speed));
    bird.speed = ((bird.speed < -MaxSpeed) ? (-MaxSpeed) : (bird.speed));
    bird.height -= bird.speed;//回合开始
    if(bird.height > N || bird.height < 0) {die = 1;return ;}
    for(Rint i = 1;i<=N;++i)
        for(Rint j = 1;j<M;++j)
            map[i][j] = map[i][j+1]; // 视图的移动
    for(Rint i = 2;i<N;++i) map[i][M] = 0;
    if(bird.round % 6 == 0){
        generatePipe();
    }
    printGame();
    getKbhit();
}
int main(){
    init();
    printGame();
    while (!die)
        runGame();
    return 0;
}
