/*
Que. Find 5 no. summary of data.
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;

// Function to calculate the median of a vector
float calculateMedian(vector<int> a)
{
    int size = a.size();
    if (size % 2 == 1)
        return a[size / 2];
    else
        return (a[size / 2 - 1] + a[size / 2]) / 2.0;
}

// Function to calculate the first quartile (Q1)
float calculateQuartile1(vector<int> v)
{
    int n = v.size();
    vector<int> first(v.begin(), v.begin() + n / 2);
    return calculateMedian(first);
}

// Function to calculate the third quartile (Q3)
float calculateQuartile3(vector<int> v)
{
    int n = v.size();
    vector<int> last(v.begin() + (n + 1) / 2, v.end());
    return calculateMedian(last);
}

int main()
{
    ifstream in("input.csv");
    if (!in.is_open())
    {
        cout << "Error: Unable to open the input file." << endl;
        return 1;
    }

    int i = 0;
    string line, mark;
    vector<int> arr;   // used to store input from the file

    // Read data from the input file
    while (getline(in, line))
    {
        stringstream str(line);

        getline(str, mark, ',');
        int x = stoi(mark);
        arr.push_back(x);
    }

    int n = arr.size();
    sort(arr.begin(), arr.end());

    double q1 = calculateQuartile1(arr);
    double q3 = calculateQuartile3(arr);
    double IQR = q3 - q1;
    double lowerWhisker = q1-1.5*IQR;
    double upperWhisker = q3+1.5*IQR;

    ofstream out("output.csv");
    // Write results to the output file and console
    out << "Minimum value: " << arr[0] << "\n";
    out << "First Quartile (Q1) value: " << calculateQuartile1(arr) << "\n";
    out << "Median value: " << calculateMedian(arr) << "\n";
    out << "Third Quartile (Q3) value: " << calculateQuartile3(arr) << "\n";
    out << "Maximum value: " << arr[n - 1] << "\n";
    out << "\n";
    out << "Inter Quartile Range: " << IQR << "\n";
    out << "Information about Whiskers: " << "\n";
    out << "Lower Whisker: " << lowerWhisker << "\n";
    out << "Upper Whisker: " << upperWhisker << "\n";
    int cnt = 0;
   
    out << "\nElements between lowerWhisker and q1: ";
    for (double val : arr)
    {
        if (val >= lowerWhisker && val <= q1)
        {
            out << val << " ";
            cnt ++;
        }
    }
     out << "\nNo. of elements in the lowerWhisker: " << cnt << "\n";
    cnt = 0;
    out << "\nElements between q3 and upperWhisker: ";
    for (double val : arr)
    {
        if (val >= q3 && val <= upperWhisker)
        {
            out << val << " ";
            cnt ++;
        }
    }
    out << "\nNo. of elements in the upperWhisker: " << cnt << "\n";
    /*
    cout << "The minimum value is " << arr[0] << endl;
    cout << "The First Quartile (Q1) is " << calculateQuartile1(arr) << endl;
    cout << "The median is " << calculateMedian(arr) << endl;
    cout << "The Third Quartile (Q3) is " << calculateQuartile3(arr) << endl;
    cout << "The maximum value is " << arr[n - 1] << endl;
    */

    return 0;
}
