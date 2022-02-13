#include "MyPlayer.h"
#include<queue>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
// �������ʵ�ֿ�ʼ
using namespace QuoridorUtils;
int mytargetY = 0;
int enemytargetY = 0;
int blockcounts = 10;
std::vector<QuoridorUtils::BlockBar> blocks;
//ֻ���ǵ�ǰλ�ú͵������ѡ�����·��
//����ϸ�ڱ������������ɸ�������ʵ��
MyPlayer::node MyPlayer::move(const Location& myLoc,int mytarget)//�ҵ�λ�ú�Ŀ��
{
    node tem;//Ҫ���صĽṹ�壬������һ��λ���Լ����·���ĳ���
    tem.allsteps = 0;
    bool havegone[11][11] = { 0 };//��¼���Ƿ��߹�
    Location before[11][11] = {0};//��¼��һ���ڵ������
    havegone[myLoc.x][myLoc.y] = 1;
    std::queue<Location> lq;
    lq.push(myLoc);
    while (!lq.empty())
    {
        Location last = lq.front();
        lq.pop();
        if (last.y == mytarget)
        {
            tem.nextstep[0].x = last.x;
            tem.nextstep[0].y = last.y;
            //printf("(%d,%d) ", tem.nextstep.x, tem.nextstep.y);
            int i = 0;
            while (before[tem.nextstep[i].x][tem.nextstep[i].y].x != myLoc.x || before[tem.nextstep[i].x][tem.nextstep[i].y].y != myLoc.y)
            {//����һ��λ�þ��ǿ�ʼλ��ʱ���������
                int oldx = tem.nextstep[i].x;
                int oldy = tem.nextstep[i].y;
                tem.nextstep[i+1].x = before[oldx][oldy].x;
                tem.nextstep[i+1].y = before[oldx][oldy].y;
                //printf("(%d,%d) ", tem.nextstep.x, tem.nextstep.y);
                ++i;
                ++tem.allsteps;
            }
            int all = tem.allsteps;
            if(before[tem.nextstep[all].x][tem.nextstep[all].y].x==myLoc.x
                &&before[tem.nextstep[all].x][tem.nextstep[all].y].y==myLoc.y)
            return tem;
        }
        else
        {
            bool directions[4];
            directions[0] = last.y < SIZE;           // �Ƿ���������� 
            directions[1] = last.y > 1;                             // �Ƿ���������� 
            directions[2] = last.x > 1;                             // �Ƿ���������� 
            directions[3] = last.x < SIZE;           // �Ƿ���������� 
            for (auto block : blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
                if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
                    if (block.start.x == last.x - 1 ||
                        block.start.x == last.x - 2) {              // ���ܵ�·�ĵ��� 
                        if (block.start.y == last.y) {
                            directions[0] = false;
                        }
                        else if (block.start.y == last.y - 1) {
                            directions[1] = false;
                        }
                    }
                }
                if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
                    if (block.start.y == last.y - 1 ||
                        block.start.y == last.y - 2) {              // ���ܵ�·�ĵ��� 
                        if (block.start.x == last.x) {
                            directions[3] = false;
                        }
                        else if (block.start.x == last.x - 1) {
                            directions[2] = false;
                        }
                    }
                }
            }
            //����Ϊ�ж���һ������ĸ������Ƿ����ǰ��
            for (int i = 0; i < 4; i++)
            {
                Location next;
                if (directions[i])//��һ����ܵ�λ�ò�����û����������
                {
                    //����Ϊ��������
                    if (i == 0)
                    {
                        next.x = last.x;
                        next.y = last.y + 1;
                    }
                    else if (i == 1)
                    {
                        next.x = last.x;
                        next.y = last.y - 1;
                    }
                    else if (i == 2)
                    {
                        next.x = last.x - 1;
                        next.y = last.y;
                    }
                    else if (i == 3)
                    {
                        next.x = last.x + 1;
                        next.y = last.y;
                    }
                    
                }
                if (havegone[next.x][next.y] == 0)//�����û�б�������
                {
                    before[next.x][next.y].x = last.x;
                    before[next.x][next.y].y = last.y;
                    lq.push(next);
                    havegone[next.x][next.y] = 1;
                }
            }
        }
    }
    return tem;//û·���߾ͷ���(-1,-1)
}
bool MyPlayer::barlegal(BlockBar bar,const Location& myLoc,const Location& enemyLoc )//�ж��·��õĵ����Ƿ��ص��Ѿ����ڵĵ��� ,���Խ��治���ص�
{
    //�����Ѵ��ڵĵ���
    bar.normalization();
    if (bar.isH())//����·��õĵ������
    {
        for (auto block : blocks)
        {
            if (block.isH())//���еĵ���Ҳ�Ǻ���
            {
                //��ʼ�������ֵ���һ�������ص�
                if (abs(bar.start.x - block.start.x) <= 1 && bar.start.y == block.start.y)
                    return false;
            }
        }
    }
    else if (bar.isV())//����·��õĵ�������
    {
        for (auto block : blocks)
        {
            if (block.isV())
            {
                if (abs(bar.start.y - block.start.y) <= 1 && bar.start.x == block.start.x)
                    return false;
            }
        }
    }
    //��Ҫ�жϷ��õ����᲻������Լ����߶Է�
    blocks.push_back(bar);//���Ԫ�غ�۲��Ƿ�˫�����������·��
    if (move(myLoc, mytargetY).allsteps==0 || move(enemyLoc, enemytargetY).allsteps == 0)//��һ��������������
    {
        blocks.pop_back();
        return false;
    }
    blocks.pop_back();//����ո���ӽ�ȥ�ĵ���Ԫ��
    return true;//û�ҵ��ص��Ҷ���·�ͷ���true
}
//���õ���ǰҪ�ж��Ƿ��Լ����е��壡
BlockBar MyPlayer::putblock(const Location& myLoc, const Location& enemyLoc)
{
    Location enemystep[100];//��¼���˵�·��
    for (int i = 0; i < 100; i++)
        enemystep[i] = move(enemyLoc, enemytargetY).nextstep[i];
    int score=0,minscore=10000;//ÿһ���õ���������ӵķ����Լ���ð��ӵķ���
    BlockBar resultbar,bestbar;//ÿһ���İ����Լ������õİ���λ��
    for(int i=1;i<=move(enemyLoc,enemytargetY).allsteps;i++)
    {
        bool flag1 = 0, flag2 = 0;
        double score1 = 0, score2 = 0;
        BlockBar bar1, bar2;//��¼ÿһ���Ŀ��ܵ����ְ��ӵĿ����Է����Լ�λ��
        Location lastLocation;//��¼��ǰ������һ��λ��
        if (enemystep[i + 1].x == -1 && enemystep[i + 1].y == -1)
            lastLocation = enemyLoc;
        else
            lastLocation = enemystep[i + 1];
        if ((enemystep[i].x ==lastLocation.x) && (enemystep[i].y - 1 == lastLocation.y))//����������
        {
        //���ַ�ʽ������
        //������ַ��÷�ʽ��������Ƚ����ֶԶ��ָ�����Լ�����
        bar1.start.x = lastLocation.x - 1;
        bar1.start.y = lastLocation.y;
        bar1.stop.x = lastLocation.x + 1;
        bar1.stop.y = lastLocation.y;
        bar2.start.x = lastLocation.x - 2;
        bar2.start.y = lastLocation.y;
        bar2.stop.x = lastLocation.x;
        bar2.stop.y = lastLocation.y;
        }
    
    else if ((enemystep[i].x == lastLocation.x) && (enemystep[i].y + 1 == lastLocation.y))//����������
    {
        bar1.start.x = lastLocation.x - 1;
        bar1.start.y = lastLocation.y - 1;
        bar1.stop.x = lastLocation.x + 1;
        bar1.stop.y = lastLocation.y - 1;
        bar2.start.x = lastLocation.x - 2;
        bar2.start.y = lastLocation.y - 1;
        bar2.stop.x = lastLocation.x;
        bar2.stop.y = lastLocation.y-1;
        
    }
    else if ((enemystep[i].y == lastLocation.y )&& (enemystep[i].x + 1 == lastLocation.x))//����������
    {
        bar1.start.x = lastLocation.x - 1;
        bar1.start.y = lastLocation.y + 1;
        bar1.stop.x = lastLocation.x - 1;
        bar1.stop.y = lastLocation.y + 1;
        bar2.start.x = lastLocation.x - 1;
        bar2.start.y = lastLocation.y - 2;
        bar2.stop.x = lastLocation.x - 1;
        bar2.stop.y = lastLocation.y;
    }
    else if ((enemystep[i].y == lastLocation.y) && (enemystep[i].x + 1 == lastLocation.x))//����������
    {
        bar1.start.x = lastLocation.x;
        bar1.start.y = lastLocation.y - 1;
        bar1.stop.x = lastLocation.x;
        bar1.stop.y = lastLocation.y + 1;
        bar2.start.x = lastLocation.x;
        bar2.start.y = lastLocation.y - 2;
        bar2.stop.x = lastLocation.x;
        bar2.stop.y = lastLocation.y;
        
    }
    if (!bar1.isNan() && barlegal(bar1, myLoc, enemyLoc))
    {
        flag1 = 1;
        blocks.push_back(bar1);
        score1 = (double)move(myLoc, mytargetY).allsteps / move(enemyLoc, enemytargetY).allsteps;
        blocks.pop_back();
    }
    if (!bar2.isNan() && barlegal(bar2, myLoc, enemyLoc))
    {
        flag2 = 1;
        blocks.push_back(bar2);
        score2 = (double)move(myLoc, mytargetY).allsteps / move(enemyLoc, enemytargetY).allsteps;
        blocks.pop_back();
    }
    if ((flag1 == 1 && flag2 == 0) || (flag2 == 1 && flag1 == 0))
    {
        if (flag1 == 1)
        {
            resultbar = bar1;
            score = score1;
        }
        else if (flag2 == 1)
        {
            resultbar = bar2;
            score = score2;
        }
    }
    else if (flag1 == 1 && flag2 == 1)//������ַ�ʽ�����ԾͱȽϷ���
    {
        if (score1 <= score2)
        {
            resultbar = bar1;
            score = score1;
        }
        else
        {
            resultbar = bar2;
            score = score2;
        }
    }

    if(score<=minscore)//���Ч�����ѷ������;Ͳ������
    {
        minscore=score;
        bestbar=resultbar;
    }
    }
    //ѭ�������������Ű���λ��
    return bestbar;
    
    //�������Ҷ����ܷžͷ���Ĭ��ֵ-1 -1 -1 -1
    
} 
Location MyPlayer::helpmove(const Location& myLoc, const Location& moveLoc, const Location& enemyLoc)//�ƶ����Ӹ�������,��Ҫ���������Է�����ʱ�Ĵ���
{
    if (moveLoc.distance(enemyLoc) == 0)//�����һ��ǡ���ǶԷ�����
    {
        //�ֱ��������������ĸ������Լ��Ե��˺󷽵�����Լ��Ƿ��Խ���߽磡
        if (myLoc.x == moveLoc.x && myLoc.y + 1 == moveLoc.y)//������
        {
            for (auto block : blocks)//��������
            {
                if (block.isH())
                {
                    if (block.start.x == enemyLoc.x - 1 || block.start.x == enemyLoc.x - 2)
                    {
                        if (block.start.y == enemyLoc.y || enemyLoc.y == SIZE)//���˱����е����û������ѡ��ŵ���
                        {
                            Location null;
                            return null;
                        }
                    }
                }
            }
            Location tem;
            tem.x = moveLoc.x;
            tem.y = moveLoc.y + 1;
            return tem;
        }
        else if (myLoc.x == moveLoc.x && myLoc.y - 1 == moveLoc.y)//������
        {
            for (auto block : blocks)
            {
                if (block.isH())
                {
                    if (block.start.x == enemyLoc.x - 1 || block.start.x == enemyLoc.x - 2)
                    {
                        if (block.start.y + 1 == enemyLoc.y || enemyLoc.y == 1)//�����ߵ����·��ǵ���
                        {
                            Location null;
                            return null;
                        }
                    }
                }
            }
            Location tem;
            tem.x = moveLoc.x;
            tem.y = moveLoc.y - 1;
            return tem;
        }
        else if (myLoc.y == moveLoc.y && myLoc.x + 1 == moveLoc.x)//������
        {
            for (auto block : blocks)
            {
                if (block.isV())
                {
                    if (block.start.y == enemyLoc.y - 1 || block.start.y == enemyLoc.y - 2)
                    {
                        if (block.start.x == enemyLoc.x || enemyLoc.x == SIZE)
                        {
                            Location null;
                            return null;
                        }
                    }
                }
            }
            Location tem;
            tem.x = moveLoc.x + 1;
            tem.y = moveLoc.y;
            return tem;
        }
        else if (myLoc.y == moveLoc.y && myLoc.x - 1 == moveLoc.x)//������
        {
            for (auto block : blocks)
            {
                if (block.isV())
                {
                    if (block.start.y == enemyLoc.y - 1 || block.start.y == enemyLoc.y - 2)
                    {
                        if (block.start.x + 1 == enemyLoc.x || enemyLoc.x == 1)
                        {
                            Location null;
                            return null;
                        }
                    }
                }
            }
            Location tem;
            tem.x = moveLoc.x - 1;
            tem.y = moveLoc.y;
            return tem;
        }
    }
    else //�����һ�����ǶԷ����Ӿ�ֱ�ӷ������·�ĵ�һ��
        return moveLoc;
}
// �������ʵ�ֽ���


     // �������ʵ�ֿ�ʼ
Step MyPlayer::nextStep(const ChessboardChange& newChange) {
    // ��֪: ��ʾ���������Ϊ API ʹ���Լ���Ϸ�����˽ⷶ��, ������֤������ȷ��, �����ճ��հ� 
    if (mytargetY == 0) {                                // �жϲ���¼�Լ���Ŀ��
        const auto d = std::chrono::system_clock::now().time_since_epoch();
        const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
        srand(nanosecond);
        if (newChange.myLoc == PLAYER0_LOC) {                // ������ʼ����Ϊ (5,1) ��Ŀ��Ϊ (x,9)
            mytargetY = PLAYER1_LOC.y;
            enemytargetY = PLAYER0_LOC.y;
        }
        else {                                             // ������ʼ����Ϊ (5,9) ��Ŀ��Ϊ (x,1)
            mytargetY = PLAYER0_LOC.y;
            enemytargetY = PLAYER1_LOC.y;
        }
    }
    std::cout << newChange << std::endl;                     // ������յ������ݵ�����̨��ʾ  
    if (!newChange.newEnemyBlockBar.isNan()) {               // �Է������˵��� 
        BlockBar tmp = newChange.newEnemyBlockBar;
        tmp.normalization();                                 // �淶Ϊ start ����С�� stop �������ʽ 
        blocks.push_back(tmp);                         // �洢���� 
    }
    Step step;                                               // ��ʼ�� step Ĭ�ϲ��ƶ����Ű� 
    int mylen = 0, enemylen = 0;
    mylen = move(newChange.myLoc, mytargetY).allsteps;
    enemylen = move(newChange.enemyLoc, enemytargetY).allsteps;
    if (mylen <= enemylen||enemylen>=8)                         //����ҵ�·�����̻��߶Է���·���㹻����ѡ������
    {
        int tem = move(newChange.myLoc, mytargetY).allsteps;
        Location moveloc = move(newChange.myLoc, mytargetY).nextstep[tem];
        //�������Ҳ�����·�����ڵ��Ǳ����ֶ�ס
        step.myNewLoc = helpmove(newChange.myLoc, moveloc, newChange.enemyLoc);
        if (step.myNewLoc.x == -1 &&step.myNewLoc.y==-1 && blockcounts > 0)//���˱����ǵ���ͱ������ˣ�ѡ��Ű�
        {
            BlockBar tem = putblock(newChange.myLoc, newChange.enemyLoc);
                step.myNewBlockBar = tem;
                step.myNewBlockBar.normalization();
                blocks.push_back(step.myNewBlockBar);
                blockcounts--;
        }

    }
    else                                          //����ҵ�·�����͵�ס�������·��û�취��������
    {
        if (blockcounts > 0)
        {
            BlockBar tem = putblock(newChange.myLoc, newChange.enemyLoc);
            if (tem.start.x == -1&&tem.start.y==-1&&tem.stop.x==-1&&tem.stop.y==-1)//���ܵ����صİ���ΪĬ��-1������
            {
                int tem = move(newChange.myLoc, mytargetY).allsteps;
                Location moveloc = move(newChange.myLoc, mytargetY).nextstep[tem];
                step.myNewLoc = helpmove(newChange.myLoc, moveloc, newChange.enemyLoc);
            }
            else
            {
                step.myNewBlockBar = tem;
                step.myNewBlockBar.normalization();
                blocks.push_back(step.myNewBlockBar);
                blockcounts--;
            }
        }
        else//�����Ѿ�������
        {
            int tem = move(newChange.myLoc, mytargetY).allsteps;
            Location moveloc = move(newChange.myLoc, mytargetY).nextstep[tem];
            step.myNewLoc = helpmove(newChange.myLoc, moveloc, newChange.enemyLoc);
        }
    }
    std::cout << step << std::endl;                          // ����ҵľ��ߵ�����̨��ʾ 
    return step;
}

void MyPlayer::restart() {
    blockcounts = 10;
    blocks.clear();
    mytargetY = 0;
    enemytargetY = 0;
}
// �������ʵ�ֽ���


