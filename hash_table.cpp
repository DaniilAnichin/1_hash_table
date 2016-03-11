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


vector<key_value> hash_table::get_chain(const int& hash)
{
    vector<key_value> chain = chains[hash];
    return chain;
}


hash_table::hash_table(int max_size /*= 1024*/):
    m_max_size(max_size),
    m_real_size(max((int)pow(10, log10(max_size)), 1000)),
    m_hash_len((int)log10((double)this->m_real_size)),
    m_pairs_num(0)
{
    chains = new vector<key_value>[m_real_size];
}


int hash_table::add_pair(const string& key, const string& value)
{
    if(m_pairs_num >= m_max_size)
    {
        cout<<"Hash table is already full"<<endl;
        return 1;
    }

    int key_hash = hash(key);

    vector<key_value> key_chain = get_chain(key_hash);
    for(const key_value old_pair: key_chain)
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

    key_chain.push_back(new_pair);
    ++m_pairs_num;

    return 0;
}


string hash_table::get_value(const string& key)
{
    int key_hash = hash(key);
    vector<key_value> key_chain = get_chain(key_hash);

    string value = "";

    for(const key_value key_pair: key_chain)
    {
        if(key_pair.first == key)
            value = key_pair.second;
    }

    return value;
}


vector<string> hash_table::get_keys()
{
    vector<string> keys_vector;

    for(int i=0; i < m_real_size; ++i)
        if(!chains[i].empty())
            for(const key_value key_pair: chains[i])
                keys_vector.push_back(key_pair.first);
        else
            cout<<1;

    return keys_vector;
}


vector<key_value> hash_table::get_pairs()
{
    vector<key_value> pairs_vector;

    for(int i=0; i < m_real_size; ++i)
        if(!chains[i].empty())
            for(const key_value key_pair: chains[i])
                pairs_vector.push_back(key_pair);

    return pairs_vector;
}
