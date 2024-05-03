#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Counter should have

---------------- Using Queue Linked List
-Add Order = add tail v 
-View Order = display all v 
- Delete Order = delete beginning v 
- Find Order Numbers Position  
-----------------
-Build menu 

*/

typedef struct node {

int data;
struct node* next;

}node;

node* create(int value){

    node* head = malloc(sizeof(node));
    head->data = value;
    head->next = NULL;

    return head;
}

node* addOrder(node* head, int value) {
    if(head == NULL){
        head = create(value);
        return head;
    }

    node* ptr = head;

    while(ptr->next != NULL){
        ptr = ptr->next;
    }

    node* temp = create(value);
    ptr->next = temp;

    return head;

}

node* deleteOrder(node* head) {

    if(head == NULL){
        printf("No Orders\n");
        return head;
    }

    node* ptr = head;
    head = head->next;
    free(ptr);

    return head;
}

void displayOrder(node* head) {

        node* ptr = head;

        while(ptr != NULL) {
            printf("Order %d -> ", ptr->data);
            ptr = ptr->next;
        }

        printf("No Orders Left\n");

}

node* findOrder(node* head, int findS) {
    node* ptr = head;
    int counter = 0;


    while(ptr != NULL) {
        if(ptr->data == findS) {
            printf("Order is number %d\n", counter+1);
            return head;
        }
        ptr = ptr->next;
        counter++;
    }
    printf("Order not found\n");
    return NULL;
}



node* head = NULL;

int main () {

  int choice = 0;
  int counter = 0;
  float totalRevenue;

do {
 
 printf("\n\nFast Food Counter\n");
 printf("1. New Order\n");
 printf("2. Finish Order\n");
 printf("3. Display All Orders\n");
 printf("4. Find Order\n");
 printf("\n5. View Menu\n");
 printf("6. Todays Revenue\n");
 printf("7. Exit\n");

printf("\nEnter your choice: ");
scanf("%d", &choice);
getchar();

if(choice == 1) {
    counter++;

    printf("\nMenu : \n");
    printf("1. Burger - $3.50\n");                  //Swich Case > if else
    printf("2. Fries - $2.00\n");
    printf("3. Soda - $1.50\n");
    printf("4. Ice Cream - $2.50\n");
    printf("5. Chicken - $4.00\n");
    printf("\n6. Done\n\n");
  
    
    float total = 0;
    int order = 0;
    int payments;
   

    while(order != 6) {
        printf("Enter your order: ");
        scanf("%d", &order);
        getchar();

        if(order == 1) {
            total = total + 3.50;
        } else if(order == 2) {
            total = total + 2.00;
        } else if(order == 3) {
            total = total + 1.50;
        } else if(order == 4) {
            total = total + 2.50;
        } else if(order == 5) {
            total = total + 4.00;
        } else if(order == 6) {
            printf("Total: $%.2f\n", total);
            
            payments = 0;
           
            printf("Enter the payment amount: ");
            scanf("%d", &payments);
            getchar();

            int change = 0;
            change = total - payments;
            
            if(change == 0) {
                printf("No Change\n");
                totalRevenue += total;
            }
            else {
                printf("Change: $%.2f\n", total - payments);
                totalRevenue += total;
            }

            head = addOrder(head, counter);
            
        } 
        
    }
}

else if (choice == 2) {
    head = deleteOrder(head);
    printf("Order Finished\n\n");
}
else if (choice == 3) {
    displayOrder(head);
}
else if(choice == 4) {
    printf("Find Order: ");
    int findS = 0;
    scanf("%d", &findS);

    head = findOrder(head, findS);
}

else if (choice == 5) {
    printf("\nMenu : \n");
    printf("1. Burger - $3.50\n");
    printf("2. Fries - $2.00\n");
    printf("3. Soda - $1.50\n");
    printf("4. Ice Cream - $2.50\n");
    printf("5. Chicken - $4.00\n");
    printf("\n6. Done\n\n");
}

else if (choice == 6) {
    long long int employeeIdMaster = 2702366634;
    long long int employeeIdUse = 0;
    char passwordUse[20];
    char passwordMaster[20] = "helloworld";

    printf("\nEnter Employee Id and Password\n");
    
    printf("Employee Id: ");
    scanf("%lld", &employeeIdUse);
    getchar ();

    printf("Password: ");
    scanf("%s", passwordUse);
    getchar ();

    if(employeeIdUse == employeeIdMaster && strcmp(passwordUse, passwordMaster) == 0) {
        if (totalRevenue < 1.0) {
            printf("No Revenue Today\n");
        }
        else {
            printf("\nTodays Revenue is: $%.2lf\n", totalRevenue);
        }
        
    }
    else {
        printf("\n! No Permission to View, Contact Manager !\n");
    }
   
}

else if (choice == 000) {
    printf("Confirm Panic Mode: ");
    char panicChoice;
    scanf("%c", &panicChoice);

    if(panicChoice == 'y' || panicChoice == 'Y') {

    while(1) {
        printf("Panic Mode Enabled\n");
        printf("\n\nAll System Locked!\n");
    }
    }

    else break;
}

} while(choice != 7); 

printf("Operation Ended");

    return 0;
}







//Fay  24/03/24