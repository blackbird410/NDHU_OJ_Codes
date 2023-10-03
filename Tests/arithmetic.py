
def main():
    # Objective : Do the four basic arithmetic operarions on two numbers provided by the user and print them.
    # Requirements : Round up the outputs by two decimal


    # Take two inputs from the user while expecting for a value error if the user try to enter an incorrect value (for example: x = "a")
    try:
        x = float(input("Enter a number: "))
        y = float(input("Enter another number: "))
    except ValueError:
        print("The value you entered is incorrect. Please try again")

    # Do the addition operation
    addition_result = round(x + y, 2)

    # Do the substraction operation
    substraction_result = round(x - y, 2)

    # Do the multiplication operation
    multiplication_result = round(x * y, 2)

    # Do the division operation IF POSSIBLE
    try:
        division_result = round(x / y, 2)
    except ZeroDivisionError:
        division_result = "Cannot divide by zero"

    # Print the results as formatted strings
    print("======== RESULTS ========")
    print(f"{x} + {y} = {addition_result:.2f}")
    print(f"{x} - {y} = {substraction_result:.2f}")
    print(f"{x} * {y} = {multiplication_result:.2f}")
    
    # Test if the division operation was successfull
    if str(division_result).isnumeric():
        print(f"{x} / {y} = {division_result:.2f}")
    else:
        print(division_result)

    # The rounding format in the formatted string force the program the output exactly two decimal, whether or not the decimals are zeros.

    return 0

if __name__ == "__main__":
    main()
