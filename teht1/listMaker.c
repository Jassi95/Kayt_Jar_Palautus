#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listMaker.h"

/*using a linked stack and not a list for easy reversing */
void addStack(char *cur_row, node **top){
  node *newNode;
//if first node
  if ((newNode = malloc(sizeof(node)))==NULL){
    fprintf(stderr, "Malloc failed");
    exit(1);
  }
  strcpy(newNode->row, cur_row); //add it node
  if(top==NULL){
    newNode->prev = NULL;
  }
  else{
    newNode->prev = *top;
  }
  *top = newNode;
}



void printStack(node **top){
   if(*top == NULL)
      printf("\nNo input\n");
   else{
      struct node *temp = *top;
      while(temp->prev != NULL){
      	 printf("%s\n",temp->row);
      	 temp = temp -> prev;
      }
      printf("%s\n",temp->row); //print the last one to stack
   }
}


void f_readFile(char *FILE_NAME, node **top){
  FILE* handle;
  char line[256];
  char *row;
  if((handle = fopen(FILE_NAME,"r"))==NULL)
  {
    fprintf(stderr, "error: Cannot open file %s \n",FILE_NAME);
		exit(1);
  }
  //read to stack
  while (fgets(line, sizeof(line), handle) != NULL){
      row=strtok(line, "\n");//save until row changing
      addStack(row, top);
  }
}
void f_writeFile(char *FILE_NAME, node **top){
  FILE* handle;

  if((handle = fopen(FILE_NAME,"w"))==NULL) //error handling
  {
    fprintf(stderr, "error: Cannot write to file %s \n", FILE_NAME);
		exit(1);
  }
  //loop linked stack
  struct node *temp = *top;
  while(temp->prev != NULL){
    fprintf(handle, "%s\n", temp->row);
    temp = temp->prev;
  }
  fprintf(handle, "%s", temp->row);// print the last one to file

}
