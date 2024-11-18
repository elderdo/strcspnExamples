#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parseLongLine(FILE *file) {
    char buffer[256];
    char *line = NULL;
    size_t lineLen = 0;
    int lineCount = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        size_t bufferLen = strlen(buffer);

        // If buffer ends without a newline, it's incomplete
        while (buffer[bufferLen - 1] != '\n' && !feof(file)) {
            line = realloc(line, lineLen + bufferLen + 1);
            memcpy(line + lineLen, buffer, bufferLen);
            lineLen += bufferLen;

            // Read the next chunk
            if (fgets(buffer, sizeof(buffer), file)) {
                bufferLen = strlen(buffer);
            } else {
                break; // End of file
            }
        }

        // Complete line
        line = realloc(line, lineLen + bufferLen + 1);
        memcpy(line + lineLen, buffer, bufferLen + 1);
        lineLen += bufferLen;
        lineCount++;

        // Process the complete line
        printf("%d. Processed line: %s\n", lineCount, line);
        printf("linesize=%d\n", strlen(line));

        // Reset line
        free(line);
        line = NULL;
        lineLen = 0;
    }
    free(line);
}

int main() {
    FILE *file = fopen("yourfile.xml", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    parseLongLine(file);
    fclose(file);
    return 0;
}

