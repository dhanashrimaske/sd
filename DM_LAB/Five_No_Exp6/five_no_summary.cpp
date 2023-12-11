
#include<bits/stdc++.h>
using namespace std;

// Function to read data from a file
vector<double> readDataFromFile(const string& file_path) {
    ifstream file(file_path);
    vector<double> data;
    // double value;
    // while (file >> value) {
    //     data.push_back(value);
    // }

    // if (data.empty()) {
    //     cerr << "Failed to read data from the input file." << endl;
    //     exit(1);
    // }

    // return data;

    
    if(!file.is_open())
    {
        cerr<<"Error: unable to open file "<<file_path;
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

float calculateMedian(vector<double> data)
{
    int size = data.size();
    if (size % 2 == 1)
        return data[size / 2];
    else
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;
}

// Function to calculate the first quartile (Q1)
float calculateQ1(vector<double> data)
{
    int n = data.size();
    vector<double> first(data.begin(), data.begin() + n / 2);
    return calculateMedian(first);
}

// Function to calculate the third quartile (Q3)
float calculateQ3(vector<double> data)
{
    int n = data.size();
    vector<double> last(data.begin() + (n + 1) / 2, data.end());
    return calculateMedian(last);
}
        
        

// Function to write the five-number summary to a file
void writeSummaryToFile(const string& output_file, double min, double q1, double median, double q3, double max,double IQR, double lw, double uw,vector<double> &data) {
    ofstream file(output_file);
    if (file.is_open()) {

        file <<"Min:"<< min <<endl <<"Q1: "<<q1<<endl<<"Median: "<< median <<endl<<"Q3: "<< q3 <<endl<<"Max: "<< max << "\n";
        file<<"Intern quartile range: "<<IQR<<endl<<"Lower Whisker: "<<lw<<endl<<"Upper Whisker: "<<uw<<endl;
        

        file<<"Numbers within the lower whisker: "<<endl;
        for(double val: data)
        {
            if(val >= lw && val <= q1)
            {
                file<<val<<" ";
            }
        }

        file<<"\nNumbers within the upper whisker: "<<endl;
        for(double val: data)
        {
            if(val >= q3 && val <= uw)
            {
                file<<val<<" ";
            }
        }

        file.close();
        cout << "\nFive-number summary written to " << output_file << endl;
    } else {
        cerr << "Unable to open the output file for writing." << endl;
    }
}

int main() {
    const string input_file = "input.csv";  
    const string output_file = "output.csv";  

    vector<double> data = readDataFromFile(input_file);
    // if (data.empty()) {
    //     cerr << "Failed to read data from the input file." << endl;
    //     return 1;
    // }

    sort(data.begin(), data.end());
    int n = data.size();

    double min = data[0];
    double max = data[n-1];

     double q1 = calculateQ1(data);
     double median = calculateMedian(data);
    double q3 = calculateQ3(data);
    double IQR = q3-q1;
    double lw = q1 - 1.5*(IQR);
    double uw = q3 + 1.5*(IQR);
    writeSummaryToFile(output_file, min, q1, median, q3, max,IQR,lw,uw,data);

    return 0;
}
