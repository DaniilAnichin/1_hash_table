#include "hash_table.h"

int hash_table::hash(const string& key)
{
    int hash = 0;
    string temp;

    temp = "whhltmsflha";

    for(int i=0; i < hash_table::m_hash_len; ++i)
        hash += ((temp[i] ^ key[i % key.size()]) % 10) * pow(10, i);
    return hash;
}


vector<key_value>* hash_table::get_chain(int& hash)
{
    vector<key_value>* chain = &chains.at(hash);
    return chain;
}


hash_table::hash_table(int max_size /*= 1024*/):
    m_max_size(max_size),
    m_real_size(max((int)pow(10, log10(max_size)), 1000)),
    m_hash_len((int)log10((double)this->m_real_size)),
    m_pairs_num(0)
{
    chains.reserve(m_real_size);
    key_value empty_pair("", "");
    vector<key_value> empty_chain(1, empty_pair);
    fill(chains.begin(), chains.end(), empty_pair);
}


int hash_table::add_pair(string& key, string& value)
{
    if(m_pairs_num >= m_max_size)
    {
        cout<<"Hash table is already full"<<endl;
        return 1;
    }

    int key_hash = hash(key);

    vector<key_value>* key_chain = get_chain(key_hash);
    for(const key_value old_pair: *key_chain)
    {
        if(key == old_pair.first)
        {
            cout<<"This key already exists in the table, revrite data[y/n]?";
            char choice = getche();

            switch(choice){
            case 'y':
            case 'Y':
                --m_pairs_num;
                break;
            case 'n':
            case 'N':
                return 0;
                break;
            default:
                cout<<"I'll take it like a 'no'."<<endl; return 0;
            }
        }
    }

    key_value new_pair(key, value);

    key_chain->push_back(new_pair);
    ++m_pairs_num;

    return 0;
}


string* hash_table::get_value(string& key)
{
    int key_hash = hash(key);
    vector<key_value>* key_chain = get_chain(key_hash);

    string* value = new string("");

    for(const key_value key_pair: *key_chain)
    {
        if(key_pair.first == key)
            *value = key_pair.second;
    }

    return value;
}


vector<string>* hash_table::get_keys()
{
    vector<string>* keys_vector = new vector<string>(m_pairs_num);

    for(const vector<key_value> chain: chains)
    {
        if(!chain.empty())
            for(const key_value key_pair: chain)
                keys_vector->push_back(key_pair.first);
    }

    return keys_vector;
}


vector<key_value>* hash_table::get_pairs()
{
    vector<key_value>* pairs_vector = new vector<key_value>(m_pairs_num);

    for(const vector<key_value> chain: chains)
    {
        if(!chain.empty())
            for(const key_value key_pair: chain)
                pairs_vector->push_back(key_pair);
    }

    return pairs_vector;
}


/*
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

//#include <cstring>
#include <iostream>
using namespace std;

class hash_table
{
private:
    int m_size;
    string hash(string) {}
public:
    hash_table(int m_size): m_size{m_size} {}
    ~hash_table() {}

    string get_by_hash(string hash) {}
};

#endif // HASH_TABLE_H
*/
