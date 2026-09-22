#include <stdio.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

void xorEncryptDecrypt(char *data, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char mode[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", mode);
	scanf("%*c"); // Consume the newline character left by scanf

    if (strcmp(mode, "encrypt") == 0) {
        char message[MAX_KEY_LENGTH];
        char filename[MAX_KEY_LENGTH];
        char key[MAX_KEY_LENGTH];

        printf("Enter the message to encrypt: ");
        fgets(message, MAX_KEY_LENGTH, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline

        printf("Enter the filename to save the encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            fprintf(stderr, "Error opening file for writing.\n");
            return 1;
        }

        xorEncryptDecrypt(message, key);
        fwrite(message, sizeof(char), strlen(message), file);
        fclose(file);
    } else if (strcmp(mode, "decrypt") == 0) {
        char filename[MAX_KEY_LENGTH];
        char key[MAX_KEY_LENGTH];

        printf("Enter the filename to decrypt: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file for reading.\n");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encryptedData = (char *)malloc((fileSize + 1) * sizeof(char));
        if (encryptedData == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            fclose(file);
            return 1;
        }

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        xorEncryptDecrypt(encryptedData, key);

        printf("Decrypted data: %s\n", encryptedData);

        free(encryptedData);
    } else {
        fprintf(stderr, "Invalid mode.\n");
        return 1;
    }

    return 0;
}