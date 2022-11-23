#include "QSourceProg.h"

int QSourceProg::get_i()
{
    return i;
}

int QSourceProg::get_m()
{
    return m;
}

int* QSourceProg::get_pm()
{
    return &m;
}

int* QSourceProg::get_pi()
{
    return &i;
}

int QSourceProg::get_aKolvots()
{
    return a.kolvots;
}
int* QSourceProg::get_paKolvots()
{
    return &a.kolvots;
}
int QSourceProg::get_adlina()
{
    return a.dlina;
}
int* QSourceProg::get_padlina()
{
    return &a.dlina;
}

int QSourceProg::get_r_dlina()
{
    return r_dlina;
}

int* QSourceProg::get_r_pdlina()
{
    return &r_dlina;
}

int QSourceProg::get_i1()
{
    return i1;
}

int* QSourceProg::get_pi1()
{
    return &i1;
}

int QSourceProg::get_j()
{
    return j;
}

int* QSourceProg::get_pj()
{
    return &j;
}

GEN_PSP QSourceProg::get_a()
{
    return a;
}

PGEN_PSP QSourceProg::get_pa()
{
    return &a;
}

char* QSourceProg::get_b()
{
    return b;
}

void QSourceProg::set_i(int iNewi)
{
    i=iNewi;
}

void QSourceProg::set_m(int iNewM)
{
    m=iNewM;
}

void QSourceProg::set_r_dlina(int iNewR_dlina)
{
    r_dlina=iNewR_dlina;
}

void QSourceProg::set_i1(int iNewI1)
{
    i1=iNewI1;
}

void QSourceProg::set_j(int iNewJ)
{
    j=iNewJ;
}

// метод устанавливающий a.dlina
void QSourceProg::set_aDlina(int newA_dlina)
{
    a.dlina = newA_dlina;
}

void QSourceProg::set_aKolvots(int newKolvots)
{
    a.kolvots = newKolvots;
}

char* QSourceProg::get_aTs()
{
    return a.ts;
}

bool QSourceProg::setKeyData(const char* keyName)
{
    //открыть файл с ключом
    kl=fopen(keyName,"rt");
    if (!kl)
    {
        return false;
    }
    //прочитать из файла с ключом значение длины регистра сдвига
    fscanf(kl,"%d", &a.dlina);
    //прочитать из файла с ключом количество точек съема
    fscanf(kl,"%d", &a.kolvots);
    //прочитать из файла с ключом номера точек съема, кроме первой, потому что она всегда подключена к нулевой ячейке
    for (int j=1;j<a.kolvots;j++)
    {
        fscanf(kl,"%d",&a.ts[j]);
    }
    //указывается, что точка съема идет из нулевой ячейки
    a.ts[0]=0;
    //прочитать из файла с ключом начальное заполнение регистра сдвига
    for (int j=0;j<a.dlina;j++)
    {
        fscanf(kl,"%d",&a.ww[j]);
    }
    //закрыть файл
    fclose(kl);
    return true;
}

bool QSourceProg::setFileData(const char *fileName)
{
    //открыть файл с открытым текстом
    te=fopen(fileName,"rb");
    if (!te)
    {
        return false;
    }
    //прочитать из файла с открытым текстом 10000 байт
    // В r_dlina будет реально прочитанное число байт, которое может быть и меньше 10000.
    r_dlina=fread(b,1,10000,te);
    return true;
}

FILE* QSourceProg::getKeyHandler()
{
    return kl;
}

FILE* QSourceProg::getDataHandler()
{
    return te;
}

void QSourceProg::crypt(std::vector <void*> listData)
{
    int currentM = *(int*)listData.at(0);
    int curretDlina = *(int*)listData.at(1);
    int currentI = *(int*)listData.at(2);
    GEN_PSP currentA = *(PGEN_PSP)listData.at(3);

    memcpy(currentA.ts,listData.at(4),16);
    currentA.kolvots = *(int*)listData.at(5);
    currentA.dlina = *(int*)listData.at(6);
    char currentB[10000];
    memcpy(currentB,listData.at(7),10000);

    for (i1=0;i1<r_dlina;i1++)
    {
        //формирование байта гаммы.
        //байт гаммы сначала равен 0
        m=0;
        //вес младшего разряда=2^0
        j=1;
        while (j<256) //чтобы повторилось 8 раз
        {
            //получение бита обратной связи и его запись в начало регистра сдвига, т.е сложение по модулю 2 чисел из ячеек, на которые указывают точки съема
            for (int n=1;n<a.kolvots;n++)
            {
                a.ww[a.ts[0]]=(a.ww[a.ts[0]]+a.ww[a.ts[n]]) % 2;
            }
            m=m+a.ww[a.ts[0]]*j;
            //к формируемому байту гаммы добавляется очередной разряд (значение умножается на вес)
            //сдвиг номеров точек съема.
            for (int n=0;n<a.kolvots;n++)
            {
                a.ts[n]=(a.ts[n]+1) % a.dlina;
            };
            //переход к следующей степени двойки для следующего веса разряда
            j=j*2;
        }
        //конец формирования байта гаммы
        //сложение по модулю 2 байта открытого текста и гаммы
        b[i1]=b[i1] ^ m;
    }
    i = j;
}

void QSourceProg::writeDataFile()
{
    //создать файл для записи замаскированного текста
    if((te1=fopen("test.txt", "wb"))==NULL)
    {
        return;
    }

    size_t test = 0;
    test = fwrite(b,1,r_dlina,te1);
    fclose(te1);
}
