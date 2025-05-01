#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 10
#define MAX_NAME_LEN 50
#define DAYS_IN_WEEK 7

const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char *shifts[] = {"Morning", "Evening", "Night"};

typedef struct {
    char name[MAX_NAME_LEN];
    int shift[DAYS_IN_WEEK]; // 0=Morning, 1=Evening, 2=Night
} Employee;

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

void addEmployee() {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Max employees reached.\n");
        return;
    }
    printf("Enter employee name: ");
    scanf(" %[^\n]", employees[employee_count].name);

    printf("Assign shifts for %s:\n", employees[employee_count].name);
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        int shift_choice;
        printf("  %s (0=Morning, 1=Evening, 2=Night): ", days[i]);
        scanf("%d", &shift_choice);
        if (shift_choice >= 0 && shift_choice <= 2)
            employees[employee_count].shift[i] = shift_choice;
        else {
            printf("Invalid shift. Defaulting to Morning.\n");
            employees[employee_count].shift[i] = 0;
        }
    }
    employee_count++;
}

void displayPerDay() {
    for (int day = 0; day < DAYS_IN_WEEK; day++) {
        printf("\n--- %s ---\n", days[day]);
        for (int i = 0; i < employee_count; i++) {
            printf("%s: %s\n", employees[i].name, shifts[employees[i].shift[day]]);
        }
    }
}

void displayPerWeek() {
    for (int i = 0; i < employee_count; i++) {
        printf("\n=== Schedule for %s ===\n", employees[i].name);
        for (int day = 0; day < DAYS_IN_WEEK; day++) {
            printf("%s: %s\n", days[day], shifts[employees[i].shift[day]]);
        }
    }
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < employee_count; i++) {
        fprintf(file, "%s\n", employees[i].name);
        for (int day = 0; day < DAYS_IN_WEEK; day++) {
            fprintf(file, "%s: %s\n", days[day], shifts[employees[i].shift[day]]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Schedule saved to %s\n", filename);
}

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Shift Planner\n");
        printf("1. Add Employee\n");
        printf("2. Display Schedule Per Day\n");
        printf("3. Display Schedule Per Week\n");
        printf("4. Save Schedule to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayPerDay();
                break;
            case 3:
                displayPerWeek();
                break;
            case 4:
                saveToFile("schedule.txt");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
