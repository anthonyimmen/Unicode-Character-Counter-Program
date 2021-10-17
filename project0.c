#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>



struct  UTFchar {

	int counter;
	char bytes[4];
	char *next[];
	bool flag;
	char originalhex;

}Unichar;

struct list {

	struct UTFchar Unichar;
	struct list *next;

}Node;

//this function creates the linked list by initializing the head with init, so init now becomes the head
void createList(Node *init, UTFchar *unichar) {
	
	Node **head = (Node**)malloc(sizeof(struct list));

	init->Unichar = *unichar; 

}

//this functions adds another node to our list
void addUniChar(Node *current, UTFchar *unichar) {

	current->next = *unichar;

}


int program() {
	
	//create a structure linked list to connect the bytes together
	Unichar *formstruct = (Unichar*)malloc((sizeof(struc UTFchar));
	Node *init = (Node*)malloc((sizeof(struc list));
	

	int nums[100];
	int i;

	while ((scanf("%d", &nums[i]) == 1)) {
	
	i++;

	}


	for (int j=0; j < i; j++) {
		printf("%d\n", nums[j]);
	}








// this section will be used to output the characters to the screen


	wchar_t string[100];
	 setlocale(LC_ALL, "");

	 printf ("Enter a string: ");
	 scanf("%ls", string); 

	 printf("String Entered: %ls: length: %d\n", string, wcslen(string));
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
