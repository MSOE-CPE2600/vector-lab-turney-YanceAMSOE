/*
 * Filename: vect.c
 * Description: Defines the functions used to make and operate vectors
 * Author: Aden Yance
 * Date: 10/21/2025
 */

 #include <stdio.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include "vect.h"
 #include "DM.h"
 
 // Math Functions
 
 Vector addvec(Vector A, Vector B) {
     Vector result;
     result.x = A.x + B.x;
     result.y = A.y + B.y;
     result.z = A.z + B.z;
     return result;
 }
 
 Vector subvec(Vector A, Vector B) {
     Vector result;
     result.x = A.x - B.x;
     result.y = A.y - B.y;
     result.z = A.z - B.z;
     return result;
 }
 
 Vector ScMultiVec(Vector A, float scalar) { 
     Vector result;
     result.x = A.x * scalar;
     result.y = A.y * scalar;
     result.z = A.z * scalar;
     return result;
 }
 

 
 // Storage / Helpers
 
 void help(void) {
     printf("====== Vector Calculator Help ======\n");
     printf("This program performs basic vector math in 3D.\n\n");
 
     printf("Available commands:\n");
     printf("  name = x y z          Create or replace a vector\n");
     printf("  name                  Display the current value of a stored vector\n");
     printf("  a + b                 Add two vectors\n");
     printf("  a - b                 Subtract two vectors\n");
     printf("  a * s   or  s * a     Multiply a vector by scalar\n");
     printf("  c = a + b             Store the sum of a and b in vector c.\n");
     printf("  c = a - b             Store the difference of a and b in vector c.\n");
     printf("  c = a * s  or  c = s * a   Store a scaled vector result in c.\n");
 
     printf("Other commands:\n");
     printf("  list                  Display all currently stored vectors.\n");
     printf("  clear                 Delete all stored vectors.\n");
     printf("  save                  Saves all the current vectors to a CSV File \n");
     printf("  load                  Load vectors from a CSV File \n");
     printf("  quit                  Exit the program.\n");
     printf("  -h                    Show this help message again.\n\n");
 }
 
 void clear(void) {
     clear_vectors_dynamic();
 }
 
 void list(void) {
     list_vectors_dynamic();
 }

 //Saves the current vectors to a file
 void save(const char* filename){
    FILE *file_ptr;
    
    file_ptr = fopen(filename, "w"); //uses the input given in main as the file name
    if (file_ptr == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    fprintf(file_ptr, "Vector Name, x value, y value, z value\n");
    for (int i = 0; i < vector_count; i++) {
        if (myVector[i].in_use) {
            fprintf(file_ptr, "%s, %.3f, %.3f, %.3f\n",  //the .3 save it to 3 decimal spots
                    myVector[i].name, myVector[i].x, myVector[i].y, myVector[i].z);
        }
    }
    fclose(file_ptr);
    printf("Vectors saved to %s\n", filename);
 }
 
 int newVect(const char* name, float x, float y, float z) {
     return add_vector_dynamic(name, x, y, z);
 }
 
 int findVect(const char* name) {
     return find_vector_dynamic(name);
 }

 // Load vectors from file
 int loadVect(const char* filename) {
     return load_vectors_from_file(filename);
 }
 
 bool quit(const char* argument ) {
     return (strcmp(argument, "quit") == 0);
 }