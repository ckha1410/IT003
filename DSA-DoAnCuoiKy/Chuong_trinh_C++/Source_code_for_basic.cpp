#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define ALPHABET_SIZE 26

//define a trie node structure
struct TrieNode
{
    char data; //storing for printing purposes only
    TrieNode* children[ALPHABET_SIZE];  //pointer array for child nodes of each node
    bool is_leaf; //a flag to check if it's a leaf node
};

TrieNode* makeTrieNode(char data)
{
    //create a trie node
    TrieNode* newNode = new TrieNode();
    //initialize every index of childNode array with NULL
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->is_leaf = 0;   //initialize the is_leaf with 0
    newNode->data = data;   //initialize the data with character in node
    return newNode;
}

void freeTrieNode(TrieNode* root)
{
    //free the trie node sequence
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL)
            freeTrieNode(root->children[i]);
        else continue;
    }
    free(root);
}

TrieNode* insert_word(TrieNode* root, char* word)
{
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in the Trie
        if (current->children[idx] == NULL)
        {
            //if node for character does not exist
            //create that child
            current->children[idx] = makeTrieNode(word[i]);
        }
        else {
            //if the corresponding child exist, do nothing
        }
        //because we have a prefix match, go down a level
        current = current->children[idx];
    }
    //at the end of word, mark this node as the leaf node
    //this implies that there is a string ending at the last currentNode
    current->is_leaf = 1;
    return root;
}

void printTrie(TrieNode* root)
{
    //print the nodes of the trie
    if (root == NULL) return;
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //print the current character in this currentNode
    cout << "->" << current->data;
    //iterate across the length of the children array to print the next character
    for (int i = 0; i < ALPHABET_SIZE; i++)
        printTrie(current->children[i]);
}

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

void print_prefix(TrieNode* root, char* prefix)
{
    if (isPrefixExist(root, prefix))
    //check if the prefix is found in the Trie
        cout << prefix << " is present in the Trie\n";
    else
        cout << prefix << " is not present in the Trie\n";
}

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

void print_search(TrieNode* root, char* word)
{
    if (search_word(root, word))
    //check if the word is found in the Trie
        cout << word << " is present in the Trie\n";
    else
        cout << word << " is not present in the Trie\n";
}

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
                lastBranchNode = current; //
                lastBranchChar = word[i];
            }
            current = current->children[idx];
        }
    }
    //now, the cnt is the count of characters in the last common prefix node
    int cnt = 0;
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

void print_delete(TrieNode* root, char* word)
{
    if (delete_word(root, word))
    //if the word is deleted in Trie
        cout << word << " is successfully deleted\n";
    else
        cout << word << " is not present in the Trie\n";
}

int main()
{
    //make a root node for the trie
    TrieNode* root = makeTrieNode('\0');

    //store the strings that we want to insert in the trie
    vector<char*>input = {"angel", "and", "advice", "brake", "break",
                          "breathe", "cat", "card", "cold", "gene",
                          "generous", "geek", "sea", "see", "season"};
    int len1 = input.size();    //number of insert operations in the trie
    //inserting
    for (int i = 0; i < len1; i++)
        root = insert_word(root, input[i]);
    //print the trie after insert
    cout << "Trie after insert: ";
    printTrie(root);
    cout << "\n\n";

    //store the strings that we want to search in the trie
    vector<char*>searchQuery = {"ant", "hello", "bag", "cat",
                                "dog", "sea", "hot"};
    int len2 = searchQuery.size();  //number of search operations in the trie
    //searching
    cout << "Searching:\n";
    for (int i = 0; i < len2; i++)
        print_search(root, searchQuery[i]);
    cout << "\n";

    //store the strings that we want to search prefix in the trie
    vector<char*>prefixQuery = {"an", "ba", "br", "ge",
                                "go", "se"};
    int len3 = prefixQuery.size();  //number of search operations in the trie
    //searching prefix
    cout << "Searching prefix:\n";
    for (int i = 0; i < len3; i++)
        print_prefix(root, prefixQuery[i]);
    cout << "\n";

    //store the strings that we want to delete in the trie
    vector<char*>deleteQuery = {"sea", "and", "cat", "hi"};
    int len4 = deleteQuery.size();  //number of delete operations in the trie
    //deleting
    cout << "Deleting:\n";
    for (int i = 0; i < len4; i++)
        print_delete(root, deleteQuery[i]);
    //print the trie after delete
    cout << "Trie after delete: ";
    printTrie(root);
    cout << "\n";

    //free trie node
    freeTrieNode(root);
    return 0;
}
