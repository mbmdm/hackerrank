/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/

inline bool is_leaf(Node *n){
    
    if (n->left == nullptr && n->right == nullptr)
        return true;
    return false;
}

void to_array(Node* root, vector<int> &store) {
    
    if (is_leaf(root)) {
        store.push_back(root->data);
        return ;
    }
    
    if (root->left != nullptr)
        to_array(root->left, store);
    
    store.push_back(root->data);
    
    if (root->right != nullptr)
        to_array(root->right, store);    
}

bool check_array(vector<int> &v){
    
    for(int i = 1; i < v.size(); i++)
        if (v[i-1] > v[i] || v[i-1] == v[i])
            return false;
    
    return true;
}

bool checkBST(Node* root) {
        
    if (root == nullptr || is_leaf(root))
        return true;
        
    vector<int> values{};
        
    to_array(root, values);
        
    return check_array(values);        
}
