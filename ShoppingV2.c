#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

FILE *fp, *fptr;
int totalBill = 0;


struct ProductsOfSameCategory{
    char productName[15];
    int price;
    //int quantity;
};

struct ProductCategories{
    char categoryName[15];
    struct ProductsOfSameCategory products[3];
}category[3];

struct customerBill{
    char customerName[15];
    char customerEmail[15];
}bill;

typedef struct SinglyLinkedList{
    int productPrice;
    char* product;
    struct SinglyLinkedList* next;   
}*Cart;


Cart getnode(){
    Cart new1= NULL;
    new1 = malloc(sizeof(struct SinglyLinkedList));
    if(new1 ==NULL){
        printf("\n Memory not availble");
        exit(0);
    }
    new1->next =NULL;
    return new1;
}


void getDetails(){
    system("cls");
    printf("Enter your name: ");
    scanf("%s", &bill.customerName);
    printf("Enter your email-id: ");
    scanf("\n\n\n%s", &bill.customerEmail);
    printf("Welcome %s", bill.customerName);
}


int welcome(){
    system("cls");
    printf("Welcome to Camera Store");
    printf("Select Mode: \n1.Admin\n2.Customer\nEnter (1/2):\t");
    int choice;
    scanf("%d", &choice);
    return choice;
}


void printStruct(){
    system("cls");
    for(int i=0;i<3;i++){
        printf("\n\nName of Category: ");
        printf("%s", category[i].categoryName);
        printf("\nProducts of this category: ");
        for(int j=0; j<3; j++){
            printf("\n\tName of Product: ");
            printf("\n%s", category[i].products[j].productName);
            printf("\n\tPrice of Product: ");
            printf("\n%d", category[i].products[j].price);
        }
    }
}


void printCategories(){
    for(int i=0;i<3;i++){
        printf("\n\nName of Category: ");
        printf("%d. %s", i+1, category[i].categoryName);
    }
    printf("\nWhich category would you like to shop?: ");
}


void printProducts(int i){
        printf("\n\nName of Category: ");
        printf("%s", category[i].categoryName);
        printf("\n Products of this category: ");
        for(int j=0; j<3; j++){
            printf("\n\t%d. Name of Product: ",j+1);
            printf("%s", category[i].products[j].productName);
            printf("\n\tPrice of Product: ");
            printf("%d", category[i].products[j].price);
        }
        printf("\nWhich Product would you like to buy?: ");

}


void printList(Cart temp){
    system("cls");
    printf("\nYour Cart: ");
    while(temp != NULL){
        printf("\nProduct: %s", temp->product);
        printf("\t\tPrice: %d", temp->productPrice);
        temp = temp->next;
    }
    printf("\n");
    printf("-----------------------------------------------");
    printf("\nCustomer Name:\t\t\t%s\nCustomer E-mail:\t\t\t%s\nYour Total Bill:\t\t\t%d", bill.customerName, bill.customerEmail ,totalBill);
    printf("\n\n\nThank You for Shopping. Visit Again.");
}


void customer(){
    Cart head=NULL, temp, new1;
    char res;
    system("cls");
    getDetails();

    do{   
        system("cls");
        printf("Welcome %s", bill.customerName);
        printf("\nWhat would you like to buy?");
        printCategories();
        int choice;
        scanf("%d", &choice);

        printProducts(choice-1);
        int prodChoice;
        scanf("%d", &prodChoice);


        if(head ==NULL){
            head =getnode();
            head->product = category[choice-1].products[prodChoice-1].productName;
            head->productPrice = category[choice-1].products[prodChoice-1].price;
            temp =head;
        }
        else{
            new1 = getnode();
            new1->product = category[choice-1].products[prodChoice-1].productName;
            new1->productPrice = category[choice-1].products[prodChoice-1].price;
            temp->next = new1;
            temp = new1;
        }
        totalBill += category[choice-1].products[prodChoice-1].price;

        printf("Want to buy another product? (y/n): ");
        scanf(" %c", &res);
    }while(res == 'y');
    printList(head);
}


void admin(){
    fp = fopen("shopping.txt","w");
    if(fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else{  
    for(int i=0;i<3;i++){
        printf("\nName of Category: ");
        scanf("%s", &category[i].categoryName);
        fprintf(fp, "%s\t", category[i].categoryName);
        printf("Enter the products of this category: \n");

        for(int j=0; j<3; j++){
            printf("Enter Name of Product: ");
            scanf("%s", &category[i].products[j].productName);
            fprintf(fp, "%s\t", category[i].products[j].productName);

            printf("Enter Price of Product: ");
            scanf("%d", &category[i].products[j].price);
            fprintf(fp, "%d\t", category[i].products[j].price);
        }
    }
    }
    fclose(fp);
    printf("\nProducts Added.\nPress 1 to continue as customer.\nPress 2 to exit.");
    int res;
    scanf("%d", &res);
    if(res == 1){
        customer();
    }
    else
        system("cls");
        printf("Thank You");

}


void readFile(){
       fp = fopen("shopping.txt","r");
            
        if(fp == NULL){
            printf("\n\t\tFile opening error");
            exit(0);
        }
        else{
            int i=0, j=0;
            while(fscanf(fp, "%d", &category[i].products[j].price)!=EOF){
                for( i=0;i<3;i++){
                fscanf(fp, "%s\t", &category[i].categoryName);
                    for( j=0; j<3; j++){
                        fscanf(fp, "%s\t", &category[i].products[j].productName);
                        fscanf(fp, "%d\t", &category[i].products[j].price);
                    }
                }
            }
        }
}

////////////////////////////MAIN////////////////////////////////

int main(){

    int choice = welcome();
    switch (choice){
        case 1:
            admin();
            break;
        case 2:
            readFile();
            customer();
         default:
            printf("Select valid choice");
            break;
    }

    //printStruct();
}