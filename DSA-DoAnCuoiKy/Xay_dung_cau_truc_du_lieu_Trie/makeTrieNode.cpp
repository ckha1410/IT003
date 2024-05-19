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
