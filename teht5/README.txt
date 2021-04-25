Author Juho Jääskeläinen
Käyttöjärjestelmät ja systeemiohjelmointi: Project 5: Parallel Zip

Sources:
https://www.openmp.org/
http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall17/Lectures/openmp.html

Build with:
gcc -fopenmp -o pzip pzip.c -Wall -Werror -g

run:
./pzip <file_name> > <zipped_file_name>


Working principle:
Load the file to memory.
Create a table for the final file.
Creates the threads.
Splits the file to chunks which are given to threads to process
Thread return the coded chunk to right place in the final table
Thread continues to next available chank untill whole file has been processed.
Prints the coded file to stdout

Notifications:
Uses openMP gcc library, for threading, easy to implement.
