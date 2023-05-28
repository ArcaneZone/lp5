#include <iostream>
#include <queue>
#include <omp.h>

// Structure to represent a node in the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to perform parallel Breadth First Search (BFS) on a binary tree
void parallelBFS(Node* root) {
    if (root == nullptr)
        return;

    std::queue<Node*> bfsQueue;
    bfsQueue.push(root);

    #pragma omp parallel
    {
        while (!bfsQueue.empty()) {
            #pragma omp for
            for (int i = 0; i < bfsQueue.size(); ++i) {
                Node* current = bfsQueue.front();
                bfsQueue.pop();
                std::cout << current->data << " ";

                if (current->left != nullptr)
                    bfsQueue.push(current->left);

                if (current->right != nullptr)
                    bfsQueue.push(current->right);
            }
        }
    }
}

// Function to perform parallel Depth First Search (DFS) on a binary tree
void parallelDFS(Node* node) {
    if (node == nullptr)
        return;

    std::cout << node->data << " ";

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallelDFS(node->left);
        }

        #pragma omp section
        {
            parallelDFS(node->right);
        }
    }
}

int main() {
    // Create a binary tree
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    std::cout << "Parallel BFS traversal: ";
    parallelBFS(root);
    std::cout << std::endl;

    std::cout << "Parallel DFS traversal: ";
    parallelDFS(root);
    std::cout << std::endl;

    return 0;
}
