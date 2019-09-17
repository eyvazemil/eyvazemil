#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar {
    struct TCar *m_Next;
    char *m_Model;
} TCAR;

typedef struct TEmployee {
    struct TEmployee *m_Next;
    struct TCar *m_Car;
    char *m_Name;
} TEMPLOYEE;

typedef struct TOffice {
    TEMPLOYEE *m_Emp;
    TCAR *m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */

// function to initialize an office in heap and return it
TOFFICE * initOffice() {
    TOFFICE * tmp = (TOFFICE *) malloc(sizeof(TOFFICE));
    tmp->m_Emp = NULL;
    tmp->m_Car = NULL;
    return tmp;
}

// function to create an employee
void addEmployee(TOFFICE * office, const char * name) {
    // create an employee in heap
    int length = (int) strlen(name);
    TEMPLOYEE * tmp = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
    // copy the name of the employee to the newly created employee
    char * str = (char *) malloc((length + 1) * sizeof(char));
    strncpy(str, name, length);
    str[length] = '\0';
    // add new employee to the particular office
    tmp->m_Next = office->m_Emp;
    tmp->m_Car = NULL;
    tmp->m_Name = str;
    office->m_Emp = tmp;
}

// function for creating a car
void addCar(TOFFICE * office, const char * model) {
    // create a car in heap
    int length = (int) strlen(model);
    TCAR * tmp = (TCAR *) malloc(sizeof(TCAR));
    // copy the model of the car to the newly created car
    char * str = (char *) malloc((length + 1) * sizeof(char));
    strncpy(str, model, length);
    str[length] = '\0';
    // add new car to the particular office
    tmp->m_Next = office->m_Car;
    tmp->m_Model = str;
    office->m_Car = tmp;
}

// this additional function simply clones each employee in office and connects it with other employees
void cloneAddEmployee(TOFFICE * office, TEMPLOYEE * employee, TEMPLOYEE * next_employee, char * name) {
    int length = (int) strlen(name);
    TEMPLOYEE * tmp = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
    char * str = (char *) malloc((length + 1) * sizeof(char));
    strncpy(str, name, length);
    str[length] = '\0';
    tmp->m_Next = next_employee;
    tmp->m_Car = NULL;
    tmp->m_Name = str;
    if(employee) employee->m_Next = tmp;
    if(!office->m_Emp) office->m_Emp = tmp;
}

// this additional function simply clones each car in office and connects it with other cars
TCAR * cloneAddCar(TOFFICE * office, TCAR * car, TCAR * next_car, char * model) {
    int length = (int) strlen(model);
    TCAR * tmp = (TCAR *) malloc(sizeof(TCAR));
    char * str = (char *) malloc((length + 1) * sizeof(char));
    strncpy(str, model, length);
    str[length] = '\0';
    tmp->m_Next = next_car;
    tmp->m_Model = str;
    if(car) car->m_Next = tmp;
    if(!office->m_Car) office->m_Car = tmp;
    return tmp;
}

// function to clone an office and return new office
TOFFICE * cloneOffice(TOFFICE * office) {
    // create new office in heap
    TOFFICE * tmp_office = initOffice();
    TEMPLOYEE * employee = office->m_Emp, * next_employee = NULL;
    TCAR * car = office->m_Car, *next_car = NULL;

    // clone employees in the office and connect the first newly cloned employee with new office
    while(employee) {
        cloneAddEmployee(tmp_office, employee, employee->m_Next, employee->m_Name);
        employee = employee->m_Next->m_Next;
    }

    // clone cars in the office and connect the first newly cloned car with new office
    while(car) {
        cloneAddCar(tmp_office, car, car->m_Next, car->m_Model);
        car = car->m_Next->m_Next;
    }

    // separate the cloned employees from the office and connect cloned employees with each other
    employee = office->m_Emp;
    while(employee) {
        if(employee->m_Car)
            employee->m_Next->m_Car = employee->m_Car->m_Next;
        else employee->m_Next->m_Car = NULL;
        next_employee = employee->m_Next->m_Next;
        if(next_employee)
            employee->m_Next->m_Next = employee->m_Next->m_Next->m_Next;
        else employee->m_Next->m_Next = NULL;
        employee->m_Next = next_employee;
        employee = next_employee;
    }

    // separate the cloned cars from the office and connect cloned cars with each other
    car = office->m_Car;
    while(car) {
        next_car = car->m_Next->m_Next;
        if(next_car)
            car->m_Next->m_Next = car->m_Next->m_Next->m_Next;
        else car->m_Next->m_Next = NULL;
        car->m_Next = next_car;
        car = next_car;
    }
    return tmp_office;
}

// function for freeing particular office
void freeOffice(TOFFICE * office) {
    TEMPLOYEE * employee = office->m_Emp;
    TEMPLOYEE * tmp_employee;
    TCAR * car = office->m_Car;
    TCAR * tmp_car;

    // free all employees
    while(employee) {
        tmp_employee = employee;
        employee = employee->m_Next;
        free(tmp_employee->m_Name);
        free(tmp_employee);
    }

    // free all cars
    while(car) {
        tmp_car = car;
        car = car->m_Next;
        free(tmp_car->m_Model);
        free(tmp_car);
    }
    free(office);
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TOFFICE *a, *b;
    char tmp[100];

    assert (sizeof(TOFFICE) == 2 * sizeof(void *));
    assert (sizeof(TEMPLOYEE) == 3 * sizeof(void *));
    assert (sizeof(TCAR) == 2 * sizeof(void *));
    a = initOffice();
    addEmployee(a, (char *) "Peter");
    addEmployee(a, (char *) "John");
    addEmployee(a, (char *) "Joe");
    addEmployee(a, (char *) "Maria");
    addCar(a, "Skoda Octavia");
    addCar(a, "VW Golf");
    a->m_Emp->m_Car = a->m_Car;
    a->m_Emp->m_Next->m_Next->m_Car = a->m_Car->m_Next;
    a->m_Emp->m_Next->m_Next->m_Next->m_Car = a->m_Car;
    assert (a->m_Emp
            && !strcmp(a->m_Emp->m_Name, "Maria")
            && a->m_Emp->m_Car == a->m_Car);
    assert (a->m_Emp->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Name, "Joe")
            && a->m_Emp->m_Next->m_Car == NULL);
    assert (a->m_Emp->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "John")
            && a->m_Emp->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert (a->m_Emp->m_Next->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
            && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car);
    assert (a->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
    assert (a->m_Car
            && !strcmp(a->m_Car->m_Model, "VW Golf"));
    assert (a->m_Car->m_Next
            && !strcmp(a->m_Car->m_Next->m_Model, "Skoda Octavia"));
    assert (a->m_Car->m_Next->m_Next == NULL);
    b = cloneOffice(a);
    strncpy (tmp, "Moe", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy (tmp, "Victoria", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy (tmp, "Peter", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy (tmp, "Citroen C4", sizeof(tmp));
    addCar(a, tmp);
    b->m_Emp->m_Next->m_Next->m_Next->m_Car = b->m_Car->m_Next->m_Next;
    assert(b->m_Emp->m_Next->m_Next->m_Car == b->m_Car->m_Next);

    assert (a->m_Emp
            && !strcmp(a->m_Emp->m_Name, "Peter")
            && a->m_Emp->m_Car == NULL);
    assert (a->m_Emp->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Name, "Victoria")
            && a->m_Emp->m_Next->m_Car == NULL);
    assert (a->m_Emp->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "Moe")
            && a->m_Emp->m_Next->m_Next->m_Car == NULL);
    assert (a->m_Emp->m_Next->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Maria")
            && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert (a->m_Emp->m_Next->m_Next->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Name, "Joe")
            && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Car == NULL);
    assert (a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "John")
            && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next->m_Next);
    assert (a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Peter")
            && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert (a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    assert (a->m_Car
            && !strcmp(a->m_Car->m_Model, "Citroen C4"));
    assert (a->m_Car->m_Next
            && !strcmp(a->m_Car->m_Next->m_Model, "VW Golf"));
    assert (a->m_Car->m_Next->m_Next
            && !strcmp(a->m_Car->m_Next->m_Next->m_Model, "Skoda Octavia"));
    assert (a->m_Car->m_Next->m_Next->m_Next == NULL);
    assert (b->m_Emp
            && !strcmp(b->m_Emp->m_Name, "Maria")
            && b->m_Emp->m_Car == b->m_Car);
    assert (b->m_Emp->m_Next
            && !strcmp(b->m_Emp->m_Next->m_Name, "Joe")
            && b->m_Emp->m_Next->m_Car == NULL);
    assert (b->m_Emp->m_Next->m_Next
            && !strcmp(b->m_Emp->m_Next->m_Next->m_Name, "John")
            && b->m_Emp->m_Next->m_Next->m_Car == b->m_Car->m_Next);
    assert (b->m_Emp->m_Next->m_Next->m_Next
            && !strcmp(b->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
            && b->m_Emp->m_Next->m_Next->m_Next->m_Car == NULL);
    assert (b->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
    assert (b->m_Car
            && !strcmp(b->m_Car->m_Model, "VW Golf"));
    assert (b->m_Car->m_Next
            && !strcmp(b->m_Car->m_Next->m_Model, "Skoda Octavia"));
    assert (b->m_Car->m_Next->m_Next == NULL);
    freeOffice(a);
    freeOffice(b);
    return 0;
}

#endif /* __PROGTEST__ */
