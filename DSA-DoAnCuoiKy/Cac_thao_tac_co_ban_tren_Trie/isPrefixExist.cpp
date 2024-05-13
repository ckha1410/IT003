//function to check if a prefix exists or not in trie
bool isPrefixExist(TrieNode* root, char* word)
{
    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in Trie
        if (current->children[idx] == NULL)
        {
            //given the word as a prefix does not exist in Trie
            return false;
        }
        //move the currentNode pointer to the already existing node for current character
        current = current->children[idx];
    }
    //prefix exist in trie
    return true;
}

//function to print the result after checking prefix existence in trie
void print_prefix(TrieNode* root, char* prefix)
{
    if (isPrefixExist(root, prefix))
    //check if the prefix is found in the Trie
        cout << prefix << " is present in the Trie!\n";
    else
        cout << prefix << " is not present in the Trie!\n";
}
