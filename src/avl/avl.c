#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Altere o valor para 1 para ativar o modo DEBUG */
#define DEBUG 0

AVLTree *avltree_new() {
    AVLTree *root = (AVLTree*) malloc(sizeof(AVLTree));
    if (root != NULL)
        *root = NULL;

    return root;
}

void free_node(struct avl_node *node) {
    if (node == NULL)
        return;

    free_node(node->left);
    free_node(node->right);
    free(node);
    node = NULL;
}

void avltree_free(AVLTree *root) {
    if (root == NULL)
        return;

    free_node(*root);
    free(root);
}

int node_height(struct avl_node *node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

int balancefactor(struct avl_node *node) {
    return labs(node_height(node->left) - node_height(node->right));
}

int avltree_is_empty(AVLTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    return -1;
}

int avltree_node_count(AVLTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    int left_height = avltree_node_count(&((*root)->left));
    int right_height = avltree_node_count(&((*root)->right));

    return (left_height + right_height + 1);
}

int avltree_height(AVLTree *root) {
    if (root == NULL)
        return -1;
    if (*root == NULL)
        return -1;

    int left_height = avltree_height(&((*root)->left));
    int right_height = avltree_height(&((*root)->right));

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

void avltree_print_inorder(AVLTree *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        avltree_print_inorder(&((*raiz)->left));
        printf("No %s: H(%d) fb(%d)\n", (*raiz)->frequency->word, node_height(*raiz), balancefactor(*raiz));
        avltree_print_inorder(&((*raiz)->right));
    }
}

frequency_t *avltree_search(AVLTree *root, char *word) {
    if (root == NULL)
        return NULL;

    struct avl_node* current = *root;
    while (current != NULL){
        if (strcmp(word, current->frequency->word) == 0){
            return current->frequency;
        }
        if (strcmp(word, current->frequency->word) > 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return NULL;
}

/* Rotacoes */
int max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

//=================================
void RotacaoLL(AVLTree *A) { // LL
    if (DEBUG)
        printf("RotacaoLL\n");
    struct avl_node *B;
    B = (*A)->left;
    (*A)->left = B->right;
    B->right = *A;
    (*A)->height = max(node_height((*A)->left), node_height((*A)->right)) + 1;
    B->height = max(node_height(B->left), (*A)->height) + 1;
    *A = B;
}

void RotacaoRR(AVLTree *A) { // RR
    if (DEBUG)
        printf("RotacaoRR\n");
    struct avl_node *B;
    B = (*A)->right;
    (*A)->right = B->left;
    B->left = (*A);
    (*A)->height = max(node_height((*A)->left), node_height((*A)->right)) + 1;
    B->height = max(node_height(B->right), (*A)->height) + 1;
    (*A) = B;
}

void RotacaoLR(AVLTree *A) { // LR
  RotacaoRR(&(*A)->left);
  RotacaoLL(A);
}

void RotacaoRL(AVLTree *A) { // RL
  RotacaoLL(&(*A)->right);
  RotacaoRR(A);
}

/* Rotacoes */
int avltree_insert(AVLTree *root, struct frequency_t *freq) {
    int return_code;

    // Arvore vazia ou no folha
    if (*root == NULL) {
        struct avl_node *new;
        new = (struct avl_node*) malloc(sizeof(struct avl_node));
        if (new == NULL)
            return -1;

        // new->frequency = (struct frequency_t *) malloc(sizeof(struct frequency_t));
        new->frequency = freq;
        if (new->frequency == NULL)
            return -1;

        // strcpy(new->frequency->word, freq->word);
        // new->frequency->count = freq->count;
        new->height = 0;
        new->left = NULL;
        new->right = NULL;
        *root = new;
        return 1;
    }

    struct avl_node *current = *root;
    if (strcmp(freq->word, current->frequency->word) < 0) {
        if ( (return_code = avltree_insert(&(current->left), freq)) == 1) {
            if (balancefactor(current) >= 2) {
                if (strcmp(freq->word, (*root)->left->frequency->word) < 0) {
                    RotacaoLL(root);
                } else {
                    RotacaoLR(root);
                }
            }
        }
    } else {
        if (strcmp(freq->word, current->frequency->word) > 0) {
            if ( (return_code = avltree_insert(&(current->right), freq)) == 1) {
                if (balancefactor(current) >= 2) {
                    if (strcmp((*root)->right->frequency->word, freq->word) < 0) {
                        RotacaoRR(root);
                    } else {
                        RotacaoRL(root);
                    }
                }
            }
        } else {
            // printf("Valor duplicado!\n");
            if (current->frequency->count < freq->count)
                current->frequency = freq;
            return 0;
        }

    }

    current->height = max(node_height(current->left), node_height(current->right)) + 1;
    return return_code;
}

struct avl_node *search_min(struct avl_node *current) {
    struct avl_node *node1 = current;
    struct avl_node *node2 = current->left;
    while (node2 != NULL) {
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

int avltree_delete(AVLTree *root, char *word) {
    if (*root == NULL) {
        printf("Valor nao existe");
        return 0;
    }

    int return_code;
    if (strcmp(word, (*root)->frequency->word) < 0) {
        if ((return_code = avltree_delete(&(*root)->left, word)) == 1) {
            if (balancefactor(*root) >= 2) {
                if (node_height((*root)->right->left) <= node_height((*root)->right->right)) {
                    RotacaoRR(root);
                } else {
                    RotacaoRL(root);
                }
            }
        }
    }

    if (strcmp((*root)->frequency->word, word) < 0) {
        if ((return_code = avltree_delete(&(*root)->right, word)) == 1) {
            if (balancefactor(*root) >= 2) {
                if (node_height((*root)->left->right) <= node_height((*root)->left->left)) {
                    RotacaoLL(root);
                } else {
                    RotacaoLR(root);
                }
            }
        }
    }

    if (strcmp((*root)->frequency->word, word) == 0) {
        if (((*root)->left == NULL || (*root)->right == NULL)) {
            // um ou nenhum filho
            struct avl_node *oldnode = (*root);
            if ((*root)->left != NULL) {
                *root = (*root)->left;
            } else {
                *root = (*root)->right;
            }

            free(oldnode);
        } else {
            // dois filhos
            struct avl_node *temp = search_min((*root)->right);
            strcpy((*root)->frequency->word, temp->frequency->word);
            avltree_delete(&(*root)->right, (*root)->frequency->word);

            if (balancefactor(*root) >= 2) {
                if (node_height((*root)->left->right) <= node_height((*root)->left->left)) {
                    RotacaoLL(root);
                } else {
                    RotacaoLR(root);
                }
            }
        }

        if (*root != NULL)
            (*root)->height = max(node_height((*root)->left), node_height((*root)->right)) + 1;

        return 1;
    }

    (*root)->height = max(node_height((*root)->left), node_height((*root)->right)) + 1;

    return return_code;
}

void avl_merge(AVLTree *root, word_count_t *word_count) {
    for (int i = 0; i < word_count->words_inserted; i++) {
        avltree_insert(root, word_count->words[i]);
    }
}
