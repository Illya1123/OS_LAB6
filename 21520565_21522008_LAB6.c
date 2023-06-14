#include<stdio.h>

int column = 0, frame = 0;
char default_ref[] ={'2','1','5','2','0','5','6','5','0','0','7'}; // MSSV là 21520565; 
int page_fault = 0;
#define MAX_SIZE 100

char arr[MAX_SIZE][MAX_SIZE];

void MeNu_Input_Arr(int frame)
{
    do
    {
        printf("---- Page Replacement algorithm ----\n");
        printf("Input page frames: ");
        scanf("%d",&frame);
        if( frame <= 0)
            printf("The values is invalid. Please enter again!\n\n");
    } while(frame <= 0 );
}

void Init_Value(char arr[MAX_SIZE][MAX_SIZE], int frame, int column)
{
    for(int j = 0; j < column ; ++j)
    {
        for(int i = 1; i <= frame; ++i)
        {
            arr[i][j] =' ';
        }
    }

    printf("Successful initialization!\n\n");
}


int main()
{
    MeNu_Input_Arr(frame);
    return 0;
}