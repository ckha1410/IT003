void search_byPrefix(TrieNode* node, char* prefix, string s, vector<string>&ans)
{
    /**
        HÀM THỰC HIỆN TÌM TẤT CẢ CÁC TỪ BẮT ĐẦU BẰNG MỘT TIỀN TỐ CHO TRƯỚC:

      * đầu vào của hàm gồm nút chứa ký tự cuối cùng của tiền tố, một xâu s để lưu từ, một vector ans dùng để lưu trữ tất cả các từ
      * kiểm tra nếu nút rỗng thì hàm kết thúc
      * khởi tạo con trỏ current thay thế nút chứa ký tự cuối của tiền tố
      * thực hiện lưu lần lượt ký tự trong trie vào xâu s
      * kiểm tra nếu nút có đánh dấu là kết thúc của từ trong trie, thực hiện lưu xâu s vào vector kết quả và khởi tạo lại s
        là tiền tố đã cho để tiếp tục tìm từ mới
      * chạy vòng lặp theo độ dài mảng, gọi đệ quy để di chuyển xuống cây để in tất cả ký tự sau tiền tố trong trie

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
      * bắt đầu từ nút gốc, di chuyển đến nút chứa ký tự cuối cùng của tiền tố cho trước
      * nếu ở bất kỳ bước nào ký tự hiện tại của tiền tố không có trong nút thì thông báo "Not have" và kết thúc hàm
      * ngược lại, tiếp tục di chuyển xuống cho đến ký tự cuối cùng của tiền tố
      * khởi tạo một biến xâu s là từ được liệt kê và lưu vào vector ans
      * thực hiện gọi hàm search_byPefix để tìm các từ bắt đầu bằng tiền tố
      * sau khi thực hiện hàm search_byPrefix, thực hiện in các từ trong vector ans thu được kết quả

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
