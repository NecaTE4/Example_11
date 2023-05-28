//150120053
//Necati Koçak
// NOTE : I did only AVL Tree. I couldn't do splay tree.
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int timeunitAVL = 0; //I assigned this variable globally to calculate time cost

//I created a node, there are left and right children and data in it
struct NODEAVL {
    int data;
    struct NODEAVL *left;
    struct NODEAVL *right;
}*root;

typedef struct NODEAVL node_avl;

int height(node_avl *node); //This function takes the height of the incoming node's children and increases them by one, whichever is maximum, and returns the resulting value.
int diff(node_avl *node); //In this function, starting from the node value, it compares the depths of its sub-nodes and finds and returns the balance factor.
node_avl *rr_rotation(node_avl *parent); //This function performs a right to right turn on a given node's parent and its right child node to balance the tree.
node_avl *ll_rotation(node_avl *parent); //This function performs a left to left turn on a given node's parent and its left child node to balance the tree.
node_avl *lr_rotation(node_avl *parent); //Using the given node's parent and the left child of this node, this function rotates left right to achieve balance.
node_avl *rl_rotation(node_avl *parent); //Using the given node's parent and the right child of this node, this function rotates right left to achieve balance.
node_avl *balance(node_avl *node); //This function calls the rotation functions necessary to balance the tree using the given node and its child nodes.
node_avl *insert(node_avl *node, int value); //This function adds the entered data to the appropriate place by creating a new node.
void preorder(node_avl *node); //This function preorders the typed avl tree recursively


// Height calculate
int height(node_avl *node) {
    int h = 0;
    if (node != NULL) {
        int l_height = height(node->left);
        int r_height = height(node->right);
        int max_height = l_height > r_height ? l_height : r_height;
        h = max_height + 1;
    }
    return h;
}

// Height Calculate for balance
int diff(node_avl *node) {
    int l_height = height(node->left);
    int r_height = height(node->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

// Right - Right Rotation (Single Left Rotation)
node_avl *rr_rotation(node_avl *parent) {
    node_avl *node = parent->right;
    parent->right = node->left;
    node->left = parent;
    timeunitAVL++;
    return node;
}


//Left - Left Rotation (Single Right Rotation)
node_avl *ll_rotation(node_avl *parent) {
    node_avl *node = parent->left;
    parent->left = node->right;
    node->right = parent;
    timeunitAVL++;
    return node;
}


//Left - Right Rotation
node_avl *lr_rotation(node_avl *parent) {
    node_avl *node = parent->left;
    parent->left = rr_rotation(node);
    return ll_rotation(parent);
}


//Right- Left Rotation
node_avl *rl_rotation(node_avl *parent)
{
    node_avl *node = parent->right;
    parent->right = ll_rotation(node);
    return rr_rotation(parent);
}


//Balancing AVL Tree
node_avl* balance(node_avl *node) {
    int b_factor = diff(node);
    if (b_factor > 1) {
        if (diff(node->left) > 0) {
            node = ll_rotation(node);
        } else {
            node = lr_rotation(node);
        }
    } else if (b_factor < -1) {
        if (diff(node->right) > 0) {
            node = rl_rotation(node);
        } else {
            node = rr_rotation(node);
        }
    }
    return node;
}


//Insert element into the tree
node_avl* insert(node_avl *node, int value) {

    if (node == NULL) {
        node_avl *temp = (node_avl *) malloc(sizeof(node_avl));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if (value < node->data) {
        timeunitAVL++;
        node->left = insert(node->left, value);
        node = balance(node);
    } else if (value > node->data) {
        timeunitAVL++;
        node->right = insert(node->right, value);
        node = balance(node);
    }else
    {
        timeunitAVL++;
        return node;
    }

    return node;
}

//Preorder Traversal of AVL Tree
void preorder(node_avl *node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}


int main(int argc,char* argv[]) {
    {
        if (argc == 1)
            printf("Error message!");
        if (argc >= 2) {
            FILE *fp = fopen(argv[1], "r");
            // Open the file for reading
            if (fp == NULL) {
                perror("Error opening file");
                return 0;
            }

            // Read the numbers from the file and store them in an array
            int numbers[SIZE];
            int i = 0;
            while (fscanf(fp, "%d", &numbers[i]) == 1) {
                i++;
            }

            // Close the file
            fclose(fp);

            // Insert the array to AVL tree
            int j;
            for (j = 0; j < i; j++) {
                root = insert(root, numbers[j]);

            }
            printf("\n");

            printf("Preorder Traversal AVL:\n");
            preorder(root);
            printf("\n");
            printf("TimeUnit AVL:\n");
            printf("%d", timeunitAVL);

        }
    }
}
