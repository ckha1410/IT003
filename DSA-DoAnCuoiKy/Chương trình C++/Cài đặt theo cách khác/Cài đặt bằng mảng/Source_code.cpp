/**
    XÂY DỰNG CHƯƠNG TRÌNH ĐƯỢC CÀI ĐẶT BẰNG MẢNG VỚI BỘ DỮ LIỆU NHẬP/XUẤT TỪ FILE
    (chi tiết ở hàm main)

    Thực hiện gọi các hàm: chèn, tìm kiếm từ, xóa đối với bộ dữ liệu testcase từ file input
    Thu được kết quả ghi ra file output

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

      * Định nghĩa cấu trúc của một nút
      * Hàm tạo một đỉnh gốc ban đầu
      * Hàm tạo một nút mới
      * Hàm thêm một chuỗi/từ vào trie
      * Hàm tìm kiếm một chuỗi/từ trong trie
      * Hàm kiểm tra xóa và xóa

    **/
public:

    struct Node
    {
        /**

          ĐỊNH NGHĨA CẤU TRÚC CỦA MỘT NÚT:
          * một mảng con có kích thước là độ dài bảng chữ cái
          * một biến exist cho biết có đỉnh tương ứng với xâu s
          * một biến cnt cho biết số lượng xâu có tiền tố là xâu được thể hiện bằng đỉnh hiện tại

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
          * khởi tạo mảng con child chứa toàn bộ giá trị -1
          * khởi tạo các giá trị khác bằng 0

        **/

        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };

    int new_node()
    {
        /**

          HÀM TẠO VÀ TRẢ VỀ GIÁ TRỊ CỦA ĐỈNH MỚI ĐƯỢC TẠO RA
          * tăng số lượng đỉnh cur vì tạo một đỉnh mới
          * khởi tạo mảng con child chứa toàn bộ giá trị -1
          * khởi tạo các giá trị khác bằng 0

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
          * bắt đầu từ đỉnh gốc (có vị trí bằng 0)
          * chạy vòng lặp theo độ dài của từ cần chèn, nếu cạnh tương ứng với chữ cái chưa tồn tại thì tạo một đỉnh mới
          * tiếp tục di chuyển đến mảng con tiếp theo
          * thực hiện tăng số lượng xâu có tiền tố được thể hiện bằng đỉnh hiện tại
          * sau khi tạo nút tương ứng với ký tự cuối cùng, thực hiện đánh dấu đỉnh tương ứng với xâu cần chèn (nút cuối cùng)

        **/

        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1)
            {
                // Nếu cạnh tương ứng chữ cái c chưa tồn tại thì ta tạo ra đỉnh mới
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            // Có thêm một xâu trong trie có tiền tố là xâu được thể hiện bằng đỉnh hiện tại
            nodes[pos].cnt++;
        }
        // Đã tìm được đỉnh tương ứng với xâu s, ta tăng biến exist của đỉnh lên 1
        nodes[pos].exist++;
    }

    bool find_word(string s)
    {
        /**

          HÀM TÌM KIẾM MỘT CHUỖI/TỪ TRONG TRIE:
          * bắt đầu từ đỉnh gốc (có vị trí bằng 0)
          * chạy vòng lặp theo độ dài của từ cần chèn, nếu cạnh tương ứng với chữ cái không tồn tại thì hàm trả về false
          * tiếp tục di chuyển đến mảng con tiếp theo
          * khi đến đỉnh tương ứng với ký tự cuối cùng, kiểm tra sự đánh dấu kết thúc của từ thông qua biến exist trong đỉnh đó. 
            Nếu bằng 0 hàm trả về true có nghĩa là tìm thấy từ, ngược lại hàm trả về false

        **/

        int pos = 0;
        for (auto f : s)
        {
            int c = f - 'a';
            // Nếu ký tự hiện tại không có trong đỉnh, hàm trả về false
            if (nodes[pos].child[c] == -1) return false;
            // Tiếp tục di chuyển đến mảng con tiếp theo
            pos = nodes[pos].child[c];
        }
        // Kiểm tra có xâu nào kết thúc tại đỉnh này hay không
        return (nodes[pos].exist != 0);
    }

    bool check_delete_word(int pos, string& s, int i)
    {
        /**

          HÀM KIỂM TRA LIỆU ĐỈNH TẠI VÍ TRÍ POS CÓ BỊ XÓA ĐI HAY KHÔNG
          * ban đầu, tìm đỉnh tương ứng với xâu s, nếu chưa đến đỉnh này thì đệ quy đi xuống các đỉnh phía dưới
            nếu đỉnh con tương ứng bị xóa, gán lại đỉnh tương ứng bằng -1
          * nếu đến đỉnh tương ứng với xâu s, xóa đánh dấu kết thúc của từ tại đỉnh này thông qua biến exist
          * nếu đỉnh tương ứng với xâu cần xóa không phải là đỉnh gốc thì thực hiện giảm số lượng 
            xâu có tiền tố chung với xâu cần xóa thông qua biến cnt
          * nếu số lượng xâu có chung tiền tố bằng 0, có nghĩa không có xâu nào đi qua nó 
            thì đỉnh đã bị xóa, hàm trả về true, ngược làm hàm trả về false

        **/

        if (i != (int)s.size())
        { 
            // Nếu chưa đến đỉnh tương ứng với xâu s thì tiếp tục đệ quy xuống dưới
            int c = s[i] - 'a';
            bool isChildDeleted = check_delete_word(nodes[pos].child[c], s, i + 1);
            if (isChildDeleted)
                nodes[pos].child[c] = -1; // Nếu đỉnh con tương ứng bị xóa thì ta gán lại đỉnh tương ứng bằng -1
        }
        else
            // Nếu đã đến đỉnh tương ứng với xâu s thì ta giảm biến exist của đỉnh đi 1
            nodes[pos].exist--;

        // Nếu đỉnh đang xét không phải gốc
        if (pos != 0)
        {
            // giảm biến cnt của đỉnh đi 1
            nodes[pos].cnt--;
            // Kiểm tra đỉnh có bị xóa đi hay không
            // Đỉnh bị xóa nếu không còn xâu nào đi qua nó, nói cách khác là
            // không còn xâu nào có tiền tố là xâu được thể hiện bởi đỉnh pos
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    }

    bool delete_word(string s)
    {
        /**

            HÀM XÓA MỘT CHUỖI/TỪ TRONG TRIE:
          * Kiểm tra từ có tồn tại trong trie hay không bằng hàm find_word
          * Nếu có tồn tại, thực hiện gọi hàm kiểm tra xóa check_delete_word và xóa

        **/

        // Kiểm tra xâu s có trong trie hay không
        if (find_word(s) == false)
            return false;
        // Nếu có, gọi hàm đệ quy xóa xâu s khỏi trie
        check_delete_word(0, s, 0);
        return true;
    }

};

int main()
{
    /**

     NHẬP XUẤT DỮ LIỆU BẰNG FILE:

     * Nhập vào độ dài 3 vector lưu trữ xâu
     * Vector input lưu trữ các xâu để chèn vào trie
     * Vector searchQuery lưu trữ các xâu thực hiện truy vấn tìm kiếm trong trie
     * Vector deleteQuery lưu trữ các xâu thực hiện truy vấn xóa trong trie
     * Thực hiện gọi các hàm thu được kết quả

    **/


    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int len1, len2, len3;
    cin >> len1 >> len2 >> len3;

    Trie myTree;

    // vector input lưu trữ các xâu để chèn vào trie
    vector<string>input(len1);
    for (int i = 0; i < len1; i++)
    {
        cin >> input[i];
        myTree.add_word(input[i]);
    }

    // vector searchQuery lưu trữ các xâu truy vấn tìm kiếm trong trie
    vector<string>searchQuery(len2);
    /// searching
    cout << "Searching:\n";
    for (int i = 0; i < len2; i++)
    {
        cin >> searchQuery[i];
        if (myTree.find_word(searchQuery[i]))
            cout << "\"" << searchQuery[i] << "\" is present in the Trie!\n";
        else
            cout << "\"" << searchQuery[i] << "\" is not present in the Trie!\n";
    }
    cout << "\n";

    // vector deleteQuery lưu trữ các xâu truy vấn xóa trong trie
    vector<string>deleteQuery(len3);
    /// deleting
    cout << "Deleting:\n";
    for (int i = 0; i < len3; i++)
    {
        cin >> deleteQuery[i];
        if (myTree.delete_word(deleteQuery[i]))
            cout << "\"" << deleteQuery[i] << "\" is successfully deleted!\n";
        else
            cout << "\"" << deleteQuery[i] << "\" is not present in the Trie!\n";
    }
    cout << "\n";

    return 0;
}
