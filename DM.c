/*
* Filename: DM.c
* Description: Dynamic memory management functions for vector lab
* Author: Aden Yance
* Date: 10/21/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vect.h"
#include "DM.h"

// Global dynamic vector storage
Vector *myVector = NULL;
int vector_count = 0;
int vector_capacity = 0;

// Initialize dynamic vector storage
int init_vector_storage(int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = 10; // Default capacity
    }
    
    myVector = (Vector*)malloc(initial_capacity * sizeof(Vector));
    if (myVector == NULL) {
        printf("Error: Failed to allocate memory for vectors\n");
        return 0;
    }
    
    vector_capacity = initial_capacity;
    vector_count = 0;
    
    // Initialize all vectors as unused
    for (int i = 0; i < vector_capacity; i++) {
        myVector[i].in_use = false;
        myVector[i].name[0] = '\0';
        myVector[i].x = 0;
        myVector[i].y = 0;
        myVector[i].z = 0;
    }
    
    return 1;
}

// Expand vector storage when needed
int expand_vector_storage() {
    int new_capacity = vector_capacity * 2;
    Vector *new_vector = (Vector*)realloc(myVector, new_capacity * sizeof(Vector));
    
    if (new_vector == NULL) {
        printf("Error: Failed to expand vector storage\n");
        return 0;
    }
    
    myVector = new_vector;
    
    // Initialize new slots
    for (int i = vector_capacity; i < new_capacity; i++) {
        myVector[i].in_use = false;
        myVector[i].name[0] = '\0';
        myVector[i].x = 0;
        myVector[i].y = 0;
        myVector[i].z = 0;
    }
    
    vector_capacity = new_capacity;
    return 1;
}

// Add a new vector using dynamic memory
int add_vector_dynamic(const char* name, float x, float y, float z) {
    // Check if vector already exists
    for (int i = 0; i < vector_count; i++) {
        if (myVector[i].in_use && strcmp(myVector[i].name, name) == 0) {
            myVector[i].x = x;
            myVector[i].y = y;
            myVector[i].z = z;
            return 1; // Vector replaced
        }
    }
    
    // Expand storage if needed
    if (vector_count >= vector_capacity) {
        if (!expand_vector_storage()) {
            return 0; // Failed to expand
        }
    }
    
    // Add new vector
    myVector[vector_count].in_use = true;
    strncpy(myVector[vector_count].name, name, NAME_LEN - 1);
    myVector[vector_count].name[NAME_LEN - 1] = '\0';
    myVector[vector_count].x = x;
    myVector[vector_count].y = y;
    myVector[vector_count].z = z;
    vector_count++;
    
    return 2; // Vector added
}

// Find vector by name
int find_vector_dynamic(const char* name) {
    for (int i = 0; i < vector_count; i++) {
        if (myVector[i].in_use && strcmp(myVector[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Clear all vectors
void clear_vectors_dynamic() {
    for (int i = 0; i < vector_count; i++) {
        myVector[i].in_use = false;
        myVector[i].name[0] = '\0';
        myVector[i].x = 0;
        myVector[i].y = 0;
        myVector[i].z = 0;
    }
    vector_count = 0;
}

// List all vectors
void list_vectors_dynamic() {
    bool any = false;
    for (int i = 0; i < vector_count; i++) {
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

// Clean up all dynamic memory
void cleanup_vector_storage() {
    if (myVector != NULL) {
        free(myVector);
        myVector = NULL;
        vector_count = 0;
        vector_capacity = 0;
    }
}

// Get current vector count
int get_vector_count() {
    return vector_count;
}

// Get current capacity
int get_vector_capacity() {
    return vector_capacity;
}

// Load vectors from CSV file
int load_vectors_from_file(const char* filename) {
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }
    
    char line[200];
    int loaded_count = 0;
    
    // Skip header line
    if (fgets(line, sizeof(line), file_ptr) == NULL) {
        printf("Error: File is empty or invalid format\n");
        fclose(file_ptr);
        return 0;
    }
    
    // Read each line and parse vectors
    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        char name[NAME_LEN];
        float x, y, z;
        
        // Parse CSV format: "name, x, y, z"
        if (sscanf(line, "%29[^,], %f, %f, %f", name, &x, &y, &z) == 4) {
            // Add vector using dynamic memory
            int result = add_vector_dynamic(name, x, y, z);
            if (result > 0) {
                loaded_count++;
                printf("Loaded: %s = %.3f %.3f %.3f\n", name, x, y, z);
            } else {
                printf("Warning: Failed to load vector %s\n", name);
            }
        } else {
            printf("Warning: Skipping invalid line: %s\n", line);
        }
    }
    
    fclose(file_ptr);
    printf("Successfully loaded %d vectors from %s\n", loaded_count, filename);
    return loaded_count;
}