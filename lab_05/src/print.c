#include "print.h"


void description(void)
{
    printf(TURQ "Данная программа реализует моделирование процесс обслуживания\n\
до ухода из системы первых 1000 заявок.\n\n\
Система массового обслуживания состоит из \n\
обслуживающего аппарата(ОА) и очереди заявок.\n\
После обслуживания каждых 100 заявок программа выдает информацию\n\
о текущей и средней длине очереди. Каждая заявка после ОА\n\
с вероятностью Р вновь поступает в 'хвост' очереди, совершая новый цикл\n\
обслуживания, а с вероятностью 1-Р покидает систему." RESET);
}

void menu(void)
{
    printf(TURQ "\n\n Пункты меню:\n\
1 - моделирование очереди из 1000 элементов в виде массива\n\
2 - моделирование очереди из 1000 элементов в виде списка\n\
3 - вывод таблицы когда-либо использованных адресов\n\
4 - вывод сравнения времени и памяти для 1 и 2 пункта\n\n\
0 - выход из программы\n\
Выберите пункт меню: " RESET);
}

