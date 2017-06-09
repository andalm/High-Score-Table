#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

 struct top_table {
    vector<int> position;
    vector<string> names;
    vector<long> scores;
};

void parse(ifstream &input_file, vector<top_table> &cases)
{
    string line;
    smatch score_table_matches;
    top_table *current_case;

    if (getline(input_file, line))
    {
        if (regex_match(line, regex("^\\d{1}$")))
        {
            cases.reserve(stoi(line));
        }

        if (regex_search(line, score_table_matches, regex("^(\\d{1})\\s(\\d{1})$")) && cases.size() < cases.capacity())
        {
            cases.push_back(top_table());
            current_case = &cases.back();
            current_case->names.reserve(stoi(score_table_matches[2]));
            current_case->scores.reserve(stoi(score_table_matches[2]));
        }


        if (regex_search(line, score_table_matches, regex("^(\\w{3})\\s(\\d+)$")))
        {
            current_case = &cases.back();
            if (current_case->names.size() < current_case->names.capacity())
            {
                current_case->names.push_back(score_table_matches[1]);
                current_case->scores.push_back(stol(score_table_matches[2]));
            }
        }
        parse(input_file, cases);
    }
}

int main()
{
    vector<top_table> cases;
    ifstream input_file("input.in");
    if (input_file.is_open())
    {
        parse(input_file, cases);
        input_file.close();
        for(uint it = 0; it < cases.size(); ++it) {
            cout << cases[it].names[0] << endl;
        }
    }
    return 0;
}
