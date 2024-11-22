### banker-allocation
Project #2  for Operating Systems

## Functions

### Common
- **`calculateNeed`**:
  - Computes the `Need` matrix, which represents the remaining resources required by each process to complete.
  - Formula: `Need[i][j] = Max[i][j] - Allocation[i][j]`.

- **`printMatrix`**:
  - Prints a 2D matrix (e.g., `Allocation`, `Max`, or `Need`) for debugging and verification.

- **`printArray`**:
  - Prints a 1D array (e.g., `Available` or `Work`) for debugging and verification.

- **`isSafe`**:
  - Determines if the system is in a safe state.
  - Implements the Banker's Algorithm logic to find a safe sequence of process execution if one exists.

#### Functions:
- **`main`**:
  - Reads input data from a file (`data.txt`) containing:
    - Number of processes and resources.
    - Available resources.
    - Allocation and Max matrices.
  - Initializes arrays and matrices with the input data.
  - Validates input and ensures no uninitialized memory access.
  - Calls the `isSafe` function to check if the system is in a safe state.
  - Outputs the results, including the safe sequence if applicable.

### `isSafe`

#### Logic:
- **Initialization**:
  - Creates and initializes the `Finish` array to track completed processes.
  - Copies the `Available` resources into a `Work` array to simulate the state of resources during execution.

- **Safety Check**:
  - Iterates over all processes to find one whose `Need` can be satisfied with the current `Work` array.
  - If a process is found:
    - Marks it as finished.
    - Adds its allocated resources to the `Work` array (simulating resource release).

- **Result**:
  - If all processes can be executed safely, outputs the safe sequence.
  - If no safe sequence exists, declares the system unsafe.

## Debugging Tools
- **`printMatrix`**:
  - Prints matrices such as `Allocation`, `Max`, and `Need` for step-by-step verification.
- **`printArray`**:
  - Prints arrays such as `Available` and `Work` to trace resource allocation and availability.
- **Intermediate Outputs**:
  - Logs the state of the system after each process allocation (e.g., updated `Work` and `Finish` arrays).

## Input File (`data.txt`)
- Format:

