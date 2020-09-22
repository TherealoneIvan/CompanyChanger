#include <iostream>
#include "pugixml.hpp"
#include "Collectiv.h"
using namespace std;

int main() {
    CompanyHandler comp;
    for (;;) {
        string command;
        cin >> command;
        if (command == "load"){
            string path;
            cin >> path;
            int n = path.length();
            char char_array[n + 1];
            strcpy(char_array, path.c_str());
            comp.Load(char_array);
        }else if (command == "print"){
            comp.Print();
        }else if (command == "add"){
            Worker new_worker;
            cin >> new_worker;
            comp.Add(new_worker);
        } else if (command == "save"){
            comp.Save();
        }else if (command == "back"){
            comp.Back();
        } else if (command == "cancel"){
            comp.Cancel();
        } else if (command == "exit"){
            break;
        } else if (command == "delete"){
            Worker new_worker;
            cin >> new_worker;
            comp.Delete(new_worker);
        }else if (command == "save-xml"){
            string path;
            cin >> path;
            comp.SaveInXML(path);
        }
//        comp.Load("/Users/macos/Desktop/tst1.xml");
//        comp.Print();
    }
    return 0;
}
