/**
    BÀI TOÁN: Cho một danh sách các số, tìm XOR lớn nhất giữa các số trong danh sách và một giá trị x cho trước 

    XÂY DỰNG CHƯƠNG TRÌNH CÓ BỘ DỮ LIỆU NHẬP/XUẤT TỪ FILE:
        * Dữ liệu vào: Đọc từ file "input.txt" có cấu trúc như sau:
            - Dòng đầu tiên chứa 2 số nguyên gồm len là số lượng danh sách các số, x là số nguyên cho trước cần tìm XOR lớn nhất
            - Dòng tiếp theo gồm len số có trong danh sách, mỗi số cách nhau ít nhất 1 dấu cách
        * Dữ liệu ra: Ghi vào file "output.txt" một dòng duy nhất là kết quả XOR lớn nhất tìm được

**/

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
const int NUMBEROFNODES = 1e4;
const int LG = 31;
class Trie
{
    /**
        THỰC HIỆN XÂY DỰNG LỚP TRIE BAO GỒM CÁC HÀM LIÊN QUAN:

        * Xác định cấu trúc của một nút
        * Hàm tạo một nút mới
        * Hàm thêm một số vào trie
        * Hàm tìm kết quả XOR lớn nhất
        
    **/

    public:
    struct Node
    {
        /**

           XÁC ĐỊNH CẤU TRÚC CỦA MỘT NÚT:
           * Tương tự với trie lưu chuỗi nhưng mảng con trỏ có kích thước là 2
           * Biến data có kiểu là số nguyên (0 hoặc 1)
           * Một cờ để đánh dấu là nút chứa bit kết thúc trong dãy bit

        **/

        int child[2];
        int exist;
        int cnt;
    } nodes[NUMBEROFNODES];

    int cur; /// cho biết hiện tại trong trie đang có bao nhiêu đỉnh

    Trie() : cur(0) /// tạo nút gốc cho trie là đỉnh 0 khi khởi tạo trie
    {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };

    int new_node()
    {
        /**
            TẠO VÀ TRẢ VỀ GIÁ TRỊ CỦA ĐỈNH MỚI ĐƯỢC TẠO RA
        **/
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }

    void add_number(int x)
    {

        /**
           HÀM THỰC HIỆN CHÈN MỘT SỐ VÀO TRONG TRIE:

         * chạy theo độ dài LG để thực hiện dịch bit
         * nếu cạnh tương ứng với bit c chưa tồn tại thì ta tạo đỉnh mới
         * tăng biến đếm cnt cho biết có thêm từ trong trie có dãy bit tiền tố là số được thể hiện bằng đỉnh hiện tại
         * khi đã tìm được đỉnh tương ứng với dãy bit của số, tăng biến exist của đỉnh lên 1

        **/

        int pos = 0;
        for (int i = LG; i >= 0; i--)
        {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1)
                nodes[pos].child[c] = new_node();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    int XOR(int x)
    {

        /**
           HÀM THỰC HIỆN TÌM XOR LỚN NHẤT VỚI GIÁ TRỊ X ĐẦU VÀO:

         * bắt đầu từ đỉnh pos = 0, xét lần lượt các bit từ lớn đến bé
         * tại bit thứ i, nếu đỉnh hiện tại đang xét có thể đi xuống cạnh có bit là f(x,i) XOR 1, ta sẽ đi qua cạnh đó để có được bit i trong đáp án là 1
         * nếu không, tiếp tục đi xuống các cạnh còn lại của đỉnh đang xét và có được bit i của đáp án là 0

        **/

        int pos = 0, res = 0;
        for (int i = LG; i >= 0; i--)
        {
            int c = (x >> i) & 1;

            if (nodes[pos].child[c ^ 1] != -1)
            {
                res += (1ll << i);
                pos = nodes[pos].child[c ^ 1];
            }
            else
                pos = nodes[pos].child[c];
        }
        return res;
    }
};

int main()
{

    /**

      XÂY DỰNG CHƯƠNG TRÌNH NHẬP XUẤT DỮ LIỆU BẰNG FILE

      * mở file input, output để nhập, xuất dữ liệu
      * đọc dữ liệu vào từ file input
      * thực hiện khởi tạo cây trie chứa các số từ dữ liệu vào input
      * thực hiện gọi hàm XOR thu được kết quả

    **/

    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int len, x;
    cin >> len >> x;

    Trie myTree;

    // vector input lưu trữ các xâu để chèn vào trie
    vector<int>input(len);
    for (int i = 0; i < len; i++)
    {
        cin >> input[i];
        myTree.add_number(input[i]);
    }

    // gọi hàm tìm XOR lớn nhất với giá trị được cho
    cout << myTree.XOR(x);

    return 0;
}
