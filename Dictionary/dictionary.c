#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 50
#define MAX_MEANING 256
#define DICTIONARY_FILE "dictionary.txt"

void add_word();
void search_word();
void display_dictionary();
void clear_input_buffer();
void to_lowercase(char *str);

int main() {
    int choice;
    
    while (1) {
        printf("\n==== Simple Word Dictionary ====\n");
        printf("1. Add a Word\n");
        printf("2. Search for a Word\n");
        printf("3. Display All Words\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                add_word();
                break;
            case 2:
                search_word();
                break;
            case 3:
                display_dictionary();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to add a word and its meaning
void add_word() {
    char word[MAX_WORD], meaning[MAX_MEANING];
    FILE *file = fopen(DICTIONARY_FILE, "a");

    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("Enter word: ");
    scanf("%s", word);
    clear_input_buffer();
    to_lowercase(word);

    printf("Enter meaning: ");
    fgets(meaning, MAX_MEANING, stdin);
    meaning[strcspn(meaning, "\n")] = '\0'; // Remove newline character

    fprintf(file, "%s:%s\n", word, meaning);
    fclose(file);

    printf("Word added successfully!\n");
}

// Function to search for a word (case insensitive)
void search_word() {
    char word[MAX_WORD], file_word[MAX_WORD], meaning[MAX_MEANING], line[300];
    FILE *file = fopen(DICTIONARY_FILE, "r");

    if (!file) {
        perror("The dictionary is empty.");
        return;
    }

    printf("Enter word to search: ");
    scanf("%s", word);
    to_lowercase(word);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^:]:%[^\n]", file_word, meaning);
        to_lowercase(file_word);
        if (strcmp(word, file_word) == 0) {
            printf("Meaning: %s\n", meaning);
            fclose(file);
            return;
        }
    }

    printf("Word not found in dictionary.\n");
    fclose(file);
}

// Function to display all words
void display_dictionary() {
    char line[300];
    FILE *file = fopen(DICTIONARY_FILE, "r");

    if (!file) {
        printf("Dictionary is empty.\n");
        return;
    }

    // Check if file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("Dictionary is empty.\n");
        fclose(file);
        return;
    }
    rewind(file);

    printf("\n=== Dictionary Contents ===\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

// Function to clear input buffer
void clear_input_buffer() {
    while (getchar() != '\n');
}
