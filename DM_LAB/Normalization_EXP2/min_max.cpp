#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

vector<double> readDataFromCSV(const string &filename)
{
    vector<double> data;
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr<<"Error: Unable to open file "<<filename<<endl;
        exit(1);
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string token;

        while(getline(ss, token, ','))
            data.push_back(stod(token));
    }

    file.close();
    return data;
}

void MinMaxNormalize(vector<double> &data, double new_min, double new_max)
{
    double oldmax = *max_element(data.begin(), data.end());
    double oldmin = *min_element(data.begin(), data.end());

    for(double &value:data)
    {
        value = (((value- oldmin) / (oldmax - oldmin)) * (new_max - new_min)) + new_min;
    }
}

void WriteDataToCSV(const string &outputfile, const vector<double> &data)
{
    ofstream file(outputfile);

    if(!file.is_open())
    {
        cerr<<"Unable to open file "<<outputfile;
        exit(1);
    }

    for(size_t i=0; i< data.size();i++)
    {
        file<<data[i]<<endl;
    }

    file.close();
}


int main()
{
    string inputFile = "input.csv";
    string outputFile = "output.csv";
    
    vector<double> data = readDataFromCSV(inputFile);

    double new_min, new_max;

    cout<<"Enter value for new_min: "<<endl;
    cin>>new_min;
    cout<<"Enter value for new_max: "<<endl;
    cin>>new_max;


    //write fun for min_max_normalization
    vector<double> MinMaxNormalizationData = data;
    MinMaxNormalize(MinMaxNormalizationData, new_min, new_max);
    WriteDataToCSV(outputFile, MinMaxNormalizationData);

    cout<<"The min_max_normalization output stored in output.csv file."<<endl;

    return 0;
}
