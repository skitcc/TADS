#include "utils.h"


void free_tree_bst(void *head)
{
    bst_t *root = head;
    // printf("%p\n", (void *)root);
    if (root)
    {
        free_tree_bst(root->left);
        free_tree_bst(root->right);
        free(root->value);
        free(root);
    }
}

void free_tree_avl(void *head)
{
    avl_t *root = head;
    if (root)
    {
        free_tree_avl(root->left);
        free_tree_avl(root->right);
        free(root->value);
        free(root);
    }
}

void print_tree(avl_t *root, int depth, const char *relation) 
{
    if (root) 
    {
        for (int i = 0; i < depth; i++) 
            printf("  ");
        printf("[%s] %s\n", relation, root->value);
        print_tree(root->left, depth + 1, "son");
        print_tree(root->right, depth, "brother");
    }
}


void debug_tree_structure(bst_t *root)
{
    if (root)
    {
        printf("Node: %s\n", root->value);
        if (root->left)
            printf("  Left: %s\n", root->left->value);
        if (root->right)
            printf("  Right: %s\n", root->right->value);

        debug_tree_structure(root->left);
        debug_tree_structure(root->right);
    }
}

void print_mas(char **mas, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s ", mas[i]);
    }
    printf("\n");
}

void free_node_bst(bst_t *node)
{
    if (node)
    {
        free(node->value);
        free(node);
        node = NULL;
    }
}

void free_node_avl(avl_t *node)
{
    if (node)
    {
        free(node->value);
        free(node);
        node = NULL;
    }
}


bst_t *find_min_bst(bst_t *root) 
{
    while (root && root->left)
        root = root->left;
    return root;
}

avl_t *find_min_avl(avl_t *root) 
{
    while (root && root->left)
        root = root->left;
    return root;
}

void free_mas(char **mas, int len)
{
    if (mas == NULL)
        return;
    for (int i = 0; i < len; i++)
    {
        free(mas[i]);
        mas[i] = NULL;
    }
    free(mas);
}

void gen_data_file(const char *filename, int len)
{
    if (len > MAX_LEN_FILE)
    {
        PRINT_COLOR(RED, "Максимальное кол-во элементов превышено! (10000)\n");
    }
    srand(time(NULL));

    FILE *file = fopen(filename, "w");

    if (!file)
        return;

    int *numbers = malloc(len * sizeof(int));
    if (!numbers) 
    {
        fclose(file);
        return;
    }

    for (int i = 0; i < len; i++) 
        numbers[i] = i + 1;
    

    for (int i = len - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    for (int i = 0; i < len; i++) 
        fprintf(file, "%d\n", numbers[i]);
    
    free(numbers);
    fclose(file);
}

int clean_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
        return 1;
    fclose(file);
    return 0;
}


