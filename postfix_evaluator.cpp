#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999
int listMaxSize;
int * list;
int length;

int shrink();

void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem){
	if(list==NULL)
	{
		initializeList();
	}
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	}
	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}

int deleteItemAt(int position){
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}

int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	shrink();
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\n\nCurrent size: %d, current length: %d\n\n", listMaxSize, length);
}

int getLength(){
	return length;
}

int insertItemAt(int pos, int item){
 	if(pos<length)
 	{
 		if (length == listMaxSize)
		{
			int *tempList;
			//allocate new memory space for tempList
			listMaxSize = 2 * listMaxSize ;
			tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
			int i;
	        for( i = 0; i < length ; i++ )
	        {
	            tempList[i] = list[i] ; //copy all items from list to tempList
	        }
	        free(list) ; //free the memory allocated before
	        list = tempList ; //make list to point to new memory
		}
		list[length] = list[pos];
		list[pos]=item;
		length++ ;
		return SUCCESS_VALUE ;
	 }
	 else {
	 	return NULL_VALUE;
	 }
}

int shrink()
{
	if(length==LIST_INIT_SIZE)
	{
		return NULL_VALUE;
	}
	else
	{
		if(2*length==listMaxSize)
		{
			int *tempList;
			//allocate new memory space for tempList
			listMaxSize =  listMaxSize/2 ;
			tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
			int i;
	        for( i = 0; i < length ; i++ )
	        {
	            tempList[i] = list[i] ; //copy all items from list to tempList
	        }
	        free(list) ; //free the memory allocated before
	        list = tempList ; //make list to point to new memory
		 	return SUCCESS_VALUE ;
    	}
		else
		{
			return NULL_VALUE;
		}
	}
}

int deleteLast()
{
	if(length>0)
	{
		length--;
		shrink();
		return SUCCESS_VALUE;
	}
	else return NULL_VALUE;
}

int clear()
{
	if(list){
		 free(list);
		 list=NULL;
		 length=0;
		 listMaxSize=0;
		 return SUCCESS_VALUE;
	 }
	else return NULL_VALUE;
}

int deleteAll(){
	if(listMaxSize==LIST_INIT_SIZE)
	{
		list[0]=list[1]=NULL;
		length=0;
	}
	else{
		free(list);
		listMaxSize=LIST_INIT_SIZE;
		list = (int*)malloc(sizeof(int)*listMaxSize) ;
	    length = 0 ;
	}
}

int postfixEvaluator(char *str){
	int listlength,value;
	int lengthOfString=strlen(str);
	for(int i=0;i<lengthOfString;i++){
		if((str[i]-'0'>=0)&&(str[i]-'0'<=9))
		{
			insertItem(str[i]-'0');
		}
		else{
			switch(str[i]){
				case '+':
					listlength=getLength();
					value=list[listlength-2]+list[listlength-1];
					deleteLast();
					deleteLast();
					insertItem(value);
					break;
				case '-':
					listlength=getLength();
					value=list[listlength-2]-list[listlength-1];
					deleteLast();
					deleteLast();
					insertItem(value);
					break;
				case '*':
					listlength=getLength();
					value=list[listlength-2]*list[listlength-1];
					deleteLast();
					deleteLast();
					insertItem(value);
					break;
				case '/':
					listlength=getLength();
					value=list[listlength-2]/list[listlength-1];
					deleteLast();
					deleteLast();
					insertItem(value);
					break;
			}
		}
	}
	int ans=list[0];
	clear();
	return ans;
}

int main(){
	initializeList();
	char str[100];
	while(1){
		scanf("%s", str);
		printf("Ans=%d\n",postfixEvaluator(str));
	}
}
