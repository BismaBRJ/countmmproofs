#include <stdio.h>

int counter_in_file(FILE *fp, char *key) { 
    if ((fp == NULL) || (key == NULL)) {
        return -1; // error code I guess
    }
    if (*key == '\0') {
        return -2; // another error code
    }

    char *ptr_key = key;
    int key_count = 0;
    char to_check, to_satisfy;

    to_check = fgetc(fp);
    while (to_check != EOF) {
        to_satisfy = *ptr_key;

        if (to_check == to_satisfy) {
            ptr_key += 1; // advance the pointer (to next char)
        } else {
            ptr_key = key; // reset key scanning (match fail in middle)
        }
        if (*ptr_key == '\0') {
            key_count += 1;
            ptr_key = key;
        }

        to_check = fgetc(fp); // advance to next char
    }

    return key_count;
}

int main(int args, char **kwargs) {
    // needs exactly one non-executable-name argument: the file name
    // therefore args must be 2
    // for now, anything other than the first file is ignored
    // (in the future, multiple databases could be counted,
    // where the arguments are treated as .mm file names,
    // then really using a for loop to count for each file)

    // <= one arg -> only executable name -> zero file names given
    if (args <= 1) {
        puts("Please specify file name");
        puts("(pass it in while calling the executable)");
        printf("Syntax: %s the_metamath_database.mm\n", kwargs[0]);
        return 0;
    }

    // otherwise, at least one file -> read the first file
    char *file_name = kwargs[1];
    FILE *fp = fopen(file_name, "r");

    // if file not found, error
    if (fp == NULL) {
        printf("Error: file \"");
        printf("%s", file_name);
        printf("\" not found\n");
        return 0;
    }

    puts("Counting...");
    int proofs_count = counter_in_file(fp, "$=");
    printf("Found %d occurrences of $=\n", proofs_count);

    printf("(Over)estimate of number of proofs in \"");
    printf("%s", file_name);
    printf("\": %d\n", proofs_count);

    fclose(fp);

    return 0;
}
