#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int MAP_SIZE_X;
int MAP_SIZE_Y;


char map[14][14] = {}; // 자리 검사를 위하여 4x4배열에서 위아리로 2씩 여백
int endCount = 0; //게임끝확인
int seq = 0; //차례
int lCount = 0, mCount = 0, nCount = 0; //lmn이 처음인지 아닌지 확인
void gotoxy(int x, int y){

 COORD CursorPosition = {x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);

}

void cls(){

    system("cls");

}
int isAvailableL(int x, int y){

    if((map[x+1][y+1] == 'l' || map[x-1][y+1] == 'l' || map[x-1][y-1] == 'l' || map[x+1][y-1] == 'l') && map[x][y] == '#'){
        return 1;
    }else return 0;

}
int isAvailableM(int x, int y){

    if((map[x+1][y] == 'm' || map[x][y+1] == 'm' || map[x-1][y] == 'm' || map[x][y-1] == 'm') && map[x][y] == '#'){
        return 1;
    }else return 0;

}
int isAvailableN(int x, int y){

    if((map[x+2][y] == 'n' || map[x][y+2] == 'n' || map[x-2][y] == 'n' || map[x][y-2] == 'n') && map[x][y] == '#'){
        return 1;
    }else return 0;

}
int lcheck(int x, int y){

    if(lCount == 0 && map[x][y] == '#'){
        map[x][y] = 'l';
        lCount = 1;
        seq++; //차례증가
        cls();
        return 1;
    }
    else if(isAvailableL(x,y)){
        map[x][y] = 'l';
        seq++; //차례증가
        cls();
        return 1;
    }else return 0;

}
int mcheck(int x, int y){

    if(mCount == 0 && map[x][y] == '#'){
        map[x][y] = 'm';
        mCount = 1;
        seq++; //차례증가
        cls();
        return 1;
    }
    else if(isAvailableM(x,y)){
        map[x][y] = 'm';
        seq++; //차례증가
        cls();
        return 1;
    }else return 0;

}
int ncheck(int x, int y){

    if(nCount == 0 && map[x][y] == '#'){
        map[x][y] = 'n';
        nCount = 1;
        seq++;
        cls();
        return 1; //차례증가
    }
    else if(isAvailableN(x,y)){
        map[x][y] = 'n';
        seq++;
        cls();//차례증가
        return 1;
    }else return 0;

}
void lmncheck(char m, int x, int y){ // lmn이 들어갈 수 있는지 체크

    switch (m){
        case 'l':
            if(!lcheck(x,y)){
                error();
            }
            break;
        case 'm':
            if(!mcheck(x,y)){
                error();
            }
            break;
        case 'n':
            if(!ncheck(x,y)){
                error();
            }
            break;
        default:
        error();
    }

}
void reset(){// map reset

    int i,j;
    for(i = 2; i < MAP_SIZE_X+2; i++)
    {
        for(j = 2; j < MAP_SIZE_Y+2; j++)
        {
            map[i][j] = '#';
        }
    }

}
void print(){//배열 출력

    int i,j;
    for(i = 2; i < MAP_SIZE_X+2; i++){
        for(j = 2; j < MAP_SIZE_Y+2; j++){
            gotoxy(i*2 + 3,j*2 + 3);
            printf("%c", map[i][j]);
        }
    }
    gotoxy(27,3);
    printf("P%d 차례 %d번", seq%2+1, seq);


  //  printf(" endcount = %d", endcount);
}
void error(){

    gotoxy(0,16);
    printf("잘못입력하셨습니다. \n");
    system("PAUSE");
    cls();

}
void gameReset(){

    reset();
    system("cls");
    endCount = 0;
    lCount = 0;
    mCount = 0;
    nCount = 0;
    seq = 0;

}
int isEnd(){

    if((endCount == (MAP_SIZE_X*MAP_SIZE_Y-seq) && seq != 0 && lCount != 0 && mCount != 0 && nCount != 0) || seq == MAP_SIZE_X*MAP_SIZE_Y){
        return 1;
    }else return 0;

}
void gameend(){//게임끝 확인

    int get;
    if(isEnd()){
        gotoxy(0,7);
        printf("P%d 승리!!! ", (seq+1)%2+1);
        gotoxy(0,8);
        printf("게임을 다시 하시려면 1, 종료하시려면 아무키나 누르세요...");
        get = getch();
        if(get == '1'){
            gameReset();
        }
        else exit(1);


    }
    else endCount = 0;

}
void checkend(){
    int i;
    int j;
    for(i = 2; i < MAP_SIZE_X+2; i++){
        for(j = 2; j < MAP_SIZE_Y+2; j++){
            if(map[i][j] == '#'){
                if(!isAvailableL(i,j)){
                    if(!isAvailableM(i,j)){
                        if(!isAvailableN(i,j)){
                            endCount++;
                        }//else {gotoxy(i*2 + 3,j*2 + 3); printf("N");}
                    }//else {gotoxy(i*2 + 3,j*2 + 3); printf("M");}
                }//else {gotoxy(i*2 + 3,j*2 + 3); printf("L");}
            }

        }
    }
}
/*
void checkend_previous() //게임끝 확인
{
    int i;
    int j;
    for(i = 2; i < 6; i++){
        for(j = 2; j < 6; j++){
            if(map[i][j] == '#'){
                if(map[i+1][j+1] != 'l' && map[i-1][j+1] != 'l' && map[i-1][j-1] != 'l' && map[i+1][j-1] != 'l'){
                    if(map[i+1][j] != 'm' && map[i][j+1] != 'm' && map[i-1][j] != 'm' && map[i][j-1] != 'm'){
                        if(map[i+2][j] != 'n' && map[i][j+2] != 'n' && map[i-2][j] != 'n' && map[i][j-2] != 'n'){
                            endCount++;
                        }//else {gotoxy(i*2 + 3,j*2 + 3); printf("N");}
                    }//else {gotoxy(i*2 + 3,j*2 + 3); printf("M");}
                }//else {gotoxy(i*2 + 3,j*2 + 3); printf("L");}
            }

        }
    }
}
*/
void setCoordinate(char* m, int* x, int* y){

    gotoxy(0,15+MAP_SIZE_Y);
    printf("l,m,n중 하나와 좌표를 입력하세요.");
    fflush(stdin); // scanf에서 엔터키를 입력하게 되는데 그게 입력버퍼에 남아 이후 scanf에 영향을 주어서 이전 입 버퍼를 비우기 위한 행위
    scanf("%c %d %d", m, x, y);



}
void convertCoordinate(int* x, int* y){

    *x += 1;
    *y = MAP_SIZE_Y+2-*y;

}
void setMapSize(){
    gotoxy(27,3);
    printf(" 맵 사이즈를 입력해 주세요... x y");
    scanf("%d %d", &MAP_SIZE_X, &MAP_SIZE_Y);

}
int main(){
    int i;
    int x,y;
    char m;

    setMapSize();
    cls();
    reset();

    for( ; ; ){
        checkend();
        gameend();
        print();
        setCoordinate(&m, &x, &y);
        convertCoordinate(&x, &y);
        lmncheck(m,x,y);

    }
}

/*
*추가할 점
잘못 입력하였을 경우 물리기 추가
칸이 다 차기 전에 승부가 결정되었을 경우 승리 표시 (게임 계속 진행 가능)
중간에 전부 꺼야하는 경우 리셋 기능 추가




*/
//맨 처음에 사람이 l을놓고 그 l이 네 꼭짓점에에 위치할경우 m이나 n을 그 좌표에서 대각선으로 한칸 이동한곳에 놓으면 컴퓨터가 이긴다

// 처음에 코너 네칸이 중요하며 코너 4칸에  따라 게임의 승패가 결정된다. (회전시키면 똑같으므로) l을 막고 l을 막을수 없는 경우에는 회전시켰을때의 판 기준으로 위에서부터 채워나가는 방향으로 진행한다

// 놓는 것의 우선순위는 이다.

// 선플레이어가 l을 맨 처음에 놓지않고 m이나 n을 놓았을 경우, m을 놓았을 경우에는 m이 올 수 있는 최우선칸에 m을 놓고  n을 놓았을 경우에는 ㅜ이 올 수 있는 최우선칸에 n을 노ㅎ는다.
