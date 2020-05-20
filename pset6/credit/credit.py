# Modified program to NOT use any cs50 libraries / functions


# Main function
# Gets user credit card number and determines credit card type if valid
def main():
    # Loops until user puts in a string of numbers only
    while True:
        try:
            credit = input("Please enter Credit Card number: ")
        except ValueError:
            continue
        else:
            if credit.isdigit():
                break

    digits = len(credit)
    if checkSum(credit, digits):
        print(str(checkCard(credit, digits)))
    else:
        print("INVALID")


# Checks number with Luhn's Algorithm
# Method: Reverse CC string (creates iterations), use iterations in for loop
# Index for digits to multiply by 2 are not odd digits due to reversed string
def checkSum(cardNum, cardDig):
    sum = 0
    for i, digit in enumerate(reversed(cardNum)):
        # Reverse digits to iterate from left to right
        dig = int(digit)

        # Even digit placement
        if i % 2 == 0:
            sum += dig
        # Odd digit placement, produces 2 digits after doubling
        elif dig >= 5:
            sum += (dig * 2) - 9
        # Odd digit placement, produces 1 digit after doubling
        else:
            sum += dig * 2

    if sum % 10 == 0:
        return True
    else:
        return False


# Checks credit card type (company)
def checkCard(credNum, credLen):
    # Checks if card meets AMEX, MasterCard, Visa parameters
    if credLen == 15 or credLen == 16 or credLen == 13:
        # Checks for AMEX
        if int(credNum[:2]) == 34 or int(credNum[:2]) == 37:
            return "AMEX"
        elif int(credNum[:2]) in range(51, 56):
            return "MASTERCARD"
        elif int(credNum[0]) == 4:
            return "VISA"


# Calls main function
if __name__ == "__main__":
    main()