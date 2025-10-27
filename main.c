/*
* Filename: main.c
* Description: Does operations with vectors
* Author: Aden Yance
* Date: 10/21/2025
* compile with a Makefile then ./vectorlab
Changing it for the github
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vect.h"
#include "DM.h"

int main(void) {
    char line[250];
    bool running = true;

    // Initialize dynamic memory storage
    if (!init_vector_storage(10)) {
        printf("Error: Failed to initialize vector storage\n");
        return 1;
    }

    printf("Vector Calculator ready.\n");
    printf("Type -h for a list of commands\n");
    printf("VectorLab> ");

    while (running && fgets(line, sizeof(line), stdin)) {

        // remove newline at end
        line[strcspn(line, "\n")] = '\0';

        // make commas act like spaces
        for (char *p = line; *p; ++p) {
            if (*p == ',') *p = ' ';
        }

        // Quit command
        if (strcmp(line, "quit") == 0) {
            running = false;
        }

        // Help command
        else if (strcmp(line, "-h") == 0) {
            help();
        }

        // List all vectors command
        else if (strcmp(line, "list") == 0) {
            list();
        }

        // Clear memory command
        else if (strcmp(line, "clear") == 0) {
            clear();
        }

        // Save command
        else if (strcmp(line, "save") == 0) {
            printf("Enter filename to save vectors (or press Enter for default 'vectors.csv'): ");
            char save_filename[100];
            if (fgets(save_filename, sizeof(save_filename), stdin)) {
                // Remove newline
                save_filename[strcspn(save_filename, "\n")] = '\0';
                
                // Use default if empty
                if (strlen(save_filename) == 0) {
                    strcpy(save_filename, "vectors.csv");
                }
                
                save(save_filename);
            }
        }

        // Load command
        else if (strcmp(line, "load") == 0) {
            printf("Enter filename to load vectors from: ");
            char load_filename[100];
            if (fgets(load_filename, sizeof(load_filename), stdin)) {
                // Remove newline
                load_filename[strcspn(load_filename, "\n")] = '\0';
                
                if (strlen(load_filename) > 0) {
                    loadVect(load_filename);
                } else {
                    printf("Error: No filename provided\n");
                }
            }
        }

        // Assignment: name = x y z command    
        else {
            char name[NAME_LEN];
            float x, y, z;
            char extra;

            if (sscanf(line, " %29s = %f %f %f %c", name, &x, &y, &z, &extra) == 4) {
                int st = newVect(name, x, y, z);
                if (st == 0) {
                    printf("Array full.\n");
                } else {
                    printf("%s = %.3f %.3f %.3f\n", name, x, y, z);
                }
            }

            // Operation with assignment: result = a + b command
            else {
                char result[NAME_LEN], Aname[NAME_LEN], Bname[NAME_LEN];
                char op;
                float num;
                char extra2;

                // result = a + b  or  result = a - b command
                if (sscanf(line, " %29s = %29s %c %29s %c", result, Aname, &op, Bname, &extra2) == 4 &&
                    (op == '+' || op == '-')) {
                    int ia = findVect(Aname);
                    int ib = findVect(Bname);
                    if (ia < 0 || ib < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R;
                        if (op == '+')
                            R = addvec(myVector[ia], myVector[ib]);
                        else
                            R = subvec(myVector[ia], myVector[ib]);
                        newVect(result, R.x, R.y, R.z);
                        printf("%s = %.3f %.3f %.3f\n", result, R.x, R.y, R.z);
                    }
                }

                // result = a * number command
                else if (sscanf(line, " %29s = %29s * %f %c", result, Aname, &num, &extra2) == 3) {
                    int ia = findVect(Aname);
                    if (ia < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R = ScMultiVec(myVector[ia], num);
                        newVect(result, R.x, R.y, R.z);
                        printf("%s = %.3f %.3f %.3f\n", result, R.x, R.y, R.z);
                    }
                }

                // result = number * a command
                else if (sscanf(line, " %29s = %f * %29s %c", result, &num, Aname, &extra2) == 3) {
                    int ia = findVect(Aname);
                    if (ia < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R = ScMultiVec(myVector[ia], num);
                        newVect(result, R.x, R.y, R.z);
                        printf("%s = %.3f %.3f %.3f\n", result, R.x, R.y, R.z);
                    }
                }

                // Plain operation: a + b command
                else if (sscanf(line, " %29s %c %29s %c", Aname, &op, Bname, &extra2) == 3 &&
                         (op == '+' || op == '-')) {
                    int ia = findVect(Aname);
                    int ib = findVect(Bname);
                    if (ia < 0 || ib < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R;
                        if (op == '+')
                            R = addvec(myVector[ia], myVector[ib]);
                        else
                            R = subvec(myVector[ia], myVector[ib]);
                        printf("ans = %.3f %.3f %.3f\n", R.x, R.y, R.z);
                    }
                }

                // Scalar multiply: a * 2 or 2 * a command
                else if (sscanf(line, " %29s * %f %c", Aname, &num, &extra2) == 2) {
                    int ia = findVect(Aname);
                    if (ia < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R = ScMultiVec(myVector[ia], num);
                        printf("ans = %.3f %.3f %.3f\n", R.x, R.y, R.z);
                    }
                }

                else if (sscanf(line, " %f * %29s %c", &num, Aname, &extra2) == 2) {
                    int ia = findVect(Aname);
                    if (ia < 0) {
                        printf("Unknown vector.\n");
                    } else {
                        Vector R = ScMultiVec(myVector[ia], num);
                        printf("ans = %.3f %.3f %.3f\n", R.x, R.y, R.z);
                    }
                }

                // Display a vector: name command
                else if (sscanf(line, " %29s %c", Aname, &extra2) == 1) {
                    int ia = findVect(Aname);
                    if (ia < 0) {
                        printf("Vector '%s' not found.\n", Aname);
                    } else {
                        Vector V = myVector[ia];
                        printf("%s = %.3f %.3f %.3f\n", Aname, V.x, V.y, V.z);
                    }
                }


                // Error message
                else {
                    printf("Unrecognized command. Use -h for help.\n");
                }
            }
        }
        printf("VectorLab> ");
    }
    
    // Clean up dynamic memory before exiting
    cleanup_vector_storage();
    printf("\nGoodbye!\n");
    return 0;
}