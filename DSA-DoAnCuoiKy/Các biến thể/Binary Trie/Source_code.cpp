/**
    XÂY DỰNG CHƯƠNG TRÌNH CÀI ĐẶT CÂY TRIE NHỊ PHÂN

    * Cây trie nhị phân được cài đặt tương tự đối với Cây trie lưu chuỗi
      Điểm khác biệt ở chỗ cây trie nhị phân có mảng con trỏ có kích thước là 2 (0 và 1)
        trong khi cây trie lưu chuỗi cần một mảng con trỏ có kích thước là 26 (ký tự từ a đến z)

    * Thực hiện xây dựng cấu trúc trie nhị phân, các thao tác cơ bản trên nó
    * Chương trình có bộ dữ liệu nhập/xuất từ file
      (chi tiết ở hàm main)

    * Thực hiện gọi các hàm: chèn, tìm kiếm số, xóa với bộ dữ liệu testcase từ file input
      Thu được kết quả ghi ra file output
      
**/

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
/// Hằng số LG cho biết cây trie có thể chứa các số nguyên tối đa 2^LG
const int LG = 31; // ở đây định nghĩa LG = 31
//
    /**

      Cây trie nhị phân được cài đặt tương tự đối với Cây trie lưu chuỗi
      (có docstring chi tiết ở chương trình cài đặt cây trie lưu chuỗi)
      * Điểm khác biệt ở chỗ cây trie nhị phân có mảng con trỏ có kích thước là 2 (0 và 1)
        trong khi cây trie lưu chuỗi cần một mảng con trỏ có kích thước là 26 (ký tự từ a đến z)

    **/

struct TrieNode
{
    /**

       XÁC ĐỊNH CẤU TRÚC CỦA MỘT NÚT:
       * Tương tự với trie lưu chuỗi nhưng mảng con trỏ có kích thước là 2
       * Biến data có kiểu là số nguyên (0 hoặc 1)
       * Một cờ để đánh dấu là nút chứa bit kết thúc trong dãy bit

    **/

    int data; //storing for printing purposes only
    TrieNode* children[2];  //pointer array for child nodes of each node
    bool is_leaf; //a flag to check if it's a leaf node
                  //that means it is the last bit in sequence bit of number in trie
};

TrieNode* makeTrieNode(int data)
{
    /**

       HÀM TẠO MỘT NÚT TRIE MỚI:
       * khởi tạo mọi chỉ mục của mảng childNode bằng NULL
       * khởi tạo cờ đánh dấu is_leaf = 0
       * lưu trữ biến data chứa bit tương ứng trong dãy bit

    **/

    //create a trie node
    TrieNode* newNode = new TrieNode();
    //initialize every index of childNode array with NULL
    for (int i = 0; i < 2; i++)
        newNode->children[i] = NULL;
    newNode->is_leaf = 0;   //initialize the is_leaf with 0
    newNode->data = data;   //initialize the data with a bit (0 or 1) in node
    return newNode;
}

void freeTrieNode(TrieNode* root)
{

    /**
       HÀM GIẢI PHÓNG CON TRỎ:

      * gọi đệ quy tìm đến nút chứa bit cuối cùng trong dãy bit
      * thực hiện giải phóng con trỏ

    **/

    //free the trie node sequence
    for (int i = 0; i < 2; i++)
    {
        if (root->children[i] != NULL)
            freeTrieNode(root->children[i]);
        else continue;
    }
    free(root);
}

TrieNode* insert_number(TrieNode* root, int num)
{
    /**
       HÀM THỰC HIỆN CHÈN MỘT SỐ VÀO TRONG TRIE:

     * đầu vào của hàm gồm nút gốc trie và một số cần chèn
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài biến LG
     * thực hiện dịch bit, kiểm tra xem trong mảng con trỏ của nút
       tương ứng với bit đó có rỗng hay không
     * nếu là NULL thì thực hiện tạo một nút mới và trỏ bit hiện tại
       vào nút mới được tạo này, sau đó di chuyển đến nút tiếp theo
     * nếu không phải là NULL, ta sẽ không chèn, thay vào đó di chuyển
       đến nút tiếp theo
     * khi đến nút tương ứng với bit cuối cùng của số cần chèn, đánh
       dấu nút đó là nút kết thúc của dãy bit

    **/

    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //across the length of the LG to shift bit
    for (int i = LG; i >= 0; i--)
    {
        //initialize the idx with bit 0 or 1 in childNode array
        int idx = (num >> i) & 1;
        //check if the node exist for the current bit in the Trie
        if (current->children[idx] == NULL)
        {
            //if node for bit does not exist, create that child
            current->children[idx] = makeTrieNode(idx);
        }
        else {
            //if the corresponding child exist, do nothing
        }
        //because we have a prefix match, go down a level
        current = current->children[idx];
    }
    //at the end of bit sequence, mark this node as the leaf node
    //that means there is the end of bit sequence of the number to be inserted
    current->is_leaf = 1;
    return root;
}

void printTrie(TrieNode* root)
{
    /**
       HÀM THỰC HIỆN IN CÂY TRIE:

     * đầu vào của hàm gồm nút gốc trie
     * nếu nút gốc là rỗng, kết thúc lần in
     * khởi tạo con trỏ current thay thế nút gốc
     * thực hiện in bit đã lưu trong nút
     * chạy vòng lặp theo kích thước của mảng con trỏ để gọi đệ quy
       in toàn bộ bit có trong mảng con trỏ của nút tương ứng này

    **/

    //print the nodes of the trie
    if (root == NULL) return;
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //print the current bit in this currentNode
    cout << "->" << current->data;
    //iterate across the length of the pointer array to print the next bit
    for (int i = 0; i < 2; i++)
        printTrie(current->children[i]);
}

bool search_number(TrieNode* root, int num)
{
    /**
       HÀM THỰC HIỆN TÌM KIẾM MỘT SỐ TRONG TRIE:

     * đầu vào của hàm gồm nút gốc trie và một số cần tìm kiếm
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài biến LG
     * thực hiện dịch bit, kiểm tra xem trong mảng con trỏ của nút
       tương ứng với bit đó có rỗng hay không
     * nếu bit hiện tại có trong nút, di chuyển tới nút con của nó
     * nếu ở bất kỳ bước nào bit hiện tại của số không có trong nút thì trả về false
     * nếu bit cuối cùng được tìm thấy, kiểm tra nút đó có biến is_leaf được đánh dấu
       hay không để kiểm tra sự kết thúc của dãy bit. Nếu có đánh dấu, hàm search trả về
       true có nghĩa là tìm thấy số trong trie, ngược lại trả về false

    **/

    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //iterate across the length of the LG to shift bit
    for (int i = LG; i >= 0; i--)
    {
        //initialize the idx with bit 0 or 1 in childNode array
        int idx = (num >> i) & 1;
        //check if the node exist for the current bit in the Trie
        if (current->children[idx] == NULL)
        {
            //given the number does not exist in Trie
            return false;
        }
        //move the currentNode pointer to the already existing node for current bit
        current = current->children[idx];
    }
    //check if currentNode is marked as the ending of the bit sequence
    if (current != NULL && current->is_leaf == 1)
        return true;
    return false;
}

void print_search(TrieNode* root, int num)
{
    /**
       HÀM THỰC HIỆN IN RA SAU KHI TÌM KIẾM MỘT SỐ

      * nếu từ được tìm thấy, thông báo số đó có xuất hiện trong trie
      * ngược lại, thông báo số đó không xuất hiện trong trie

    **/

    if (search_number(root, num))
    //check if the number is found in the Trie
        cout << num << " is present in the Trie!\n";
    else
        cout << num << " is not present in the Trie!\n";
}

bool delete_number(TrieNode* root, int num)
{
    /**
       HÀM THỰC HIỆN XÓA MỘT SỐ TRONG TRIE:
       (Thực hiện xóa gồm có 3 trường hợp)

      * đầu vào của hàm gồm nút gốc trie và một số cần xóa
      * ban đầu, thực hiện tìm kiếm tiền tố là dãy bit chung dài nhất giữa
        số cần xóa và các số có trong trie
        (tương tự với cách tìm kiếm tiền tố chung ở trie lưu chuỗi)
      * tại nút chứa bit cuối cùng của số cần xóa, kiểm tra nếu nút này còn
        trỏ đến các nút con khác, có nghĩa dãy bit của số cần xóa là tiền tố
        hoàn toàn của các số khác trong trie, thực hiện xóa đánh dấu thể hiện
        bit cuối cùng của số này
      * nếu nút chung cuối cùng là tồn tại, có nghĩa số cần xóa có chung tiền tố
        dãy bit chung với các số khác trong trie, thực hiện xóa bằng cách cho
        nút này trỏ đến bit chung cuối cùng bằng NULL
      * nếu nút chung cuối cùng không tồn tại, có nghĩa số cần xóa không có chung
        tiền tố dãy bit với bất cứ số nào trong trie, thực hiện xóa bằng cách cho
        nút gốc trỏ đến bit đầu tiên của số bằng NULL

    **/

    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //initialize the lastBranchNode with the node contains the bit that is the last common bit sequence
    TrieNode* lastBranchNode = NULL;
    //initialize the lastBranchBit with the bit is the last common prefix
    int lastBranchBit = 0;
    //iterate across the length of the LG to shift bit
    for (int i = LG; i >= 0; i--)
    {
        //initialize the ind with bit 0 or 1 in childNode array
        int idx = (num >> i) & 1;
        //check if the node exist for the current bit in the Trie
        //return not found to delete
        if (current->children[idx] == NULL)
            return false;
        else
        {
            //the cnt is the count of bit in the current childNode array
            int cnt = 0;
            //Iterate across the length of the current childNode
            for (int j = 0; j < 2; j++)
                //check if exist bit
                if (current->children[j] != NULL)
                {
                    //increase cnt by 1
                    cnt++;
                }
            //check if the count of bit in the current childNode is more than 1
            //that means the current childNode has the bit that is a common prefix
                //between the deleted number and other numbers in the trie
            if (cnt > 1)
            {
                //assigns the current node pointer is the most common bit sequence node
                lastBranchNode = current;
                //assigns the current bit is the last common prefix
                lastBranchBit = idx;
            }
            //move the next currentNode pointer
            current = current->children[idx];
        }
    }
    //now, the cnt is the count of bit in the last common prefix node
    int cnt = 0;
    //iterate across the length of pointer array to count of bit in the current node
    for (int i = 0; i < 2; i++)
        if (current->children[i] != NULL)
            cnt++;
    //Case 1: the deleted number is a bit sequence of other numbers in trie
    //check if the count of bit in the last common prefix node is more than 0
        //that means the last bit of deleted number is not the bit that is the last common bit sequence
    if (cnt > 0)
    {
        //at the end of bit sequence at the currentNode, mark this node is not the leaf node
        current->is_leaf = 0;
        return true;
    }
    //Case 2: the deleted number shares a common bit sequence with other numbers in trie
    //check if the last node has the common bit sequence
    if (lastBranchNode != NULL)
    {
        //delete all node from the last common prefix node to node has the last bit in deleted number
            //by letting the last common prefix node point to NULL
        lastBranchNode->children[lastBranchBit] = NULL;
        return true;
    }
    //Case 3: the deleted number does not share any common bit sequence with other number in trie
    else
    {
        int first = (num >> 1) & 1;
        //delete all node by letting root node point the first bit of deleted number is NULL
        root->children[first] = NULL;
        return true;
    }
    return false;
}

void print_delete(TrieNode* root, int num)
{
    /**
       HÀM THỰC HIỆN IN RA SAU KHI XÓA MỘT SỐ

      * nếu số đã được xóa, thông báo số đó đã được xóa thành công
      * ngược lại, thông báo không tìm thấy số cần xóa

    **/

    if (delete_number(root, num))
    //if the number is deleted in Trie
        cout << num << " is successfully deleted!\n";
    else
        cout << num << " is not present in the Trie!\n";
}

int main()
{

    /**

      XÂY DỰNG CHƯƠNG TRÌNH NHẬP XUẤT DỮ LIỆU BẰNG FILE

      * mở file input, output để nhập, xuất dữ liệu
      * đọc dữ liệu vào từ file input
      * thực hiện khởi tạo cây trie với nút gốc rỗng
      * lưu trữ các số nhập vào bằng vector có tên input
      * lưu trữ các số truy vấn tìm kiếm bằng vector có tên searchQuery
      * lưu trữ các số truy vấn xóa bằng vector có tên deleteQuery
      * thực hiện gọi các hàm tương ứng thu được kết quả

    **/

        //open file to import and export data
        freopen("inputB1.txt", "r", stdin);
        freopen("outputB1.txt", "w", stdout);

        int len1, len2, len3;
        cin >> len1 >> len2 >> len3;
        //len1 is a number of insert operations in the trie
        //len2 is a number of search operations in the trie
        //len3 is a number of delete operations in the trie

        //make a root node for the trie
        TrieNode* root = makeTrieNode(0);


        /// import string and insert into the trie
        for (int i = 0; i < len1; i++)
        {
            int num_input;
            cin >> num_input;   //import number input from file
            root = insert_number(root, num_input);
        }
        //print the trie after insert
        cout << "Trie after insert: ";
        printTrie(root);
        cout << "\n\n";

        /// searching
        cout << "Searching:\n";
        for (int i = 0; i < len2; i++)
        {
            int num_search;
            cin >> num_search;    //import search query number from file
            print_search(root, num_search);
        }
        cout << "\n";

        /// deleting
        cout << "Deleting:\n";
        for (int i = 0; i < len3; i++)
        {
            int num_delete;
            cin >> num_delete;     //import delete query number from file
            print_delete(root, num_delete);
        }
        //print the trie after delete
        cout << "Trie after delete: ";
        printTrie(root);
        cout << "\n";

        //free trie node
        freeTrieNode(root);
        return 0;
}
