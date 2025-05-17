#include <iostream>
#include <fstream>
#include <cstring>

   using namespace std;

 const int MAX_PRODUCTS = 100;
const int NAME_LEN = 50;

     char productNames[MAX_PRODUCTS][NAME_LEN];
  int productIDs[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
float prices[MAX_PRODUCTS];
   int productCount = 0;

     void loadInventory();
      void saveInventory();
   void addProduct();
void sellProduct();
void restockProduct();
       void viewInventory();
void searchProduct();
int findProductByID(int id);
    bool idExists(int id);
void clearInputBuffer();

int main() {
	 cout << "Name: Jawad Ahmad" << endl;
    cout << "Reg No: 240810" << endl;
    loadInventory();

    int choice;

    do {
cout << "\n=== Hardware Store Inventory Management ===\n";
cout << "1. Add New Product\n";
cout << "2. Sell Product\n";
cout << "3. Restock Product\n";
cout << "4. View Inventory\n";
    cout << "5. Search Product\n";
    cout << "6. Save and Exit\n";
    cout << "Enter your choice: ";
       cin >> choice;
    clearInputBuffer();

switch(choice) 
{
case 1: 
addProduct(); 
break;
case 2: 
sellProduct();
 break;
case 3: 
restockProduct();
 break;
case 4: 
viewInventory(); 
break;
case 5:
 searchProduct(); 
break;
case 6: 
saveInventory();
cout << "Inventory saved. Exiting program.\n";
break;
default: cout << "Invalid choice. Please try again.\n";
        }
    } 
while(choice != 6);

 return 0;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void loadInventory() 
{
ifstream fin("inventory.txt");
if (!fin) 
       {
cout << "No inventory file found. Starting with empty inventory.\n";
return;
    }
productCount = 0;
    while (productCount < MAX_PRODUCTS && !fin.eof()) {
int id, qty;
   float price;
 char name[NAME_LEN];

fin >> id >> name >> qty >> price;
if (fin.fail()) break;

productIDs[productCount] = id;
strncpy(productNames[productCount], name, NAME_LEN);
productNames[productCount][NAME_LEN - 1] = '\0';
quantities[productCount] = qty;
prices[productCount] = price;

productCount++;
}
fin.close();

cout << productCount << " products loaded from inventory.txt\n";
} 

void saveInventory() {
 ofstream fout("inventory.txt");
 for (int i = 0; i < productCount; i++) {
fout << productIDs[i] << " " << productNames[i] << " " << quantities[i] << " " << prices[i] << "\n";
}
fout.close();
}
bool idExists(int id) {
for (int i = 0; i < productCount; i++) {
if (productIDs[i] == id)
return true;
    }
return false;
}

int findProductByID(int id) {
for (int i = 0; i < productCount; i++) {
        if (productIDs[i] == id)
            return i;
    }
    return -1;
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Inventory full, cannot add more products.\n";
        return;
    }

    int id;
    char name[NAME_LEN];
    int qty;
    float price;
		cout << "Enter Product ID (unique number): ";
    cin >> id;
    clearInputBuffer();

    if (id < 0) {
        cout << "Product ID cannot be negative.\n";
        return;
    }

    if (idExists(id)) 
	{
cout << "Product ID already exists. Please use a unique ID.\n";
    return;
}
   cout << "Enter Product Name (no spaces): ";
cin >> name;
clearInputBuffer();

    cout << "Enter Quantity in stock: ";
    cin >> qty;
    clearInputBuffer();

    if (qty < 0) {
cout << "Quantity cannot be negative.\n";
       
	 return;
    }

    cout << "Enter Price per unit: ";
   
 cin >> price;
    clearInputBuffer();
    if (price < 0) {
        cout << "Price cannot be negative.\n";
return;
    }

    productIDs[productCount] = id;
    strncpy(productNames[productCount], name, NAME_LEN);
    productNames[productCount][NAME_LEN - 1] = '\0';
    quantities[productCount] = qty;
    prices[productCount] = price;

    productCount++;

    cout << "Product added successfully.\n";
}

void sellProduct() {
 if (productCount == 0) {
        cout << "Inventory is empty.\n";
  return;
    }

    int id, qty;
    cout << "Enter Product ID to sell: ";
	cin >> id;
    clearInputBuffer();

    int idx = findProductByID(id);
    if (idx == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter quantity to sell: ";
    cin >> qty;
    clearInputBuffer();

    if (qty <= 0) {
        cout << "Quantity must be positive.\n";
        return;
    }

    if (quantities[idx] < qty) {
        cout << "Not enough stock. Available quantity: " << quantities[idx] << "\n";
        return;
    }

    quantities[idx] -= qty;
cout << "Sale successful. Remaining stock: " << quantities[idx] << "\n";
}

void restockProduct() {
if (productCount == 0) {
cout << "Inventory is empty.\n";
        return;
    }

    int id, qty;
   cout << "Enter Product ID to restock: ";
cin >> id;
   clearInputBuffer();

    int idx = findProductByID(id);
    if (idx == -1) {
cout << "Product not found.\n";
        return;
    }

cout << "Enter quantity to add: ";
    cin >> qty;
clearInputBuffer();

    if (qty <= 0) {
        cout << "Quantity must be positive.\n";
return;
    }

    quantities[idx] += qty;
    cout << "Restock successful. New stock: " << quantities[idx] << "\n";
}

void viewInventory() {
    if (productCount == 0) {
        cout << "Inventory is empty.\n";
        return;
    }

cout << "ID\tName\tQuantity\tPrice\n";
    cout << "---------------------------------\n";

    for (int i = 0; i < productCount; i++) {
cout << productIDs[i] << "\t" << productNames[i] << "\t" << quantities[i] << "\t\t" << prices[i] << "\n";
    }
}

void searchProduct() {
    if (productCount == 0) {
    cout << "Inventory is empty.\n";
return;
    }

    cout << "Search by:\n1. Product ID\n2. Product Name\nEnter choice: ";
int choice;
    cin >> choice;
clearInputBuffer();

    if (choice == 1) {
        int id;
cout << "Enter Product ID: ";
cin >> id;
        clearInputBuffer();

        int idx = findProductByID(id);
        if (idx == -1) {
            cout << "Product Not Found.\n";
    return;
        }

cout << "Product Details:\n";
        cout << "ID: " << productIDs[idx] << "\n";
cout << "Name: " << productNames[idx] << "\n";
        cout << "Quantity: " << quantities[idx] << "\n";
        cout << "Price: " << prices[idx] << "\n";




    } else if (choice == 2) {
char name[NAME_LEN];
        cout << "Enter Product Name (no spaces): ";
cin >> name;
        clearInputBuffer();
bool found = false;
        for (int i = 0; i < productCount; i++) {
            if (strcmp(productNames[i], name) == 0) {
    cout << "Product Details:\n";
             cout << "ID: " << productIDs[i] << "\n";
  cout << "Name: " << productNames[i] << "\n";
           cout << "Quantity: " << quantities[i] << "\n";
    cout << "Price: " << prices[i] << "\n";
           found = true;
         break;
            }
        }
  if (!found) {
cout << "Product Not Found.\n";
        }
    } 
	else {
cout << "Invalid choice.\n";
    }
}


