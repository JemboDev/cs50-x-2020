# https://cs50.harvard.edu/x/2020/psets/6/credit/
# Program that determines whether a provided credit card number is valid according to Luhn’s algorithm (29.05.20)

from cs50 import get_string
from sys import exit


def main():
    # getting cc number from user
    credit_card_number = get_string("Number: ")

    # getting str len
    digits_count = len(credit_card_number)

    # cutting invalid cards by digit num right away
    if digits_count is not 13 and \
       digits_count is not 15 and \
       digits_count is not 16:
        print("INVALID")
        exit(0)

    # getting first two digits
    start_with = int(credit_card_number[:2])

    # validation using Luhn's Algorithm
    is_valid = luhn(credit_card_number)

    # final validation
    if (digits_count is 15 and
        (start_with is 34 or start_with is 37) and
            is_valid):
        print("AMEX")
    elif (digits_count is 16 and
          (start_with >= 51 and start_with <= 55) and
          is_valid):
        print("MASTERCARD")
    elif (digits_count is 13 or digits_count is 16 and
          (start_with >= 40 and start_with <= 49) and
          is_valid):
        print("VISA")
    else:
        print("INVALID")

# implementation of Luhn's Algorithm


def luhn(credit_card_number):
    even_sum, odd_sum = 0, 0
    odd_numbers = credit_card_number[-1::-2]
    even_numbers = credit_card_number[-2:: -2]

    for num in odd_numbers:
        odd_sum += int(num)

    for num in even_numbers:
        int_num = int(num)
        int_num *= 2
        int_num = int_num - 9 if int_num > 9 else int_num
        even_sum += int_num

    total_sum = even_sum + odd_sum

    return True if total_sum % 10 is 0 else False


main()
