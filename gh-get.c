#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	
	/* Print args for now */
	for(i = 0; i < argc; i++) { printf("%d: %s\n", i + 1, argv[i]); }
	
	return 0;
}
