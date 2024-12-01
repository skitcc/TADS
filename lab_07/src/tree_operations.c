#include "tree_operations.h"

bst_t *create_node_bst(char *value)
{
    bst_t *new_node = malloc(sizeof(bst_t));
    if (!new_node)
    {
        return NULL;
    }

    new_node->value = strdup(value);
    if (!new_node->value)
    {
        
        free(new_node);
        return NULL;
    }

    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

avl_t *create_node_avl(const char *value)
{
    avl_t *new_node = malloc(sizeof(avl_t));
    if (!new_node)
        return NULL;

    new_node->value = strdup(value);
    if (!new_node->value)
    {
        free(new_node);
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

int max(int a, int b)
{
    return (a > b) ? a : b; 
}

int get_height(avl_t *node)
{
    if (!node)
        return 0;
    return node->height;
}

avl_t* right_rotate(avl_t *y) 
{
    avl_t *x = y->left;
    avl_t *T2 = x->right;

    // Выполняем поворот
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    y->height = 1 + max(get_height(y->left), get_height(y->right));
    x->height = 1 + max(get_height(x->left), get_height(x->right));

    // Возвращаем новый корень
    return x;
}


avl_t *left_rotate(avl_t *root)
{
    avl_t *y = root->right;
    avl_t *T2 = y->left;

    y->left = root;
    root->right = T2;

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

int get_balance(avl_t *node)
{
    if (!node)
        return 0;
    int left_height = node->left ? node->left->height : 0;
    int right_height = node->right ? node->right->height : 0;
    return left_height - right_height;
}

void *insert_avl(void *head, const char *value)
{
    printf("value in iser : %s\n", value);
    avl_t *root = head;
    if (root == NULL)
        return create_node_avl(value);
    
    int diff = strcmp(value, root->value);

    if (diff < 0)
        root->left = insert_avl(root->left, value);
    if (diff > 0)
        root->right = insert_avl(root->right, value);
    else
        return root;

    root->height = 1 + max(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);


    if (balance > 1 && strcmp(value, root->left->value) < 0)
        return right_rotate(root);

    if (balance < -1 && strcmp(value, root->right->value) > 0)
        return left_rotate(root);

    if (balance > 1 && strcmp(value, root->left->value) > 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && strcmp(value, root->right->value) < 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
    
}



void *delete_node_avl(void *head) 
{
    avl_t *root = head;
    if (!root) 
        return NULL;

    // Узел с одним или без потомков
    if (!root->left || !root->right) 
    {
        avl_t *temp = root->left ? root->left : root->right;

        // Освобождаем текущий узел
        free(root->value); // Освобождаем значение узла
        free(root);        // Освобождаем узел

        return temp;       // Возвращаем единственного потомка или NULL
    }
    else
    {
        // Узел с двумя потомками: ищем минимальный элемент в правом поддереве
        avl_t *temp = find_min_avl(root->right);
        if (!temp) 
        {
            fprintf(stderr, "Ошибка: find_min_avl вернул NULL\n");
            return root;
        }

        // Копируем значение минимального узла
        char *new_value = strdup(temp->value);
        if (!new_value) 
        {
            perror("Ошибка выделения памяти");
            exit(EXIT_FAILURE);
        }

        free(root->value); // Освобождаем старое значение
        root->value = new_value;

        // Удаляем минимальный узел
        root->right = delete_node_avl(root->right);
    }

    // Обновляем высоту
    root->height = 1 + max(get_height(root->left), get_height(root->right));

    // Балансировка
    int balance = get_balance(root);

    // LL
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);

    // LR
    if (balance > 1 && get_balance(root->left) < 0) 
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RR
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);

    // RL
    if (balance < -1 && get_balance(root->right) > 0) 
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}



void *insert_bst(void *head, char *value)
{
    bst_t *root = head;
    if (root == NULL)
    {
        return create_node_bst(value);
    }
    int diff = strcmp(value, root->value); 
    if (diff < 0)
        root->left = insert_bst(root->left, value);
    if (diff > 0)
        root->right = insert_bst(root->right, value);

    return root;
}


bst_t *delete_node_bst(bst_t *node)
{
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
    {
        bst_t *temp = node->right;
        free_node_bst(node);
        return temp;
    }
    else if (node->right == NULL)
    {
        bst_t *temp = node->left;
        free_node_bst(node);
        return temp;
    }

    else if (node->left == NULL && node->right == NULL)
    {
        free_node_bst(node);
        return NULL;
    }

    else
    {
        bst_t *min_node = find_min_bst(node->right);
        free(node->value);
        node->value = strdup(min_node->value);
        node->right = delete_node_bst(min_node);
        return node;
    }
}

void *search_node_avl(void *head, const char *value, int *comparisons)
{
    avl_t *node = head;
    if (node == NULL)
        return NULL;

    int diff = strcmp(value, node->value);    
    (*comparisons)++;
    if (diff == 0)
        return node;
    else if (diff < 0)
        return search_node_avl(node->left, value, comparisons);
    else
        return search_node_avl(node->right, value, comparisons);
}


void *search_node_bst(void *head, const char *value, int *comparisons)
{
    bst_t *node = head;
    if (node == NULL)
        return NULL;

    int diff = strcmp(value, node->value);
    (*comparisons)++;
    if (diff == 0)
        return node;
    else if (diff < 0)
        return search_node_bst(node->left, value, comparisons);
    else
        return search_node_bst(node->right, value, comparisons);
}


void prefix_traversal_bst(void *head, bool is_measuring)
{
    bst_t *root = head;
    if (root)
    {
        if (!is_measuring)
            printf("%s ", root->value);
        prefix_traversal_bst(root->left, is_measuring);
        prefix_traversal_bst(root->right, is_measuring);
    }
}

void prefix_traversal_avl(void *head, bool is_measuring)
{
    avl_t *root = head;
    if (root)
    {
        if (!is_measuring)
            printf("%s ", root->value);
        prefix_traversal_avl(root->left, is_measuring);
        prefix_traversal_avl(root->right, is_measuring);
    }
}

void inorder_store(bst_t **array, bst_t *root, int *index) 
{
    if (!root)
        return;

    inorder_store(array, root->left, index);
    array[(*index)++] = root;
    inorder_store(array, root->right, index);
}


avl_t *build_avl_tree(bst_t **array, int start, int end) 
{
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;

    avl_t *root = malloc(sizeof(avl_t));
    if (!root)
        return NULL;

    // Создаем копию значения
    root->value = strdup(array[mid]->value); // Независимая копия строки
    if (!root->value)
    {
        free(root); // Освобождаем память для узла, если strdup провалился
        return NULL;
    }

    root->left = build_avl_tree(array, start, mid - 1);
    root->right = build_avl_tree(array, mid + 1, end);

    // Высота узла
    int left_height = root->left ? root->left->height : 0;
    int right_height = root->right ? root->right->height : 0;
    root->height = 1 + (left_height > right_height ? left_height : right_height);

    return root;
}



int nodes_count(bst_t *root)
{
    if (root == NULL)
        return 0;
    return 1 + nodes_count(root->left) + nodes_count(root->right);
}

avl_t *balance_tree(bst_t *root) 
{
    if (!root)
        return NULL;

    int node_count = nodes_count(root);

    bst_t **nodes = malloc(node_count * sizeof(bst_t *));
    if (!nodes)
        return NULL;

    int index = 0;
    inorder_store(nodes, root, &index);

    avl_t *balanced_root = build_avl_tree(nodes, 0, node_count - 1);

    free(nodes);

    return balanced_root;
}


