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
	int bytescount;

}Unichar;

struct UTFchar * sortinput(struct UTFchar *list, long long counter) { //this function will sort the current array indescending order	
	struct UTFchar *temp = list;
	struct UTFchar *tempi;
	struct UTFchar *tempj;
	for (int i = 0; i < counter; ++i) {	
		tempi = list+i;
		for (int j = i + 1; j < counter; ++j) {
			tempj = list+j;
			if (tempi->counter < tempj->counter) { //this includes char of same count right next to each other
				
				//this sections swaps the bytes with each, this is done to sort the list. It will not work just by interchanging the structs
				//flips temp and tempi
				temp->counter = tempi->counter; 
				temp->bytes1 = tempi->bytes1;
				temp->bytes2 = tempi->bytes2;
				temp->bytes3 = tempi->bytes3;
				temp->bytes4 = tempi->bytes4;
				
				//flips tempi and tempj
				tempi->counter = tempj->counter;
				tempi->bytes1 = tempj->bytes1;
				tempi->bytes2 = tempj->bytes2;
				tempi->bytes3 = tempj->bytes3;
				tempi->bytes4 = tempj->bytes4;
				
				//flips tempj and temp
				tempj->counter = temp->counter;
				tempj->bytes1 = temp->bytes1;
				tempj->bytes2 = temp->bytes2;
				tempj->bytes3 = temp->bytes3;
				tempj->bytes4 = temp->bytes4;

			}	
		}
	}
	return temp;
}


void printinput(struct UTFchar *list, long long counter) { //this function will print the output in the specifed format
	struct UTFchar *tempi;
	for (int i = 0; i < counter; ++i) {
	tempi = list+i;
	unsigned char unicodebytes[4];
		unicodebytes[0] = tempi->bytes1;
		unicodebytes[1] = tempi->bytes2;
		unicodebytes[2] = tempi->bytes3;
		unicodebytes[3] = tempi->bytes4;
	unsigned char *unicodestr = &unicodebytes[0];
		if (tempi->counter != 0) {
		printf("%s->%llu\n", unicodestr, tempi->counter);
		}
	}

}


int program() { //this is the function that will do almost all of the work 

	char tempbyte;	
	unsigned char onebyte;
	unsigned char twobyte;
	unsigned char threebyte;
	unsigned char fourbyte;
	struct UTFchar *list;
	long long counter = 1;
	int bytecount; 
	struct UTFchar *head = (struct UTFchar *)(malloc(sizeof(head)*BIG_NUMBER));


	//create a dynamically sized array of Unichars using malloc with BIGNUM
	list = (struct UTFchar *)(malloc(sizeof(list)*BIG_NUMBER)); 
	head = list;

	//reads in first character from file
	tempbyte = fgetc(stdin); 

        //this loop will scan in the rest of the bytes associtated with the current character
	while (tempbyte != EOF) {
		onebyte = tempbyte;
	if (onebyte >= 240) {
		bytecount = 4;
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
	struct UTFchar *headcopy = (struct UTFchar *)(malloc(BIG_NUMBER));
	headcopy = head;

	while(i < counter) { //will scan through the array to see if a node already exists and compares current character bytes with every UTFchar inside of array the while loop breaks when 'i' has exceed how many characters we have read.  
		if ((bytecount == 4) && (onebyte == headcopy->bytes1) && (twobyte == headcopy->bytes2) && 
		(threebyte == headcopy->bytes3) && (fourbyte == headcopy->bytes4)) {
		headcopy->bytes1 = onebyte;
		headcopy->bytes2 = twobyte;
		headcopy->bytes3 = threebyte;
		headcopy->bytes4 = fourbyte;
		headcopy->counter += 1;
		headcopy->bytescount = 4;
		flag = 1;
		break;
		}
	
		else if ((bytecount == 3) && (onebyte == headcopy->bytes1) && (twobyte == headcopy->bytes2) && 
		(threebyte == headcopy->bytes3)) {
		headcopy->bytes1 = onebyte;
		headcopy->bytes2 = twobyte;
		headcopy->bytes3 = threebyte;
		headcopy->counter += 1;
		headcopy->bytescount = 3;
		flag = 1;
		break;
		}

		else if ((bytecount == 2) && (onebyte == headcopy->bytes1) && (twobyte == headcopy->bytes2)) {
		headcopy->bytes1 = onebyte;
		headcopy->bytes2 = twobyte;
		headcopy->counter += 1;
		headcopy->bytescount = 2;
		flag = 1;
		break;
		}

		else if ((bytecount == 1) && (onebyte == headcopy->bytes1)) {
		headcopy->bytes1 = onebyte;
		headcopy->counter += 1;
		headcopy->bytescount = 1;
		flag = 1;
		break;
		}
		
		else { //if none match then increment to the next index in array
		++headcopy;
		++i;
		}	
	}
	

	//this will insert character into array if it does not previously exist
	if (flag == 0) { //flag will still be zero if the node hasnt been found, this will create a new node in array
		struct UTFchar *temp = (struct UTFchar *)(malloc(sizeof(temp)*BIG_NUMBER));
		temp = headcopy; 
		if (bytecount == 4) {
		temp->bytes1 = onebyte;
		temp->bytes2 = twobyte;
		temp->bytes3 = threebyte;
		temp->bytes4 = fourbyte;
		temp->bytescount = 4;
		temp->counter += 1;
		}

		else if (bytecount == 3) {
		temp->bytes1 = onebyte;
		temp->bytes2 = twobyte;
		temp->bytes3 = threebyte;
		temp->bytescount = 3;
		temp->counter += 1;
		}

		else if (bytecount == 2) {
		temp->bytes1 = onebyte;
		temp->bytes2 = twobyte;
		temp->bytescount = 2;
		temp->counter += 1;
		}
	
		else  {
		temp->bytes1 = onebyte;
		temp->bytescount = 1;
		temp->counter += 1;
		}

	}
	
		//increment onebyte to the next byte in the input file
		tempbyte = fgetc(stdin);
		++counter;
	
	}

	//we have now read in all the characters now we need to sort and output
	
	list = sortinput(list, counter);
	printinput(list, counter);
	
	return 0;
}


int main(int argc, char** argv)
{

	int result;
	result = program();
	return result;

}
