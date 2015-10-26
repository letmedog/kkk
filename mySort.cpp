//
//  main.cpp
//  kkk
//
//  Created by Gémeaux on 15/9/30.
//  Copyright © 2015年 bath. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <deque>
#include <fstream>
#include<stdio.h>
using namespace std;

#pragma -- Split string by an input pattern, return an string array
vector <string> split(string str, string pattern)
{
    vector<string> result;
    if(pattern.empty())
        return result;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos)
    {
        if(start!=index)
            result.push_back(str.substr(start,index-start));
        start=index+1;
        index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        result.push_back(str.substr(start));
    return result;
}

#pragma -- A class including a structure for tree sort and output the sorted data
class Trees{
    struct Tnode{
        int d;
        string code;
        string name;
        Tnode* left;
        Tnode* right;
        Tnode(int d,string code, string name):d(d),code(code),name(name),left(NULL),right(NULL){
        }
    };
    
    Tnode* root;
    
public:
    Trees(){
        root = NULL;
    }
    ~Trees(){
        clear(root);
    }
    void clear(Tnode* ptree){
        if(ptree==NULL)
            return;
        clear(ptree->left);
        clear(ptree->right);
        delete ptree;
        ptree = NULL;
    }
    void create(int i,string code,string name){
        Tnode* p=new Tnode(i,code,name);
        insert(root,p);
    }
    void insert(Tnode*& pt,Tnode* p){
        if(pt==NULL){
            pt=p;
            return;
        }
        
        if(p->d<pt->d){
            insert(pt->left,p);
          
        }
        else{
            insert(pt->right,p);
            
        }
    }
    
    void inorder(Tnode* pt){
        if(pt==NULL){
            return;
        }
        inorder(pt->left);
        cout<<" "<<pt->code<<"   "<<pt->d<<"   "<<pt->name<<endl;
        inorder(pt->right);
    }
    void disp(){
        inorder(root);
    }
};

#pragma -- main function
int main(int argc, const char * argv[]) {
    string pattern = ";";           //";" as spliter
    string data[1024][3];           //Store the valid data and being sorted
    int n = 0;                      //The nth valid line
    
    //Read files according to the names input on the command line
    for (int f = 1; f<argc; f++) {
        vector<string> result;
        //string fileName = argv[f];
        ifstream in(argv[f]);
        string line;
        
    if(in){
        while(getline(in,line)){
            
            // Check if each line of data can be splitted into 3 parts
            char s[1024];
            line.copy(s, line.length());
            int splitCheck = 0;
            for (int snum = 0; snum < line.length(); snum++) {
                if (s[snum] == ';') splitCheck++;
            }
            
            if (splitCheck == 2) {
                result = split(line, pattern); //Split current line of data by ";"
                
                // Check the empty item
                int checkFormat = 0;
                if ((result[0] == "") && (result[1] == "") && (result[2] == "")) {
                    checkFormat++;
                }
                
                // Check the duplicate item
                int checkSame = 0;
                for (int check = 0; check < n ; check++) {
                    if (data[check][0] == result[0] && data[check][1] == result[1] && data[check][1] == result[1]) {
                        checkSame++;
                    }
                }
                
                // Check if the input age is a number (Check data type)
                int checkInt = 0;
                string age = result[1];
                for (int ageNum = 0 ; ageNum<age.length(); ageNum++) {
                    if (isdigit(result[1][ageNum])){
                        checkInt++;
                    }
                }
                
                // Check if the input age is in the normal range
                int checkAge = 0;
                int a = atoi(age.c_str());
                if (a>=0 && a <= 200) {
                    checkAge++;
                }
                
                // If passing all the checking processes, store the current line to the data array
                if (checkFormat == 0 && checkSame == 0 && checkInt > 0 && checkAge > 0) {
                    for (int i = 0; i<3; i++) {
                        data[n][i] = result[i];
                    }
                    n++;    // Ready for the next item
                }
            }
        }
        in.close();//File closed
    }
    else{
        cout<<"no such file"<<endl;
    }
    }
    
   
    Trees tr;        // Initialize a Tree
    
    // Put the stored data into the Tree for sorting
    for (int i = 0; i<n; i++) {
        int age = atoi(data[i][1].c_str());
        string code = data[i][0];
        string name = data[i][2];
        tr.create(age,code,name);
    }
    cout<<" code   age    name"<<endl;
    tr.disp();      // Output the results
    cout<<endl;
    return 0;
}

