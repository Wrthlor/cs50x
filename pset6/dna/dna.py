from sys import argv
import csv


def main():

    # Checks for correct number of command-line arguments
    if len(argv) != 3:
        print("Usage error: dna.py database.csv sequence.txt")
        exit()

    # Open DNA sequence txt file and read contents into memory
    with open(argv[2], "r") as txt_file:
        dna = txt_file.read()

    # Open database csv file and read contents into memory
    with open(argv[1], "r") as csv_file:
        ppl = csv.reader(csv_file)
        # Gets all the keys from header of csv file
        keys = next(ppl)[1:]

        # Creates an array of integers to store STR repeats
        num = [0] * len(keys)
        for i in range(len(keys)):

            # Calls function to determine number of STR repeats
            num[i] = (calc_sequence(dna, keys[i]))

        # Calls function to check for any matches
        check_match(ppl, num)


def calc_sequence(dna_seq, dna_STR):

    # Declare counter variables and STR length
    count, tempMax = 0, 0
    l = len(dna_STR)

    # Loop through whole DNA sequence
    for i in range(len(dna_seq)):
        count = 0

        # Checks for STR match in DNA
        if (dna_seq[i: i + l] == dna_STR):

            # Keeps increasing count while there are matches
            while dna_seq[i: i + l] == dna_STR:
                count += 1
                i += l

            # Keeps track of highest number of sequential matches
            if count > tempMax:
                tempMax = count

    return tempMax


# Checks for STR count match
def check_match(people, comparator):

    for row in people:

        # Converts list to array of ints using map() function
        ppl_row = (list(map(int, row[1:])))

        # If there is a match, print the corresponding name
        if ppl_row == comparator:
            print(row[0])
            return

    print("No match")


if __name__ == "__main__":
    main()