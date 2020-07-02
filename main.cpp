#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "header.h"
using namespace std;



/**
@function main
Запрашивает команду, передает управление соответствующим функциям
*/
int main(int argc, char *argv[]){


    if (argc != 4){    ///Если поступило не 4 аргумента, 3 из которых пользовательских, то финиш программы
        cout << "Nujno 2 argumenta! 1 - file s mebelu, 2 - s materialami, 3 - dlya sklada\n";
        exit(0);
    }


    while (true){
        int call;
        cout << "\n1 - dobavit material\n2 - sdelat mebel i otvezti na sklad\n3 - prodat mebel\n4 - naity info o mebeli\n5 - info o materialah\n6 - Dobavit sklad\n0 - vihod\nVvedite komandu: ";

        while (cin >> call && (call < 0 || call > 6)) cout << "Nepravilnaya komanda! ";
        cout << endl;
        switch (call){
            case 0: exit(0); break;
            case 1: add_material(argv[2]); break;
            case 2: craft(argv[1], argv[2], argv[3]); break;
            case 3: sell(argv[1], argv[3]); break;
            case 4: _find(argv[1], argv[3]); break;
            case 5: show_material_info(argv[2]); break;
            case 6: add_storage(argv[1], argv[3]); break;
        }
    }

    return 0;
}

