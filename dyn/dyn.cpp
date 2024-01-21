#include<bits/stdc++.h>

using namespace std; 

// Source : https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// An AVL tree node  
class Node  
{  
    public: 
    int val;
    int count;
    int left_count;
    Node *left;  
    Node *right;  
    int height;
};  
  
// A utility function to get the  
// height of the tree  
int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N -> height;  
}
  
/* Helper function that allocates a  
   new node with the given val and  
   NULL left and right pointers. */
Node* newNode(int val, int count)  
{  
    Node* node = new Node(); 
    node -> val = val;  
    node -> count = count;
    node -> left_count = 0;
    node -> left = NULL;  
    node -> right = NULL;  
    node -> height = 1; // new node is initially 
                        // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;
    Node *T2 = x->right;
    
    y -> left_count -= x -> left_count;
    y -> left_count -= x -> count;
    // Perform rotation  
    x -> right = y;  
    y -> left = T2;  
  
    // Update heights  
    y -> height = max(height(y -> left), 
                      height(y -> right)) + 1;  
    x -> height = max(height(x -> left), 
                      height(x -> right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node *leftRotate(Node *x)  
{  
    Node *y = x -> right;  
    Node *T2 = y -> left;  
    
    y -> left_count += x -> left_count;
    y -> left_count += x -> count;

    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x -> height = max(height(x -> left),     
                    height(x -> right)) + 1;  
    y -> height = max(height(y -> left),  
                    height(y -> right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N -> left) - height(N -> right);  
}  
  
// Recursive function to insert a val 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
Node* insert(Node* node, int left_num, int val, int count)
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL){
        return(newNode(val, count));  
    }
    
    if (left_num <= node -> left_count) {
        node -> left = insert(node -> left, left_num, val, count);
        node -> left_count += count;
    }
    else if (left_num < node -> left_count + node -> count) {
        Node tmp = *node;
        node -> count = count;
        node -> val = val;
        int split = left_num - node -> left_count;
        node -> left_count += split;
        node -> left = insert(node -> left, tmp.left_count + 1, tmp.val, split);
        node -> right = insert(node -> right, 0, tmp.val, tmp.count - split);
    }
    else if (left_num >= node -> left_count + node -> count) {
        node -> right = insert(node -> right, left_num - node -> left_count - node -> count, val, count);  
    }

    /* 2. Update height of this ancestor node */
    node -> height = 1 + max(height(node -> left),  
                        height(node -> right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && (node -> left -> right == NULL || node -> left -> left != NULL && node -> left -> left -> height > node -> left -> right -> height))  
        return rightRotate(node);
  
    // Right Right Case  
    if (balance < -1 && (node -> right -> left == NULL || node -> right -> right != NULL && node -> right -> right -> height > node -> right -> left -> height))
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && (node -> left -> left == NULL || node -> left -> right != NULL && node -> left -> right -> height > node -> left -> left -> height))
    {  
        node -> left = leftRotate(node -> left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && (node -> right -> right == NULL || node -> right -> left != NULL && node -> right -> left -> height > node -> right -> right -> height))  
    {  
        node -> right = rightRotate(node -> right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;
}
  

int fnd(Node *node, int left_num) {
    if(left_num < node -> left_count) {
        return fnd(node -> left, left_num);
    } 
    else if(left_num < node -> left_count + node -> count) {
        return node -> val;
    }
    else {
        return fnd(node -> right, left_num - node -> left_count - node -> count);
    }
}

// Driver Code 
int main()  
{  
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Node *root = NULL;
    int n;
    cin>>n;
    int num1,num2,num3;
    int prev_w = 0;
    int len = 0;
    for(int i = 0; i < n; i++) {
        char chr;
        cin>>chr;
        if(chr == 'i') {
            cin>>num1>>num2>>num3;
            root = insert(root, (num1 + prev_w) % (len + 1), num2, num3);
            len += num3;
        }
        else {
            cin>>num1;
            prev_w = fnd(root, (num1 + prev_w) % len);
            cout<<prev_w<<endl;
        }
    }
      
    return 0;  
}