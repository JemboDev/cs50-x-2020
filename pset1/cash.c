// https://lab.cs50.io/cs50/labs/2020/x/cash/
// Change coins count [greedy algorithm] (04.04.20)

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coins; // min num of coins
    float dollars; // user's input
    // getting user's input as dollars
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    // converting dollars to cents to avoid imprecision of floating-point values
    int cents = round(dollars * 100);
    // counting the least amount of coins
    while (cents > 0)
    {
        coins = cents / 25;
        cents %= 25;

        coins += (cents / 10);
        cents %= 10;

        coins += (cents / 5);
        cents %= 5;

        coins += cents;
        cents = 0;
    }
    printf("%i\n", coins);
}
