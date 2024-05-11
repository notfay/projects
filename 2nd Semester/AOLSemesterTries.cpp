#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Stored in GitHub, projects>2nd Semester > AOLSemester2Tries.cpp
//To-Do : 

//Sebelumnya soal ini saya buat juga dengan metode BST, karena saya kira kalau trie dan tree itu sama saja
//karena berhubung contoh kode belum ditunjukkan saya minta izin untuk mengambil referensi dari beberapa website

//Reference from :
// - BNS : BINUS Data Structure - Trie PPT
// - SF : https://www.sanfoundry.com/c-program-implement-trie/
// - DG : https://www.digitalocean.com/community/tutorials/trie-data-structure-in-c-plus-plus
// - TRGMBR : https://www.google.com/url?sa=i&url=https%3A%2F%2Fbootcamp.uxdesign.cc%2Fwhat-is-trie-data-structure-why-do-you-need-it-c11dbcdfa75b&psig=AOvVaw3N2HpeQjoJlhJvV4uYx25m&ust=1714964946002000&source=images&cd=vfe&opi=89978449&ved=0CBIQjRxqFwoTCOj_lbXE9YUDFQAAAAAdAAAAABAE 

#define ALPHABET_SIZE 26

// BNS, DG, SF
typedef struct node {
    struct node* children[ALPHABET_SIZE];   //Ini memasukkan nodenya setiap karakter
    char description[50];       //Deskripsi slang
    char slang[25]; //Slangnya
    int word;   //untuk cek apakah dia di akhir kata atau bukan // nge flag, 0 berarti gaada dan 1 berarti ada
} node;

node* root = NULL;  //global variabel set root ke NULL

//DG. BNS
node* create(const char description[],const char slang[]) { //harus menggunakan const char* kalau tidak akan mendapatkan error ini OLSemester2.cpp:63:43: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings] AOLSemester2.cpp:64:46: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings] root = insert(root, "LMAO", "Laughing My");
    node* head = (node*)malloc(sizeof(node));   //Mengalokasikan memori untuk node
    
    for(int i = 0; i < ALPHABET_SIZE; i++) {   //Looping untuk setiap karakter
        head->children[i] = NULL;           //sama seperti di bst dan linked list kita akan null kan setiap karakternya
    }

    head->word = 0; 
    strcpy(head->description, description); //copy deskripsi ke node, seperti di bst dan linkedlist
    strcpy(head->slang, slang); //copy slang ke node, seperti di bst dan linkedlist

    return head;
}

//DG, SF, TRGMBR
node* insert(node* root, const char slang[], const char description[]) {    
    int len = strlen(slang);    //menghitung panjang slang untuk bisa di loop
    int index;  //nentuin dimana posisi node baru dan yang bakalan dimasukkin ke dalam dictionary
    node* head = root;

    if(root == NULL) {  //apabila dictionary kosong
        root = create("", "");  //akan dibuat node baru, tapi dengan  isinya kosong terlebih dahulu
        head = root;    //dijadikan paling atas
    }   //karena pada awalan trie itu paling atas adalah root, lalu leafnya di isi dengan karakter alphabet (TRGMBR untuk referensi)

    //masuk ke else apabila sudah ada

    for(int i = 0; i < len; i++) {  //Looping setiap karakter pada string slang
        index = slang[i] - 'a'; // menghitung indeks berdasarkan karakter slang yang diinput 

        if(head->children[index] == NULL) { // cek, jika tidak ada anak pada indeks yang diberikan / NULL
            head->children[index] = create("", ""); //dibuat node dengan isinya kosong terlebih dahulu yang nantinya akan diisi oleh slang dan deskripsi  
        }

        head = head->children[index]; //sama saja kaya traverse di linkedlist, tapi dia akan traverse di setiap karakter 
    }

    if(head->word) {
        strcpy(head->description, description);
        printf("and updated the description\n", slang); //apabila kata yang diinput sudah ada, maka deskripsi akan diupdate
    }

    head->word = 1; //flagged, tandanya udh di akhir kata

    strcpy(head->description, description); //memasukkan deskripsi  yang user input ke dalam ndoenya
    strcpy(head->slang, slang); //memasukkan slang yang user input ke dalam node
    printf("\n%s Added to the dictionary\n", slang); 

    return root;
}


//DG
void display(node* root, char str[], int level) { 
    if (root == NULL) { //parameter level itu nentuin di level / kedalaman berapa dia ,  str itu untuk menyimpan gabungan dari node-node yang ada di dictionary
        printf("Currently Empty!, Please add slang to the dictionary!\n"); //Jika di dictionary belum ada apa2,maka di display ini
        return;
    }

    if (root->word) {       //Jika sudah di akhir kata, maka akan di display semua gabungan node slangnya dan deskripsi
        str[level] = '\0';  //Menambahkan null terminator untuk mengakhiri string
        printf("\n-Slang: %s\n", str); //Slang di dictionary di display 
        printf("-Description: %s\n\n", root->description); //Deskripsi di display juga
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {   //Looping ke semua yg ada di dictionary
        if (root->children[i]) {    //Jika ada di dictionary
            str[level] = i + 'a'; //Menggabungkan karakter yang ada di dictionary
            display(root->children[i], str, level + 1); //Recursion, prosesnya diulang, untuk gabungin semua karakter yang ada di dictionary
        }
    }
}

//SF, DG
int search(node* root, char* slang) {
   if(root == NULL) {
    printf("\nError: %s not Found\n\n", slang);   //Jika yg kita cari tidak ada di dictionary, maka dia akan diberikan pesan ini
    return 0;
   }
    node* head = root;  //sma sperti di linkedlist yang menggunakan node* ptr tapi saya menggunakan head
    int len = strlen(slang);    //Menghitung panjang slang

    for(int i = 0; i < len; i++) {  //Looping setiap karakter pada string slang
        int index = slang[i] - 'a';  //menghitung indeks berdasarkan karakter slang yang diinput

        if(head->children[index] == NULL) { // cek, jika tidak ada anak pada indeks yang diberikan / NULL
            printf("\nError: %s not Found\n\n", slang);
            return 0; //berarti gaada di dictionary
        }

        head = head->children[index]; //traverse ke yang sesuai dengan karakter slang
    }

    if(head != NULL && head->word == 1) { //Jika ditemukan dan di akhir kata
        printf("\n-Slang: %s\n", head->slang);    //Akan di display 
        printf("-Description: %s\n", head->description);
        return 1;
    }

    return 0;
}


void searchPrefixRecursive(node* root, char searchSlang[], int n, char prefix[]) {
    if(root->word == 1) {   //Jika sudah di akhir kata, maka akan di display semua gabungan node slangnya dan deskripsi
        searchSlang[n] = '\0'; //Menambahkan null terminator untuk mengakhiri string
        printf("\n-Slang : %s%s\n", prefix, searchSlang);
        printf("-Desciption : %s\n\n", root->description); 
    }

    for(int i = 0; i < ALPHABET_SIZE; i++) { //Looping ke semua yg ada di dictionary
        if(root->children[i] != NULL) { //cek apakah ada anak pada posisi indeks i
            searchSlang[n] = 'a' + i; //nambahkan karakter yang sesuai ke dalam array searchSlang
            searchPrefixRecursive(root->children[i], searchSlang, n + 1, prefix);
        }
    }
}


//BNS
void searchPrefix(node* root, char prefix[]) {
    if(root == NULL) {
        printf("Currently Empty! Please add slang to the dictionary!\n");   //Kalo gaada apa2 dikasih pesan ini
        return;
    }

    int n = strlen(prefix);
    node* head = root;
    int last = 0; //flag untuk menandai apakah prefix tidak ditemukan dalam dictionary

    for(int i = 0; i < n && last == 0; i++) {
        int index = prefix[i] - 'a'; //menghitung indeks berdasarkan karakter slang yang diinput
        if(head->children[index] == NULL) { // cek, jika tidak ada anak pada indeks yang diberikan / NULL
            printf("Error: There is no prefix \"%s\" in the dictionary.\n", prefix); 
            last = 1; //berarti gaada di dictionary 
        } else { 
            head = head->children[index]; //traverse ke yang sesuai dengan karakter slang
        }
    }

    if (!last) { //Jika ada
        printf("\nWords starts with \"%s\":\n", prefix); //Maka akan di display 
        char searchSlang[25]; //Buffer untuk penyimpanan sementara kata yang ditemukan
        searchPrefixRecursive(head, searchSlang, 0, prefix); //Recursion, prosesnya diulang, untuk gabungin semua karakter yang ada di dictionary
    }
}



int countWords(const char* check) { 
    int counter = 1;     //loop ini untuk menentukan jumlah kalimat yang ada di string
    for(int i = 0; check[i] != '\0'; i++) {  //akan looping mulai dari awal string sampai belum eol   
        if(check[i] == ' ' && check[i+1] != ' ' && check[i+1] != '\0') {    //disini akan di loop  sampai ketemu spasi, dan dia ngecek apakah kata selanjutnya (i+1) bukan spasi dan bukan eol, maka counter bertambah (jadi tandanya itu adalah satu kata)
            counter++;                  
        }                               //semoga bisa dipahamin karena nge jelasinnya aga susah .-.
    }
    return counter;     //return counter ke main
}

int isValid(const char* slang) {
    if (strlen(slang) < 2) {    //cek apakah panjang string kurang dari 2, jika iya maka return 1
        return 1;
    }

    for (int i = 0; i < strlen(slang); i++) {   //loop perkata samopai eol
        if (isspace(slang[i])) {               //cek apakah ada spasi, menggunakan isspace yang dari library ctype.h, jika ditemukan spasi maka return 1
            return 1;
        }
    }
    return 0;       //jika tidak ada spasi dan panjang string lebih dari 2 maka return 0 (valid)
}

int main () {
    int choice = 0; //pilihan menu
    

    do {
        printf("\n1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix\n");     //Opsi yang diberikan
        printf("4. View all slang words\n");
        printf("5. Exit\n");

        printf("\nInput Choices : ");   //Input choice user
        scanf("%d", &choice);
        getchar(); // buffer

        if(choice == 1) {
            char addSlang[25];
            char addDesc[100];
            system("cls");

            do {
                printf("\nInput a new slang word [Must be more than 1 characters and contains no space] :\n-");
                fgets(addSlang, sizeof(addSlang), stdin); //sama seperti scanf, fgets digunakan untuk input string, tapi fgets i mengambil inputan sampai eol, dan tidak akan mengambil inputan yang berlebihan
                addSlang[strcspn(addSlang, "\n")] = '\0';  //menggunakan fgets agar bug dibawah tidak terjadi, ini buat ngapus line terakhir (\n) 
            } while (isValid(addSlang));

            // do {
            // printf("Input a new slang word [Must be more than 1 characters and contains no space] :\n-");           //Bug disini dimana saat kita input "d a" output ini akan double
            //scanf("%s", addSlang); 
            // } while (isValid(addSlang));


            printf("\n\n%s is a valid slang word!\n\n", addSlang);

            do {
                printf("\nInput a new slang word description [Must be more than 2 words] :\n-");    //dia akan terus looping sampai syarat dibawah terpenuhi
                scanf(" %[^\n]", addDesc);                      //disini akan diminta untuk input deskripsi, dan akan di loop terus sampai syarat dibawah terpenuhi
            } while(countWords(addDesc) < 3);            //deskripsi yang telah diinput akan di cek di function ini apa sudah memenuhi syaratnya          

            root = insert(root, addSlang, addDesc);     //akhirnya akan dimasukkan ke dalam dictionary

            printf("\nPress enter to continue... ");
            while(getchar() != '\n');
            getchar();
            system("cls");
            
        }

        if(choice == 2) {
            char searchSlang[25];   //Ini adalah slang yang ingin kita cari 
           

            do {
                printf("Input slang word to search [Must be more than 1 characters and contains no space] : ");
                fgets(searchSlang, sizeof(searchSlang), stdin); //sama seperti scanf, fgets digunakan untuk input string, tapi fgets i mengambil inputan sampai eol, dan tidak akan mengambil inputan yang berlebihan
                searchSlang[strcspn(searchSlang, "\n")] = '\0';
            } while (isValid(searchSlang)); //sama seperti diatas, ini untuk memastikan inputan yang kita masukkan valid

            search(root, searchSlang);  //Setelah sesuai dengan syarat maka bisa lanjut untuk dicari 

            printf("\nPress enter to continue... ");
            while(getchar() != '\n');
            getchar();
            system("cls");

        }

        if(choice == 3 ) {
            char prefix[25];  // Ini adalah prefix yang ingin kita cari
            printf("\nInput a prefix to be searched: ");
            scanf("%s", prefix);

            searchPrefix(root, prefix);

            printf("\nPress enter to continue... ");
            while(getchar() != '\n');
            getchar();
            system("cls");
        }


        if(choice == 4) {
            char str[100]; 
            display(root, str, 0); 

            printf("\nPress enter to continue... ");
            while(getchar() != '\n');
            getchar();
            system("cls");
        }
        
        if(choice == 6) {

            system("cls");
            printf("Sebelumnya saya juga udah pernah buat project ini menggunakan bst, karena saya kira trie itu sama aja kaya tree, ternyata beda\n\n");
            printf("Untuk melihat yang versi bst (belum complete tapi) bisa melalu link ini : \n\"https://github.com/notfay/projects/blob/main/2nd%%20Semester/AOLSemester2BST.cpp\"  ( bismillah tambahan point :) ) \n");
            printf("\n\nUntuk mengakhiri ada pepatah yang pernah menyebutkan, \"When i wrote this code, only God and I understood what it did. Now, only God knows\" \n");
        
            break;
        }

    } while(choice != 5);
  
    printf("Thank you... Have a nice day :)\n");
   
    return 0; 
}
