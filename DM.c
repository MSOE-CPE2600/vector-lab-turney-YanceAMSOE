/*
* Filename: main.c
* Description: Does operations with vectors
* Author: Aden Yance
* Date: 9/30/2025
* compile with a Makefile then ./vectorlab
Changing it for the github
*/
int allocate(int **ptr, int size){
    *ptr = (int*)malloc(size*sizeof(int));
    return 0;
}
void deallocate(int *ptr){
    free(ptr);

}