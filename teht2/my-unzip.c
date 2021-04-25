#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INTEGER 4294967295 //max integer with this amount of bytes
#define INTEGER_BYTES 2
#define ASCII_BYTES 1


void unzip_file(char* file_name){

  FILE*fp = fopen(file_name,"r");
  if (fp==NULL){perror("Error: "); exit(1);}

  uint32_t count;
  int curChar;

  while(!feof(fp)){ //feop() == true when end of file
    //reads the input to variables
    fread(&count,1,INTEGER_BYTES,fp);
    fread(&curChar,1,ASCII_BYTES,fp);
    for(int i=0; i<count;i++){
      putc(curChar,stdout);
    }

  }

}


int main(int argc, char **argv){

  if(argc >=2){

    for(int i=1;i<argc;i++){
      char* file_name = argv[i];
      unzip_file(file_name);
    }
    }

  else{
    printf("%s\n","Wrong use. example : ./my-unzip <file_name> > <result_file>" );
  }
  return 0;
}
