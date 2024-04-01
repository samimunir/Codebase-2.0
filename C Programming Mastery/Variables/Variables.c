/*
    Sami Munir
    March 31st, 2024
    C Programming Mastery
    Variables
    Variables.c
*/

#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("Variables -->\n-------------\n");

    int x = 7;
    printf("the variable [x] contains the value: %d\n", x);
    int y = 556;
    printf("the variable [y] contains the value: %d\n", y);
    float gpa = 2.05;
    printf("the variable [gpa] contains the value: %f\n", gpa);
    char grade = 'C';
    printf("the variable [grade] contains the value: %c\n", grade);
    char name[] = "Sambreezy";
    printf("the variable [name] contains the value: %s\n", name);

    /*
        char data type
        - single character
        - %c
        - 1 byte
    */
    char s = '$';
    /*
        char[] data type
        - array of characters
        - %s
        - >= 0 bytes
    */
    char string[] = "C Programming";
    /*
        float data type
        - 32 bits of precision (6-7 digits)
        - %f
        - 4 bytes
    */
    float floating_point_number = 3.141592;
    /*
        double data type
        - 64 bits of precisions (15-16 digits)
        - %lf
        - 8 bytes
    */
    double double_number = 3.141592653589793;
    /*
        bool (boolean) data type
        - %d
        - 1 byte
    */
    bool flag = true;
    /*
        short int
        - (-32,768 to +32,767)
        - %d
        - 2 bytes
    */
    short int short_int = 2;
    /*
        unsigned int
        - %u
        - 4 bytes
    */
    unsigned int z = 11;

    return 0;
}