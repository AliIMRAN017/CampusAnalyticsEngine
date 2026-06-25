# Campus Analytics Engine 🎓

Campus Analytics Engine is a C++ based management system designed to streamline institutional records, analyze student performance, generate merit logs, and handle system audit metrics efficiently.

---

## 🚀 Key Features
* **Departmental Summary:** Computes active student headcounts and average CGPAs per department.
* **Campus Merit Log:** Automatically filters and sorts the Top 10 students based on academic performance.
* **System Audit Exporter:** Scans registry files (`students.txt`, `courses.txt`, etc.) and generates an authorized data summary export.
* **Graceful Error Handling:** Equipped with fallback mechanisms for corrupted or malformed data records.

---

## 🛠️ Prerequisites
Before running this project, ensure you have a C++ compiler installed on your system:
* **Windows:** MinGW / GCC
* **macOS:** Apple Clang / Xcode Command Line Tools
* **Linux:** GCC

To check if you have `g++` installed, run:
```bash
g++ --version

💻 How to Compile and Run
Since this project consists of multiple .cpp files, they must all be compiled together. Follow the instructions below based on your operating system:

1. Open Terminal in Project Directory
Open your terminal (or VS Code integrated terminal) and ensure you are in the root directory where all the .cpp and .h files are located.

2. Compilation & Execution Commands
🔹 Windows (PowerShell / CMD)
Run the following shortcut command to compile all files and execute the application:

PowerShell
g++ *.cpp -o campus_app && .\campus_app.exe
Or step-by-step:

PowerShell
# Compile
g++ *.cpp -o campus_app

# Run
.\campus_app.exe
🔹 macOS / Linux (Terminal)
Run the following shortcut command:

Bash
g++ *.cpp -o campus_app && ./campus_app
Or step-by-step:

Bash
# Compile
g++ *.cpp -o campus_app

# Run
./campus_app
📂 Project Structure
Main.cpp - Core application workflow and menu systems.

Analytics.cpp / .h - Data processing, sorting, and reporting logic.

Student.cpp / .h - Student record models and structures.

Attendance.cpp / .h - Tracking logs and presence database management.

*.txt - Database flat-files (Registry entries).

