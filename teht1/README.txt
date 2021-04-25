Author: Juho Jääskeläinen

REVERSE readme

build: make

Usage:
./reverse
<type line to be reversed>

./reverse <filename>
reverses the file and prints it

./reverse <filename> <filename2>
reverses file and saves the reversed output to file2

Working principle:
Reads input, and saves it to linked stack. So that the last input is the top of the stack
Then it just outputs the stack from top to bottom.
