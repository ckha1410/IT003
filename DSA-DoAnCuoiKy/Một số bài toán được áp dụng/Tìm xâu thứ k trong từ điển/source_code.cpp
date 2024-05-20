/**
    BÀI TOÁN: Cho một danh sách từ điển gồm các xâu, thực hiện tìm kiếm xâu thứ k trong danh sách từ điển đó

    PHƯƠNG PHÁP:
        * Xây dựng cây trie từ danh sách xâu đầu vào
        * Ở đỉnh hiện tại đang xét, ta sử dụng biến đếm cnt ở mỗi đỉnh con để xác định kí tự tiếp theo của xâu đáp án là gì. 
          Sau đó di chuyển xuống đỉnh con đó để tiếp tục tìm kí tự tiếp theo.

    XÂY DỰNG CHƯƠNG TRÌNH CÓ BỘ DỮ LIỆU NHẬP/XUẤT TỪ FILE:
        * Dữ liệu vào: Đọc từ file "input.txt" có cấu trúc như sau:
            - Dòng đầu tiên chứa 2 số nguyên gồm len là số lượng danh sách từ điển các xâu, k là số thứ tự của xâu cần tìm kiếm
            - len dòng tiếp theo là các từ có trong danh sách
        * Dữ liệu ra: Ghi vào file "output.txt" một dòng duy nhất là xâu thứ k trong danh sách từ điển

**/

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

    string find_k_string(int k)
    {
        /**
            HÀM THỰC HIỆN TÌM XÂU THỨ K CÓ TRONG TỪ ĐIỂN
        **/
        
        int pos = 0;
        string res = "";

        while (true)
        {
            if (nodes[pos].exist >= k) break;
            k -= nodes[pos].exist;

            for (int i = 0; i < 26; i++)
                if (nodes[pos].child[i] != -1)
                {
                    int nxt = nodes[pos].child[i];
                    if (nodes[nxt].cnt >= k)
                    {
                        res += char(i + 'a');
                        pos = nxt;
                        break;
                    }
                    k -= nodes[nxt].cnt;
                }
        }
        return res;
    }

};

int main()
{
    /**

     NHẬP XUẤT DỮ LIỆU BẰNG FILE:

     * Nhập vào len là số lượng các từ và k là số thứ tự của xâu cần tìm kiếm
     * Thực hiện tạo cây trie bằng cách chèn các từ vào trie
     * Thực hiện gọi hàm find_k_string() để tìm kiếm xâu thứ k trong danh sách từ điển đã tạo
     * Thực hiện in kết quả tìm kiếm

    **/

    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int len, k;
    cin >> len >> k;

    Trie myTree;

    // vector input lưu trữ các từ để truy vấn
    vector<string>input(len);
    // thực hiện chèn từ vào trong trie
    for (int i = 0; i < len; i++)
    {
        cin >> input[i];
        myTree.add_word(input[i]);
    }

    // khai báo một xâu ans nhận kết quả là xâu thứ k sau khi thực hiện hàm find_k_string()
    string ans;
    ans = myTree.find_k_string(k);

    // thực hiện in kết quả
    cout << ans;

    return 0;
}
