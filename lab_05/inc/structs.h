#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "definitions.h"

struct queue_slot
{
    double arrival_time; //время прихода в очередб
    struct queue_slot *next; //указатель на след элемент
};

struct queue
{
    struct queue_slot *pin; //указатель на начало очереди
    struct queue_slot *pout; //указатель на конец очереди
    int len; //длина очереди
    int in_num; //число вошедших в очередь заявок
    int state; //переменная для вычисления средней длины
    int max; // переменная для подсчета очереди в списке
    double total_stay_time; //время нахождения заявок в очереди
};

struct machine
{
    double time; //текущее время состояния аппарата 
    double downtime; // время простоя аппарата
    int triggering; // количесво срабатывания аппарата
    int processed_count; //кол-во обработанных из очереди заявок
};

struct mem_slot
{
    struct queue_slot *queue_slot; //указатель на участок памяти
    int busy; // состояние участка 1(занят) или 0
    struct mem_slot *next; //указатель на след элемент очереди
};

#endif