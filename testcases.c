#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILENAME 256

void check_test_case(const char *output_file, const char *expected_file, const char *test_name) {
    char command[MAX_FILENAME * 2];
    snprintf(command, sizeof(command), "diff -q %s %s", output_file, expected_file);

    int status = system(command);

    if (status == 0) {
        printf("Test %s PASSED\n", test_name);
    } else {
        printf("Test %s FAILED\n", test_name);
    }
}

int main() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "output", 6) == 0 && strstr(entry->d_name, ".txt")) {
            char expected_file[MAX_FILENAME];
            snprintf(expected_file, sizeof(expected_file), "expected_output%s", entry->d_name + 6); // Extract number

            check_test_case(entry->d_name, expected_file, entry->d_name);
        }
    }

    closedir(dir);
    printf("\nAll tests completed!\n");
    return 0;
}
