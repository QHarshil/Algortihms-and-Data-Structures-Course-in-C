
import random

QUESTIONS = ["which part of the array is already sorted after one pass?",
"how would we sort this array in place without a swap function? What code would change, and how would it change?",
"which lines of code ensure that this sort is stable, and why?",
"Walk through the operation of your sort on the array [3, 2, 1] and explain each operation as it sorts."
"explain your use of a pointer in sortIntegers (where is/are the pointers and why do you use them?)",
"What is the minimum amount of code you could change to make this sort descending instead of ascending?",
"How much space does your implmentation of insertion sort use? Could you use less?"]


def main():

    choice = random.choice(QUESTIONS)
    print(choice)

if __name__ == "__main__":
    main()