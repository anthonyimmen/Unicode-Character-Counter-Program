#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>



int mainprogram() {

	int nums[100];
	int i;

/*	while ((scanf("%d", &nums[i]) == 1)) {
	
	i++;

	}


	for (int j=0; j < i; j++) {
		printf("%d\n", nums[j]);
	}
*/
	wchar_t string[100];
	 setlocale(LC_ALL, "");

	 printf ("Enter a string: ");
	 scanf("%ls", string); 

	 pringf("String Entered: %ls: length: %dn", string, wcsle(string));


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

	result = mainprogram();
	return result;

}
