#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct node{
    char definition[1000];
    struct node *alphabet[26];
    int tail;
};

struct node *root = NULL;

struct node *newData(){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->tail = 0;

    for(int i = 0; i < 26; i++){
        newNode->alphabet[i] = NULL;
    }
    return newNode;
}

void insertData(struct node * root, const char * slang, char definition[]){
    struct node * curr = root;

    for(int i = 0; i < strlen(slang); i++){
        int index = slang[i] - 'a';
    
        if(!curr->alphabet[index]){
            curr->alphabet[index] = newData();
        }
        curr = curr->alphabet[index];
    }
    if(curr->tail == 1){
        printf("Successfully updated new slang word.\n");
    }else{
        printf("Successfully released new slang word.\n");
    }
    strcpy(curr->definition, definition);
    curr->tail = 1;
}

int slangValidation(char * slang){
    int len = strlen(slang);

    if(len < 2){
        return 0;
    }
    for(int i = 0; i < len; i++){
        if(slang[i] == ' '){
            return 0;
        }
    }
    return 1;
}

int definitionValidation(char * definition){
    int len = strlen(definition);
    int wordCheck = 0, space = 0;

    for(int i = 0; i < len; i++){
        if(definition[i] == ' ' && space == 0){
            wordCheck++;
            space = 1;
        }
        if(definition[i] != ' '){
            space = 0;
        }
    }

    if(wordCheck > 1){
        return 1;
    }else{
        return 0;
    }
}

struct node *searchData(struct node * root, const char * slang){
    struct node * curr = root;

    for(int i = 0; i < strlen(slang); i++){
        int index = slang[i] - 'a';
    
        if(!curr->alphabet[index]){
            return NULL;
        }
        curr = curr->alphabet[index];
    }
    return curr;
}

bool unfound(struct node * root){
    for(int i = 0; i < 26; i++){
        if(root->alphabet[i]){
            return false;
        }
    }
    return true;
}

int x = 1;
void printData(struct node * root, const char * slang){
    struct node * curr = root;
    char word[100];

    if(curr->tail){
    	
        printf("%d. %s\n", x++, slang);
        return;
    }

    for(int i = 0; i < 26; i++){
        if(curr->alphabet[i]){
            strcpy(word, slang);
            word[strlen(slang)] = i + 'a';
            word[strlen(slang) + 1] = '\0';
            printData(curr->alphabet[i], word);
        }
    }
}

void displayData(struct node * root, const char * slang){
    char wordData[100];
    strcpy(wordData, slang + strlen(slang));
    printData(root, wordData);
}

int y = 1;

void printPrefix(struct node * curr, const char * prefix, char * wordData){
    if(curr->tail){
        printf("%d. %s%s\n", y++, prefix, wordData);
    }
    for(int i = 0; i < 26; ++i){
        if(curr->alphabet[i]){
            wordData[strlen(wordData)] = i + 'a';
            wordData[strlen(wordData) + 1] = '\0';
            printPrefix(curr->alphabet[i], prefix, wordData);
            wordData[strlen(wordData) - 1] = '\0';
        }
    }
}

void displayPrefix(struct node * root, const char * prefix){
    struct node * curr = root;
    for(int i = 0; i < strlen(prefix); ++i){
        int index = prefix[i] - 'a';
        if(!curr->alphabet[index]){
            return;
        }
        curr = curr->alphabet[index];
    }
    char word[100];
    word[0] = '\0';
    printPrefix(curr, prefix, word);
}

int main(){
    root = newData();

    int choice;
    char slang[100];
    char definition[1000];
    char search[100];
    char prefix[100];

    struct node *findResult;
    struct node *findPrefix;

    do{
        puts(" ");
        printf("Hello, welcome to Boogle!\n");
        printf("Select 1 of this 5 menu :\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Input your choice: ");
        scanf("%d", &choice);
        getchar();
        puts("");

        switch(choice){
            case 1:
                do{
                    printf("Input a new slang word (Must be more than 1 char and contains no space!) : ");
                    scanf("%[^\n]", slang);
                    getchar();
                } while(slangValidation(slang) != 1);
                do{
                    printf("Input a new slang word desc (Must be more than 2 words) : ");
                    scanf("%[^\n]", definition);
                    getchar();
                } while(definitionValidation(definition) != 1);

                insertData(root, slang, definition);

                break;

            case 2:
                do{
                    printf("Input a slang word to be search (Must be more than 1 char and contains no space!) : ");
                    scanf("%s", search);
                    getchar();
                } while(slangValidation(search) != 1);

                findResult = searchData(root, search);

                if(findResult){
                    printf("Slang word              : %s\n", search);
                    printf("Slang word definition   : %s\n", findResult->definition);
                } else{
                    printf("There is no word \"%s\"  in the dictionary.\n",search);
                }
                break;

            case 3:
                printf("\nInput a prefix to be search: ");
                scanf("%s", prefix);
                getchar();

                findPrefix = searchData(root, prefix);
                if(findPrefix){
                    printf("Words starting with \"%s\": \n", prefix);
                    displayPrefix(root, prefix);
                } else{
                    printf("There is no slang word yet in the dictionary.\n");
                }
                y = 1;

                break;

            case 4:
                if(unfound(root)){
                    puts("There is no slang word yet in the dictionary.");
                }else{
					puts("List of all slang words in the dictionary: ");
                    displayData(root, slang);
            	}
                x = 1;
                break;

            case 5:
                printf("Thank you... Have a nice day :)\n");
                puts("");
                break;

            default:
                printf("Invalid input\n");
                puts("");
        }
    } while(choice != 5);

    return 0;
}
