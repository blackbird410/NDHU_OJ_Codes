from math import pi, pow


def main():
    # Get the inputs
    test_cases = int(input())

    for _ in range(test_cases):
        n, f = [int(x) for x in input().split()]
        radii = [int(r) for r in input().split()]
        
        # Print the maximum volume
        v = get_max_volume(n, f, radii)
        print(v)


def get_max_volume(n, f, radii):
    """Returns the maximum volume of pie each person can have based on the number of pie(n), the number of friends(n) and the different radius in the radii list."""

    if n == 1:
        return round((pi * pow(radii[0], 2)) / (f + 1), 4)

    # Binary search algorithm
    min_v = 0
    max_v = pi * pow(max(radii), 2)

    # Start with the mid range value of the interval from 0 to the volume of the largest pie
    v = (min_v + max_v) / 2
    
    # Find the largest volume a pie can be divided into for everyone to have one piece of one pie
    while True:
        pieces = 0 
        for r in radii:
            pie_v = pi * pow(r, 2)
            pieces += pie_v // v

        # print(v)
        if pieces > f + 1:
            # Too small slices
            min_v = (max_v + min_v) / 2
        elif pieces < f + 1:
            # Too big slices
            max_v = (max_v + min_v) / 2
        prev_v = v
        v = (max_v + min_v) / 2

        if prev_v == v:
            return round(v, 4)


if __name__ == "__main__":
    main()
