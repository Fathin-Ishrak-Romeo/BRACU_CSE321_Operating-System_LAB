#include <stdio.h>

struct Range {
    int start;
    int end;
};

int isPerfectNumber(int num) {
    int sum = 0;

    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    return sum == num;
}

void printPerfectNumbers(struct Range range) {
    printf("Perfect numbers between %d and %d are:\n", range.start, range.end);

    for (int i = range.start; i <= range.end; i++) {
        if (isPerfectNumber(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    struct Range range;

    printf("Enter the start of the range: ");
    scanf("%d", &range.start);
    printf("Enter the end of the range: ");
    scanf("%d", &range.end);

    printPerfectNumbers(range);

    return 0;
}
