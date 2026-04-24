#include <stdio.h>
#include <string.h>
#include "sort.h"

typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;


int compare_by_age(const void *a, const void *b) { 
    int diff = ((Employee *)a)->age - ((Employee *)b)->age;
    return (diff > 0) - (diff < 0);
}

int compare_by_salary(const void *a, const void *b) {   
    double diff = ((Employee *)a)->salary - ((Employee *)b)->salary;
    return (diff > 0) - (diff < 0);
}

int compare_by_name(const void *a, const void *b) {
    return strcmp(((Employee *)a)->name, ((Employee *)b)->name);
}

void print_employees(Employee *arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("%s, Age: %d, Salary: %.2f\n", arr[i].name, arr[i].age, arr[i].salary);
    }
}

int main() {
    Employee employees[] = {
        {"Alice", 25, 50000.0}, {"Bob", 30, 70000.0}, 
        {"Charlie", 22, 45000.0}, {"Dave", 35, 80000.0}
    };
    int N = sizeof(employees) / sizeof(employees[0]);

    printf("Sorted by Age:\n");
    shell_sort(employees, N, sizeof(Employee), compare_by_age);
    print_employees(employees, N);
    printf("\n");

    printf("Sorted by Salary:\n");
    shell_sort(employees, N, sizeof(Employee), compare_by_salary);
    print_employees(employees, N);
    printf("\n");

    printf("Sorted by Name:\n");
    shell_sort(employees, N, sizeof(Employee), compare_by_name);
    print_employees(employees, N);

    return 0;
}