#include<bits/stdc++.h>
using namespace std;

vector<double> readFromCSV(const string &inputfile)
{
    vector<double> data;
    ifstream file(inputfile);
    if(!file.is_open())
    {
        cerr<<"Error: unable to open file "<<inputfile;
        exit(1);
    }

    string line;
    while(getline(file,line))
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

vector<vector<double>> widthBinning(const vector<double> &data, int num_bins)
{
   vector<vector<double>> result(num_bins);

   double min_val = *min_element(data.begin() , data.end());
   double max_val = *max_element(data.begin() , data.end());

    double w = (max_val - min_val)/num_bins;

   for (double value : data) {
        int binIndex = min(static_cast<int>((value - min_val) / w), num_bins- 1);
        result[binIndex].push_back(value);
    }

    return result;
}

void writeFileToCSV(const string & outputfile, const vector<vector<double>>& data)
{
   ofstream file(outputfile);
    if(!file.is_open())
    {
        cerr<<"Error: unable to open file "<<outputfile;
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
    int num_bins = 0;
    string inputFile = "input.csv";
    string outputFile = "output(width).csv";

    vector<double> data = readFromCSV(inputFile);

    sort(data.begin() , data.end());

    cout<<"Enter no. of bins: ";
    cin>>num_bins;
    vector<vector<double>> widthBinData = widthBinning(data, num_bins);
    writeFileToCSV(outputFile , widthBinData);


}