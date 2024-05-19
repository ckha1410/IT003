TrieNode* insert_word(TrieNode* root, char* word)
{
    /**
       HÀM THỰC HIỆN CHÈN MỘT CHUỖI/TỪ VÀO TRONG TRIE:

     * đầu vào của hàm gồm nút gốc trie và một từ cần chèn
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của từ cần chèn; với mỗi ký tự, 
       kiểm tra xem trong mảng con trỏ của nút tương ứng với ký tự đó có rỗng hay không bằng chỉ mục vị trí idx
     * nếu là NULL thì thực hiện tạo một nút mới và trỏ ký tự hiện tại vào nút mới được tạo này, sau đó di chuyển đến nút tiếp theo
     * nếu không phải là NULL, ta sẽ không chèn, thay vào đó di chuyển đến nút tiếp theo
     * khi đến nút tương ứng với ký tự cuối cùng của từ cần chèn, đánh dấu nút đó là nút kết thúc từ thông qua biến is_leaf

    **/

    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
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
    //that means there is a string ending at the last currentNode
    current->is_leaf = 1;
    return root;
}
