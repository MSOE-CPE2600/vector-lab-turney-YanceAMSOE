/*
* Filename: DM.h
* Description: Dynamic memory management header for vector lab
* Author: Aden Yance
* Date: 10/21/2025
*/

#ifndef DM_H
#define DM_H

#include <stdbool.h>
#include "vect.h"

// Dynamic memory management functions
int init_vector_storage(int initial_capacity);
int expand_vector_storage();
int add_vector_dynamic(const char* name, float x, float y, float z);
int find_vector_dynamic(const char* name);
void clear_vectors_dynamic();
void list_vectors_dynamic();
void cleanup_vector_storage();
int get_vector_count();
int get_vector_capacity();
int load_vectors_from_file(const char* filename);

// Global vector storage (extern declaration)
extern Vector *myVector;
extern int vector_count;
extern int vector_capacity;

#endif