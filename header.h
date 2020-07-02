#include <iostream>
#pragma once

/**
@class material
Класс с материалами, в нем хранится инфа про кол-во материалов (доски, бруски), доступ к приватным полям через сетеры, гетеры
*/
class material{
private:
    int doska_count = 0;
    int brusok_count = 0;
public:
    int get_doska_count();
    int get_brusok_count();
    void set_doska_count(int val);
    void set_brusok_count (int val);
};


/**
@class furniture
Класс, в котором хранится информация о мебели (сколько материалов надо для конкретного вида, сколько ячеек занимает на складе 1 единица,),
состоянии склада(общая вместимость, текущая заполненность),
*/
class furniture{
private:
    ///кол-во досок на 1 кровать
    int bed_doska_cost = 5;
    ///кол-во брусков на 1 кровать
    int bed_brusok_cost = 3;
    ///кол-во ячеек для 1 кровати на складе
    int bed_cost = 5;
    ///кол-во кроватей на складе
    int* bed_count;

    int cabinet_doska_cost = 7;
    int cabinet_brusok_cost = 3;
    int cabinet_cost = 8;
    int* cabinet_count;

    int table_doska_cost = 4;
    int table_brusok_cost = 4;
    int table_cost = 3;
    int* table_count;

    ///кол-во ячеек на складе
    int* storage_capacity;
    ///кол-во заполненных ячеек
    int* curr_capacity;
    ///кол-во складов
    int storage_count = 0;

public:
    int get_bed_count(int index);
    int get_bed_doska_cost();
    int get_bed_brusok_cost();
    int get_bed_cost();
    void set_bed_count(int index, int val);
    void set_bed_doska_cost(int val);
    void set_bed_brusok_cost(int val);
    void set_bed_cost(int val);

    int get_cabinet_count(int index);
    int get_cabinet_doska_cost();
    int get_cabinet_brusok_cost();
    int get_cabinet_cost();
    void set_cabinet_count(int index, int val);
    void set_cabinet_doska_cost(int val);
    void set_cabinet_brusok_cost(int val);
    void set_cabinet_cost(int val);

    int get_table_count(int index);
    int get_table_doska_cost();
    int get_table_brusok_cost();
    int get_table_cost();
    void set_table_count(int index, int val);
    void set_table_doska_cost(int val);
    void set_table_brusok_cost(int val);
    void set_table_cost(int val);

    int get_storage_capacity(int index);
    int get_curr_capacity(int index);
    void set_storage_capacity(int index, int val);
    void set_curr_capacity(int index, int val);

    int get_storage_count();
    void set_storage_count(int val);

    void init_bed_count();
    void init_cabinet_count();
    void init_table_count();
    void init_storage_capacity();
    void init_curr_capacity();

    ~furniture(){
        delete[] bed_count;
        delete[] cabinet_count;
        delete[] table_count;
        delete[] storage_capacity;
        delete[] curr_capacity;
    }

    friend std::ostream& operator<<(std::ostream &out, const material a);
    friend std::ostream& operator<<(std::ostream &out, const furniture a);
};

/**
@function add_material
Функция добавления материалов путем загрузки экземпляра класса, изменения его полей с помощью сеттеров, геттеров, и сохранения его в файл
*/
void add_material(char* material_filename);



/**
@function get_type
Функция для запроса типа мебели, 1 - кровать, 2 - шкаф, 3 - стол
*/
int get_type();




/**
@function get_inf
Функция для получения файла для считывания
*/
std::ifstream get_inf(char* filename);




/**
@function get_outf
Функция для получения файла на запись
*/
std::ofstream get_outf(char* filename);



/**
@function craft_bed
В соответствии с введенным кол-вом кроватей, которые нужно создать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
и material(кол-во брусков, досок)
*/
void craft_bed(furniture* a, material* b, int index);




/**
@function craft_cabinet
В соответствии с введенным кол-вом шкафов, которые нужно создать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
и material(кол-во брусков, досок)
*/
void craft_cabinet(furniture* a, material* b, int index);




/**
@function craft_table
В соответствии с введенным кол-вом столов, которые нужно создать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
и material(кол-во брусков, досок)
*/
void craft_table(furniture* a, material* b, int index);




/**
@function craft
Функция для создания мебели
*/
void craft(char* furniture_filename, char* material_filename, char* storage_filename);




/**
@function sell_bed
В соответствии с введенным кол-вом кроватей, которые нужно продать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
*/
void sell_bed(furniture* a, int index);




/**
@function sell_cabinet
В соответствии с введенным кол-вом шкафов, которые нужно продать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
*/
void sell_cabinet(furniture* a, int index);




/**
@function sell_table
В соответствии с введенным кол-вом столов, которые нужно продать изменяются поля в классах furniture(кол-во данного типа мебели, текущая заполненность на складе)
*/
void sell_table(furniture* a, int index);




/**
@function sell
Функция для продажи мебели
*/
void sell(char* furniture_filename, char* storage_filename);




/**
@function show_bed_info
Выводит информацию о кроватях на складе
*/
void show_bed_info(furniture* a, int index);




/**
@function show_cabinet_info
Выводит информацию о шкафах на складе
*/
void show_cabinet_info(furniture* a, int index);




/**
@function show_table_info
Выводит информацию о столах на складе
*/
void show_table_info(furniture* a, int index);




/**
@function _find
В зависимости от типа мебели, показывает информацию о нем через функции show
*/
void _find(char* furniture_filename, char* storage_filename);




/**
@function show_material_info
Показывает информацию о материалах (кол-во брусков и досок)
*/
void show_material_info(char* material_filename);




/**
@function dump_furniture
Загружает мебель в файл, элементы динамичных полей в отдельный файл
*/
void dump_furniture(furniture a, char* furniture_filename, char* storage_filename);




/**
@function load_furniture
Загружает мебель из файла, элементы динамичных полей из отдельного файла
*/
void load_furniture(furniture* a, char* storage_filename);




/**
@function add_storage
Добавляет склад
*/
void add_storage(char* furniture_filename, char* storage_filename);
