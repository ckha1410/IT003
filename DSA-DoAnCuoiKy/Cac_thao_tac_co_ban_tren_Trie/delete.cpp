bool deleteWord(TrieNode* root, char* word)
{
    TrieNode* current = root;
    TrieNode* lastBranchNode = NULL;
    char lastBranchChar = 'a';

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int) word[i] - 'a';
        if (current->children[idx] == NULL)
            return false;
        else
        {
            int cnt = 0;
            for (int j = 0; j < ALPHABET_SIZE; j++)
                if (current->children[j] != NULL)
                    cnt++;
            if (cnt > 1)
            {
                lastBranchNode = current;
                lastBranchChar = word[i];
            }
            current = current->children[idx];
        }
    }
    int cnt = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (current->children[i] != NULL)
            cnt++;
    //Case 1:
    if (cnt > 0)
    {
        current->is_leaf = 0;
        return true;
    }
    //Case 2:
    if (lastBranchNode != NULL)
    {
        lastBranchNode->children[lastBranchChar] = NULL;
        return true;
    }
    //Case 3:
    else
    {
        root->children[word[0]] = NULL;
        return true;
    }
    return false;
}

void print_delete(TrieNode* root, char* word)
{
    if (deleteWord(root, word))
        cout << word << " is successfully deleted\n";
    else
        cout << word << " is not present in the Trie\n";
}
