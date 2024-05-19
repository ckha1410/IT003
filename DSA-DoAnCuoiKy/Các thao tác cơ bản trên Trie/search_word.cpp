bool search_word(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN TÌM KIẾM MỘT TỪ TRONG TRIE:
       
     * đầu vào của hàm gồm nút gốc trie và một từ cần tìm kiếm
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của từ cần tìm kiếm và đi xuống cây theo các nút tương ứng với mỗi ký tự
     * nếu ký tự hiện tại có trong nút, di chuyển tới nút con của nó
     * nếu ở bất kỳ bước nào ký tự hiện tại của từ không có trong nút thì trả về false
     * nếu ký tự cuối cùng được tìm thấy, kiểm tra nút đó có biến is_leaf được đánh dấu hay không 
       để kiểm tra sự kết thúc của từ. Nếu có đánh dấu, hàm search trả về true có nghĩa là tìm thấy từ, ngược lại trả về false

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
