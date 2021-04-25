#include <stdio.h> // stdout
#include <stdlib.h> // exit() and malloc()
#include <stdint.h> // uint_32
#include <sys/sysinfo.h> // get_nprocs()
#include <fcntl.h> // open()
#include <unistd.h> // read()
#include <time.h>
#include <string.h>
#include <omp.h>



/*
Working princible divide the data into datasize/nthreads size chunks and then make every thread work for their own chunk. Problem: what if some chunks are inherintly slower forcing some workers to wait for the last one to finnish?
If we divide into smaller chunks then the probability of one worker being idle for long time(waiting for others to finnish) decreases. Lets start with dividing the data to datasize/10*nthreads chunks.
source:http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall17/Lectures/openmp.html
*/


#define MAX_INTEGER 4294967295
#define INTEGER_BYTES 2
#define ASCII_BYTES 1

typedef struct zchar{
  uint32_t count;
  int character;
  struct zchar *next;
} zchar ;

typedef struct chunk{
  int order;
  struct zchar *chunkStart;
  struct chunk *next;
}chunk;


void zip_file(char* file_name){
  int num_of_threads = get_nprocs_conf();



  char* buffer = 0;
  //open file
  FILE *fp = fopen(file_name,"r");
  if (fp==NULL){perror("Error: "); exit(1);}
  fseek(fp,0,SEEK_END);
  long length = ftell(fp);
  fseek(fp,0,SEEK_SET);
  if((buffer = malloc(length * sizeof(char))) ==NULL){
    fprintf(stderr, "Malloc failed");
    exit(1);
  }
  if(buffer){
    fread(buffer,1,length,fp);
  }
  fclose(fp);


  //calculating the step for paralelization

  long paralel_ending =length-length%(10*num_of_threads); //for future since we can only deal with equal size chunks in parallel
  long step = paralel_ending/(10*num_of_threads);
  int chunk_amount=paralel_ending/step;



  //INITILIZE chunks data
  struct chunk *chunk_head = malloc(sizeof(chunk));
  struct chunk *cur_chunk=chunk_head;
  struct chunk *chunk_arr[chunk_amount];

  for(int i=0;i<chunk_amount;i++){
    cur_chunk->order=i;
    cur_chunk->chunkStart=NULL;
    cur_chunk->next = malloc(sizeof(chunk));
    chunk_arr[i]=cur_chunk;
    cur_chunk=cur_chunk->next;
    cur_chunk->next=NULL;
    //printf("%d\n",i );
  }

//jos ajaisi jokaisen chunk pointerin arrayhyn. Ja josta niihin pääsee käsiksi?


  #pragma omp parallel for

    for(int i=0;i<chunk_amount;i++){ //loops the chunks of file in parallel

          int k;
          uint32_t count = 1;
          int curChar;
          int nextChar;
          struct zchar * c_ptr_head;
          struct zchar *c_ptr;

        c_ptr = malloc(sizeof(struct zchar));
        c_ptr_head = c_ptr;

        char my_chunk[step];
        strncpy( my_chunk,buffer + i*step, step); //makes own copy to read

        for(k = 0;k<step;k++){  //Goes trough the copy

          curChar=my_chunk[k];
          nextChar=my_chunk[k+1];

          if(curChar==nextChar && count < MAX_INTEGER){//does compression and writes it to linked list
            count++;
          }else{
            c_ptr->count=count;
            c_ptr->character=curChar;
            c_ptr->next = malloc(sizeof(struct zchar));
            c_ptr=c_ptr->next;
            c_ptr->next=NULL;
            count=1;
          }
        } //tämä atomic?
        cur_chunk = chunk_arr[i];//goes to right chunk
        cur_chunk->chunkStart=c_ptr_head; //saves the list to chunk list

      }




//prints the parallel made thinkg chunk by chunk to stdout
  cur_chunk = chunk_head;
  while(cur_chunk->next !=NULL){//goes trough chunks
    struct zchar *c_ptr = cur_chunk->chunkStart;
  //  printf("\n\ntama tulee chunkista %d\n\n",cur_chunk->order);
    while(c_ptr->next != NULL){//goes trough chunk
      fwrite(&c_ptr->count,1,INTEGER_BYTES,stdout);
      fwrite(&c_ptr->character,1,ASCII_BYTES,stdout);
      //printf("%c",c_ptr->character );
      c_ptr = c_ptr->next;
    }

    cur_chunk=cur_chunk->next;
  }

  uint32_t count=1;
  for(int i=paralel_ending; i<length; i++){ //now for those who dont fit to parallel.
    int curChar = buffer[i];
    int nextChar = buffer[i+1];

    //Compression
    if(curChar==nextChar && count < MAX_INTEGER){
      count++;
    }else{
      //printf("%d",count);
      //printf("%c",curChar );
      fwrite(&count,1,INTEGER_BYTES,stdout);
      fwrite(&curChar,1,ASCII_BYTES,stdout);
      count=1;
      }
    }

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
