#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<cmath>
#include<algorithm>
using namespace std;

// Function to read numbers from a CSV file
vector<double> readDataFromCSV(const string& filename) 
{
    vector<double> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            data.push_back(stod(token));
        }
    }

    file.close();
    return data;
}

// Function to write numbers to a CSV file
void writeDataToCSV(const string& filename, const vector<double>& data) 
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i]<<endl;
        // if (i < data.size() - 1) {
        //     file <<endl;
        // }
    }

    file.close();
}

// Min-Max normalization
void minMaxNormalize(vector<double>& data, double newMin, double newMax) 
{
    double oldMin = *min_element(data.begin(), data.end());   // old min
    double oldMax = *max_element(data.begin(), data.end());   // old max

    for (double &value : data) {
        value = (((value - oldMin) / (oldMax - oldMin)) * (newMax - newMin)) + newMin;
    }
}

// Z-score normalization
void zScoreNormalize(vector<double>& data) 
{
    double mean = 0.0;
    for (const double &value : data) {
        mean += value;
    }
    mean /= data.size();     // calculating mean

    double variance = 0.0; 
    for (const double &value : data) {
        variance += pow(value - mean, 2);
    }
    variance = sqrt(variance / (data.size()));    // calculating standard deviation

    for (double &value : data) {
        value = (value - mean) / variance;
    }
}

int main() 
{
    string inputFileName = "input.csv";
    string outputFileNameMinMax = "output_minmax.csv";
    string outputFileNameZScore = "output_zscore.csv";

    vector<double> data = readDataFromCSV(inputFileName);

    // Taking new min and max value for the normalised data
    double min_new, max_new;
    cout<<"Enter newMin value for data: "<<endl;
    cin>>min_new;
    cout<<"Enter newMax value for data: "<<endl;
    cin>>max_new;

    // Min-Max normalization
    vector<double> minMaxNormalizedData = data;
    minMaxNormalize(minMaxNormalizedData, min_new, max_new);
    writeDataToCSV(outputFileNameMinMax, minMaxNormalizedData);

    // Z-score normalization
    vector<double> zScoreNormalizedData = data;
    zScoreNormalize(zScoreNormalizedData);
    writeDataToCSV(outputFileNameZScore, zScoreNormalizedData);

    cout << "Data has been normalized and saved to output files." << endl;

    return 0;
}