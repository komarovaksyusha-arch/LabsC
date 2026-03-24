#include "array.h"
#include <stdlib.h>
#include <string.h>

void init_array_tree(ArrayBinaryTree* tree) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree->data[i] = EMPTY_NODE;
        tree->years[i] = EMPTY_NODE;
        tree->names[i][0] = '\0';
    }
    tree->current_index = 0;
    tree->size = 0;
}

void delete_array_tree(ArrayBinaryTree* tree) {
    tree->size = 0;
    tree->current_index = 0;
}

int is_empty_array(ArrayBinaryTree* tree) {
    return tree->size == 0;
}

void make_root_current_array(ArrayBinaryTree* tree) {
    tree->current_index = 0;
}

void move_to_left_array(ArrayBinaryTree* tree) {
    int left = 2 * tree->current_index + 1;
    if (left < MAX_TREE_SIZE && tree->data[left] != EMPTY_NODE) {
        tree->current_index = left;
    }
}

void move_to_right_array(ArrayBinaryTree* tree) {
    int right = 2 * tree->current_index + 2;
    if (right < MAX_TREE_SIZE && tree->data[right] != EMPTY_NODE) {
        tree->current_index = right;
    }
}

void move_to_parent_array(ArrayBinaryTree* tree) {
    if (tree->current_index > 0) {
        tree->current_index = (tree->current_index - 1) / 2;
    }
}

int get_current_value_array(ArrayBinaryTree* tree) {
    return tree->data[tree->current_index];
}

void set_current_value_array(ArrayBinaryTree* tree, int value, const char* name, int year) {
    if (tree->current_index < MAX_TREE_SIZE) {
        tree->data[tree->current_index] = value;
        tree->years[tree->current_index] = year;
        strncpy(tree->names[tree->current_index], name, 49);
        tree->names[tree->current_index][49] = '\0';
    }
}

void create_left_child_array(ArrayBinaryTree* tree, int value, const char* name, int year) {
    int left = 2 * tree->current_index + 1;
    if (left < MAX_TREE_SIZE && tree->data[left] == EMPTY_NODE) {
        tree->data[left] = value;
        tree->years[left] = year;
        strncpy(tree->names[left], name, 49);
        tree->names[left][49] = '\0';
        tree->size++;
    }
}

void create_right_child_array(ArrayBinaryTree* tree, int value, const char* name, int year) {
    int right = 2 * tree->current_index + 2;
    if (right < MAX_TREE_SIZE && tree->data[right] == EMPTY_NODE) {
        tree->data[right] = value;
        tree->years[right] = year;
        strncpy(tree->names[right], name, 49);
        tree->names[right][49] = '\0';
        tree->size++;
    }
}

void load_ordered_array_tree(ArrayBinaryTree* tree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    int value;
    while (fscanf(file, "%d", &value) == 1) {
        int current = 0;
        while (current < MAX_TREE_SIZE) {
            if (tree->data[current] == EMPTY_NODE) {
                tree->data[current] = value;
                tree->size++;
                break;
            } else if (value < tree->data[current]) {
                current = 2 * current + 1;
            } else {
                current = 2 * current + 2;
            }
        }
    }
    fclose(file);
}

static void build_genealogical_array(ArrayBinaryTree* tree, FILE* file, int index) {
    char buffer[256];
    if (fscanf(file, "%255s", buffer) != 1 || strcmp(buffer, "**") == 0) {
        return;
    }
    
    int value = atoi(buffer);
    char name[50];
    int year;
    
    if (fscanf(file, "%49s %d", name, &year) != 2) {
        return;
    }
    
    tree->data[index] = value;
    tree->years[index] = year;
    strncpy(tree->names[index], name, 49);
    tree->names[index][49] = '\0';
    tree->size++;
    
    build_genealogical_array(tree, file, 2 * index + 1);
    build_genealogical_array(tree, file, 2 * index + 2);
}

void load_genealogical_array_tree(ArrayBinaryTree* tree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    build_genealogical_array(tree, file, 0);
    fclose(file);
}

void add_element_array(ArrayBinaryTree* tree) {
    int value, year;
    char name[50];
    
    printf("Enter value: ");
    scanf("%d", &value);
    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter year: ");
    scanf("%d", &year);
    
    int current = 0;
    while (current < MAX_TREE_SIZE) {
        if (tree->data[current] == EMPTY_NODE) {
            tree->data[current] = value;
            tree->years[current] = year;
            strncpy(tree->names[current], name, 49);
            tree->names[current][49] = '\0';
            tree->size++;
            break;
        } else if (value < tree->data[current]) {
            current = 2 * current + 1;
        } else {
            current = 2 * current + 2;
        }
    }
}

void find_sophia_array(ArrayBinaryTree* tree) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        if (tree->data[i] != EMPTY_NODE && strcmp(tree->names[i], "Peter") == 0) {
            // Проверяем детей
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;
            
            // Проверяем внуков слева
            if (left_child < MAX_TREE_SIZE && tree->data[left_child] != EMPTY_NODE) {
                int left_grandchild = 2 * left_child + 1;
                if (left_grandchild < MAX_TREE_SIZE && tree->data[left_grandchild] != EMPTY_NODE && 
                    strcmp(tree->names[left_grandchild], "Sophia") == 0) {
                    printf("Sophia found! Year of birth: %d\n", tree->years[left_grandchild]);
                    return;
                }
                
                int right_grandchild = 2 * left_child + 2;
                if (right_grandchild < MAX_TREE_SIZE && tree->data[right_grandchild] != EMPTY_NODE && 
                    strcmp(tree->names[right_grandchild], "Sophia") == 0) {
                    printf("Sophia found! Year of birth: %d\n", tree->years[right_grandchild]);
                    return;
                }
            }
            
            // Проверяем внуков справа
            if (right_child < MAX_TREE_SIZE && tree->data[right_child] != EMPTY_NODE) {
                int left_grandchild = 2 * right_child + 1;
                if (left_grandchild < MAX_TREE_SIZE && tree->data[left_grandchild] != EMPTY_NODE && 
                    strcmp(tree->names[left_grandchild], "Sophia") == 0) {
                    printf("Sophia found! Year of birth: %d\n", tree->years[left_grandchild]);
                    return;
                }
                
                int right_grandchild = 2 * right_child + 2;
                if (right_grandchild < MAX_TREE_SIZE && tree->data[right_grandchild] != EMPTY_NODE && 
                    strcmp(tree->names[right_grandchild], "Sophia") == 0) {
                    printf("Sophia found! Year of birth: %d\n", tree->years[right_grandchild]);
                    return;
                }
            }
        }
    }
    printf("Sophia not found as granddaughter of Peter\n");
}

void print_birthday_plan_array(ArrayBinaryTree* tree) {
    printf("Birthday Plan:\n");
    for (int month = 1; month <= 12; month++) {
        int current = 0;
        while (current < MAX_TREE_SIZE && tree->data[current] != EMPTY_NODE) {
            if (month == tree->data[current]) {
                printf("%02d: %s\n", month, tree->names[current]);
                break;
            } else if (month < tree->data[current]) {
                current = 2 * current + 1;
            } else {
                current = 2 * current + 2;
            }
        }
    }
}

void print_array_preorder(ArrayBinaryTree* tree, int index) {
    if (index >= MAX_TREE_SIZE || tree->data[index] == EMPTY_NODE) {
        printf("** ");
        return;
    }
    
    printf("%d(%s) ", tree->data[index], tree->names[index]);
    print_array_preorder(tree, 2 * index + 1);
    print_array_preorder(tree, 2 * index + 2);
}

void print_array_inorder(ArrayBinaryTree* tree, int index) {
    if (index >= MAX_TREE_SIZE || tree->data[index] == EMPTY_NODE) {
        printf("** ");
        return;
    }
    
    print_array_inorder(tree, 2 * index + 1);
    printf("%d(%s) ", tree->data[index], tree->names[index]);
    print_array_inorder(tree, 2 * index + 2);
}

void print_array_postorder(ArrayBinaryTree* tree, int index) {
    if (index >= MAX_TREE_SIZE || tree->data[index] == EMPTY_NODE) {
        printf("** ");
        return;
    }
    
    print_array_postorder(tree, 2 * index + 1);
    print_array_postorder(tree, 2 * index + 2);
    printf("%d(%s) ", tree->data[index], tree->names[index]);
}

void print_array_levelorder(ArrayBinaryTree* tree) {
    if (tree->size == 0) return;
    
    int queue[MAX_TREE_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        printf("%d(%s) ", tree->data[current], tree->names[current]);
        
        int left = 2 * current + 1;
        if (left < MAX_TREE_SIZE && tree->data[left] != EMPTY_NODE) {
            queue[rear++] = left;
        } else {
            printf("** ");
        }
        
        int right = 2 * current + 2;
        if (right < MAX_TREE_SIZE && tree->data[right] != EMPTY_NODE) {
            queue[rear++] = right;
        } else {
            printf("** ");
        }
    }
}

void log_array_tree(FILE* log, ArrayBinaryTree* tree, int print_type) {
    fprintf(log, "Array Tree state: ");
    switch (print_type) {
        case 1: print_array_preorder(tree, 0); break;
        case 2: print_array_inorder(tree, 0); break;
        case 3: print_array_postorder(tree, 0); break;
        case 4: print_array_levelorder(tree); break;
    }
    fprintf(log, "\n");
}