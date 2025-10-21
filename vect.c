/*
 * Filename: vect.c
 * Description: Defines the functions used to make and operate vectors
 * Author: Aden Yance
 * Date: 9/30/2025
 */

 #include <stdio.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include "vect.h"
 
 // Global storage
 Vector myVector[MAX_VECTORS];
 
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
     printf("  quit                  Exit the program.\n");
     printf("  save                  Saves all the current vectors to a CSV File \n");
     printf("  -h                    Show this help message again.\n\n");
 }
 
 void clear(void) {
     for (int i = 0; i < MAX_VECTORS; i++) {
         myVector[i].in_use = false;
         myVector[i].name[0] = '\0';
         myVector[i].x = 0;
         myVector[i].y = 0;
         myVector[i].z = 0;
     }
 }
 
 void list(void) {
     bool any = false;
     for (int i = 0; i < MAX_VECTORS; i++) {
         if (myVector[i].in_use) {
             printf("%s = %.3f %.3f %.3f\n",
                    myVector[i].name,
                    myVector[i].x,
                    myVector[i].y,
                    myVector[i].z);
             any = true;
         }
     }
     if (!any) {
         printf("No vectors stored.\n");
     }
 }

 //Saves the current vectors to a file
 void save(String Fname){
    FILE *file_ptr;
    
    file_ptr = fopen(Fname, "w"); //uses the input given in main as the file name
    for (int i = 0; i < MAX_VECTORS; i++) { // have to change the max vectors for dynamic memory 
    fprintf(file_ptr, "Vector Name, x value, y value, and z value \n")
    fprintf(file_ptr, "%s, %.3f, %.3f, %.3f\n", myVector[i].name, myVector[i].x, myVector[i].y, myVector[i].z);
    }
    fclose(file_ptr);

 }
 
 int newVect(const char* name, float x, float y, float z) {
     // replace if exists
     for (int i = 0; i < MAX_VECTORS; i++) {
         if (myVector[i].in_use && strcmp(myVector[i].name, name) == 0) {
             myVector[i].x = x;
             myVector[i].y = y;
             myVector[i].z = z;
             return 1;  // Vector is replaced
         }
     }
 
     // add to first empty slot
     for (int i = 0; i < MAX_VECTORS; i++) {
         if (!myVector[i].in_use) {
             myVector[i].in_use = true;
             strncpy(myVector[i].name, name, NAME_LEN - 1);
             myVector[i].name[NAME_LEN - 1] = '\0';
             myVector[i].x = x;
             myVector[i].y = y;
             myVector[i].z = z;
             return 2;  // Vector is added
         }
     }
 
     return 0;  // Vector Array is full
 }
 
 int findVect(const char* name) {
     for (int i = 0; i < MAX_VECTORS; i++) {
         if (myVector[i].in_use && strcmp(myVector[i].name, name) == 0) {
             return i;  // Vector is found
         }
     }
     return -1;  // Vector is not found
 }
 
 bool quit(const char* argument ) {
     return (strcmp(argument, "quit") == 0);
 }