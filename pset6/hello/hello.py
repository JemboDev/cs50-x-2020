# https://cs50.harvard.edu/x/2020/psets/6/hello/
# Program that prints out a simple greeting to the user (29.05.20)

from cs50 import get_string

name = get_string("What's your name?\n")
print(f"hello, {name}")