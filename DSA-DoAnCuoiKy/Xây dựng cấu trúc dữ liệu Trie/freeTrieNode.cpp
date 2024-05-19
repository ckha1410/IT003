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
