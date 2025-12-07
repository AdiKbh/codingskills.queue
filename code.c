#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Queue Structure for Cart
struct Cart {
    char foodName[100];
    char hotelName[50];
    int quantity;
    float price; // Total price for this line item (unit price * quantity)
} cart[MAX];
int front = -1, rear = -1;
float totalBill = 0;

// Hotel pricing structure
struct FoodAvailability {
    char hotelName[50];
    float price; // Unit price
};

// Function Prototypes (Added main and new option)
void addToCart(char food[], char hotel[], int qty, float price);
void removeFromCart();
void viewCart();
void orderNow();
void chooseHotel(char foodName[], struct FoodAvailability hotels[], int count);
void foodMenu();

// --- QUEUE OPERATIONS ---

// Function to add item to cart (enqueue)
void addToCart(char food[], char hotel[], int qty, float price) {
    if (rear == MAX - 1) {
        printf("Cart is Full! Cannot add more items.\n");
        return;
    }
    if (front == -1) front = 0;

    rear++;
    strcpy(cart[rear].foodName, food);
    strcpy(cart[rear].hotelName, hotel);
    cart[rear].quantity = qty;
    cart[rear].price = price * qty;
    totalBill += price * qty;

    printf("\n%s from %s (Qty: %d) added to cart!\n\n", food, hotel, qty);
}

// Function to remove item from cart (dequeue) - FIRST IN, FIRST OUT
void removeFromCart() {
    if (front == -1) {
        printf("\nCart is empty! Nothing to remove.\n");
        return;
    }

    // Display the item being removed
    printf("\nRemoving: %s from %s (Qty: %d) - Rs %.2f\n",
           cart[front].foodName, cart[front].hotelName, cart[front].quantity, cart[front].price);

    // Update the total bill
    totalBill -= cart[front].price;

    if (front == rear) {
        // Queue becomes empty
        front = rear = -1;
    } else {
        // Move front to the next element
        front++;
    }
    printf("Item removed from cart! Total Bill is now Rs %.2f\n\n", totalBill);
}

// View Cart
void viewCart() {
    if (front == -1) {
        printf("\nCart is empty!\n");
        return;
    }

    printf("\n------ CART ITEMS (Order: First to Last) ------\n");
    for (int i = front; i <= rear; i++) {
        printf("%d. %s (%s) x %d = Rs %.2f\n",
               (i - front) + 1, // Display item number relative to the front
               cart[i].foodName,
               cart[i].hotelName,
               cart[i].quantity,
               cart[i].price);
    }
    printf("------------------------\n");
    printf("Total Bill: Rs %.2f\n\n", totalBill);
}

// Order Now (Clear queue)
void orderNow() {
    if (front == -1) {
        printf("\nCart is empty! Cannot place an empty order.\n");
        return;
    }

    viewCart();
    printf("Order placed successfully! 🎉\n");
    printf("Thank you for ordering ❤\n");

    // Reset queue pointers and bill
    front = rear = -1;
    totalBill = 0;
}

// --- MENU LOGIC ---

// Select Hotel for selected food
void chooseHotel(char foodName[], struct FoodAvailability hotels[], int count) {
    int choice, qty;

    printf("\nAvailable in:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - Rs %.2f\n", i + 1, hotels[i].hotelName, hotels[i].price);
    }
    printf("%d. Back\n", count + 1);
    printf("Select Hotel: ");

    // Input validation for hotel choice
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Returning to menu.\n");
        while (getchar() != '\n');
        return;
    }

    if (choice < 1 || choice > count) return; // Returns if outside valid range

    printf("Enter quantity: ");
    
    // Input validation for quantity
    if (scanf("%d", &qty) != 1 || qty <= 0) {
        printf("Invalid quantity. Returning to menu.\n");
        while (getchar() != '\n');
        return;
    }

    addToCart(foodName, hotels[choice - 1].hotelName, qty, hotels[choice - 1].price);
}

// Display food menu for ordering
void foodMenu() {
    struct FoodAvailability hotels[5];
    int choice;

    while (1) {
        printf("\n--- FOOD MENU ---\n");

        printf("\n ---APPETIZERS---- \n");
        printf("1. Samosa (2 pcs) - Rs 50\n");
        printf("2. Spring Rolls - Rs 80\n");
        printf("3. French Fries - Rs 70\n");
        printf("4. Paneer Tikka - Rs 120\n");
        printf("5. Chicken Seekh Kebab - Rs 150\n");

        printf("\n ---MAIN COURSE---- \n");
        printf("6. Chicken Biryani - Rs 200\n");
        printf("7. Mutton Biryani - Rs 250\n");
        printf("8. Veg Biryani - Rs 150\n");
        printf("9. Chicken Curry - Rs 180\n");
        printf("10. Paneer Butter Masala - Rs 160\n");

        printf("\n ---BREADS/SIDES--- \n");
        printf("11. Tandoori Roti - Rs 20\n");
        printf("12. Butter Naan - Rs 40\n");
        printf("13. Garlic Naan - Rs 50\n");
        printf("14. Steamed Rice - Rs 80\n");
        printf("15. Dal Makhani - Rs 130\n");

        printf("\n ---BEVERAGES--- \n");
        printf("16. Bottled Water - Rs 20\n");
        printf("17. Cold Drink (Can) - Rs 50\n");
        printf("18. Fresh Lime Soda - Rs 60\n");
        printf("19. Masala Chai - Rs 40\n");
        printf("20. Lassi - Rs 70\n");
        printf("21. Back to Main Menu\n");

        printf("\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 21) break;

        if (choice < 1 || choice > 20) {
            printf("Invalid choice!\n");
            continue;
        }

        switch (choice) {
            case 1:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 50;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 45;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 48;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 52;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 47;
                chooseHotel("Samosa (2 pcs)", hotels, 5);
                break;
            case 2:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 80;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 75;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 78;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 82;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 77;
                chooseHotel("Spring Rolls", hotels, 5);
                break;
            case 3:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 70;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 65;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 68;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 72;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 67;
                chooseHotel("French Fries", hotels, 5);
                break;
            case 4:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 120;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 110;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 118;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 122;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 117;
                chooseHotel("Paneer Tikka", hotels, 5);
                break;
            case 5:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 150;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 140;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 148;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 152;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 147;
                chooseHotel("Chicken Seekh Kebab", hotels, 5);
                break;
            case 6:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 200;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 190;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 198;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 202;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 197;
                chooseHotel("Chicken Biryani", hotels, 5);
                break;
            case 7:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 250;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 240;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 248;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 252;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 247;
                chooseHotel("Mutton Biryani", hotels, 5);
                break;
            case 8:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 150;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 140;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 148;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 152;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 147;
                chooseHotel("Veg Biryani", hotels, 5);
                break;
            case 9:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 180;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 170;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 178;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 182;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 177;
                chooseHotel("Chicken Curry", hotels, 5);
                break;
            case 10:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 160;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 150;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 158;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 162;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 157;
                chooseHotel("Paneer Butter Masala", hotels, 5);
                break;
            case 11:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 20;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 18;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 19;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 21;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 20;
                chooseHotel("Tandoori Roti", hotels, 5);
                break;
            case 12:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 40;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 38;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 39;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 41;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 40;
                chooseHotel("Butter Naan", hotels, 5);
                break;
            case 13:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 50;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 48;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 49;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 51;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 50;
                chooseHotel("Garlic Naan", hotels, 5);
                break;
            case 14:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 80;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 75;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 78;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 82;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 77;
                chooseHotel("Steamed Rice", hotels, 5);
                break;
            case 15:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 130;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 125;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 128;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 132;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 127;
                chooseHotel("Dal Makhani", hotels, 5);
                break;
            case 16:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 20;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 18;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 19;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 21;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 20;
                chooseHotel("Bottled Water", hotels, 5);
                break;
            case 17:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 50;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 48;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 49;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 51;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 50;
                chooseHotel("Cold Drink (Can)", hotels, 5);
                break;
            case 18:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 60;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 55;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 58;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 62;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 57;
                chooseHotel("Fresh Lime Soda", hotels, 5);
                break;
            case 19:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 40;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 38;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 39;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 41;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 40;
                chooseHotel("Masala Chai", hotels, 5);
                break;
            case 20:
                strcpy(hotels[0].hotelName, "Meghana Foods"); hotels[0].price = 70;
                strcpy(hotels[1].hotelName, "Hotel Taj"); hotels[1].price = 65;
                strcpy(hotels[2].hotelName, "Pump House"); hotels[2].price = 68;
                strcpy(hotels[3].hotelName, "Empire"); hotels[3].price = 72;
                strcpy(hotels[4].hotelName, "Royal Palace"); hotels[4].price = 67;
                chooseHotel("Lassi", hotels, 5);
                break; // <-- BREAK added here

            default:
                printf("Invalid choice!\n");
        }
    }
}

// --- MAIN EXECUTION ---
int main() {
    int choice;

    while (1) {
        printf("\n====== FOOD ORDERING SYSTEM ======\n");

        printf("1. Search/Add Food (Menu)\n");
        printf("2. View Cart\n");
        printf("3. Order Now and Generate Bill\n");
        printf("4. Remove oldest item from Cart (Dequeue)\n"); // New option for demonstrating FIFO
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input, try again!\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: foodMenu(); break;
            case 2: viewCart(); break;
            case 3: orderNow(); break;
            case 4: removeFromCart(); break; // New Case
            case 5:
                printf("Thank you for using the Food Ordering System! Visit Again 😊\n");
                exit(0);
            default:
                printf("Invalid choice, please select 1-5.\n");
        }
    }
    return 0;
}