#include<iostream>
#include "hashtable.h"

using namespace std;
int main(){

    Hashtable<int> myhashtable(20);
    
    myhashtable.insert("ankit",90);
    myhashtable.insert("deepak",190);
    myhashtable.insert("mohit",80);
    myhashtable.insert("mahesh",30);
    myhashtable.insert("rohit",70);
    myhashtable.insert("manish",492);
    myhashtable.erase("rohit");
    myhashtable.print();

    auto ptr = myhashtable.search("mahesh");
    if(ptr != NULL){
    	cout<<"found ! value = "<<*ptr<<endl;
    }
    else{
    	cout<<"Not found\n";
    }
    myhashtable["ravi"] = 40;
    myhashtable["ravi"] += 120;
    cout<<myhashtable["ankit"]<<endl;
    cout<<myhashtable["ravi"]<<endl;
    return 0;

}
