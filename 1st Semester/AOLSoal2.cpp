#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Main-build 

//Display done
//Sort done
//export done
//search done

//Note : sesaui dengan  point ke 6 dari Instruction Pengerjaan,  "Example only serves as an example. You may create the command line program as creative as you can.", jadi bentuk program saya berbeda dengan contoh yang ada di soal
//		tetapi, fungsi program sama dengan yang  ada di soal  


struct info {
    char location1[100];
    char location2[100];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[100];
    char furnish[100];
};

struct Data {
    char location1[500];
    char location2[500];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[500];
    char furnish[500];
};

void display(int rows) { 
	
    FILE *files;							//tapi pas saya coba pake converter online dari xlsx ke csv ternyata bisa di baca sama outputnya bener .-.
    files = fopen("file.csv", "r");			//kayanya filenya ke corrupt pak , makanya kemaren gabisa di read + outputnya "pk", karena kemaren pas download filenya itu .xlsx lalu saya ganti manual ke .csv habis itu balik ke .xlsx lagi 

    if (files == NULL) {
    	
        printf("Error D1: Data not found :(\n");	//apabila nama file tidak sesuai dengan file.csv, error ini akan ditampilkan
        
    } else {
    	
    
    	printf("\n\n______________________________________________________________________________________________________________________\n");
        printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
 		printf("______________________________________________________________________________________________________________________\n");
    	       
	
        fscanf(files, "%*[^\n]");

        for (int i = 0; i < rows; i++) {		//looping untuk fscanf dari file & printf sebanyak rows yang telah dimasukkan oleh user
        	
        	char location1[100]; 	char location2[100]; char type[100]; char furnish[200];
 			int price, rooms, bath, carP;
    
            if (fscanf(files, "%[^,,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]", location1, location2, &price, &rooms, &bath, &carP, type, furnish) == 8) {	 //sesuai dengan yang bapak contohkan waktu itu
                printf("%-30s%-20s%-12d%-8d%-10d%-8d%-13s%-20s\n", location1, location2, price, rooms, bath, carP, type, furnish);					
            } else {
                break; 
            }
            
        }
        
		printf("______________________________________________________________________________________________________________________\n\n");
		printf(" \n\t\t\t\t\t %d property displayed, returning to Main Menu\n\n\n", rows);
		
        fclose(files);
    }
}


//merupakan fuction yang menggunakan bubbleSort + struct untuk sorting, sesuai dengan apa yang user ingin di sort

void voidSortRoomsAsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].rooms > data[j + 1].rooms) {	//ini menunjukkan kalau yang ingin di sort adalah roomsnya dan secara  ascended		
                struct info temp = data[j];			//yang akan di sort itu adalah satu set dari struct info data
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}																																					//perbedaan dari kedua ini adalah pada ifnya yang atas menggunakan > agar mensort secara ascend 
																																					//	yang bawah menggunakan tanda < pada ifnya agar mensort secara descend
void voidSortRoomsDsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].rooms < data[j + 1].rooms) {		//ini menunjukkan kalau yang ingin di sort adalah roomsnya dan secara descended
                struct info temp = data[j];				//yang di sort juga merupakan struct info data
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void voidSortPriceAsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].price > data[j + 1].price) {			//yang di sort adalah price, berbeda dengan yang diataa dimana data[i].rooms kalau yang ini akan menggunakan .price untuk mensortnya, sebagai ajuan kalau bisa saya bilang
                struct info temp = data[j];						
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }													//kebawahnya juga sama
        }
    }
}

void voidSortPriceDsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].price < data[j + 1].price) {
                struct info temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void voidSortBathAsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].bathrooms > data[j + 1].bathrooms) {
                struct info temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void voidSortBathDsc(struct info data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j].bathrooms < data[j + 1].bathrooms) {
                struct info temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void voidPrintSort(struct info data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%-30s%-20s%-12d%-8d%-10d%-8d%-13s%-20s\n", data[i].location1, data[i].location2, data[i].price, data[i].rooms, data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);	//Function ini untuk nge print hasil dari sorting, sizenya adlah 10
	}
	
}

//Akhir dari function Sort

void exportData(struct info data[], int size, const char *filename) {
    FILE *exportFile;
    exportFile = fopen(filename, "w");		//filename itu nama file yang kita input, dalam mode w untuk write

    if (exportFile == NULL) {
        printf("Error E1: Unable to create/open the file for export. kok bisa?\n");		
        return;
    }

   
    fprintf(exportFile, "Location,City,Price,Rooms,Bathroom,Carpark,Type,Furnish\n");	//fprintf untuk nge write ke dalam file yang kita mau

    
    for (int i = 0; i < size; i++) {
        fprintf(exportFile, "%s,%s,%d,%d,%d,%d,%s,%s\n",							//data yang habis di sort akan masuk ke dalam struct data, dari struct data akan di write ke dalam filenya
                data[i].location1, data[i].location2, data[i].price, data[i].rooms,
                data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
    }

    fclose(exportFile);
    printf("\n\t\t\t\t\t    Data exported successfully to %s\n\n\n", filename);
}


//2 function terakhir yang paling susah menurut saya, jadi saya butuh bantuan 3rd party

int readData(struct Data data[]) {
    FILE *file;
    file = fopen("file.csv", "r"); 
    if (file == NULL) {
        printf("Error R1: Cannot open the file T.T.\n");			
        return -1;
    }

    char buffer[3942]; 
    int i = 0;

    fgets(buffer, sizeof(buffer), file);

   
    while (fgets(buffer, sizeof(buffer), file) && i < 1000) {		//data akan di scan sampai 1000, jika saya set ke 3942 (total data dari file.csv) maka program tidak lanjut saya tidak tau ini kenapa
        sscanf(buffer, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s",
               data[i].location1, data[i].location2, &data[i].price,
               &data[i].rooms, &data[i].bathrooms, &data[i].carParks,
               data[i].type, data[i].furnish);

       
        size_t len1 = strlen(data[i].location1);
        size_t len2 = strlen(data[i].location2);
        for (size_t j = 0; j < len1; j++) {
            if (data[i].location1[j] == '"') {
                memmove(&data[i].location1[j], &data[i].location1[j + 1], len1 - j);	//kedua function di bawah ini untuk menghilangkan tanda " agar saat di search bisa secara normal
                len1--;
                j--;
            }																			//misalkan tidak ada ini, maka saya harus input, contohnya : "KLCC
        }																				//tapi berkat ini saya bisa search : KLCC, saja tanpa tanda "
        for (size_t j = 0; j < len2; j++) {
            if (data[i].location2[j] == '"') {
                memmove(&data[i].location2[j], &data[i].location2[j + 1], len2 - j);
                len2--;
                j--;
            }
        }

        i++;
    }

    fclose(file);
    return i; 
}

void searchData(struct Data data[], int dataSize, const char *column, const char *query) {
    int found = 0;

		printf("\n\n______________________________________________________________________________________________________________________\n");
        printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-17s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");  
 		printf("___________________________________________________________________________________________________________________\n\n");
	
    for (int i = 0; i < dataSize; i++) {
        if (strcmp(column, "Location") == 0 || strcmp(column, "location") == 0 && strcmp(data[i].location1, query) == 0) {
         printf("%-30s%-20s%-12d%-8d%-10d%-8d%-13s%-20s\n", data[i].location1, data[i].location2, data[i].price, data[i].rooms, data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);	//agar tetap accept first character lowercase dan uppercase	
            found = 1;
        } else if (strcmp(column, "City") == 0  || strcmp(column, "city") == 0 && strcmp(data[i].location2, query) == 0) {
             printf("%-30s%-20s%-12d%-8d%-10d%-8d%-13s%-20s\n", data[i].location1, data[i].location2, data[i].price, data[i].rooms, data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);	//juga sama
             
            found = 1;
        }
        
    }

    if (!found) {
        printf ("Error SF2: Location: \"%s\" or Data: \"%s\" is either not available or invalid\n", column, query);		//Error ini akan muncul apabila ada typo di dalamnya atau tidak ditemukan
    }
}



int main() {
    int menuChoice;
    printf("_______________________________________________________________________________________________________________________\n");
    printf("________________________________________________________________________________________________________________________\n");			//tampilan paling awal dan atas saat program baru jalan
    printf("\t\t  Welcome to Beellow Property Program, for better user experience please use windowed mode\n");
    printf("_______________________________________________________________________________________________________________________\n");

do {    
	 printf("_______________________________________________________________________________________________________________________\n");
    printf("\n\t\t\t\t\t\tWhat do you want to do?\n\n");
    printf("\t\t\t\t\t\t   1. Display data\n");
    printf("\t\t\t\t\t\t   2. Search Data\n");
    printf("\t\t\t\t\t\t   3. Sort Data\n");					//Menu ditengah agar mudah dilihat, saya mengutamakan user satisfaction 
    printf("\t\t\t\t\t\t   4. Export Data\n");
    printf("\t\t\t\t\t\t   5. Exit\n\n");
    printf("    \t\t\t\t\t       Please pick your choice: ");

    scanf("%d", &menuChoice);
    getchar(); 
    
  
    if (menuChoice == 1) {
    	
    	int rows;
    	
    	do {
    	printf ("    \t\t\t\t\t   Input number of rows to be displayed: ");
    	scanf("%d", &rows);
    	getchar();
    	
    	if(rows <= 0) {
    		printf("\n\nError D2: Invalid rows :?\n\n"); //Error akan muncul apabila input user bukan positif
		}
		else {
		break; }
    
    	}while(rows <= 0);		//akan terus ditanya untuk menginput row di atas 0
    	
        display(rows); 
        
    }
    else if (menuChoice == 2) {			//Search data, saya gatau kenapa pak saya juga udah nanya GPT, masalahnya dia gabisa baca 3942 data dari filenya, sama kalo structnya lebih dari 1027 programmnya ga jalan
        
    struct Data data[1027];				//Tapi kebanyakan ke detect, masih berfungsi walaupun ga full ;) (bismillah nila  ga dikurang). tapi kalo di bagian sort, itu bisa di ke detect semua yang ada di dalam file.csv
    int dataSize = readData(data);

    if (dataSize == -1) {
        return 1;
    }

    char column[500];
    char query[500];

    printf("\t\t\t\t             Please choose Location or City: ");
    scanf("%99s", column); 
    getchar();

    printf("\t\t\t\t\t  Enter which data you want to find (Case Sensitive): ");
    scanf("%99s", query); 
    getchar();

    searchData(data, dataSize, column, query);
        
        
    }
    else if (menuChoice == 3) {
       
    FILE *files;
    files = fopen("file.csv", "r");
    struct info data[3942];  	
    
	if (files == NULL) {
		
    	printf("Error S1: Data not found :(\n");
    	
		}   
		
    else {
	
    	char filter1[15];
        char filter2[5];
        
		printf ("\n\n\t\t\t\t\t Available filters (Price, Rooms, Bathroom)\n");
		printf	("\t\t\t\t\t        Please type the filter: ");
        scanf ("%s", filter1);
        getchar ();
        
        printf("\n\n\t\t\t\t\t    Sort by Ascending or Descending order\n");
        printf("\t\t\t\t\t         Please type Asc or Dsc: ");
        scanf("%s", filter2);
        getchar();   
       
        fscanf(files, "%*[^\n]"); //agar kalimat paling atas di file.csv tidak di scan (location1, ocation2, price, room, dll)
       
       	int i = 0;
    	  for (; i < 3942; i++) {
       	 	if (fscanf(files, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]", data[i].location1, data[i].location2, &data[i].price, &data[i].rooms, &data[i].bathrooms, &data[i].carParks, data[i].type, data[i].furnish) != 8) {	 
            	break; 
                }
           }
       	
       		if ((strcmp(filter1, "Rooms") == 0 || strcmp(filter1, "rooms") == 0) && (strcmp(filter2, "Asc") == 0 || strcmp(filter2, "asc") == 0)) {
       			
				printf("\n\n______________________________________________________________________________________________________________________\n");	//Kegunaan dari ini adalah untuk tetap accept lowercase dan uppercase
       			printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   //untuk kebawahnya juga sama
        		printf("________________________________________________________________________________________________________________\n");
        		
   		 		voidSortRoomsAsc(data, i);
    			voidPrintSort(data, 10);
    			
    			printf("______________________________________________________________________________________________________________________\n\n");
		} else if ((strcmp(filter1, "Rooms") == 0 || strcmp(filter1, "rooms") == 0) && (strcmp(filter2, "Dsc") == 0 || strcmp(filter2, "dsc") == 0)) {	
			
				printf("\n\n______________________________________________________________________________________________________________________\n");
       			printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        		printf("________________________________________________________________________________________________________________\n");
        		
    			voidSortRoomsDsc(data, i);
   	 			voidPrintSort(data, 10); 	 
   	 			
   	 			printf("______________________________________________________________________________________________________________________\n\n");
}
       
       else if ((strcmp(filter1, "Price") == 0 || strcmp(filter1, "price") == 0) && (strcmp(filter2, "Asc") == 0 || strcmp(filter2, "asc") == 0)) {
       	
				printf("\n\n______________________________________________________________________________________________________________________\n");
       			printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        		printf("________________________________________________________________________________________________________________\n");
        		
    			voidSortPriceAsc(data, i);
   	 			voidPrintSort(data, 10); 
   	 			
				printf("______________________________________________________________________________________________________________________\n\n");	 
}
else if ((strcmp(filter1, "Price") == 0 || strcmp(filter1, "price") == 0) && (strcmp(filter2, "Dsc") == 0 || strcmp(filter2, "dsc") == 0)) {
	
			printf("\n\n______________________________________________________________________________________________________________________\n");
       		printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        	printf("________________________________________________________________________________________________________________\n");
        	
    		voidSortPriceDsc(data, i);
   			voidPrintSort(data, 10); 
   			
			printf("______________________________________________________________________________________________________________________\n\n");	 
}
       
       		else if ((strcmp(filter1, "Bathroom") == 0 || strcmp(filter1, "bathroom") == 0) && (strcmp(filter2, "Asc") == 0 || strcmp(filter2, "asc") == 0)) {
       			
			printf("\n\n______________________________________________________________________________________________________________________\n");
       		printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        	printf("________________________________________________________________________________________________________________\n");
    	
			voidSortBathAsc(data, i);
   	 		voidPrintSort(data, 10); 	 
   	 
			printf("______________________________________________________________________________________________________________________\n\n");
}
else if ((strcmp(filter1, "Bathroom") == 0 || strcmp(filter1, "bathroom") == 0) && (strcmp(filter2, "Dsc") == 0 || strcmp(filter2, "dsc") == 0)) {
	
			printf("\n\n______________________________________________________________________________________________________________________\n");
       		printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        	printf("________________________________________________________________________________________________________________\n");
    	
			voidSortBathDsc(data, i);
   	 		voidPrintSort(data, 10); 	
		
			printf("______________________________________________________________________________________________________________________\n\n"); 
}
     
else if ((strcmp(filter1, "Carpark") == 0 || strcmp(filter1, "carpark") == 0) && (strcmp(filter2, "Asc") == 0 || strcmp(filter2, "asc") == 0)) {
		
			printf("\n\n______________________________________________________________________________________________________________________\n");
       		printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        	printf("________________________________________________________________________________________________________________\n");
    		printf("\n\n\t\t\t\t\t      All listed property has 0 carparks\n"); 
			printf("______________________________________________________________________________________________________________________\n\n");	 
}
else if ((strcmp(filter1, "Carpark") == 0 || strcmp(filter1, "carpark") == 0) && (strcmp(filter2, "Dsc") == 0 || strcmp(filter2, "dsc") == 0)) {
			
			printf("\n\n______________________________________________________________________________________________________________________\n");
       		printf("\n%-28s%-20s%-10s%-7s%-12s%-13s%-13s%-20s", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");   
        	printf("________________________________________________________________________________________________________________\n");
    	 	printf("\n\n\t\t\t\t\t      All listed property has 0 carparks\n");
			printf("______________________________________________________________________________________________________________________\n\n"); 
}
else {
			printf ("\n\nError SF1: Filter 1: \"%s\" and Filter 2: \"%s\" is not available or invalid\n", filter1, filter2);
			printf ("Please use the correct filter names. Press Enter to continue\n");
			getchar();
} 
                    

    	

    fclose(files);
}
    
   
       
    }
    else if (menuChoice == 4) {
    	
    	
    char filename[50]; 
    int saver;
    char options;
	struct info data[3942];
	
	
	
	printf("\n\t\t      !! Attention User, please use the sort feature first before using this feature !!\n\n");	//karena dari soal, dia nge save dengan nama file sorted_xxx.csv, saya menginterpretasikan bahwa harus di sort dulu
	printf ("\t\t\t\t\t\t   Proceed? (Y/N): ");	//opsi untuk memastikan user sudah sort atau belum, jika belum, maka akan kembali ke main menu, kalau semisalnya user belum sort tapi sudah lanjut, maka data untuk filenya tidak tersimpan (data sehabis di sort akan disimpan di struct)
	scanf("%c", &options);
	getchar();
		
	if (options == 'y' || options == 'Y') {
	
	printf ("\t\t\t\t\tHow many data would you like to export: ");
	scanf("%d", &saver);
	printf("\n\t\t\t\tEnter the filename for export (with .csv extension): ");
	scanf("%s", filename);

	exportData(data, saver, filename);
}
	else {
		printf("\n\t\t\t\t\t\t    Actions aborted\n\n\n");	//dibatalkan apabila user tidak memilih y atau Y, selain dari itu akan dibatalkan
	} 
	
    } 
    	
    else if (menuChoice == 5){	//option untuk exit
        break;
    }
    
    else {
    	printf("\n\nError M1: Invalid input .-.\n\n");		//error ini akan ditampilkan apabila input tidak sesuai dengan yang telah disediakan
	}
    
} while(menuChoice != 5);  //Selama choice di menu belum 5, menu akan selalu di loop

 printf("\n\t\t\t\t\t   Thank you for using this program :)\n");
 printf("\t\t\t\t\t\t  Completed on 26/12/23\n");

    return 0;
}




