//function to delete a word in the trie
bool delete_word(TrieNode* root, char* word)
{
    //initialize the current Node pointer with the root node
    TrieNode* current = root;
    //initialize the lastBranchNode with the node contains the character that is the last common prefix
    TrieNode* lastBranchNode = NULL;
    //initialize the lastBranchChar with the character is the last common prefix
    char lastBranchChar = 'a';
    //iterate across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
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

//function to print the result after deleting
void print_delete(TrieNode* root, char* word)
{
    if (delete_word(root, word))
    //if the word is deleted in Trie
        cout << word << " is successfully deleted!\n";
    else
        cout << word << " is not present in the Trie!\n";
}
