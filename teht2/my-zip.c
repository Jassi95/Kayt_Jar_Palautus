#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INTEGER 4294967295
#define INTEGER_BYTES 2
#define ASCII_BYTES 1

void zip_file(char* file_name){

  //open file
  FILE*fp = fopen(file_name,"r");

  if (fp==NULL){perror("Error: "); exit(1);}
  // Compression variables
  uint32_t count;
  int curChar = getc(fp);
  int nextChar= curChar;
  //compression
  while(nextChar != EOF){
    //until char changes or we run out of numbers with 4 bytes
    for(count = 0; curChar == nextChar && count < MAX_INTEGER; count++){
        nextChar = getc(fp);
    }
    // if used correctly it will be directed to new file
    fwrite(&count,1,INTEGER_BYTES,stdout);
    fwrite(&curChar,1,ASCII_BYTES,stdout);
    curChar = nextChar;
    count =1;
  }
  fclose(fp);
}


int main(int argc, char **argv){

  if(argc >=2){

    for(int i=1;i<argc;i++){
      char* file_name = argv[i];
      zip_file(file_name);
    }
  }

  else{
    printf("%s\n","Wrong use. example : ./my-zip <file_name> > <result_file>" );
  }
  return 0;
}
