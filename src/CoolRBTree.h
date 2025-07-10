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
    
    CoolNodeInt* RC_tree_change(CoolNodeInt* cur, CoolNodeInt* node){
        if (cur->color == 1 && node->color == 1){
            LeftRightRotate(node->parent);
            ColorInvertion(cur);
            update_height(node);
            update_height(cur);
            return cur;
        }
        else if(node->l){
            if (node->l->color == 1 && node->r->color == 1){
                ColorInvertion(node);
                update_height(cur);
                update_height(node);
                return node;
            }
            else if (cur->color == 1){
                LeftRotate(node);
                update_height(node);
                update_height(cur);
                return cur;
            }
            else{
                update_height(cur);
                update_height(node);
                return node;
            }
        }
        else{
            LeftRotate(node);
            update_height(node);
            update_height(cur);
            return cur;
        }
    }

    CoolNodeInt* LC_tree_change(CoolNodeInt* cur, CoolNodeInt* node){
        if (cur->color == 1 && node->color == 1){
            RightRotate(node->parent);
            ColorInvertion(node);
        }
        update_height(cur);
        update_height(node);
        return node;
    }
    
    CoolNodeInt* InsertRec(CoolNodeInt* root, T val){
        CoolNodeInt* buffer;
        if (root->value > val){
            if (root->l){
                buffer = InsertRec(root->l, val);
                if (buffer){
                    root = buffer->parent;
                    if (!root){
                        update_height(buffer);
                        return buffer;
                    }
                    if (root->l == buffer){
                        return LC_tree_change(buffer, root);
                    }
                    else{
                        return RC_tree_change(buffer, root);
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
                return LC_tree_change(buffer, root);
            }
        }
        else if (root->value < val){
            if (root->r){
                buffer = InsertRec(root->r, val);
                if (buffer){
                    root = buffer->parent;
                    if (!root){
                        update_height(buffer);
                        return buffer;
                    }
                    if (root->l == buffer){
                        return LC_tree_change(buffer, root);
                    }
                    else{
                        return RC_tree_change(buffer, root);
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
                return RC_tree_change(buffer, root);
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
        return get_height(root);
    } //
    bool insert(T val){
        if (!root){
            root = new CoolNodeInt(val);
            size = 1;
            root->color = 0;
            return true;
        }
        CoolNodeInt* cur = root;
        CoolNodeInt* node;
        //std::stack<CoolNodeInt*> path;
        while (cur){
            if (cur->value > val){
                //path.push(cur);
                if (cur->l){
                    cur = cur->l;
                }
                else{
                    cur->l = new CoolNodeInt(val);
                    cur->l->parent = cur;
                    cur = cur->l;
                    break;
                }
            }
            else if (cur->value < val){
                //path.push(cur);
                if (cur->r){
                    cur = cur->r;
                }
                else{
                    cur->r = new CoolNodeInt(val);
                    cur->r->parent = cur;
                    cur = cur->r;
                    break;
                }
            }
            else{
                return false;
            }
        }
        while (cur->parent){
            node = cur->parent;
            if (cur == node->l){
                cur = LC_tree_change(cur, node);
            }
            else{
                cur = RC_tree_change(cur, node);
            }
        }
        update_height(cur);
        size += 1;
        return true;
    }
    bool InsertRecursive(T val){
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
    
    bool remove(T val); // Еще не реализовано
    bool find(T val){
        if (find(root, val)){
            return true;
        }
        return false;
    }
};

