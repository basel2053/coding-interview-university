#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

typedef struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *insertIntoBST(TreeNode *root, int val) {
  if (root == NULL) {
    root = malloc(sizeof(TreeNode));
    root->val = val;
  } else if (val > root->val) {
    root->right = insertIntoBST(root->right, val);
  } else {
    root->left = insertIntoBST(root->left, val);
  }
  return root;
}

int getCount(struct TreeNode *root) {
  if (root == NULL)
    return 0;
  return 1 + getCount(root->left) + getCount(root->right);
}

void printInOrder(TreeNode *root) {
  if (root == NULL)
    return;
  printInOrder(root->left);
  printf("%d ", root->val);
  printInOrder(root->right);
}

TreeNode *deleteTree(TreeNode *root) {
  if (root == NULL)
    return root;
  root->left = deleteTree(root->left);
  root->right = deleteTree(root->right);
  free(root);
  return root;
}

struct TreeNode *exists(TreeNode *root, int val) {
  if (root == NULL) {
    return NULL;
  }
  if (root->val == val) {
    return root;
  }
  return root->val > val ? exists(root->left, val) : exists(root->right, val);
}

int treeHeight(TreeNode *root) {
  if (root == NULL)
    return 0;
  return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

int getMax(TreeNode *root) {
  if (root == NULL)
    return 0;

  if (root->right == NULL) {
    return root->val;
  }
  return getMax(root->right);
}

int getMin(TreeNode *root) {
  if (root == NULL)
    return 0;

  if (root->left == NULL) {
    return root->val;
  }
  return getMin(root->left);
}

int getMin2(TreeNode *root) {
  TreeNode *current = root;
  while (current->left != NULL) {
    current = current->left;
  }
  return current->val;
}

int isLeaf(TreeNode *node) { return node->left == NULL && node->right == NULL; }

TreeNode *getNode(TreeNode *root, int val) {
  if (root == NULL)
    return NULL;
  if (root->val == val)
    return root;
  return root->val > val ? getNode(root->left, val) : getNode(root->right, val);
}

TreeNode *deleteNode(TreeNode *root, int key) {
  if (root == NULL) {
    return root;
  }
  if (root->val > key)
    root->left = deleteNode(root->left, key);
  else if (root->val < key)
    root->right = deleteNode(root->right, key);
  else {
    if (isLeaf(root)) {
      free(root);
      root = NULL;
    } else if (root->left == NULL) {
      TreeNode *tmp = root;
      root = root->right;
      free(tmp);
    } else if (root->right == NULL) {
      TreeNode *tmp = root;
      root = root->left;
      free(tmp);
    } else {
      // NOTE: find min in right sub-tree or max in left
      TreeNode *tmp = root->right;
      while (tmp->left != NULL) {
        tmp = tmp->left;
      }
      root->val = tmp->val;
      root->right = deleteNode(root->right, tmp->val);
    }
  }
  return root;
}

TreeNode *getSuccessor(TreeNode *root, int val) {
  if (root == NULL)
    return NULL;
  TreeNode *current = getNode(root, val);
  if (current == NULL)
    return NULL;
  if (current->right != NULL) {
    current = current->right;
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  } else {
    TreeNode *successor = NULL;
    TreeNode *ancestor = root;
    while (ancestor != current) {
      if (current->val < ancestor->val) {
        successor = ancestor;
        ancestor = ancestor->left;
      } else {
        ancestor = ancestor->right;
      }
    }
    return successor;
  }
}

// INFO: Check if its a valid BST using inorder traversal or range of values.

int main() {
  TreeNode *root = NULL;
  root = insertIntoBST(root, 5);
  root = insertIntoBST(root, 3);
  // root = insertIntoBST(root, 8);
  // root = insertIntoBST(root, 1);
  // root = insertIntoBST(root, 6);
  // root = insertIntoBST(root, 7);
  // root = insertIntoBST(root, 10);
  int nodesCount = getCount(root);
  int height = treeHeight(root);
  printf("count of nodes: %d, tree height: %d\n", nodesCount, height);
  printf("tree max value: %d, tree min value: %d\n", getMax(root),
         getMin(root));

  root = deleteNode(root, 10);
  printInOrder(root);
  return 0;
}
