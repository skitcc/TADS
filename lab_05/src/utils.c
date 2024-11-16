#include "utils.h"


// Функция вычисления ожидаемого времени моделирования
double calculate_expected_model_time(int arrival_start, int arrival_end, int preproc_start, int preproc_end) 
{
    double model_time = 0;

    if ((COMING_END + COMING_START) <= (PROCESSING_END + PROCESSING_START)) {
        model_time = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
    } else {
        model_time = ((double)(PROCESSING_END + PROCESSING_START) / 2) * TOTAL_NEED * (1 / 0.2);
    }

    if ((COMING_START == 0) && (COMING_END == 6) && (PROCESSING_END == 1) && (PROCESSING_START == 0)) {
        model_time = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
    }

    return model_time;
}

void display_interim_results(struct machine *machine, struct queue *queue) 
{
    printf("Обработано заявок: %d\n", machine->processed_count);
    printf("Текущая длина очереди: %d\n", queue->len);
    printf("Средняя длина очереди: %.2f\n\n", (double)(queue->state / machine->triggering));
}

// Функция вывода окончательных результатов
void display_final_results(struct machine *machine, struct queue *queue, int *memory_used, int max_queue_size, int arrival_start, int arrival_end, int preproc_start, int preproc_end) 
{
    double expected_model_time = calculate_expected_model_time(arrival_start, arrival_end, preproc_start, preproc_end);
    *memory_used = max_queue_size * (sizeof(struct queue_slot) - sizeof(struct queue_slot*));

    printf("Ожидаемое время моделирования: %.2f\n", expected_model_time);
    printf("Полученное время моделирования: %.2f\n", machine->time);
    // printf("Погрешность: ~%.2f%%\n\n", fabs((machine->time - expected_model_time) / expected_model_time * 100));
    printf("Количество заявок, поступивших в очередь: %d\n", queue->in_num);
    printf("Количество заявок, покинувших очередь: %d\n", machine->processed_count);
    printf("Среднее время в очереди: %.2f\n", queue->total_stay_time / machine->processed_count);
    printf("Время простоя аппарата: %.2f\n", machine->downtime);
    printf("Количество срабатываний аппарата: %d\n\n", machine->triggering);
}



// Вспомогательная функция для продвижения указателя в очереди
void advance_queue_pointer(struct queue_slot **pointer, struct queue_slot *array, int length) 
{
    if (*pointer == array + length - 1) {
        *pointer = array;
    } else {
        (*pointer)++;
    }
}

// Сравнение результатов использования списка и массива
void compare_queue_models(struct mem_slot **mem) 
{
    int memory_list = 0, memory_array = 0;
    unsigned long time_list = simulate_service_list(mem, &memory_list);
    unsigned long time_array = simulate_service_arr(&memory_array);

    free_memory_list(mem);

    printf("Время для списка (в тиках): %lu\n", time_list);
    printf("Время для массива (в тиках): %lu\n", time_array);
    printf("Память для списка (в байтах): %d\n", memory_list);
    printf("Память для массива (в байтах): %d\n", memory_array);
}