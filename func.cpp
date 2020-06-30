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

void craft_bed(furniture* a, material* b){
    cout << "Cena krovati: doski - " << a->get_bed_doska_cost() << " bruski - " << a->get_bed_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 krovati na sklade: " << a->get_bed_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko krovatey sdelat? ";
        cin >> c;
        need_doski = c * a->get_bed_doska_cost(), need_bruski = c * a->get_bed_brusok_cost(), need_capacity = c * a->get_bed_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity() - a->get_curr_capacity()))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_bed_count(a->get_bed_count() + c);
    a->set_curr_capacity(a->get_curr_capacity() + c * a->get_bed_cost());

}

void craft_cabinet(furniture* a, material* b){
    cout << "Cena shkafa: doski - " << a->get_cabinet_doska_cost() << " bruski - " << a->get_cabinet_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 shkafa na sklade: " << a->get_cabinet_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko shkafov sdelat? ";
        cin >> c;
        need_doski = c * a->get_cabinet_doska_cost(), need_bruski = c * a->get_cabinet_brusok_cost(), need_capacity = c * a->get_cabinet_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity() - a->get_curr_capacity()))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_cabinet_count(a->get_cabinet_count() + c);
    a->set_curr_capacity(a->get_curr_capacity() + c * a->get_cabinet_cost());
}

void craft_table(furniture* a, material* b){
    cout << "Cena stola: doski - " << a->get_table_doska_cost() << " bruski - " << a->get_table_brusok_cost() << endl;
    cout << "Kol-vo ya4eek dlya 1 stola na sklade: " << a->get_table_cost() << endl;

    int need_doski, need_bruski, need_capacity, c;
    while (1){
        cout << "Skolko krovatey sdelat? ";
        cin >> c;
        need_doski = c * a->get_table_doska_cost(), need_bruski = c * a->get_table_brusok_cost(), need_capacity = c * a->get_table_cost();
        if ((need_doski > b->get_doska_count()) || (need_bruski > b->get_brusok_count()) || (need_capacity > (a->get_storage_capacity() - a->get_curr_capacity()))) cout << "Ne dostato4no materialov ili ycheek!\n";
        else break;
    }


    b->set_doska_count(b->get_doska_count() - need_doski);
    b->set_brusok_count(b->get_brusok_count() - need_bruski);
    a->set_table_count(a->get_table_count() + c);
    a->set_curr_capacity(a->get_curr_capacity() + c * a->get_table_cost());
}


void craft(char* furniture_filename, char* material_filename){
    ifstream f;
    f.open(material_filename);
    if (!f) exit(0);
    material a;
    f.read((char*)&a, sizeof(material));
    f.close();

    int type = get_type();
    ifstream ff = get_inf(furniture_filename);
    furniture b;
    ff.read((char*)&b, sizeof(furniture));
    ff.close();

    cout << "\n\nKol-vo svobodnih ya4eek na sklade: " << b.get_storage_capacity() - b.get_curr_capacity() << endl;
    cout << "Vashi materiali: doski - " << a.get_doska_count() << " bruski - " << a.get_brusok_count() << endl;
    switch(type){
        case 1 : craft_bed(&b, &a); break;
        case 2 : craft_cabinet(&b, &a); break;
        case 3 : craft_table(&b, &a); break;
    }

    ofstream fff = get_outf(furniture_filename);
    fff.write((char*)&b, sizeof(furniture));
    fff.close();

    ofstream ffff;
    ffff.open(material_filename);
    if(!ffff) exit(0);
    ffff << a;
    ffff.close();

    cout << "Mebel uspeshno proizvedena i uze lejit na sklade!\n";
}






void sell_bed(furniture* a){
    cout << "\nKol-vo krovatey sey4as: " << a->get_bed_count() << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_bed_count()) cout << "Stolko netu!\n";
        else break;
    }

    a->set_bed_count(a->get_bed_count() - c);
    a->set_curr_capacity(a->get_curr_capacity() - a->get_bed_cost() * c);
}

void sell_cabinet(furniture* a){
    cout << "\nKol-vo shkafov sey4as: " << a->get_cabinet_count() << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_cabinet_count()) cout << "Stolko netu!\n";
        else break;
    }

    a->set_cabinet_count(a->get_cabinet_count() - c);
    a->set_curr_capacity(a->get_curr_capacity() - a->get_cabinet_cost() * c);
}

void sell_table(furniture* a){
    cout << "\nKol-vo stolov sey4as: " << a->get_table_count() << endl;
    int c;
    while (1){
        cout << "Skolko prodat? ";
        cin >> c;
        if (c > a->get_table_count()) cout << "Stolko netu!\n";
        else break;
    }

    a->set_table_count(a->get_table_count() - c);
    a->set_curr_capacity(a->get_curr_capacity() - a->get_table_cost() * c);
}


void sell(char* furniture_filename){
    int type = get_type();
    ifstream f = get_inf(furniture_filename);
    furniture a;
    f.read((char*)&a, sizeof(furniture));
    f.close();

    switch(type){
        case 1 : sell_bed(&a); break;
        case 2 : sell_cabinet(&a); break;
        case 3 : sell_table(&a); break;
    }

    ofstream ff = get_outf(furniture_filename);

    ff << a;
    ff.close();

    cout << "Mebel uspushno prodana!\n";
}




void show_bed_info(furniture* a){
    cout << "\nKol-vo krovatey: " << a->get_bed_count() << endl;
    cout << "Materiali dlya 1 krovaty: doski - " << a->get_bed_doska_cost() << ", bruski - " << a->get_bed_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 krovati na sklade: " << a->get_bed_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih krovatyami: " << a->get_bed_cost() * a->get_bed_count() << "\n\n";
}

void show_cabinet_info(furniture* a){
    cout << "\nKol-vo shkafov: " << a->get_cabinet_count() << endl;
    cout << "Materiali dlya 1 shkafa: doski - " << a->get_cabinet_doska_cost() << ", bruski - " << a->get_cabinet_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 shkafa na sklade: " << a->get_cabinet_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih shkafami: " << a->get_cabinet_cost() * a->get_cabinet_count() << "\n\n";
}

void show_table_info(furniture* a){
    cout << "\nKol-vo stolov: " << a->get_table_count() << endl;
    cout << "Materiali dlya 1 stola: doski - " << a->get_table_doska_cost() << ", bruski - " << a->get_table_brusok_cost() << endl;
    cout << "Ya4eek dlya 1 stola na sklade: " << a->get_table_cost() << endl;
    cout << "Kol-vo ya4eek zanimaemih stolami: " << a->get_table_cost() * a->get_table_count() << "\n\n";
}

void _find(char* furniture_filename){
    int type = get_type();
    ifstream f = get_inf(furniture_filename);
    furniture a;
    f.read((char*)&a, sizeof(furniture));
    f.close();

    switch(type){
        case 1 : show_bed_info(&a); break;
        case 2 : show_cabinet_info(&a); break;
        case 3 : show_table_info(&a); break;
    }

}



void show_material_info(char* material_filename){
    ifstream f = get_inf(material_filename);
    material a;
    f.read((char*)&a, sizeof(material));
    f.close();

    cout << "Vashi materiali: doski - " << a.get_doska_count() << " bruski - " << a.get_brusok_count() << endl;
}


int furniture::get_bed_count(){return bed_count;}
int furniture::get_bed_doska_cost(){return bed_doska_cost;}
int furniture::get_bed_brusok_cost(){return bed_brusok_cost;}
int furniture::get_bed_cost(){return bed_cost;}
void furniture::set_bed_count(int val){bed_count = val;}
void furniture::set_bed_doska_cost(int val){bed_doska_cost = val;}
void furniture::set_bed_brusok_cost(int val){bed_brusok_cost = val;}
void furniture::set_bed_cost(int val){bed_cost = val;}

int furniture::get_cabinet_count(){return cabinet_count;}
int furniture::get_cabinet_doska_cost(){return cabinet_doska_cost;}
int furniture::get_cabinet_brusok_cost(){return cabinet_brusok_cost;}
int furniture::get_cabinet_cost(){return cabinet_cost;}
void furniture::set_cabinet_count(int val){cabinet_count = val;}
void furniture::set_cabinet_doska_cost(int val){cabinet_doska_cost = val;}
void furniture::set_cabinet_brusok_cost(int val){cabinet_brusok_cost = val;}
void furniture::set_cabinet_cost(int val){cabinet_cost = val;}

int furniture::get_table_count(){return table_count;}
int furniture::get_table_doska_cost(){return table_doska_cost;}
int furniture::get_table_brusok_cost(){return table_brusok_cost;}
int furniture::get_table_cost(){return table_cost;}
void furniture::set_table_count(int val){table_count = val;}
void furniture::set_table_doska_cost(int val){table_doska_cost = val;}
void furniture::set_table_brusok_cost(int val){table_brusok_cost = val;}
void furniture::set_table_cost(int val){table_cost = val;}

int furniture::get_storage_capacity(){return storage_capacity;}
int furniture::get_curr_capacity(){return curr_capacity;}
void furniture::set_storage_capacity(int val){
    if (val > curr_capacity) storage_capacity = val;
}
void furniture::set_curr_capacity(int val){curr_capacity = val;}

int material::get_doska_count(){return doska_count;}
int material::get_brusok_count(){return brusok_count;}
void material::set_doska_count(int val){doska_count = val;}
void material::set_brusok_count (int val){brusok_count = val;}
