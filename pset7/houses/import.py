# https://cs50.harvard.edu/x/2020/psets/7/houses/
# Program to import student data into a database (18.06.20)

from sys import argv, exit
from cs50 import SQL
import csv

# Checking for exactly 1 arg after prog's name
if len(argv) != 2:
    print("Usage: import.py characters.csv")
    exit(1)

# Connecting to the students database
db = SQL("sqlite:///students.db")

# Clearing db before insertion
db.execute("DELETE FROM students")

# Resetting id auto increment value
db.execute("UPDATE SQLITE_SEQUENCE SET SEQ=0 WHERE NAME='students'")

# Opening .csv file and inserting info into db
with open(argv[1]) as input_data:
    csv_dict_reader = csv.DictReader(input_data)
    for row in csv_dict_reader:

        # Parsing name into first, last and middle if any
        name = row["name"].split()
        first = name[0]
        middle = name[1] if len(name) == 3 else None
        last = name[1] if len(name) == 2 else name[2]

        # Inserting parsed vals into db
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   first, middle, last, row["house"], row["birth"])