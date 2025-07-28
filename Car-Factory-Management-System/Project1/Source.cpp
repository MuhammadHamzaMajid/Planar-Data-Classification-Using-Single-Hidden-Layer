#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
void initialization();
void ratio(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float, float, float, int, int, int, int, int, int, int, int, int, int, int, int);
void carA_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float, float, float, int, int, int, int, int, int, int, int, int, int, int, int);
void carB_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float, float, float, int, int, int, int, int, int, int, int, int, int, int, int);
void carC_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float, float, float, int, int, int, int, int, int, int, int, int, int, int, int);
void buy(int, int, int, int, int, int);
void manufacturing(int, int, int);
void testing(int, int, int);
void sales(int, int, int);
int main(void)
{
    //Retrieving the Passwords

    FILE* fpass;
    fpass = fopen("Passwords.txt", "r");
    FILE* fpassint;
    fpassint = fopen("Password Values.txt", "w");
    char ch = fgetc(fpass);
    while (ch != EOF)
    {
        if (isdigit(ch)) {
            fputc(ch, fpassint);
        }
        if (isspace(ch)) {
            fputc(ch, fpassint);
        }
        ch = fgetc(fpass);
    }
    fclose(fpass);
    fclose(fpassint);

    int passworda, check;
    FILE* passcheck1;
    passcheck1 = fopen("Password Values.txt", "r");
    fscanf(passcheck1, "%d", &check);
    fclose(passcheck1);
    printf("\033[0;32m");
    printf("Control shifted to factory manager\n\n");
    printf("\033[0;33m");
    printf("Enter your password: ");
    scanf(" %d", &passworda);

    while (passworda != check)
    {
        printf("Wrong! Enter your password: ");
        scanf(" %d", &passworda);
    }
    printf("\nFile opened:\n");
    printf("\033[0;32m");
    printf("Press R to erase any previous records.\n");
    switch (_getch())
    {
    case 'R':
        FILE * erase;
        erase = fopen("Car Sales.txt", "w");
        fclose(erase);
        erase = fopen("Electricity Consumption.txt", "w");
        fclose(erase);
        erase = fopen("Testing.txt", "w");
        fclose(erase);
        erase = fopen("Time Duration.txt", "w");
        fclose(erase);
        erase = fopen("Ratios.txt", "w");
        fclose(erase);
        system("cls");
        break;
    }
    printf("Press S to start the recoding process.\n");
    switch (_getch())
    {
    case 'S':
        initialization();
    default:
        printf("Program terminated.\n");
    }
}
void initialization()
{
    //Retrieving Values from a file
    int Budget, imported_cost, local_cost, employee_sal;
    int carA_imported, carA_local, carA_employs;
    int carB_imported, carB_local, carB_employs;
    int carC_imported, carC_local, carC_employs;
    int carA_min, carB_min, carC_min;
    FILE* fp;
    fp = fopen("Project.txt", "r");
    FILE* fpint;
    fpint = fopen("Car values.txt", "w");
    char ch = fgetc(fp);
    while (ch != EOF)
    {
        if (isdigit(ch)) {
            fputc(ch, fpint);
        }
        if (isspace(ch)) {
            fputc(ch, fpint);
        }
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(fpint);

    fp = fopen("Car values.txt", "r");
    fscanf(fp, "%d", &Budget);
    fscanf(fp, "%d", &imported_cost);
    fscanf(fp, "%d", &local_cost);
    fscanf(fp, "%d", &employee_sal);
    fscanf(fp, "%d", &carA_imported);
    fscanf(fp, "%d", &carA_local);
    fscanf(fp, "%d", &carA_employs);
    fscanf(fp, "%d", &carB_imported);
    fscanf(fp, "%d", &carB_local);
    fscanf(fp, "%d", &carB_employs);
    fscanf(fp, "%d", &carC_imported);
    fscanf(fp, "%d", &carC_local);
    fscanf(fp, "%d", &carC_employs);
    fscanf(fp, "%d", &carA_min);
    fscanf(fp, "%d", &carB_min);
    fscanf(fp, "%d", &carC_min);
    fclose(fp);

    //Determining the costs of Cars per unit:
    int carA_cost = carA_imported * imported_cost + carA_local * local_cost + carA_employs * employee_sal;
    int carB_cost = carB_imported * imported_cost + carB_local * local_cost + carB_employs * employee_sal;
    int carC_cost = carC_imported * imported_cost + carC_local * local_cost + carC_employs * employee_sal;
    int q_carX = carA_cost + carB_cost + carC_cost, temp = q_carX;


    //This loop will give max number of car1s that can be produced, provided other cars are also produced
    q_carX = carA_cost + carB_cost + carC_cost;
    int n_carA = 0;
    while (q_carX <= Budget)
    {
        q_carX = carA_min * carA_cost + carB_min * carB_cost + carC_min * carC_cost + n_carA * carA_cost;
        if (q_carX <= Budget)
            n_carA += 1;
    }


    //This loop will give max number of car2s that can be produced, provided other cars are also produced
    q_carX = carA_cost + carB_cost + carC_cost;
    int n_carB = 0;
    while (q_carX <= Budget)
    {
        q_carX = carA_min * carA_cost + carB_min * carB_cost + carC_min * carC_cost + n_carB * carB_cost;
        if (q_carX <= Budget)
            n_carB += 1;
    }

    //This loop will give max number of car3s that can be produced, provided other cars are also produced
    q_carX = carA_cost + carB_cost + carC_cost;
    int n_carC = 0;
    while (q_carX <= Budget)
    {
        q_carX = carA_min * carA_cost + carB_min * carB_cost + carC_min * carC_cost + n_carC * carC_cost;
        if (q_carX <= Budget)
            n_carC += 1;
    }
    if (n_carA <= 1 && n_carB <= 1 && n_carC <= 1) {
        printf("This budget is unsufficient to produce a profit.\nPress Esc to exit.\n");
    }
    else
    {
        fp = fopen("Project.txt", "r");
        ch = fgetc(fp);
        while (ch != EOF)
        {
            printf("%c", ch);
            ch = fgetc(fp);
        }
        fclose(fp);
        printf("\n");
        printf("\033[0;31m");
        printf("Press S to enter a specific ratio in which you want to produce the cars.\n");
        printf("Press A to minimize the production of carA.\n");
        printf("Press B to minimize the production of carB.\n");
        printf("Press C to minimize the production of carC.\n");
        switch (_getch())
        {
        case 'S':
            system("cls");
            ratio(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'A':
            system("cls");
            carA_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'B':
            system("cls");
            carB_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'C':
            system("cls");
            carC_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        }
    }
}
void ratio(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float carA_cost, float carB_cost, float carC_cost, int carA_imported, int carA_local, int carA_employs, int carB_imported, int carB_local, int carB_employs, int carC_imported, int carC_local, int carC_employs, int employee_sal, int local_cost, int imported_cost)
{
    float carA_ratio, carB_ratio, carC_ratio;
    printf("\033[0;32m");
    printf("Enter the ratio in which you want to produce the cars: ");
    printf("\033[0;31m");
    scanf_s(" %f %f %f", &carA_ratio, &carB_ratio, &carC_ratio);
    printf("\033[0;35m");
    printf("For the given ratio:\n\n");
    int t = 0, u = 0, v = 0;
    int q_carX;
    for (int i = carA_min; i <= carA_min || i <= n_carA; i++)
    {
        for (int j = carB_min; j <= carB_min || j <= n_carB; j++)
        {
            for (int k = carC_min; k <= carC_min || k <= n_carC; k++)
            {
                q_carX = i * carA_cost + j * carB_cost + k * carC_cost;
                if (q_carX <= Budget && (float(i) / float(j) <= (carA_ratio / carB_ratio) + 0.1) && (float(i) / float(j) >= (carA_ratio / carB_ratio) - 0.1) && (float(i) / float(k) <= (carA_ratio / carC_ratio) + 0.1) && (float(i) / float(k) >= (carA_ratio / carC_ratio) - 0.1)) {
                    t = int(i), u = int(j), v = int(k);
                }
            }
        }
    }
    int total_imported = t * carA_imported + u * carB_imported + v * carC_imported;
    int total_local = t * carA_local + u * carB_local + v * carC_local;
    int total_employs = t * carA_employs + u * carB_employs + v * carC_employs;
    printf("Imported Materials: %d\n", total_imported);
    printf("Local Materials: %d\n", total_local);
    printf("Employs needed: %d\n", total_employs);
    printf("Cars produced:\n");
    printf("Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
    printf("Employee's Salary: %d\n", total_employs * employee_sal);
    printf("Total Cost for Local Materials: %d\n", local_cost * total_local);
    printf("Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
    printf("Budget used: %.1f (out of %.1f)\n", t * carA_cost + u * carB_cost + v * carC_cost, Budget);
    if (total_employs == 0) {
        printf("\033[0m");
        printf("This is not a valid ratio in the given budget. Please press Y to reenter, or X to go back to initialization.\n");
        switch (_getch())
        {
        case 'Y':
            system("cls");
            ratio(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'X':
            system("cls");
            initialization();
            break;
        }
    }
    else {
        FILE* pointer;
        pointer = fopen("Ratios.txt", "a");
        FILE* fp;
    fp = fopen("Project.txt", "r");
    FILE* fpint;
    fpint = fopen("Car values.txt", "w");
    char ch = fgetc(fp);
    while (ch != EOF)
    {
        if (isdigit(ch)) {
            fputc(ch, fpint);
        }
        if (isspace(ch)) {
            fputc(ch, fpint);
        }
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(fpint);
        fprintf(pointer, "Cars are produced in the ratio: %d : %d : %d\n", int(carA_ratio), int(carB_ratio), int(carC_ratio));
        fprintf(pointer, "Cars produced:\n");
        fprintf(pointer, "Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
        fprintf(pointer, "Imported Materials: %d\n", total_imported);
        fprintf(pointer, "Local Materials: %d\n", total_local);
        fprintf(pointer, "Employs needed: %d\n", total_employs);
        fprintf(pointer, "Employee's Salary: %d\n", total_employs * employee_sal);
        fprintf(pointer, "Total Cost for Local Materials: %d\n", local_cost * total_local);
        fprintf(pointer, "Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
        fprintf(pointer, "Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
        fprintf(pointer, "--------------------------------------------------------");
        fclose(pointer);
        printf("\033[0;32m");
        printf("Press V to buy the parts and hire employs: ");
        switch (_getch()) {
        case 'V':
            system("cls");
            buy(total_imported, total_local, total_employs, t, u, v);
        }
    }
}
void carA_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float carA_cost, float carB_cost, float carC_cost, int carA_imported, int carA_local, int carA_employs, int carB_imported, int carB_local, int carB_employs, int carC_imported, int carC_local, int carC_employs, int employee_sal, int local_cost, int imported_cost)
{
    float carB_ratio, carC_ratio;
    printf("\033[0;32m");
    printf("Enter the ratio in which you want to produce the remaining cars: ");
    printf("\033[0;31m");
    scanf_s(" %f %f", &carB_ratio, &carC_ratio);
    printf("\033[0;35m");
    printf("For the given ratio:\n\n");
    int t = 0, u = 0, v = 0;
    int q_carX;
    for (int i = carA_min; i <= carA_min; i++)
    {
        for (int j = carB_min; j <= carB_min || j <= n_carB; j++)
        {
            for (int k = carC_min; k <= carC_min || k <= n_carC; k++)
            {
                q_carX = i * carA_cost + j * carB_cost + k * carC_cost;
                if (q_carX <= Budget && (float(j) / float(k) <= (carB_ratio / carC_ratio) + 0.1) && (float(j) / float(k) >= (carB_ratio / carC_ratio) - 0.1)) {
                    t = int(i), u = int(j), v = int(k);
                }
            }
        }
    }
    int total_imported = t * carA_imported + u * carB_imported + v * carC_imported;
    int total_local = t * carA_local + u * carB_local + v * carC_local;
    int total_employs = t * carA_employs + u * carB_employs + v * carC_employs;
    printf("Imported Materials: %d\n", total_imported);
    printf("Local Materials: %d\n", total_local);
    printf("Employs needed: %d\n", total_employs);
    printf("Cars produced:\n");
    printf("Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
    printf("Employee's Salary: %d\n", total_employs * employee_sal);
    printf("Total Cost for Local Materials: %d\n", local_cost * total_local);
    printf("Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
    printf("Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
    if (total_employs == 0) {
        printf("\033[0m");
        printf("This is not a valid ratio in the given budget. Please press Y to reenter, or X to go back to initialization.\n");
        switch (_getch())
        {
        case 'Y':
            system("cls");
            carA_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'X':
            system("cls");
            initialization();
            break;
        }
    }
    else {
        FILE* pointer1;
        pointer1 = fopen("Ratios.txt", "a");
        fprintf(pointer1, "Cars were produced in the ratio: B(%d) : C(%d) & %d carAs", int(carB_ratio), int(carC_ratio), carC_min);
        fprintf(pointer1, "Cars are produced in the ratio: %d : %d : %d\n", 0, int(carB_ratio), int(carC_ratio));
        fprintf(pointer1, "Cars produced:\n");
        fprintf(pointer1, "Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
        fprintf(pointer1, "Imported Materials: %d\n", total_imported);
        fprintf(pointer1, "Local Materials: %d\n", total_local);
        fprintf(pointer1, "Employs needed: %d\n", total_employs);
        fprintf(pointer1, "Employee's Salary: %d\n", total_employs * employee_sal);
        fprintf(pointer1, "Total Cost for Local Materials: %d\n", local_cost * total_local);
        fprintf(pointer1, "Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
        fprintf(pointer1, "Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
        fprintf(pointer1, "--------------------------------------------------------");
        fclose(pointer1);
        printf("\033[0;32m");
        printf("Press V to buy the parts and hire employs: ");
        switch (_getch()) {
        case 'V':
            system("cls");
            buy(total_imported, total_local, total_employs, t, u, v);
        }
    }
}
void carB_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float carA_cost, float carB_cost, float carC_cost, int carA_imported, int carA_local, int carA_employs, int carB_imported, int carB_local, int carB_employs, int carC_imported, int carC_local, int carC_employs, int employee_sal, int local_cost, int imported_cost)
{
    float carA_ratio, carC_ratio;
    printf("\033[0;32m");
    printf("Enter the ratio in which you want to produce the remaining cars: ");
    printf("\033[0;31m");
    scanf_s(" %f %f", &carA_ratio, &carC_ratio);
    printf("\033[0;35m");
    printf("For the given ratio:\n\n");
    int t = 0, u = 0, v = 0;
    int q_carX;
    for (int i = carA_min; i <= carA_min || i <= n_carA; i++)
    {
        printf("a");
        for (int j = carB_min; j <= carB_min; j++)
        {
            for (int k = carC_min; k <= carC_min || k <= n_carC; k++)
            {
                q_carX = i * carA_cost + j * carB_cost + k * carC_cost;
                if (q_carX <= Budget && (float(i) / float(k) <= (carA_ratio / carC_ratio) + 0.1) && (float(i) / float(k) >= (carA_ratio / carC_ratio) - 0.1)) {
                    t = int(i), u = int(j), v = int(k);
                }
            }
        }
    }
    int total_imported = t * carA_imported + u * carB_imported + v * carC_imported;
    int total_local = t * carA_local + u * carB_local + v * carC_local;
    int total_employs = t * carA_employs + u * carB_employs + v * carC_employs;
    printf("Imported Materials: %d\n", total_imported);
    printf("Local Materials: %d\n", total_local);
    printf("Employs needed: %d\n", total_employs);
    printf("Cars produced:\n");
    printf("Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
    printf("Employee's Salary: %d\n", total_employs * employee_sal);
    printf("Total Cost for Local Materials: %d\n", local_cost * total_local);
    printf("Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
    printf("Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
    if (total_employs == 0) {
        printf("\033[0m");
        printf("This is not a valid ratio in the given budget. Please press Y to reenter, or X to go back to initialization.\n");
        switch (_getch())
        {
        case 'Y':
            system("cls");
            carB_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'X':
            system("cls");
            initialization();
            break;
        }
    }
    else {
        FILE* pointer1;
        pointer1 = fopen("Ratios.txt", "a");
        fprintf(pointer1, "Cars were produced in the ratio: A(%d) : C(%d) & %d carBs", int(carA_ratio), int(carC_ratio), carB_min);
        fprintf(pointer1, "Cars are produced in the ratio: %d : %d : %d\n", int(carA_ratio), 0, int(carC_ratio));
        fprintf(pointer1, "Cars produced:\n");
        fprintf(pointer1, "Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
        fprintf(pointer1, "Imported Materials: %d\n", total_imported);
        fprintf(pointer1, "Local Materials: %d\n", total_local);
        fprintf(pointer1, "Employs needed: %d\n", total_employs);
        fprintf(pointer1, "Employee's Salary: %d\n", total_employs * employee_sal);
        fprintf(pointer1, "Total Cost for Local Materials: %d\n", local_cost * total_local);
        fprintf(pointer1, "Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
        fprintf(pointer1, "Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
        fprintf(pointer1, "--------------------------------------------------------");
        fclose(pointer1);

        printf("\033[0;32m");
        printf("Press V to buy the parts and hire employs: ");
        switch (_getch()) {
        case 'V':
            system("cls");
            buy(total_imported, total_local, total_employs, t, u, v);
        }
    }
}
void carC_minimum(float Budget, int carA_min, int carB_min, int carC_min, int n_carA, int n_carB, int n_carC, float carA_cost, float carB_cost, float carC_cost, int carA_imported, int carA_local, int carA_employs, int carB_imported, int carB_local, int carB_employs, int carC_imported, int carC_local, int carC_employs, int employee_sal, int local_cost, int imported_cost)
{
    float carA_ratio, carB_ratio;
    printf("\033[0;32m");
    printf("Enter the ratio in which you want to produce the remaining cars: ");
    printf("\033[0;31m");
    scanf_s(" %f %f", &carA_ratio, &carB_ratio);
    printf("\033[0;35m");
    printf("For the given ratio:\n\n");
    int t = 0, u = 0, v = 0;
    int q_carX;
    for (int i = carA_min; i <= carA_min || i <= n_carA; i++)
    {
        for (int j = carB_min; j <= carB_min || j <= n_carB; j++)
        {
            for (int k = carC_min; k <= carC_min; k++)
            {
                q_carX = i * carA_cost + j * carB_cost + k * carC_cost;
                if (q_carX <= Budget && (float(i) / float(k) <= (carA_ratio / carB_ratio) + 0.1) && (float(i) / float(k) >= (carA_ratio / carB_ratio) - 0.1)) {
                    t = int(i), u = int(j), v = int(k);
                }
            }
        }
    }
    int total_imported = t * carA_imported + u * carB_imported + v * carC_imported;
    int total_local = t * carA_local + u * carB_local + v * carC_local;
    int total_employs = t * carA_employs + u * carB_employs + v * carC_employs;
    printf("Imported Materials: %d\n", total_imported);
    printf("Local Materials: %d\n", total_local);
    printf("Employs needed: %d\n", total_employs);
    printf("Cars produced:\n");
    printf("Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
    printf("Employee's Salary: %d\n", total_employs * employee_sal);
    printf("Total Cost for Local Materials: %d\n", local_cost * total_local);
    printf("Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
    printf("Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);

    if (total_employs == 0) {
        printf("\033[0m");
        printf("This is not a valid ratio in the given budget. Please press Y to reenter, or X to go back to initialization.\n");
        switch (_getch())
        {
        case 'Y':
            system("cls");
            carC_minimum(Budget, carA_min, carB_min, carC_min, n_carA, n_carB, n_carC, carA_cost, carB_cost, carC_cost, carA_imported, carA_local, carA_employs, carB_imported, carB_local, carB_employs, carC_imported, carC_local, carC_employs, employee_sal, local_cost, imported_cost);
            break;
        case 'X':
            system("cls");
            initialization();
            break;
        }
    }
    else {
        FILE* pointer1;
        pointer1 = fopen("Ratios.txt", "a");
        fprintf(pointer1, "Cars were produced in the ratio: A(%d) : B(%d) & %d carCs", int(carA_ratio), int(carB_ratio), carC_min);
        fprintf(pointer1, "Cars are produced in the ratio: %d : %d : %d\n", int(carA_ratio), int(carB_ratio), 0);
        fprintf(pointer1, "Cars produced:\n");
        fprintf(pointer1, "Car1: %d\nCar2: %d\nCar3: %d\n", t, u, v);
        fprintf(pointer1, "Imported Materials: %d\n", total_imported);
        fprintf(pointer1, "Local Materials: %d\n", total_local);
        fprintf(pointer1, "Employs needed: %d\n", total_employs);
        fprintf(pointer1, "Employee's Salary: %d\n", total_employs * employee_sal);
        fprintf(pointer1, "Total Cost for Local Materials: %d\n", local_cost * total_local);
        fprintf(pointer1, "Total Cost for Imported Materials: %d\n", imported_cost * total_imported);
        fprintf(pointer1, "Budget used: %.1f\n", t * carA_cost + u * carB_cost + v * carC_cost);
        fprintf(pointer1, "--------------------------------------------------------");
        fclose(pointer1);
        printf("\033[0;32m");
        printf("Press V to buy the parts and hire employs: ");
        switch (_getch()) {
        case 'V':
            system("cls");
            buy(total_imported, total_local, total_employs, t, u, v);
        }
    }
}
void buy(int total_imported, int total_local, int total_employs, int t, int u, int v)
{
    int time_imported, time_local, time_hiring;
    printf("\033[0;32m");
    printf("Enter the time taken for the arrival of imported parts: ");
    printf("\033[0;33m");
    scanf_s(" %d", &time_imported);
    printf("\033[0;32m");
    printf("Enter the time taken for the arrival of local parts: ");
    printf("\033[0;33m");
    scanf_s(" %d", &time_local);
    printf("\033[0;32m");
    printf("Enter the time taken to hire employs: ");
    printf("\033[0;33m");
    scanf_s(" %d", &time_hiring);
    FILE* ftime;
    ftime = fopen("Time Duration.txt", "a");
    fprintf(ftime, "The time taken for arrival of imported parts(in days): %d\n", time_imported);
    fprintf(ftime, "The time taken for arrival of local parts(in days): %d\n", time_local);
    fprintf(ftime, "The time taken for arranging employees(in days): %d\n", time_hiring);
    fclose(ftime);
    system("cls");
    manufacturing(t, u, v);
}
void manufacturing(int t, int u, int v)
{
    float electricity_carA, electricity_carB, electricity_carC;
    float time_a, time_b, time_c;
    int passworda, check;
    FILE* passcheck;
    passcheck = fopen("Password Values.txt", "r");
    fscanf(passcheck, "%d", &check);
    fscanf(passcheck, "%d", &check);
    fclose(passcheck);
    printf("\033[0; 32m");
    printf("Control shifted to assembly manager\n\n");
    printf("\033[0;33m");
    printf("Enter your password: ");
    scanf(" %d", &passworda);

    while (passworda != check)
    {
        printf("\033[0m");
        printf("Wrong! Enter your password: ");
        scanf(" %d", &passworda);
    }
    printf("\033[0;31m");
    printf("\nFile opened:\n");
    printf("At the assembly line of Car A:\n");
    printf("Electricity consumption for %d cars(total): ", t);
    scanf_s(" %f", &electricity_carA);
    printf("Time duration for manufacturing %d cars: ", t);
    scanf_s(" %f", &time_a);
    printf("\nAt the assembly line of Car B:\n");
    printf("Electricity consumption for %d cars(total): ", u);
    scanf_s(" %f", &electricity_carB);
    printf("Time duration for manufacturing %d cars: ", u);
    scanf_s(" %f", &time_b);
    printf("\nAt the assembly line of Car C:\n");
    printf("Electricity consumption for %d cars(total): ", v);
    scanf_s(" %f", &electricity_carC);
    printf("Time duration for manufacturing %d cars: ", v);
    scanf_s(" %f", &time_c);

    FILE* ftimer;
    FILE* felectricity;
    ftimer = fopen("Time Duration.txt", "a");
    felectricity = fopen("Electricity Consumption.txt", "a");
    fprintf(ftimer, "The time taken for production of A-type Cars: %f\n", time_a);
    fprintf(ftimer, "The time taken for production of B-type Cars: %f\n", time_b);
    fprintf(ftimer, "The time taken for production of C-type Cars: %f\n", time_c);
    fprintf(felectricity, "ELectricity consumed for carA: %f\n", electricity_carA);
    fprintf(felectricity, "ELectricity consumed for carB: %f\n", electricity_carB);
    fprintf(felectricity, "ELectricity consumed for carC: %f\n", electricity_carC);
    fprintf(felectricity, "Average electricty used/carA: %f\n", float(t) / electricity_carA);
    fprintf(felectricity, "Average electricty used/carB: %f\n", float(u) / electricity_carB);
    fprintf(felectricity, "Average electricty used/carC: %f\n", float(v) / electricity_carC);
    fprintf(felectricity, "------------------------------------------------------------\n");
    fprintf(ftimer, "Average time taken / carA: %f\n", float(t) / time_a);
    fprintf(ftimer, "Average time taken / carB: %f\n", float(u) / time_b);
    fprintf(ftimer, "Average time taken / carC: %f\n", float(v) / time_c);
    fprintf(ftimer, "------------------------------------------------\n");
    fclose(ftimer);
    fclose(felectricity);
    system("cls");
    testing(t, u, v);
}
void testing(int t, int u, int v)
{
    int passworda, check;
    FILE* passcheck3;
    passcheck3 = fopen("Password Values.txt", "r");
    fscanf(passcheck3, "%d", &check);
    fscanf(passcheck3, "%d", &check);
    fscanf(passcheck3, "%d", &check);
    fclose(passcheck3);
    printf("\033[0;32m");
    printf("Control shifted to testing manager\n\n");
    printf("\033[0;31m");
    printf("Enter your password: ");
    printf("\033[0;33m");
    scanf(" %d", &passworda);

    while (passworda != check)
    {
        printf("\033[0;31m");
        printf("Wrong! Enter your password: ");
        scanf(" %d", &passworda);
    }

    printf("File opened: \n");
   
    printf("\033[0;32m");
    printf("At the testing Site:\n\n");
    int A_fail1, A_fail2, A_fail3, B_fail1, B_fail2, B_fail3, C_fail1, C_fail2, C_fail3;
    printf("How many A-type Cars(out of %d) failed Test 1? ", t);
    scanf_s(" %d", &A_fail1);
    printf("How many A-type Cars(out of %d) failed Test 2? ", t);
    scanf_s(" %d", &A_fail2);
    printf("How many A-type Cars(out of %d) failed Test 3? ", t);
    scanf_s(" %d", &A_fail3);

    printf("How many B-type Cars(out of %d) failed Test 1? ", u);
    scanf_s(" %d", &B_fail1);
    printf("How many B-type Cars(out of %d) failed Test 2? ", u);
    scanf_s(" %d", &B_fail2);
    printf("How many B-type Cars(out of %d) failed Test 3? ", u);
    scanf_s(" %d", &B_fail3);

    printf("How many C-type Cars(out of %d) failed Test 1? ", v);
    scanf_s(" %d", &C_fail1);
    printf("How many C-type Cars(out of %d) failed Test 2? ", v);
    scanf_s(" %d", &C_fail2);
    printf("How many C-type Cars(out of %d) failed Test 3? ", v);
    scanf_s(" %d", &C_fail3);

    FILE* fp1;
    fp1 = fopen("Testing.txt", "a");
    fprintf(fp1, "On average, %f %% car As fail test 1.\n", (float(A_fail1) / float(t)) * 100);
    fprintf(fp1, "On average, %f %% car As fail test 2.\n", (float(A_fail2) / float(t)) * 100);
    fprintf(fp1, "On average, %f %% car As fail test 3.\n", (float(A_fail3) / float(t)) * 100);

    fprintf(fp1, "On average, %f %% car Bs fail test 1.\n", (float(B_fail1) / float(u)) * 0.01);
    fprintf(fp1, "On average, %f %% car Bs fail test 2.\n", (float(B_fail2) / float(u)) * 100);
    fprintf(fp1, "On average, %f %% car Bs fail test 3.\n", (float(B_fail3) / float(u)) * 100);

    fprintf(fp1, "On average, %f %% car Cs fail test 1.\n", (float(C_fail1) / float(v)) * 100);
    fprintf(fp1, "On average, %f %% car Cs fail test 2.\n", (float(C_fail2) / float(v)) * 100);
    fprintf(fp1, "On average, %f %% car Cs fail test 3.\n", (float(C_fail3) / float(v)) * 100);
    fprintf(fp1, "--------------------------------------------------------------------------\n");
    fclose(fp1);
    system("cls");
    sales(t, u, v);
}
void sales(int t, int u, int v)
{
    int passworda, check;
    FILE* passcheck4;
    passcheck4 = fopen("Password Values.txt", "r");
    fscanf(passcheck4, "%d", &check);
    fscanf(passcheck4, "%d", &check);
    fscanf(passcheck4, "%d", &check);
    fscanf(passcheck4, "%d", &check);
    fclose(passcheck4);
    printf("\033[0;32m");
    printf("Control shifted to sales manager\n\n");
    printf("\033[0;33m");
    printf("Enter your password: ");
    printf("\033[0;31m");
    scanf(" %d", &passworda);

    while (passworda != check)
    {
        printf("Wrong! Enter your password: ");

        scanf(" %d", &passworda);
    }

    printf("File opened: \n");
    //Retrieving Values from a file
    int carA, carB, carC, temp;
    FILE* fp;
    fp = fopen("Project.txt", "r");
    FILE* fpint;
    fpint = fopen("Car values.txt", "w");
    char ch = fgetc(fp);
    while (ch != EOF)
    {
        if (isdigit(ch)) {
            fputc(ch, fpint);
        }
        if (isspace(ch)) {
            fputc(ch, fpint);
        }
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(fpint);

    fp = fopen("Car Values.txt", "r");
    for (int l = 1; l < 23; l++)
    {
        fscanf(fp, "%d", &temp);
        if (l == 14) {
            carA = temp;
        }
        if (l == 15) {
            carB = temp;
        }
        if (l == 16) {
            carC = temp;
        }
    }
    int time;
    printf("Enter the time duration during which you want to measure the car sales(in days): ");
    scanf_s(" %d", &time);
    int carA_sales, carB_sales, carC_sales;
    printf("CarA s sold in %d days:", time);
    scanf_s(" %d", &carA_sales);
    printf("CarB s sold in %d days:", time);
    scanf_s(" %d", &carB_sales);
    printf("CarC s sold in %d days:", time);
    scanf_s(" %d", &carC_sales);
    FILE* file, f;
    file = fopen("Car Sales.txt", "a");
    fprintf(file, "Sales of Car A within %d days: %d\n", time, carA_sales);
    fprintf(file, "Sales of Car B within %d days: %d\n", time, carB_sales);
    fprintf(file, "Sales of Car C within %d days: %d\n", time, carC_sales);
    if (carA_sales <= carA)
        fprintf(file, "\nCar A is not being sold in desired quantity!\n");
    if (carB_sales <= carB)
        fprintf(file, "\nCar B is not being sold in desired quantity!\n");
    if (carC_sales <= carC)
        fprintf(file, "\nCar C is not being sold in desired quantity!\n");
    fprintf(file, "-----------------------------------------------------------\n");
    fclose(file);
    printf("Complete stats of car production have been uploaded of one complete run for the factory manager.\n");
}
