/*
Que. Find freuent itemset from the given transaction data.
*/

#include <bits/stdc++.h>
#include <map>
using namespace std;

ifstream input_file;                  // Input file stream for reading data from a file.
double minimum_frequency;                 // Minimum frequency for itemsets to be considered frequent.
vector<set<string>> transaction_data; // A vector to store transaction data.
set<string> unique_items;          // Set to store unique items in the transactions.
map<string, int> item_frequency;         // A map to store the frequency of each item.

// Function to split a string into words based on alphanumeric characters.
vector<string> get_words(string str)
{
    vector<string> tmp_set;
    string tmp = "";
    int i = 0;
    while (str[i])
    {
        if (isalnum(str[i]))
            tmp += str[i];
        else
        {
            if (tmp.size() > 0)
                tmp_set.push_back(tmp);
            tmp = "";
        }
        i++;
    }

    if (tmp.size() > 0)
        tmp_set.push_back(tmp);

    return tmp_set;
}

// Function to combine elements in a vector into a string, excluding the one at 'miss' index.
string combine_elements(vector<string> &arr, int miss)
{
    string str;
    for (int i = 0; i < arr.size(); i++)
        if (i != miss)
            str += arr[i] + " ";
    str = str.substr(0, str.size() - 1);
    return str;
}

// Function to clone a set and return a copy.
set<string> clone_set(const set<string> &arr)
{
    set<string> duplicate;
    for (const auto &item : arr)
    {
        duplicate.insert(item);
    }
    return duplicate;
}

// Function to generate frequent itemsets of size k based on candidate itemsets of size k-1.
set<string> apriori_generate(set<string> &sets, int k)
{
    set<string> set2;
    for (set<string>::iterator it1 = sets.begin(); it1 != sets.end(); it1++)
    {
        set<string>::iterator it2 = it1;
        it2++;
        for (; it2 != sets.end(); it2++)
        {
            vector<string> v1 = get_words(*it1);
            vector<string> v2 = get_words(*it2);

            bool all_equal = true;
            for (int i = 0; i < k - 1 && all_equal; i++)
                if (v1[i] != v2[i])
                    all_equal = false;

            v1.push_back(v2[k - 1]);
            if (v1[v1.size() - 1] < v1[v1.size() - 2])
                swap(v1[v1.size() - 1], v1[v1.size() - 2]);

            for (int i = 0; i < v1.size() && all_equal; i++)
            {
                string tmp = combine_elements(v1, i);
                if (sets.find(tmp) == sets.end())
                    all_equal = false;
            }

            if (all_equal)
                set2.insert(combine_elements(v1, -1));
        }
    }
    return set2;
}

int main()
{
    input_file.open("item_set_input.csv", ios::in); // Open the input file for reading.

    if (!input_file.is_open())
    {
        perror("Error in opening file : "); // Print an error message if the file cannot be opened.
    }
    cout << "Frequency % :";
    cin >> minimum_frequency; // Read the minimum frequency from the user.

    string str;
    while (!input_file.eof())
    {
        getline(input_file, str);

        vector<string> arr = get_words(str);

        set<string> tmp_set;
        for (int i = 0; i < arr.size(); i++)
            tmp_set.insert(arr[i]);
        transaction_data.push_back(tmp_set); // Store the transaction data in the 'transaction_data' vector.

        for (const auto &item : tmp_set)
        {
            unique_items.insert(item);      // Store unique items in the 'unique_items' set.
            item_frequency[item]++;          // Increment the frequency of each item in the 'item_frequency' map.
        }

    }
    input_file.close(); // Close the input file.

    cout << "No of transactions: " << transaction_data.size() << endl;
    minimum_frequency = minimum_frequency * transaction_data.size() / 100; // Calculate the minimum frequency threshold.
    cout << "Min frequency:" << minimum_frequency << endl;

    queue<set<string>::iterator> q;
    for (const auto &item : unique_items)
    {
        if (item_frequency[item] < minimum_frequency)
            q.push(unique_items.find(item));
    }

    while (!q.empty())
    {
        unique_items.erase(*q.front()); // Remove infrequent items from the 'unique_items' set.
        q.pop();
    }

    int pass = 1;
    cout << "\nFrequent " << pass++ << " -item set : \n";
    for (const auto &item : unique_items)
    {
        cout << "{" << item << "} " << item_frequency[item] << endl; // Display frequent 1-itemsets.
    }

    int i = 2;
    set<string> previous = clone_set(unique_items);

    while (i)
    {
        set<string> current = apriori_generate(previous, i - 1); // Generate candidate itemsets of size 'i'.

        if (current.empty())
        {
            break;
        }

        for (const auto &item : current)
        {
            vector<string> arr = get_words(item);

            int total = 0;
            for (int j = 0; j < transaction_data.size(); j++)
            {
                bool present = true;
                for (int k = 0; k < arr.size() && present; k++)
                    if (transaction_data[j].find(arr[k]) == transaction_data[j].end())
                        present = false;
                if (present)
                    total++;
            }
            if (total >= minimum_frequency)
                item_frequency[item] += total;
            else
                q.push(current.find(item));
        }

        while (!q.empty())
        {
            current.erase(*q.front());
            q.pop();
        }

        bool flag = true;

        for (const auto &item : current)
        {
            vector<string> arr = get_words(item);

            if (item_frequency[item] < minimum_frequency)
                flag = false;
        }

        if (current.empty())
            break;

        cout << "\n\nFrequent " << pass++ << " -item set : \n";
        for (const auto &item : current)
        {
            cout << "{" << item << "} " << item_frequency[item] << endl; // Display frequent k-itemsets.
        }

        previous = clone_set(current);
        i++;
    }

    ofstream output_file("output.csv", ios::out); // Open an output file for writing.

    for (const auto &item : previous)
    {
        output_file << "{" << item << "}" << endl; // Write frequent itemsets to the output file.
    }
    return 1;
}