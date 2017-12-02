// pwgen.c : Defines the entry point for the console application.
//

#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int main(int argc, char **argv)
{
	// Character constants
	const char puncts[] = "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
	const char lowers[] = "abcdefghijklmnopqrstuvwxyz";
	const char uppers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char digits[] = "0123456789";

	// Selected character buffer
	char characters[255] = "";

	// Character selection flags
	bool hasLower = false;
	bool hasUpper = false;
	bool hasDigit = false;
	bool hasPunct = false;

	// Check command-line parameters
	if (argc <= 1)
	{
		fprintf(stderr, "Usage: pwdgen.exe TEMPLATE LENGHT\r\n");
		return EXIT_FAILURE;
	}

	// Parse length
	char *endPtr;
	size_t length = strtol(argv[2], &endPtr, 10);

	// Parse template and select characters
	size_t i;

	for (i = 0; i < strlen(argv[1]); i++)
	{
		if (!hasLower && islower(argv[1][i]))
		{
			hasLower = true;
			strcat(characters, lowers);
		}

		if (!hasUpper && isupper(argv[1][i]))
		{
			hasUpper = true;
			strcat(characters, uppers);
		}

		if (!hasDigit && isdigit(argv[1][i]))
		{
			hasDigit = true;
			strcat(characters, digits);
		}

		if (!hasPunct && ispunct(argv[1][i]))
		{
			hasPunct = true;
			strcat(characters, puncts);
		}
	}

	// Initialize the seed.
	srand(time(NULL));

	// Generate the password
	for (i = 0; i < length; i++)
	{
		fprintf(stdout, "%c", characters[rand() % strlen(characters)]);
	}

	fprintf(stdout, "\n");

	return EXIT_SUCCESS;
}
