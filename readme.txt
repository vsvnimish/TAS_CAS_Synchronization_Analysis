# 🔒 Mutual Exclusion Algorithms – TAS, CAS & Bounded CAS

This project implements three mutual exclusion algorithms commonly used in concurrent programming:

- **TAS (Test-And-Set Lock)**
- **CAS (Compare-And-Swap Lock)**
- **Bounded Waiting CAS**

Each program simulates multiple threads attempting to enter a critical section and measures:

- Average waiting time  
- Worst-case waiting time  
- Effect of varying number of threads  
- Effect of varying number of CS attempts (`k`)

---

# 🛠️ Tech Stack

- **Language:** C++  
- **Concurrency:** POSIX Threads (`pthread`)  
- **Build Tools:** g++ (GNU C++ Compiler)  
- **OS Compatibility:** Linux / Unix-based systems  
- **Input/Output:** Text-based input (`inp-params.txt`) & generated output logs  
- **Synchronization Primitives:**  
  - Test-And-Set (TAS)  
  - Compare-And-Swap (CAS)  
  - Bounded CAS fairness mechanism

---

## 📁 Folder Requirements

Make sure the following files are placed **in the same directory**:

```
inp-params.txt  
SrcAssgn3-tas-CS19B1026.cpp  
SrcAssgn3-cas-CS19B1026.cpp  
SrcAssgn3-cas-bounded-CS19B1026.cpp  
```

All programs read their inputs from `inp-params.txt` and produce output files in the same folder.

---

# 🚀 How to Run

Below are the steps to compile and execute each program.

---

## 1️⃣ TAS Program

### **Compile**
```bash
g++ -pthread SrcAssgn3-tas-CS19B1026.cpp -o p
```

### **Execute**
```bash
./p < inp-params.txt > TAS-ME-Output.txt
```

### **Output Produced**
```
TAS-ME-Output.txt
```

---

## 2️⃣ CAS Program

### **Compile**
```bash
g++ -pthread SrcAssgn3-cas-CS19B1026.cpp -o g
```

### **Execute**
```bash
./g < inp-params.txt > CAS-ME-Output.txt
```

### **Output Produced**
```
CAS-ME-Output.txt
```

---

## 3️⃣ Bounded CAS Program

### **Compile**
```bash
g++ -pthread SrcAssgn3-cas-bounded-CS19B1026.cpp -o j
```

### **Execute**
```bash
./j < inp-params.txt > Bounded-CAS-ME-Output.txt
```

### **Output Produced**
```
Bounded-CAS-ME-Output.txt
```

---

# 📊 Summary of Observations

### ⭐ **TAS vs CAS**
- Both algorithms behave almost the same.
- Average time to enter CS is nearly identical.
- Minor differences in worst-case times occur due to OS scheduling and thread swapping.

### ⭐ **CAS vs Bounded Waiting CAS**
- CAS: a thread may be overtaken up to **(N − 1) × k** times → more starvation.
- Bounded CAS: overtaking occurs at most **N − 1** times → far more fairness.
- Therefore:
  - **Bounded CAS generally has lower worst-case time.**
  - **CAS may exhibit higher starvation effects.**
- Bounded CAS has slightly higher average entry time due to its additional fairness loop.

---

# 📝 Notes

- `k` = number of times each thread attempts to enter the critical section.
- All output files contain timing logs used for plotting graphs.
- Refer to the project report PDF for complete analysis, explanations, and graphs.

---
