#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<string>
#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
    string key;
    T value;
    Node<T> * next;

    Node(string k,T t){
        key = k;
        value = t;
        next = NULL;
    }
    ~Node(){ // not clear;
        if(next != NULL){
            delete next;
        }
    }
};


template<typename T>
class Hashtable{

    Node<T>** table;
    int current_size;
    int table_size;
    
    int hashfun(string key){
        int indx=0;
        int p=1;
        for(int i=0; i<key.length(); i++){
            indx = indx + (key[i]*p)%table_size;
            indx = indx % table_size;
            p = (p*29)%table_size;
        } 
        return indx;
    }

    void rehash(){
        Node<T>** oldTable = table;
        int old_table_size = table_size;
        table_size = 2*table_size;
        table = new Node<T>*[table_size];
        for(int i=0; i<table_size; i++){
            table[i] = NULL;

        }
        current_size = 0;
        // shift the elements from old table to new table;
        for(int i=0; i<old_table_size; i++){
            Node<T>* temp = oldTable[i];
            while(temp != NULL){
                insert(temp->key,temp->value); 
                temp = temp->next;
            }
            if(oldTable[i] != NULL){
                delete oldTable[i];
            }
        }
        delete [] oldTable;
    }

public:
    Hashtable(int ts = 19){
        table_size = ts;
        table = new Node<T>*[table_size];
        current_size = 0;
        for(int i=0; i<table_size; i++){
            table[i] = NULL;
        }
    }

    void insert(string key,T value){
        int index = hashfun(key);

        Node<T>* newnode = new Node<T>(key,value);
        // insert at the head of linklist with id = index;
        newnode->next = table[index];
        table[index] = newnode;
        ++current_size;
        //rehash
        float loadFactor = current_size/(1.0*table_size);
        if(loadFactor > 0.7){
            rehash();
        }
    }

    void print(){
        for(int i=0; i<table_size; i++){
            Node<T>* temp = table[i];
            cout<<"Bucket "<<i<<" -->";
            while(temp != NULL){
                cout<<temp->key<<"-->";
                temp = temp->next;
            }
            cout<<endl;
        }
    }
    T* search(string key){
        int index = hashfun(key);
        Node<T>* temp = table[index];
        while(temp != NULL){
            if(temp->key == key)
                return &(temp->value);
            temp = temp->next;
        }

        return NULL;

    }
    T& operator [](string key){
        T* loc = search(key);
        if(loc == NULL){
            T garbage;
            insert(key , garbage);
            loc = search(key);
        }
        return *loc;
    }
    void erase(string key){
        int index = hashfun(key);
        Node<T>* temp = table[index];
        if(table[index] == NULL){
            return;
        }
        Node<T>* prev = NULL;
        while(temp != NULL){
            if(temp->key == key){
                if(prev != NULL){
                    prev->next = temp->next;
                    temp->next = NULL;
                    delete temp;
                }
                else{
                    table[index] = temp->next;
                    temp->next = NULL;
                    delete temp;
                }
                return;
            }
            prev = temp;
        }
    }
};
#endif












