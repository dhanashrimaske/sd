
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// Function to calculate the Pearson correlation coefficient
double calculatePearsonCoefficient(const vector<double>& x, const vector<double>& y) {
    if (x.size() != y.size()) {
        cerr << "Error: Data sizes do not match" << endl;
        return 0.0;
    }

    int n = x.size();

    // Calculate the means
    double meanX = 0.0;
    double meanY = 0.0;
    for (int i = 0; i < n; i++) {
        meanX += x[i];
        meanY += y[i];
    }
    meanX /= n;
    meanY /= n;

    // Calculate the Pearson correlation coefficient
    double numerator = 0.0;
    double denominatorX = 0.0;
    double denominatorY = 0.0;

    for (int i = 0; i < n; i++) {
        numerator += (x[i] - meanX) * (y[i] - meanY);
        denominatorX += pow(x[i] - meanX, 2);
        denominatorY += pow(y[i] - meanY, 2);
    }

    // Check for division by zero
    if (denominatorX == 0.0 || denominatorY == 0.0) {
        return 0.0;
    }

    double correlation = numerator / (sqrt(denominatorX) * sqrt(denominatorY));

    return correlation;
}

int main() {
    string inputFileName = "input.csv";
    string outputFileName = "correlation_output.csv";

    vector<double> hoursOfStudy;
    vector<double> examScores;

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string token;
        getline(ss, token, ',');
        try {
            hoursOfStudy.push_back(stod(token));
        } catch (invalid_argument& e) {
            continue;
        }

        getline(ss, token, ',');
        try {
            examScores.push_back(stod(token));
        } catch (invalid_argument& e) {
            cerr << "Error parsing exam score: " << e.what() << endl;
            continue;
        }
    }
    inputFile.close();

    double correlation = calculatePearsonCoefficient(hoursOfStudy, examScores);

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cout << "Error: Unable to open output file." << endl;
        return 1;
    }

    outputFile << "Pearson Correlation Coefficient" << endl;
    outputFile << correlation << endl;
    outputFile.close();

    cout << "Pearson Correlation Coefficient: " << correlation << endl;
    cout << "Result written to " << outputFileName << endl;

    return 0;
}