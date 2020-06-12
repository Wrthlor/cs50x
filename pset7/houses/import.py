from cs50 import SQL
from sys import argv
import string
import csv

# Checks for correct number of command-line arguments
if len(argv) != 2:
    print("Usage error: import.py characters.csv")
    exit()

# Creates database
db = SQL("sqlite:///students.db")

# Opens CSV file
with open(argv[1], "r") as csv_file:
    characters = csv.DictReader(csv_file, delimiter=",")

    # Iterate over CSV file
    for row in characters:

        # Splits names into list to check for middle names
        names = row["name"].split()

        # Characters with middle names
        if len(names) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       names[0], names[1], names[2], row["house"], row["birth"])

        # Characters without middle names
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       names[0], None, names[1], row["house"], row["birth"])
