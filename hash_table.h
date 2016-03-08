#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

#include "my_conio.h"


using namespace std;

typedef pair<string, string> key_value;


class hash_table
{
public:
    hash_table(int max_size = 1024);
//    ~hash_table();

    int add_pair(const string& key, const string& value);
    string* get_value(string& key);
    vector<string>* get_keys();
    vector<key_value>* get_pairs();

private:
    int m_max_size;
    int m_real_size;
    int m_hash_len;
    int m_pairs_num;

    vector<vector<key_value> > chains;

    int hash(const string& key);
    vector<key_value>* get_chain(int& hash);
};

#endif // HASH_TABLE_H
