/*
 * Filename: vect.h
 * Description: Defines the functions for vect.c
 * Author: Aden Yance
 * Date: 10/21/2025
 */

 #ifndef VECT_H
 #define VECT_H

 #include <stdbool.h>

 #define NAME_LEN    30

 typedef struct {
     char  name[NAME_LEN];
     float x;
     float y;
     float z;
     bool  in_use;  
 } Vector;

 // Math Functions
 Vector addvec(Vector A, Vector B);
 Vector subvec(Vector A, Vector B);
 Vector ScMultiVec(Vector A, float scalar);  // scalar multiply

 // Helper Functions 
 void save(const char* filename);
 int  loadVect(const char* filename);
 void help(void);
 void clear(void);
 void list(void);
 int  newVect(const char* name, float x, float y, float z);
 int  findVect(const char* name);
 bool quit(const char* argument);

 // Dynamic memory functions 
 int init_vector_storage(int initial_capacity);
 void cleanup_vector_storage();

 #endif