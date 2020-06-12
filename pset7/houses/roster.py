from cs50 import SQL
from sys import argv
import string
import csv

# Checks for correct number of command-line arguments
if len(argv) != 2:
    print("Usage error: roster.py [House name]")
    exit()

# Creates database
db = SQL("sqlite:///students.db")

# Queries list of names and year from
list = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first",
                  argv[1])

# Iterates over generated list query
for row in list:

    # Characters without middle name
    if row["middle"] == None:
        print("{} {}, born {}".format(row["first"], row["last"], row["birth"]))

    # Characters with middle name
    else:
        print("{} {} {}, born {}".format(row["first"], row["middle"], row["last"], row["birth"]))