#include "trie.h"

/*int trie_check()
{
	return 0;
}*/

int trie_relocate(int base[],int check[],char arry[],int len,int s,int bi)
{
	int i,j;

	for(i=0;i<len;i++)
	{
		if(check[base[s]+arry[i]]==s)
		{
			check[bi+arry[i]]=s;
			base[bi+arry[i]]=base[base[s]+arry[i]];

			for(j=0;j<len;j++)
			{
				if(check[j]==base[s]+arry[i])
				{
					check[base[base[s]+arry[i]]+arry[j]]=bi+arry[j];
				}
			}
			
			check[base[s]+arry[i]]=-1;
		}
	}

	base[s]=bi;

	return 0;
}

char* trie_readfile(const char* filename,long *lct)
{
	FILE *fp;

	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("\nfile open error\n");
		exit(0);
	}
	else
	{
		int ts=TSIZE*sizeof(char);
		int count,i;
		char *arry=(char*)malloc(ts);

		fseek(fp,*lct,SEEK_SET);
		count=fread(arry,sizeof(char),ts-1,fp);	

		if(feof(fp)==0)
		{
			*lct=ftell(fp);
			
			for(i=count-1;i>=0;i--)
			{
				if(arry[i]=='\n')
				{
					arry[i+1]=END;
					break;
				}
			}
			(*lct)-=(count-1-i);
		}
		else
		{
			*lct=-1;
			arry[count]=END;
		}

		return arry;
	}
}

void trie_readfile1(FILE *fp,char *arry)
{
	//char *arry=(char*)malloc(4000);
	
	//printf("read file! ");

	if(fp==NULL)
	{
		printf("\nreadfile error!\n");
		exit(0);
	}

	if( fgets(arry,400,fp) == NULL && feof(fp)==0)
	{
		printf("\nreadfile error!\n");
		exit(0);
	}
	/*fgets(arry,400,fp);*/

	//printf("read file end! ");
	//return arry;
}



/*int trie_lookup(char str[],int base[],int check[])
{
	int i,s=base[0],t;

	for(i=0;str[i]!='\0';i++)
	{
		t=s+str[i];

		if(check[t]==s)
		{
			s=t;
		}
		else
		{
			printf("\nfailed to lookup\n");
			return -1;
		}
	}

	return 0;
}*/

int trie_lookup(ptrieNode root, char *str,char result[100][6])
{
	int i=0, j, k=0, flag, counter=0;
	ptrieNode pt;

	while(str[i]!=END)
	{
		pt=root;
		flag=0;

		while(str[i]!='\n'&&str[i]!=END)
		{
			if(pt==NULL)
			{
				flag=1;

				while(str[i]!='\n')
				{
					i++;
				}

				break;
			}

			for(j=0;j<pt->i;j++)
			{	
				if((pt->ptn)[j].c==str[i])
				{
					/*printf("%c",str[i]);*/
					pt=(pt->ptn)[j].ptrieN;
					goto con;
				}
			}

			flag=1;

			while(str[i]!='\n')
			{
				i++;
			}

			break;

			con:i++;
		}

		if(flag==0)
		{
			strcpy(result[k],"Yes\n");
			/*printf("%d:Yes\n",k);*/
			counter++;
		}

		k++;

		if(str[i+1]!=END)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	return counter;
}

int trie_lookup1(ptrieNode root,char *str,char result[100][6],int row)
{
	int i=0, j, flag=-1, counter=0;
	ptrieNode pt=root;

	//printf("lookup number %d! ",row);

	while(str[i]!='\n'&&str[i]!='\0')
	{
		flag=0;

		if(pt==NULL)
		{
			flag=1;
			break;
		}

		for(j=0;j<pt->i;j++)
		{	
			if((pt->ptn)[j].c==str[i])
			{
				/*printf("%c",str[i]);*/
				pt=(pt->ptn)[j].ptrieN;
				goto con;
			}
		}

		flag=1;
		break;

		con:i++;
	}

	if(flag==0)
	{
		strcpy(result[row],"Yes");
		printf("%d:Yes ",row);
		return 1;
	}

	//printf("lookup end! ");
	return 0;
}

void trie_insert(ptrieNode root,char *str)
{
	int i=0,j,k;
	ptrieNode prev,p=root;

	//printf("insert! ");

	while(str[i]!='\n'&&str[i]!='\0')
	{
		
		for(j=0;j<p->i;j++)
		{
			if((p->ptn)[j].c==str[i])
			{
				k=j;
				prev=p;
				p=(p->ptn)[j].ptrieN;
	
				goto con;
			}
		}

			
		addChar(p,str[i]);
		k=p->i-1;
			
		prev=p;
		p=NULL;

		con:if(p==NULL)
		{
			p=(prev->ptn)[k].ptrieN=(ptrieNode)malloc(sizeof(trieNode));
			p->i=0;
			p->ptn=NULL;
		}

		i++;
	}

	//printf("insert end! ");
}

void trie_destroy(ptrieNode root)
{
	int i;

	if(root==NULL)
	{
		return;
	}
	
	for(i=0;i<root->i;i++)
	{
		trie_destroy((root->ptn)[i].ptrieN);
	}
	
	free(root->ptn);
	free(root);
	
	//counterfree++;
	//printf("free! ");
	//root=NULL;
	
}

ptrieNode trie_create(char* str)
{
	ptrieNode p, prev, root=(ptrieNode)malloc(sizeof(trieNode));
	int i,j,k;

        /*p=(ptrieNode)malloc(sizeof(trieNode));*/
	root->i=0;
	root->ptn=NULL;

	for(i=0;str[i]!=END;i++)
	{printf("%c",str[i]);	
		p=root;
		/*printf("p->i:%d,str[%d]:%c\n",p->i,i,str[i]);*/

		while(str[i]!='\n'&&str[i]!=END)
		{
			/*flag=0;
			if(p==NULL)
			{
				p=(ptrieNode)malloc(sizeof(trieNode));
				p->i=0;
				p->ptn=NULL;
			}*/
			for(j=0;j<p->i;j++)
			{
				if((p->ptn)[j].c==str[i])
				{
					k=j;
					prev=p;
					p=(p->ptn)[j].ptrieN;
					/*flag=1;
					break;*/
					goto con;
				}
			}

			
			addChar(p,str[i]);
			k=p->i-1;
			/*printf("p->i:%d,str[%d]:%c,k=%d\n",p->i,i,str[i],k);*/
			prev=p;
			p=NULL;

			con:if(p==NULL)
			{
				p=(prev->ptn)[k].ptrieN=(ptrieNode)malloc(sizeof(trieNode));
				p->i=0;
				p->ptn=NULL;
			}

			i++;
		}

		if(str[i]==END)
		{
			break;
		}
	}

	return root;
}

void addChar(ptrieNode p,char c)
{
	int j;
	ptNode pt=(ptNode)malloc((p->i+1)*sizeof(tNode));

	for(j=0;j<p->i;j++)
	{
		pt[j]=(p->ptn)[j];
	}

	pt[j].c=c;
	pt[j].ptrieN=NULL;

	if(p->ptn!=NULL)
	{
		free(p->ptn);
		p->ptn=NULL;
	}

	p->ptn=pt;
	p->i++;
}


