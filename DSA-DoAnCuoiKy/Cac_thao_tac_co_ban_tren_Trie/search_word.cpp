//function to search a word in the trie
bool search_word(TrieNode* root, char* word)
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

//function to print the result after searching
void print_search(TrieNode* root, char* word)
{
    if (search_word(root, word))
    //check if the word is found in the Trie
        cout << word << " is present in the Trie!\n";
    else
        cout << word << " is not present in the Trie!\n";
}
