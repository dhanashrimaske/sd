/*
Que. Calculate information gain for attribute given in the data.
*/

#include<bits/stdc++.h>
using namespace std;

// Function to calculate the entropy of a dataset
double calculateEntropy(const vector<string>& labels) 
{
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

// Function to calculate the information gain for an attribute
double calculateInformationGain(const vector<vector<string>>& dataset, int attributeIndex) 
{
    int totalExamples = dataset.size();
    vector<string> labels(totalExamples);

    for (int i = 0; i < totalExamples; i++) {
        labels[i] = dataset[i][dataset[i].size() - 1];
    }

    double entropyS = calculateEntropy(labels);

    map<string, vector<string>> attributeValues;
    for (const vector<string>& example : dataset) {
        attributeValues[example[attributeIndex]].push_back(example[example.size() - 1]);
    }

    double entropyAfterSplit = 0.0;
    for (const auto& pair : attributeValues) {
        vector<string> attributeLabels = pair.second;
        double probability = static_cast<double>(attributeLabels.size()) / totalExamples;
        entropyAfterSplit += probability * calculateEntropy(attributeLabels);
    }

    cout<<"Entropy of attributes: "<<entropyAfterSplit<<endl;
    return entropyS - entropyAfterSplit;
}

int main() 
{
    string inputFileName = "input.csv"; // Change to your input file name
    string outputFileName = "output.csv"; // Change to your output file name

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
    vector<string> attributeNames;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
        attributeNames.push_back(item);
    }

    vector<vector<string>> dataset;
    while (getline(inputFile, line)) {
        vector<string> record;
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            record.push_back(item);
        }
        dataset.push_back(record);
    }

    if (dataset.empty()) {
        cerr << "Error: Input dataset is empty." << endl;
        return 1;
    }

    int numAttributes = attributeNames.size() - 1;

    outputFile << "Attribute,Information Gain" << endl;

    for (int i = 0; i < numAttributes; i++) {
        double informationGain = calculateInformationGain(dataset, i);
        outputFile << attributeNames[i] << "," << fixed << setprecision(4) << informationGain << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Information Gain calculation complete. Results saved in " << outputFileName << endl;

    return 0;
}
