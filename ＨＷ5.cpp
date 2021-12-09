#include <iostream>
using namespace std;
void show(int n, int a[], int b[], int c[])
{
    cout << "A柱\t"
         << "B柱\t"
         << "C柱" << endl;
    for (int i = n; i >= 0; i--)
    {
        cout << a[i] << "\t" << b[i] << "\t" << c[i] << endl;
    }
    cout << "-------------------------------\n";
}

int main()
{
    int n; //多少盤子
    cout << "請輸入要挑戰多少個圓盤？";
    cin >> n;

    int a[n + 1], origina[n + 1]; //a跟移動前狀態
    int b[n + 1], originb[n + 1]; //b跟移動前狀態
    int c[n + 1], originc[n + 1]; //c跟移動前狀態

    while (n != EOF)
    {
        if (cin.fail())
        {
            cout << "Not a number!!" << endl;
            cin.clear();
            cin.ignore();
            cout << "請輸入要挑戰多少個圓盤？";
            cin >> n;
        }
        else
        { //將全部圓盤放到Ａ柱
            for (int i = n; i >= 0; i--)
            {
                a[i] = n - i;
                b[i] = 0;
                c[i] = 0;
            }
            break;
        }
    }

    //遊戲開始
    int finish = 0;
    while (finish == 0)
    {
        show(n, a, b, c);

        //儲存 移動前的狀態
        for (int i = 0; i < n + 1; i++)
        {
            //循序逐個元素進行複製
            origina[i] = a[i];
            originb[i] = b[i];
            originc[i] = c[i];
        }

        //玩家輸入移動項目
        char tower;
        int disk;
        cout << "請輸入要移動的圓盤：";
        cin >> disk;
        if (cin.fail())
        {
            cout << "Not a number!!" << endl;
            cin.clear();
            cin.ignore();
            continue;
        }

        cout << "請輸入要移動到哪個柱？";
        cin >> tower;

        //Pop
        int dopop = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] == disk && a[i + 1] == 0)
            {
                a[i] = 0;
                dopop = 1;
                break;
            }
            else if (b[i] == disk && b[i + 1] == 0)
            {
                b[i] = 0;
                dopop = 1;
                break;
            }
            else if (c[i] == disk && c[i + 1] == 0)
            {
                c[i] = 0;
                dopop = 1;
                break;
            }
        }

        //Push
        if (dopop == 1)
        {
            switch (tower)
            {
            case 'A': //A柱移入圓盤
            case 'a':
                for (int i = n - 1; i >= 0; i--)
                {
                    if (a[i] != 0 && a[i] > disk)
                    {
                        a[i + 1] = disk;
                        break;
                    }
                    else if (a[0] == 0)
                    {
                        a[0] = disk;
                        break;
                    }
                    else
                    {
                        if (i == 0)
                        {
                            cout << "A柱上方圓盤數字較大！！" << endl;
                            cout << "-------------------------------" << endl;
                            for (int i = 0; i < n + 1; i++)
                            {
                                a[i] = origina[i];
                                b[i] = originb[i];
                                c[i] = originc[i];
                            }
                        }
                    }
                }
                break;
            case 'B': //B柱移入圓盤
            case 'b':
                for (int i = n - 1; i >= 0; i--)
                {
                    if (b[i] != 0 && b[i] > disk)
                    {
                        b[i + 1] = disk;
                        break;
                    }
                    else if (b[0] == 0)
                    {
                        b[0] = disk;
                        break;
                    }
                    else
                    {
                        if (i == 0)
                        {
                            cout << "B柱上方圓盤數字較大！！" << endl;
                            cout << "-------------------------------" << endl;
                            for (int i = 0; i < n + 1; i++)
                            {
                                a[i] = origina[i];
                                b[i] = originb[i];
                                c[i] = originc[i];
                            }
                        }
                    }
                }
                break;
            case 'C': //C柱移入圓盤
            case 'c':
                for (int i = n - 1; i >= 0; i--)
                {
                    if (c[i] != 0 && c[i] > disk)
                    {
                        c[i + 1] = disk;
                        break;
                    }
                    else if (c[0] == 0)
                    {
                        c[0] = disk;
                        break;
                    }
                    else
                    {
                        if (i == 0)
                        {
                            cout << "C柱上方圓盤數字較大！！" << endl;
                            cout << "-------------------------------" << endl;
                            for (int i = 0; i < n + 1; i++)
                            {
                                a[i] = origina[i];
                                b[i] = originb[i];
                                c[i] = originc[i];
                            }
                        }
                    }
                }
                break;
            default:
                cout << "輸入錯誤，請再輸入一次：\n";
                cout << "-------------------------------" << endl;
                for (int i = 0; i < n + 1; i++)
                {
                    a[i] = origina[i];
                    b[i] = originb[i];
                    c[i] = originc[i];
                }
                break;
            }
        }
        else
        {
            cout << "圓盤" << disk << "上方還有圓盤或輸入錯誤!!" << endl;
            cout << "-------------------------------" << endl;
            continue;
        }

        if (c[n - 1] == 1)
        {
            finish = 1;
            cout << "YOU WIN!!!!!";
            show(n, a, b, c);
        }
    }
    return 0;
}