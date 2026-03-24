#ifndef BINARY_TREE_LINKED_H
#define BINARY_TREE_LINKED_H

#include <stdio.h>

typedef struct TreeNode {
    int data;
    int year;
    char name[50];
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
    TreeNode* current;
} BinaryTree;

// Базовые операции
void init_tree(BinaryTree* tree);
void delete_tree(BinaryTree* tree);
int is_empty(BinaryTree* tree);
void make_root_current(BinaryTree* tree);
void move_to_left(BinaryTree* tree);
void move_to_right(BinaryTree* tree);
void move_to_parent(BinaryTree* tree);
int get_current_value(BinaryTree* tree);
void set_current_value(BinaryTree* tree, int value, const char* name, int year);
void create_left_child(BinaryTree* tree, int value, const char* name, int year);
void create_right_child(BinaryTree* tree, int value, const char* name, int year);

// Операции из задания
void load_ordered_tree(BinaryTree* tree, const char* filename);
void load_genealogical_tree(BinaryTree* tree, const char* filename);
void add_element(BinaryTree* tree);
void print_birthday_plan(BinaryTree* tree);
void find_sophia(BinaryTree* tree);
void find_sophia_helper(TreeNode* node, int depth, const char* path);

// Функции вывода
void print_preorder(TreeNode* node);
void print_inorder(TreeNode* node);
void print_postorder(TreeNode* node);
void print_levelorder(BinaryTree* tree);
void log_tree(FILE* log, BinaryTree* tree, int print_type);

#endif