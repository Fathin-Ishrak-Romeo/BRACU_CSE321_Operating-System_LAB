#include <stdio.h>

int main() {
    int num1;
    int num2;
    int result;

    printf("Enter first number:");
    scanf(" %d", &num1);
    
    printf("Enter second number:");
    scanf(" %d", &num2);

    if (num1 > num2) {
        printf("The first number is greater than the second number. \n");
        result = (num1 - num2);
        printf("Result: %d \n", result);
    } 
    
    else if (num1 < num2) {
        printf("The first number is less than the second number. \n");
        result = (num1 + num2);
        printf("Result: %d \n", result);
    } 
    
    else if (num1 == num2) {
        printf("the first number is equal to the second number \n");
        result = (num1 * num2);
        printf("Result: %d \n", result);
    }

}