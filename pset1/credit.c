// https://lab.cs50.io/cs50/labs/2020/x/credit/
// Credit card number validation (08.04.20)

#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool luhn(long cc_num, int digit_count);

int main(void)
{
    // getting user's input
    long cc_num = get_long("Enter your CC number: ");
    // counting # of digits in cc_number
    int digit_count = (cc_num == 0) ? 1 : (log10(cc_num) + 1);
    // getting rid of invalid nums based on the digit_count first
    if (digit_count != 13 &&
        digit_count != 15 &&
        digit_count != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        // getting first two digits
        int start_with = cc_num / pow(10, digit_count - 2);
        // checking cc_num using Luhn's Algorithm
        bool valid = luhn(cc_num, digit_count);
        // final check to determine cc type
        if (digit_count == 15 && 
            (start_with == 34 || start_with == 37) &&
            valid)
        {
            printf("AMEX\n");
        }
        else if (digit_count == 16 && 
                 (start_with >= 51 && start_with <= 55) &&
                 valid)
        {
            printf("MASTERCARD\n");
        }
        else if ((digit_count == 13 || digit_count == 16) && 
                 (start_with >= 40 && start_with <= 49) &&
                 valid)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
// implementation of Luhn's Algorithm 
bool luhn(long cc_num, int digit_count)
{
    int odd_sum = 0, even_sum = 0, total_sum;
    // getting digits one-by-one and doing Luhn's stuff :D
    for (int i = 1; i <= digit_count; i++) 
    {
        int digit = cc_num % 10;

        if (i % 2 != 0)
        {
            odd_sum += digit;
        }
        else
        {
            digit *= 2;
            // dealing w/ 2 digit numbers (adding those products' digits)
            if (digit > 9)
            {
                digit -= 9;
            }

            even_sum += digit;
        }
        cc_num /= 10; // trimming used digits
    }

    total_sum = odd_sum + even_sum;

    if (total_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
