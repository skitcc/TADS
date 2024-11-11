#include "list.h"



// Функция моделирования обслуживания заявок с использованием списка
unsigned long simulate_service_list(struct mem_slot **mem, int *memory_used) 
{
    struct queue queue = { .pin = NULL, .pout = NULL, .len = 0, .in_num = 0, .state = 0, .max = 0, .total_stay_time = 0 };
    struct machine machine = { .time = 0, .downtime = 0, .processed_count = 0, .triggering = 0 };

    double total_time = 0;
    int process_status = 0;

    printf("\nМоделирование с использованием списка:\n\n");

    unsigned long start_time = tick(), time_adjustment = 0, temp_time = 0;

    while (machine.processed_count < TOTAL_NEED) {
        // Обрабатываем новые заявки в очереди
        while (queue.len == 0 || machine.time > total_time) {
            process_new_request_list(&total_time, &queue, &machine, mem);
        }

        process_status = process_request_list(&machine, &queue, mem);
        
        // Вывод промежуточной информации
        temp_time = tick();
        if (process_status && machine.processed_count % INTER_NEED == 0) {
            display_interim_results(&machine, &queue);
        }
        time_adjustment += tick() - temp_time;

        if (process_status) {
            process_status = 0;
        }
    }

    unsigned long elapsed_time = tick() - start_time - time_adjustment;

    double expected_time = calculate_expected_model_time();
    *memory_used = queue.max * sizeof(struct queue_slot);

    display_final_results(&machine, &queue, memory_used, queue.max);

    return elapsed_time;
}

// Обработка новой заявки
void process_new_request_list(double *total_time, struct queue *queue, struct machine *machine, struct mem_slot **mem) 
{
    double arrival_interval = get_time(COMING_START, COMING_END);
    *total_time += arrival_interval;

    // Если очередь пуста, обновляем время простоя машины
    if (queue->len == 0 && *total_time > machine->time) {
        machine->downtime += *total_time - machine->time;
        machine->time = *total_time;
    }

    // Создаем новую заявку и добавляем ее в очередь
    struct queue_slot *new_request = malloc(sizeof(struct queue_slot));
    if (queue->pin != NULL) {
        queue->pin->next = new_request;
    }
    new_request->next = NULL;
    new_request->arrival_time = *total_time;
    queue->pin = new_request;

    if (queue->len == 0) {
        queue->pout = new_request;
    }
    queue->len++;
    queue->in_num++;
    add_mem(new_request, mem);
}

// Обработка заявки на аппарате
int process_request_list(struct machine *machine, struct queue *queue, struct mem_slot **mem) 
{
    int processed = 0;

    queue->state += queue->len;
    if (queue->len > queue->max) {
        queue->max = queue->len;
    }

    machine->triggering++;
    machine->time += get_time(PROCESSING_START, PROCESSING_END);

    struct queue_slot *current_request = queue->pout;
    if (queue->len > 1) {
        queue->pout = current_request->next;
    }

    if (!chance()) {  // Вероятность возвращения в очередь
        queue->pin->next = current_request;
        queue->pin = current_request;
        current_request->next = NULL;
    } else {
        // Заявка завершена, удаляем из очереди
        if (queue->len == 1) {
            queue->pin = queue->pout = NULL;
        }
        queue->total_stay_time += machine->time - current_request->arrival_time;
        machine->processed_count++;
        queue->len--;
        delete_mem(current_request, *mem);
        free(current_request);

        processed = 1;
    }
    return processed;
}

// Отображение используемой памяти
void show_memory_usage(struct mem_slot **mem) 
{
    struct mem_slot *current = *mem, *temp;

    if (current == NULL) {
        printf("\nДля данной операции необходимо использовать модель списка.\n\n");
    } else {
        printf("Использование памяти:\n+ - память используется\n- - память не используется\n");

        int count = 0;
        while (current != NULL && count < 80) {
            printf("%p ", (void*)current->queue_slot);
            printf(current->busy ? "+\n" : "-\n");

            temp = current;
            current = current->next;
            free(temp);
            count++;
        }
        *mem = NULL;
    }
}

// Функция освобождения памяти для списка
void free_memory_list(struct mem_slot **mem) 
{
    struct mem_slot *current = *mem, *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *mem = NULL;
}