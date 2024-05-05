#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Stored in GitHub, projects>2nd Semester > AOLSemester2Tries.cpp

//Sebelumnya soal ini saya buat juga dengan metode BST, karena saya kira kalau trie dan tree itu sama saja
//karena berhubung contoh kode belum ditunjukkan saya minta izin untuk mengambil referensi dari beberapa website

//Reference from :
// - BNS : https://view.officeapps.live.com/op/view.aspx?src=https%3A%2F%2Fstbm7resourcesprod%2Eblob%2Ecore%2Ewindows%2Enet%3A443%2Fresources%2Fgeneral%5Fcourse%5Foutline%2Fcourse%5Foutline%2Fmain%5Fmaterial%2FRS1%2F024369%2F20240112105037D6660%5FSesi%252017%2520%2D%2520Trie%2Epptx%3Fsv%3D2020%2D08%2D04%26st%3D2024%2D05%2D03T04%253A00%253A18Z%26se%3D2024%2D05%2D03T10%253A15%253A18Z%26sr%3Db%26sp%3Dr%26sig%3DU5aFX8pX2fhc%252F3NJhtS4YKX0UZjGrs%252FIh0otwfAis6s%253D&wdSlideId=256&wdModeSwitchTime=1714709741926
// - SF : https://www.sanfoundry.com/c-program-implement-trie/
// - DG : https://www.digitalocean.com/community/tutorials/trie-data-structure-in-c-plus-plus
// - TRGMBR : https://www.google.com/url?sa=i&url=https%3A%2F%2Fbootcamp.uxdesign.cc%2Fwhat-is-trie-data-structure-why-do-you-need-it-c11dbcdfa75b&psig=AOvVaw3N2HpeQjoJlhJvV4uYx25m&ust=1714964946002000&source=images&cd=vfe&opi=89978449&ved=0CBIQjRxqFwoTCOj_lbXE9YUDFQAAAAAdAAAAABAE 

#define ALPHABET_SIZE 26

// BNS, DG, SF
typedef struct node {
    struct node* children[ALPHABET_SIZE];   //Ini memasukkan nodenya setiap karakter
    char description[50];       //Deskripsi slang
    char slang[25]; //Slangnya
    int word;   //cek apakah dia di akhir kata atau bukan // nge flag
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
    int index;  
    node* head = root;

    if(root == NULL) {  //apabila dictionary kosong
        root = create("", "");  //akan dibuat node baru, tapi dengan  isinya kosong terlebih dahulu
        printf("*Added to the dictionary\n");   //karena pada awalan trie itu paling atas adalah root, lalu leafnya di isi dengan karakter alphabet (TRGMBR untuk referensi)
        head = root;    //dijadikan paling atas
    }

    //masuk ke else apabila sudah ada

    for(int i = 0; i < len; i++) {  //Looping setiap karakter pada string slang
        index = slang[i] - 'a'; // menghitung indeks berdasarkan karakter slang yang diinput 

        if(head->children[index] == NULL) { // cek, jika tidak ada anak pada indeks yang diberikan / NULL
            head->children[index] = create("", ""); //dibuat node dengan isinya kosong terlebih dahulu yang nantinya akan diisi oleh slang dan deskripsi  
        }

        head = head->children[index]; //sama saja kaya traverse di linkedlist, tapi dia akan traverse di setiap karakter 
    }

    head->word = 1; //flagged, tandanya udh di akhir kata

    strcpy(head->description, description); //memasukkan deskripsi  yang user input ke dalam ndoenya
    strcpy(head->slang, slang); //memasukkan slang yang user input ke dalam node
    printf("*Added to the dictionary\n"); 

    return root;
}


//DG
void display(node* root, char str[], int level) {
    if (root == NULL) {
        printf("Currently Empty!, Please add slang to the dictionary!\n"); //Jika di dictionary belum ada apa2,maka di display ini
        return;
    }

    if (root->word) {       //
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

//SF, DG
int search(node* root, char* slang) {
   if(root == NULL) {
    printf("\n*%s not Found\n\n", slang);   //Jika yg kita cari tidak ada di dictionary, maka dia akan diberikan pesan ini
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

            root = insert(root, addSlang, addDesc);
            system("cls");
        }

        if(choice == 2) {
            char searchSlang[25];   //Ini adalah slang yang ingin kita cari 

            do {
                printf("Input slang word to search [Must be more than 1 characters and contains no space] : ");
                scanf("%s", searchSlang);
            } while (isValid(searchSlang)); //sama seperti diatas, ini untuk memastikan inputan yang kita masukkan valid

            search(root, searchSlang);  //Setelah sesuai dengan syarat maka bisa lanjut untuk dicari 
        }

        if(choice == 4) {
            char str[100];  
            display(root, str, 0);
        }

    } while(choice != 5);
  
    printf("Thank you... Have a nice day :)\n");
   
    
    return 0; 
}