#include "linked.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_nodes(TreeNode* node) {
    if (node) {
        free_nodes(node->left);
        free_nodes(node->right);
        free(node);
    }
}

void init_tree(BinaryTree* tree) {
    tree->root = NULL;
    tree->current = NULL;
}

void delete_tree(BinaryTree* tree) {
    free_nodes(tree->root);
    tree->root = NULL;
    tree->current = NULL;
}

int is_empty(BinaryTree* tree) {
    return tree->root == NULL;
}

void make_root_current(BinaryTree* tree) {
    tree->current = tree->root;
}

void move_to_left(BinaryTree* tree) {
    if (tree->current && tree->current->left) {
        tree->current = tree->current->left;
    }
}

void move_to_right(BinaryTree* tree) {
    if (tree->current && tree->current->right) {
        tree->current = tree->current->right;
    }
}

void move_to_parent(BinaryTree* tree) {
    if (tree->current && tree->current->parent) {
        tree->current = tree->current->parent;
    }
}

int get_current_value(BinaryTree* tree) {
    return tree->current ? tree->current->data : -1;
}

void set_current_value(BinaryTree* tree, int value, const char* name, int year) {
    if (tree->current) {
        tree->current->data = value;
        tree->current->year = year;
        strncpy(tree->current->name, name, 49);
        tree->current->name[49] = '\0';
    }
}

void create_left_child(BinaryTree* tree, int value, const char* name, int year) {
    if (!tree->current) return;
    
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->year = year;
    strncpy(new_node->name, name, 49);
    new_node->name[49] = '\0';
    new_node->parent = tree->current;
    new_node->left = new_node->right = NULL;
    
    if (tree->current->left) {
        free_nodes(tree->current->left);
    }
    tree->current->left = new_node;
}

void create_right_child(BinaryTree* tree, int value, const char* name, int year) {
    if (!tree->current) return;
    
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->year = year;
    strncpy(new_node->name, name, 49);
    new_node->name[49] = '\0';
    new_node->parent = tree->current;
    new_node->left = new_node->right = NULL;
    
    if (tree->current->right) {
        free_nodes(tree->current->right);
    }
    tree->current->right = new_node;
}

// Новая функция для вставки узла в упорядоченное дерево
static void insert_ordered(BinaryTree* tree, TreeNode* new_node) {
    if (!tree->root) {
        tree->root = new_node;
        tree->current = new_node;
        return;
    }

    TreeNode* current = tree->root;
    while (1) {
        if (new_node->data < current->data) {
            if (!current->left) {
                current->left = new_node;
                new_node->parent = current;
                break;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = new_node;
                new_node->parent = current;
                break;
            }
            current = current->right;
        }
    }
}

void load_ordered_tree(BinaryTree* tree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int value, year;
    char name[50];
    
    while (fscanf(file, "%d \"%49[^\"]\" %d", &value, name, &year) == 3) {
        // Создаем новый узел
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->data = value;
        strncpy(new_node->name, name, 49);
        new_node->name[49] = '\0';
        new_node->year = year;
        new_node->left = new_node->right = NULL;

        // Вставляем в дерево
        if (!tree->root) {
            tree->root = new_node;
            continue;
        }

        TreeNode* current = tree->root;
        while (1) {
            if (value < current->data) {
                if (!current->left) {
                    current->left = new_node;
                    new_node->parent = current;
                    break;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new_node;
                    new_node->parent = current;
                    break;
                }
                current = current->right;
            }
        }
    }
    fclose(file);
}

TreeNode* read_genealogical_node(FILE* file) {
    char buffer[256];
    
    // Читаем первый токен (ID или **)
    if (fscanf(file, "%255s", buffer) != 1) {
        return NULL;
    }
    
    // Если встретили ** - это пустой узел
    if (strcmp(buffer, "**") == 0) {
        return NULL;
    }
    
    // Создаем новый узел
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    // Читаем имя
    char name[50];
    if (fscanf(file, "%49s", name) != 1) {
        free(node);
        return NULL;
    }
    
    // Читаем год рождения
    int year;
    if (fscanf(file, "%d", &year) != 1) {
        free(node);
        return NULL;
    }
    
    // Заполняем данные узла
    node->data = atoi(buffer); // ID становится значением узла
    strncpy(node->name, name, 49);
    node->name[49] = '\0';
    node->year = year;
    node->parent = NULL;
    
    // Рекурсивно читаем левого и правого потомков
    node->left = read_genealogical_node(file);
    if (node->left) {
        node->left->parent = node;
    }
    
    node->right = read_genealogical_node(file);
    if (node->right) {
        node->right->parent = node;
    }
    
    return node;
}

void load_genealogical_tree(BinaryTree* tree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    
    // Удаляем старое дерево, если было
    delete_tree(tree);
    
    // Читаем новое дерево
    tree->root = read_genealogical_node(file);
    tree->current = tree->root;
    
    fclose(file);
    
    // Проверяем корректность загрузки
    if (!tree->root) {
        printf("Warning: Tree is empty after loading\n");
    }
}

void add_element(BinaryTree* tree) {
    if (!tree) return;

    int value, year;
    char name[50];
    
    printf("Enter value (month 1-12): ");
    scanf("%d", &value);
    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter year: ");
    scanf("%d", &year);

    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->year = year;
    strncpy(new_node->name, name, 49);
    new_node->name[49] = '\0';
    new_node->left = new_node->right = NULL;

    if (!tree->root) {
        new_node->parent = NULL;
        tree->root = tree->current = new_node;
        printf("Added root: %d '%s' (%d)\n", value, name, year);
        return;
    }

    TreeNode* current = tree->root;
    while (1) {
        if (value < current->data) {
            if (!current->left) {
                new_node->parent = current;
                current->left = new_node;
                printf("Added left child to %d: %d '%s' (%d)\n", 
                      current->data, value, name, year);
                break;
            }
            current = current->left;
        } else {
            if (!current->right) {
                new_node->parent = current;
                current->right = new_node;
                printf("Added right child to %d: %d '%s' (%d)\n", 
                      current->data, value, name, year);
                break;
            }
            current = current->right;
        }
    }
}

void find_sophia_helper(TreeNode* node, int depth, const char* path) {
    if (!node || depth > 2) return;

    char new_path[256];
    if (depth == 0) {
        snprintf(new_path, sizeof(new_path), "%s", node->name);
    } else {
        snprintf(new_path, sizeof(new_path), "%s -> %s", path, node->name);
    }

    if (depth == 2 && strcmp(node->name, "Sophia") == 0) {
        printf("Sophia found as granddaughter!\n");
        printf("Year of birth: %d\n", node->year);
        printf("Family path: %s\n", new_path);
        return;
    }

    find_sophia_helper(node->left, depth + 1, new_path);
    find_sophia_helper(node->right, depth + 1, new_path);
}

void find_sophia(BinaryTree* tree) {
    if (is_empty(tree)) {
        printf("Error: Tree is empty!\n");
        return;
    }
    
    printf("Searching for Sophia...\n");
    find_sophia_helper(tree->root, 0, "");
}

void print_birthday_plan(BinaryTree* tree) {
    printf("Birthday Plan:\n");
    for (int month = 1; month <= 12; month++) {
        TreeNode* current = tree->root;
        while (current) {
            if (month == current->data) {
                printf("%02d: %s (born %d)\n", month, current->name, current->year);
                break;
            }
            current = (month < current->data) ? current->left : current->right;
        }
    }
}

void print_node_info(TreeNode* node) {
    if (!node) {
        printf("NULL");
        return;
    }
    printf("%d '%s' (%d)", node->data, node->name, node->year);
}

void print_preorder(TreeNode* node) {
    if (!node) {
        printf("NULL ");
        return;
    }
    print_node_info(node);
    printf(" ");
    print_preorder(node->left);
    print_preorder(node->right);
}

void print_inorder(TreeNode* node) {
    if (!node) {
        printf("NULL ");
        return;
    }
    print_inorder(node->left);
    print_node_info(node);
    printf(" ");
    print_inorder(node->right);
}

void print_postorder(TreeNode* node) {
    if (!node) {
        printf("NULL ");
        return;
    }
    print_postorder(node->left);
    print_postorder(node->right);
    print_node_info(node);
    printf(" ");
}

void print_levelorder(BinaryTree* tree) {
    if (!tree || !tree->root) {
        printf("Tree is empty!");
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = tree->root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        print_node_info(current);
        printf(" ");

        if (current->left) {
            queue[rear++] = current->left;
        } else {
            printf("NULL ");
        }

        if (current->right) {
            queue[rear++] = current->right;
        } else {
            printf("NULL ");
        }
    }
}

void log_tree(FILE* log, BinaryTree* tree, int print_type) {
    fprintf(log, "Tree state: ");
    switch (print_type) {
        case 1: 
            print_preorder(tree->root);
            break;
        case 2: 
            print_inorder(tree->root);
            break;
        case 3: 
            print_postorder(tree->root);
            break;
        case 4: 
            print_levelorder(tree);
            break;
    }
    fprintf(log, "\n");
}