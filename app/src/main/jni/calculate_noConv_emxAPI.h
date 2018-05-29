/*
 * File: calculate_noConv_emxAPI.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 11-May-2018 21:38:46
 */

#ifndef CALCULATE_NOCONV_EMXAPI_H
#define CALCULATE_NOCONV_EMXAPI_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "calculate_noConv_types.h"

/* Function Declarations */
extern emxArray_real32_T *emxCreateND_real32_T(int numDimensions, int *size);
extern emxArray_real32_T *emxCreateWrapperND_real32_T(float *data, int
  numDimensions, int *size);
extern emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows, int
  cols);
extern emxArray_real32_T *emxCreate_real32_T(int rows, int cols);
extern void emxDestroyArray_real32_T(emxArray_real32_T *emxArray);
extern void emxInitArray_real32_T(emxArray_real32_T **pEmxArray, int
  numDimensions);

#endif

/*
 * File trailer for calculate_noConv_emxAPI.h
 *
 * [EOF]
 */
