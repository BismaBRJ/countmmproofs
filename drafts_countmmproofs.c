// drafts_countmmproofs.c
// created Saturday, 16 November 2024
// by BismaBRJ
// https://github.com/BismaBRJ/countmmproofs

// last updated Saturday, 16 November 2024

#include <stdio.h>

int counter_in_str(char *text, char *key) {
    if ((text == NULL) || (key == NULL)) { // points to nowhere
        return -1; // "error", I guess
    }
    if (*key == '\0') { // annoying edge case: key is empty string
        return -1; // could be infinity in theory, perhaps
    }

    char *ptr_text = text;
    char *ptr_key = key;
    int key_count = 0;
    char to_check, to_satisfy;

    while (*ptr_text != '\0') {
        to_check = *ptr_text; // dereference
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

        ptr_text += 1; // advance the pointer (to next char)
    }

    return key_count;
}

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

void test_1() {
    int thing = counter_in_str("abcabcabca", "bc");
    printf("count: %d\n", thing);
}

void test_2() {
    FILE *fp;
    fp = fopen("./smalltest.txt", "r");

    char cur_char;
    cur_char = fgetc(fp);
    while (cur_char != EOF) {
        printf("%c", cur_char);
        cur_char = fgetc(fp);
    }
    
    fclose(fp);
}

void test_3() {
    FILE *fp;
    fp = fopen("./smalltest.txt", "r");
    puts("Result:");
    int howmany = counter_in_file(fp, "$=");
    fclose(fp);
    printf("Count: %d\n", howmany);
    puts("Done!");
}

void test_4() {
    FILE *fp;
    fp = fopen("./set.mm", "r");
    puts("Result:");
    int howmany = counter_in_file(fp, "$=");
    fclose(fp);
    printf("Count: %d\n", howmany);
    puts("Done!");
}

/* drafts driver code:
int main() {
    // test_1();
    // test_2();
    // test_3();

    test_4();
    // post running note: took four seconds. Result: 43565
    // Using file set.mm per 16 November 2024
    // of commit:
// github.com/metamath/set.mm/commit/2813f8eb3a62e829c4c7afea58513c2d77d4c98f

    return 0;
}
*/

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
