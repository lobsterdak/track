#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>



int EMPTY_FILE = 0;

char* input_poem (int *num_of_strings, const char *name_of_file){
    int file_name;
    struct stat buff;
    int i;
    if ((file_name = open(name_of_file, O_RDONLY)) == -1) {
        return NULL;
    }
    if(fstat(file_name, &buff) == -1){
        return NULL;
    }
    if (buff.st_size == 0){
        EMPTY_FILE = 1;
        return NULL;
    }
    char *massiv = (char*)malloc(sizeof(char) * (buff.st_size + 1));
    if(read(file_name, massiv + 1, buff.st_size) == -1){
        return 0;
    }
    massiv[0] = '\0';
    (*num_of_strings) = 0;
    for (i = 1; massiv[i]; i++){
        if (massiv[i] == '\n'){
            massiv[i] = '\0';
            (*num_of_strings)++;
        }
    }
    close(file_name);
    return massiv;
}

char** create_pointers (char *massiv, int num_of_strings){
    char **pointers = (char**)malloc(sizeof(char*) * num_of_strings);
    int i = 0, j = 0;
    while (j < num_of_strings){
        if(massiv[i] == '\0'){
            pointers[j] = massiv + i + 1;
            j++;
        }
        i++;
    }
    return pointers;
}

char** create_pointers_back (char *massiv, int num_of_strings){
    char **pointers_back = (char**)malloc(sizeof(char*) * num_of_strings);
    int i = 1, j = 0;
    while (j < num_of_strings){
        if(massiv[i] == '\0'){
            pointers_back[j] = massiv + i - 1;
            j++;
        }
        i++;
    }
    return pointers_back;
}

void print_strings (char **pointers,int num_of_strings){
    int i;
    for (i = 0; i < num_of_strings; i++){
        printf("%s\n", pointers[i]);
    }
}

void print_in_file (char **pointers, int num_of_strings, const char *str){
    int i;
    FILE *file_out = fopen(str, "w+");
    char a[1] = {'\n'};
    for (i = 0; i < num_of_strings; i++){
        
        fwrite(pointers[i], sizeof(char), strlen(pointers[i]), file_out);
        if (i != num_of_strings - 1)
            fwrite(a, sizeof(char), 1, file_out);
    }
    fclose(file_out);
}

int compare (const void *s1, const void *s2){
    int i = 0, j = 0;
    char *s_1 = *((char**)s1);
    char *s_2 = *((char**)s2);
    if ((s_1[i + 1] == '\0') || (s_2[j + 1] == '\0')){
        if (s_2[j + 1] == '\0') 
            return 1;
        else if (s_1[i + 1] == '\0')
                return 0;
            else 
                return -1;
    }
    for (i = 0, j = 0; (s_1[i + 1] != '\0') && (s_2[j + 1] != '\0'); i++, j++){
        while((isalpha(s_1[i]) == 0) && (s_1[i + 1] != '\0'))
            i++;
        while((isalpha(s_2[j]) == 0) && (s_2[j + 1] != '\0'))
            j++;
        if ((s_1[i + 1] == '\0') || (s_2[j + 1] == '\0')){
            if (s_2[j + 1] == '\0') 
                return 1;
            else if (s_1[i + 1] == '\0')
                    return 0;
                else 
                    return -1;
        }
        else if (tolower(s_1[i]) < tolower(s_2[j]))
                return -1;
            else if (tolower(s_1[i]) > tolower(s_2[j]))
                    return 1;
                else
                    continue;
    }
    return 0;
}

int compare_back (const void *s1, const void *s2){
    int i = 0, j = 0;
    char *s_1 = *((char**)s1);
    char *s_2 = *((char**)s2);
    if ((s_1[i - 1] == '\0') || (s_2[j - 1] == '\0')){
        if (s_2[j - 1] == '\0') 
            return 1;
        else if (s_1[i - 1] == '\0')
                return 0;
            else 
                return -1;
    }
    for (i = 0, j = 0; (s_1[i - 1] != '\0') && (s_2[j - 1] != '\0'); i--, j--){
        while((isalpha(s_1[i]) == 0) && (s_1[i - 1] != '\0'))
            i--;
        while((isalpha(s_2[j]) == 0) && (s_2[j - 1] != '\0'))
            j--;
        if ((s_1[i - 1] == '\0') || (s_2[j - 1] == '\0')){
            if (s_2[j - 1] == '\0') 
                return 1;
            else if (s_1[i - 1] == '\0')
                    return 0;
                else 
                    return -1;
        }
        else if (tolower(s_1[i]) < tolower(s_2[j]))
                return -1;
            else if (tolower(s_1[i]) > tolower(s_2[j]))
                    return 1;
                else
                    continue;
    }
    return 0;
}

void replace_pointers (char ***pointers_back, int num_of_strings){
    int i = 0, j = 0;
    for (i = 0; i < num_of_strings; i++){
        j = 0; 
        while (*(*(*pointers_back + i) + j) != '\0'){
            j--;
        }
        *(*pointers_back + i) = (*(*pointers_back + i) + j + 1);
    }
}

int main () {
    
    char *massiv;
    int num_of_strings = 0;
    char **pointers, **pointers_back;
    massiv = input_poem(&num_of_strings, "onegyn.txt");
    if (massiv == NULL){
        if (EMPTY_FILE)
            printf("EMPTY FILE\n");
        else 
            perror("ERROR");
        return 0;
    }
    pointers = create_pointers(massiv, num_of_strings);
    pointers_back = create_pointers_back(massiv, num_of_strings);
    printf("\nСтроки отсортированы по алфавиту c конца, результат записан в файл back_onegyn_out.txt\n");
    qsort(pointers_back, (size_t)num_of_strings, sizeof(char*), compare_back);
    replace_pointers(&pointers_back, num_of_strings);
    print_in_file(pointers_back, num_of_strings, "back_onegyn_out.txt");
    printf("\nСтроки отсортированы по алфавиту, результат записан в файл onegyn_out.txt\n");
    qsort(pointers, (size_t)num_of_strings, sizeof(char*), compare);
    print_in_file(pointers, num_of_strings, "onegyn_out.txt");
    return 0;
}
