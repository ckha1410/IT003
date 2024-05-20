#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
/// khởi tạo không gian trie gồm có số lượng nút là 10000
const int NUMBEROFNODES = 1e4;

class Trie
{
    /**

      MỘT LỚP ĐỊNH NGHĨA TRIE BAO GỒM CÁC HÀM/CẤU TRÚC LIÊN QUAN:

      * định nghĩa cấu trúc của một nút
      * hàm tạo một đỉnh gốc ban đầu
      * hàm tạo một nút mới
      * hàm duyệt dfs cây trie

    **/
public:

    struct Node
    {
        /**

          ĐỊNH NGHĨA CẤU TRÚC CỦA MỘT NÚT:
          Docstring mô tả tương tự ở file soure_code.cpp cài đặt bằng mảng

        **/

        int child[26];
        int exist, cnt;
    } nodes[NUMBEROFNODES];

    int cur;
    /** Biến cur cho biết hiện trong trie đang có bao nhiêu đỉnh **/

    Trie() : cur(0)
    {
        /**

          Tạo nút gốc cho Trie là đỉnh 0 khi khởi tạo Trie
          Docstring mô tả tương tự ở file soure_code.cpp cài đặt bằng mảng

        **/

        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };

    int new_node()
    {
        /**

          HÀM TẠO VÀ TRẢ VỀ GIÁ TRỊ CỦA ĐỈNH MỚI ĐƯỢC TẠO RA
          Docstring mô tả tương tự ở file soure_code.cpp cài đặt bằng mảng

        **/

        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }

    void add_word(string s)
    {
        /**

          HÀM THÊM MỘT CHUỖI/TỪ VÀO TRONG TRIE:
          Docstring mô tả tương tự ở file soure_code.cpp cài đặt bằng mảng

        **/

        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1)
            {
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    void dfs(int pos, string& current_string, vector<string>& res)
    {
        for (int i = 1; i <= nodes[pos].exist; i++)
            res.push_back(current_string);
        for (int i = 0; i < 26; i++) if (nodes[pos].child[i] != -1)
        {
            current_string += char(i + 'a');
            dfs(nodes[pos].child[i], current_string, res);
            current_string.pop_back();
        }
    }

    vector<string> sort_strings()
    {
        /**
            * khởi tạo một vector res lưu trữ các xâu được sắp xếp
            * thực hiện gọi hàm dfs duyệt cây trie

        **/

        vector<string> res;
        string current_string = "";
        dfs(0, current_string, res);
        return res;
    }

};

int main()
{
    /**

     NHẬP XUẤT DỮ LIỆU BẰNG FILE:

     * Nhập vào số lượng các xâu cần sắp xếp
     * Thực hiện tạo cây trie bằng cách chèn các từ vào trie
     * Thực hiện gọi hàm sắp xếp thu được kết quả vào vector ans
     * Thực hiện in các từ đã được sắp xếp trong vector ans

    **/

    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int len;
    cin >> len;

    Trie myTree;

    // vector input lưu trữ các xâu để sắp xếp
    vector<string>input(len);
    // thực hiện chèn từ vào trong trie
    for (int i = 0; i < len; i++)
    {
        cin >> input[i];
        myTree.add_word(input[i]);
    }

    // tạo vector ans lưu trữ các từ đã được sắp xếp
    vector<string> ans;
    ans = myTree.sort_strings();

    // in ra các giá trị của vector ans
    for (auto r : ans)
        cout << r << "\n";

    return 0;
}
