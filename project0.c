#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include <stdbool.h>
#define BIG_NUMBER 11112064 //macro used for malloc

struct  UTFchar { //my structure that is used for each character

	long long counter;
	unsigned char bytes1;
	unsigned char bytes2;
	unsigned char bytes3;
	unsigned char bytes4;

}Unichar;


int compf(const void * a, const void * b) {

	long long acount = ((struct UTFchar *)a)->counter;
	long long bcount = ((struct UTFchar *)b)->counter;
	if (bcount > acount) {
		return 1;
	}
	else {
		return -1;
	}

}


void printinput(struct UTFchar *list, long long counter) { //this function will print the output in the specifed format
	printf("this is counter: %llu\n", counter);
	for (int i = 0; i < counter; ++i) {
	unsigned char unicodebytes[4];
		unicodebytes[0] = list[i].bytes1;
		unicodebytes[1] = list[i].bytes2;
		unicodebytes[2] = list[i].bytes3;
		unicodebytes[3] = list[i].bytes4;
	unsigned char *unicodestr = &unicodebytes[0];
		if ((list[i].counter >= 1)) {
		printf("%s->%llu\n", unicodestr, list[i].counter);
		}
	}

}


int program() { //this is the function that will do almost all of the work 

	char tempbyte;	
	unsigned char onebyte;
	unsigned char twobyte;
	unsigned char threebyte;
	unsigned char fourbyte;
	int bytecount;
	long long counter = 1;
	//create a dynamically sized array of Unichars using malloc with BIGNUM
	struct UTFchar *head = (malloc(sizeof(Unichar)*BIG_NUMBER)); // this is the array of characters
	memset(head, 0, sizeof(head));

	//reads in first character from file
	tempbyte = fgetc(stdin); 

        //this loop will scan in the rest of the bytes associtated with the current character
	while (tempbyte != EOF) {
		onebyte = (unsigned char)tempbyte;
	if (onebyte >= 240) {
		twobyte = (unsigned char)fgetc(stdin);	
		threebyte = (unsigned char)fgetc(stdin);
		fourbyte = (unsigned char)fgetc(stdin);
	}
	else if (onebyte >= 224) {
		bytecount = 3;
		twobyte = (unsigned char)fgetc(stdin);
		threebyte = (unsigned char)fgetc(stdin);
	}
	else if (onebyte >= 192) {
		bytecount = 2;
		twobyte = (unsigned char)fgetc(stdin);
	}
	else { //this is ASCII
		bytecount = 1;
	} 
	
	int i = 0; 
	int flag = 0; //used to denote if the character exists
	

	while(i < counter) { //will scan through the array to see if a node already exists and compares current character bytes with every UTFchar inside of array the while loop breaks when 'i' has exceed how many characters we have read.  
		if ((bytecount == 4) && (onebyte == head[i].bytes1) && (twobyte == head[i].bytes2) && 
		(threebyte == head[i].bytes3) && (fourbyte == head[i].bytes4)) {
		head[i].counter += 1;	
		flag = 1;
		break;
		}
	
		else if ((bytecount == 3) && (onebyte == head[i].bytes1) && (twobyte == head[i].bytes2) && 
		(threebyte == head[i].bytes3)) {
		head[i].counter += 1;
		flag = 1;
		break;
		}

		else if ((bytecount == 2) && (onebyte == head[i].bytes1) && (twobyte == head[i].bytes2)) {
		head[i].counter += 1;
		flag = 1;
		break;
		}

		else if ((bytecount == 1) && (onebyte == head[i].bytes1)) {
		head[i].counter += 1;
		flag = 1;
		break;
		}
		
		else { //if none match then increment to the next index in array
		++i;
		}	
	}
	

	//this will insert character into array if it does not previously exist
	if (flag == 0) { //flag will still be zero if the node hasnt been found, this will create a new node in array
		if (bytecount == 4) {
		head[i].bytes1 = (unsigned char)onebyte;
		head[i].bytes2 = (unsigned char)twobyte;
		head[i].bytes3 = (unsigned char)threebyte;
		head[i].bytes4 = (unsigned char)fourbyte;
		head[i].counter += 1;
		}

		else if (bytecount == 3) {
		head[i].bytes1 = (unsigned char)onebyte;
		head[i].bytes2 = (unsigned char)twobyte;
		head[i].bytes3 = (unsigned char)threebyte;
		head[i].counter += 1;
		}

		else if (bytecount == 2) {
		head[i].bytes1 = (unsigned char)onebyte;
		head[i].bytes2 = (unsigned char)twobyte;
		head[i].counter += 1;
		}
	
		else  {
		head[i].bytes1 = (unsigned char)onebyte;
		head[i].counter += 1;
		}

	++counter;

	}
	
		//increment onebyte to the next byte in the input file
		tempbyte = fgetc(stdin);
		
	
	}

	//we have now read in all the characters now we need to sort and output
	
	qsort(head, counter, sizeof(Unichar), compf);
	printinput(head, counter);
	
	return 0;
}


int main(int argc, char** argv)
{

	int result;
	result = program();
	return result;

}
