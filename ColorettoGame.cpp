#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
void showcolor(int a)
{
    switch (a)
    {
    case 0:
        cout << "Gray";
        break;
    case 1:
        cout << "Yellow";
        break;
    case 2:
        cout << "Orange";
        break;
    case 3:
        cout << "Blue";
        break;
    case 4:
        cout << "Brown";
        break;
    case 5:
        cout << "Pink";
        break;
    case 6:
        cout << "Green";
        break;
    case 7:
        cout << "Joker";
        break;
    case 8:
        cout << "+Two";
        break;
    }
}

bool most3(int players, vector<vector<int>> row, vector<int> takerow)
{
    int is3 = 0;
    for (size_t i = 0; i < row.size(); i++)
    {
        if (row[i].size() == 3)
            is3++;
        else if (find(takerow.begin(), takerow.end(), i) != takerow.end())
            is3++;
    }

    if (is3 == row.size())
        return true;
    else
        return false;
}

int main()
{
    srand(time(0));
    int players;
    int colors[9] = {9, 9, 9, 9, 9, 9, 9, 3, 10}; //＊＊記得改
    vector<vector<int>> player;
    vector<int> playercard(9, 0);
    vector<vector<int>> row;
    vector<int> rowcard;
    vector<int> supply;

    cout << "請輸入幾位玩家: ";
    cin >> players;

    //七種顏色卡各9張，彩色卡3張，+2分卡10張
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < colors[i]; j++)
            supply.push_back(i);
    }

    //洗牌
    for (int i = 0; i < 76; i++)              //＊＊記得改
        swap(supply[i], supply[rand() % 76]); //＊＊記得改

    //遊戲開始先發一張牌
    for (int j = 0; j < players; j++)
    {
        playercard[supply.back()]++;
        player.push_back(playercard);
        playercard[supply.back()]--;
        supply.pop_back();
        row.push_back(rowcard);
    }
    cout << "[遊戲開始，各發一張牌給玩家]";

    //show出每一人的牌
    cout << "\nColor    Gray    Yellow  Orange   Blue   Brown    Pink   Green    Joker  +Two" << endl;
    for (int j = 0; j < players; j++)
    {
        cout << "Player" << j + 1 << ":   ";
        for (int i = 0; i < 9; i++)
        {
            cout << player[j][i] << "       ";
        }
        cout << endl;
    }

    //遊戲開始
    int finish = 0;
    int action;
    vector<int> turn(players, 0);
    vector<int> takerow(players, -1);
    int round = 0;
    while (finish == 0)
    {
        //如果還有人沒拿牌就繼續
        while (find(turn.begin(), turn.end(), 0) != turn.end())
        {
            for (int i = 0; i < players; ++i)
            {
                //跳過已經拿牌的玩家
                if (turn[i] == 0)
                {
                    //判斷是否為最後一局
                    if (supply.size() == 15)
                    {
                        cout << "----------------------------------------------------------------------------------\n";
                        cout << "[這是最後一局囉！]" << endl;
                        finish = 1;
                    }
                    cout << "----------------------------------------------------------------------------------";

                    /*判斷桌上是否有牌*/
                    //行列卡皆無卡
                    int rowempty = 0;
                    for (size_t k = 0; k < row.size(); k++)
                    {
                        if (row[k].empty())
                            rowempty++;
                    }

                    if (rowempty == row.size())
                    {
                        cout << "\nPlayer" << i + 1 << "抽牌：";
                        action = 1;
                    }
                    //行列卡皆已滿
                    else if (most3(players, row, takerow))
                    {
                        //player選擇抽牌或拿牌
                        cout << "\nPlayer" << i + 1 << " 行列卡上皆滿或已拿取了唷，";
                        action = 2;
                    }
                    else
                    {
                        //player選擇抽牌或拿牌
                        cout << "\nPlayer" << i + 1 << " 請輸入1(抽牌) or 2(拿牌):";
                        cin >> action;
                    }

                    switch (action)
                    {
                    case 1:
                        cout << "[";
                        showcolor(supply.back());
                        cout << "] 要放置到第幾排？";
                        int place;
                        while (cin >> place)
                        {
                            if (place > players || place < 0)
                            {
                                cout << "[輸入錯誤，請重新輸入要放置到第幾排？";
                            }
                            else if (row[place - 1].size() == 3)
                            {
                                cout << "Row" << place << "已經滿了唷，請重新輸入要放置到第幾排？";
                            }
                            else if (find(takerow.begin(), takerow.end(), place - 1) != takerow.end())
                            {
                                cout << "Row" << place << "拿過就不能再放囉，請重新輸入要放置到第幾排？";
                            }
                            else
                            {
                                row[place - 1].push_back(supply.back());
                                supply.pop_back();
                                break;
                            }
                        }
                        break;
                    case 2:
                        cout << "要拿取第幾排？";
                        int take;
                        while (cin >> take)
                        {
                            //輸入的row已被拿取過
                            if (find(takerow.begin(), takerow.end(), take - 1) != takerow.end())
                            {
                                cout << "Row" << take << "已拿取過，請重新輸入要拿取第幾排？";
                            }
                            else
                            {
                                //玩家取牌
                                for (int takerow = 0; takerow < row[take - 1].size(); takerow++)
                                    player[i][row[take - 1][takerow]]++;
                                //清空行列卡，此局不能再使用
                                vector<int>().swap(row[take - 1]);
                                takerow[i] = take - 1;
                                //玩家結束此局
                                turn[i] = 1;
                                break;
                            }
                        }
                        break;
                    default:
                        cout << "[輸入錯誤，請再輸入一次]" << endl;
                        i--;
                        break;
                    }

                    //將結果印出來
                    for (int m = 0; m < row.size(); m++)
                    {
                        cout << "Row " << m + 1 << ": ";
                        for (int n = 0; n < row[m].size(); n++)
                        {
                            showcolor(row[m][n]);
                            cout << " ";
                        }
                        cout << endl;
                    }

                    cout << "Color    Gray    Yellow  Orange   Blue   Brown    Pink   Green    Joker  +Two" << endl;
                    for (int g = 0; g < players; g++)
                    {
                        cout << "Player" << g + 1 << ":   ";
                        for (int h = 0; h < 9; h++)
                            cout << player[g][h] << "       ";
                        cout << endl;
                    }
                }
            }
        }
        vector<int>(players, 0).swap(turn);
        vector<int>(players, -1).swap(takerow);
    }

    cout << "----------------------------------------------------------------------------------\n";
    cout << "[遊戲結束！]" << endl;
    cout << "----------------------------------------------------------------------------------\n";

    //計分-計算兩分卡
    vector<int> score(players, 0);
    for (int i = 0; i < players; i++)
    {
        score[i] = player[i].back() * 2;
        player[i].pop_back();
    }

    //先將牌卡數量從大排到小 彩色卡不加入排列
    for (int i = 0; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].size() - 1; j++)
        {
            for (int h = 0; h < player[i].size() - 1; h++)
            {
                if (player[i][h] < player[i][j])
                {
                    swap(player[i][h], player[i][j]);
                }
            }
        }
    }

    //計算色卡分數
    for (int j = 0; j < player.size(); j++)
    {
        //分配彩色卡
        while (player[j].back() > 0)
        {
            for (int h = 0; h < player[j].size(); h++)
            {
                if (player[j][h] < 6)
                {
                    player[j][h]++;
                    player[j].back()--;
                    break;
                }
            }
        }

        //分數加上所有色卡分數
        for (int m = 0; m < player[j].size(); m++)
        {
            if (m < 3)
            {
                if (player[j][m] >= 6)
                    score[j] = score[j] + 21;
                else if (player[j][m] == 5)
                    score[j] = score[j] + 15;
                else if (player[j][m] == 4)
                    score[j] = score[j] + 10;
                else if (player[j][m] == 3)
                    score[j] = score[j] + 6;
                else if (player[j][m] == 2)
                    score[j] = score[j] + 3;
                else
                    score[j] = score[j] + player[j][m];
            }
            else
            {
                if (player[j][m] >= 6)
                    score[j] = score[j] - 21;
                else if (player[j][m] == 5)
                    score[j] = score[j] - 15;
                else if (player[j][m] == 4)
                    score[j] = score[j] - 10;
                else if (player[j][m] == 3)
                    score[j] = score[j] - 6;
                else if (player[j][m] == 2)
                    score[j] = score[j] - 3;
                else
                    score[j] = score[j] - player[j][m];
            }
        }
        cout << "Player" << j + 1 << ":   " << score[j] << endl;
    }

    cout << "重新排列：" << endl;
    for (int g = 0; g < players; g++)
    {
        cout << "Player" << g + 1 << ":   ";
        for (int h = 0; h < player[g].size(); h++)
        {
            cout << player[g][h] << "       ";
        }
        cout << endl;
    }

    //判斷獲勝者
    int highscore = -100;
    int winner = -1;
    for (int i = 0; i < players; i++)
    {
        if (score[i] > highscore)
        {
            highscore = score[i];
            winner = i;
        }
    }
    cout << "[獲勝者是： Player" << winner + 1 << "!!!!]";

    return 0;
}