#include "../music/word_count.h"

struct node {
    char word[WORD_SIZE];
    struct node *left;
    struct node *right;
};

typedef struct node *BSTree;

BSTree *bstree_new();
int bstree_free(BSTree *root);
int bstree_is_empty(BSTree *root);
int bstree_node_count(BSTree *root);
int bstree_height(BSTree *root);
int bstree_insert(BSTree *root, char *word);
int bstree_search(BSTree *root, char *word);
int bstree_delete(BSTree *root, char *word);
void bstree_print_preorder(BSTree *root);
void bstree_print_inorder(BSTree *root);
void bstree_print_postorder(BSTree *root);
