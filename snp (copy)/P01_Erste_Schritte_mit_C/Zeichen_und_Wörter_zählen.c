#include <stdio.h>

int main(void) {
  int charCount = 0;
  int wordCount = 0;
  char currentChar;
  int inWord = 0; // 0 = false, 1 = true

  printf("Geben Sie eine Zeile Text ein:\n");

  while ((currentChar = getchar()) != '\n') {
    charCount++;

    // Wortzählung
    if (currentChar == ' ' || currentChar == '\t') {
      if (inWord) {
        inWord = 0; // Ende eines Wortes
      }
    } else {
      if (!inWord) {
        inWord = 1; // Beginn eines Wortes
        wordCount++;
      }
    }
  }

  printf("Zeichenzahl: %d\n", charCount);
  printf("Wortanzahl: %d\n", wordCount);

  return 0;
}
