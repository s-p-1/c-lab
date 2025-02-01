#include<stdio.h>
#include<stdlib.h>

void resize_adj_list(int **adj_list, int *size) {
    int new_size = (*size) * 2;  // Doubling the size
    int *new_list = (int *)realloc(*adj_list, new_size * sizeof(int));

    if (new_list == NULL) {
        printf("Memory Failure\n");
        return;
    }

    *adj_list = new_list;
    *size = new_size;  // Update the size
}

// int main() {
//     int size = 5;
//     int *p = (int *)malloc(size * sizeof(int));

//     if (p == NULL) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }

//     // Initialize values
//     for (int i = 0; i < size; i++) {
//         p[i] = i + 1;
//     }

//     printf("Before resize: ");
//     for (int i = 0; i < size; i++) {
//         printf("%d ", p[i]);
//     }
//     printf("\n");

//     // Resize adjacency list
//     resize_adj_list(&p, &size);

//     printf("After resize: ");
//     for (int i = 0; i < size; i++) {
//         printf("%d ", p[i]);
//     }
//     printf("\n");

//     free(p);  // Free allocated memory
//     return 0;
// }
