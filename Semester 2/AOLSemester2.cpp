#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
    char slang[50];
    char description[50];

    struct node* left;
    struct node* right;

}node;

node* create(const char* slang, const char* description) {
    node* head = (node*)malloc(sizeof(node));

    strcpy(head->slang, slang);
    strcpy(head->description, description);

    head->left = NULL;
    head->right = NULL;

    return head;
}


node* insert(node* root, const char* slang, const char* description) {
    if (root == NULL) {
        return create(slang, description);
    }
    if (strcmp(root->slang, slang) > 0) {                       //Menu pertama
        root->left = insert(root->left, slang, description);
    } 
    else if (strcmp(root->slang, slang) < 0) {
        root->right = insert(root->right, slang, description);
    }
    else {
        strcpy(root->slang, slang);
        strcpy(root->description, description);
    }

    return root;
}


node* search(node* root, const char* slang) {
    if(root == NULL) {
        printf("\n%s Not found in dictionary\n\n", slang);                                    
        return NULL;
    }
    if(strcmp(root->slang, slang) == 0) {
        printf("\nSlang word : %s\n", root->slang);
        printf("Description : %s\n", root->description);
        return root;                                                //Menu kedua
    }
    if(strcmp(root->slang, slang) < 0) {
        return search(root->left, slang);
    }
    else {
        return search(root->right, slang);
    }
}


void disIn(node* root) {
    if(root == NULL) {
        return;
    }

        disIn(root->left);
        printf("\n-%s\n", root->slang);         //Menu keempat
        disIn(root->right);
        
    
}
    
int countWords(const char* word) {
    int count = 1, i; 
    for(i = 0; word[i] != '\0'; i++) {
        if(word[i] == ' ' && word[i+1] != ' ' && word[i+1] != '\0') {   //Web
            count++;
        }
    }
    return count;
}

int isValid(const char* slang) {
    
    if (strlen(slang) < 2) {    //Ngecek apakah dia kurang dari 2, kalo iya balikin 1
        return 1;
    }

    for (int i = 0; i < strlen(slang); i++) {
        if (isspace(slang[i])) {                //Nge loop satu per satu katanya untuk nge cek apakah ada spasi, pengecekan menggunakan library ctype,h = isspace
            return 1;
        }
    }
    return 0;
}



int main () {

    node* root = NULL;
    int choice = 0;
    
    do {
    
    printf("1. Release a new slang word\n");
    printf("2. Search a slang word\n");
    printf("3. View all slang words starting with a certain prefix\n");
    printf("4. View all slang words\n");
    printf("5. Exit\n");

    printf("\nInput Choices : ");
    scanf(" %d", &choice);

    getchar();

    if(choice == 1) {

        char addSlang[25];
        char addDesc[100];


         do {
                printf("Input a new slang word [Must be more than 1 characters and contains no space] :\n-");
                fgets(addSlang, sizeof(addSlang), stdin); 
                addSlang[strcspn(addSlang, "\n")] = '\0'; //menggunakan fgets agar bug dibawah tidak terjadi, ini buat ngapus line terakhir (\n) 
            } while (isValid(addSlang));


        // do {
        //     printf("Input a new slang word [Must be more than 1 characters and contains no space] :\n-");   //Bug disini dimana saat kita input "d a" output ini akan double
        //     scanf("%s", addSlang); 
        // } while (isValid(addSlang));


        printf("\n\n%s is a valid slang word!\n", addSlang);


       do {
            printf("\nInput a new slang word description [Must be more than 2 words] :\n-");
            scanf(" %[^\n]", addDesc); 
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
        disIn(root);
    }

} while(choice != 5);
  
    printf("Thank you... Have a nice day :)\n");
    
    return 0; 

}


