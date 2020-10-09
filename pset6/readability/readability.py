# https://cs50.harvard.edu/x/2020/psets/6/readability/
# Program that computes the approximate grade level needed to comprehend some text (31.05.20)

from cs50 import get_string

# getting input from user
text = get_string("Text: ")

letters, words, sentences = 0, 0, 0

# iterating the text
for char in text:
    if char.isalpha():
        letters += 1
    elif char is " ":
        words += 1
    elif char is "." or char is "!" or char is "?":
        sentences += 1

words = 0 if text == "" else words + 1

# getting average letters and centences
L = letters * 100 / float(words)
S = sentences * 100 / float(words)

# getting the index
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade: {index}")