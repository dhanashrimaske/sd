#include<iostream>
#include<fstream>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<vector>
#include<ostream>
using namespace std;


vector<double> readDataFromCSV(const string &filename)
{
    vector<double> data;
    ifstream file(filename);

    if(!file.is_open())
    {
        cerr<<"Unable to open file "<<filename;
        exit(1);
    }

    string line ;
    while(getline(file, line))
    {
        stringstream ss(line);
        string token;
        while(getline(ss, token, ','))
        {
            data.push_back(stod(token));
        }
    }

    file.close();
    return data;
}

void z_sore_normalization(vector<double> & data)
{
    double sum = 0.0;
    double mean = 0.0;
    for(int i=0;i<data.size();i++)
    {
        sum = sum + data[i];
    }

    mean = sum / data.size();
    
    double variance = 0.0;
    for(int i=0;i<data.size();i++)
    {
        variance = variance + pow(data[i]-mean,2);
    }

    variance = sqrt(variance/data.size());
    for(double &value: data)
    {
        value = (value - mean) / variance; 
    }

    // double mean = 0.0;
    // for (const double &value : data) {
    //     mean += value;
    // }
    // mean /= data.size();     // calculating mean

    // double variance = 0.0; 
    // for (const double &value : data) {
    //     variance += pow(value - mean, 2);
    // }
    // variance = sqrt(variance / (data.size()));    // calculating standard deviation

    // for (double &value : data) {
    //     value = (value - mean) / variance;
    // }
}


void writeDataFromCSV(string &outputfile ,vector<double> &data)
{
    ofstream file(outputfile);
    if(!file.is_open())
    {
        cerr<<"Unable to open file "<<outputfile;
        exit(1);
    }

    for(size_t i=0;i<data.size();i++)
    {
        file<<data[i]<<endl;
    }

    file.close();
}

int main()
{
    string inputFile = "input.csv";
    string outputFile = "output(z_score).csv";

    vector<double> data = readDataFromCSV(inputFile); 

    vector<double> ZSoreNormalizationData = data;
    z_sore_normalization(ZSoreNormalizationData);
    writeDataFromCSV(outputFile, ZSoreNormalizationData);

    cout<<"The output of normalization is in "<<outputFile<<endl;

    return 0;
}
