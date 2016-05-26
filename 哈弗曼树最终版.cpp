#include<stdio.h>
#include<stdlib.h>
typedef struct htree
{
	int left;
	int weight;
	int right;
	int parent;
}htree; 
void inithtree(htree *t) //树初始化 已过测试 
{
	int i;
	for(i=0;i<26;i++)
	{
		t[i].left=-1;
		t[i].weight=0;
		t[i].right=-1;
		t[i].parent=-1;
	}
}
void freqchar(char *text,htree *t) //频率计算 已过测试 
{
	int i;
	for(i=0;text[i]!='#';i++)
	t[text[i]-'a'].weight++;
}
void select(htree *t,int &one_small,int &two_small,int rear)  //选择两个最小的数 已过测试 
{
    int i,min1,min2,temp;
    one_small=two_small=0;
    min1=min2=1000;
    for(i=0;i<rear;i++)
    {
        if(t[i].weight!=0&&t[i].parent==-1)
        {
            if(t[i].weight<min1)
            {
                two_small=one_small;
                min2=min1;
                one_small=i;
                min1=t[i].weight;
            }
            else if(t[i].weight<=min2)
            {
                two_small=i;
                min2=t[i].weight;
            }
        }
    }
    if(min1>min2)
    {
    	temp=one_small;
     	one_small=two_small;
        two_small=temp;
    }
}
int createhtree(htree *t) //创建哈弗曼树 已过测试 
{
	int one_small,two_small,i,rear=26,count=0;
	for(i=0;i<rear;i++)
	if(t[i].weight!=0)
		count++;
	for(i=0;i<rear;i++,rear++)
	{
	   select(t,one_small,two_small,rear);
	   t[one_small].parent=rear;
	   t[two_small].parent=rear;
	   t[rear].parent=-1;
	   t[rear].left=one_small;
	   t[rear].right=two_small;
       t[rear].weight=t[one_small].weight+t[two_small].weight;
       if(rear<count+24)
       continue;
       else break;
    }
    return rear;
}
void coding(htree *t,int head_i,char *code) //哈弗曼编码 已过测试 
{
	int i,j=0,temp_p,temp_o;
	printf("\n哈夫曼编码结果:\n");
	for(i=0;i<26;i++)
	{
		if(t[i].weight!=0)
		{
			for(temp_o=i,temp_p=t[i].parent;temp_p!=head_i;temp_o=temp_p,temp_p=t[temp_p].parent)
			{
				if(t[temp_p].left==temp_o)
				code[j++]=0;
				if(t[temp_p].right==temp_o)
				code[j++]=1;
				if(t[temp_p].parent==head_i)
				{
					if(t[head_i].left==temp_p)
					code[j++]=0;
					if(t[head_i].right==temp_p)
					code[j++]=1;
				}
			}
			printf("%c:",'a'+i);
			for(;j>0;j--)
				printf("%d",code[j-1]);
			printf("\n");
			j=0;	
		}
	}
}
void printhtree(htree *t,int head_i,int *path) //中序打印 已过测试 
{
	int i=0,j,pointer,count=0,count_r=0,rear=26;
	pointer=head_i;
	printf("\n中序遍历结果：\n");
	for(j=0;j<rear;j++)
	if(t[j].weight!=0)
		count++;
	while(i!=-1||pointer!=-1)
	{
		while(pointer!=-1)
		{
			path[++i]=pointer;
			pointer=t[pointer].left;
		}
		if(i!=-1)
		{
			pointer=path[i];
			printf("%d-",t[pointer].weight);
			if(t[pointer].left==-1&&t[pointer].right==-1)
			count_r++;
			pointer=t[pointer].right;
			i--;
		}	
		if(count_r==count)
		{
			printf("^");
			break;	
		}		
	}
}
int main()
{
	int i=0,head_i;
	char text[100];
	htree t[100];
	char code[100];
	int path[50];
 	printf("请输入要输入的字符：\n");
 	do
 	{
	 	text[i]=getchar();
	 	i++;
 	}	
 	while(text[i-1]!='#');
 	inithtree(t);
 	freqchar(text,t);
 	head_i=createhtree(t);
 	printhtree(t,head_i,path);
 	coding(t,head_i,code);
 	return 0;
}
