#include<bits/stdc++.h>
#include<vector>

using namespace std;

vector<double> readFromCSV(string &inputfile)
{
    vector<double> data;
    ifstream file(inputfile);
    if(!file.is_open())
    {
        cerr<<"Error: unable to open file "<<inputfile;
        exit(1);
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string token;
        while(getline(ss,token,','))
        {
            data.push_back(stod(token));
        }
    }

    file.close();
    return data;

}

vector<vector<double>> FrequencyBinning(const vector<double> &data , int num_bins)
{

    vector<vector<double>> result(num_bins);
    int datasize = data.size();
    int itemsPerBin = datasize / num_bins;
    int remainder = datasize% num_bins;

    int index =0;
    for(int i=0;i<num_bins;i++)
    {
        int bin = itemsPerBin + (i < remainder ? 1:0);
        for(int j =0;j<bin;j++)
        {
           result[i].push_back(data[index++]);
        }
    }

    return result;
}

void writeFileToCSV(const string &outputFile ,const vector<vector<double>> &data)
{
    ofstream file(outputFile);
    if(!file.is_open())
    {
        cerr<<"Error: unable to open file "<<outputFile;
        exit(1);
    }

    for(size_t i=0; i<data.size();i++)
    {
        file<<"Bin no."<<i+1<<": ";
        for(size_t j =0;j<data[i].size();j++)
        {
            file<<data[i][j];
            if(j < data[i].size()-1)
            {
                file<<",";
            }
        }
        file<<endl;
    }

    file.close();
}

int main()
{
    string inputFile = "input.csv";
    string outputFile = "output.csv";

    vector<double> data = readFromCSV(inputFile);

    sort(data.begin() , data.end());
    int num_bins;
    cout<<"Enter number of bins: ";
    cin>>num_bins;

    //function for equalFrequency
    vector<vector<double>> FrequencyBinData = FrequencyBinning(data, num_bins);
    writeFileToCSV(outputFile , FrequencyBinData);

}