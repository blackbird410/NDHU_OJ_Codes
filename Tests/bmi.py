
def main():
    # Objective: Calculate the body mass index of a person.
    # Inputs: The body weight (kg) and height (cm) of the person
    # Output: The BMI with two decimal points.
    # Requirements : Creation of three variables (user_weight, user_height, bmi)

    # Take the user inputs
    try:
        user_weight = float(input("Enter the body weight(kg): "))
        user_height = float(input("Enter the height(cm): "))
        bmi = round(user_weight / user_height, 2)

        # If everything goes well print the BMI
        print(f"BMI: {bmi}")
    except ValueError:
        print("Wrong input! Please enter a number.")
    except ZeroDivisionError:
        print("Wrong input! Height cannot be zero.")


if __name__ == "__main__":
    main()
