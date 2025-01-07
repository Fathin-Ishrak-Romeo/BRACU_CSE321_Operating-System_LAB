#include <stdio.h>
#include <string.h>

int main() {
        
    char pass[50];

    printf("Provide a new password: ");
    scanf("%s", pass);
    
    int length = strlen(pass);
    int lowerCase = 0, upperCase = 0, digit = 0, specialChar = 0;
    
    for (int i = 0; i < length; i++) {
        char j = pass[i];
        
        if (j >= 'a' && j <= 'z') {
            lowerCase++;
        }

        else if (j >= 'A' && j <= 'Z') {
            upperCase++;
        }

        else if (j >= '0' && j <= '9') {
            digit++;
        }

        else if (j == '_' || j == '$' || j == '#' || j == '@') {
            specialChar++;
        }
    }


    if (lowerCase && upperCase && digit && specialChar) {
        printf("OK! \n");
    }
    
    else{
        if (!lowerCase) {
            printf("Lowercase character missing.\n");
        }
    
        if (!upperCase) {
            printf("Uppercase character missing.\n");
        }
    
        if (!digit) {
            printf("Digit missing.\n");
        }
    
        if (!specialChar) {
            printf("Special character missing.\n");
        }
    }

}