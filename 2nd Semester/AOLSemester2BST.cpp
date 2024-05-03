#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{        //Standard pembentukan node biasa yang berisi kalimat untuk slangnya dan deskripsi
    char slang[50];
    char description[50];

    struct node* left;
    struct node* right; //karena dia itu tree maka dia akan mempunyai leaf dari kiri dan kanan

}node;

node* create(const char* slang, const char* description) { //harus menggunakan const char* kalau tidak akan mendapatkan error ini OLSemester2.cpp:63:43: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings] AOLSemester2.cpp:64:46: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings] root = insert(root, "LMAO", "Laughing My");
    node* head = (node*)malloc(sizeof(node));   //di C++ harus menggunakan (node*) terlebih dahulu

    strcpy(head->slang, slang);                 //strcpy digunakan untuk nge copy kalimat yang ada di char slang dan dimasukkan ke dalam node leafnya
    strcpy(head->description, description);

    head->left = NULL;                          
    head->right = NULL;

    return head;
}

 //Menu pertama
node* insert(node* root, const char* slang, const char* description) {  //Standard insert tree biasa, referensi tentunya dari yang diajarkan di kampus
    if (root == NULL) {
        printf("Added to the dictionary\n");
        return create(slang, description);
    }
    if (strcmp(root->slang, slang) > 0) {                      
        root->left = insert(root->left, slang, description);    //karena syaratnya adalah  lexicographical maka harus dibalik agar saat di display berdasarkan lexicographical
    } 
    else if (strcmp(root->slang, slang) < 0) {                      //sebagai contoh bila dicoding seperti biasa (right berarti > 0) dan (left berarti < 0) maka bila menggunakan input "simp", "da", "rizz", maka outputnya berurutan dari yang paling atas adalah simp, rizz, da
        root->right = insert(root->right, slang, description);          //karena ini dibalik maka outputnya akan menjadi da, rizz, simp, sesuai dengan yg ada di soal
    }
    else {
        strcpy(root->slang, slang);                 //else ini apabila ditemukan kata yang sama, maka akan diupdate slang dan deskripsinya menjadi yang paling baru
        strcpy(root->description, description);
        printf("Updated the word %s with new description\n", root->slang); 
    }

    return root;
}


 //Menu kedua
node* search(node* root, const char* slang) {  //Standard tree search function, referensi juga dari yang diajarkan di kampus 
    if(root == NULL) {
        printf("\n%s Not found in dictionary\n\n", slang);                 //Syaratnya apabila tidak ditemukan maka akan display pesan ini                     
        return NULL;
    }
    if(strcmp(root->slang, slang) == 0) {               //Ini saat ditemukan, apabila saat di strcmpr kalimat dari yang ingin kita cari (const char* slang) ternyata sama ( == 0) dengan yang ada di tree maka akan di printf isi dari node leaf tersebut
        printf("\nSlang word : %s\n", root->slang);
        printf("Description : %s\n", root->description);
        return root;                                               
    }
    if(strcmp(root->slang, slang) < 0) {
        return search(root->left, slang);
    }
    else {
        return search(root->right, slang);
    }
}

//Menu keempat
void disIn(node* root) {        //Inorder, bisa dibilang ini akan printf dari yang terkecil sampai terbesar
    if(root == NULL) return;

        disIn(root->left);
        printf("\n-%s\n", root->slang);         
        disIn(root->right);
  
}
    
int countWords(const char* check) { //Referensi dari sanfoundry.com (function untuk count words in string)
    int counter = 1, i; 
    for(i = 0; check[i] != '\0'; i++) { //Loop untuk mengecek apakah ada spasi, in akan loop sampe eol stringnya
        if(check[i] == ' ' && check[i+1] != ' ' && check[i+1] != '\0') {  //bila saat loop ditemukan spasi(berarti kalimatnya sudah selesai), dan di character berikutnya (i+1) itu bukan spasi dan eol maka akan count menambah jadi 1  
            counter++;                                                    //apabila tidak memenuhi ini maka tandanya dia masih di kalimat itu 
        }
    }
    return counter;
}

int isValid(const char* slang) {    //Function untuk ngecek apakah inputan memenuhi syarat (lebih dari 2 karakter dan tidak ada spasi)
    
    if (strlen(slang) < 2) {    //Ngecek apakah panjang karakter dia kurang dari 2, 
        return 1;
    }

    for (int i = 0; i < strlen(slang); i++) {
        if (isspace(slang[i])) {                //Nge loop satu per satu  untuk nge cek apakah ada spasi, pengecekan menggunakan library ctype,h = isspace
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

    getchar();          //buffer

    if(choice == 1) {

        char addSlang[25];
        char addDesc[100];


         do {
                printf("Input a new slang word [Must be more than 1 characters and contains no space] :\n-");
                fgets(addSlang, sizeof(addSlang), stdin); //sama seperti scanf, fgets digunakan untuk input string, tapi fgets i mengambil inputan sampai eol, dan tidak akan mengambil inputan yang berlebihan
                addSlang[strcspn(addSlang, "\n")] = '\0'; //menggunakan fgets agar bug dibawah tidak terjadi, ini buat ngapus line terakhir (\n) 
            } while (isValid(addSlang));


        // do {
        //     printf("Input a new slang word [Must be more than 1 characters and contains no space] :\n-");   //Bug disini dimana saat kita input "d a" output ini akan double
        //     scanf("%s", addSlang); 
        // } while (isValid(addSlang));


        printf("\n\n%s is a valid slang word!\n", addSlang);


       do {
            printf("\nInput a new slang word description [Must be more than 2 words] :\n-");    //dia akan terus looping sampai syarat dibawah terpenuhi
            scanf(" %[^\n]", addDesc);                      //disini akan diminta untuk input deskripsi, dan akan di loop terus sampai syarat dibawah terpenuhi
        } while(countWords(addDesc) < 3);            //deskripsi yang telah diinput akan di cek di function ini apa sudah memenuhi syaratnya 

        root = insert(root, addSlang, addDesc);         //bila sudah memenuhi semua syarat diatas maka akan dimasukkan ke tree
        system("cls");                      //ini untuk membersihkan screen terminal
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


