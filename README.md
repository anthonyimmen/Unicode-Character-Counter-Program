# Unicode Character Counter Program 

In order to run the code you need to download all of the files into a folder. Open the folder in terminal, enter make clean, make all, then './project0 << test2' or 'cat test2 | ./project0'.

Libraries used: stdio.h, stdlib.h, string.h, unistd.h, wchar.h, locale.h, limits.h, stdbool.h

## Code summary:

This project's goal is to read in a file, count how many times each character has appeared, output each character and the amount of times it has appeared in a descending sorted order. My project is able to do so by reading each character byte by byte, scanning to see if the current character has already been added into the array, which holds all of the characters that have been read, then adding the current character into a new slot if it is a new character, and updating the counter of the current character. My code runs in O(n^2) because I read in all the characters once, the go back through the characters another time to sort, insert, and print. 

For approaches to complete this project, there were three that I thought about and one of those I ended up picking. There was the decimal approach for reading in and adding the character to the array/list, the hexidecimal approach, and the binary with bit masking approach. I ended up picking the decimal approach because it was easiest in my eyes. I initially tried to use the binary approach, but I was having many issues trying to convert/mask by bits to binary. After coming across all of those issues, I went with the decimal approach. This decimal approach is further discussed in the description of my program function. 

There is currently one known bug in my code that I made a work-around for. The bug is that during the output before my correct output "->0" this is outputted to the console. This is not correct, and I was unsure why it was occuring after analyzing my code throughly. In order to make it work correctly, I created a check in the printinput() function that checks if the counter variable in the current stuct != 0. Thus, by including that peice of code, I was able to skip that line and have a correct output. 

## Brief description of functions:

compf() - this function is used as a comparator function for qsort. It is passed into qsort to compare. If b is greater than a, then we return a positive number, and if its not then we return a negative number.

printinput() - this function is used to print all the inputed characters in the format 'character' -> 'number of appearances'

program() - this is the main file of the program and is used to handle much of the heavy lifting. i.e. reading in the bytes, byte by byte, inserting the current character into the array, and making sure that the same character is not being inserted multiple times separately. When the code is checking where the current character is within the array to insert, it is using the decimal form of the character bytes to do so. It compares each of the bytes of the element in the array to the bytes of the current character. 

main() - calls the program() function to complete the task.



