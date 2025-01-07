#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_extra_spaces(const char *input_file, const char *output_file) {
    FILE *input, *output;
    char line[1000];
    
    input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error: Could not open the input file.\n");
        exit(1);
    }
    
    output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error: Could not open the output file.\n");
        fclose(input);
        exit(1);
    }
    
    while (fgets(line, sizeof(line), input)) {
        char *token = strtok(line, " ");
        int first_word = 1;

        while (token != NULL) {
            if (!first_word) {
                fprintf(output, " ");
            }
            fprintf(output, "%s", token);
            first_word = 0;
            token = strtok(NULL, " ");
        }
    }

    fclose(input);
    fclose(output);
}

int main() {
    const char *input_file = "input1.txt";
    const char *output_file = "output1.txt";

    remove_extra_spaces(input_file, output_file);

    printf("Extra spaces removed successfully. Check '%s' for the result.\n", output_file);
    return 0;
}
