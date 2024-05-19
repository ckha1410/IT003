bool PrefixExist(TrieNode* root, char* prefix)
{
    /**
       HÀM THỰC HIỆN KIỂM TRA SỰ TỒN TẠI CỦA MỘT TIỀN TỐ TRONG TRIE

     * đầu vào của hàm gồm nút gốc trie và một tiền tố cần tìm kiếm
     * khởi tạo con trỏ current thay thế nút gốc
     * bắt đầu từ nút gốc, chạy vòng lặp theo độ dài của tiền tố cần tìm kiếm và đi xuống cây theo các nút tương ứng với mỗi ký tự
     * nếu ký tự hiện tại có trong nút, di chuyển tới nút con của nó
     * nếu ở bất kỳ bước nào ký tự hiện tại của tiền tố không có trong nút thì trả về false
     * nếu ký tự cuối cùng của tiền tố được tìm thấy, hàm trả về true, ngược lại, hàm trả về false

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

    if (PrefixExist(root, prefix))
    //check if the prefix is found in the Trie
        cout << "Prefix \"" << prefix << "\" is present in the Trie!\n";
    else
        cout << "Prefix \"" << prefix << "\" is not present in the Trie!\n";
}
