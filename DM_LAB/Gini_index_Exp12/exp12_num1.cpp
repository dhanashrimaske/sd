#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;

// Structure to represent a data record
struct Record {
    double value;
    string label;
};

// Function to calculate the Gini index of a dataset
double calculateGiniIndex(const vector<Record>& records) {
    int total = records.size();
    map<string, int> labelCounts;

    for (const Record& record : records) {
        labelCounts[record.label]++;
    }

    double giniIndex = 1.0;
    for (const auto& pair : labelCounts) {
        double probability = static_cast<double>(pair.second) / total;
        giniIndex -= pow(probability, 2);
    }

    return giniIndex;
}

// Function to calculate the Gini index for a numerical attribute
double calculateGiniIndexForNumericalAttribute(const vector<Record>& records, double threshold) {
    vector<Record> leftSubset, rightSubset;

    // Split records based on the threshold
    for (const Record& record : records) {
        if (record.value <= threshold) {
            leftSubset.push_back(record);
        } else {
            rightSubset.push_back(record);
        }
    }

    // Calculate Gini index for each subset
    double giniLeft = calculateGiniIndex(leftSubset);
    double giniRight = calculateGiniIndex(rightSubset);

    // Calculate the weighted sum of Gini indices
    int total = records.size();
    double weightLeft = static_cast<double>(leftSubset.size()) / total;
    double weightRight = static_cast<double>(rightSubset.size()) / total;

    return weightLeft * giniLeft + weightRight * giniRight;
}

// Function to find the best split for a numerical attribute
double findBestSplit(const vector<Record>& records) {
    // Sort records based on the attribute value
    vector<Record> sortedRecords = records;
    sort(sortedRecords.begin(), sortedRecords.end(), [](const Record& a, const Record& b) {
        return a.value < b.value;
    });

    int n = sortedRecords.size();

    double bestThreshold = sortedRecords[0].value;
    double bestGiniIndex = calculateGiniIndexForNumericalAttribute(sortedRecords, bestThreshold);

    // Iterate through possible thresholds and find the one with the lowest Gini index
    for (int i = 1; i < n; i++) {
        double threshold = (sortedRecords[i - 1].value + sortedRecords[i].value) / 2.0;
        double giniIndex = calculateGiniIndexForNumericalAttribute(sortedRecords, threshold);

        if (giniIndex < bestGiniIndex) {
            bestThreshold = threshold;
            bestGiniIndex = giniIndex;
        }
    }

    return bestThreshold;
}

int main() {
    string inputFileName = "input_num1.csv"; // Change to your input file name
    string outputFileName = "output_num1.csv"; // Change to your output file name

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    // Storing header row (attribute names) into vector attributeNames
    string line;
    getline(inputFile, line);

    vector<Record> dataset;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        Record record;
        char delimiter;

        // Assuming the format is: value,label
        ss >> record.value >> delimiter >> record.label;
        dataset.push_back(record);
    }

    if (dataset.empty()) {
        cerr << "Error: Input dataset is empty." << endl;
        return 1;
    }

    double bestThreshold = findBestSplit(dataset);

    outputFile << "Best Threshold,Gini Index" << endl;
    outputFile << fixed << setprecision(4) << bestThreshold << "," << calculateGiniIndexForNumericalAttribute(dataset, bestThreshold) << endl;

    inputFile.close();
    outputFile.close();

    cout << "Gini Index calculation complete. Result saved in " << outputFileName << endl;

    return 0;
}
