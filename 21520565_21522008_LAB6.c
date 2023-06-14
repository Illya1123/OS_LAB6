#include<stdio.h>

int column = 0, frame = 0;
char default_ref[] = {'2','1','5','2','0','5','6','5','0','0','7'}; // MSSV là 21520565; 
int page_fault = 0;
#define MAX_SIZE 100

char arr[MAX_SIZE][MAX_SIZE];

void inputReferencedSequence() {
    int choice = 0;
    printf("---Page Replacement algorithm---\n");
    printf("1.Default referenced sequence\n");
    printf("2.Manual input sequence\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while(choice != 1 && choice != 2);

    if(choice == 1)
    {
        // dán chuỗi tham chiếu mặc định cho hàng đầu tiên của mảng và tăng giá trị biến column
        for(int i = 0; i < 11 ; i++)
        {
            arr[0][i] = default_ref[i];
            column++;
        }
    }
    else {
        // cho vòng lặp để người dùng tự nhập vào chuỗi tham chiếu của mình 
        printf("Enter the number of pages: ");
        scanf("%d", &column);
        printf("Enter your referenced sequence: ");
        int i = 0;
        while(i < column)
        {
            char ch;
            scanf("%c", &ch);
            if(ch != ' ' && ch != '\n')
            {
                arr[0][i++] = ch;
            }
        }
    }
}

void displayArray (char arr[MAX_SIZE][MAX_SIZE], int rows , int columns)
{
    for(int i  = 0; i < rows ; i++)
    {
        for(int j = 0; j < columns ; j++)
            printf("%c ", arr[i][j]);

        printf("\n");
    }
}


int main()
{

    inputReferencedSequence();
    displayArray(arr, 1, column);
    return 0;
}