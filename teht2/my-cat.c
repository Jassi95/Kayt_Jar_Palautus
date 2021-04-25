#include <stdio.h>
#include <stdlib.h>



void echo_file(char* file_name){
  //open file, takes file line by line to buffer prints buffer, closes file
  char buffer[255];
  FILE*fp = fopen(file_name,"r");

  if (fp==NULL){perror("Error: "); exit(1);}

  while (fgets(buffer,255,fp)!=NULL){
    printf("%s",buffer );
  }
  fclose(fp);
}


int main(int argc, char **argv){

  if(argc >1){ //loops all the inputs
    for(int i=1;i< argc;i++ ){
      char* file_name = argv[i];
      echo_file(file_name);
    }
  }

  else{
    printf("%s\n","Wrong use. example : ./my-cat <file_name> " );
  }
  return 0;
}
