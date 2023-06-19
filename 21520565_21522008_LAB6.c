#include<stdio.h>
#include<stdbool.h>
#define MAX_SIZE 100

int column = 0, frame, page_fault = 0;
char default_ref[] = {'2','1','5','2','0','5','6','5','0','0','7'}; // MSSV là 21520565; 
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
        char temp = getc(stdin); // xóa kí tự xuống hàng đầu tiên
        printf("Enter your referenced sequence: ");
        char ch = ' ';
        while(ch != '\n')
        {
            scanf("%c", &ch);
            if(ch != ' ' && ch != '\n')
            {
                arr[0][column++] = ch;
            }
        }
    }
}

void displayArray()
{
    for(int i  = 0; i < frame + 2 ; i++)
    {
        for(int j = 0; j < column ; j++)
            printf("%c ", arr[i][j]);

        printf("\n");
    }
}

int MeNu_Input_Arr()
{
    inputReferencedSequence();
    do
    {
        printf("---- Page Replacement algorithm ----\n");
        printf("Input page frames: ");
        scanf("%d",&frame);
        if( frame <= 0)
            printf("The values is invalid. Please enter again!\n\n");
    } while(frame <= 0 );
    
    // khởi tạo rỗng cho các giá trị
    Init_Value();

    int choice = 0;
    // choose algorithm
    printf("---- Page Replacement algorithm ----\n");
    printf("1.FIFO algorithm\n");
    printf("2.OPT algorithm\n");
    printf("3.LRU algorithm\n");
    
    do {
         printf("Enter your choice: ");
        scanf("%d", &choice);
    } while(choice != 1 && choice != 2 && choice != 3);

    return choice;
}

void Init_Value()
{
    for(int j = 0; j < column ; ++j)
    {
        for(int i = 1; i <= frame + 1; ++i)
        {
            arr[i][j] = ' ';
        }
    }
}

// move the values of previous column into current column
void copy_preColumn(int cur_col)
{
    for(int i = 1; i <= frame; ++i)
    {
        arr[i][cur_col] = arr[i][cur_col - 1];
    }
}

// check the values is in frames?
bool Check_Exists_Page(int cur_col, char value)
{
    // trả về false nếu có lỗi trang
    for(int i = 1; i <= frame; ++i)
    {
        if(arr[i][cur_col] == value)
            return true;
    }
    return false;
}

bool isCheckedPage(char checkpage[MAX_SIZE], char page, int num)
{
    for(int i = 0; i < num ; i++)
        if(checkpage[i] == page)
            return true;
    return false;
}

void FIFO() {
    int pos = 1;
    for(int i = 0; i < column ; i++)
    {
        if(i == 0) // xử lí riêng trang đầu tiên
        {
            // trang đầu tiên chắc chắn có lỗi trang
            page_fault++;
            pos++;
            arr[1][i] = arr[0][i];
            arr[frame+1][i] = '*';
        }
        else {
            // copy giá trị của cột trước gán cho cột hiên tại
            copy_preColumn(i);
            // kiểm tra giá trị page hiện tại có nằm trong các frame hay không
            if(!Check_Exists_Page(i, arr[0][i]))
            {
                arr[pos++][i] = arr[0][i];
                arr[frame+1][i] = '*';
                page_fault++;
                if(pos > frame)
                    pos = 1;
            }
        }        
    }
}

void LRU() {
    char pageReplace = ' ';
    int count = 0;
    for(int i = 0; i < column ; i++)
    {
        if(i == 0) // xử lí riêng trang đầu tiên
        {
            // trang đầu tiên chắc chắn có lỗi trang
            page_fault++;
            arr[1][i] = arr[0][i];
            arr[frame+1][i] = '*';
        }
        else {
            copy_preColumn(i);
            //kiểm tra lỗi trang
            if(!Check_Exists_Page(i , arr[0][i]))
            {
                char checkedpage[MAX_SIZE];
                
                if(i < frame)
                {
                    arr[i+1][i] = arr[0][i];
                }
                else {
                    // tìm đến trang lâu nhất chưa sử dụng 
                    for(int j = i - 1 ; j >= 0 ; j--)
                    {
                        if(!isCheckedPage(checkedpage, arr[0][j], count) && Check_Exists_Page(i, arr[0][j]))
                        {
                            pageReplace = arr[0][j];
                            checkedpage[count++] = arr[0][j];
                        }
                        if(count == frame)
                            break;
                    } 

                    // duyệt trong các frame hiện tại để tìm ra trang thay thế 
                    for(int f = 1; f <= frame ; f++)
                    {
                        if(arr[f][i] == pageReplace)
                        {
                            arr[f][i] = arr[0][i];
                            break;
                        }
                    }                 
                }

                arr[frame+1][i] = '*';
                count = 0;     
                pageReplace = ' ';                  
                page_fault++;
            }
        }
    }
}

void OPT() {
    char pageReplace = ' ';
    int count = 0;
    for(int i = 0; i < column ; i++)
    {
        if(i == 0) // xử lí riêng trang đầu tiên
        {
            // trang đầu tiên chắc chắn có lỗi trang
            page_fault++;
            arr[1][i] = arr[0][i];
            arr[frame+1][i] = '*';
        }
        else {
            copy_preColumn(i);
            //kiểm tra lỗi trang
            if(!Check_Exists_Page(i , arr[0][i]))
            {
                char checkedpage[MAX_SIZE];
                
                if(i < frame)
                {
                    arr[i+1][i] = arr[0][i];
                }
                else {
                    // tìm đến trang còn lâu mới sử dụng
                    for(int j = i + 1 ; j < column; j++)
                    {
                        if(!isCheckedPage(checkedpage, arr[0][j], count) && Check_Exists_Page(i, arr[0][j]))
                        {
                            pageReplace = arr[0][j];
                            checkedpage[count++] = arr[0][j];
                        }
                        if(count == frame)
                            break;
                    } 

                    // xảy ra trường hợp là một trang không còn được sử dụng nữa 
                    if(count != frame)
                    {
                        for(int f = 1; f <= frame ; f++)
                        {
                            if(!isCheckedPage(checkedpage, arr[f][i], count))
                            {
                                arr[f][i] = arr[0][i];
                                break;
                            }
                        }
                    }
                    else {
                           // duyệt trong các frame hiện tại để tìm ra trang thay thế 
                        for(int f = 1; f <= frame ; f++)
                        {
                            if(arr[f][i] == pageReplace)
                            {
                                arr[f][i] = arr[0][i];
                                break;
                            }
                        }         
                    }                         
                }

                arr[frame+1][i] = '*';
                count = 0;     
                pageReplace = ' ';                  
                page_fault++;
            }
        }
    }
}

int main()
{
    int choice = MeNu_Input_Arr();
    switch (choice)
    {
        case 1:
        {
            FIFO();
            break;
        }
        case 2:
        {
            OPT();
            break;
        }
        case 3:
        {   
            LRU();
            break;
        }        
        default:
            break;
    }

    // hiển thị mảng kết quả ra màn hình
    displayArray();
    printf("\nNumber of Page Fault: %d", page_fault);
    return 0;
}