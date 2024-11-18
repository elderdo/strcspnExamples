#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char buffer[256] = "<tag1><tag2>stuff</tag2></tag1>";


  char tagName[256] = "";
  char content[256] = "";
  char* ptr = buffer;

  if (sscanf(ptr,"<%s", tagName) == 1) {
    tagName[strcspn(tagName,"> ")] = '\0';
    printf("tagname=%s\n", tagName);
    printf("buffer=%s\n", buffer);
  }
}

