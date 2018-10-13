#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define AlphaSize 26
using namespace std;

char boggle[10][10],word[100];
bool visited[10][10];
int rows,cols,index=0,cnt=0;

struct Trie{
    bool EOW;
    Trie* next[AlphaSize];
};

Trie* createTrieNode(){
    Trie* t=(Trie*)malloc(sizeof(Trie));
    for(int i=0;i<AlphaSize;i++)
    {
        t->next[i]=NULL;
    }
    t->EOW=false;
    return t;
}

bool insertWord(Trie* root,char* word){
    Trie *temp=root;
    for(int i=0;word[i]!='\0';i++){
        if(temp->next[(word[i]-'a')]==NULL){
            temp->next[(word[i]-'a')]=createTrieNode();
        }
        temp=temp->next[(word[i]-'a')];
    }
    if(temp->EOW==true)
        return false;
    temp->EOW=true;
    return true;
}

bool isValidWord(Trie* root,char* word)
{
    Trie *temp=root;
    for(int i=0;word[i]!='\0';i++)
    {
        if(temp->next[(word[i]-'a')]==NULL)
        {
            return false;
        }
        temp=temp->next[(word[i]-'a')];
    }
    return temp->EOW;
}
char str[30];
int idx=0;
void printTrie(Trie* root){
    Trie* temp=root;
    if(temp->EOW)
        cout<<str<<endl;
    for(int i=0;i<AlphaSize;i++){
        if(temp->next[i]!=NULL)
        {
            str[idx++]='a'+i;
            str[idx]='\0';
            printTrie(temp->next[i]);
        }
    }
    str[--idx]='\0';
}

void generateAndPrintWords(int x,int y,Trie* root, Trie* t){
    if(visited[x][y])
        return;
    word[index++]=boggle[x][y];
    word[index]='\0';
    visited[x][y]=true;
    if(strlen(word)>=3 && isValidWord(root,word)){
        insertWord(t,word);
        cnt++;
    }
    for(int i=x-1;i<=x+1;i++){
        for(int j=y-1;j<=y+1;j++){
            if((i>=0 && i<rows) && (j>=0 && j<cols)){
                generateAndPrintWords(i,j,root,t);
            }
        }
    }
    visited[x][y]=false;
    word[--index]='\0';
}

int main(){
    char word[30];
    Trie* root=createTrieNode();
    Trie* t=createTrieNode();
    FILE *fp=fopen("dictionary.txt","r");
    if(fp==NULL){
        cout<<"File Not Found!";
    }
    while(!feof(fp)){
        fscanf(fp,"%s",word);
        insertWord(root,word);
    }
    fclose(fp);
    cout<<"Number of Rows: ";
    cin>>rows;
    cols=rows;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cin>>boggle[i][j];
        }
    }
    memset(visited,false,sizeof(visited));
    cout<<endl;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            generateAndPrintWords(i,j,root,t);
        }
    }
    printTrie(t);
    cout<<endl<<"Total Words are: "<<cnt;
    return 0;
}
