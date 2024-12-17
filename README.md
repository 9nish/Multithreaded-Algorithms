# Multithreaded Algorithms in C++

This repository contains the design and implementation of parallel algorithms using threads in C++. The project focuses on achieving efficient multithreading, analyzing both theoretical and practical performance metrics, and contrasting them with serial implementations.

---

## **Project Overview**

- **Goal**: To implement and analyze parallel versions of fundamental and advanced algorithms for matrix operations and graph problems.
- **Theoretical Model**: Used the **fork-join parallelism model** to measure:
  - **Work**: Total operations executed across all threads.
  - **Span**: Longest chain of dependent operations.
  - **Parallelism**: Ratio of work to span.
- **Practical Analysis**: Coarsened base cases to minimize overhead from excessive thread spawning, ensuring practical speedups compared to serial implementations.

---

## **Algorithms Implemented**

Each algorithm includes:
- **Serial Implementation**: For correctness verification and baseline performance comparison.
- **Parallel Implementation**: Designed using multithreading to exploit parallelism.

### **Matrix Operations**
1. **Matrix-Vector Multiplication**  
   - Parallelized the computation of rows and columns independently.
2. **Matrix-Matrix Multiplication**  
   - Parallelized individual block multiplications.
3. **Matrix Transposition**  
   - Designed parallel tasks to handle rows and columns of the matrix.
4. **Divide-and-Conquer Matrix Multiplication**  
   - Used a parallelized recursive approach for matrix block multiplication.
5. **Strassen's Algorithm**  
   - Parallelized Strassen's divide-and-conquer algorithm for matrix multiplication.

### **Graph Algorithm**
6. **Floyd-Warshall Algorithm**  
   - Parallelized the computation of shortest paths for all pairs in a weighted graph.

---

## **Performance Insights**
- **Thread Sanitizer**: Verified thread safety using `-fsanitize=thread` to ensure no data races or synchronization issues.
- **Key Findings**:
  - Excessive thread spawning leads to performance degradation due to overhead.
  - Coarsening the recursion base cases significantly improves runtime for practical inputs.

---

## **Repository Structure**

Each folder contains:
- Serial implementation files for correctness verification and baseline performance.
- Parallel implementation files using multithreading.

### **Example Folder Structure**
```plaintext
Multithreaded_Algorithms/
├── Matrix_Vector_Multiplication/
│   ├── serial_MatVecMul.cpp
│   ├── parallel_MatVecMul.cpp
├── Floyd_Warshall/
│   ├── serial_FloydWarshall_TestCase1.cpp
│   ├── parallel_FloydWarshall_TestCase1.cpp
│   ├── serial_FloydWarshall_TestCase2.cpp
│   ├── parallel_FloydWarshall_TestCase2.cpp
└── ...
```

---

## **How to Run**

### **Requirements**
- **Compiler**: g++ with C++11 or later.

### **Compilation and Execution**
1. Clone the repository:
   ```bash
   git clone https://github.com/9nish/Multithreaded_Algorithms.git
   cd Multithreaded_Algorithms
   ```
2. Navigate to the desired algorithm's folder, e.g., Matrix_Vector_Multiplication:
    ```bash
    cd Matrix_Vector_Multiplication
    ```
3. Compile the parallel implementation:
    ```bash
    g++ -o parallel_MatVecMul parallel_MatVecMul.cpp -pthread
    ```
4. Run the executable:
    ```bash
    ./parallel_MatVecMul
    ```
5. Optional Debugging
    To check for thread safety:
    ```bash
    g++ -fsanitize=thread -g parallel_MatVecMul.cpp -o debug_parallel -pthread
    ./debug_parallel
    ```