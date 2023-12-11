/*
Que. Find t and d weight of a data.
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
using namespace std;

// to represent the particular column data in csv file
struct CellData
{
    int count;
    int tWeight;
    int dWeight;
};

// reading input from csv file and updating corresponding data structures
void readData(const string &filename, map<string, map<string, CellData>> &cellData,
              map<string, int> &columnTotal, map<string, int> &rowTotal)
{
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Couldn't open file: " << filename << endl;
        return;
    }

    string line, row, col, count;
    int val;

    int lineNumber = 0;

    while (getline(file, line))
    {
        stringstream str(line);

        if (lineNumber == 0)
        {
            lineNumber++;
            continue; // Skip the header line
        }

        getline(str, row, ',');
        getline(str, col, ',');
        getline(str, count, ',');

        val = stoi(count);

        cellData[row][col].count += val;
        columnTotal[col] += val;
        rowTotal[row] += val;
    }
}

// calculating and writing the result to output CSV file
void writeResult(const string &filename, const map<string, map<string, CellData>> &cellData,
                 const map<string, int> &columnTotal, const map<string, int> &rowTotal)
{
    // calculate final total for both row or column (which is same)
    // useful for calculating t-wt for Total and d-wt for last total row
    int finalTotal = 0;
    for(const auto val : rowTotal)
    {
        finalTotal = finalTotal + val.second;
    }

    ofstream fw(filename, ios::out);  // open the file in write mode
    
    fw << "Column\\Row, Cnt, T-wt, D-wt, Cnt, T-wt, D-wt, Cnt, T-wt, D-wt" << endl;

    for (const auto &rowEntry : rowTotal)
    {
        const string &row = rowEntry.first;
        fw << row << ",";

        for (const auto &colEntry : columnTotal)
        {
            const string &col = colEntry.first;
            const CellData &cell = cellData.at(row).at(col);

            fw << cell.count << ",";
            fw << ((float)cell.count / rowTotal.at(row)) * 100 << "%,";   // t_wt
            fw << ((float)cell.count / colEntry.second) * 100 << "%,";    // d_wt
        }

        fw << rowTotal.at(row) << ","
           << "100%," << ((float)rowTotal.at(row) / finalTotal) * 100 << "%" << endl;
    }
    // rowTotal.at(rowTotal.begin()->first)

    fw << "Total,";

    for (const auto &colEntry : columnTotal)
    {
        fw << colEntry.second << ",";
        fw << ((float)colEntry.second / finalTotal) * 100 << "%,";
        fw << "100%,";
    }

    fw << finalTotal << ",100%, 100%" << endl;
}

int main()
{
    map<string, map<string, CellData>> cellData;
    map<string, int> columnTotal;
    map<string, int> rowTotal;

    readData("input.csv", cellData, columnTotal, rowTotal);
    writeResult("output.csv", cellData, columnTotal, rowTotal);

    cout << "Processing complete. Results saved to 'output.csv'." << endl;

    return 0;
}