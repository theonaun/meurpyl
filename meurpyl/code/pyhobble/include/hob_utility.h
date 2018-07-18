/*

//////////////////////////////////////////////////////////////////////////////
Generally
//////////////////////////////////////////////////////////////////////////////

    HEADER_NAME:    hob_utility.h
    COMPANION_C:    hob_utility.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines global utility functions for items such
                    as memory management.

//////////////////////////////////////////////////////////////////////////////
Functions
//////////////////////////////////////////////////////////////////////////////

    hob_xmalloc(size_t): Runs malloc, raises errors if necessary, and zeros.

    hob_xfree(void *)  : Zeros memory, frees memory, and sets pointer to 0.

*/

#ifndef HOB_UTILITY_H
#define HOB_UTILITY_H

#include <stdlib.h>

void * hob_xmalloc (size_t); 

void   hob_xfree(void *);

#endif