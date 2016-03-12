// Copyright (C) 2016 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        hash_table.h
// Date:        2016.03.11
// Author:      Daniil Anichin

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <assert.h>

#include "my_conio.h"


using namespace std;

struct key_value
{
    string first;
    string second;
};

struct chain_link
{
    chain_link* next;
    key_value* current;
};

key_value* pair_create(string key, string value);

void pair_destroy(key_value* waste_pair);

chain_link* link_create(key_value* current = nullptr);

void link_destroy(chain_link* waste_chain_link);

class hash_table
{
public:
    hash_table(int max_size = 1024);
    ~hash_table();

    int add_pair(const string& key, const string& value);
    string edit_pair(const string& key, const string& value);
    string delete_pair(const string& key);
    string get_value(const string& key);
    vector<string> get_keys();
    vector<string> get_values();

private:
    int m_max_size;
    int m_real_size;
    int m_hash_len;
    int m_pairs_num;

    chain_link** chains;

    int hash(const string& key);
    chain_link* get_chain(const int& hash);
};

#endif // HASH_TABLE_H
