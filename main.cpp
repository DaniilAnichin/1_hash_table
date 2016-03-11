#include <iostream>

#include"hash_table.h"

using namespace std;

int main()
{
    hash_table tab(5);

    string key = "abc";
    string value = "defghigk";
    tab.add_pair(key, value);

    key = "abc";
    value = "defghigklmn";
    tab.add_pair(key, value);

    key = "abr";
    value = "defghigk";
    tab.add_pair(key, value);

    for(const string key: tab.get_keys())
        cout<<key;
//        keys_vector.push_back(key_pair.first);

    return 0;
}
