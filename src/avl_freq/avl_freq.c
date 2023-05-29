#include "avl_freq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Altere o valor para 1 para ativar o modo DEBUG */
#define DEBUG 0

#define FOUND_SIZE 1024

AVLFreqTree *avlfreqtree_new() {
    AVLFreqTree *root = (AVLFreqTree *)malloc(sizeof(AVLFreqTree));
    if (root != NULL)
        *root = NULL;

    return root;
}

void avlfreq_free_node(struct avlfreq_node *node) {
    if (node == NULL)
        return;

    avlfreq_free_node(node->left);
    avlfreq_free_node(node->right);
    free(node);
    node = NULL;
}

void avlfreqtree_free(AVLFreqTree *root) {
    if (root == NULL)
        return;

    avlfreq_free_node(*root);
    free(root);
}

int avlfreq_node_height(struct avlfreq_node *node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

int avlfreq_balancefactor(struct avlfreq_node *node) {
    return labs(avlfreq_node_height(node->left) - avlfreq_node_height(node->right));
}

int avlfreqtree_is_empty(AVLFreqTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    return -1;
}

int avlfreqtree_node_count(AVLFreqTree *root) {
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    int left_height = avlfreqtree_node_count(&((*root)->left));
    int right_height = avlfreqtree_node_count(&((*root)->right));

    return (left_height + right_height + 1);
}

int avlfreqtree_height(AVLFreqTree *root) {
    if (root == NULL)
        return -1;
    if (*root == NULL)
        return -1;

    int left_height = avlfreqtree_height(&((*root)->left));
    int right_height = avlfreqtree_height(&((*root)->right));

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

void avlfreqtree_print_inorder(AVLFreqTree *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        avlfreqtree_print_inorder(&((*raiz)->left));
        printf("No %s: H(%d) fb(%d) %d\n", (*raiz)->frequency->word, avlfreq_node_height(*raiz), avlfreq_balancefactor(*raiz), (*raiz)->frequency->count);
        avlfreqtree_print_inorder(&((*raiz)->right));
    }
}

frequency_t **avlfreqtree_search(AVLFreqTree *root, int frequency, int *ammount) {
    if (root == NULL)
        return NULL;

    avlfreqtree_print_inorder(root);
    *ammount = 0;

    struct avlfreq_node* current = *root;
    frequency_t **found = malloc(FOUND_SIZE * sizeof(frequency_t *));
    while (current != NULL){
        if (current->frequency->count < frequency) {
            current = current->right;
        } else if (current->frequency->count > frequency) {
            current = current->left;
        } else {
            while (1) {
                if (!current || current->frequency->count != frequency)
                    break;

                found[*ammount] = current->frequency;
                *ammount += 1;
                current = current->left;
            }
            // return found;
        }

    }
    return found;
}

/* Rotacoes */
int avlfreq_max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

//=================================
void AVLFreqRotacaoLL(AVLFreqTree *A) { // LL
    if (DEBUG)
        printf("AVLFreqRotacaoLL\n");
    struct avlfreq_node *B;
    B = (*A)->left;
    (*A)->left = B->right;
    B->right = *A;
    (*A)->height = avlfreq_max(avlfreq_node_height((*A)->left), avlfreq_node_height((*A)->right)) + 1;
    B->height = avlfreq_max(avlfreq_node_height(B->left), (*A)->height) + 1;
    *A = B;
}

void AVLFreqRotacaoRR(AVLFreqTree *A) { // RR
    if (DEBUG)
        printf("AVLFreqRotacaoRR\n");
    struct avlfreq_node *B;
    B = (*A)->right;
    (*A)->right = B->left;
    B->left = (*A);
    (*A)->height = avlfreq_max(avlfreq_node_height((*A)->left), avlfreq_node_height((*A)->right)) + 1;
    B->height = avlfreq_max(avlfreq_node_height(B->right), (*A)->height) + 1;
    (*A) = B;
}

void AVLFreqRotacaoLR(AVLFreqTree *A) { // LR
  AVLFreqRotacaoRR(&(*A)->left);
  AVLFreqRotacaoLL(A);
}

void AVLFreqRotacaoRL(AVLFreqTree *A) { // RL
  AVLFreqRotacaoLL(&(*A)->right);
  AVLFreqRotacaoRR(A);
}

/* Rotacoes */
int avlfreqtree_insert(AVLFreqTree *root, struct frequency_t *freq) {
    int return_code;

    // Arvore vazia ou no folha
    if (*root == NULL) {
        struct avlfreq_node *new;
        new = (struct avlfreq_node*) malloc(sizeof(struct avlfreq_node));
        if (new == NULL)
            return -1;

        new->frequency = freq;
        if (new->frequency == NULL)
            return -1;

        new->height = 0;
        new->left = NULL;
        new->right = NULL;
        *root = new;
        return 1;
    }

    struct avlfreq_node *current = *root;
    if (freq->count <= current->frequency->count) {
        if ( (return_code = avlfreqtree_insert(&(current->left), freq)) == 1) {
            if (avlfreq_balancefactor(current) >= 2) {
                if (freq->count <= (*root)->left->frequency->count) {
                    AVLFreqRotacaoLL(root);
                } else {
                    AVLFreqRotacaoLR(root);
                }
            }
        }
    } else {
        if (freq->count > current->frequency->count) {
            if ( (return_code = avlfreqtree_insert(&(current->right), freq)) == 1) {
                if (avlfreq_balancefactor(current) >= 2) {
                    if ((*root)->right->frequency->count < freq->count) {
                        AVLFreqRotacaoRR(root);
                    } else {
                        AVLFreqRotacaoRL(root);
                    }
                }
            }
        } else {
            return 0;
        }
        if (current->frequency->count < freq->count)
            current->frequency = freq;
    }

    current->height = avlfreq_max(avlfreq_node_height(current->left), avlfreq_node_height(current->right)) + 1;
    return return_code;
}

struct avlfreq_node *avlfreq_search_min(struct avlfreq_node *current) {
    struct avlfreq_node *node1 = current;
    struct avlfreq_node *node2 = current->left;
    while (node2 != NULL) {
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

void avlfreq_merge(AVLFreqTree *root, word_count_t *word_count) {
    for (int i = 0; i < word_count->words_inserted; i++) {
        avlfreqtree_insert(root, word_count->words[i]);
    }
}

