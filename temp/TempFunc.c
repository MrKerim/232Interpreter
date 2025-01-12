#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ArrayTable {
    char name[10];
    int dim;
    char size1[10];
    char size2[10];
}; 
struct ArrayTable ST[20];
int AT_index = 0;

char* declaration(char* lhs, char* rhs1, char* spaces) {
    char* return_array = malloc(50); 
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }
    
    strcpy(ST[AT_index].name, lhs); 

    int i = 0;
    int size_index = 0;
    ST[AT_index].dim = 1;
    while(rhs1[i] != ')' && rhs1[i] != '\0') {
        if(rhs1[i] == ','){
            ST[AT_index].dim = 2;
            size_index++;
            break;
        } else {
            ST[AT_index].size1[size_index] = rhs1[i];
            size_index++;
        }
        i++;
    } 
    ST[AT_index].size1[size_index] = '\0';

    size_index = 0;
    if(ST[AT_index].dim == 2){
        while(rhs1[i] != ')' && rhs1[i] != '\0'){
            i++;
            ST[AT_index].size2[size_index] = rhs1[i];
            size_index++;
        } 
        ST[AT_index].size2[size_index-1] = '\0'; 
        sprintf(return_array, "%sint %s[%s][%s];\n", spaces, ST[AT_index].name, ST[AT_index].size1, ST[AT_index].size2);
    } else {
        sprintf(return_array, "%sint %s[%s];\n", spaces, ST[AT_index].name, ST[AT_index].size1);
    }
    AT_index++;
    return return_array;
}

char* read(char* lhs, char* rhs1, char* spaces) {
    char* return_array = malloc(2048); 
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < AT_index; i++) { 
        if (strcmp(ST[i].name, lhs) == 0) {
            sprintf(return_array,
                "%sFILE *myFile;\n"
                "%smyFile = fopen(%s, \"r\");\n"
                "%sfor (int i = 0; i < %s; i++){\n"
                "%s    fscanf(myFile, \"%%d\", %s[i]);\n"
                "%s}\n"
                "%sfclose(myFile);\n", spaces, spaces, rhs1, spaces, ST[i].size1, spaces, ST[i].name, spaces, spaces);
            return return_array; // Doğru eşleşme bulununca hemen çık
        }
    }

    // Hiçbir eşleşme bulunamazsa bir hata döndür
    sprintf(return_array, "/* Error: Array %s not found in ArrayTable */\n", lhs);
    return return_array;
}


char* dot_product(char* lhs, char* rhs1, char* rhs2, char* spaces) {
    char* return_array = malloc(2048); 
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }
    int size = 0;
    int found_rhs1 = 0;
    int found_rhs2 = 0;

    for (int i = 0; i < AT_index; i++) {
        if (strcmp(ST[i].name, rhs1) == 0) {
            size = atoi(ST[i].size1);
            found_rhs1 = 1;
        }
        if (strcmp(ST[i].name, rhs2) == 0) {
            found_rhs2 = 1;
        }
    }

    if (!found_rhs1 || !found_rhs2) {
        sprintf(return_array, "/* Error: Arrays not found or dimensions mismatch */\n");
        return return_array;
    }

    sprintf(return_array, "%sP_dot = 0;\n", spaces);
    for (int i = 0; i < size; i++) {
        char buffer[100];
        sprintf(buffer, "%sP_dot += %s[%d] * %s[%d];\n", spaces, rhs1, i, rhs2, i);
        strcat(return_array, buffer);
    }
    char buffer[50]; 
    sprintf(buffer, "%sint %s = P_dot;\n", spaces, lhs);
    strcat(return_array, buffer);
    return return_array;
}

char* mmult(char* lhs, char* rhs1, char* rhs2, char* spaces) {
    char* return_array = malloc(8192); 
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }
    int rows1 = 0, cols1 = 0, rows2 = 0, cols2 = 0;
    int found_rhs1 = 0;
    int found_rhs2 = 0;

    for (int i = 0; i < AT_index; i++) {
        if (strcmp(ST[i].name, rhs1) == 0) {
            rows1 = atoi(ST[i].size1);
            cols1 = atoi(ST[i].size2);
            found_rhs1 = 1;
        }
        if (strcmp(ST[i].name, rhs2) == 0) {
            rows2 = atoi(ST[i].size1);
            cols2 = atoi(ST[i].size2);
            found_rhs2 = 1;
        }
    }

    if (!found_rhs1 || !found_rhs2 || cols1 != rows2) {
        sprintf(return_array, "/* Error: Arrays not found or dimensions mismatch */\n");
        return return_array;
    }

    sprintf(return_array, "%sint %s[%d][%d];\n", spaces, lhs, rows1, cols2);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            char buffer[50];
            sprintf(buffer, "%s%s[%d][%d] = 0;\n", spaces, lhs, i, j);
            strcat(return_array, buffer);
            for (int k = 0; k < cols1; k++) {
                sprintf(buffer, "%s%s[%d][%d] += %s[%d][%d] * %s[%d][%d];\n", spaces, lhs, i, j, rhs1, i, k, rhs2, k, j);
                strcat(return_array, buffer);
            }
        }
    }
    return return_array;
}

char* sum(char* lhs) {
    char* return_array = malloc(1024);
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }
    int size1 = 0, size2 = 0;
    int dimen = 0;
    int found_lhs = 0;
    for (int i = 0; i < 20; i++) {
        if (strcmp(ST[i].name, lhs) == 0) {
            dimen = ST[i].dim;
            size1 = atoi(ST[i].size1);
            if (dimen == 2) {
                size2 = atoi(ST[i].size2);
            }
            found_lhs = 1;
            break;
        }
    }
    if (!found_lhs) {
        sprintf(return_array, "/* Error: Arrays not found or dimensions mismatch */\n");
        return return_array;
    }

    if (dimen == 1) {
        sprintf(return_array,
                "P_sum = 0;\n"
                "for (int i = 0; i < %d; i++) {\n"
                "    P_sum += %s[i];\n"
                "}\n",
                size1, lhs);
    } else if (dimen == 2) {
        sprintf(return_array,
                "P_sum = 0;\n"
                "for (int i = 0; i < %d; i++) {\n"
                "    for (int j = 0; j < %d; j++) {\n"
                "        P_sum += %s[i][j];\n"
                "    }\n"
                "}\n",
                size1, size2, lhs);
    }
    return return_array;
}

char* aver(char* lhs) {
    char* return_array = malloc(1024);
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }
    int size1 = 0, size2 = 0; 
    int dimen = 0;
    int found_lhs = 0;
    for (int i = 0; i < 20; i++) {
        if (strcmp(ST[i].name, lhs) == 0) {
            dimen = ST[i].dim;
            size1 = atoi(ST[i].size1);
            if (dimen == 2) {
                size2 = atoi(ST[i].size2);
            }
            found_lhs = 1;
            break;
        }
    }

    if (!found_lhs) {
        sprintf(return_array, "/* Error: Array %s not found */\n", lhs);
        return return_array;
    }

    if (dimen == 1) {
        if (size1 == 0) {
            sprintf(return_array, "/* Error: Division by zero */\n");
        } else {
            sprintf(return_array,
                    "P_aver = 0;\n"
                    "for (int i = 0; i < %d; i++) {\n"
                    "    P_aver += %s[i];\n"
                    "}\n"
                    "P_aver /= %d;\n",
                    size1, lhs, size1);
        }
    } else if (dimen == 2) {
        int total_elements = size1 * size2;
        if (total_elements == 0) {
            sprintf(return_array, "/* Error: Division by zero */\n");
        } else {
            sprintf(return_array,
                    "P_aver = 0;\n"
                    "int total_elements = %d;\n"
                    "for (int i = 0; i < %d; i++) {\n"
                    "    for (int j = 0; j < %d; j++) {\n"
                    "        P_aver += %s[i][j];\n"
                    "    }\n"
                    "}\n"
                    "P_aver /= total_elements;\n",
                    total_elements, size1, size2, lhs);
        }
    }

    return return_array;
}

char* copy(char lhs[], char rhs[]) {
    char* return_array = malloc(100);
    int dim;
    char* size1 = malloc(10);
    char* size2 = malloc(10);
    for(int j = 0; j < 20; j++) {
        if(strcmp(ST[j].name, lhs) == 0) {
            dim = ST[j].dim;
            size1 = ST[j].size1;
            size2 = ST[j].size2;
        }
    }
    if (dim == 1) {
        sprintf(return_array, "\tfor(int i = 0; i < %s; i++) {\n\t\t%s[i] = %s[i];\n\t}\n", size1, lhs, rhs);
    } else if(dim == 2) {
        sprintf(return_array, "\tfor (int i=0 ; i < %s; i++) {\n\t\tfor (int j=0 ; j < %s; j++) {\n\t\t\t%s[i][j] = %s[i][j];\n\t\t}\n\t}\n", size1, size2, lhs, rhs);
    }

    return return_array;
}

char* init(char lhs[], char rhs[]) {
    char* return_array = malloc(100);
    int dim;
    char* size1 = malloc(10);
    char* size2 = malloc(10);
    for(int j = 0; j < 20; j++) {
        if(strcmp(ST[j].name, lhs) == 0) {
            dim = ST[j].dim;
            size1 = ST[j].size1;
            size2 = ST[j].size2;
        }
    }
    if (dim == 1) {
        sprintf(return_array, "\tfor(int i = 0; i < %s; i++) {\n\t\t%s[i] = %s;\n\t}\n", size1, lhs, rhs);
    } else if(dim == 2) {
        sprintf(return_array, "\tfor (int i=0 ; i < %s; i++) {\n\t\tfor (int j=0 ; j < %s; j++) {\n\t\t\t%s[i][j] = %s;\n\t\t}\n\t}\n", size1, size2, lhs, rhs);
    }

    return return_array;
}

char* diag(char* lhs, char* rhs) {
    char* return_array = malloc(1024);
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }

    int size = 0;
    int found_rhs = 0;
    for (int i = 0; i < 20; i++) {
        if (strcmp(ST[i].name, rhs) == 0 && ST[i].dim == 2) {
            size = atoi(ST[i].size1);
            found_rhs = 1;
            break;
        }
    }

    if (!found_rhs) {
        sprintf(return_array, "/* Error: 2D array %s not found or not square */\n", rhs);
        return return_array;
    }

    sprintf(return_array,
            "for (int i = 0; i < %d; i++) {\n"
            "    %s[i] = %s[i][i];\n"
            "}\n",
            size, lhs, rhs);

    return return_array;
}

char* exchange(char* lhs, int idx1_lhs, int idx2_lhs, char* rhs, int idx1_rhs, int idx2_rhs) {
    char* return_array = malloc(1024);
    if (!return_array) {
        perror("Failed to allocate memory for return_array");
        exit(EXIT_FAILURE);
    }

    sprintf(return_array,
            "int temp = %s[%d][%d];\n"
            "%s[%d][%d] = %s[%d][%d];\n"
            "%s[%d][%d] = temp;\n",
            lhs, idx1_lhs, idx2_lhs,
            lhs, idx1_lhs, idx2_lhs, rhs, idx1_rhs, idx2_rhs,
            rhs, idx1_rhs, idx2_rhs);

    return return_array;
}

char* print(char* lhs) {

    int size1 = 0, size2 = 0, dimen = 0, found_lhs = 0;

    // Array Table'dan array bilgilerini kontrol et
    for (int i = 0; i < 20; i++) {
        if (strcmp(ST[i].symbol, lhs) == 0) {
            dimen = ST[i].dim;
            size1 = atoi(St[i].size1);
            if (dimen == 2) {
                size2 = atoi(ST[i].size2);
            }
            found_lhs = 1;
            break;
        }
    }

    if (!found_lhs) {
        sprintf(return_array, "/* Error: Array %s not found */\n", lhs);
        return return_array;
    }

    // 1D Diziler için yazdırma
    if (dimen == 1) {
        sprintf(return_array, 
                "for (int i = 0; i < %d; i++) {\n"
                "    printf(\"%%d \", %s[i]);\n"
                "}\n"
                "printf(\"\\n\");\n",
                size1, lhs);
    } 
    // 2D Diziler için yazdırma
    else if (dimen == 2) {
        sprintf(return_array, 
                "for (int i = 0; i < %d; i++) {\n"
                "    for (int j = 0; j < %d; j++) {\n"
                "        printf(\"%%d \", %s[i][j]);\n"
                "    }\n"
                "    printf(\"\\n\");\n"
                "}\n",
                size1, size2, lhs);
    }

    return return_array;
}

