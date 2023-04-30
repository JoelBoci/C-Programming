#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// KEYBOARD METHODS

// From letter to position (character position)
int keyboardForwards(char letter) {
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Store position of the letter
	int position = 0;

	for (int i = 0; i < 26; i++) {
		if (letter == alphabet[i]) {
			position = i;
		}
	}

	return position;
}

// From position to letter (letter at the position specified e.g., position 0 = A
char keyboardBackwards(int position) {
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char letter = ' ';

	for (int i = 0; i < 26; i++) {
		if (position == i) {
			letter = alphabet[i];
		}
	}

	return letter;
}



// PLUGBOARD METHODS

// Encrypting forwards
int plugboardForwards(char pairs[], int position) {
	// If the length is less than 1 or equal to 1 (one letter only) then return the position passed through
	// If the number of pairs is odd, then return the position passed through
	if (strlen(pairs) <= 1 || strlen(pairs) % 2 == 1) {
		return position;
	}

	char letterA = ' ';
	char letterB = ' ';
	int positionA = 0;
	int positionB = 0;

	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char modify[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Loop through the pairs, skip 2 letters everytime (makes sure it goes in pairs)
	for (int i = 0; i < strlen(pairs); i+=2) {
		letterA = pairs[i];
		letterB = pairs[i + 1];

		// Loop through 26 letters, assign i to positionA variable (means char a is at position i)
		for (int i = 0; i < 26; i++) {
			if (letterA == modify[i]) {
				positionA = i;
			}
		}

		// Assign the value at char a's position to the letter stored in variable letterB
		modify[positionA] = letterB;

		// Loop through 26 letters, assign i to positionB variable (means char b is at position i)
		for (int i = 0; i < 26; i++) {
			if (letterB == modify[i]) {
				positionB = i;
			}
		}

		// Assign the value at char b's position to the letter stored in variable letterA
		modify[positionB] = letterA;
	}

	// Assign the letter held at the position passed through as the parameter in the normal alphabet array
	char letter = alphabet[position]; 

	// Loop through the modified array, and find the letter passed through
	for (int i = 0; i < 26; i++) {
		if (letter == modify[i]) { 
			position = i;
		}
	}

	return position;
}

// Encrypting backwards
int plugboardBackwards(char pairs[], int position) {
	// If the length is less than 1 or equal to 1 (one letter only) then return the position passed through
	// If the number of pairs is odd, then return the position passed through
	if (strlen(pairs) <= 1 || strlen(pairs) % 2 == 1) {
		return position;
	}

	char letterA = ' ';
	char letterB = ' ';
	int positionA = 0;
	int positionB = 0;

	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char modify[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Loop through the pairs, skip 2 letters everytime (makes sure it goes in pairs)
	for (int i = 0; i < strlen(pairs); i += 2) {
		letterA = pairs[i];
		letterB = pairs[i + 1];

		// Loop through 26 letters, assign i to positionA variable (means char a is at position i)
		for (int i = 0; i < 26; i++) {
			if (letterA == modify[i]) {
				positionA = i;
			}
		}

		// Assign the value at char a's position to the letter stored in variable letterB
		modify[positionA] = letterB;

		// Loop through 26 letters, assign i to positionB variable (means char b is at position i)
		for (int i = 0; i < 26; i++) {
			if (letterB == modify[i]) {
				positionB = i;
			}
		}

		// Assign the value at char b's position to the letter stored in variable letterA
		modify[positionB] = letterA;
	}

	// Assign the letter held at the position passed through as the parameter in the modified array
	char letter = modify[position];

	// Loop through the normal alphabet array, and find the letter passed through
	for (int i = 0; i < 26; i++) {
		if (letter == alphabet[i]) {
			position = i;
		}
	}

	return position;
}



// ROTOR METHODS

typedef struct Rotor {
	// The regular alphabet
	char alphabet[27];

	// The mapping of the rotor (wiring)
	char mapping[27];

	// The character where the notch is
	char notch;

} Rotor;

// All 5 rotors
Rotor I = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q' };
Rotor II = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E' };
Rotor III = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V' };
Rotor IV = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J' };
Rotor V = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "VZBRGITYUPSDNHLXAWMJQOFECK", 'Z' };

// Used for user input
Rotor userSlowRotor;
Rotor userMiddleRotor;
Rotor userFastRotor;

// Rotors going forwards, 3 - 1
int rotorRotateForwards(Rotor rotor, int position) {
	// Assign the letter at the index specified by position in the rotor mapping array
	char letter = rotor.mapping[position];

	// Loop through alphabet
	for (int i = 0; i < 26; i++) {
		// Assign the value of i to position if the letter is equal to the letter in the alphabet array
		if (letter == rotor.alphabet[i]) {
			position = i;
			break;
		}
	}

	return position;
}

// Rotors going backwards, 1 - 3
int rotorRotateBackwards(Rotor rotor, int position) {
	// Assign the letter at the inde specified by position in the alphabet array
	char letter = rotor.alphabet[position];

	// Loop through rotor mapping
	for (int i = 0; i < 26; i++) {
		// Assign the value of i to position if the letter is equal to the letter in the rotor mapping array
		if (letter == rotor.mapping[i]) {
			position = i;
			break;
		}
	}

	return position;
}

void rotorRotate(Rotor* rotor /*used pointers to modify array*/, int n, bool forward) {
	// loop until i is less than n (step)
	for (int i = 0; i < n; i++) {
		// If we are rotating forward
		if (forward) {
			
			// Set the first letter of the alphabet to variable 
			char alphabetFirst = rotor->alphabet[0];

			// Loop through alphabet, starting from the second position (1st index)
			for (int j = 1; j < 26; j++) {

				// Switch previous character with the current
				rotor->alphabet[j - 1] = rotor->alphabet[j];
				                               
			}

			// Change the last letter to the first letter
			rotor->alphabet[25] = alphabetFirst;

			// Set the first letter of the rotor mapping to variable 
			char mappingFirst = rotor->mapping[0];

			// Loop through rotor mapping, starting from the second position (1st index)
			for (int j = 1; j < 26; j++) {
				// Switch previous character with the current
				rotor->mapping[j - 1] = rotor->mapping[j];
			}

			// Change the last letter to the first letter
			rotor->mapping[25] = mappingFirst;
		}

		else { // If we are rotating backwards

			// Set the last letter of the alphabet to variable 
			char alphabetLast = rotor->alphabet[25];

			// Loop through alphabet, starting from the last position 
			for (int j = strlen(rotor->alphabet) - 1; j > 0; j--) {
				// Switch current character with the previous character
				rotor->alphabet[j] = rotor->alphabet[j - 1];
			}

			// Change the first letter to the last letter
			rotor->alphabet[0] = alphabetLast;

			// Set the last letter of the rotor mapping to variable 
			char mappingLast = rotor->mapping[25];

			// Loop through rotor mapping, starting from the last position 
			for (int j = strlen(rotor->alphabet) - 1; j > 0; j--) {
				// Switch current character with the previous character
				rotor->mapping[j] = rotor->mapping[j - 1];
			}

			// Change the first letter to the last letter
			rotor->mapping[0] = mappingLast;
		}
	}
}

// Rotate the rotor to the position of the letter given (used for the key / rotor start)
void rotateToLetter(Rotor* rotor, char letter) {
	int n = 0; // Used to assign the position of the letter in the alphabet
	
	for (int i = 0; i < 26; i++) {
		if (letter == rotor->alphabet[i]) {
			n = i;
			break;
		}
	}

	// Rotor the rotor forward by n positions
	rotorRotate(rotor, n, true);
}

// Rotates the rotors to the values entered by user e.g. rotor start = CAT
void setRotorStart(char start[]) {
	rotateToLetter(&userSlowRotor, start[0]);
	rotateToLetter(&userMiddleRotor, start[1]);
	rotateToLetter(&userFastRotor, start[2]);
}

// Ring Settings 
void setRing(Rotor* rotor, int n) { 
	// Rotor backwards by 1
	rotorRotate(rotor, n - 1, false);

	int notchPosition = 0;

	// Loop through alphabet
	for (int i = 0; i < 26; i++) {
		if (rotor->notch == rotor->alphabet[i]) {

			// Assign i to the notch position
			notchPosition = i;
			break;
		}
	}

	// Reassign the notch value
	// + 27 = + 1 but + 1 did not work for some reason
	rotor->notch = rotor->alphabet[(notchPosition - n + 27) % 26];
}

// Ring Settings
void setRings(int rings[]) {
	setRing(&userSlowRotor, rings[0]);
	setRing(&userMiddleRotor, rings[1]);
	setRing(&userFastRotor, rings[2]);
}



// REFLECTOR METHODS
typedef struct Reflector {

	// The regular alphabet
	char alphabet[27]; // Had to be 27 as to create a space for the null value \0

	// The reflector mapping / wiring
	char mapping[27]; // Had to be 27 as to create a space for the null value \0

} Reflector;

Reflector A = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "EJMZALYXVBWFCRQUONTSPIKHGD" };
Reflector B = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "YRUHQSLDPXNGOKMIEBFZCWVJAT" };
Reflector C = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "FVPJIAOYEDRZXWGCTKUQSBNMHL" };

Reflector userReflector;

// Static reflector  
int reflect(Reflector reflector, int position) {
	// Assign the letter at the index specified by position in the refelctor mapping array
	char letter = reflector.mapping[position];

	for (int i = 0; i < 26; i++) {

		// Assign the value of i to position if the letter is equal to the letter in the reflector alphabet array
		if (letter == reflector.alphabet[i]) {
			position = i;
		}
	}

	return position;
}

int main(int argc, char** argv) {
	printf("*** Use fullscreen for better experience *** \n\n");
	printf(",------.          ,--.                                 ,--.   ,--.                 ,--.      ,--.                  \n");
	printf("|  .---' ,--,--,  `--'  ,---.  ,--,--,--.  ,--,--.     |   `.'   |  ,--,--.  ,---. |  ,---.  `--' ,--,--,   ,---.  \n");
	printf("|  `--,  |      \\ ,--. | .-. | |        | ' ,-.  |     |  |'.'|  | ' ,-.  | | .--' |  .-.  | ,--. |      \\ | .-. : \n");
	printf("|  `---. |  ||  | |  | ' '-' ' |  |  |  | \\ '-'  |     |  |   |  | \\ '-'  | \\ `--. |  | |  | |  | |  ||  | \\  --. \n");
	printf("`------' `--''--' `--' .`-  /  `--`--`--'  `--`--'     `--'   `--'  `--`--'  `---' `--' `--' `--' `--''--'  `----' \n");
	printf("                       `---'                                                                                       \n\n");

	printf("  __  __             _           _                  _               _     ___              _                    ___   _   ___   ___   ____  ___    __ \n");
	printf(" |  \\/  |  __ _   __| |  ___    | |__   _  _     _ | |  ___   ___  | |   | _ )  ___   __  (_)    ___     _  _  |_  ) / | | __| | __| |__ / | __|  / / \n");
	printf(" | |\\/| | / _` | / _` | / -_)   | '_ \\ | || |   | || | / _ \\ / -_) | |   | _ \\ / _ \\ / _| | |   |___|   | || |  / /  | | |__ \\ |__ \\  |_ \\ |__ \\ / _ \\ \n");
	printf(" |_|  |_| \\__,_| \\__,_| \\___|   |_.__/  \\_, |    \\__/  \\___/ \\___| |_|   |___/ \\___/ \\__| |_|            \\_,_| /___| |_| |___/ |___/ |___/ |___/ \\___/ \n");
	printf("                                        |__/                                                                                                          \n");

	int startQuit = 0;
	while (1) {
		printf("Enter 1 to start or 2 to quit: ");
		if (scanf("%d", &startQuit) != 1) {
			while (getchar() != '\n');
			printf("Error: Invalid input\n\n");
			continue;
		}

		if (startQuit == 1) {

			// For rotors
			// Side note: had to use different variables in order to avoid errors :(
			int rotorChoice1 = 0;
			int rotorChoice2 = 0;
			int rotorChoice3 = 0;

			// User selects rotors
			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("____ ____ ___ ____ ____    ____ ____ _    ____ ____ ___ _ ____ _  _ \n");
			printf("|__/ |  |  |  |  | |__/    [__  |___ |    |___ |     |  | |  | |\\ | \n");
			printf("|  \\ |__|  |  |__| |  \\    ___] |___ |___ |___ |___  |  | |__| | \\| \n\n\n");

			printf("-> Note: | 1 = I | 2 = II | 3 = III | 4 = IV | 5 = V |");

			// FIRST ROTOR
			int fRotorValidInput = 0;
			do {
				printf("\n\n-> Choose the first (slow) rotor: ");
				char input[1];
				scanf("%s", input);

				// Check for valid input format
				if (sscanf(input, "%d", &rotorChoice1) != 1) {
					printf("Invalid input. Please enter a valid number.\n\n");
					continue;
				}

				// Check for valid rotor selection
				if (rotorChoice1 < 1 || rotorChoice1 > 5) {
					printf("Invalid rotor selection. Please enter a number between 1 and 5.\n\n");
					continue;
				}

				fRotorValidInput = 1;

			} while (!fRotorValidInput);

			switch (rotorChoice1) {
			case 1:
				userSlowRotor = I;
				break;
			case 2:
				userSlowRotor = II;
				break;
			case 3:
				userSlowRotor = III;
				break;
			case 4:
				userSlowRotor = IV;
				break;
			case 5:
				userSlowRotor = V;
				break;
			default:
				userSlowRotor = I;
				break;
			}

			// SECOND ROTOR
			int sRotorValidInput = 0;
			do {
				printf("\n-> Choose the second (middle) rotor: ");
				char input[1];
				scanf("%s", input);

				// Check for valid input format
				if (sscanf(input, "%d", &rotorChoice2) != 1) {
					printf("Invalid input. Please enter a valid number.\n\n");
					continue;
				}

				// Check for valid rotor selection
				if (rotorChoice2 < 1 || rotorChoice2 > 5) {
					printf("Invalid rotor selection. Please enter a number between 1 and 5.\n\n");
					continue;
				}

				// Check for duplicate rotor
				if (rotorChoice2 == rotorChoice1) {
					printf("You have already selected that rotor. Please select a different one.\n\n");
					continue;
				}

				sRotorValidInput = 1;

			} while (!sRotorValidInput);

			switch (rotorChoice2) {
			case 1:
				userMiddleRotor = I;
				break;
			case 2:
				userMiddleRotor = II;
				break;
			case 3:
				userMiddleRotor = III;
				break;
			case 4:
				userMiddleRotor = IV;
				break;
			case 5:
				userMiddleRotor = V;
				break;
			default:
				userMiddleRotor = II;
				break;
			}

			// THIRD ROTOR
			int tRotorValidInput = 0;
			do {
				printf("\n-> Choose the third (fast) rotor: ");
				char input[1];
				scanf("%s", input);

				// Check for valid input format
				if (sscanf(input, "%d", &rotorChoice3) != 1) {
					printf("Invalid input. Please enter a valid number.\n\n");
					continue;
				}

				// Check for valid rotor selection
				if (rotorChoice3 < 1 || rotorChoice3 > 5) {
					printf("Invalid rotor selection. Please enter a number between 1 and 5.\n\n");
					continue;
				}

				// Check for duplicate rotor
				if (rotorChoice3 == rotorChoice1 || rotorChoice3 == rotorChoice2) {
					printf("You have already selected that rotor. Please select a different one.\n\n");
					continue;
				}

				tRotorValidInput = 1;

			} while (!tRotorValidInput);

			switch (rotorChoice3) {
			case 1:
				userFastRotor = I;
				break;
			case 2:
				userFastRotor = II;
				break;
			case 3:
				userFastRotor = III;
				break;
			case 4:
				userFastRotor = IV;
				break;
			case 5:
				userFastRotor = V;
				break;
			default:
				userFastRotor = III;
				break;
			}

			printf("\n-> ROTORS >>> %d %d %d", rotorChoice1, rotorChoice2, rotorChoice3);
			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");



			// User chooses reflector
			int reflectorChoice = 0;
			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("____ ____ ____ _    ____ ____ ___ ____ ____    ____ ____ _    ____ ____ ___ _ ____ _  _ \n");
			printf("|__/ |___ |___ |    |___ |     |  |  | |__/    [__  |___ |    |___ |     |  | |  | |\\ | \n");
			printf("|  \\ |___ |    |___ |___ |___  |  |__| |  \\    ___] |___ |___ |___ |___  |  | |__| | \\| \n\n");

			int reflectorValidInput = 0;
			do {
				printf("-> Choose the reflector (1 = A | 2 = B | 3 = C): ");
				char input[1];
				scanf("%s", input);

				// Check for valid input format
				if (sscanf(input, "%d", &reflectorChoice) != 1) {
					printf("Invalid input. Please enter a valid number.\n\n");
					continue;
				}

				// Check for valid rotor selection
				if (reflectorChoice < 1 || reflectorChoice > 3) {
					printf("Invalid rotor selection. Please enter a number between 1 and 5.\n\n");
					continue;
				}

				reflectorValidInput = 1;

			} while (!reflectorValidInput);

			switch (reflectorChoice) {
			case 1:
				userReflector = A;
				break;
			case 2:
				userReflector = B;
				break;
			case 3:
				userReflector = C;
				break;
			default:
				userReflector = B;
				break;
			}
			printf("\n-> REFLECTOR >>> %d", reflectorChoice);
			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");



			//Next is the plugboard pairing
			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("___  _    _  _ ____ ___  ____ ____ ____ ___     ____ ____ _    ____ ____ ___ _ ____ _  _ \n");
			printf("|__] |    |  | | __ |__] |  | |__| |__/ |  \\    [__  |___ |    |___ |     |  | |  | |\\ | \n");
			printf("|    |___ |__| |__] |__] |__| |  | |  \\ |__/    ___] |___ |___ |___ |___  |  | |__| | \\| \n\n");

			printf("-> Must be in alphabetical order e.g., BZ, not ZB\n");

			char plugboardPairs[20];
			int plugboardValidInput = 0;

			while (plugboardValidInput == 0) {
				printf("\n-> Enter pairs in format ABCDEF (even number of letters, no duplicates) or enter '/' for no pairs: ");
				scanf("%s", plugboardPairs);

				// Check for no configuration entered
				if (strcmp(plugboardPairs, "/") == 0) {
					printf("\n-> PLUGBOARD >>> No plugboard configuration entered.");
					plugboardValidInput = 1;
				}

				else {
					// Check for valid input
					if (strlen(plugboardPairs) > 20) {
						printf("\nError: Too many plugboard pairs entered. Maximum allowed is %d!\n\n", 10);
						continue;
					}
					else if (strlen(plugboardPairs) % 2 != 0) {
						printf("Error: Odd number of characters entered for plugboard pairs!\n\n");
						continue;
					}

					// Check for duplicates and spaces
					int invalidInput = 0;
					for (int i = 0; i < strlen(plugboardPairs); i++) {
						if (plugboardPairs[i] == ' ') {
							printf("Error: Space found in plugboard configuration!\n\n");
							invalidInput = 1;
							break;
						}

						if (isdigit(plugboardPairs[i])) {
							printf("Error: You cannot enter digits!\n\n");
							invalidInput = 1;
							break;
						}

						for (int j = i + 1; j < strlen(plugboardPairs); j++) {
							if (plugboardPairs[i] == plugboardPairs[j]) {
								printf("Error: Duplicate letter found in plugboard configuration!\n\n");
								invalidInput = 1;
								break;
							}
						}
						if (invalidInput == 1) {
							break;
						}
					}

					if (invalidInput == 1) {
						continue;
					}
				}

				for (int i = 0; i < strlen(plugboardPairs); i++) {
					plugboardPairs[i] = toupper(plugboardPairs[i]);
				}

				plugboardValidInput = 1;
			}

			printf("\n-> PLUGBOARD >>> ");

			for (int i = 0; i < strlen(plugboardPairs); i++) {
				printf("%c", plugboardPairs[i]);
			}

			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");




			// Next is the rotor start / key settings
			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("_  _ ____ _   _    ____ ____ ___ ___ _ _  _ ____ \n");
			printf("|_/  |___  \\_/     [__  |___  |   |  | |\\ | | __ \n");
			printf("| \\_ |___   |      ___] |___  |   |  | | \\| |__] \n\n");

			char rotorStart[3];
			int keyValidInput = 0;

			while (keyValidInput == 0) {
				printf("-> Enter the rotor start / key in format ABC (AAA for default): ");
				scanf("%s", rotorStart);

				// Check for valid input
				int len = strlen(rotorStart);

				if (len != 3) {
					printf("Error: Rotor start / key must be 3 characters long!\n\n");
				}
				else {
					int containsDigit = 0;

					for (int i = 0; i < len; i++) {
						if (isdigit(rotorStart[i])) {
							containsDigit = 1;
							break;
						}
					}

					if (containsDigit == 1) {
						printf("Error: There can not be any numbers or special characters!\n\n");
					}
					else {
						for (int i = 0; i < strlen(rotorStart); i++) {
							rotorStart[i] = toupper(rotorStart[i]);
						}

						keyValidInput = 1;

						setRotorStart(rotorStart);
					}
				}
			}

			printf("\n-> ROTOR START >>> ");

			for (int i = 0; i < strlen(rotorStart); i++) {
				printf("%c", rotorStart[i]);
			}

			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");




			// Next is the ring settings
			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("____ _ _  _ ____    ____ ____ ___ ___ _ _  _ ____ \n");
			printf("|__/ | |\\ | | __    [__  |___  |   |  | |\\ | | __ \n");
			printf("|  \\ | | \\| |__]    ___] |___  |   |  | | \\| |__] \n\n");

			printf("-> Note: 1 = A, 26 = Z (enter 1 for each for default)\n\n");

			int rotorRingSetting[3];
			int ringsValidInput = 0;

			while (ringsValidInput == 0) {
				printf("-> Enter the first ring setting in number format: ");
				if (scanf("%d", &rotorRingSetting[0]) != 1 || rotorRingSetting[0] < 1 || rotorRingSetting[0] > 26) {
					printf("Error: Invalid input. Please enter a number between 1 and 26.\n\n");
					// Clear input buffer
					while (getchar() != '\n');
					continue;
				}

				printf("\n-> Enter the second ring setting in number format: ");
				if (scanf("%d", &rotorRingSetting[1]) != 1 || rotorRingSetting[1] < 1 || rotorRingSetting[1] > 26) {
					printf("Error: Invalid input. Please enter a number between 1 and 26.\n\n");
					// Clear input buffer
					while (getchar() != '\n');
					continue;
				}

				printf("\n-> Enter the third ring setting in number format: ");
				if (scanf("%d", &rotorRingSetting[2]) != 1 || rotorRingSetting[2] < 1 || rotorRingSetting[2] > 26) {
					printf("Error: Invalid input. Please enter a number between 1 and 26.\n\n");
					// Clear input buffer
					while (getchar() != '\n');
					continue;
				}

				ringsValidInput = 1;
			}

			setRings(rotorRingSetting);

			printf("\n-> RING SETTING >>> ");

			for (int i = 0; i < sizeof(rotorRingSetting) / sizeof(rotorRingSetting[0]); i++) {
				printf("%d ", rotorRingSetting[i]);
			}

			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");



			// Finally, the user can enter their message
			char message[676];
			int messageValidInput = 0;

			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("_  _ ____ ____ ____ ____ ____ ____ \n");
			printf("|\\/| |___ [__  [__  |__| | __ |___ \n");
			printf("|  | |___ ___] ___] |  | |__] |___ \n\n");

			printf("-> Note: Message cannot contain numbers, special characters, or spaces\n\n");

			while (messageValidInput == 0) {
				printf("-> Enter the message: ");
				scanf("%s", message);

				// Check for valid input
				int hasNumbers = 0;
				int hasSpecialChars = 0;
				int hasSpaces = 0;
				
				for (int i = 0; i < strlen(message); i++) {
					if (isspace(message[i])) {
						hasSpaces = 1;
						break;
					}

					if (isdigit(message[i])) {
						hasNumbers = 1;
						break;
					}

					if (ispunct(message[i])) {
						hasSpecialChars = 1;
						break;
					}
				}

				if (hasNumbers || hasSpecialChars || hasSpaces) {
					printf("Error: Message cannot contain numbers, special characters, or spaces.\n\n");
				}
				else {
					for (int i = 0; i < strlen(message); i++) {
						message[i] = toupper(message[i]);
					}

					messageValidInput = 1;
				}
			}

			printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");



			printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			printf("____ _  _ ____ ____ _   _ ___  ___ ____ ___     _  _ ____ ____ ____ ____ ____ ____ \n");
			printf("|___ |\\ | |    |__/  \\_/  |__]  |  |___ |  \\    |\\/| |___ [__  [__  |__| | __ |___ \n");
			printf("|___ | \\| |___ |  \\   |   |     |  |___ |__/    |  | |___ ___] ___] |  | |__] |___ \n\n");

			printf("-> ");
			for (int i = 0; i < strlen(message); i++) {

				// If the second and third rotor are at the notch, then rotate all 3
				if ((userMiddleRotor.alphabet[0] == userMiddleRotor.notch) && (userFastRotor.alphabet[0] == userFastRotor.notch)) {
					rotorRotate(&userSlowRotor, 1, true);
					rotorRotate(&userMiddleRotor, 1, true);
					rotorRotate(&userFastRotor, 1, true);
				}

				// Double step anomaly - the rotation of the second rotor would cause all rotors to rotate
				else if (userMiddleRotor.alphabet[0] == userMiddleRotor.notch) {
					rotorRotate(&userSlowRotor, 1, true);
					rotorRotate(&userMiddleRotor, 1, true);
					rotorRotate(&userFastRotor, 1, true);
				}

				// If the third rotor is at the notch, rotate itself and the middle rotor
				else if (userFastRotor.alphabet[0] == userFastRotor.notch) {
					rotorRotate(&userMiddleRotor, 1, true);
					rotorRotate(&userFastRotor, 1, true);
				}

				// If the fast rotor is not at the notch, just rotate itself
				else {
					rotorRotate(&userFastRotor, 1, true);
				}

				char letter = message[i];

				int position = keyboardForwards(letter);

				position = plugboardForwards(plugboardPairs, position);

				position = rotorRotateForwards(userFastRotor, position);

				position = rotorRotateForwards(userMiddleRotor, position);

				position = rotorRotateForwards(userSlowRotor, position);

				position = reflect(userReflector, position);

				position = rotorRotateBackwards(userSlowRotor, position);

				position = rotorRotateBackwards(userMiddleRotor, position);

				position = rotorRotateBackwards(userFastRotor, position);

				position = plugboardBackwards(plugboardPairs, position);

				letter = keyboardBackwards(position);
				printf("%c ", letter);
			}
			printf("\n");
			break;
		}

		else if (startQuit == 2) {
			printf("\nBye bye :(......\n");
			return 0;
		}

		else {
			printf("Error: Invalid input\n\n");
		}
	}
	
	exit(0);
	return 0;
}