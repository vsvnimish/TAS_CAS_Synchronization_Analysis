🔒 Mutual Exclusion Algorithms – TAS, CAS & Bounded CAS

This project implements three mutual exclusion algorithms commonly used in concurrent programming:

TAS (Test-And-Set Lock)

CAS (Compare-And-Swap Lock)

Bounded Waiting CAS

Each program simulates multiple threads attempting to enter a critical section and measures:

Average waiting time

Worst-case waiting time

Effect of varying number of threads

Effect of varying number of CS attempts (k)

🛠️ Tech Stack

Language: C++

Concurrency: POSIX Threads (pthread)

Compiler: g++ (GNU C++ Compiler)

OS Compatibility: Linux / Unix-based systems

Input/Output: Text-based input (inp-params.txt) & output logs

Synchronization Methods:

Test-And-Set (TAS)

Compare-And-Swap (CAS)

Bounded CAS fairness mechanism

📁 Folder Requirements

Place the following files in the same directory:

inp-params.txt  
SrcAssgn3-tas-CS19B1026.cpp  
SrcAssgn3-cas-CS19B1026.cpp  
SrcAssgn3-cas-bounded-CS19B1026.cpp  


Programs read from inp-params.txt and generate output files locally.

🚀 How to Run

Below are the commands to compile and execute each program.

1️⃣ TAS Program
Compile
g++ -pthread SrcAssgn3-tas-CS19B1026.cpp -o p

Run
./p < inp-params.txt > TAS-ME-Output.txt

Output
TAS-ME-Output.txt

2️⃣ CAS Program
Compile
g++ -pthread SrcAssgn3-cas-CS19B1026.cpp -o g

Run
./g < inp-params.txt > CAS-ME-Output.txt

Output
CAS-ME-Output.txt

3️⃣ Bounded CAS Program
Compile
g++ -pthread SrcAssgn3-cas-bounded-CS19B1026.cpp -o j

Run
./j < inp-params.txt > Bounded-CAS-ME-Output.txt

Output
Bounded-CAS-ME-Output.txt

📊 Summary of Observations
⭐ TAS vs CAS

Behaviors are almost identical.

Average entry time to the critical section is nearly the same.

Minor differences in worst-case times are caused by scheduling variations.

⭐ CAS vs Bounded Waiting CAS

CAS: a thread can be overtaken up to (N − 1) × k times → more starvation.

Bounded CAS: overtaking limited to N − 1 times → fairer.

Therefore:

Bounded CAS has lower worst-case waiting time.

CAS may cause starvation under high contention.

Bounded CAS has slightly higher average entry time due to fairness checks.

📝 Notes

k = number of times each thread enters the critical section.

Output files contain timing logs used for graph generation.

Refer to the project report PDF for full analysis and explanation.
