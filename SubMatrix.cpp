#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int m, n;
    cout << "[請輸入二維矩陣的長寬]\n"
         << "長:";
    cin >> m;
    cout << "寬:";
    cin >> n;

    vector<int> width(m + 1);
    vector<vector<int>> matrix(n, width);

    //輸入矩陣
    for (size_t i = 0; i < m; i++)
    {
        cout << "請輸入矩陣第" << i + 1 << "排數字：\n";
        for (int j = 0; j < n; j++)
        {
            int mn;
            cin >> mn;
            matrix[i][j] = mn;
        }
    }

    // cout輸入矩陣
    cout << "輸入矩陣為：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    //排列出每一列矩陣
    int submax = -100;
    int total = 0;
    vector<vector<int>> submatrix;
    vector<int> putin;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            for (size_t h = j; h < n; h++)
            {
                total = total + matrix[i][h];
                putin.push_back(total);
            }
            total = 0;
        }
        submatrix.push_back(putin);
        putin.clear();
    }

    //計算每一列有幾種選取方式（階層）
    int count = 0;
    for (size_t i = 0; i < n; i++)
        count = count + i + 1;

    int subtotal = 0;
    cout << "\nAnswer:";
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < submatrix.size(); j++)
        {
            for (size_t h = j; h < submatrix.size(); h++)
            {
                subtotal = subtotal + submatrix[h][i];
                if (submax < subtotal)
                    submax = subtotal;
            }
            subtotal = 0;
        }
    }

    cout << endl;
    cout << "子矩陣最大值：" << submax;

    return 0;
}