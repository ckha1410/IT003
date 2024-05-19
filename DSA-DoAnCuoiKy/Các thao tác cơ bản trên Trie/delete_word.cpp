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
