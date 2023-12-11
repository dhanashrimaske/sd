#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

// Structure to represent a data record
struct Record {
    vector<string> attributes;
    string label;
};

// Function to check if a string represents a numerical value
bool isNumerical(const string& str) {
    return all_of(str.begin(), str.end(), [](char c) {
        return isdigit(c) || c == '.' || c == '-';
    });
}

// Function to convert a string to a numerical value
double toNumerical(const string& str) {
    return stod(str);
}

// Function to calculate the entropy of a dataset
double calculateEntropy(const vector<string>& labels) {
    int total = labels.size();
    map<string, int> labelCounts;

    for (const string& label : labels) {
        labelCounts[label]++;
    }

    double entropy = 0.0;
    for (const auto& pair : labelCounts) {
        double probability = static_cast<double>(pair.second) / total;
        entropy -= probability * log2(probability);
    }

    return entropy;
}

// Function to calculate the Gini index of a dataset
double calculateGiniIndex(const vector<string>& labels) {
    int total = labels.size();
    map<string, int> labelCounts;

    for (const string& label : labels) {
        labelCounts[label]++;
    }

    double giniIndex = 1.0;
    for (const auto& pair : labelCounts) {
        double probability = static_cast<double>(pair.second) / total;
        giniIndex -= pow(probability, 2);
    }

    return giniIndex;
}

// Function to calculate the information gain for an attribute
double calculateInformationGain(const vector<Record>& dataset, int attributeIndex) {
    int totalExamples = dataset.size();
    vector<string> labels(totalExamples);

    for (int i = 0; i < totalExamples; i++) {
        labels[i] = dataset[i].label;
    }

    double entropyS = calculateEntropy(labels);

    map<string, vector<string>> attributeValues;
    for (const Record& example : dataset) {
        attributeValues[example.attributes[attributeIndex]].push_back(example.label);
    }

    double entropyAfterSplit = 0.0;
    for (const auto& pair : attributeValues) {
        vector<string> attributeLabels = pair.second;
        double probability = static_cast<double>(attributeLabels.size()) / totalExamples;
        entropyAfterSplit += probability * calculateEntropy(attributeLabels);
    }

    return entropyS - entropyAfterSplit;
}

// Function to calculate the Gini index for an attribute
double calculateGiniIndexForAttribute(const vector<Record>& dataset, int attributeIndex) {
    int totalExamples = dataset.size();
    vector<string> labels(totalExamples);

    for (int i = 0; i < totalExamples; i++) {
        labels[i] = dataset[i].label;
    }

    map<string, vector<string>> attributeValues;
    for (const Record& example : dataset) {
        attributeValues[example.attributes[attributeIndex]].push_back(example.label);
    }

    double giniIndexForAttribute = 0.0;
    for (const auto& pair : attributeValues) {
        vector<string> attributeLabels = pair.second;
        double probability = static_cast<double>(attributeLabels.size()) / totalExamples;
        giniIndexForAttribute += probability * calculateGiniIndex(attributeLabels);
    }

    return giniIndexForAttribute;
}

int main() {
    string inputFileName = "mixed_dataset.csv"; // Change to your input file name
    string informationGainOutputFileName = "information_gain_output.csv"; // Change to your information gain output file name
    string giniIndexOutputFileName = "gini_index_output.csv"; // Change to your gini index output file name

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    ofstream informationGainOutputFile(informationGainOutputFileName);
    if (!informationGainOutputFile.is_open()) {
        cerr << "Error: Unable to open information gain output file." << endl;
        return 1;
    }

    ofstream giniIndexOutputFile(giniIndexOutputFileName);
    if (!giniIndexOutputFile.is_open()) {
        cerr << "Error: Unable to open gini index output file." << endl;
        return 1;
    }

    // Storing header row (attribute names) into vector attributeNames
    string line;
    getline(inputFile, line);
    stringstream ss(line);
    vector<string> attributeNames;
    string item;
    while (getline(ss, item, ',')) {
        attributeNames.push_back(item);
    }

    vector<Record> dataset;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        Record record;
        char delimiter;

        // Assuming the format is: attribute1,attribute2,...,label
        for (int i = 0; i < attributeNames.size() - 1; i++) {
            getline(ss, item, ',');
            record.attributes.push_back(item);
        }

        getline(ss, item, ','); // read the label
        record.label = item;

        dataset.push_back(record);
    }

    if (dataset.empty()) {
        cerr << "Error: Input dataset is empty." << endl;
        return 1;
    }

    int numAttributes = attributeNames.size() - 1;

    informationGainOutputFile << "Attribute,Information Gain" << endl;
    giniIndexOutputFile << "Attribute,Gini Index" << endl;

    for (int i = 0; i < numAttributes; i++) {
        double informationGain = calculateInformationGain(dataset, i);
        double giniIndex = calculateGiniIndexForAttribute(dataset, i);

        informationGainOutputFile << attributeNames[i] << "," << fixed << setprecision(4) << informationGain << endl;
        giniIndexOutputFile << attributeNames[i] << "," << fixed << setprecision(4) << giniIndex << endl;
    }

    inputFile.close();
    informationGainOutputFile.close();
    giniIndexOutputFile.close();

    cout << "Information Gain and Gini Index calculation complete. Results saved in "
         << informationGainOutputFileName << " and " << giniIndexOutputFileName << endl;

    return 0;
}
