# https://cs50.harvard.edu/x/2020/psets/6/mario/more/
# Program that prints out a double half-pyramid of a specified height (29.05.20)

from cs50 import get_int

# getting input from user
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# building two pyramids
for i in range(height):
    print(" " * (height - i - 1), end='')
    print("#" * (i + 1), end='')
    print("  ", end='')
    print("#" * (i + 1), end='')
    print()