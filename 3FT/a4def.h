/*--------------------------------------------------------------------*/
/* a4def.h                                                            */
/* Author: Christopher Moretti                                        */
/*--------------------------------------------------------------------*/

#ifndef A4DEF_INCLUDED
#define A4DEF_INCLUDED

/* Return statuses */
enum { SUCCESS,
       INITIALIZATION_ERROR, PARENT_CHILD_ERROR , ALREADY_IN_TREE,
       NO_SUCH_PATH, CONFLICTING_PATH, NOT_A_DIRECTORY, NOT_A_FILE,
       MEMORY_ERROR
};

/* In lieu of a proper boolean datatype */
typedef enum bool { FALSE, TRUE } boolean;
/*
   a Node_T is an object that contains a path payload and references to
   the node's files and children (if they exist).
*/
typedef struct node* Node_T;

#endif
