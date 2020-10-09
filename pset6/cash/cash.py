# https://cs50.harvard.edu/x/2020/psets/6/cash/
# Program that calculates the minimum number of coins required to give a user change (29.05.20)

from cs50 import get_float

# getting user's input
while True:
    change_owed = get_float("Change owed: ")
    if change_owed > 0:
        break

# converting to cents to avoid imprecision
cents = int(change_owed * 100)

# counting coins
while cents > 0:
    coins = cents // 25
    cents %= 25

    coins += cents // 10
    cents %= 10

    coins += cents // 5
    cents %= 5

    coins += cents
    cents = 0

print(coins)