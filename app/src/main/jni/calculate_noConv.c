/*
 * File: calculate_noConv.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 11-May-2018 21:38:46
 */

/* Include Files */
#include <jni.h>
#include "calculate_noConv.h"
#include "calculate_noConv_emxutil.h"
#include <android/log.h>

/* Function Declarations */
static float rt_hypotf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_hypotf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = (float)fabs(u0);
  b = (float)fabs(u1);
  if (a < b) {
    a /= b;
    y = b * (float)sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * (float)sqrt(b * b + 1.0F);
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * Arguments    : float PG_bus4
 *                float V_bus4
 *                float PL_bus3
 *                float QL_bus3
 *                float PL_bus2
 *                float QL_bus2
 *                float V_bus1
 *                float ANG_bus1
 *                float G_line12
 *                float B_line12
 *                float SS_line12
 *                float G_line13
 *                float B_line13
 *                float SS_line13
 *                float G_line24
 *                float B_line24
 *                float SS_line24
 *                float G_line34
 *                float B_line34
 *                float SS_line34
 *                emxArray_real32_T *z
 * Return Type  : void
 */
void calculate_noConv(float PG_bus4, float V_bus4, float PL_bus3, float QL_bus3,
                      float PL_bus2, float QL_bus2, float V_bus1, float ANG_bus1,
                      float G_line12, float B_line12, float SS_line12, float
                      G_line13, float B_line13, float SS_line13, float G_line24,
                      float B_line24, float SS_line24, float G_line34, float
                      B_line34, float SS_line34, emxArray_real32_T *z)
{
  float linedata[32];
  float fv0[32];
  int i;
  int ix;
  creal32_T ss[4];
  creal32_T y[4];
  creal32_T busdata_data[32];
  float tol;
  float mtmp;
  float totalbuses;
  emxArray_creal32_T *ybus;
  emxArray_creal32_T *vc;
  emxArray_creal32_T *VACC;
  creal32_T P_data[4];
  creal32_T Q_data[4];
  float ai;
  float YV_re;
  float y_data[4];
  float YV_im;
  float b_y_data[4];
  float re;
  float brm;
  float im;
  float bim;
  float P_data_re;

  /*        FROM    TO      NOT USED    NOT USED      G              B         NOT USED     SS */
  linedata[0] = 1.0F;
  linedata[4] = 2.0F;
  linedata[8] = 0.01008F;
  linedata[12] = 0.0504F;
  linedata[16] = G_line12;
  linedata[20] = B_line12;
  linedata[24] = 10.25F;
  linedata[28] = SS_line12;
  linedata[1] = 1.0F;
  linedata[5] = 3.0F;
  linedata[9] = 0.00744F;
  linedata[13] = 0.0372F;
  linedata[17] = G_line13;
  linedata[21] = B_line13;
  linedata[25] = 7.75F;
  linedata[29] = SS_line13;
  linedata[2] = 2.0F;
  linedata[6] = 4.0F;
  linedata[10] = 0.00744F;
  linedata[14] = 0.0372F;
  linedata[18] = G_line24;
  linedata[22] = B_line24;
  linedata[26] = 7.75F;
  linedata[30] = SS_line24;
  linedata[3] = 3.0F;
  linedata[7] = 4.0F;
  linedata[11] = 0.01272F;
  linedata[15] = 0.0636F;
  linedata[19] = G_line34;
  linedata[23] = B_line34;
  linedata[27] = 12.75F;
  linedata[31] = SS_line34;

  /*        NR   PG     QG  PL      QL       V   ANG[NU] TYP[NU] */
  /*  V, ANG = const */
  /*  P,Q = const */
  /*  P,Q = const */
  /*  P, V = const */
  fv0[0] = 1.0F;
  fv0[4] = 0.0F;
  fv0[8] = 0.0F;
  fv0[12] = 50.0F;
  fv0[16] = 30.99F;
  fv0[20] = V_bus1;
  fv0[24] = ANG_bus1;
  fv0[28] = 1.0F;
  fv0[1] = 2.0F;
  fv0[5] = 0.0F;
  fv0[9] = 0.0F;
  fv0[13] = PL_bus2;
  fv0[17] = QL_bus2;
  fv0[21] = 1.0F;
  fv0[25] = 0.0F;
  fv0[29] = 2.0F;
  fv0[2] = 3.0F;
  fv0[6] = 0.0F;
  fv0[10] = 0.0F;
  fv0[14] = PL_bus3;
  fv0[18] = QL_bus3;
  fv0[22] = 1.0F;
  fv0[26] = 0.0F;
  fv0[30] = 2.0F;
  fv0[3] = 4.0F;
  fv0[7] = PG_bus4;
  fv0[11] = 0.0F;
  fv0[15] = 80.0F;
  fv0[19] = 49.58F;
  fv0[23] = V_bus4;
  fv0[27] = 0.0F;
  fv0[31] = 3.0F;
  for (i = 0; i < 8; i++) {
    for (ix = 0; ix < 4; ix++) {
      busdata_data[ix + (i << 2)].re = fv0[ix + (i << 2)];
      busdata_data[ix + (i << 2)].im = 0.0F;
    }
  }

  /*  Bus Type: 1.Slack Bus    2.PQ Bus    3.PV Bus */
  for (i = 0; i < 4; i++) {
    ss[i].re = 0.0F;
    ss[i].im = linedata[28 + i];
    y[i].re = linedata[16 + i];
    y[i].im = linedata[20 + i];
  }

  tol = 1.0F;
  mtmp = 2.0F;
  for (ix = 0; ix < 3; ix++) {
    if (linedata[ix + 1] > tol) {
      tol = linedata[ix + 1];
    }

    if (linedata[ix + 5] > mtmp) {
      mtmp = linedata[ix + 5];
    }
  }

  if (tol >= mtmp) {
    totalbuses = tol;
  } else {
    totalbuses = mtmp;
  }

  emxInit_creal32_T(&ybus, 2);

  /*  total buses */
  /*  no. of branches */
  i = ybus->size[0] * ybus->size[1];
  ybus->size[0] = (int)totalbuses;
  ybus->size[1] = (int)totalbuses;
  emxEnsureCapacity((emxArray__common *)ybus, i, (int)sizeof(creal32_T));
  ix = (int)totalbuses * (int)totalbuses;
  for (i = 0; i < ix; i++) {
    ybus->data[i].re = 0.0F;
    ybus->data[i].im = 0.0F;
  }

  for (ix = 0; ix < 4; ix++) {
    ybus->data[((int)linedata[ix] + ybus->size[0] * ((int)linedata[4 + ix] - 1))
      - 1].re = -y[ix].re;
    ybus->data[((int)linedata[ix] + ybus->size[0] * ((int)linedata[4 + ix] - 1))
      - 1].im = -y[ix].im;
    ybus->data[((int)linedata[4 + ix] + ybus->size[0] * ((int)linedata[ix] - 1))
      - 1] = ybus->data[((int)linedata[ix] + ybus->size[0] * ((int)linedata[4 +
      ix] - 1)) - 1];
  }

  for (ix = 0; ix < (int)totalbuses; ix++) {
    for (i = 0; i < 4; i++) {
      if ((linedata[i] == 1.0F + (float)ix) || (linedata[4 + i] == 1.0F + (float)
           ix)) {
        ybus->data[((int)(1.0F + (float)ix) + ybus->size[0] * ((int)(1.0F +
          (float)ix) - 1)) - 1].re = (ybus->data[((int)(1.0F + (float)ix) +
          ybus->size[0] * ((int)(1.0F + (float)ix) - 1)) - 1].re + y[i].re) +
          ss[i].re;
        ybus->data[((int)(1.0F + (float)ix) + ybus->size[0] * ((int)(1.0F +
          (float)ix) - 1)) - 1].im = (ybus->data[((int)(1.0F + (float)ix) +
          ybus->size[0] * ((int)(1.0F + (float)ix) - 1)) - 1].im + y[i].im) +
          ss[i].im;
      }
    }
  }

  emxInit_creal32_T(&vc, 2);
  i = vc->size[0] * vc->size[1];
  vc->size[0] = (int)totalbuses;
  vc->size[1] = (int)totalbuses;
  emxEnsureCapacity((emxArray__common *)vc, i, (int)sizeof(creal32_T));
  ix = (int)totalbuses * (int)totalbuses;
  for (i = 0; i < ix; i++) {
    vc->data[i].re = 0.0F;
    vc->data[i].im = 0.0F;
  }

  emxInit_creal32_T(&VACC, 2);
  i = VACC->size[0] * VACC->size[1];
  VACC->size[0] = (int)totalbuses;
  VACC->size[1] = (int)totalbuses;
  emxEnsureCapacity((emxArray__common *)VACC, i, (int)sizeof(creal32_T));
  ix = (int)totalbuses * (int)totalbuses;
  for (i = 0; i < ix; i++) {
    VACC->data[i].re = 0.0F;
    VACC->data[i].im = 0.0F;
  }

  i = z->size[0] * z->size[1];
  z->size[0] = (int)totalbuses;
  z->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)z, i, (int)sizeof(float));
  ix = (int)totalbuses << 2;
  for (i = 0; i < ix; i++) {
    z->data[i] = 0.0F;
  }

  /*  per unit active power at buses */
  for (i = 0; i < 4; i++) {
    ss[i] = busdata_data[i + 20];
    y[i] = ss[i];
    tol = busdata_data[i + 4].re - busdata_data[i + 12].re;
    ai = busdata_data[i + 4].im - busdata_data[i + 12].im;
    if (ai == 0.0F) {
      P_data[i].re = tol / 100.0F;
      P_data[i].im = 0.0F;
    } else if (tol == 0.0F) {
      P_data[i].re = 0.0F;
      P_data[i].im = ai / 100.0F;
    } else {
      P_data[i].re = tol / 100.0F;
      P_data[i].im = ai / 100.0F;
    }

    tol = busdata_data[i + 8].re - busdata_data[i + 16].re;
    ai = busdata_data[i + 8].im - busdata_data[i + 16].im;
    if (ai == 0.0F) {
      Q_data[i].re = tol / 100.0F;
      Q_data[i].im = 0.0F;
    } else if (tol == 0.0F) {
      Q_data[i].re = 0.0F;
      Q_data[i].im = ai / 100.0F;
    } else {
      Q_data[i].re = tol / 100.0F;
      Q_data[i].im = ai / 100.0F;
    }
  }

  /*  per unit reactive power at buses */
  tol = 1.0F;

  /*  kk=input('Enter the tolerance for iteration '); */
  /* alfa=input('Enter the value of ALPHA '); */
  while (tol > 0.001F) {
    for (i = 0; i < (int)(totalbuses + -1.0F); i++) {
      YV_re = 0.0F;
      YV_im = 0.0F;
      for (ix = 0; ix < (int)totalbuses; ix++) {
        if (2.0F + (float)i != 1.0F + (float)ix) {
          mtmp = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)
            (1.0F + (float)ix) - 1)) - 1].re * ss[(int)(1.0F + (float)ix) - 1].
            re - ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)
            (1.0F + (float)ix) - 1)) - 1].im * ss[(int)(1.0F + (float)ix) - 1].
            im;
          tol = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(1.0F
            + (float)ix) - 1)) - 1].re * ss[(int)(1.0F + (float)ix) - 1].im +
            ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(1.0F +
            (float)ix) - 1)) - 1].im * ss[(int)(1.0F + (float)ix) - 1].re;
          YV_re += mtmp;
          YV_im += tol;

          /*  multiplying admittance & voltage */
        }
      }

      if ((busdata_data[(int)(2.0F + (float)i) + 27].re == 3.0F) &&
          (busdata_data[(int)(2.0F + (float)i) + 27].im == 0.0F)) {
        /* Calculating Qi for PV bus */
        /* Q(i) = -imag(conj(V(i))*(YV + ybus(i,i)*V(i))); */
        mtmp = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F
          + (float)i) - 1)) - 1].re * ss[(int)(2.0F + (float)i) - 1].re -
          ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F +
          (float)i) - 1)) - 1].im * ss[(int)(2.0F + (float)i) - 1].im;
        tol = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F +
          (float)i) - 1)) - 1].re * ss[(int)(2.0F + (float)i) - 1].im +
          ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F +
          (float)i) - 1)) - 1].im * ss[(int)(2.0F + (float)i) - 1].re;
        Q_data[(int)(2.0F + (float)i) - 1].re = -(ss[(int)(2.0F + (float)i) - 1]
          .re * (YV_im + tol) + -ss[(int)(2.0F + (float)i) - 1].im * (YV_re +
          mtmp));
        Q_data[(int)(2.0F + (float)i) - 1].im = 0.0F;
        busdata_data[(int)(2.0F + (float)i) + 7] = Q_data[(int)(2.0F + (float)i)
          - 1];
      }

      /*  end */
      mtmp = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F +
        (float)i) - 1)) - 1].re;
      tol = ybus->data[((int)(2.0F + (float)i) + ybus->size[0] * ((int)(2.0F +
        (float)i) - 1)) - 1].im;
      if (tol == 0.0F) {
        re = 1.0F / mtmp;
        im = 0.0F;
      } else if (mtmp == 0.0F) {
        re = 0.0F;
        im = -(1.0F / tol);
      } else {
        brm = (float)fabs(mtmp);
        bim = (float)fabs(tol);
        if (brm > bim) {
          bim = tol / mtmp;
          mtmp += bim * tol;
          re = 1.0F / mtmp;
          im = (0.0F - bim) / mtmp;
        } else if (bim == brm) {
          if (mtmp > 0.0F) {
            bim = 0.5F;
          } else {
            bim = -0.5F;
          }

          if (tol > 0.0F) {
            mtmp = 0.5F;
          } else {
            mtmp = -0.5F;
          }

          re = bim / brm;
          im = (0.0F - mtmp) / brm;
        } else {
          bim = mtmp / tol;
          mtmp = tol + bim * mtmp;
          re = bim / mtmp;
          im = -1.0F / mtmp;
        }
      }

      tol = P_data[(int)(2.0F + (float)i) - 1].re - (0.0F - Q_data[(int)(2.0F +
        (float)i) - 1].im);
      ai = P_data[(int)(2.0F + (float)i) - 1].im - Q_data[(int)(2.0F + (float)i)
        - 1].re;
      if (-ss[(int)(2.0F + (float)i) - 1].im == 0.0F) {
        if (ai == 0.0F) {
          P_data_re = tol / ss[(int)(2.0F + (float)i) - 1].re;
          mtmp = 0.0F;
        } else if (tol == 0.0F) {
          P_data_re = 0.0F;
          mtmp = ai / ss[(int)(2.0F + (float)i) - 1].re;
        } else {
          P_data_re = tol / ss[(int)(2.0F + (float)i) - 1].re;
          mtmp = ai / ss[(int)(2.0F + (float)i) - 1].re;
        }
      } else if (ss[(int)(2.0F + (float)i) - 1].re == 0.0F) {
        if (tol == 0.0F) {
          P_data_re = ai / -ss[(int)(2.0F + (float)i) - 1].im;
          mtmp = 0.0F;
        } else if (ai == 0.0F) {
          P_data_re = 0.0F;
          mtmp = -(tol / -ss[(int)(2.0F + (float)i) - 1].im);
        } else {
          P_data_re = ai / -ss[(int)(2.0F + (float)i) - 1].im;
          mtmp = -(tol / -ss[(int)(2.0F + (float)i) - 1].im);
        }
      } else {
        brm = (float)fabs(ss[(int)(2.0F + (float)i) - 1].re);
        bim = (float)fabs(-ss[(int)(2.0F + (float)i) - 1].im);
        if (brm > bim) {
          bim = -ss[(int)(2.0F + (float)i) - 1].im / ss[(int)(2.0F + (float)i) -
            1].re;
          mtmp = ss[(int)(2.0F + (float)i) - 1].re + bim * -ss[(int)(2.0F +
            (float)i) - 1].im;
          P_data_re = (tol + bim * ai) / mtmp;
          mtmp = (ai - bim * tol) / mtmp;
        } else if (bim == brm) {
          if (ss[(int)(2.0F + (float)i) - 1].re > 0.0F) {
            bim = 0.5F;
          } else {
            bim = -0.5F;
          }

          if (-ss[(int)(2.0F + (float)i) - 1].im > 0.0F) {
            mtmp = 0.5F;
          } else {
            mtmp = -0.5F;
          }

          P_data_re = (tol * bim + ai * mtmp) / brm;
          mtmp = (ai * bim - tol * mtmp) / brm;
        } else {
          bim = ss[(int)(2.0F + (float)i) - 1].re / -ss[(int)(2.0F + (float)i) -
            1].im;
          mtmp = -ss[(int)(2.0F + (float)i) - 1].im + bim * ss[(int)(2.0F +
            (float)i) - 1].re;
          P_data_re = (bim * tol + ai) / mtmp;
          mtmp = (bim * ai - tol) / mtmp;
        }
      }

      P_data_re -= YV_re;
      mtmp -= YV_im;
      ss[(int)(2.0F + (float)i) - 1].re = re * P_data_re - im * mtmp;
      ss[(int)(2.0F + (float)i) - 1].im = re * mtmp + im * P_data_re;

      /*  Compute Bus Voltages. */
      /*  Calculating Corrected Voltage for PV bus */
      if ((busdata_data[(int)(2.0F + (float)i) + 27].re == 3.0F) &&
          (busdata_data[(int)(2.0F + (float)i) + 27].im == 0.0F)) {
        mtmp = rt_hypotf(ss[(int)(2.0F + (float)i) - 1].re, ss[(int)(2.0F +
          (float)i) - 1].im);
        if (ss[(int)(2.0F + (float)i) - 1].im == 0.0F) {
          tol = ss[(int)(2.0F + (float)i) - 1].re / mtmp;
          mtmp = 0.0F;
        } else if (ss[(int)(2.0F + (float)i) - 1].re == 0.0F) {
          tol = 0.0F;
          mtmp = ss[(int)(2.0F + (float)i) - 1].im / mtmp;
        } else {
          tol = ss[(int)(2.0F + (float)i) - 1].re / mtmp;
          mtmp = ss[(int)(2.0F + (float)i) - 1].im / mtmp;
        }

        vc->data[(int)(2.0F + (float)i) - 1].re = rt_hypotf(y[(int)(2.0F +
          (float)i) - 1].re, y[(int)(2.0F + (float)i) - 1].im) * tol;
        vc->data[(int)(2.0F + (float)i) - 1].im = rt_hypotf(y[(int)(2.0F +
          (float)i) - 1].re, y[(int)(2.0F + (float)i) - 1].im) * mtmp;
        busdata_data[(int)(2.0F + (float)i) + 19] = vc->data[(int)(2.0F + (float)
          i) - 1];
        ss[(int)(2.0F + (float)i) - 1] = vc->data[(int)(2.0F + (float)i) - 1];
      }

      /*  Calculating Accelerated Voltage for PQ bus */
      if ((busdata_data[(int)(2.0F + (float)i) + 27].re == 2.0F) &&
          (busdata_data[(int)(2.0F + (float)i) + 27].im == 0.0F)) {
        VACC->data[(int)(2.0F + (float)i) - 1].re = y[(int)(2.0F + (float)i) - 1]
          .re + 1.6F * (ss[(int)(2.0F + (float)i) - 1].re - y[(int)(2.0F +
          (float)i) - 1].re);
        VACC->data[(int)(2.0F + (float)i) - 1].im = y[(int)(2.0F + (float)i) - 1]
          .im + 1.6F * (ss[(int)(2.0F + (float)i) - 1].im - y[(int)(2.0F +
          (float)i) - 1].im);
        busdata_data[(int)(2.0F + (float)i) + 19] = VACC->data[(int)(2.0F +
          (float)i) - 1];
        ss[(int)(2.0F + (float)i) - 1] = VACC->data[(int)(2.0F + (float)i) - 1];
      }

      /* V(i)=V; */
    }

    /*  Increment iteration count. */
    for (ix = 0; ix < 4; ix++) {
      y_data[ix] = rt_hypotf(ss[ix].re, ss[ix].im) - rt_hypotf(y[ix].re, y[ix].
        im);
    }

    for (ix = 0; ix < 4; ix++) {
      b_y_data[ix] = (float)fabs(y_data[ix]);
    }

    tol = b_y_data[0];
    for (ix = 0; ix < 3; ix++) {
      if (b_y_data[ix + 1] > tol) {
        tol = b_y_data[ix + 1];
      }
    }

    /*  Calculate tolerance. */
    for (i = 0; i < 4; i++) {
      y[i] = ss[i];
    }
  }

  emxFree_creal32_T(&VACC);
  emxFree_creal32_T(&vc);
  emxFree_creal32_T(&ybus);

    /* real(VACC') */
    for (i = 0; i < 4; i++) {
        z->data[i] = busdata_data[i].re;
    }

    for (i = 0; i < 4; i++) {
        z->data[i + z->size[0]] = busdata_data[i + 28].re;
    }

    for (ix = 0; ix < 4; ix++) {
        y[ix] = busdata_data[ix + 20];
        y_data[ix] = rt_hypotf(y[ix].re, y[ix].im);
    }

    for (i = 0; i < 4; i++) {
        z->data[i + (z->size[0] << 1)] = y_data[i];
    }

    for (ix = 0; ix < 4; ix++) {
        y_data[ix] = (float)atan2(ss[ix].im, ss[ix].re);
    }

    for (i = 0; i < 4; i++) {
        z->data[i + z->size[0] * 3] = y_data[i];
    }
}

/*
 * File trailer for calculate_noConv.c
 *
 * [EOF]
 */
