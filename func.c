#include <stdio.h>
#include <stdlib.h>

void rankings(int number, int ranking[], int total_score[], int x[][5])
{
    //int ranking[6]={1,1,1,1,1,1};
    //int total_score
    int i, j;
    for (i = 0; i < 6; i++)
    {
        ranking[i] = 1;
        total_score[i] = 0;
    }
    for (i = 0; i < 5; i++) //student.id
    {
        for (j = 0; j < 5; j++) //subject
        {
            if ((*((int *)x + i * 5 + j)) > (*((int *)x + number * 5 + j)))
                ranking[j]++; //single subject r anking
            total_score[i] = total_score[i] + *((int *)x + i * 5 + j);
        }
        for (i = 0; i < 5; i++)
            if (total_score[i] > total_score[number])
                ranking[5]++;
    }
}

void high_Low(int *class_high, int *class_low, int high[], int low[], int x[][5])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        high[i] = 0;
        low[i] = 101;
    }
    for (i = 0; i < 5; i++)
    {
        int temp_high = 0, temp_low = 0;
        for (j = 0; j < 5; j++)
        {
            temp_high += *((int *)x + i * 5 + j);
            temp_low += *((int *)x + i * 5 + j);
            if (high[j] < *((int *)x + i * 5 + j))
                high[j] = *((int *)x + i * 5 + j);
            if (low[j] > *((int *)x + i * 5 + j))
                low[j] = *((int *)x + i * 5 + j);
        }
        if (temp_high > *class_high)
            *class_high = temp_high;
        if (temp_low < *class_low)
            *class_low = temp_low;
    }
}

void score_scale(int scale[][5], int class_score[], int x[][5])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        int temp = 0;
        for (j = 0; j < 5; j++)
        {
            temp += x[i][j];
            int part = x[i][j] / 20;
            switch (part) //各科分数段
            {
            case 0:
                scale[0][j] += 1;
                break; //0~19
            case 1:
                scale[1][j] += 1;
                break; //20~39
            case 2:
                scale[2][j] += 1;
                break; //40~59
            case 3:
                scale[3][j] += 1;
                break; //60~79
            case 4:
                scale[4][j] += 1;
                break; //80~99
            }
        }
        class_score[temp / 100]++; //班级分数段
    }
}

int advantage(int number, int x[][5])
{
    int score = 0;
    int i;
    for (i = 0; i < 5; i++)
        if ((*((int *)x + number * 5 + i)) > score)
            score = (*((int *)x + number * 5 + i));
    return score;
}

void initScore(int arr[][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arr[i][j] = rand()%101;
        }
    }
}

void initScale(int arr[][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arr[i][j] = 0;
        }
    }
}

void initClassScore(int arr[])
{
    for (int i = 0; i < 5; i++)
    {
        arr[i] = 0;
    }
}

void print1D(int arr[])
{
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print2D(int arr[][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void printAdvantage(int id, int adv, int arr[][5])
{
    printf("优势科目: ");
    for (int i = 0; i < 5; i++)
    {
        if (arr[0][i] == adv)
        {
            switch (i)
            {
            case 1:
                printf("语文 分数: %d\n", arr[id][0]);
                break;
            case 2:
                printf("数学 分数: %d\n", arr[id][1]);
                break;
            case 3:
                printf("英语 分数: %d\n", arr[id][2]);
                break;
            case 4:
                printf("物理 分数: %d\n", arr[id][3]);
                break;
            case 5:
                printf("化学 分数: %d\n", arr[id][4]);
            }
        }
    }
}