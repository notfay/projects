#include <stdio.h>
#include <stdlib.h>

/*Counter should have

---------------- Using Queue Linked List
-Add Order = add tail
-View Order = display all
- Delete Order = delete beginning
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
            printf("%d -> ", ptr->data);
            ptr = ptr->next;
        }

        printf("End of Order");

}



node* head = NULL;

int main () {

    head = addOrder(head, 1);
    head = addOrder(head, 2);
    head = addOrder(head, 3);

    displayOrder(head);

    return 0;
}