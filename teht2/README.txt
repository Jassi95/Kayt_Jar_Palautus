Author: Juho Jääskeläinen

unix utilities readme

Build all: make



my-cat

This utility reads a file (or multiple files) and prints out file contents.

Run:
./my-cat filename(s)
./my-cat file1.txt file2.txt [...]

my-grep

This utility scans files or the standard input (stdin) for a search term.
If a matching line is found, it is printed out.
my-grep

This utility scans files or the standard input (stdin) for a search term.
If a matching line is found, it is printed out.

Run:
./my-grep search_term filename(s)
./my-grep search_term file1.txt file2.txt [...]
./my-grep search_term

In the last example standard input (stdin) is used.

my-zip

This utility is used to compress files with run-length encoding.

Run:
./my-zip filename(s)
./my-zip file1.txt
./my-zip file1.txt > out.file

By default, output is written to standard output.
Output redirection can be used to save the output stream in a file.

my-unzip

This utility is used to decompress files processed by my-zip.

Run:
./my-unzip filename(s)
./my-unzip file1.txt
./my-unzip file1.txt > out.file

By default, output is written to standard output.
Output redirection can be used to save the output stream in a file.
