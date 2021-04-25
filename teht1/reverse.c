#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "listMaker.h"


int main(int argc, char **argv ){
 node *top=NULL;

  if(argc < 2){
    /* readstdin and reverse the order*/
        char input_buffer[256];
        if(fgets(input_buffer,sizeof(input_buffer),stdin)==NULL) exit(1);
        input_buffer[strcspn(input_buffer, "\n")] = '\0';  // loop off potential trailing \n
        size_t len = strlen(input_buffer);
        while (len) {
          putc(input_buffer[--len], stdout);
        }

     }
  else if (argc == 2){ /*read file and print out*/

    //strcpy(argv[1], &FILE_NAME);
    f_readFile(argv[1],&top);

    printStack(&top);
    exit(0);
  }
  else if (argc == 3){
    /*readfile and print to file*/
    if (strcmp(argv[1], argv[2])== 0 ){
      fprintf(stderr, "Input and output file must differ\n" );
      exit(1);
    }
    f_readFile(argv[1],&top);
    f_writeFile(argv[2],&top);
    exit(0);
  }
  else if (argc > 3){//liikaa muutujia
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);

  }
}
