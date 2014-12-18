#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 100*1024*1024
#define END '\1'
#define BUFSIZE 400
//#define NUM 1
//#define NOL (10*1000*1000)/NUM

typedef struct tNode tNode,*ptNode;

typedef struct trieNode
{
	int i;
	ptNode ptn;
}trieNode,*ptrieNode;

struct tNode
{
	char c;
	ptrieNode ptrieN;
};

/*typedef struct ptNode
{
        int n;
        ptrieNode *ppt;
}ptNode;*/

int trie_check();
int trie_relocate(int base[],int check[],char arry[],int len,int s,int bi);
char* trie_readfile(const char *filename,long *lct);
int trie_lookup(ptrieNode pt,char *str,char result[100][6]);
void addChar(ptrieNode p,char c);
ptrieNode trie_create(char str[]);
int trie_lookup1(ptrieNode root,char *str,char result[100][6],int row);
void trie_readfile1(FILE *fp,char *arry);
void trie_insert(ptrieNode root,char *str);
void trie_destroy(ptrieNode root);

#endif
