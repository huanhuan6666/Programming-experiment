#pragma once
#include <vector>
#include "Player.h"
// �������
namespace QuoridorUtils {
    class MyPlayer final : public Player {
    private:
        std::vector<BlockBar> blocks;                                           // ʵ������Ҫ, ��ɾ 
        int mytargetY = 0;                                                        // ʵ������Ҫ, ��ɾ 
        int enemytargetY = 0;
        int blockcounts = 10;
    public:
        struct node
        {
            Location nextstep[100];
            int allsteps;
        };
        MyPlayer(const std::string& key) : Player(key) { };          // ������� 
        Step nextStep(const ChessboardChange& newChange) override;   // ��������ʵ�� 
        void restart() override;                                     // ��������ʵ�� 
        node move(const Location& myLoc, int mytarget);//�ƶ����Ӻ�����Ҫ�������·���ĺϷ�Ŀ��λ��
        BlockBar putblock(const Location& myLoc, const Location& enemyLoc);//���õ��庯����Ҫ���ص���ĺϷ���ʼ��������
        Location helpmove(const Location& myLoc, const Location& moveLoc, const Location& enemyLoc);
        bool barlegal(BlockBar bar, const Location& myLoc, const Location& enemyLoc);
    };
}

