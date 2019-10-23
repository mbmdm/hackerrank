    bool lca_contains(Node *root, int v){
        
        if (root == nullptr) return false;
        else if (root->data == v) return true;
        else if (root == nullptr) return false;
        else{
            bool flag = lca_contains(root->left, v);
            if (flag) return true;
            return lca_contains(root->right, v);
        }
    }
  
    Node *lca(Node *root, int v1, int v2) {

        if (root->data == v1 || root->data == v2)
            return root;

        bool f1 = lca_contains(root->left, v1);
        bool f2 = lca_contains(root->left, v2);

        if (f1 && f2)
            return lca(root->left, v1, v2);

        else if (f1 || f2) 
            return root;
        
        else //(f1 == false && f2 == false)
            return lca(root->right, v1, v2);
    }