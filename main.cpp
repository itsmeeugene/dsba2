#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


// Function to read data from a CSV file
void readCSVFile(const string& filename, vector<Point>& points) {
    ifstream file(filename);

    string line, cell;
    while (getline(file, line)) {
        stringstream lineStream(line);
        Point point;
        int id_point = 0;
        double value;
        string name;

        while (getline(lineStream, cell, ',')) {
            if (!cell.empty()) {
                if (id_point == 0) {
                    point.setID(stoi(cell));
                } else if (id_point == 1) {
                    name = cell;
                } else {
                    value = stod(cell);
                    point.addValue(value);
                }
                id_point++;
            }
        }

        // Create a new Point object
        point.setName(name);
        points.push_back(point);
    }

    file.close();
}

// Function to write data to a CSV file
void writeCSVFile(const string& filename, const vector<Point>& points) {
    ofstream file(filename);

    for (const auto& point : points) {
        file << point.getID() << "," << point.getName() << ",";

        for (int i = 0; i < point.getTotalValues(); i++) {
            file << point.getValue(i) << ",";
        }

        file << "\n";
    }

    file.close();
}

int main() {
    string inputFile = "synthetic_credit_consumers.csv";
    string outputFile = "processed_data.csv";

    vector<Point> points;

    readCSVFile(inputFile, points);

//...

    writeCSVFile(outputFile, points);

    return 0;
}