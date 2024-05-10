bool isPrefixExist(TrieNode* root, char* word)
{
    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    // Iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in Trie
        if (current->children[idx] == NULL)
            //given the word as a prefix doesn't exist in Trie
            return false;
        //Move the currentNode pointer to the already existing node for current character
        current = current->children[idx];
    }
    //prefix exist in Trie
    return true;
}
