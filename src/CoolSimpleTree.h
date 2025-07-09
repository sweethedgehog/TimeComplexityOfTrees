#pragma once

#include <iostream>
#include <stack>

template <typename T>
class CoolSimpleTree{
private:
    class CoolNodeInt{
    public:
        T value;
        int height;
        CoolNodeInt* l;
        CoolNodeInt* r;
        
        CoolNodeInt(){
            value = NULL;
            height = 1;
            l = nullptr;
            r = nullptr;
        } //
        CoolNodeInt(T val){
            value = val;
            height = 1;
            l = nullptr;
            r = nullptr;
        } //
        CoolNodeInt(T val, CoolNodeInt* l, CoolNodeInt* r){
            value = val;
            height = 0;
            this->l = l;
            this->r = r;
        } //
        ~CoolNodeInt(){
            delete l;
            delete r;
        } //
    };
    
    CoolNodeInt* root;
    int size;
    
    int find_size(CoolNodeInt* root){
        if (!root){
            return 0;
        }
        return 1 + find_size(root->l) + find_size(root->r);
    } //
    int get_height(CoolNodeInt* node){
        return (node) ? node->height : 0;
    } //
    CoolNodeInt* InsertRec(CoolNodeInt* root, T val){
        CoolNodeInt* buffer;
        if (!root){
            return new CoolNodeInt(val);
        }
        
        if (root->value > val){
            buffer = InsertRec(root->l, val);
            if (buffer){
                root->l = buffer;
            }
            else{
                return new CoolNodeInt(val);
            }
        }
        else if (root->value < val){
            buffer = InsertRec(root->r, val);
            if (buffer){
                root->r = buffer;
            }
            else{
                return new CoolNodeInt(val);
            }
        }
        else{
            return nullptr;
        }
        
        update_height(root);
        return root;
    } //
    void update_height(CoolNodeInt* node){
        if (node){
            node->height = 1 + std::max(get_height(node->l), get_height(node->r));
        }
    } //
    
public:
    CoolSimpleTree(){
        root = nullptr;
        size = 0;
    } //
    CoolSimpleTree(T val){
        root = new CoolNodeInt(val);
        size = 1;
    } //
    CoolSimpleTree(CoolNodeInt* root){
        this->root = root;
        size = find_size(root);
    } //
    ~CoolSimpleTree(){
        delete root;
    } //
    
    int height(){
        return get_height(root);
    } //
    
    bool find(T val){
        CoolNodeInt* cur = root;
        while (cur->value != val){
            if (!cur){
                return false;
            }
            if (cur->value > val){
                cur = cur->l;
            }
            else if (cur->value < val){
                cur = cur->r;
            }
            else{
                return true;
            }
        }
    } //
    bool insert(T val){
        std::stack<CoolNodeInt*> change_h;
        CoolNodeInt* cur;
        if (!root){
            root = new CoolNodeInt(val);
            size = 1;
            return true;
        }
        cur = root;
        while (cur){
            change_h.push(cur);
            if (cur->value > val){
                    cur = cur->l;
            }
            else if (cur->value < val){
                    cur = cur->r;
            }
            else{
                return false;
            }
        }
        if (change_h.top()->value > val){
            change_h.top()->l = new CoolNodeInt(val);
        }
        else{
            change_h.top()->r = new CoolNodeInt(val);
        }
        
        while (!change_h.empty()){
            update_height(change_h.top());
            change_h.pop();
        }
        size += 1;
        return true;
    } //
    bool InsertRecursive(T val){
        CoolNodeInt* buffer = InsertRec(root, val);
        if (!buffer){
            return false;
        }
        root = buffer;
        size += 1;
        return true;
    } //
    bool remove(T val){
        CoolNodeInt* cur = root;
        std::stack<CoolNodeInt*> update_h;
        bool founded = false;
        bool deleted = false;
        if (!root){
            return false;
        }
        while (!founded && cur){
            if (cur->value > val){
                update_h.push(cur);
                cur = cur->l;
                
            }
            else if (cur->value < val){
                update_h.push(cur);
                cur = cur->r;
            }
            else{
                founded = true;
                while (!deleted){
                    if (cur->l){
                        cur->value = cur->l->value;
                        update_h.push(cur);
                        cur = cur->l;
                    }
                    else if (cur->r){
                        cur->value = cur->r->value;
                        update_h.push(cur);
                        cur = cur->r;
                    }
                    else{
                        if (!update_h.empty() && update_h.top()->l == cur){
                            update_h.top()->l = nullptr;
                        }
                        else if (!update_h.empty() && update_h.top()->r == cur){
                            update_h.top()->r = nullptr;
                        }
                        delete cur;
                        if (cur == root){
                            root = nullptr;
                        }
                        deleted = true;
                    }
                }
                size -= 1;
                while (!update_h.empty()){
                    update_height(update_h.top());
                    update_h.pop();
                }
            }
        }
        return deleted;
    } //
};
