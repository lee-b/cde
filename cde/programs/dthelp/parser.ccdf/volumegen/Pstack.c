/* $XConsortium: Pstack.c /main/4 1995/11/08 11:47:39 rswiston $ */
/************************************<+>*************************************
 ****************************************************************************
 *
 * File:         PStack.c
 *
 * Project:      Cache Creek (Rivers) Project
 * Description:  Utility functions for volumegen program
 * Author:       Brian Cripe
 *               Modifications by (Mike Wilson)
 * Language:     C
 *
 * (C) Copyright 1992, Hewlett-Packard, all rights reserved.
 *
 ****************************************************************************
 ************************************<+>*************************************/


#include <stdio.h>
#include "PstackI.h"

#define REALLOC_INCR  10





/*****************************************************************************
 * Function:	    PStack PStackCreate();
 *
 * Parameters:      NONE.
 *
 * Return Value:    PStack.
 *
 * Purpose:         Generates a PStack structure and returns it to the 
 *                  caller.
 *
 *****************************************************************************/
PStack PStackCreate()
{
    PStack stack;
    stack = (PStack) malloc (sizeof (struct PStackRec));
    stack->count = 0;
    stack->size = REALLOC_INCR;
    stack->items = (void **) malloc (stack->size * sizeof (void **));

    return (stack);
}



/*****************************************************************************
 * Function:	    PStack PStackDestroy();
 *
 * Parameters:      stack:
 *
 * Return Value:    void.
 *
 * Purpose:         Destroys a PStack structure.
 *
 *****************************************************************************/
void PStackDestroy(
     PStack stack)
{
    free (stack->items);
    free (stack);
}





/*****************************************************************************
 * Function:	    PStack PStackPush();
 *
 * Parameters:      stack:
 *                  ptr:
 *
 * Return Value:    void
 *
 * Purpose:         Pushes a PStack structure on the current stack.
 *
 *****************************************************************************/
void PStackPush(
     PStack stack,
     void *ptr)
{
    if (stack->count == stack->size) {
	stack->size += REALLOC_INCR;
	stack->items = (void **) realloc (stack->items, 
					  stack->size * sizeof (void **));
    }

    *(stack->items + stack->count) = ptr;
    stack->count++;
}



/*****************************************************************************
 * Function:	    PStack *PStackPeek();
 *
 * Parameters:      stack:
 *
 * Return Value:    void.
 *
 * Purpose:         Gets a PStack.
 *
 *****************************************************************************/
void *PStackPeek(
     PStack stack)

{
    if (stack->count == 0)
	return (NULL);

    else
	return (*(stack->items + stack->count - 1));
}


/*****************************************************************************
 * Function:	    PStack *PStackPop();
 *
 * Parameters:      stack:
 *
 * Return Value:    void.
 *
 * Purpose:         Pops the top element off the stack
 *
 *****************************************************************************/
void *PStackPop(
     PStack stack)
{
    if (stack->count == 0)
	return (NULL);

    else {
	stack->count--;
	return (*(stack->items + stack->count));
    }
}

	    
















