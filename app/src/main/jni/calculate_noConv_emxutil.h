/*
 * File: calculate_noConv_emxutil.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 11-May-2018 21:38:46
 */

#ifndef CALCULATE_NOCONV_EMXUTIL_H
#define CALCULATE_NOCONV_EMXUTIL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "calculate_noConv_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_creal32_T(emxArray_creal32_T **pEmxArray);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxInit_creal32_T(emxArray_creal32_T **pEmxArray, int numDimensions);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for calculate_noConv_emxutil.h
 *
 * [EOF]
 */
