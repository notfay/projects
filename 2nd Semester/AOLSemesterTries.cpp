#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct node {
    struct node* children[ALPHABET_SIZE];
    char description[50];
    char slang[25];
    int word;
} node;

node* root = NULL;

node* createNode(const char description[],const char slang[]) {
    node* head = (node*)malloc(sizeof(node));
    
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        head->children[i] = NULL;
    }

    head->word = 0;
    strcpy(head->description, description);
    strcpy(head->slang, slang);

    return head;
}

node* insert(node* root, const char slang[], const char description[]) {
    int len = strlen(slang);
    int index;
    node* head = root;

    if(root == NULL) {
        root = createNode("", "");
        head = root;
    }

    for(int i = 0; i < len; i++) {
        index = slang[i] - 'a';

        if(head->children[index] == NULL) {
            head->children[index] = createNode("", "");
        }

        head = head->children[index];
    }


    head->word = 1;
    strcpy(head->description, description);
    strcpy(head->slang, slang);
    printf("*Added to the dictionary\n");

    return root;
}



void display(node* root, char str[], int level) {
    if (root == NULL) {
        printf("Currently Empty!, Please add slang to the dictionary!\n");
        return;
    }

    if (root->word) {
        str[level] = '\0';
        printf("\n- Slang: %s\n", str);
        printf("-Description: %s\n\n", root->description);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}

int search(node* root, char* slang) {
   if(root == NULL) {
    printf("\n*%s not Found\n\n", slang);
    return 0;
   }
    node* head = root;
    int len = strlen(slang);

    for(int i = 0; i < len; i++) {
        int index = slang[i] - 'a';

        if(head->children[index] == NULL) {
            return 0;
        }

        head = head->children[index];
    }

    if(head != NULL && head->word == 1) {
        printf("-Slang: %s\n", head->slang);
        printf("-Description: %s\n", head->description);
        return 1;
    }

    return 0;
}

int countWords(const char* check) { 
    int counter = 1, i; 
    for(i = 0; check[i] != '\0'; i++) {
        if(check[i] == ' ' && check[i+1] != ' ' && check[i+1] != '\0') {
            counter++;
        }
    }
    return counter;
}

int isValid(const char* slang) {
    if (strlen(slang) < 2) {
        return 1;
    }

    for (int i = 0; i < strlen(slang); i++) {
        if (isspace(slang[i])) {
            return 1;
        }
    }
    return 0;
}

int main () {
    int choice = 0;
    
    do {
        printf("\n1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");

        printf("\nInput Choices : ");
        scanf("%d", &choice);
        getchar(); // buffer

        if(choice == 1) {
            char addSlang[25];
            char addDesc[100];

            do {
                printf("\nInput a new slang word [Must be more than 1 characters and contains no space] :\n-");
                fgets(addSlang, sizeof(addSlang), stdin); 
                addSlang[strcspn(addSlang, "\n")] = '\0'; 
            } while (isValid(addSlang));

            printf("\n\n%s is a valid slang word!\n\n", addSlang);

            do {
                printf("\nInput a new slang word description [Must be more than 2 words] :\n-");    
                fgets(addDesc, sizeof(addDesc), stdin);
                addDesc[strcspn(addDesc, "\n")] = '\0'; 
            } while(countWords(addDesc) < 3);            

            root = insert(root, addSlang, addDesc);
            system("cls");
        }

        if(choice == 2) {
            char searchSlang[25];

            do {
                printf("Input slang word to search [Must be more than 1 characters and contains no space] : ");
                scanf("%s", searchSlang);
            } while (isValid(searchSlang));

            search(root, searchSlang);
        }

        if(choice == 4) {
            char str[100];
            display(root, str, 0);
        }

    } while(choice != 5);
  
    printf("Thank you... Have a nice day :)\n");
   
    
    return 0; 
}
