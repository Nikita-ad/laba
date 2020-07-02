#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "header.h"
using namespace std;

ostream& operator<<(ostream &out, const material a){
    out.write((char*)&a, sizeof(material));
    return out;
}

ostream& operator<<(ostream &out, const furniture a){
    out.write((char*)&a, sizeof(furniture));
    return out;
}

void add_material(char* material_filename){
    ifstream f = get_inf(material_filename);
    material a;
    f.read((char*)&a, sizeof(material));
    f.close();

    int call, to_add;
    cout << "Dosku - 1\nBrusok - 2\nViberite material: ";
    cin >> call;
    cout << "Vvedite kol-vo materiala: ";
    cin >> to_add;

    if (call == 1){
        int doska = a.get_doska_count();
        doska += to_add;
        a.set_doska_count(doska);
    }
    else if (call == 2){
        int brusok = a.get_brusok_count();
        brusok += to_add;
        a.set_brusok_count(brusok);
    }
    ofstream ff = get_outf(material_filename);
    ff << a;
    ff.close();

    cout << "Material uspeshno dobavlen!\n";
}


int get_type(){
    int type = 0;
    while(type < 1 || type > 3){
        cout << "Krovat - 1\nSkaf - 2\nStol - 3\nViberite type mebeli: ";
        cin >> type;
        if (type < 1 || type > 3) cout << "Ne verniy type!\n";
    }
    return type;
}

ifstream get_inf(char* filename){
    ifstream f;
    f.open(filename);
    if (!f) exit(0);
    return f;
}

ofstream get_outf(char* filename){
    ofstream f;
    f.open(filename);
    if (!f) exit(0);
    return f;
}

void craft_bed(furniture* a, material* b, int index){
    cout << "Cena krovati: doski - " << a->get_bed_doska_cost() << " bruski - " << a->get_bed_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 krovati na sklade: " << a->get_bed_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko krovatey sdelat? ";
        cin >> c;
        need_doski = c * a->get_bed_doska_cost(), need_bruski = c * a->get_bed_brusok_cost(), need_capacity = c * a->get_bed_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity(index) - a->get_curr_capacity(index)))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_bed_count(index, a->get_bed_count(index) + c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) + c * a->get_bed_cost());

}

void craft_cabinet(furniture* a, material* b, int index){
    cout << "Cena shkafa: doski - " << a->get_cabinet_doska_cost() << " bruski - " << a->get_cabinet_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 shkafa na sklade: " << a->get_cabinet_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko shkafov sdelat? ";
        cin >> c;
        need_doski = c * a->get_cabinet_doska_cost(), need_bruski = c * a->get_cabinet_brusok_cost(), need_capacity = c * a->get_cabinet_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity(index) - a->get_curr_capacity(index)))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_cabinet_count(index, a->get_cabinet_count(index) + c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) + c * a->get_cabinet_cost());
}

void craft_table(furniture* a, material* b, int index){
    cout << "Cena stola: doski - " << a->get_table_doska_cost() << " bruski - " << a->get_table_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 stola na sklade: " << a->get_table_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko krovatey sdelat? ";
        cin >> c;
        need_doski = c * a->get_table_doska_cost(), need_bruski = c * a->get_table_brusok_cost(), need_capacity = c * a->get_table_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity(index) - a->get_curr_capacity(index)))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_table_count(index, a->get_table_count(index) + c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) + c * a->get_table_cost());
}


void craft(char* furniture_filename, char* material_filename, char* storage_filename){
    ifstream f = get_inf(material_filename);
    material a;
    f.read((char*)&a, sizeof(material));
    f.close();

    int type = get_type();
    ifstream ff = get_inf(furniture_filename);
    furniture b;
    ff.read((char*)&b, sizeof(furniture));
    ff.close();
    b.init_bed_count();
    b.init_cabinet_count();
    b.init_table_count();
    b.init_storage_capacity();
    b.init_curr_capacity();
    load_furniture(&b, storage_filename);

    int storage_count = b.get_storage_count(), i = 0, num;
    cout << "Vashi materiali: doski - " << a.get_doska_count() << " bruski - " << a.get_brusok_count() << "\n\n";
    for (i; i < storage_count; i++){
        cout << i + 1 << ". svobodno ya4eek: " << b.get_storage_capacity(i) - b.get_curr_capacity(i) << endl;
    }
    cout << "Vvedite nomer sklada: ";
    cin >> num;
    num--;

    switch(type){
        case 1 : craft_bed(&b, &a, num); break;
        case 2 : craft_cabinet(&b, &a, num); break;
        case 3 : craft_table(&b, &a, num); break;
    }

    dump_furniture(b, furniture_filename, storage_filename);

    ofstream fff = get_outf(material_filename);
    fff << a;
    fff.close();

    cout << "Mebel uspeshno proizvedena i uze lejit na sklade!\n";
}



void add_storage(char* furniture_filename, char* storage_filename){
    ifstream ff = get_inf(furniture_filename);
    furniture a;
    ff.read((char*)&a, sizeof(furniture));
    ff.close();

    a.set_storage_count(a.get_storage_count() + 1);
    a.init_bed_count();
    a.init_cabinet_count();
    a.init_table_count();
    a.init_storage_capacity();
    a.init_curr_capacity();
    load_furniture(&a, storage_filename);

    int bed_count = 0, cabinet_count = 0, table_count = 0, curr_capacity = 0, storage_capacity;
    cout << "\nVvedite kol-vo ya4eek na sklade: ";
    cin >> storage_capacity;

    a.set_bed_count(a.get_storage_count() - 1, bed_count);
    a.set_cabinet_count(a.get_storage_count() - 1, cabinet_count);
    a.set_table_count(a.get_storage_count() - 1, table_count);
    a.set_curr_capacity(a.get_storage_count() - 1, curr_capacity);
    a.set_storage_capacity(a.get_storage_count() - 1, storage_capacity);

    dump_furniture(a, furniture_filename, storage_filename);

    cout << "Sklad uspeshno dobavlen!\n";
}




void sell_bed(furniture* a, int index){
    cout << "\nKol-vo krovatey sey4as: " << a->get_bed_count(index) << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_bed_count(index)) cout << "Stolko netu!\n";
        else break;
    }

    a->set_bed_count(index, a->get_bed_count(index) - c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) - a->get_bed_cost() * c);
}

void sell_cabinet(furniture* a, int index){
    cout << "\nKol-vo shkafov sey4as: " << a->get_cabinet_count(index) << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_cabinet_count(index)) cout << "Stolko netu!\n";
        else break;
    }

    a->set_cabinet_count(index, a->get_cabinet_count(index) - c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) - a->get_cabinet_cost() * c);
}

void sell_table(furniture* a, int index){
    cout << "\nKol-vo stolov sey4as: " << a->get_table_count(index) << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_table_count(index)) cout << "Stolko netu!\n";
        else break;
    }

    a->set_table_count(index, a->get_table_count(index) - c);
    a->set_curr_capacity(index, a->get_curr_capacity(index) - a->get_table_cost() * c);
}


void sell(char* furniture_filename, char* storage_filename){
    int type = get_type();
    ifstream f = get_inf(furniture_filename);
    furniture a;
    f.read((char*)&a, sizeof(furniture));
    f.close();
    a.init_bed_count();
    a.init_cabinet_count();
    a.init_table_count();
    a.init_storage_capacity();
    a.init_curr_capacity();
    load_furniture(&a, storage_filename);

    int storage_count = a.get_storage_count(), i = 0, num;

    for (i; i < storage_count; i++){
        cout << i + 1 << ". svobodno ya4eek: " << a.get_storage_capacity(i) - a.get_curr_capacity(i) << endl;
    }
    cout << "Vvedite nomer sklada: ";
    cin >> num;
    num--;

    switch(type){
        case 1 : sell_bed(&a, num); break;
        case 2 : sell_cabinet(&a, num); break;
        case 3 : sell_table(&a, num); break;
    }

    dump_furniture(a, furniture_filename, storage_filename);

    cout << "Mebel uspushno prodana!\n";
}




void show_bed_info(furniture* a, int index){
    cout << "\nKol-vo krovatey: " << a->get_bed_count(index) << endl;
    cout << "Materiali dlya 1 krovaty: doski - " << a->get_bed_doska_cost() << ", bruski - " << a->get_bed_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 krovati na sklade: " << a->get_bed_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih krovatyami: " << a->get_bed_cost() * a->get_bed_count(index) << "\n\n";
}

void show_cabinet_info(furniture* a, int index){
    cout << "\nKol-vo shkafov: " << a->get_cabinet_count(index) << endl;
    cout << "Materiali dlya 1 shkafa: doski - " << a->get_cabinet_doska_cost() << ", bruski - " << a->get_cabinet_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 shkafa na sklade: " << a->get_cabinet_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih shkafami: " << a->get_cabinet_cost() * a->get_cabinet_count(index) << "\n\n";
}

void show_table_info(furniture* a, int index){
    cout << "\nKol-vo stolov: " << a->get_table_count(index) << endl;
    cout << "Materiali dlya 1 stola: doski - " << a->get_table_doska_cost() << ", bruski - " << a->get_table_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 stola na sklade: " << a->get_table_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih stolami: " << a->get_table_cost() * a->get_table_count(index) << "\n\n";
}

void _find(char* furniture_filename, char* storage_filename){
    int type = get_type();
    ifstream f = get_inf(furniture_filename);
    furniture a;
    f.read((char*)&a, sizeof(furniture));
    f.close();
    a.init_bed_count();
    a.init_cabinet_count();
    a.init_table_count();
    a.init_storage_capacity();
    a.init_curr_capacity();
    load_furniture(&a, storage_filename);

    int storage_count = a.get_storage_count(), i = 0, num;

    for (i; i < storage_count; i++){
        cout << i + 1 << ". svobodno ya4eek: " << a.get_storage_capacity(i) - a.get_curr_capacity(i) << endl;
    }
    cout << "Vvedite nomer sklada: ";
    cin >> num;
    num--;

    switch(type){
        case 1 : show_bed_info(&a, num); break;
        case 2 : show_cabinet_info(&a, num); break;
        case 3 : show_table_info(&a, num); break;
    }

}



void show_material_info(char* material_filename){
    ifstream f = get_inf(material_filename);
    material a;
    f.read((char*)&a, sizeof(material));
    f.close();

    cout << "Vashi materiali: doski - " << a.get_doska_count() << " bruski - " << a.get_brusok_count() << endl;
}



void dump_furniture(furniture a, char* furniture_filename, char* storage_filename){
    ofstream f = get_outf(furniture_filename);
    f.write((char*)&a, sizeof(furniture));
    f.close();

    ofstream ff = get_outf(storage_filename);
    int storage_count = a.get_storage_count(), i = 0;

    for (i; i < storage_count; i++){
        ff << a.get_bed_count(i) << " ";
        ff << a.get_cabinet_count(i) << " ";
        ff << a.get_table_count(i) << " ";
        ff << a.get_storage_capacity(i) << " ";
        ff << a.get_curr_capacity(i) << " ";
    }

    ff.close();
}


void load_furniture(furniture* a, char* storage_filename){

    ifstream ff = get_inf(storage_filename);
    int storage_count = a->get_storage_count(), i = 0;

    for (i; i < storage_count; i++){
        int bed_count = 0;
        int cabinet_count = 0;
        int table_count = 0;
        int storage_capacity = 0;
        int curr_capacity = 0;

        ff >> bed_count;
        ff >> cabinet_count;
        ff >> table_count;
        ff >> storage_capacity;
        ff >> curr_capacity;


        a->set_bed_count(i, bed_count);
        a->set_cabinet_count(i, cabinet_count);
        a->set_table_count(i, table_count);
        a->set_storage_capacity(i, storage_capacity);
        a->set_curr_capacity(i, curr_capacity);
    }
    ff.close();
}

int furniture::get_bed_count(int index){return bed_count[index];}
int furniture::get_bed_doska_cost(){return bed_doska_cost;}
int furniture::get_bed_brusok_cost(){return bed_brusok_cost;}
int furniture::get_bed_cost(){return bed_cost;}
void furniture::set_bed_count(int index, int val){bed_count[index] = val;}
void furniture::set_bed_doska_cost(int val){bed_doska_cost = val;}
void furniture::set_bed_brusok_cost(int val){bed_brusok_cost = val;}
void furniture::set_bed_cost(int val){bed_cost = val;}

int furniture::get_cabinet_count(int index){return cabinet_count[index];}
int furniture::get_cabinet_doska_cost(){return cabinet_doska_cost;}
int furniture::get_cabinet_brusok_cost(){return cabinet_brusok_cost;}
int furniture::get_cabinet_cost(){return cabinet_cost;}
void furniture::set_cabinet_count(int index, int val){cabinet_count[index] = val;}
void furniture::set_cabinet_doska_cost(int val){cabinet_doska_cost = val;}
void furniture::set_cabinet_brusok_cost(int val){cabinet_brusok_cost = val;}
void furniture::set_cabinet_cost(int val){cabinet_cost = val;}

int furniture::get_table_count(int index){return table_count[index];}
int furniture::get_table_doska_cost(){return table_doska_cost;}
int furniture::get_table_brusok_cost(){return table_brusok_cost;}
int furniture::get_table_cost(){return table_cost;}
void furniture::set_table_count(int index, int val){table_count[index] = val;}
void furniture::set_table_doska_cost(int val){table_doska_cost = val;}
void furniture::set_table_brusok_cost(int val){table_brusok_cost = val;}
void furniture::set_table_cost(int val){table_cost = val;}

int furniture::get_storage_capacity(int index){return storage_capacity[index];}
int furniture::get_curr_capacity(int index){return curr_capacity[index];}
void furniture::set_storage_capacity(int index, int val){
    storage_capacity[index] = val;
}
void furniture::set_curr_capacity(int index, int val){curr_capacity[index] = val;}


void furniture::init_bed_count(){
    bed_count = new int[storage_count];
}
void furniture::init_cabinet_count(){
    cabinet_count = new int[storage_count];
}
void furniture::init_table_count(){
    table_count = new int[storage_count];
}
void furniture::init_storage_capacity(){
    storage_capacity = new int[storage_count];
}
void furniture::init_curr_capacity(){
    curr_capacity = new int[storage_count];
}


int furniture::get_storage_count(){return storage_count;}
void furniture::set_storage_count(int val){storage_count = val;}

int material::get_doska_count(){return doska_count;}
int material::get_brusok_count(){return brusok_count;}
void material::set_doska_count(int val){doska_count = val;}
void material::set_brusok_count (int val){brusok_count = val;}
