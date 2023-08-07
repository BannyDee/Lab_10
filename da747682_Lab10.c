#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct TrieBranch{	
    struct Trie *children[26];
    int count;
};
struct Trie{
    struct TrieBranch* root;
};
struct TrieBranch* nodeInit(){
    struct TrieBranch* new = (struct TrieNode*)malloc(sizeof(struct TrieBranch));
    if (new != NULL)
    {
        new->count = 0;
        for(int i = 0; i < 26; i++){
            new->children[i] = NULL;
        }
    }
    return new;
}
// Initializes a trie structure
struct TrieBranch* createTrie()
{
     struct Trie* myTree = (struct Trie*)malloc(sizeof(struct Trie));
     if(myTree){
        myTree->root = nodeInit(); 
    }
    myTree->root->count = 0;
    return myTree;
}
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if((pTrie == NULL)||(word == NULL)){
        return;
    }
    struct TrieBranch* temp = pTrie->root;
    for(int i = 0;word[i];i++){
        int j = word[i] - 'a';
        if(temp->children[j] == NULL){
            temp->children[j] = nodeInit();
        }
        temp = temp->children[j];
    }
    temp->count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char *word)
{
    if((pTrie == NULL)||(word == NULL)){
        return 0;
    }
    int i = 0;
    struct TrieBranch* temp = pTrie->root;
    while(word[i]){
        int j = word[i] - 'a';
        if(temp->children[j] == NULL){
            return 0;
        }
        temp = temp->children[j];
        ++i;
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie* pTrie)
{
    if(pTrie == NULL){
        return 0;
    }
    if(pTrie->root != NULL){
        for(int i = 0; i < 26; i++){
            if(pTrie->root->children[i] != NULL){
                deallocateTrie(pTrie->root->children[i]);
            }
        }
        free(pTrie->root);
    }
    free(pTrie);
    return 0;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){ 
        printf("Unable to Open File");
        return 0;
    }
    int num = 0;
    fscanf(fp, "%d",&num);
    for(int i = 0; i < num;i++){
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return num;
}

int main()
{
	char *inWords[256];
    printf("What\n");
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++){
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL){
		printf("There is an error in this program\n");
    }
    for(int i = 0; i< numWords; i++){
        free(inWords[i]);
    }
    return 0;
}