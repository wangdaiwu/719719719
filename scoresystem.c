#include "head2.h"

int score[5][5];


void scoreSystem()
{
    printf("请选择查询内容: \n");
    printf("1.班级分数段\n");
    printf("2.班级最高/低分 科目最高/低分\n");
    printf("3.学生成绩分析\n");
    printf("others.退出系统\n");
    int choice = -1;
    initScore(score);
    while (1)
    {
        scanf("%d", &choice);

        if (choice == 1)
        {
            int scale[5][5];
            int class_score[5];
            initScale(scale);
			//printf("1\n");
            initClassScore(class_score);
			//printf("1\n");
            score_scale(scale, class_score, score);
            //printf("1\n");
            printf("班级分数段: ");
            print1D(class_score);
            printf("\n各科分数段\n");
            print2D(scale);
        }
        
        else if (choice == 2)
        {
            int class_high = -1, class_low = INT_MAX;
            int high[5], low[5];
            high_Low(&class_high, &class_low, high, low, score);
            printf("班级最高分: %d, 班级最低分: %d\n", class_high, class_low);
            printf("各科最高分: ");
            print1D(high);
            printf("\n各科最低分: ");
            print1D(low);
            printf("\n");
        }

        else if (choice == 3)
        {
            printf("输入学生ID: ");
            int id;
            scanf("%d", &id);
            id--;

            int rank[6], total_score[6];
            rankings(id, rank, total_score, score);

            printf("总成绩排名: %d\n", rank[5]);
            printf("各科成绩排名: ");
            print1D(rank);

            int adv;
            adv = advantage(id, score);
            printAdvantage(id, adv, score);
        }

        else
        {
            return;
        }
    }
}
