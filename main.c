#include "trie.h"

//long counterfree=0;

int main(int argc, char *argv[])
{
	FILE *fp;
	char *p1=(char*)malloc(BUFSIZE),**p2=(char**)malloc(100*sizeof(char*));
	char result[100][6];
	ptrieNode pt;
	//ptrieNode *ppt=(ptrieNode*)malloc(TSIZE*sizeof(ptrieNode));
	int i, n, num, count=0;
	long l=0,m=0;
	ptrieNode root;
	
	if(argc<3) {
		printf("ERROR: No word file specified\n");
		exit(0);
	}	

    /*for(i=0;i<TSIZE;i++)
    {
        ppt[i]=NULL;
    }*/
 
	for(i=0;i<100;i++)
	{
		strcpy(result[i],"No ");
	}

        /*p1=trie_readfile(argv[1],&l);

	while(*p1!='\0')
	{
		printf("%c",*p1);
		p1++;
	}*/

	/*while(l!=-1)
	{
		p1=trie_readfile(argv[1],&l);
		pt=trie_create(p1);
		p2=trie_readfile(argv[2],&m);
		n=trie_lookup(pt,p2,result);
		count+=n;
		free(p1);
		free(p2);
		free(pt);
	}
	*/
	
	if( (fp=fopen(argv[2],"r")) == NULL )
	{
		printf("\nfile open error!\n");
		exit(0);
	}

	/*why is there an extra character '\0'?*/
	for(i=0;i<100;i++)
	{	if(feof(fp)==0)
		{
			/*p2[i]=(char*)malloc(400);*/
			p2[i]=(char*)malloc(BUFSIZE);
            trie_readfile1(fp,p2[i]);
		}
		else
		{
			p2[i]=NULL;
		}
	}

	fclose(fp);

	if( (fp=fopen(argv[1],"r")) == NULL )
	{
		printf("\nfile open error!\n");
		exit(0);
	}

	num=0;
//printf("size=%d\n",sizeof(tNode));
   //fseek(fp,224960994L,SEEK_SET);
	while(feof(fp)==0 && num<10)
	{//printf("ftell=%ld\n",ftell(fp));
		root=(ptrieNode)malloc(sizeof(trieNode));
		root->i=0;
		root->ptn=NULL;

		for(i=0;i<1000*1000;i++)
		{            
			trie_readfile1(fp,p1);
			trie_insert(root,p1);
			//free(p1);

			if(feof(fp)!=0)
			{
				break;
			}
		}

		for(i=0;i<100;i++)
		{
			if( p2[i]==NULL || p2[i][0] =='\0' )
			{
				break;
			}

			n=trie_lookup1(root,p2[i],result,i);
			count+=n;
		} 
      
		trie_destroy(root);
		/*if(root==NULL)
		{
            printf("trie deleted!\n");
        }*/
        printf("num=%d\n",num);
        //printf("counterfree=%ld\n",counterfree);
		num++;
	}

	fclose(fp);

	printf("The number of 'Yes' is %d\n",count);

	if((fp=fopen("result.dat","w")) == NULL)
	{
		printf("\nfile write error\n");
		exit(0);
	}


 
	for(i=0;i<100;i++)
	{
        //fputs(result[i],fp);    
        //fwrite(&result[i],sizeof(result[i]),1,fp);           
		fprintf(fp,"%s %d\n",result[i],i+1);
		//fflush(fp);
	}
	
	fclose(fp);
	
	system("pause");

	return 0;
    }
