bool search(TrieNode* root, char* word)
{
    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //Iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int) word[i] - 'a';
        if (current->children[idx] == NULL)
            return false;
        current = current->children[idx];
    }
    if (current != NULL && current->is_leaf == 1)
        return true;
    return false;
}

void print_search(TrieNode* root, char* word)
{
    if (search(root, word))
        cout << word << " is present in the Trie\n";
    else
        cout << word << " is not present in the Trie\n";
}
