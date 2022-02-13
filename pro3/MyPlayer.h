#pragma once
#include <vector>
#include "Player.h"
// 面向过程
namespace QuoridorUtils {
    class MyPlayer final : public Player {
    private:
        std::vector<BlockBar> blocks;                                           // 实例所需要, 可删 
        int mytargetY = 0;                                                        // 实例所需要, 可删 
        int enemytargetY = 0;
        int blockcounts = 10;
    public:
        struct node
        {
            Location nextstep[100];
            int allsteps;
        };
        MyPlayer(const std::string& key) : Player(key) { };          // 必须存在 
        Step nextStep(const ChessboardChange& newChange) override;   // 必须自行实现 
        void restart() override;                                     // 必须自行实现 
        node move(const Location& myLoc, int mytarget);//移动棋子函数，要返回最短路径的合法目标位置
        BlockBar putblock(const Location& myLoc, const Location& enemyLoc);//放置挡板函数，要返回挡板的合法起始结束坐标
        Location helpmove(const Location& myLoc, const Location& moveLoc, const Location& enemyLoc);
        bool barlegal(BlockBar bar, const Location& myLoc, const Location& enemyLoc);
    };
}

