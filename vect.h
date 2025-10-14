/*
 * Filename: vect.h
 * Description: Defines the functions for vect.c
 * Author: Aden Yance
 * Date: 9/30/2025
 */

 #ifndef VECT_H
 #define VECT_H
 
 #include <stdbool.h>
 
 #define MAX_VECTORS 10
 #define NAME_LEN    30
 
 typedef struct {
     char  name[NAME_LEN];
     float x;
     float y;
     float z;
     bool  in_use;  
 } Vector;
 
 // Global storage
 extern Vector myVector[MAX_VECTORS];
 
 // Math Functions
 Vector addvec(Vector A, Vector B);
 Vector subvec(Vector A, Vector B);
 Vector ScMultiVec(Vector A, float scalar);  // scalar multiply
 Vector CrMultiVec(Vector A, Vector B);      // extra credit: cross multiply
 float  DoMultiVec(Vector A, Vector B);      // extra credit: dot multiply
 
 // Helper Functions 
 void help(void);
 void clear(void);
 void list(void);
 int  newVect(const char* name, float x, float y, float z);
 int  findVect(const char* name);
 bool quit(const char* argument);
 
 #endif