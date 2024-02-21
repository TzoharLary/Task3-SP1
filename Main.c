#pragma once
#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    StrList *list = StrList_alloc(); // Initialize your list
    char buffer[1024];
    int option, index, count, numofString;

    do{

        scanf("%d", &option);
        getchar(); // Consume the newline character

        switch (option) {
            // get from the user the string and add /0 in the end of the string that the user write
            case 1:
                scanf("%d", &numofString);
                getchar(); // Consume the newline character left by scanf
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                char *token = strtok(buffer, " "); // Start tokenizing the input
                while (token != NULL && numofString > 0) {
                StrList_insertLast(list, token); // Add the token to the list
                token = strtok(NULL, " "); // Continue to the next token
                numofString--; // Decrement the count of strings to insert  
    }
                break;
            case 2:
                scanf("%d", &index);
                getchar(); // Consume the newline character
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
                StrList_insertAt(list, buffer, index); // insert the string in the index that the user give
                break;
            case 3:
                StrList_print(list);//print the string that recieved from the user
                break;
            case 4:
                printf("%zu\n", StrList_size(list)); // print the lenght of the string
                break;
            case 5:
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7:
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
                printf("%d\n", StrList_count(list, buffer));
                break;
            case 8:
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
                StrList_remove(list, buffer);
                break;
            case 9:
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                 while (StrList_size(list) > 0) {
                 StrList_removeAt(list, 0); // Always remove the first element
                 }
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                StrList_isSorted(list);
                break;
            case 0:
                break;
            default:
                break;
        }
        }
        
        while (option != 0);

    StrList_free(list); // Free the list
    return 0;
}
