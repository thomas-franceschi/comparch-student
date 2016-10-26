/*
 * btree-rand.c
 *
 *  Created on: Sep 21, 2016
 *      Author: Jay Brockman
 */

#include "mipslib.h"
#define NULL 0
#define SIZE 1000

struct treeNode {
  int value;
  struct treeNode *left, *right;
};

struct treeNode *root = NULL;
int m_w = 1, m_z = 2;

// 32-bit random number generator by George Marsaglia
// https://programmingpraxis.com/2010/10/05/george-marsaglias-random-number-generators/
int randInt() {
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  return (m_z << 16) + m_w;
}

struct treeNode* createNode(unsigned val) {
  struct treeNode *newNode;
  newNode = (struct treeNode *) malloc(sizeof (struct treeNode));
  newNode->value = val;
  newNode->left = NULL;
  newNode->right = NULL;
  return(newNode);
}

void insert(struct treeNode **node, int data) {
  if (*node == NULL) {
    *node = createNode(data);
  }
  else if (data < (*node)->value) {
    insert(&(*node)->left, data);
  }
  else if (data > (*node)->value) {
    insert(&(*node)->right, data);
  }
}

void inOrder(struct treeNode *node) {
  if (node != NULL) {
    inOrder(node->left);
    //printf("%d\n", node->value);
    inOrder(node->right);
  }
  return;
}

int main()
{
  int i;
  for (i = 0;  i < SIZE;  i++)
    insert(&root, randInt());
  inOrder(root);
  return 0;
}
