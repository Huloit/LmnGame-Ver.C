#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int MAP_SIZE_X;
int MAP_SIZE_Y;


char map[14][14] = {}; // �ڸ� �˻縦 ���Ͽ� 4x4�迭���� ���Ƹ��� 2�� ����
int endCount = 0; //���ӳ�Ȯ��
int seq = 0; //����
int lCount = 0, mCount = 0, nCount = 0; //lmn�� ó������ �ƴ��� Ȯ��
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
        seq++; //��������
        cls();
        return 1;
    }
    else if(isAvailableL(x,y)){
        map[x][y] = 'l';
        seq++; //��������
        cls();
        return 1;
    }else return 0;

}
int mcheck(int x, int y){

    if(mCount == 0 && map[x][y] == '#'){
        map[x][y] = 'm';
        mCount = 1;
        seq++; //��������
        cls();
        return 1;
    }
    else if(isAvailableM(x,y)){
        map[x][y] = 'm';
        seq++; //��������
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
        return 1; //��������
    }
    else if(isAvailableN(x,y)){
        map[x][y] = 'n';
        seq++;
        cls();//��������
        return 1;
    }else return 0;

}
void lmncheck(char m, int x, int y){ // lmn�� �� �� �ִ��� üũ

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
void print(){//�迭 ���

    int i,j;
    for(i = 2; i < MAP_SIZE_X+2; i++){
        for(j = 2; j < MAP_SIZE_Y+2; j++){
            gotoxy(i*2 + 3,j*2 + 3);
            printf("%c", map[i][j]);
        }
    }
    gotoxy(27,3);
    printf("P%d ���� %d��", seq%2+1, seq);


  //  printf(" endcount = %d", endcount);
}
void error(){

    gotoxy(0,16);
    printf("�߸��Է��ϼ̽��ϴ�. \n");
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
void gameend(){//���ӳ� Ȯ��

    int get;
    if(isEnd()){
        gotoxy(0,7);
        printf("P%d �¸�!!! ", (seq+1)%2+1);
        gotoxy(0,8);
        printf("������ �ٽ� �Ͻ÷��� 1, �����Ͻ÷��� �ƹ�Ű�� ��������...");
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
void checkend_previous() //���ӳ� Ȯ��
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
    printf("l,m,n�� �ϳ��� ��ǥ�� �Է��ϼ���.");
    fflush(stdin); // scanf���� ����Ű�� �Է��ϰ� �Ǵµ� �װ� �Է¹��ۿ� ���� ���� scanf�� ������ �־ ���� �� ���۸� ���� ���� ����
    scanf("%c %d %d", m, x, y);



}
void convertCoordinate(int* x, int* y){

    *x += 1;
    *y = MAP_SIZE_Y+2-*y;

}
void setMapSize(){
    gotoxy(27,3);
    printf(" �� ����� �Է��� �ּ���... x y");
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
*�߰��� ��
�߸� �Է��Ͽ��� ��� ������ �߰�
ĭ�� �� ���� ���� �ºΰ� �����Ǿ��� ��� �¸� ǥ�� (���� ��� ���� ����)
�߰��� ���� �����ϴ� ��� ���� ��� �߰�




*/
//�� ó���� ����� l������ �� l�� �� ���������� ��ġ�Ұ�� m�̳� n�� �� ��ǥ���� �밢������ ��ĭ �̵��Ѱ��� ������ ��ǻ�Ͱ� �̱��

// ó���� �ڳ� ��ĭ�� �߿��ϸ� �ڳ� 4ĭ��  ���� ������ ���а� �����ȴ�. (ȸ����Ű�� �Ȱ����Ƿ�) l�� ���� l�� ������ ���� ��쿡�� ȸ������������ �� �������� ���������� ä�������� �������� �����Ѵ�

// ���� ���� �켱������ �̴�.

// ���÷��̾ l�� �� ó���� �����ʰ� m�̳� n�� ������ ���, m�� ������ ��쿡�� m�� �� �� �ִ� �ֿ켱ĭ�� m�� ����  n�� ������ ��쿡�� ���� �� �� �ִ� �ֿ켱ĭ�� n�� �뤾�´�.
