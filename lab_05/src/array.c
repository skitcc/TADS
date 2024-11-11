#include "array.h"

// Функция для запуска симуляции обслуживания заявок
unsigned long simulate_service_arr(int *memory_used) 
{
    int max_queue_size = TOTAL_NEED;
    struct queue_slot *queue_array = malloc(max_queue_size * sizeof(struct queue_slot));

    struct queue queue = {
        .pin = queue_array,
        .pout = queue_array,
        .len = 0,
        .in_num = 0,
        .state = 0,
        .total_stay_time = 0
    };

    struct machine machine = {
        .time = 0,
        .downtime = 0,
        .triggering = 0,
        .processed_count = 0
    };

    double total_time = 0;
    int overflow_flag = 0;
    printf("\nМоделирование с использованием массива:\n\n");

    unsigned long start_time = tick();
    unsigned long time_adjustment = 0, temp_time = 0;

    while (overflow_flag != 2 && machine.processed_count < TOTAL_NEED) {
        while (queue.len == 0 || machine.time > total_time) {
            process_new_request_arr(&total_time, &machine, &queue, queue_array, max_queue_size);
            if (queue.len != 0 && queue.len != 1 && queue.pout == queue.pin) {
                overflow_flag = 2; // Остановка симуляции при переполнении очереди
            }
        }

        if (overflow_flag != 2) {
            overflow_flag = process_request_arr(&machine, &queue, queue_array, max_queue_size);
        }

        temp_time = tick();
        if (overflow_flag == 1 && machine.processed_count % INTER_NEED == 0) {
            display_interim_results(&machine, &queue);
        }
        time_adjustment += tick() - temp_time;

        if (overflow_flag == 1) {
            overflow_flag = 0;
        }
    }

    unsigned long elapsed_time = tick() - start_time - time_adjustment;

    if (overflow_flag == 2) {
        printf("Переполнение очереди! Моделирование остановлено. Длина очереди: %d\n", queue.len);
    } else {
        display_final_results(&machine, &queue, memory_used, max_queue_size);
    }

    free(queue_array);
    return elapsed_time;
}

// Функция для обработки новой заявки в очереди
void process_new_request_arr(double *total_time, struct machine *machine, struct queue *queue, struct queue_slot *array, int max_queue_size) {
    double arrival_interval = get_time(COMING_START, COMING_END);
    *total_time += arrival_interval;

    if (queue->len == 0 && *total_time > machine->time) {
        machine->downtime += *total_time - machine->time;
        machine->time = *total_time;
    }

    advance_queue_pointer(&queue->pin, array, max_queue_size);
    queue->pin->arrival_time = *total_time;
    queue->len++;
    queue->in_num++;
}

// Функция обработки заявки на аппарате
int process_request_arr(struct machine *machine, struct queue *queue, struct queue_slot *array, int array_length) 
{
    int request_processed = 0;

    queue->state += queue->len;
    machine->triggering++;
    machine->time += get_time(PROCESSING_START, PROCESSING_END);

    struct queue_slot *current_request = queue->pout;
    advance_queue_pointer(&queue->pout, array, array_length);

    if (!chance()) {  // Вероятность возвращения в очередь
        advance_queue_pointer(&queue->pin, array, array_length);
        queue->pin->arrival_time = current_request->arrival_time;
    } else {
        if (queue->len == 1) {
            queue->pin = queue->pout;
        }
        queue->total_stay_time += machine->time - current_request->arrival_time;
        machine->processed_count++;
        queue->len--;
        request_processed = 1;
    }

    return request_processed;
}
