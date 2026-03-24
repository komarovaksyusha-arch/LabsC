#ifndef BINARY_TREE_ARRAY_H
#define BINARY_TREE_ARRAY_H

#include <stdio.h>

#define MAX_TREE_SIZE 1000
#define EMPTY_NODE -1

typedef struct {
    int data[MAX_TREE_SIZE];
    char names[MAX_TREE_SIZE][50];
    int years[MAX_TREE_SIZE];
    int current_index;
    int size;
} ArrayBinaryTree;

// Базовые операции
void init_array_tree(ArrayBinaryTree* tree);
void delete_array_tree(ArrayBinaryTree* tree);
int is_empty_array(ArrayBinaryTree* tree);
void make_root_current_array(ArrayBinaryTree* tree);
void move_to_left_array(ArrayBinaryTree* tree);
void move_to_right_array(ArrayBinaryTree* tree);
void move_to_parent_array(ArrayBinaryTree* tree);
int get_current_value_array(ArrayBinaryTree* tree);
void set_current_value_array(ArrayBinaryTree* tree, int value, const char* name, int year);
void create_left_child_array(ArrayBinaryTree* tree, int value, const char* name, int year);
void create_right_child_array(ArrayBinaryTree* tree, int value, const char* name, int year);

// Операции из задания
void load_ordered_array_tree(ArrayBinaryTree* tree, const char* filename);
void load_genealogical_array_tree(ArrayBinaryTree* tree, const char* filename);
void add_element_array(ArrayBinaryTree* tree);
void find_sophia_array(ArrayBinaryTree* tree);
void print_birthday_plan_array(ArrayBinaryTree* tree);

// Функции вывода
void print_array_preorder(ArrayBinaryTree* tree, int index);
void print_array_inorder(ArrayBinaryTree* tree, int index);
void print_array_postorder(ArrayBinaryTree* tree, int index);
void print_array_levelorder(ArrayBinaryTree* tree);
void log_array_tree(FILE* log, ArrayBinaryTree* tree, int print_type);

#endif