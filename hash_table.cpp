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


unsigned int hash_table::hash(const string& key)
{
    unsigned int hash = 0;

    for(unsigned int i=0; i < hash_table::m_hash_len; ++i)
        hash += ((key[i % key.size()] ^ (key[i % key.size()] >> 4))\
                & (char)15)<<(4 * i);
    return hash;
}


hash_table::hash_table(unsigned int max_size/* = 256*/):
    m_max_size(max_size),
    m_hash_len(get_hash_len(max_size - 1)),
    m_real_size(1 << (4 * m_hash_len)),
    m_pairs_num(0),
    empty(link_create())
{
    chains = new chain_link*[m_real_size];
    for(unsigned int i=0; i < m_real_size; ++i)
        chains[i] = empty;
}


hash_table::~hash_table()
{
    for(unsigned int i=0; i < m_real_size; ++i)
    {
        chain_link* key_chain = chains[i];
        while(key_chain->current != nullptr)
        {
            if(key_chain->next != nullptr)
            {
                chain_link* next_link = key_chain->next;
                link_destroy(key_chain);
                key_chain = next_link;
            }
            else if(key_chain != empty)
            {
                link_destroy(key_chain);
                break;
            }
        }
    }

    link_destroy(empty);

    delete[] chains;
}


string hash_table::add_pair(const string& key, const string& value)
{
    bool conflict = false;

    if(m_pairs_num >= m_max_size)
    {
        return "Hash table is already full;";
    }

    chain_link* key_chain = chains[hash(key)];

    if(key_chain->current == nullptr)
    {
        key_value* new_pair = pair_create(key, value);
        chain_link* new_link = link_create(new_pair);

        chains[hash(key)] = new_link;
        ++m_pairs_num;
    }
    else
    {
        while(key_chain->current != nullptr)
        {
            if(key == key_chain->current->first)
            {
                cout<<"This key already exists in the table, revrite data[y/n]?";
                char choice = getche();

                switch(choice){
                case 'y':
                case 'Y':
                    key_chain->current->second = value;
                    break;
                case 'n':
                case 'N':
                    break;
                default:
                    cout<<"I'll take it like a 'no'."<<endl;
                }
                conflict = true;
            }
            if(key_chain->next != nullptr)
                key_chain = key_chain->next;
            else
                break;
        }

        if(!conflict)
        {
            key_value* new_pair = pair_create(key, value);
            chain_link* new_link = link_create(new_pair);

            key_chain->next = new_link;
            ++m_pairs_num;
        }
    }

    return "Success;";
}


string hash_table::edit_pair(const string& key, const string& value)
{
    chain_link* key_chain = chains[hash(key)];

    bool found = false;

    while(key_chain->current != nullptr)
    {
        if(key_chain->current->first == key)
        {
            key_chain->current->second = value;
            found = true;
        }
        if(key_chain->next != nullptr)
            key_chain = key_chain->next;
        else

            break;
    }

    string result = (found == false ? "Key is not found;" : "Success;");

    return result;
}


string hash_table::delete_pair(const string& key)
{
    chain_link* key_chain = chains[hash(key)];

    bool found = false;

    if(key_chain != empty && key_chain->current->first == key)
    {
        chains[hash(key)] = (key_chain->next == nullptr ? empty : key_chain->next);
        link_destroy(key_chain);
        --m_pairs_num;
        found = true;
    }
    else
    while(key_chain->next != nullptr)
    {
        if(key_chain->next->current->first == key)
        {
            chain_link* next_link = key_chain->next->next;
            link_destroy(key_chain->next);
            key_chain->next = next_link;
            --m_pairs_num;
            found = true;
            break;
        }

        key_chain = key_chain->next;
    }

    string result = (found ? "Success;" : "Key is not found;");

    return result;
}


string hash_table::get_value(const string& key)
{
    chain_link* key_chain = chains[hash(key)];

    string value = "";
    bool found = false;

    while(key_chain->current != nullptr)
    {
        if(key_chain->current->first == key)
        {
            value = key_chain->current->second;
            found = true;
        }

        if(key_chain->next != nullptr)
            key_chain = key_chain->next;
        else
            break;
    }

    if(found == false)
        value = "Key is not found;";

    return value;
}


vector<string> hash_table::get_keys()
{
    vector<string> keys_vector;

    for(unsigned int i=0; i < m_real_size; ++i)
    {
        chain_link* key_chain = chains[i];
        while(key_chain->current != nullptr)
        {
            keys_vector.push_back(key_chain->current->first);
            if(key_chain->next != nullptr)
                key_chain = key_chain->next;
            else
                break;
        }
    }

    return keys_vector;
}


vector<string> hash_table::get_values()
{
    vector<string> values_vector;

    for(unsigned int i=0; i < m_real_size; ++i)
    {
        chain_link* key_chain = chains[i];
        while(key_chain->current != nullptr)
        {
            values_vector.push_back(chains[i]->current->second);
            if(key_chain->next != nullptr)
                key_chain = key_chain->next;
            else
                break;
        }
    }

    return values_vector;
}

