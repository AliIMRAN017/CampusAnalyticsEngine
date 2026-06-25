#include <iostream>
#include <fstream>
#include <string>
#include "filehandler.h"

using namespace std;


int parseLineToFields(const string& line, string fields[], int maxFields) {
    int fieldCount = 0;
    string currentField = "";
    bool insideQuotes = false;

    for (size_t i = 0; i < line.length(); i++) {
        char ch = line[i];

        if (ch == '"') {
            insideQuotes = !insideQuotes; 
        } else if (ch == ',' && !insideQuotes) {
            if (fieldCount < maxFields) {
                fields[fieldCount++] = currentField;
            }
            currentField = "";
        } else {
            if (ch != '\r' && ch != '\n') {
                currentField += ch;
            }
        }
    }
    
    if (fieldCount < maxFields) {
        fields[fieldCount++] = currentField;
    }
    return fieldCount;
}


string getColumnValue(const string& line, int columnIndex) {
    string fields[20]; 
    int total = parseLineToFields(line, fields, 20);
    if (columnIndex >= 0 && columnIndex < total) {
        return fields[columnIndex];
    }
    return "";
}
