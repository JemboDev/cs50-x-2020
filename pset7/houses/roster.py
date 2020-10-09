# https://cs50.harvard.edu/x/2020/psets/7/houses/
# Program to produce class rosters (18.06.20)

from sys import argv, exit
from cs50 import SQL

# Checking for exactly 1 arg after prog's name
if len(argv) != 2:
    print("Usage: roster.py Gryffindor")
    exit(1)

# Connecting to the students database
db = SQL("sqlite:///students.db")

# Getting ordered students as list of dicts
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# Printing one by one
for person in students:

    first = person['first']
    middle = person['middle']
    last = person['last']
    birth = person['birth']

    if middle is None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")