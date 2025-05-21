import random
import sys

# -----------------------------------------------------------------------------
# Test Case Generation Logic
# -----------------------------------------------------------------------------
# This is where you customize the generation for each specific problem.
# The script should print the generated test case to standard output.
# -----------------------------------------------------------------------------

def generate_case():
    """Generates a single test case and prints it to stdout."""

    # --- Example 1: Single random number N (current default in template.cpp) ---
    # n = random.randint(1, 1000)
    # print(n)
    # return

    # --- Example 2: N, then N random numbers ---
    # n = random.randint(1, 10)
    # print(n)
    # arr = [random.randint(1, 100) for _ in range(n)]
    # print(*arr) # The * unpacks the list into space-separated values
    # return

    # --- Example 3: Two random numbers M and N ---
    # m = random.randint(1, 50)
    # n = random.randint(1, 50)
    # print(m, n)
    # return

    # --- Example 4: A random string ---
    # length = random.randint(1, 20)
    # s = ''.join(random.choice('abcde') for _ in range(length))
    # print(s)
    # return

    # --- Example 5: A grid/matrix ---
    # rows = random.randint(2, 5)
    # cols = random.randint(2, 5)
    # print(rows, cols)
    # for _ in range(rows):
    #     row_data = [random.randint(0, 9) for _ in range(cols)]
    #     print(*row_data)
    # return
    
    # --- Placeholder for the default problem in template.cpp (sum of 1 to N) ---
    # You should replace this with actual generation logic for your current problem.
    n = random.randint(1, 1000) # Default for sum 1 to N problem
    print(n)


# -----------------------------------------------------------------------------
# Script Execution
# -----------------------------------------------------------------------------
if __name__ == "__main__":
    # To generate a specific number of cases or use command-line args:
    # num_cases = 1
    # if len(sys.argv) > 1:
    #     try:
    #         num_cases = int(sys.argv[1])
    #     except ValueError:
    #         print(f"Usage: python {sys.argv[0]} [number_of_cases]", file=sys.stderr)
    #         sys.exit(1)
    # 
    # for _ in range(num_cases):
    #     generate_case()
    #     # If generating multiple cases to a single file, you might need a separator
    #     # or ensure your problem reader handles multiple concatenated cases.
    #     # print("---") # Example separator

    # For typical stress testing, test.sh calls this script once per test case.
    generate_case()
