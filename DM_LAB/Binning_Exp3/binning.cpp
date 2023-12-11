/*
Que. Perform binning on data: Equi-frequency and Equi-width Binning
*/

#include<bits/stdc++.h>
using namespace std;

// Function to read data from CSV file
vector<double> readCSV(const string& filename) {
    vector<double> data;
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            data.push_back(stod(value));
        }
    }

    file.close();
    return data;
}

// Function to perform Equi-width binning
vector<vector<double>> equiWidthBinning(const vector<double>& data, int numBins) {
    vector<vector<double>> result(numBins);

    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());
    double binWidth = (maxVal - minVal) / numBins;

    for (double value : data) {
        int binIndex = min(static_cast<int>((value - minVal) / binWidth), numBins - 1);
        result[binIndex].push_back(value);
    }

    return result;
}

// Function to perform Equi-frequency binning
vector<vector<double>> equiFrequencyBinning(const vector<double>& data, int numBins) {
    vector<vector<double>> result(numBins);

    int dataSize = data.size();
    int itemsPerBin = dataSize / numBins;
    int remainder = dataSize % numBins;

    int currentIndex = 0;
    for (int i = 0; i < numBins; ++i) {
        int binSize = itemsPerBin + (i < remainder ? 1 : 0);

        for (int j = 0; j < binSize; ++j) {
            result[i].push_back(data[currentIndex++]);
        }
    }

    return result;
}

// Function to write data to CSV file with specified format
void writeCSV(const vector<vector<double>>& bins, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < bins.size(); ++i) {
        file << "Bin No " << i + 1 << ":";
        for (size_t j = 0; j < bins[i].size(); ++j) {
            file << bins[i][j];
            if (j < bins[i].size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

int main() {
    string inputFileName = "input.csv"; // Replace with your input CSV file name
    string equiWidthOutputFileName = "equiWidthOutput.csv";
    string equiFrequencyOutputFileName = "equiFrequencyOutput.csv";

    int numBins;
    cout << "Enter the number of bins: ";
    cin >> numBins;

    // Read data from CSV file
    vector<double> inputData = readCSV(inputFileName);

    // sorting the inputdata in the vector (required for binning)
    sort(inputData.begin(),inputData.end());

    // Perform Equi-width binning
    vector<vector<double>> equiWidthBins = equiWidthBinning(inputData, numBins);

    // Perform Equi-frequency binning
    vector<vector<double>> equiFrequencyBins = equiFrequencyBinning(inputData, numBins);

    // Write data to CSV files with specified format
    writeCSV(equiWidthBins, equiWidthOutputFileName);
    writeCSV(equiFrequencyBins, equiFrequencyOutputFileName);

    cout << "Binning process completed successfully." << endl;

    return 0;
}