#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void search_in_file(char* search_term, char*file_name){
  printf("%s looking: %s\n",file_name,search_term );


  char *line_buf = NULL;
  size_t line_buf_size=0;
  int line_count=0;
  ssize_t line_size;

  FILE*fp = fopen(file_name,"r");

  if (fp==NULL){perror("Error: "); exit(1);}

  line_size = getline(&line_buf,&line_buf_size,fp);

  while(line_size >= 0){//goes trough the file
    line_count++;
    //finding logic
    char *ptr = strstr(line_buf,search_term);
    if(ptr!=NULL){
      printf("%s",line_buf );
    }


    line_size = getline(&line_buf,&line_buf_size,fp);
  }


  fclose(fp);
}



int main(int argc, char **argv){
  char* search_term = argv[1];
  if(argc >2){ //loops all the input files

    for(int i=2;i< argc;i++ ){
      char* file_name = argv[i];
      search_in_file(search_term,file_name);

    }
  }

  else if(argc == 2){//reads input and prints line if it maches search term
    char input_buffer[256];
    while(fgets(input_buffer,sizeof(input_buffer),stdin)!=NULL){
        input_buffer[strcspn(input_buffer, "\n")] = '\0';
        char *ptr = strstr(input_buffer,search_term);
        if(ptr!=NULL){
          printf("%s%s\n",input_buffer," matches search term" );
        }
    }
  }
    else{
      printf("%s\n","Invalid use, Example: my-grep <search-term> *<file>" );
      return 1;
    }




  return 0;
}
