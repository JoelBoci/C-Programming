#include <stdio.h>
#include <string.h>

char caeserCipherEncryption(char message, int key) {	
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz", cipher[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index;

	for (int i = 0; i < 26; i++) {
		if (message == alphabet[i]) {
			index = i;

			return cipher[(index + key) % 26];
		}
	}

	return message;
}

char caeserCipherDecryption(char message, int key) {
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz", plain[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index;

	for (int i = 0; i < 26; i++) {
		if (message == alphabet[i]) {
			index = i;

			return plain[(26 + (index - key)) % 26];
		}
	}
		
	return message;
}

int main(int argc, char* argv[]) {

	printf("Welcome to the Caeser Cipher Program\n");

	int choice;
	do {
		printf("\nPress (1) to begin or (2) to quit: ");
		scanf_s("%d", &choice);

	} while (choice != 1 && choice != 2);

	if (choice == 1) {

		// Encryption

		/*char plainText[50] = "hello world";
		char cipherText[50];
		
		printf("\nPlaintext: %s\n", plainText);
		for (int i = 0; i < 50; i++) {
			cipherText[i] = caeserCipherEncryption(plainText[i], 3);
		}

		printf("Ciphertext: %s\n", cipherText);*/





		// Decryption

		/*char cipherText[50] = "vhfxulwb dqg sulydfb";
		char plainText[50];

		printf("\nCiphertext: %s\n", cipherText);
		for (int i = 0; i < 50; i++) {
			plainText[i] = caeserCipherDecryption(cipherText[i], 3);
		}

		printf("Plaintext: %s\n", plainText);*/
	}
	else {
		exit(0);
	}
	
	return 0;
}