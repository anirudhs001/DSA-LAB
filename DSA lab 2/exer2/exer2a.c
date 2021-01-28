
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char* argv[]) {
    //open file to read from
    if (argc != 3) {
        printf("Usage: $./thisfile file1 file2 \ncopies everything from file1 to file2\n");
        exit(1);
    }
    FILE* fr = fopen(argv[1], "r+");

    //open file to write to 
    FILE* fw = fopen(argv[2], "w+");

    if (fr == NULL || fw == NULL) {
        printf("file does not exist");
        fclose(fr);
        fclose(fw);
        exit(1);
    }
    char c;
    while (fscanf(fr, "%c", &c) != EOF) {
        printf("%c", c);
        if (fprintf(fw, "%c", c) < 0) {
            printf("\n some error occured, closing all files!");
            fclose(fr);
            fclose(fw);
            exit(2);
        }
    }   
    fclose(fr);
    fclose(fw);
    printf("\nDone copying everything from file1.txt to file2.txt\n");
    return 0;
}
