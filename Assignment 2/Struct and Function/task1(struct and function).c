#include <stdio.h>

struct Item {
    int quantity;
    float unit_price;
};

float calculateItemCost(struct Item item) {
    return item.quantity * item.unit_price;
}

float calculatePerPersonPayment(float total_bill, int num_people) {
    return total_bill / num_people;
}

int main() {
    struct Item paratha, vegetable, water;
    int num_people;
    float total_bill, per_person_payment;

    printf("Quantity of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

    printf("Quantity of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetable.unit_price);

    printf("Quantity of Mineral Water: ");
    scanf("%d", &water.quantity);
    printf("Unit Price: ");
    scanf("%f", &water.unit_price);

    total_bill = calculateItemCost(paratha) + 
                 calculateItemCost(vegetable) + 
                 calculateItemCost(water);

    printf("Number of People: ");
    scanf("%d", &num_people);

    per_person_payment = calculatePerPersonPayment(total_bill, num_people);

    printf("Individual people will pay: %.2f tk\n", per_person_payment);

    return 0;
}
