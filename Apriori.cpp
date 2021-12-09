#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    cout << "請輸入欲開啟的檔案：";
    string filename;
    cin >> filename;

    //讀取檔案
    vector<string> fileitem;
    vector<vector<string>> fileitems;
    ifstream ifs(filename, ios::in);
    if (!ifs.is_open())
    {
        cout << "Failed to open file.\n";
    }
    else
    {
        string s;
        while (getline(ifs, s))
        {
            //push_back索引6數起之後的1個字元
            int pos = s.find(" ");
            fileitem.push_back(s.substr(pos + 1, 1));
            while (s.find(",") != string::npos)
            {
                pos = s.find(",");
                //從s.find(",")這個位置開始，push_back1個字符
                fileitem.push_back(s.substr(pos + 1, 1));
                s.erase(pos, 1);
            }
            fileitems.push_back(fileitem);
            fileitem.clear();
        }
        ifs.close();
    }

    for (size_t i = 0; i < fileitems.size(); i++)
    {
        for (size_t j = 0; j < fileitems[i].size(); j++)
        {
            cout << fileitems[i][j] << " ";
        }
        cout << endl;
    }

    //輸入關聯參數的門檻值
    double min_supp, min_conf;
    cout << "請輸入Support參數的門檻值：";
    cin >> min_supp;
    cout << "請輸入Confidence參數的門檻值:";
    cin >> min_conf;

    /*每筆資料的取值組合有2^fileitems[i].size()種
    例  ＡＢＣ
        0 0 0    Ａ 0,1 4個一輪
        0 0 1    Ｂ 0,1 2個一輪
        0 1 0    Ｃ 0,1 1個一輪
        0 1 1
        1 0 0
        1 0 1
        1 1 0 
        1 1 1
    */

    vector<vector<string>> allcc; //記錄每筆資料取值組合
    vector<string> allcomb;       //記錄每種取值組合
    vector<string> allcomb_i;     //記錄每種取值組合出現在第幾筆資料

    for (size_t i = 0; i < fileitems.size(); i++)
    {
        //依第y個元素計算0,1出現次數
        vector<int> TT;
        int t = pow(2, fileitems[i].size());
        for (size_t y = 0; y < fileitems[i].size(); y++)
        {
            t = t / 2;
            TT.push_back(t);
        }

        vector<bool> c(TT.size(), false); //取值(0,0,0)
        vector<string> cc;                //記錄取值組合
        for (size_t y = 0; y < pow(2, fileitems[i].size()); y++)
        {
            //計算取值情況(0,0,0)
            for (size_t m = 0; m < TT.size(); m++)
            {
                if (y % TT[m] == 0 && y != 0)
                    c[m] = !c[m];
            }
            //依取值轉換成商品組合(1or0表示有or無此商品)
            string cstring;
            for (size_t m = 0; m < fileitems[i].size(); m++)
            {
                if (c[m] == 0)
                {
                    cstring = cstring + fileitems[i][m];
                }
            }

            if (!cstring.empty())
            {
                cc.push_back(cstring);
                vector<string>::iterator it = find(allcomb.begin(), allcomb.end(), cstring);
                if (it == allcomb.end())
                {
                    allcomb.push_back(cstring);
                    string c_count = to_string(i);
                    allcomb_i.push_back(c_count);
                }
                else
                {
                    string c_count = to_string(i);
                    allcomb_i[it - allcomb.begin()] = allcomb_i[it - allcomb.begin()] + c_count;
                }
            }
            cstring.clear();
        }
        vector<int>(TT.size(), 0).swap(TT);
        allcc.push_back(cc);
    }

    //計算超過Support門檻的商品組是否有超過Confidence門檻
    vector<vector<string>> conf;
    vector<string> conf_content;
    for (size_t i = 0; i < allcc.size(); i++)
    {
        for (size_t j = 0; j < allcc[i].size(); j++)
        {
            //尋找allcc的元素在allcomb的位址
            vector<string>::iterator it = find(allcomb.begin(), allcomb.end(), allcc[i][j]);
            //計算Support
            double supp = double(allcomb_i[it - allcomb.begin()].size()) / double(fileitems.size());
            if (supp >= min_supp)
            {
                //計算Confidence
                for (size_t m = 0; m < allcc[i].size(); m++)
                {
                    //計算比對標的的support  allcc[i][j],it是先決條件商品的組合及迭代器，allcc[i][m],it2是次要條件商品的組合及迭代器
                    vector<string>::iterator it2 = find(allcomb.begin(), allcomb.end(), allcc[i][m]);
                    double supp2 = double(allcomb_i[it2 - allcomb.begin()].size()) / double(fileitems.size());

                    //檢查組合裡的商品是否重複
                    int repeat = 0;
                    for (size_t p = 0; p < allcc[i][j].size(); p++)
                    {
                        if (allcc[i][m].find(allcc[i][j][p]) != string::npos)
                        {
                            repeat = 1;
                        }
                    }
                    //重複就跳過
                    if (repeat == 1)
                        continue;

                    //計算兩個之間的confidence
                    int count2 = 0;
                    for (size_t p = 0; p < allcomb_i[it2 - allcomb.begin()].size(); p++)
                    {
                        if (allcomb_i[it - allcomb.begin()].find(allcomb_i[it2 - allcomb.begin()][p]) != string::npos)
                        {
                            count2++;
                        }
                    }

                    double confidence = double(count2) / double(allcomb_i[it - allcomb.begin()].size());

                    //若皆超過兩個統計值的門檻
                    if (confidence >= min_conf && supp2 >= min_supp)
                    {
                        conf_content.push_back(allcc[i][j]); //conf_content[0]記錄先決條件商品的組合
                        conf_content.push_back(allcc[i][m]); //conf_content[1]記錄次要條件商品的組合

                        //若
                        if (confidence > 1)
                        {
                            string D = to_string(allcomb_i[it - allcomb.begin()].size());
                            conf_content.push_back(D); //conf_content[2]記錄先決條件商品的組合出現次數
                            conf_content.push_back(D); //conf_content[3]記錄先決條件商品的組合出現次數
                        }
                        else
                        {
                            string D = to_string(count2);
                            conf_content.push_back(D);
                            string D2 = to_string(allcomb_i[it - allcomb.begin()].size());
                            conf_content.push_back(D2);
                        }

                        //尋找有無重複紀錄
                        vector<vector<string>>::iterator it3 = find(conf.begin(), conf.end(), conf_content);
                        if (it3 == conf.end())
                        {
                            conf.push_back(conf_content);
                            conf_content.clear();
                        }
                        else
                            conf_content.clear();
                    }
                    else
                        continue;
                }
            }
            else
                continue;
        }
    }

    for (size_t i = 0; i < conf.size(); i++)
    {
        cout << conf[i][0] << " -> " << conf[i][1] << " (" << conf[i][2] << "/" << conf[i][3] << ")" << endl;
    }
}