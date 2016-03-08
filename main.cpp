#include <iostream>

#include"hash_table.h"

using namespace std;

int main()
{
    string item = "item another staff";
    string item2 = "stap civility";
    string item3 = "stap frdgvt";

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

    cout<<tab.get_keys();


    return 0;
}
