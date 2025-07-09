#pragma once


template <typename T>

class CoolRBTree{
private:
    class CoolNodeInt{
    public:
        T value;
        int color; // 0 - black, 1 - red
        int height;
        CoolNodeInt* l;
        CoolNodeInt* r;
        CoolNodeInt* parent;

        CoolNodeInt(){
            value = NULL;
            color = 1;
            height = 1;
            l = nullptr;
            r = nullptr;
            parent = nullptr;
        }
        
        CoolNodeInt(T value){
            this->value = value;
            color = 1;
            height = 1;
            l = nullptr;
            r = nullptr;
            parent = nullptr;
        } //
        CoolNodeInt(T value, CoolNodeInt* l, CoolNodeInt* r, CoolNodeInt* parent){
            this->value = value;
            color = 1;
            height = 1;
            this->l = l;
            this->r = r;
            this->parent = parent;
        } //
        ~CoolNodeInt(){
            delete l;
            delete r;
            delete parent;
        } //
    };
    CoolNodeInt* root;
    int size;
    
    void LeftRotate(CoolNodeInt* node){
        CoolNodeInt* cur = node->r;
        node->r = cur->l;
        if (cur->l){
            cur->l->parent = node;
        }
        cur->l = node;
        if (root == node){
            root = cur;
        }
        std::swap(node->color, cur->color);
        cur->parent = node->parent;
        node->parent = cur;
        if (cur->parent){
            if (cur->parent->l == node){
                cur->parent->l = cur;
            }
            else{
                cur->parent->r = cur;
            }
        }
        update_height(node);
        update_height(cur);
    } //
    void RightRotate(CoolNodeInt* node){
        CoolNodeInt* cur = node->l;
        node->l = cur->r;
        if (cur->r){
            cur->r->parent = node;
        }
        cur->r = node;
        if (root == node){
            root = cur;
        }
        std::swap(node->color, cur->color);
        cur->parent = node->parent;
        node->parent = cur;
        if (cur->parent){
            if (cur->parent->l == node){
                cur->parent->l = cur;
            }
            else{
                cur->parent->r = cur;
            }
        }
        update_height(node);
        update_height(cur);
    } //
    void LeftRightRotate(CoolNodeInt* node){
        LeftRotate(node->l);
        RightRotate(node);
    } //
    void RightLeftRotate(CoolNodeInt* node){
        RightRotate(node->r);
        LeftRotate(node);
    } //
    void ColorInvertion(CoolNodeInt* node){
        color_change(node->l);
        color_change(node->r);
        if (node != root){
            color_change(node);
        }
    } //
    CoolNodeInt* InsertRec(CoolNodeInt* root, T val){
        CoolNodeInt* buffer;
        if (root->value > val){
            if (root->l){
                buffer = InsertRec(root->l, val);
                if (buffer){
                    //root->l = buffer;
                    //buffer->parent = root;
                    if (buffer->color == 1 && root->color == 1){
                        RightRotate(root->parent);
                        ColorInvertion(root);
                    }
                }
                else{
                    return nullptr;
                }
            }
            else{
                root->l = new CoolNodeInt(val);
                buffer = root->l;
                buffer->parent = root;
                if (buffer->color == 1 && root->color == 1){
                    RightRotate(root->parent);
                    ColorInvertion(root);
                }
            }
        }
        else if (root->value < val){
            if (root->r){
                buffer = InsertRec(root->r, val);
                if (buffer){
                    //root->r = buffer;
                    //buffer->parent = root;
                    if (buffer->color == 1 && root->color == 1){
                        LeftRightRotate(root->parent);
                        ColorInvertion(root->parent);
                    }
                    else if(root->l){
                        if (root->l->color == 1 && root->r->color == 1){
                            ColorInvertion(root);
                        }
                        else if (root->r->color == 1){
                            LeftRotate(root);
                            return root->parent;
                        }
                    }
                    else{
                        LeftRotate(root);
                        return root->parent;
                    }
                }
                else{
                    return nullptr;
                }
            }
            else{
                root->r = new CoolNodeInt(val);
                buffer = root->r;
                buffer->parent = root;
                if (buffer->color == 1 && root->color == 1){
                    LeftRightRotate(root->parent);
                    ColorInvertion(root->parent);
                }
                else if(root->l){
                    if (root->l->color == 1 && root->r->color == 1){
                        ColorInvertion(root);
                    }
                    else{
                        LeftRotate(root);
                        return root->parent;
                    }
                }
                else{
                    LeftRotate(root);
                    return root->parent;
                }
            }
        }
        else if (root->value == val){
            return nullptr;
        }
        
        
        update_height(root);
        return root;
    } //
    CoolNodeInt* find(CoolNodeInt* node, T val){
        if (!node){
            return nullptr;
        }
        if (node->value > val){
            return find(node->l, val);
        }
        else if (node->value < val){
            return find(node->r, val);
        }
        else{
            return node;
        }
    }
    
    int get_height(CoolNodeInt* node){
        return node ? node->height : 0;
    } //
    void update_height(CoolNodeInt* node){
        if (node){
            node->height = 1 + std::max(get_height(node->l), get_height(node->r));
        }
    } //
    void color_change(CoolNodeInt* node){
            node->color += 1;
            node->color %= 2;
    } //
    
    void clear_tree(CoolNodeInt* node){
        if (node){
            clear_tree(node->l);
            clear_tree(node->r);
            node->parent = nullptr;
            node->l = nullptr;
            node->r = nullptr;
            delete node;
        }
    } //
    
public:
    CoolRBTree(){
        root = nullptr;
        size = 0;
    } //
    CoolRBTree(T val){
        root = new CoolNodeInt(val);
        root->color = 0;
        size = 1;
    } //
    CoolRBTree(CoolNodeInt* root){
        
    } // Пока лень реализовывать
    ~CoolRBTree(){
        clear_tree(root);
    }
    
    int height(){
        return root->height;
    } //
    
    bool insert(T val){
        if (!root){
            size = 1;
            root = new CoolNodeInt(val);
            root->color = 0;
            return true;
        }
        CoolNodeInt* buffer;
        buffer = InsertRec(root, val);
        if (!buffer){
            return false;
        }
        size += 1;
        //root = buffer;
        return true;
    }
    //bool InsertRecursive(int val); Только рекурсивная вставка (insert - рекурсивная)
    bool remove(T val); // Еще не реализовано
    bool find(T val){
        if (find(root, val)){
            return true;
        }
        return false;
    }
};

