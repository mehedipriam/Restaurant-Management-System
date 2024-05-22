#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_EMPLOYEES 50
#define MAX_LINE_LENGTH 100

// Structure to hold restaurant item information
struct MenuItem
{
    char name[50];
    char category[50];
    float price;
};

// Structure to hold employee information
struct Employee
{
    char name[50];
    char position[50];
    float salary;
    char mobile[15];
    char address[100];
};

// Function prototypes
void loadMenuFromCSV(char *filename, struct MenuItem menu[], int *count);
void printMenu(struct MenuItem menu[], int count);
void addItem(struct MenuItem menu[], int *count);
void saveMenuToCSV(char *filename, struct MenuItem menu[], int count);
void addEmployee(struct Employee employees[], int *count);
void loadEmployeesFromCSV(char *filename, struct Employee employees[], int *count);
void saveEmployeesToCSV(char *filename, struct Employee employees[], int count);
void generateBill(struct MenuItem menu[], int count);

int main()
{
    struct MenuItem menu[MAX_ITEMS];
    int itemCount = 0;
    loadMenuFromCSV("menu.csv", menu, &itemCount);

    struct Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    loadEmployeesFromCSV("employees.csv", employees, &employeeCount);

    while (1)
    {
        printf("\nRestaurant Management System\n");
        printf("1. View Menu\n");
        printf("2. Add Item\n");
        printf("3. Add Employee\n");
        printf("4. Save Employees\n");
        printf("5. Generate Customer Bill\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printMenu(menu, itemCount);
            break;
        case 2:
            addItem(menu, &itemCount);
            break;
        case 3:
            addEmployee(employees, &employeeCount);
            break;
        case 4:
            saveEmployeesToCSV("employees.csv", employees, employeeCount);
            printf("Employees saved successfully.\n");
            break;
        case 5:
            generateBill(menu, itemCount);
            break;
        case 6:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void loadMenuFromCSV(char *filename, struct MenuItem menu[], int *count)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s not found, creating new file.\n", filename);
        file = fopen(filename, "w");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    *count = 0;
    while ((*count < MAX_ITEMS) && fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        strcpy(menu[*count].name, token);

        token = strtok(NULL, ",");
        strcpy(menu[*count].category, token);

        token = strtok(NULL, ",");
        menu[*count].price = atof(token);

        (*count)++;
    }

    fclose(file);
}

void printMenu(struct MenuItem menu[], int count)
{
    printf("\nMenu:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s - %s - %.2f\n", menu[i].name, menu[i].category, menu[i].price);
    }
}

void addItem(struct MenuItem menu[], int *count)
{
    printf("Enter name of the item: ");
    fgets(menu[*count].name, sizeof(menu[*count].name), stdin);
    strtok(menu[*count].name, "\n");

    printf("Enter category of the item: ");
    fgets(menu[*count].category, sizeof(menu[*count].category), stdin);
    strtok(menu[*count].category, "\n");

    printf("Enter price of the item: ");
    scanf("%f", &menu[*count].price);
    getchar();

    (*count)++;
    saveMenuToCSV("menu.csv", menu, *count);
    printf("Item added successfully.\n");
}

void saveMenuToCSV(char *filename, struct MenuItem menu[], int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s,%.2f\n", menu[i].name, menu[i].category, menu[i].price);
    }

    fclose(file);
}

void addEmployee(struct Employee employees[], int *count)
{
    printf("Enter name of the employee: ");
    fgets(employees[*count].name, sizeof(employees[*count].name), stdin);
    strtok(employees[*count].name, "\n");

    printf("Enter position of the employee: ");
    fgets(employees[*count].position, sizeof(employees[*count].position), stdin);
    strtok(employees[*count].position, "\n");

    printf("Enter salary of the employee: ");
    scanf("%f", &employees[*count].salary);
    getchar();

    printf("Enter mobile number of the employee: ");
    fgets(employees[*count].mobile, sizeof(employees[*count].mobile), stdin);
    strtok(employees[*count].mobile, "\n");

    printf("Enter address of the employee: ");
    fgets(employees[*count].address, sizeof(employees[*count].address), stdin);
    strtok(employees[*count].address, "\n");

    (*count)++;
    saveEmployeesToCSV("employees.csv", employees, *count);
    printf("Employee added successfully.\n");
}

void loadEmployeesFromCSV(char *filename, struct Employee employees[], int *count)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s not found, creating new file.\n", filename);
        file = fopen(filename, "w");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    *count = 0;
    while ((*count < MAX_EMPLOYEES) && fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        strcpy(employees[*count].name, token);

        token = strtok(NULL, ",");
        strcpy(employees[*count].position, token);

        token = strtok(NULL, ",");
        employees[*count].salary = atof(token);

        token = strtok(NULL, ",");
        strcpy(employees[*count].mobile, token);

        token = strtok(NULL, ",");
        strcpy(employees[*count].address, token);

        (*count)++;
    }

    fclose(file);
}

void saveEmployeesToCSV(char *filename, struct Employee employees[], int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s,%.2f,%s,%s\n", employees[i].name, employees[i].position, employees[i].salary, employees[i].mobile, employees[i].address);
    }

    fclose(file);
}

void generateBill(struct MenuItem menu[], int count)
{
    char customerName[50];
    printf("Enter customer's name: ");
    fgets(customerName, sizeof(customerName), stdin);
    strtok(customerName, "\n");

    char date[20];
    printf("Enter the date (YYYY-MM-DD): ");
    scanf("%s", date);
    getchar();

    char filename[50];
    sprintf(filename, "bills.csv");

    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    // Check if the file is empty to write the header
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "Customer,Date,Name,Category,Price,Quantity,Total\n");
    }

    struct tm billTime;
    sscanf(date, "%d-%d-%d", &billTime.tm_year, &billTime.tm_mon, &billTime.tm_mday);
    billTime.tm_year -= 1900;
    billTime.tm_mon -= 1;
    billTime.tm_hour = 0;
    billTime.tm_min = 0;
    billTime.tm_sec = 0;
    time_t billDate = mktime(&billTime);

    printf("Enter customer's order (enter 'done' to finish):\n");
    float total = 0;
    while (1)
    {
        char itemName[50];
        printf("Item name: ");
        fgets(itemName, sizeof(itemName), stdin);
        strtok(itemName, "\n");

        if (strcmp(itemName, "done") == 0)
        {
            break;
        }

        int quantity;
        printf("Quantity: ");
        scanf("%d", &quantity);
        getchar();

        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(itemName, menu[i].name) == 0)
            {
                float itemTotal = menu[i].price * quantity;
                fprintf(file, "%s,%s,%s,%s,%.2f,%d,%.2f\n", customerName, date, menu[i].name, menu[i].category, menu[i].price, quantity, itemTotal);
                total += itemTotal;
                printf("Total for %s (Quantity: %d): %.2f\n", menu[i].name, quantity, itemTotal);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Item '%s' not found in menu.\n", itemName);
        }
    }

    fprintf(file, "%s,Total,,,,,%.2f\n", date, total);
    fclose(file);

    printf("Total bill for %s: %.2f\n", customerName, total);
    printf("Bill generated successfully. Saved in bills.csv\n");
}
