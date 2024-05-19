#include <iostream>
#include <string.h>
#include <vector>
#include<fstream>
using namespace std;
/// Định nghĩa số lượng phần từ của mảng con trỏ là độ dài bảng chữ cái
#define ALPHABET_SIZE 26

struct TrieNode
{
    /**
       XÁC ĐỊNH CẤU TRÚC CỦA MỘT NÚT:

     * một biến data dùng cho mục đích in cây trie
     * mảng con trỏ cho các nút con của mỗi nút, có kích thước là độ dài bảng chữ cái ALPHABET_SIZE = 26 ký tự
     * một cờ để đánh dấu là nút chứa ký tự kết thúc của từ

    **/

    char data; //storing for printing purposes only
    TrieNode* children[ALPHABET_SIZE];  //pointer array for child nodes of each node
    bool is_leaf; //a flag to check if it's a leaf node
                  //that means it is the last character of a word in trie
};

TrieNode* makeTrieNode(char data)
{
    /**
       HÀM TẠO MỘT NÚT TRIE MỚI:

     * khởi tạo mọi chỉ mục của mảng childNode bằng NULL
     * khởi tạo cờ đánh dấu is_leaf = 0
     * lưu trữ biến data chứa ký tự tương ứng của chuỗi

    **/

    TrieNode* newNode = new TrieNode();
    //initialize every index of childNode array with NULL
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->is_leaf = 0;   //initialize the is_leaf with 0
    newNode->data = data;   //initialize the data with character in node
    return newNode;
}

void freeTrieNode(TrieNode* root)
{
    /**
       HÀM GIẢI PHÓNG CON TRỎ:

     * gọi đệ quy tìm đến nút chứa ký tự cuối cùng của từ
     * thực hiện giải phóng con trỏ

    **/

    //free the trie node sequence
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL)
            freeTrieNode(root->children[i]);
        else continue;
    }
    free(root);
}

TrieNode* insert_word(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN CHÈN MỘT CHUỖI/TỪ VÀO TRONG TRIE:

     * đầu vào của hàm gồm nút gốc trie và một từ cần chèn
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của từ cần chèn
       với mỗi ký tự, kiểm tra xem trong mảng con trỏ của nút tương ứng
       với ký tự đó có rỗng hay không bằng chỉ mục vị trí idx
     * nếu là NULL thì thực hiện tạo một nút mới và trỏ ký tự hiện tại
       vào nút mới được tạo này, sau đó di chuyển đến nút tiếp theo
     * nếu không phải là NULL, ta sẽ không chèn, thay vào đó di chuyển
       đến nút tiếp theo
     * khi đến nút tương ứng với ký tự cuối cùng của từ cần chèn, đánh
       dấu nút đó là nút kết thúc từ thông qua biến is_leaf

    **/

    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the idx with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in the Trie
        if (current->children[idx] == NULL)
        {
            //if node for character does not exist
            //create that child
            current->children[idx] = makeTrieNode(word[i]);
        }
        else {
            //if the corresponding child exist, do nothing
        }
        //because we have a prefix match, go down a level
        current = current->children[idx];
    }
    //at the end of word, mark this node as the leaf node
    //this implies that there is a string ending at the last currentNode
    current->is_leaf = 1;
    return root;
}

void print_trie(TrieNode* root)
{
    /**
       HÀM THỰC HIỆN IN CÂY TRIE:

     * đầu vào của hàm gồm nút gốc trie
     * nếu nút gốc là rỗng, kết thúc lần in
     * khởi tạo con trỏ current thay thế nút gốc
     * thực hiện in ký tự đã lưu trong nút
     * chạy vòng lặp theo độ dài bảng chữ cái để gọi đệ quy
       in toàn bộ ký tự có trong mảng con trỏ của nút tương ứng này

    **/

    //print the nodes of the trie
    if (root == NULL) return;
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //print the current character in this currentNode
    cout << current->data << "->";
    //iterate across the length of the children array to print the next character
    for (int i = 0; i < ALPHABET_SIZE; i++)
        print_trie(current->children[i]);
}

bool search_word(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN TÌM KIẾM MỘT TỪ TRONG TRIE:

     * đầu vào của hàm gồm nút gốc trie và một từ cần tìm kiếm
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của từ cần tìm kiếm
       và đi xuống cây theo các nút tương ứng với mỗi ký tự
     * nếu ký tự hiện tại có trong nút, di chuyển tới nút con của nó
     * nếu ở bất kỳ bước nào ký tự hiện tại của từ không có trong nút thì trả về false
     * nếu ký tự cuối cùng được tìm thấy, kiểm tra nút đó có biến is_leaf được đánh dấu
       hay không để kiểm tra sự kết thúc của từ. Nếu có đánh dấu, hàm search trả về
       true có nghĩa là tìm thấy từ, ngược lại trả về false

    **/

    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the idx with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in Trie
        if (current->children[idx] == NULL)
        {
            //given the word does not exist in Trie
            return false;
        }
        //move the currentNode pointer to the already existing node for current character
        current = current->children[idx];
    }
    //check if currentNode is marked as the ending of the word
    if (current != NULL && current->is_leaf == 1)
        return true;
    return false;
}


void print_search(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN IN RA SAU KHI TÌM KIẾM TỪ

     * nếu từ được tìm thấy, thông báo từ đó có xuất hiện trong trie
     * ngược lại, thông báo từ đó không xuất hiện trong trie

    **/

    if (search_word(root, word))
    //check if the word is found in the Trie
        cout << "\"" << word << "\" is present in the Trie!\n";
    else
        cout << "\"" << word << "\" is not present in the Trie!\n";
}

bool search_prefix(TrieNode* root, char* prefix)
{
    /**
       HÀM THỰC HIỆN KIỂM TRA SỰ TỒN TẠI CỦA MỘT TIỀN TỐ TRONG TRIE

     * đầu vào của hàm gồm nút gốc trie và một tiền tố cần tìm kiếm
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của tiền tố cần tìm kiếm
       và đi xuống cây theo các nút tương ứng với mỗi ký tự
     * nếu ký tự hiện tại có trong nút, di chuyển tới nút con của nó
     * nếu ở bất kỳ bước nào ký tự hiện tại của tiền tố không có trong nút
       thì hàm trả về false
     * nếu ký tự cuối cùng của tiền tố được tìm thấy, hàm trả về true
       ngược lại, hàm trả về false

    **/

    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //iterate across the length of the prefix
    for (int i = 0; prefix[i] != '\0'; i++)
    {
        //initialize the idx with index of each character in childNode array
        int idx = (int) prefix[i] - 'a';
        //check if the node exist for the current character in Trie
        if (current->children[idx] == NULL)
        {
            //given the prefix does not exist in Trie
            return false;
        }
        //move the currentNode pointer to the already existing node for current character
        current = current->children[idx];
    }
    //prefix exist in trie
    return true;
}

void print_prefix(TrieNode* root, char* prefix)
{
    /**
       HÀM THỰC HIỆN IN RA SAU KHI TÌM KIẾM TIỀN TỐ

     * nếu tiền tố được tìm thấy, thông báo tiền tố đó có xuất hiện trong trie
     * ngược lại, thông báo tiền tố đó không xuất hiện trong trie

    **/

    if (search_prefix(root, prefix))
    //check if the prefix is found in the Trie
        cout << "Prefix \"" << prefix << "\" is present in the Trie!\n";
    else
        cout << "Prefix \"" << prefix << "\" is not present in the Trie!\n";
}


bool delete_word(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN XÓA MỘT TỪ TRONG TRIE:
       (Thực hiện xóa gồm có 3 trường hợp xảy ra)

     * đầu vào của hàm gồm nút gốc trie và một từ cần xóa
     * ban đầu, khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của tiền tố cần tìm kiếm và đi xuống cây theo các nút tương ứng với mỗi ký tự
     * khởi tại một biến lastBranchNode là nút chứa ký tự cuối của tiền tố chung dài nhất giữa từ cần xóa và các từ trong trie
     * khởi tại một biến lastBranchChar là ký tự cuối của tiền tố chung dài nhất giữa từ cần xóa và các từ trong trie
     * Thực hiện tìm nút tiền tố chung dài nhất giữa từ cần xóa và các từ trong trie:
        * chạy vòng lặp theo độ dài của từ cần xóa và bắt đầu di chuyển xuống cây
        * nếu ở bất kỳ bước nào ký tự hiện tại của từ không có trong nút thì hàm trả về false
        * ngược lại, thực hiện đếm số lượng nút con chứa ký tự mà con trỏ hiện tại có thể trỏ đến
        bằng cách chạy vòng lặp theo độ dài của mảng và tăng biến đếm cnt
        * nếu số lượng lớn hơn 1, có nghĩa nút hiện tại chứa ký tự là tiền tố chung
          giữa từ cần xóa và các từ trong trie (vì nó trỏ đến nhiều hơn 1 ký tự)
        * thực hiện cập nhật giá trị của biến lastBrachNode và lastBrachChar
     * tại nút hiện tại và đã đi đến ký tự cuối cùng của từ cần xóa:
       thực hiện đếm số lượng nút con mà nút này có thể trỏ đến bằng cách chạy vòng lặp theo độ dài của mảng
     * nếu số lượng bằng 1, có nghĩa nút này chỉ trỏ đến ký tự tiếp theo trong trie:
        * có nghĩa, từ cần xóa là tiền tố hoàn toàn của các từ khác trong trie, đây là trường hợp 1:
          thực hiện xóa từ bằng cách xóa đánh dấu is_leaf ở nút này, thể hiện không còn sự kết thúc của từ
        * ngược lại, có nghĩa từ cần xóa có chung tiền tố với các từ khác trong trie, đây là trường hợp 2:
          thực hiện xóa từ bằng cách cho nút tiền tố chung dài nhất trỏ đến ký tự lastBranchChar bằng NULL
        * nếu không thuộc 2 trường hợp trên, ta có trường hợp 3: từ cần xóa không có chung tiền tố nào
          với các từ khác trong trie (lastBranchNode = NULL):
          thực hiện xóa từ bằng cách cho nút gốc trỏ đến ký tự đầu tiên của từ bằng NULL

    **/

    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //initialize the lastBranchNode with the node contains the character that is the last common prefix
    TrieNode* lastBranchNode = NULL;
    //initialize the lastBranchChar with the character is the last common prefix
    char lastBranchChar = 'a';
    //iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the idx with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in trie
        //return not found to delete
        if (current->children[idx] == NULL)
            return false;
        else
        {
            //the cnt is the count of characters in the current childNode array
            int cnt = 0;
            //Iterate across the length of the current childNode
            for (int j = 0; j < ALPHABET_SIZE; j++)
                //check if exist character
                if (current->children[j] != NULL)
                {
                    //increase cnt by 1
                    cnt++;
                }
            //check if the count of character in the current childNode is more than 1
            //that means the current childNode has the character that is a common prefix
                //between the deleted word and other words in the trie
            if (cnt > 1)
            {
                //assigns the current node pointer is the most common prefix node
                lastBranchNode = current;
                //assigns the current character is the last common prefix
                lastBranchChar = word[i];
            }
            //move the next currentNode pointer
            current = current->children[idx];
        }
    }
    //now, the cnt is the count of characters in the last common prefix node
    int cnt = 0;
    //iterate across the length of pointer array to count of character in the current node
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (current->children[i] != NULL)
            cnt++;
    //Case 1: the deleted word is a prefix of other word in trie
    //check if the count of character in the last common prefix node is more than 0
        //that means the last character of deleted word is not the character that is the last common prefix
    if (cnt > 0)
    {
        //at the end of word at the currentNode, mark this node is not the leaf node
        current->is_leaf = 0;
        return true;
    }
    //Case 2: the deleted word shares a common prefix with other words in trie
    //check if the last node has the common prefix
    if (lastBranchNode != NULL)
    {
        //delete all node from the last common prefix node to node has the last character in deleted word
            //by letting the last common prefix node point to NULL
        lastBranchNode->children[lastBranchChar] = NULL;
        return true;
    }
    //Case 3: the deleted word does not share any common prefix with other words in trie
    else
    {
        //delete all node by letting root node point the first character of deleted word is NULL
        root->children[word[0]] = NULL;
        return true;
    }
    return false;
}

void print_delete(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN IN RA SAU KHI XÓA TỪ

     * nếu từ đã được xóa, thông báo từ đó đã được xóa thành công
     * ngược lại, thông báo không tìm thấy từ cần xóa

    **/

    if (delete_word(root, word))
    //if the word is deleted in Trie
        cout << "\"" << word << "\" is successfully deleted!\n";
    else
        cout << "\"" << word << "\" is not present in the Trie!\n";
}

void search_byPrefix(TrieNode* node, char* prefix, string s, vector<string>&ans)
{
    /**
        HÀM THỰC HIỆN TÌM TẤT CẢ CÁC TỪ BẮT ĐẦU BẰNG MỘT TIỀN TỐ CHO TRƯỚC:

      * đầu vào của hàm gồm nút chứa ký tự cuối cùng của tiền tố,
        một xâu s để lưu từ, một vector ans dùng để lưu trữ tất cả các từ
      * kiểm tra nếu nút rỗng thì hàm kết thúc
      * khởi tạo con trỏ current thay thế nút chứa ký tự cuối của tiền tố
      * thực hiện lưu lần lượt ký tự trong trie vào xâu s
      * kiểm tra nếu nút có đánh dấu là kết thúc của từ trong trie
        thực hiện lưu xâu s vào vector kết quả và khởi tạo lại s
        là tiền tố đã cho để tiếp tục in từ mới
      * chạy vòng lặp theo độ dài mảng, gọi đệ quy để di chuyển xuống cây
        để in tất cả ký tự của từ trong trie

    **/

    if (node == NULL) return;
    //initialize the currentNode pointer with the node
    TrieNode* current = node;
    //store each character of the corresponding node into the string
    s += current->data;
    //check if currentNode is marked as the ending of the word
    if (current->is_leaf)
    {
        //store the string into the vector
        ans.push_back(s);
        //initialize the string with the prefix to print the next word
        s = prefix;
    }
    //iterate across the length of the children array to store the next character
    for (int i = 0; i < ALPHABET_SIZE; i++)
        search_byPrefix(current->children[i], prefix, s, ans);
}

void list_word_byPrefix(TrieNode* root, char* prefix)
{
    /**
        HÀM THỰC HIỆN IN RA CÁC TỪ BẮT ĐẦU BẰNG MỘT TIỀN TỐ CHO TRƯỚC

      * đầu vào của hàm gồm nút gốc trie và một tiền tố cho trước
      * khởi tạo một vector để lưu trữ các từ bắt đầu bằng tiền tố cho trước
      * khởi tạo con trỏ current thay thế nút gốc
      * bắt đầu từ nút gốc, di chuyển đến nút chứa ký tự cuối cùng của tiền tố
        cho trước
      * nếu ở bất kỳ bước nào ký tự hiện tại của tiền tố không có trong nút
        thì thông báo "Not have" và kết thúc hàm
      * ngược lại, tiếp tục di chuyển xuống cho đến ký tự cuối cùng của tiền tố
      * khởi tạo một biến xâu s là từ được liệt kê và lưu vào vector ans
      * thực hiện gọi hàm search_byPefix để tìm các từ bắt đầu bằng tiền tố
      * sau khi thực hiện hàm search_byPrefix, thực hiện in các từ trong vector ans
        thu được kết quả

    **/

    vector<string>ans;
    TrieNode* current = root;
    //iterate across the length of the string
    for (int i = 0; prefix[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
        int idx = (int) prefix[i] - 'a';
        //check if the node exist for the current character in Trie
        if (current->children[idx] == NULL)
        {
            //given the word as a prefix does not exist in Trie
            cout << "Not have!";
            return;
        }
        //move the currentNode pointer to the already existing node for current character
        current = current->children[idx];
    }
    //initialize the string with the prefix to print word
    string s = prefix;
    //iterate across the length of the children array to move down the tree
    //to find words starting with the prefix
    for (int i = 0; i < ALPHABET_SIZE; i++)
        search_byPrefix(current->children[i], prefix, s, ans);

    //print all the words stored in the vector
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " - ";
}

int main()
{
    /**

      XÂY DỰNG CHƯƠNG TRÌNH NHẬP XUẤT DỮ LIỆU BẰNG FILE

      * mở file input, output để nhập, xuất dữ liệu
      * đọc dữ liệu vào từ file input
      * thực hiện khởi tạo cây trie với nút gốc rỗng
      * lưu trữ các chuỗi nhập vào bằng vector có tên input
      * lưu trữ các chuỗi truy vấn tìm kiếm bằng vector có tên searchQuery
      * lưu trữ các chuỗi truy vấn tìm kiếm tiền tố bằng vector có tên prefixQuery
      * lưu trữ các chuỗi truy vấn xóa bằng vector có tên deleteQuery
      * lưu trữ các chuỗi truy vấn liệt kê bằng vector có tên listQuery
      * thực hiện gọi các hàm tương ứng thu được kết quả

    **/
        //open file to import and export data
        freopen("input1.txt", "r", stdin);
        freopen("output1.txt", "w", stdout);

        int len1, len2, len3, len4;
        cin >> len1 >> len2 >> len3 >> len4;
        //len1 is a number of insert operations in the trie
        //len2 is a number of search operations in the trie
        //len3 is a number of delete operations in the trie
        //len4 is a number of list operations in the trie
        char str[1000];     //the character array for alternation

        //make a root node for the trie
        TrieNode* root = makeTrieNode('\0');

        /// import string and insert into the trie
        for (int i = 0; i < len1; i++)
        {
            char *input;
            input = str;
            cin >> input;   //import string input from file
            root = insert_word(root, input);
        }
        //print the trie after insert
        cout << "Trie after insert: ";
        print_trie(root);
        cout << "\n\n";

        /// searching
        cout << "Searching:\n";
        for (int i = 0; i < len2; i++)
        {
            char *searchQuery;
            searchQuery = str;
            cin >> searchQuery;     //import search query string from file
            print_search(root, searchQuery);
        }
        cout << "\n";

        /// deleting
        cout << "Deleting:\n";
        for (int i = 0; i < len3; i++)
        {
            char *deleteQuery;
            deleteQuery = str;
            cin >> deleteQuery;     //import delete query string from file
            print_delete(root, deleteQuery);
        }
        //print the trie after delete
        cout << "Trie after delete: ";
        print_trie(root);
        cout << "\n\n";

        /// listing
        cout << "Listing:";
        for (int i = 0; i < len4; i++)
        {
            char *listQuery;
            listQuery = str;
            cin >> listQuery;     //import search query string from file
            cout << "\nWords are listed by the prefix \"" << listQuery << "\": ";
            list_word_byPrefix(root, listQuery);
        }

        //free trie node
        freeTrieNode(root);
        return 0;
}
