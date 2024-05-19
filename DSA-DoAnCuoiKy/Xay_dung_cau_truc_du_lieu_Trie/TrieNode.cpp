struct TrieNode
{
    /**
       XÁC ĐỊNH CẤU TRÚC CỦA MỘT NÚT:

     * một biến data dùng cho mục đích in cây trie
     * mảng con trỏ cho các nút con của mỗi nút, có kích thướng là độ dài bảng chữ cái ALPHABET_SIZE = 26
     * một cờ để đánh dấu là nút chứa ký tự kết thúc của từ

    **/

    char data; //storing for printing purposes only
    TrieNode* children[ALPHABET_SIZE];  //pointer array for child nodes of each node
    bool is_leaf; //a flag to check if it's a leaf node
                  //that means it is the last character of a word in trie
};
