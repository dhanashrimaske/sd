/*
WAP for Baye's classsification
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// Function to split a string based on a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read the CSV file and store data in a map
map<string, vector<vector<string>>> readCSV(const string& filename) {
    ifstream file(filename);
    map<string, vector<vector<string>>> data;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> tokens = split(line, ',');
            string label = tokens.back();
            tokens.pop_back();

            vector<string> instance(tokens.begin(), tokens.end());

            data[label].push_back(instance);
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
    }

    return data;
}

// Function to calculate the probability of a value for a given attribute
double calculateProbability(const string& value, const map<string, vector<vector<string>>>& data, const string& label, int attributeIndex) {
    int count = 0;
    for (const vector<string>& instance : data.at(label)) {
        if (instance[attributeIndex] == value) {
            count++;
        }
    }
    return static_cast<double>(count) / data.at(label).size();
}

// Function to get the total number of instances in the dataset
int getTotalInstances(const map<string, vector<vector<string>>>& data) {
    int totalInstances = 0;
    for (const auto& entry : data) {
        totalInstances += entry.second.size();
    }
    return totalInstances;
}

// Function to predict the class of a new instance using Naive Bayes
string predictClass(const map<string, vector<vector<string>>>& data, const vector<string>& instance) {
    cout << "Probability for each class and attribute value:\n";
    
    string bestLabel;
    double bestProb = -1.0;

    for (const auto& entry : data) {
        const string& label = entry.first;
        const vector<vector<string>>& instances = entry.second;

        double prob = static_cast<double>(instances.size()) / getTotalInstances(data);

        for (int i = 0; i < instance.size(); ++i) {
            double attributeProb = calculateProbability(instance[i], data, label, i);
            prob *= attributeProb;

            cout << "Class: " << label << ", Attribute " << (i + 1) << " = " << instance[i] << ", Probability: " << attributeProb << "\n";
        }

        cout << "Prior Probability for Class " << label << ": " << static_cast<double>(instances.size()) / getTotalInstances(data) << "\n";
        cout << "\nOverall Probability for Class " << label << ": " << prob << "\n\n";

        if (prob > bestProb) {
            bestProb = prob;
            bestLabel = label;
        }
    }

    return bestLabel;
}

int main() {
    string filename = "input.csv";

    map<string, vector<vector<string>>> data = readCSV(filename);
    if (data.empty()) {
        return 1;
    }

    // Get input for the new instance
    vector<string> new_instance;
    cout << "Enter values for the new instance:\n";
    for (int i = 0; i < data.begin()->second[0].size(); ++i) {
        string value;
        cout << "Attribute " << (i + 1) << ": ";
        cin >> value;
        new_instance.push_back(value);
    }

    // Predict the class for the new instance
    string predictedClass = predictClass(data, new_instance);
    cout << "\nHence, Predicted class for the new instance: " << predictedClass << "\n";

    return 0;
}