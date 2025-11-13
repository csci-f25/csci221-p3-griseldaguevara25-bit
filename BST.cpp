#include <iostream>
#include <climits> 
using namespace std;

// ===============================
// Binary Search Tree (BST) Node
// ===============================
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// =============================================
// Create a new node with the given integer data
// =============================================
struct node* newNode(int data) {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ==============================================
// Insert a new value into the BST (recursive)
// ==============================================
void insert(struct node** rootRef, int data) {
    if (*rootRef == NULL) {
        *rootRef = newNode(data);
    } else if (data <= (*rootRef)->data) {
        insert(&((*rootRef)->left), data);
    } else {
        insert(&((*rootRef)->right), data);
    }
}

// ===============================================
// Compute total number of nodes in the BST
// ===============================================
int size(struct node* root) {
    if (root == NULL) return 0;
    return size(root->left) + size(root->right) + 1;
}

// ===============================================
// Compute maximum depth (height) of the BST
// ===============================================
int maxDepth(struct node* root) {
    if (root == NULL) return 0;
    int lheight = maxDepth(root->left);
    int rheight = maxDepth(root->right);
    return (lheight > rheight ? lheight : rheight) + 1;
}

// ===============================================
// In-order traversal
// ===============================================
void printTreeInOrder(struct node* root) {
    if (root == NULL) return;
    printTreeInOrder(root->left);
    cout << root->data << " ";
    printTreeInOrder(root->right);
}

// ===============================================
// Pre-order traversal
// ===============================================
void printTreePreOrder(struct node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
}

// ===============================================
// Post-order traversal
// ===============================================
void printTreePostOrder(struct node* root) {
    if (root == NULL) return;
    printTreePostOrder(root->left);
    printTreePostOrder(root->right);
    cout << root->data << " ";
}

// ===============================================
// Lookup a value in the BST
// ===============================================
bool lookup(struct node* root, int target) {
    if (root == NULL) return false;
    if (root->data == target)
        return true;
    else if (target < root->data)
        return lookup(root->left, target);
    else
        return lookup(root->right, target);
}

// ===============================================
// Find maximum and minimum values
// ===============================================
int findMaxValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->right == NULL) return root->data;
    return findMaxValue(root->right);
}

int findMinValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->left == NULL) return root->data;
    return findMinValue(root->left);
}

struct node* findMinValueNode(struct node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return findMinValueNode(root->left);
}

int findMinValueNoRecursive(struct node* root) {
    if (root == NULL) return -1;
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}

// ===============================================
// 1. Find the kth largest element in the BST
// ===============================================
// @param root: pointer to BST root
// @param k: order number (1 = largest, 2 = 2nd largest, etc.)
// @return pointer to node that holds the kth largest value,
//         or NULL if k > number of nodes
struct node* findKthLargest(struct node* root, int k) {
    // TODO: Implement using reverse in-order traversal 
    // Hints:
    //  - Use a static or reference counter that decrements each visit.
    //  - When counter reaches 0, return the current node.
	static int count = 0;
	if(root == NULL);
	    return NULL;

struct node* right = findKthLargest(root->right, k);
	if (right != NULL) return right;

	count++;
	if(count == k)
	   return root;



    return findKthLargest(root->left, k); // placeholder
}

// ===============================================
// 2. Find minimum absolute difference between any
//     two node values in the BST
// ===============================================
// @param root: pointer to BST root
// @return smallest absolute difference between any two nodes
int getMinimumDifference(struct node* root) {
    // TODO: Implement using in-order traversal
    // Hints:
    //  - Keep track of previous nodes value (prev).
    //  - Compare abs(current - prev) at each step and update minDiff.
	static int prev = -1;
	static int minDiff = INT_MAX;

	if(root == NULL)
	   return minDiff;

	getMinimumDifference(root->left);
	if (prev != -1){
	    int diff = abs(root->data - prev);
	    if(diff <  minDiff)
	       minDiff = diff;
}
	prev = root->data;
	getMinimumDifference(root->right);

 	return minDiff; // placeholder
}

// ===============================================
// 3. Delete a node by value
// =============================================
// @param rootRef: pointer to pointer to root
// @param data: integer value to delete
// @return pointer to deleted node (if found), otherwise NULL
struct node* deleteNode(struct node** rootRef, int data) {
	if (*rootRef == NULL) return NULL;

	if (data < (*rootRef)-> data){
	      (*rootRef)->left = deleteNode(&((*rootRef)->left), data);
	}
	else if (data > (*rootRef)->data){
	    (*rootRef)->right = deleteNode(&((*rootRef)->right), data);
	}
	else {
		//found node
  	 struct node* temp = *rootRef;

	// no child
	if(temp->left == NULL && temp->right == NULL){
	    delete temp;
	    *rootRef = NULL;
	    return NULL;
}
    //one child
	else if (temp->left == NULL){
		*rootRef = temp->right;
		delete temp;
}

	else if (temp->right == NULL){
		*rootRef = temp->left;
		delete temp;
}

// two children
	else{
	    struct node* successor = findMinValueNode(temp->right);
	    temp->data = successor->data;
	    temp->right = deleteNode(&(temp->right), successor->data);

      }

   }
 return *rootRef; // placeholder
}

// ===============================================
// 4. Delete all nodes
// ===============================================
// @param rootRef: pointer to pointer to root

// @return void
void deleteTree(struct node** rootRef) {
    // TODO: Recursively delete all nodes (post-order)
    //  1. Delete left subtree.
    //  2. Delete right subtree.
    //  3. Delete current node and set root to NULL.

	if (*rootRef == NULL)
	     return;

	deleteTree(&((*rootRef)->left));
	deleteTree(&((*rootRef)->right));

	delete *rootRef;
	*rootRef = NULL;

}

int main() {
    struct node* root = NULL;

    int values[] = { -5, -4, -1, 1, 41, 20, 11, 90, 29, 32, 65, 70, 30, 75};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i)
        insert(&root, values[i]);

    cout << "In-Order: ";  printTreeInOrder(root);  cout << endl;
    cout << "Tree size: " << size(root) << ", Height: " << maxDepth(root) << endl;

    // Find kth largest
    int k = 3;
    struct node* kth = findKthLargest(root, k);
    if (kth) cout << "\n3rd largest value: " << kth->data << endl;

    // Minimum absolute difference
    cout << "Minimum absolute difference: " << getMinimumDifference(root) << endl;

    // Delete node
    cout << "\nDeleting node with value 20..." << endl;
    struct node* deleted = deleteNode(&root, 20);
    if (deleted != NULL){
      cout << "Deleted node had value: " << deleted->data << endl;
      cout << "After deletion (In-Order): ";  printTreeInOrder(root);  cout << endl;
    }

    // Cleanup all nodes
    cout << "\nDeleting all nodes..." << endl;
    deleteTree(&root);
    if(root == NULL)
      cout << "Tree successfully cleared." << endl;
    else
      cout << "Error: Tree not cleared." << endl;

    return 0;
}
