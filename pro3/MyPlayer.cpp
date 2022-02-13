#include "MyPlayer.h"
#include<queue>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
// 面向过程实现开始
using namespace QuoridorUtils;
int mytargetY = 0;
int enemytargetY = 0;
int blockcounts = 10;
std::vector<QuoridorUtils::BlockBar> blocks;
//只考虑当前位置和挡板情况选出最短路线
//具体细节比如跳过对手由辅助函数实现
MyPlayer::node MyPlayer::move(const Location& myLoc,int mytarget)//我的位置和目标
{
    node tem;//要返回的结构体，包括第一步位置以及最短路径的长度
    tem.allsteps = 0;
    bool havegone[11][11] = { 0 };//记录点是否走过
    Location before[11][11] = {0};//记录上一个节点的坐标
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
            {//当上一个位置就是开始位置时输出该坐标
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
            directions[0] = last.y < SIZE;           // 是否可以向上走 
            directions[1] = last.y > 1;                             // 是否可以向下走 
            directions[2] = last.x > 1;                             // 是否可以向左走 
            directions[3] = last.x < SIZE;           // 是否可以向右走 
            for (auto block : blocks) {                        // 遍历挡板列表, 找到被阻挡的方向 
                if (block.isH()) {                                   // 水平方向挡板, start 与 stop 的 y 相等 
                    if (block.start.x == last.x - 1 ||
                        block.start.x == last.x - 2) {              // 可能挡路的挡板 
                        if (block.start.y == last.y) {
                            directions[0] = false;
                        }
                        else if (block.start.y == last.y - 1) {
                            directions[1] = false;
                        }
                    }
                }
                if (block.isV()) {                                   // 竖直方向挡板, start 与 stop 的 x 相等 
                    if (block.start.y == last.y - 1 ||
                        block.start.y == last.y - 2) {              // 可能挡路的挡板 
                        if (block.start.x == last.x) {
                            directions[3] = false;
                        }
                        else if (block.start.x == last.x - 1) {
                            directions[2] = false;
                        }
                    }
                }
            }
            //以上为判断上一个点的四个方向是否可以前进
            for (int i = 0; i < 4; i++)
            {
                Location next;
                if (directions[i])//下一层可能的位置并且是没有搜索过的
                {
                    //依次为上下左右
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
                if (havegone[next.x][next.y] == 0)//这个点没有被搜索过
                {
                    before[next.x][next.y].x = last.x;
                    before[next.x][next.y].y = last.y;
                    lq.push(next);
                    havegone[next.x][next.y] = 1;
                }
            }
        }
    }
    return tem;//没路可走就返回(-1,-1)
}
bool MyPlayer::barlegal(BlockBar bar,const Location& myLoc,const Location& enemyLoc )//判断新放置的挡板是否重叠已经存在的挡板 ,可以交叉不能重叠
{
    //遍历已存在的挡板
    bar.normalization();
    if (bar.isH())//如果新放置的挡板横向
    {
        for (auto block : blocks)
        {
            if (block.isH())//已有的挡板也是横向
            {
                //起始坐标绝对值相差一以内则重叠
                if (abs(bar.start.x - block.start.x) <= 1 && bar.start.y == block.start.y)
                    return false;
            }
        }
    }
    else if (bar.isV())//如果新放置的挡板纵向
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
    //还要判断放置挡板后会不会堵死自己或者对方
    blocks.push_back(bar);//添加元素后观察是否双方还存在最短路径
    if (move(myLoc, mytargetY).allsteps==0 || move(enemyLoc, enemytargetY).allsteps == 0)//有一方被堵死都不行
    {
        blocks.pop_back();
        return false;
    }
    blocks.pop_back();//清除刚刚添加进去的挡板元素
    return true;//没找到重叠且都有路就返回true
}
//放置挡板前要判断是否自己还有挡板！
BlockBar MyPlayer::putblock(const Location& myLoc, const Location& enemyLoc)
{
    Location enemystep[100];//记录敌人的路径
    for (int i = 0; i < 100; i++)
        enemystep[i] = move(enemyLoc, enemytargetY).nextstep[i];
    int score=0,minscore=10000;//每一步得到的优秀板子的分数以及最好板子的分数
    BlockBar resultbar,bestbar;//每一步的板子以及最后最好的板子位置
    for(int i=1;i<=move(enemyLoc,enemytargetY).allsteps;i++)
    {
        bool flag1 = 0, flag2 = 0;
        double score1 = 0, score2 = 0;
        BlockBar bar1, bar2;//记录每一步的可能的两种板子的可行性分数以及位置
        Location lastLocation;//记录当前步的上一步位置
        if (enemystep[i + 1].x == -1 && enemystep[i + 1].y == -1)
            lastLocation = enemyLoc;
        else
            lastLocation = enemystep[i + 1];
        if ((enemystep[i].x ==lastLocation.x) && (enemystep[i].y - 1 == lastLocation.y))//敌人向上走
        {
        //两种方式的评分
        //如果两种放置方式都可以则比较哪种对对手更差并对自己更好
        bar1.start.x = lastLocation.x - 1;
        bar1.start.y = lastLocation.y;
        bar1.stop.x = lastLocation.x + 1;
        bar1.stop.y = lastLocation.y;
        bar2.start.x = lastLocation.x - 2;
        bar2.start.y = lastLocation.y;
        bar2.stop.x = lastLocation.x;
        bar2.stop.y = lastLocation.y;
        }
    
    else if ((enemystep[i].x == lastLocation.x) && (enemystep[i].y + 1 == lastLocation.y))//敌人向下走
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
    else if ((enemystep[i].y == lastLocation.y )&& (enemystep[i].x + 1 == lastLocation.x))//敌人向左走
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
    else if ((enemystep[i].y == lastLocation.y) && (enemystep[i].x + 1 == lastLocation.x))//敌人向右走
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
    else if (flag1 == 1 && flag2 == 1)//如果两种方式都可以就比较分数
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

    if(score<=minscore)//如果效果更佳分数更低就采用这个
    {
        minscore=score;
        bestbar=resultbar;
    }
    }
    //循环结束返回最优板子位置
    return bestbar;
    
    //上下左右都不能放就返回默认值-1 -1 -1 -1
    
} 
Location MyPlayer::helpmove(const Location& myLoc, const Location& moveLoc, const Location& enemyLoc)//移动棋子辅助函数,主要用于遇到对方棋子时的处理
{
    if (moveLoc.distance(enemyLoc) == 0)//如果下一步恰好是对方棋子
    {
        //分别讨论上下左右四个方向以及对敌人后方挡板的以及是否会越过边界！
        if (myLoc.x == moveLoc.x && myLoc.y + 1 == moveLoc.y)//向上走
        {
            for (auto block : blocks)//遍历挡板
            {
                if (block.isH())
                {
                    if (block.start.x == enemyLoc.x - 1 || block.start.x == enemyLoc.x - 2)
                    {
                        if (block.start.y == enemyLoc.y || enemyLoc.y == SIZE)//敌人背后有挡板就没法走了选择放挡板
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
        else if (myLoc.x == moveLoc.x && myLoc.y - 1 == moveLoc.y)//向下走
        {
            for (auto block : blocks)
            {
                if (block.isH())
                {
                    if (block.start.x == enemyLoc.x - 1 || block.start.x == enemyLoc.x - 2)
                    {
                        if (block.start.y + 1 == enemyLoc.y || enemyLoc.y == 1)//向下走敌人下方是挡板
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
        else if (myLoc.y == moveLoc.y && myLoc.x + 1 == moveLoc.x)//向右走
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
        else if (myLoc.y == moveLoc.y && myLoc.x - 1 == moveLoc.x)//向左走
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
    else //如果下一步不是对方棋子就直接返回最短路的第一步
        return moveLoc;
}
// 面向过程实现结束


     // 面向过程实现开始
Step MyPlayer::nextStep(const ChessboardChange& newChange) {
    // 须知: 本示例代码仅作为 API 使用以及游戏规则了解范例, 甚至保证不了正确性, 切勿照抄照搬 
    if (mytargetY == 0) {                                // 判断并记录自己的目标
        const auto d = std::chrono::system_clock::now().time_since_epoch();
        const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
        srand(nanosecond);
        if (newChange.myLoc == PLAYER0_LOC) {                // 己方初始坐标为 (5,1) 则目标为 (x,9)
            mytargetY = PLAYER1_LOC.y;
            enemytargetY = PLAYER0_LOC.y;
        }
        else {                                             // 己方初始坐标为 (5,9) 则目标为 (x,1)
            mytargetY = PLAYER0_LOC.y;
            enemytargetY = PLAYER1_LOC.y;
        }
    }
    std::cout << newChange << std::endl;                     // 输出接收到的数据到控制台显示  
    if (!newChange.newEnemyBlockBar.isNan()) {               // 对方放置了挡板 
        BlockBar tmp = newChange.newEnemyBlockBar;
        tmp.normalization();                                 // 规范为 start 坐标小于 stop 坐标的形式 
        blocks.push_back(tmp);                         // 存储挡板 
    }
    Step step;                                               // 初始化 step 默认不移动不放板 
    int mylen = 0, enemylen = 0;
    mylen = move(newChange.myLoc, mytargetY).allsteps;
    enemylen = move(newChange.enemyLoc, enemytargetY).allsteps;
    if (mylen <= enemylen||enemylen>=8)                         //如果我的路径更短或者对方的路线足够长就选择下棋
    {
        int tem = move(newChange.myLoc, mytargetY).allsteps;
        Location moveloc = move(newChange.myLoc, mytargetY).nextstep[tem];
        //这种情况也有最短路径存在但是被对手堵住
        step.myNewLoc = helpmove(newChange.myLoc, moveloc, newChange.enemyLoc);
        if (step.myNewLoc.x == -1 &&step.myNewLoc.y==-1 && blockcounts > 0)//敌人背后是挡板就被堵死了，选择放板
        {
            BlockBar tem = putblock(newChange.myLoc, newChange.enemyLoc);
                step.myNewBlockBar = tem;
                step.myNewBlockBar.normalization();
                blocks.push_back(step.myNewBlockBar);
                blockcounts--;
        }

    }
    else                                          //如果我的路径长就挡住对手最短路线没办法挡就走棋
    {
        if (blockcounts > 0)
        {
            BlockBar tem = putblock(newChange.myLoc, newChange.enemyLoc);
            if (tem.start.x == -1&&tem.start.y==-1&&tem.stop.x==-1&&tem.stop.y==-1)//不能挡返回的板子为默认-1就走棋
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
        else//挡板已经用完了
        {
            int tem = move(newChange.myLoc, mytargetY).allsteps;
            Location moveloc = move(newChange.myLoc, mytargetY).nextstep[tem];
            step.myNewLoc = helpmove(newChange.myLoc, moveloc, newChange.enemyLoc);
        }
    }
    std::cout << step << std::endl;                          // 输出我的决策到控制台显示 
    return step;
}

void MyPlayer::restart() {
    blockcounts = 10;
    blocks.clear();
    mytargetY = 0;
    enemytargetY = 0;
}
// 面向过程实现结束


