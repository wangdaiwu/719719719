#include <stdio.h>
#include <stdlib.h>

void rankings(int number, int ranking[], int total_score[], int x[][5]);
void high_Low(int *class_high, int *class_low, int high[], int low[], int x[][5]);
void score_scale(int scale[][5], int class_score[], int x[][5]);
int advantage(int number, int x[][5]);
void initScore(int arr[][5]);
void initScale(int arr[][5]);
void initClassScore(int arr[]);
void print1D(int arr[]);
void print2D(int arr[][5]);
void printAdvantage(int id, int adv, int arr[][5]);
