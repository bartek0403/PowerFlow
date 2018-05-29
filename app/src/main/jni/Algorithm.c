/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 11-May-2018 21:38:46
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "calculate_noConv.h"
#include "main.h"
#include "calculate_noConv_terminate.h"
#include "calculate_noConv_emxAPI.h"
#include "calculate_noConv_initialize.h"
#import <jni.h>

/* Function Declarations */
static float argInit_real32_T(void);
static void main_calculate_noConv(jfloat args[20]);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
    return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_calculate_noConv(jfloat args[20])
{


    emxArray_real32_T *z;
    emxInitArray_real32_T(&z, 2);

    /* Initialize function 'calculate_noConv' input arguments. */
    // ZAINICJOWAC Z ARGUMENTOW FUNKCJI
   /* PG_bus4 = argInit_real32_T();
    V_bus4 = argInit_real32_T();
    PL_bus3 = argInit_real32_T();
    QL_bus3 = argInit_real32_T();
    PL_bus2 = argInit_real32_T();
    QL_bus2 = argInit_real32_T();
    V_bus1 = argInit_real32_T();
    ANG_bus1 = argInit_real32_T();
    G_line12 = argInit_real32_T();
    B_line12 = argInit_real32_T(); */

    /* Call the entry-point 'calculate_noConv'. */
   /* calculate_noConv(PG_bus4, V_bus4, PL_bus3, QL_bus3, PL_bus2, QL_bus2, V_bus1,
                     ANG_bus1, G_line12, B_line12, SS_line12,
                     G_line13, B_line13, SS_line13,
                     G_line24, B_line24, SS_line24,
                     G_line34, B_line34, SS_line34, z); */

    emxDestroyArray_real32_T(z);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
JNIEXPORT jfloatArray JNICALL Java_com_pwr_janek_powerflow1_MainActivity_nMain(JNIEnv *env, jobject jclazz, jfloatArray args)
{
    //Inicjalizacja tablicy tymczasowej i głównej
    jfloat temp[16];
    jfloatArray output = (*env)->NewFloatArray(env,16);

    //Odbiór danych wejściowych
    jfloat *body = (*env) -> GetFloatArrayElements(env,args,0);
    float PG_bus4 = body[0] ;
    float V_bus4 = body[1];
    float PL_bus3 = body[2];
    float QL_bus3 = body[3];
    float PL_bus2 = body[4];
    float QL_bus2 = body[5];
    float V_bus1 = body[6];
    float ANG_bus1 = body[7];
    float G_line12 = body[8];
    float B_line12 = body[9];
    float SS_line12 = body[10];
    float G_line13 = body[11];
    float B_line13 = body[12];
    float SS_line13 = body[13];
    float G_line24 = body[14];
    float B_line24 = body[15];
    float SS_line24 = body[16];
    float G_line34 = body[17];
    float B_line34 = body[18];
    float SS_line34 = body[19];

    //Inicjalizacja tablicy wyjśćiowej - matlab
    emxArray_real32_T *z;
    emxInitArray_real32_T(&z, 2);

    // Główna funkcja
    calculate_noConv(PG_bus4, V_bus4, PL_bus3, QL_bus3, PL_bus2, QL_bus2, V_bus1,
                     ANG_bus1, G_line12, B_line12, SS_line12,
                     G_line13, B_line13, SS_line13,
                     G_line24, B_line24, SS_line24,
                     G_line34, B_line34, SS_line34, z);

    //Kopiowanie danych tablica wyjściowa(matlab) - tablica tymczasowa
    for(int i=0; i < z->allocatedSize ;i++){
        temp[i]= z->data[i];
    }

    //Kopiowanie dancyh tablica tymczasowa - tablica główna
    (*env)->SetFloatArrayRegion(env, output, 0, 16, temp);
    emxDestroyArray_real32_T(z);

    return output;
}



/*
 * File trailer for main.c
 *
 * [EOF]
 */
