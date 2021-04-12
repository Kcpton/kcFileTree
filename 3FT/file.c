/*--------------------------------------------------------------------*/
/* file.c                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


#include "dynarray.h"
#include "file.h"
#include "node1.c"

struct file {
   char* path;
   void* contents;
};

File_T File_new(char* path, void* contents) {
    File_T output;
    output = (File_T) malloc(sizeof(struct file));
    if (output == NULL) {
        return NULL;
    }
    output->path = (char*) malloc(strlen(path) + 1);
    if(output->path == NULL) {
        return NULL;
    }
    strcpy(output->path, path);
    output->contents = contents;
}

static int File_compare(File_T file1, File_T file2) {
    return strcmp(file1->path, file2->path);
}

int File_insert(Node_T inNode, char* path, void* contents)  {
    size_t loc;
    File_T newFile;
    if(DynArray_bsearch(inNode->files, path, loc, File_compare)) {
        return ALREADY_IN_TREE;
    }
    newFile = File_new(path, contents);
    if(newFile == NULL) {
        return NULL;
    }
    if(DynArray_addAt(inNode->files, loc, newFile)) {
        return SUCCESS;
    }
    return MEMORY_ERROR;
}

int File_contatins(Node_T inNode, char* path) {
    size_t *loc;
    if(DynArray_bsearch(inNode->files, path, loc, File_compare)) {
        return TRUE;
    }
    return FALSE;
}

static File_T File_getFile(Node_T inNode, char* path) {
    size_t* loc;
    int exist = DynArray_bsearch(inNode->files, path, loc, 
        File_compare);
    File_T outFile;
    if (exist == 0) {
        return NULL;
    }
    outFile = DynArray_get(inNode->files, *loc);
    return outFile;
}

char* File_toString(Node_T inNode, char* path) {
    File_T outFile = File_getFile(inNode, path);
    return outFile->path;
}

int File_replace(Node_T inNode, char* path, void* contents) {
    File_T outFile = File_getFile(inNode, path);
    void* output;
    if(outFile == NULL) {
        return NULL;
    }
    output = outFile->contents;
    outFile->contents = contents;
    return output;
}

void* File_getcontents(Node_T inNode, char* path) {
    File_T outFile = File_getFile(inNode, path);
    return outFile->contents;
}


char* File_getFileName(Node_T inNode, size_t fileID) {
    File_T outfile = DynArray_get(inNode->files, fileID);
    if (outfile == NULL) {
        return NULL;
    }
    return outfile->path;
}

size_t File_getNumFiles(Node_T inNode, char* path) {
    return DynArray_getLength(inNode->files);
}

int File_rmFile(Node_T inNode, char* path){
    size_t* loc;
    int exist = DynArray_bsearch(inNode->files, path, loc, 
        File_compare);
    File_T outFile;
    if (!exist) {
        if(DynArray_bsearch(inNode->files, path, loc, 
            File_compare)) {
            return NOT_A_FILE;
        }
        return NO_SUCH_PATH;
    }
    outFile = DynArray_removeAt(inNode->files, *loc);
    free(outFile->path);
    free(outFile);
    return SUCCESS;
}
