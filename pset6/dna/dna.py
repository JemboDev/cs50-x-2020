# https://cs50.harvard.edu/x/2020/psets/6/dna/
# Program that identifies a person based on their DNA (06.06.2020)

from sys import argv, exit
import csv
import re

# checking for exactly 2 arguments after the name
if len(argv) is not 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# getting info from .csv and .txt files
with open(argv[1]) as input_data, open(argv[2]) as input_sequence:
    # getting list of STRs without 'name' field (STRs[0])
    csv_dict_reader = csv.DictReader(input_data)
    STRs = list(csv_dict_reader.fieldnames)
    STRs.pop(0)

    # getting info about diff people's STRs
    # [{'name': 'Alice', 'AGAT': '4'...}, ...]
    data = []
    for row in csv_dict_reader:
        data.append(dict(row))

    # getting sequence string
    sequence = input_sequence.read().replace("\n", "")

# iterating through STRs, looking for matches in sequence
# found look like     [('AGATAGATAGAT', 'AGAT')]
# matches looks like  {'AGAT': 3, 'ATAT': 5, ...}
matches = {}
for STR in STRs:
    found = re.findall(rf'(({STR})\2+)', sequence)
    if not found:
        continue
    longest = 0
    length = len(found[0][0])
    for item in found:
        if len(item[0]) > length:
            longest = found.index(item)
    matches[STR] = str(len(found[longest][0]) // len(STR))

# looking for match in data
for person in data:
    found = bool(matches)
    for key in matches:
        if matches[key] != person[key]:
            found = False
    if found:
        print(person['name'])
        exit(0)

# if nothing matches
print("No match")