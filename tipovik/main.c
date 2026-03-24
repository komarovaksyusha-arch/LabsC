#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked.h"
    #define Tree BinaryTree
    #define init_tree init_tree
    #define delete_tree delete_tree
    #define is_empty is_empty
    #define make_root_current make_root_current
    #define move_to_left move_to_left
    #define move_to_right move_to_right
    #define move_to_parent move_to_parent
    #define get_current_value get_current_value
    #define set_current_value set_current_value
    #define create_left_child create_left_child
    #define create_right_child create_right_child
    #define load_ordered_tree load_ordered_tree
    #define load_genealogical_tree load_genealogical_tree
    #define add_element add_element
    #define find_sophia find_sophia
    #define print_birthday_plan print_birthday_plan
    #define print_preorder(tree) print_preorder((tree)->root)
    #define print_inorder(tree) print_inorder((tree)->root)
    #define print_postorder(tree) print_postorder((tree)->root)
    #define print_levelorder print_levelorder
    #define log_tree log_tree

void show_menu() {
    printf("\nMenu:\n");
    printf("1. Load ordered tree from file\n");
    printf("2. Load genealogical tree from file\n");
    printf("3. Add element to ordered tree\n");
    printf("4. Find Sophia (Peter's granddaughter)\n");
    printf("5. Print birthday plan\n");
    printf("6. Print tree (preorder)\n");
    printf("7. Print tree (inorder)\n");
    printf("8. Print tree (postorder)\n");
    printf("9. Print tree (levelorder)\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    Tree tree;
    init_tree(&tree);
    FILE* log = fopen("tree_log.txt", "w");
    int choice;
    char filename[100];
    
    do {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter filename for ordered tree: ");
                scanf("%99s", filename);
                load_ordered_tree(&tree, filename);
                log_tree(log, &tree, 1);
                break;
                
            case 2:
                printf("Enter filename for genealogical tree: ");
                scanf("%99s", filename);
                load_genealogical_tree(&tree, filename);
                log_tree(log, &tree, 1);
                break;
                
            case 3:
                add_element(&tree);
                log_tree(log, &tree, 1);
                break;
                
            case 4:
                find_sophia(&tree);
                fprintf(log, "Searched for Sophia\n");
                break;
                
            case 5:
                print_birthday_plan(&tree);
                fprintf(log, "Printed birthday plan\n");
                break;
                
            case 6:
                printf("Preorder: ");
                print_preorder(&tree);
                printf("\n");
                fprintf(log, "Printed tree (preorder)\n");
                break;
                
            case 7:
                printf("Inorder: ");
                print_inorder(&tree);
                printf("\n");
                fprintf(log, "Printed tree (inorder)\n");
                break;
                
            case 8:
                printf("Postorder: ");
                print_postorder(&tree);
                printf("\n");
                fprintf(log, "Printed tree (postorder)\n");
                break;
                
            case 9:
                printf("Levelorder: ");
                print_levelorder(&tree);
                printf("\n");
                fprintf(log, "Printed tree (levelorder)\n");
                break;
                
            case 0:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
    
    fclose(log);
    delete_tree(&tree);
    return 0;
}