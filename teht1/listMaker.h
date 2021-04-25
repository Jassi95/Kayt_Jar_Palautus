/*Last input is read as first*/
typedef struct node{
  char row[256];
  struct node *prev;
} node ;

void f_readFile(char *FILE_NAME, node **top);
void f_writeFile(char *FILE_NAME, node **top);

void addStack(char *cur_row, node **top);
void printStack(node **top);
