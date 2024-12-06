#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 100
#define MAX_STACK 100
typedef struct {
 int id;
 char name[50];
 float price;
 int quantity;
} Product;
typedef struct {
 Product products[MAX_PRODUCTS];
 int count;
} ProductArray;
typedef struct {
 Product product;
} StackItem;
typedef struct {
 StackItem items[MAX_STACK];
 int top;
} Stack;
typedef struct {
 Product products[MAX_CUSTOMERS];
 int front, rear, count;
} Queue; //done//

ProductArray productArray;
Stack undoStack;
Queue billingQueue;
void initialize() {
 productArray.count = 0;
 undoStack.top = -1;
 billingQueue.front = 0;
 billingQueue.rear = 0;
 billingQueue.count = 0;
} //done//

void push(StackItem item) {
 if (undoStack.top < MAX_STACK - 1) {
 undoStack.items[++undoStack.top] = item;
 } else {
 printf("Undo stack overflow!\n");
 }
}
StackItem pop() {
 if (undoStack.top >= 0) {
 return undoStack.items[undoStack.top--];
 } else {
 printf("Undo stack underflow!\n");
 StackItem empty = {0};
 return empty;
 }
}//done//

int isEmpty(Stack *stack) {
 return stack->top == -1;
}
void enqueue(Product product) {
 if (billingQueue.count < MAX_CUSTOMERS) {
 billingQueue.products[billingQueue.rear] = product;
 billingQueue.rear = (billingQueue.rear + 1) % MAX_CUSTOMERS;
 billingQueue.count++;
 } else {
 printf("Billing queue is full!\n");
 }
}
Product dequeue() {
 if (billingQueue.count > 0) {
 Product product = billingQueue.products[billingQueue.front];
 billingQueue.front = (billingQueue.front + 1) % MAX_CUSTOMERS;
 billingQueue.count--;
 return product;
 } else {
 printf("Billing queue is empty!\n");
 Product empty = {0};
 return empty;
 }
}

void addProduct() {
    if (productArray.count < MAX_PRODUCTS) {
        Product *p = &productArray.products[productArray.count++];
        printf("Enter Product ID: ");
        while (scanf("%d", &p->id) != 1) {
            printf("Invalid input. Enter a valid Product ID: ");
            while (getchar() != '\n');
        }

        printf("Enter Product Name: ");
        scanf("%49s", p->name);

        printf("Enter Product Price: ");
        while (scanf("%f", &p->price) != 1 || p->price <= 0) {
            printf("Invalid input. Enter a valid Product Price: ");
            while (getchar() != '\n');
        }

        printf("Enter Product Quantity: ");
        while (scanf("%d", &p->quantity) != 1 || p->quantity < 0) {
            printf("Invalid input. Enter a valid Product Quantity: ");
            while (getchar() != '\n');
        }

        printf("Product added successfully!\n");
    } else {
        printf("Product list is full!\n");
    }
}
void removeProduct() {
 int id, found = 0;
 printf("Enter Product ID to remove: ");
 scanf("%d", &id);
 for (int i = 0; i < productArray.count; i++) {
 if (productArray.products[i].id == id) {
 found = 1;

 StackItem item;
 item.product = productArray.products[i];
 push(item);

 for (int j = i; j < productArray.count - 1; j++) {
 productArray.products[j] = productArray.products[j + 1];
 }
 productArray.count--;
 printf("Product removed successfully!\n");
 break;
 }
 }
 if (!found) {
 printf("Product not found!\n");
 }
}
void updateProduct() {
 int id, found = 0;
 printf("Enter Product ID to update: ");
 scanf("%d", &id);
 for (int i = 0; i < productArray.count; i++) {
 if (productArray.products[i].id == id) {
 found = 1;
 printf("Updating Product ID: %d\n", productArray.products[i].id);
 printf("Enter new Product Name: ");
 scanf("%s", productArray.products[i].name);
 printf("Enter new Product Price: ");
 scanf("%f", &productArray.products[i].price);
 printf("Enter new Product Quantity: ");
 scanf("%d", &productArray.products[i].quantity);
 printf("Product updated successfully!\n");
break;
 }
 }
 if (!found) {
 printf("Product not found!\n");
 }
}
void displayProducts() {
 if (productArray.count == 0) {
 printf("No products available.\n");
 return;
 }
 printf("Product List:\n");
 for (int i = 0; i < productArray.count; i++) {
 printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
 productArray.products[i].id,
 productArray.products[i].name,
 productArray.products[i].price,
 productArray.products[i].quantity);
 }
}
void searchProduct() {
 int id, found = 0;
 printf("Enter Product ID to search: ");
 scanf("%d", &id);
 for (int i = 0; i < productArray.count; i++) {
 if (productArray.products[i].id == id) {
 found = 1;
 printf("Product found: ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
 productArray.products[i].id,
 productArray.products[i].name,
 productArray.products[i].price,
 productArray.products[i].quantity);
 break;
 }
 }
 if (!found) {
 printf("Product not found!\n");
 }
}
void generateBill() {
    if (billingQueue.count == 0) {
        printf("Billing queue is empty.\n");
    } else {
        float total = 0;
        printf("Billing Details:\n");
        while (billingQueue.count > 0) {

            Product p = billingQueue.products[billingQueue.front];
            billingQueue.front = (billingQueue.front + 1) % MAX_CUSTOMERS;
            billingQueue.count--;
            float productTotal = p.price * p.quantity;
            printf("Product ID: %d, Name: %s, Price: %.2f, Quantity: %d, Total: %.2f\n",
                   p.id, p.name, p.price, p.quantity, productTotal);
            total += productTotal;
        }
        printf("Total Bill: %.2f\n", total);
        clearQueue();
    }
}

void undo() {
 if (!isEmpty(&undoStack)) {
 StackItem item = pop();
 productArray.products[productArray.count++] = item.product;
 printf("Undo successful: Product ID %d added back.\n", item.product.id);
 } else {
 printf("Nothing to undo!\n");
 }
}
void clearQueue() {
 billingQueue.front = 0;
 billingQueue.rear = 0;
 billingQueue.count = 0;
 printf("Billing queue cleared.\n");
}
void displayQueue() {
 if (billingQueue.count == 0) {
 printf("Billing queue is empty.\n");
 return;
 }
 printf("Current Billing Queue:\n");
 for (int i = 0; i < billingQueue.count; i++) {
 int index = (billingQueue.front + i) % MAX_CUSTOMERS;
 printf("Product ID: %d, Name: %s, Price: %.2f\n",
 billingQueue.products[index].id,
 billingQueue.products[index].name,
 billingQueue.products[index].price);
 }
}
void addToQueue() {
 int id, found = 0;
 printf("Enter Product ID to add to billing queue: ");
 scanf("%d", &id);
 for (int i = 0; i < productArray.count; i++) {
 if (productArray.products[i].id == id) {
 found = 1;
 enqueue(productArray.products[i]);
 printf("Product added to billing queue successfully!\n");
 break;
 }
 }
 if (!found) {
 printf("Product not found!\n");
 }
}
void menu() {
 int choice;
 do {
 printf("\nGrocery Management System\n");
 printf("1. Add Product\n");
 printf("2. Remove Product\n");
 printf("3. Update Product\n");
 printf("4. Display Products\n");
 printf("5. Search Product\n");
 printf("6. Generate Bill\n");
 printf("7. Undo\n");
 printf("8. Add to Billing Queue\n");
 printf("9. Display Billing Queue\n");
 printf("10. Clear Billing Queue\n");
 printf("11. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 switch (choice) {
 case 1: addProduct(); break;
 case 2: removeProduct(); break;
 case 3: updateProduct(); break;
 case 4: displayProducts(); break;
 case 5: searchProduct(); break;
 case 6: generateBill(); break;
 case 7: undo(); break;
 case 8: addToQueue(); break;
 case 9: displayQueue(); break;
 case 10: clearQueue(); break;
 case 11: printf("Exiting...\n"); break;
 default: printf("Invalid choice! Please try again.\n");
 }
 } while (choice != 11);
}
int main() {
 initialize();
 menu();
 return 0;
}
