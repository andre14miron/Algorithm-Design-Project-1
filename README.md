# Algorithm Design Project #1

## Description
This problem set served as the first assignment for the "Algorithm Design" course, covering the following algorithms: Divide et Impera, Greedy and Dynamic Programming. The set consists of four main problems, along with a bonus problem. Each problem is solved using specific algorithmic techniques as outlined below:
- **Problem #1** : `Binary Search with Knapsack Problem`
- **Problem #2**: `Greedy`
- **Problem #3**: `Dynamic Programming - Knapsack Variation`
- **Problem #4**: `Dynamic Programming - Matrix Manipulation`
- **Problem #5**: `Matrix Exponentiation for Linear Recurrence`

!! The problem requirements can be found in the PDF file of the assignment. !!


## Problem #1: Feribot (Ferry)
### Solution
To find the smallest possible value for C, a `binary search` algorithm is employed. The search interval is determined by:
- Cmin: the heaviest car can be alone on a ferry, or m cars with the lightest weight.
- Cmax: the heaviest m cars that can be loaded on a ferry.

The binary search utilizes the `knapsack problem` to determine if C is a valid solution. If it is, the search is continued with smaller values; otherwise, the search continues with higher values.

### Complexity:
- **Time Complexity**: O(n + n*log(n))
- **Space Complexity**: O(n)

## Problem #2: Nostory
### Solution Task #1:
For this task, the goal is to create a vector that contains the largest elements from the union of two input vectors. The union vector is sorted to obtain the desired elements.

### Solution Task #2:
The algorithm is similar to Task #1. To account for allowed moves, a new structure is created to store the value and index in the original vector. The sorted union vector is searched for the largest elements. If an element has been previously selected from the same index, it is considered a move. A separate vector is used to keep track of the moves. If no more moves are available, the search area is expanded.

### Complexity:
- **Time Complexity**: O(n)
- **Space Complexity**: O(n)

## Problem #3: Sushi
### Solution Task #1:
The algorithm for this task follows the principles of dynamic programming, specifically the knapsack problem. The score of a sushi platter corresponds to the value of objects in the knapsack, and the price of the platter corresponds to the weight, constrained by a budget.

### Complexity:
- **Time Complexity**: O(m * n * x)
- **Space Complexity**: O(m * n * x)

### Solution Task #2:
Similar to Task #1, but considering the constraint of having at most 2 platters of each type. Each identical platter is treated as a separate object with the same properties.

### Complexity:
- **Time Complexity**: O(m * n * x)
- **Space Complexity**: O(m * n * x)

### Solution Task #3:
The algorithm considers the previous solutions and optimizes for having at most n platters. An extra field is added to the matrix to keep track of the number of used platters. If choosing a platter with k platters already used, the solution is compared to the previous solution with k-1 platters. To verify if 2 platters of the same type are used, the moment when k-2 platters were used is checked. The maximum solution is selected.

### Complexity:
- **Time Complexity**: O(m * n^2 * x)
- **Space Complexity**: O(m * n^2 * x)

## Problem #4: Semnale (Signals)
## Solution Task #1:
Dynamic programming is used to solve this task. Two matrices, fr0 and fr1, are created to store the number of signals with k bits where the last bit is 0 and 1, respectively. Each column j represents the number of signals containing j 1 bits. The matrices are generated as follows: 
- **the number of signals with the last bit 0 and k bits of 1** is the sum of 
    - signals with the last bit 0 and k bits of 1 that just received 0
    - signals with the last bit 1 and k bits of 1 that just received 0
- **the number of signals with the last bit 1 and k bits of 1** is the number of signals with the last bit 0 and k-1 bits of 1 that just received 1 (thus having k bits).

### Complexity:
- **Time Complexity**: O(xy + y^2)
- **Space Complexity**: O(xy + y^2)

### Solution Task #2:
Similar to Task #1, but accounting for signals ending in 11. To account for signals with k bits, only two vectors are needed instead of an entire matrix. The matrices are generated as follows: 
- **the number of signals with the last bit 0 and k bits of 1** is the sum of 
    - signals with the last bit 0 and k bits of 1 that just received 0, 
    - signals with the last bit 1 and k bits of 1 that just received 0
    - signals with the last bits 11 and k bits of 1 that just received 0. 
- **the number of signals with the last bit 1 and k bits of 1** is the number of signals with the last bit 0 and k-1 bits of 1 that just received 1 (thus having k bits)
- **the number of signals with the last bits 11 and k bits of 1** is the number of signals with the last bit 1 and k-1 bits of 1 that just received 1 (thus having k bits).

### Complexity:
- **Time Complexity**: O(x*y + y^2)
- **Space Complexity**: O(y)

## Problem #5 (bonus): BadGPT
### Solution
The compressed string is parsed character by character. If a compressed group of interest is detected, the corresponding flags are activated. If a digit is found while a flag is active, it is added to the number of occurrences. Once a group ends, the number of generated strings is calculated using the Fibonacci number of the generated number plus one. The Fibonacci number is calculated using the `Matrix Exponentiation for Linear Recurrence` algorithm from the lecture materials.

### Complexity
- **Time Complexity**: O(m * log(n))
- **Space Complexity**: O(N^2 + m)
