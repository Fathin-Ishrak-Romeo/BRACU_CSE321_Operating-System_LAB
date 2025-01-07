#include <stdio.h>

int main() {
    char str[100];
    char *start, *end; 
    int isPalindrome = 1; 

    printf("Enter a string: ");
    scanf("%s", str);

    start = str; 
    end = str; 

    while (*end != '\0') {
        end++;
    }
    end--; 

    while (start < end) {
        if (*start != *end) {
            isPalindrome = 0; 
            break;
        }
        start++;
        end--;
    }

    if (isPalindrome) {
        printf("Palindrome.");
    } else {
        printf("Not Palindrome.");
    }

    return 0;
}
