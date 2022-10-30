#ifndef QSOURCEPROG_H
#define QSOURCEPROG_H

#endif // QSOURCEPROG_H

//структура для описания генератора гаммы
typedef struct GEN_PSP
{
    //регистр сдвига (максимальная длина 201 ячейка) char ts[201];//номера точек съема
    char ts[201];
    //количество точек съема
    int kolvots;
    //длина регистра сдвига
    int dlina;
} GEP_PSP,*PGEN_PSP;

class QSourceProg
{
private:
    //m - байт гаммы
    int m = 0;
    //r_dlina - реально прочитанное из файла количество байт
    int r_dlina = 0;
    //i и i1 - счетчики циклов,
    int i = 0;
    int i1 = 0;
    //j - вес очередного разряда, который нужен, чтобы сформировать байт гаммы
    int j = 0;
    // Генератор гаммы
    GEN_PSP a;
    //массив для работы с текстом (сначала в него текст читается из файла, потом в нем же текст преобразуется)
    char b[10000];

public:
    // метод возвращающий i
    int get_i();
    // метод возвращающий указатель i
    int* get_pi();
    // метод возвращающий m
    int get_m();
    // метод возвращающий указатель m
    int* get_pm();
    // метод возвращающий r_dlina
    int get_r_dlina();
    // метод возвращающий указатель r_dlina
    int* get_r_pdlina();
    char* get_aTs();
    // метод возвращающий i1
    int get_i1();
    // метод возвращающий указатель i1
    int* get_pi1();
    // метод возвращающий j
    int get_j();
    // метод возвращающий указатель p
    int* get_pj();
    // метод возвращающий a
    GEN_PSP get_a();
    // метод возвращающий указатель a
    PGEN_PSP get_pa();
    int get_aKolvots();
    int* get_paKolvots();
    int get_adlina();
    int* get_padlina();
    // метод возвращающий b
    char* get_b();
    // метод устанавливающий i
    void set_i(int iNewi);
    // метод устанавливающий m
    void set_m(int iNewM);
    // метод устанавливающий r_dlina
    void set_r_dlina(int iNewR_dlina);
    // метод устанавливающий i1
    void set_i1(int iNewI1);
    // метод устанавливающий j
    void set_j(int iNewJ);
    // метод устанавливающий a.dlina
    void set_aDlina(int newA_dlina);
    // метод устанавливающий a.kolvots
    void set_aKolvots(int newKolvots);
    // метод устанавливающий a.ww
    void set_ww(int newWw);
    // метод устанавливающий b
    void set_b();
};

