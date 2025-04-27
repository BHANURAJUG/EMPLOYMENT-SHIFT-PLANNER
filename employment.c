#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 10
#define DAYS 7
#define SHIFTS 3

const char* shift_names[SHIFTS] = {"Morning", "Evening", "Night"};
const char* day_names[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

typedef struct {
    char name[50];
    int availability[DAYS][SHIFTS]; // 1 if available, 0 otherwise
} Employee;

void initialize_availability(Employee employees[], int num_employees) {
    for (int i = 0; i < num_employees; i++) {
        for (int d = 0; d < DAYS; d++) {
            for (int s = 0; s < SHIFTS; s++) {
                employees[i].availability[d][s] = 1; // All available by default
            }
        }
    }
    // Example: Making Bob unavailable for Night shifts
    for (int d = 0; d < DAYS; d++) {
        employees[1].availability[d][2] = 0;
    }
}

void assign_shifts(Employee employees[], int num_employees, int schedule[DAYS][SHIFTS]) {
    int assigned[DAYS][MAX_EMPLOYEES] = {0};

    for (int d = 0; d < DAYS; d++) {
        for (int s = 0; s < SHIFTS; s++) {
            for (int e = 0; e < num_employees; e++) {
                if (employees[e].availability[d][s] && !assigned[d][e]) {
                    schedule[d][s] = e;
                    assigned[d][e] = 1;
                    break;
                }
            }
        }
    }
}

void print_schedule(Employee employees[], int schedule[DAYS][SHIFTS]) {
    printf("Shift Schedule:\n");
    for (int d = 0; d < DAYS; d++) {
        printf("%s:\n", day_names[d]);
        for (int s = 0; s < SHIFTS; s++) {
            int e = schedule[d][s];
            printf("  %s: %s\n", shift_names[s], employees[e].name);
        }
        printf("\n");
    }
}

int main() {
    Employee employees[MAX_EMPLOYEES] = {
        {"Alice"},
        {"Bob"},
        {"Carol"},
        {"Dave"},
        {"Eve"}
    };
    int num_employees = 5;
    int schedule[DAYS][SHIFTS];

    initialize_availability(employees, num_employees);
    assign_shifts(employees, num_employees, schedule);
    print_schedule(employees, schedule);

    return 0;
}