// Copyright (C) 2016 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        hash_table.cpp
// Date:        2016.03.11
// Author:      Daniil Anichin

#include "hash_table.h"

key_value* pair_create(string key, string value)
{
    key_value* new_pair = new key_value;
    new_pair->first=key;
    new_pair->second=value;

    return new_pair;
}


void pair_destroy(key_value* waste_pair)
{
    assert(waste_pair);

    delete waste_pair;
}

chain_link* link_create(key_value* current/* = nullptr*/)
{
    chain_link* new_link = new chain_link;

    new_link->next = nullptr;
    new_link->current =current;

    return new_link;
}


void link_destroy(chain_link* waste_chain_link)
{
    assert(waste_chain_link);

    delete waste_chain_link;
}


int hash_table::hash(const string& key)
{
    int hash = 0;
    string temp;

    temp = "whhltmsflha";

    for(int i=0; i < hash_table::m_hash_len; ++i)
        hash += ((temp[i] ^ key[i % key.size()]) % 10) * pow(10, i);
    return hash;
}


chain_link* hash_table::get_chain(const int& hash)
{
    chain_link* chain = chains[hash];
    return chain;
}


hash_table::hash_table(int max_size /*= 1024*/):
    m_max_size(max_size),
    m_real_size(max((int)pow(10, log10(max_size)), 1000)),
    m_hash_len((int)log10((double)this->m_real_size)),
    m_pairs_num(0)
{
    chain_link* empty = link_create();
    chains = new chain_link*[m_real_size];
    for(int i=0; i < m_real_size; ++i)
        chains[i] = empty;
}


hash_table::~hash_table()
{
    delete[] chains;
}


int hash_table::add_pair(const string& key, const string& value)
{
    if(m_pairs_num >= m_max_size)
    {
        cout<<"Hash table is already full"<<endl;
        return 1;
    }

    int key_hash = hash(key);

    chain_link* key_chain = get_chain(key_hash);

    if(key_chain->current == nullptr)
    {
        key_value* new_pair = pair_create(key, value);

        chain_link* new_link = link_create(new_pair);
        chains[key_hash] = new_link;
    }
    else
    {
        while(key_chain->next != nullptr)
        {
            if(key == key_chain->current->first)
            {
                cin.ignore();
                cout<<"This key already exists in the table, revrite data[y/n]?";
                char choice = getche();

                switch(choice){
                case 'y':
                case 'Y':
                    key_chain->current->second = value; return 0;
                    break;
                case 'n':
                case 'N':
                    return 0;
                    break;
                default:
                    cout<<"I'll take it like a 'no'."<<endl; return 0;
                }
            }

            key_chain = key_chain->next;
        }

        key_value* new_pair = pair_create(key, value);

        chain_link* new_link = link_create(new_pair);
        key_chain->next = new_link;
    }
    ++m_pairs_num;

    return 0;
}


string hash_table::edit_pair(const string& key, const string& value)
{
    chain_link* key_chain = get_chain(hash(key));

    bool found = false;


//    for(key_value& key_pair: *key_chain)
    if(key_chain->current != nullptr)
        while(key_chain->next != nullptr)
        {
            if(key_chain->current->first == key)
                key_chain->current->second = value; found = true;
            key_chain = key_chain->next;
        }

    string result = (found == false ? "Key is not found;" : "");

    return result;
}


string hash_table::delete_pair(const string& key)
{
    chain_link* key_chain = get_chain(hash(key));

    bool found = false;

    if(key_chain->current != nullptr)
        while(key_chain->next != nullptr)
        {
            if(key_chain->current->first == key)
            {
                link_destroy(key_chain->next);
                key_chain->next = key_chain->next->next;found = true;
            }
            key_chain = key_chain->next;
        }

    string result = (found == false ? "Key is not found;" : "");

    return result;
}


string hash_table::get_value(const string& key)
{
    chain_link* key_chain = get_chain(hash(key));

    string value = "";
    bool found = false;

    if(key_chain->current != nullptr)
        while(key_chain->next != nullptr)
        {
            if(key_chain->current->first == key)
                value = key_chain->current->second;found = true;
            key_chain = key_chain->next;
        }

    if(found == false)
        value = "Key is not found;";

    return value;
}


vector<string> hash_table::get_keys()
{
    vector<string> keys_vector;

    for(int i=0; i < m_real_size; ++i)
    {
        chain_link* key_chain = chains[i];
        if(key_chain->current != nullptr)
            do
            {
                keys_vector.push_back(chains[i]->current->first);
                key_chain = key_chain->next;
            } while(key_chain->next != nullptr);
    }

    return keys_vector;
}


vector<string> hash_table::get_values()
{
    vector<string> values_vector;

    for(int i=0; i < m_real_size; ++i)
    {
        chain_link* key_chain = chains[i];
        if(key_chain->current != nullptr)
            while(key_chain->next != nullptr)
            {
                values_vector.push_back(chains[i]->current->second);
                key_chain = key_chain->next;
            }
    }

    return values_vector;
}

