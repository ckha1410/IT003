void printTrie(TrieNode* root)
{
    /**
       HÀM THỰC HIỆN IN CÂY TRIE:

     * đầu vào của hàm gồm nút gốc trie
     * kiểm tra nếu nút gốc là rỗng, kết thúc lần in
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
        printTrie(current->children[i]);
}
