#include<bits/stdc++.h>
using namespace std;
vector<vector<string>> readData(const string &filename)
{
vector<vector<string>> data;
fstream file(filename, ios::in);
if (!file.is_open())
{
cerr << "Error in opening input file: " << filename << endl;
exit(1);
}
string line;
// Read the header line to determine the column names
getline(file, line);
stringstream headerStream(line);
vector<string> columnNames;
// Split the header line into column names
while (getline(headerStream, line, ','))
{
columnNames.push_back(line);
}
// Initialize the data vector
data.push_back(columnNames);
while (getline(file, line))
{
stringstream ss(line);
vector<string> rowData;
while (getline(ss, line, ','))
{
rowData.push_back(line);
}
data.push_back(rowData);
}
file.close();
return data;
}
float calCoef(const vector<vector<string>> &data, const string &columnA, const string
&columnB)
{
int n = data.size() - 1; // Number of data rows (excluding header)
int sumA = 0, sumB = 0, sumAB = 0;
int sumA2 = 0, sumB2 = 0;
int columnAIndex = -1, columnBIndex = -1;
// Find the indices of the specified columns in the header
for (size_t i = 0; i < data[0].size(); i++)
{
if (data[0][i] == columnA)
{
columnAIndex = i;
}
if (data[0][i] == columnB)
{
columnBIndex = i;
}
}
if (columnAIndex == -1 || columnBIndex == -1)
{
cerr << "Error: Specified columns not found in the header." << endl;
exit(1);
}
for (int i = 1; i <= n; i++)
{
int valA = (data[i][columnAIndex] == "Y") ? 1 : 0;
int valB = (data[i][columnBIndex] == "Y") ? 1 : 0;
sumA += valA;
sumB += valB;
sumAB += valA * valB;
sumA2 += valA * valA;
sumB2 += valB * valB;
}
float numerator = n * sumAB - sumA * sumB;
float denominatorA = n * sumA2 - sumA * sumA;
float denominatorB = n * sumB2 - sumB * sumB;
if (denominatorA == 0 || denominatorB == 0)
{
return 0.0; // To handle cases where division by zero may occur
}
return numerator / sqrt(denominatorA * denominatorB);
}
void writeCoef(const string &filename, float corr_coeff)
{
ofstream file(filename, ios::out);
if (!file.is_open())
{
cerr << "Error in opening output file: " << filename << endl;
exit(1);
}
file << "Pearson Correlation Coefficient"
<< "," << corr_coeff << endl;
file.close();
}
int main()
{
string inputFileName = "correlation_input.csv";
string outputFileName = "output.csv";
vector<vector<string>> data = readData(inputFileName);
float corr_coeff = calCoef(data, "Tue", "Wed");
writeCoef(outputFileName, corr_coeff);
cout << "Correlation coefficient calculated and saved in '" << outputFileName << "'." <<
endl;
return 0;
}