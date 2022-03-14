import sys


def bmi(weight, height):
    return 1.00 * weight / (height * height)


if __name__ == '__main__':
    w = input('Your weight (kg): ')
    try:
        w = int(w) # from string
    except:
        print("Invalid weight")
        sys.exit(1)

    h = input('Your height (meter): ')
    try:
        h = float(h)
    except:
        print("Invalid height")
        sys.exit(2)

    result = bmi(w, h)
    print(f"Your BMI is {round(result, 2)}")
