#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include <stdbool.h>

#define BIG_BOY 1112064 //that's one big boy

struct  UTFchar {

	long long counter;
	unsigned char bytes1;
	unsigned char bytes2;
	unsigned char bytes3;
	unsigned char bytes4;
	int bytescount;

}Unichar;

void sortinput(struct UTFchar *list, long long counter) { //this function will sort the current array indescending order	
//	counter = counter * 2;

	struct UTFchar *temp = list;
	for (int i = 0; i < counter; i++) {
		
		struct UTFchar *tempi = list+i;
		for (int j = i + 1; j < counter; j++) {
			
			struct UTFchar *tempj = list+j;
			if (tempi->counter < tempj->counter) { //does this include char of same count rightnext toeachother
				temp = list+i;
				tempi = (list+j);
				tempj = temp;
			}	
		}
	}
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
		printf("%s->%llu\n", unicodestr, tempi->counter);
	}

}


int program() {

	char tempbyte;	
	unsigned char onebyte;
	unsigned char twobyte;
	unsigned char threebyte;
	unsigned char fourbyte;
	struct UTFchar *list;
	long long counter = 1;
	int bytecount; 
	struct UTFchar *head = (struct UTFchar *)(malloc(BIG_BOY));
	//create a dynamically sized array of Unichars using malloc
	list = (struct UTFchar *)(malloc(BIG_BOY));
	head = list;
	//need to read in first character from file
	tempbyte = fgetc(stdin); //read in first byte of the file
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
	
	//need to scan through array and find where the current character is 
	
	int i = 0;
	int flag = 0;
	struct UTFchar *headcopy = (struct UTFchar *)(malloc(BIG_BOY));
	headcopy = head;

	while(i < counter) { //will scan through the array to see if a node already exists
	//need to compare current character bytes with every UTFchar inside of array
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
	
	if (flag == 0) { //flag will still be zero if the node hasnt been found, this will create a new node in array
		struct UTFchar *temp = (struct UTFchar *)(malloc(BIG_BOY));
		temp = headcopy+counter;
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
	
		else if (bytecount == 1) {
		temp->bytes1 = onebyte;
		temp->bytescount = 1;
		temp->counter += 1;
		}

		else {
		break; //this will cover the empty file case
		}
	}
	
	//	increment onebyte to the next byte in the input file
		tempbyte = fgetc(stdin);
		++counter;
	
	}

	//we have now read in all the characters now we need to sort and output
	
	sortinput(list, counter);
	printinput(list, counter);
	
	return 0;
}


int main(int argc, char** argv)
{

	int result;

	//error check
	if (argc > 1) {
		dprintf(STDERR_FILENO, "Usage: %s <n>\n", argv[0]);
		exit(0);
	}
	else {
		dprintf(STDERR_FILENO, "Starting program...\n");
	}

	result = program();
	return result;

}
