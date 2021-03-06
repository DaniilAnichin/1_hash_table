// Copyright (C) 2016 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        main.cpp
// Date:        2016.03.11
// Author:      Daniil Anichin

#include <iostream>
#include <limits>

#include "hash_table.h"

using namespace std;


int start_run();

inline void alert(string reason)
{
    cout<<reason<<endl<<"Press any key to go back"<<endl;
    getch();
}


inline void get_no_empty(string& value)
{
    getline(cin, value);
    if(!value.size())
        value = "\n";
}


int main(void)
{
    int result;

    do
        result = start_run();
    while(result == -1);

    return 0;
}


int start_run()
{
    vector<string> start_menu{
                "Add a pair;",
                "Get the list of the keys;",
                "Get the value from the key;",
                "Get the list of the pairs;",
                "Change pair;",
                "Delete pair;",
                "Delete table;",
                "Exit program;"
    };

    int incorrect_choice = 1;
    int exit = 0;

    int hash_size = 0;
    cout<<"Input the size of the hash table to work with:"<<endl;
    cin>>hash_size;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(hash_size <= 0)
    {
        cout<<"This size is too small, I'll set 16;"<<endl;
        hash_size = 16;
    }
    else if(hash_size > 65536)
    {
        cout<<"This size is too huge, I'll set 65536;"<<endl;
        hash_size = 65536;
    }
    else
        cout<<"Success;"<<endl;

    kb_wait();

    hash_table table(hash_size);

    do
    {
        incorrect_choice = 1;

        clear_screen();
        string nums("12345678");
        for(unsigned int i = 0; i < nums.length(); ++i)
            cout<<"("<<i+1<<"): "<<start_menu.at(i)<<endl;

        cout<<"Input the number of menu item:"<<endl;

        char menu_symbol;
        while(incorrect_choice)
        {
            menu_symbol = getch();
            if(nums.find(menu_symbol) == string::npos)
                cout<<"Unknown: "<<menu_symbol<<"; repeat the choice"<<endl;
            else
                incorrect_choice = 0;
        }

        switch(menu_symbol)
        {
        case '1':
        {
            cout<<"Input the key:"<<endl;
            string key_to_add;
            get_no_empty(key_to_add);
            if(key_to_add.size())
                key_to_add = "\n";
            cin.sync();

            cout<<"Input the value:"<<endl;
            string value_to_add;
            get_no_empty(value_to_add);
            cin.sync();

            cout<<table.add_pair(key_to_add, value_to_add)<<endl;

            kb_wait();
        }
            break;
        case '2':
        {
            cout<<"Hash keys are:"<<endl;
            for(const string key: table.get_keys())
                cout<<key<<endl;
            kb_wait();
        }
            break;
        case '3':
        {
            cout<<"Input the key:"<<endl;
            string key_to_get;
            get_no_empty(key_to_get);
            cin.sync();

            cout<<"The value is:"<<endl<<table.get_value(key_to_get)<<endl;
            kb_wait();
        }
            break;
        case '4':
        {
            cout<<"Hash table content is:"<<endl;
            for(const string value: table.get_values())
                cout<<value<<endl;
            kb_wait();
        }
            break;
        case '5':
        {
            cout<<"Input the key:"<<endl;
            string key_to_change;
            get_no_empty(key_to_change);
            cin.sync();

            cout<<"Input the new value:"<<endl;
            string value_to_change;
            get_no_empty(value_to_change);
            cin.sync();

            cout<<table.edit_pair(key_to_change, value_to_change)<<endl;

            kb_wait();
        }
            break;
        case '6':
        {
            cout<<"Input the key:"<<endl;
            string key_to_delete;
            get_no_empty(key_to_delete);
            cin.sync();

            cout<<table.delete_pair(key_to_delete)<<endl;

            kb_wait();
        }
            break;
        case '7':
            cout<<"See you later;"<<endl; exit = -1;
            break;
        case '8':
            cout<<"Good luck;"<<endl; exit = 1;
            break;
        }
    }while(!exit);

    return exit;
}
