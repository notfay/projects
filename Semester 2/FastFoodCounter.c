#include <stdio.h>
#include <stdlib.h>

/*Counter should have

---------------- Using Queue Linked List
-Add Order = add tail
-View Order = display all
- Delete Order = delete beginning
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

        printf("End of Order");

}



node* head = NULL;

int main () {

  int choice;
  int counter = 0;

do {
 
 printf("\n\nFast Food Counter\n");
 printf("1. New Order\n");
 printf("2. Delete Order\n");
 printf("3. Display All Orders\n");
 printf("4. View Menu\n");
 printf("5. Exit\n");

printf("Enter your choice: ", &choice);
scanf("%d", &choice);
getchar();

if(choice == 1) {
    counter = counter + 1;

    printf("\nMenu : \n");
    printf("1. Burger - $3.50\n");
    printf("2. Fries - $2.00\n");
    printf("3. Soda - $1.50\n");
    printf("4. Ice Cream - $2.50\n");
    printf("5. Chicken - $4.00\n");
    printf("\n6. Done\n");
    printf("\n\nNote : Cash Payments is only available if below $20\n");
    
    float total = 0;
    int order = 0;
    while(order != 6) {
        printf("Enter your order: ", &order);
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
            if(total > 20) {
            printf("Enter Card Number\n");
            int card;
            scanf("%d", &card);
            getchar();
            printf("\nThank you for your payment\n");
            head = addOrder(head, counter);
            
        } else {
            head = addOrder(head, counter);
            
        }
        
    }
}
}

else if (choice == 3) {
    displayOrder(head);
}

} while(choice != 5); 

    return 0;
}