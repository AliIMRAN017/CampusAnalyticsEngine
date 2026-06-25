#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "analytics.h"
#include "student.h"    
#include "filehandler.h"
using namespace std;

void generateDepartmentSummary() {
    ifstream dataReader("students.txt");
    if (!dataReader.is_open()) {
        cout << "Error: Registry file inaccessible." << endl;
        return;
    }

    string fileRow;
    getline(dataReader, fileRow);

    string majorNames[50];
    double scoreSums[50] = {0};
    int studentCounts[50] = {0};
    int uniqueMajors = 0;

    while (getline(dataReader, fileRow)) {
        if (fileRow == "") continue;
        if (getColumnValue(fileRow, 5) != "active") continue;

        string currentMajor = getColumnValue(fileRow, 2);
        
        double individualGpa = 0.0;
        try { individualGpa = stod(getColumnValue(fileRow, 4)); } catch(...) { continue; }

        int matchingIndex = -1;
        for (int idx = 0; idx < uniqueMajors; idx++) {
            if (majorNames[idx] == currentMajor) {
                matchingIndex = idx;
                break;
            }
        }

        if (matchingIndex != -1) {
            scoreSums[matchingIndex] += individualGpa;
            studentCounts[matchingIndex]++;
        } else if (uniqueMajors < 50) {
            majorNames[uniqueMajors] = currentMajor;
            scoreSums[uniqueMajors] = individualGpa;
            studentCounts[uniqueMajors] = 1;
            uniqueMajors++;
        }
    }
    dataReader.close();

    cout << "\n=====================================================" << endl;
    cout << "         INSTITUTIONAL DEPARTMENTAL SUMMARY          " << endl;
    cout << "=====================================================" << endl;
    cout << left << setw(25) << "Department Name" << setw(15) << "Total Students" << setw(15) << "Average CGPA" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (int idx = 0; idx < uniqueMajors; idx++) {
        double processedAvg = scoreSums[idx] / studentCounts[idx];
        cout << left << setw(25) << majorNames[idx] 
             << setw(15) << studentCounts[idx] 
             << setw(15) << fixed << setprecision(2) << processedAvg << endl;
    }
    cout << "=====================================================" << endl;
}


void generateMeritList() {
    Student qualifiedRecords[200];
    int recordCounter = 0;

    ifstream databaseFile("students.txt");
    if (!databaseFile.is_open()) return;

    string textLine;
    getline(databaseFile, textLine);

    while (getline(databaseFile, textLine) && recordCounter < 200) {
        if (textLine == "") continue;
        if (getColumnValue(textLine, 5) == "active") {
            qualifiedRecords[recordCounter].roll = getColumnValue(textLine, 0);
            qualifiedRecords[recordCounter].name = getColumnValue(textLine, 1);
            qualifiedRecords[recordCounter].dept = getColumnValue(textLine, 2);
            qualifiedRecords[recordCounter].semester = getColumnValue(textLine, 3);
            try { qualifiedRecords[recordCounter].cgpa = stod(getColumnValue(textLine, 4)); } catch(...) { qualifiedRecords[recordCounter].cgpa = 0.0; }
            recordCounter++;
        }
    }
    databaseFile.close();

    if (recordCounter == 0) {
        cout << "No active student entries available to evaluate merit." << endl;
        return;
    }

    // Bubble Sort
    for (int step = 0; step < recordCounter - 1; step++) {
        for (int cmpIdx = 0; cmpIdx < recordCounter - step - 1; cmpIdx++) {
            if (qualifiedRecords[cmpIdx].cgpa < qualifiedRecords[cmpIdx + 1].cgpa) {
                Student tempRecord = qualifiedRecords[cmpIdx];
                qualifiedRecords[cmpIdx] = qualifiedRecords[cmpIdx + 1];
                qualifiedRecords[cmpIdx + 1] = tempRecord;
            }
        }
    }

    cout << "\n====================================================================" << endl;
    cout << "                        CAMPUS MERIT LOG (TOP 10)                    " << endl;
    cout << "====================================================================" << endl;
    cout << left << setw(5) << "Pos" << setw(15) << "Roll No" << setw(25) << "Student Name" << setw(10) << "CGPA" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    int displayLimit = (recordCounter < 10) ? recordCounter : 10;
    for (int rankIdx = 0; rankIdx < displayLimit; rankIdx++) {
        cout << left << setw(5) << (rankIdx + 1) 
             << setw(15) << qualifiedRecords[rankIdx].roll 
             << setw(25) << qualifiedRecords[rankIdx].name 
             << setw(10) << fixed << setprecision(2) << qualifiedRecords[rankIdx].cgpa << endl;
    }
    cout << "====================================================================" << endl;
}


void exportSystemStatus() {
    ofstream exportStream("system_export_report.txt");
    if (!exportStream.is_open()) {
        cout << "Error creating export file asset." << endl;
        return;
    }

    exportStream << "CAMPUS ANALYTICS ENGINE - DATA SUMMARY EXPORT\n";
    exportStream << "Generated Security Timestamp Checkpoint context\n";
    exportStream << "-----------------------------------------------------\n";

    string registryFiles[] = {"students.txt", "courses.txt", "enrollments.txt", "attendance_log.txt", "fees.txt"};
    string trackingHeaders[] = {"Total Registered Student Rows: ", "Total Loaded Course Assets: ", "Total Enrollment Mappings: ", "Total Attendance Logs Filed: ", "Total Financial Ledgers: "};

    for (int sectionIdx = 0; sectionIdx < 5; sectionIdx++) {
        ifstream streamReader(registryFiles[sectionIdx]);
        int rowCounter = 0;
        if (streamReader.is_open()) {
            string singleRow;
            getline(streamReader, singleRow); 
            while (getline(streamReader, singleRow)) {
                if (singleRow != "") rowCounter++;
            }
            streamReader.close();
        }
        exportStream << trackingHeaders[sectionIdx] << rowCounter << "\n";
    }

    exportStream.close();
    cout << "Success: Enterprise system metrics exported to 'system_export_report.txt' safely." << endl;
}
