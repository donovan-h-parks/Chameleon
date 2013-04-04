/*
 * File: NMDS.cpp
 *
 * Originally: mds.c
 *
 * (c) Peter Kleiweg 2000 - 2005
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 */

#include "stdafx.h"

#include "NMDS.hpp"

#define BUFSIZE 2047

#define MAXIT 50

#define NITER 100
#define MAGIC 0.2
#define TOL 1e-04

enum mdsTYPE { mdsKRUSKAL, mdsSAMMON };

typedef long int integer;
typedef double doublereal;

#define custom_min(a,b) ((a) <= (b) ? (a) : (b))
#define custom_max(a,b) ((a) >= (b) ? (a) : (b))
#define custom_abs(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    long int
        i;
    double
        f;
} VALUE;

VALUE
    *value;

mdsTYPE
    mdstype = mdsKRUSKAL;

bool
    converged = false;

double
    *x,
    *y,
    stress,
    *Tmat,
    final_value,
    final_r,
    magic = MAGIC,
    final_magic,
    tol = TOL;

int
    arg_c,
    maxitdefined = 0,
    stopped_after,
		k;

long int
    size,
    maxit = MAXIT,
    niter = NITER,
    input_line = 0;

void
    *s_malloc (size_t size);

char
    *get_arg (void);

int
    cmp_by_s (void const *p1, void const *p2),
    cmp_by_i (void const *p1, void const *p2),
    cmp_lbl (void const *key, void const *p),
    order (void const *p1, void const *p2),
    revorder (void const *p1, void const *p2);

int
    rs_ (
        integer *nm,
        integer *n,
        doublereal *a,
        doublereal *w,
        integer *matz,
        doublereal *z__,
        doublereal *fv1,
        doublereal *fv2,
        integer *ierr
    );

double corr (void);

void
    VR_mds_init_data (
        long int pn,
        long int pc,
        long int pr,
        long int *orde,
        long int *ordee,
        double *xx
    ),
    VR_mds_dovm (void),
    vmmin (long int n, double *b),
    VR_sammon (
        double *dd,
        long int *nn,
        int *kd,
        double *Y,
        long int *niter,
        double *stress,
        double *aa,
        double *tol
    );


void NMDS::Project(const Matrix& dissMatrix, int maxIter)
{
    long int
        i,
        j,
        n,
        ierr,
        li,
        lsize,
        *ord,
        *orderord;
    double
        sum,
        *dbl_n,
        *fv1,
        *fv2,
        *vectors;

		k = 3;
		maxit = maxIter;
		size = dissMatrix.size();

    x = (double *) s_malloc (size * size * sizeof (double));
		Tmat = (double *) s_malloc (size * size * sizeof (double));
    for (i = 0; i < size; i++) 
		{
        x [i + i * size] = 0.0;
				Tmat [i + i * size] = 0.0;

        for (j = 0; j < i; j++) 
				{
            x [i + j * size] = x [i * size + j] = dissMatrix[i][j];
						Tmat [i + j * size] = Tmat [i * size + j] = dissMatrix[i][j] * dissMatrix[i][j];
				}
    }

		// initialize
    for (i = 0; i < size; i++) {
        sum = 0;
        for (j = 0; j < size; j++)
            sum += Tmat [i + j * size];
        sum /= size;
        for (j = 0; j < size; j++)
            Tmat [i + j * size] -= sum;
    }
    for (j = 0; j < size; j++) {
        sum = 0;
        for (i = 0; i < size; i++)
            sum += Tmat [i + j * size];
        sum /= size;
        for (i = 0; i < size; i++)
            Tmat [i + j * size] -= sum;
    }
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            Tmat [i + j * size] *= -0.5;

    dbl_n = (double *) s_malloc (size * sizeof (double));
    fv1 = (double *) s_malloc (size * sizeof (double));
    fv2 = (double *) s_malloc (size * sizeof (double));
    vectors = (double *) s_malloc (size * size * sizeof (double));

    li = 1;
    lsize = size;

    rs_ (&lsize, &lsize, Tmat, dbl_n, &li, vectors, fv1, fv2, &ierr);

    free (fv1);
    free (fv2);
    free (Tmat);

    value = (VALUE *) s_malloc (size * sizeof (VALUE));
    for (i = 0; i < size; i++) {
        value [i].i = i;
        value [i].f = dbl_n [i];
    }

    free (dbl_n);

    qsort (value, size, sizeof (VALUE), revorder);

    for (i = 0; i < k; i++)
        value [i].f = sqrt (value [i].f);

    y = (double *) s_malloc (size * k * sizeof (double));
    for (i = 0; i < size; i++)
        for (j = 0; j < k; j++)
            y [i + size * j] = vectors [i + value [j].i * size] * value [j].f;

    corr();

    free (value);
    free (vectors);

    if (mdstype == mdsKRUSKAL) 
		{

        value = (VALUE*) s_malloc ((size * size - size) / 2 * sizeof (VALUE));
        n = 0;
        for (i = 0; i < size; i++)
            for (j = i + 1; j < size; j++) {
                value [n].f = x [i + j * size];
                value [n].i = n;
                n++;
            }

        qsort (value, (size * size - size) / 2, sizeof (VALUE), order);

        ord = (long int *) s_malloc ((size * size - size) / 2 * sizeof (long int));
        for (i = 0; i < n; i++)
            ord [i] = value [i].i;

        free (value);

        orderord = (long int *) s_malloc ((size * size - size) / 2 * sizeof (long int));
        for (i = 0; i < n; i++)
            orderord [ord [i]] = i;

        VR_mds_init_data (n, k, size, ord, orderord, y);

        VR_mds_dovm ();

    } 
		else 
		{

        n = size;
        VR_sammon(x, &n, &k, y, &niter, &stress, &magic, &tol);
        final_value = stress;
    }

		m_projectedData.clear();
		for(i = 0; i < size; ++i)
			m_projectedData.append(QVector<double>(k));

		for (i = 0; i < size; i++)
        for (j = 0; j < k; j++)
            m_projectedData[i][j] = y[i + j * size];

    m_correlation = corr();

		free(x);
}

double corr ()
{
    long int
        i,
        j,
        n;
    double
        f,
        f1,
        *yy,
        sumx,
        sumxx,
        sumy,
        sumyy,
        sumxy,
        sx,
        sy;

    yy = (double *) s_malloc (size * size * sizeof (double));
    for (i = 0; i < size; i++) {
        yy [i + size * i] = 0.0;
        for (j = 0; j < size; j++) {
            f = 0.0;
            for (n = 0; n < k; n++) {
                f1 = y [i + size * n] - y [j + size * n];
                f += f1 * f1;
            }
            yy [i + size * j] = yy [j + size * i] = sqrt (f);
        }
    }

    n = (size * size - size) / 2;
    sumxy = sumxx = sumyy = sumx = sumy = 0.0;
    for (i = 0; i < size; i++)
        for (j = 0; j < i; j++) {
            sumx += x [i + size * j];
            sumxx += x [i + size * j] * x [i + size * j];
            sumy += yy [i + size * j];
            sumyy += yy [i + size * j] * yy [i + size * j];
            sumxy += x [i + size * j] * yy [i + size * j];
        }
    sx = sqrt ((sumxx - sumx * sumx / n) / (n - 1));
    sy = sqrt ((sumyy - sumy * sumy / n) / (n - 1));

    final_r = (sumxy - sumx * sumy / n) / ((n - 1) * sx * sy);

    free (yy);

		return final_r;
}

int order (void const *p1, void const *p2)
{
    if (((VALUE *) p1)->f < ((VALUE *) p2)->f)
        return -1;
    if (((VALUE *) p1)->f > ((VALUE *) p2)->f)
        return 1;
    return 0;
}

int revorder (void const *p1, void const *p2)
{
    if (((VALUE *) p1)->f < ((VALUE *) p2)->f)
        return 1;
    if (((VALUE *) p1)->f > ((VALUE *) p2)->f)
        return -1;
    return 0;
}

void *s_malloc (size_t size)
{
    void *p;

    p = malloc (size);

    return p;
}

double d_sign(doublereal *a, doublereal *b)
{
    double
        x;
    x = (*a >= 0 ? *a : - *a);
    return (*b >= 0 ? x : -x);
}

/*

 MASS.c

 */

#define VR_stepredn        0.2
#define VR_acctol          0.0001
#define VR_reltest         10.0
#define VR_abstol          1.0e-2
#define VR_reltol          1.0e-3
#define VR_REPORT          5

long int
    VR_n,
    VR_nr,
    VR_nc,
    VR_dimx,
    *VR_ord,
    *VR_ord2;
double
    *VR_d,
    *VR_y,
    *VR_yf,
    *VR_x;

void VR_mds_init_data (long int pn, long int pc, long int pr, long int *orde,
                 long int *ordee, double *xx)
{
    VR_n = pn;
    VR_nr = pr;
    VR_nc = pc;
    VR_dimx = VR_nr * VR_nc;
    VR_d = (double *) s_malloc (VR_n * sizeof (double));
    VR_y = (double *) s_malloc (VR_n * sizeof (double));
    VR_yf = (double *) s_malloc (VR_n * sizeof (double));
    VR_ord = orde;
    VR_ord2 = ordee;
    VR_x = xx;
}

void VR_mds_dovm ()
{
    vmmin (VR_dimx, VR_x);
}

double **Lmatrix(int n)
{
    int
        i;
    double
        **m;

    m = (double **) s_malloc (n * sizeof (double *));

    for (i = 0; i < n; i++)
        m [i] = (double *) s_malloc ((i + 1) * sizeof (double));

    return m;
}

void calc_dist (double *x)
{
    int   r1, r2, c, index;
    double tmp, tmp1;

    index = 0;
    for (r1 = 0; r1 < VR_nr; r1++)
        for (r2 = r1 + 1; r2 < VR_nr; r2++) {
            tmp = 0.0;
            for (c = 0; c < VR_nc; c++) {
                tmp1 = x[r1 + c * VR_nr] - x[r2 + c * VR_nr];
                tmp += tmp1 * tmp1;
            }
            VR_d[index++] = sqrt(tmp);
        }
    for (index = 0; index < VR_n; index++)
        VR_y[index] = VR_d[VR_ord[index]];
}

void VR_mds_fn(
    double *y, double *yf, long int *pn, double *pssq, long int *pd,
    double *x, long int *pr, long int *pncol, double *der,
    long int *do_derivatives)
{
    int   n = *pn, i, ip=0, known, u, s, r = *pr, ncol = *pncol, k=0;
    double tmp, ssq, *yc, slope, tstar, sstar;

    yc = (double *) s_malloc ((n + 1) * sizeof (double));
    yc[0] = 0.0;
    tmp = 0.0;
    for (i = 0; i < n; i++) {
        tmp += y[i];
        yc[i + 1] = tmp;
    }
    known = 0;
    do {
        slope = 1.0e+200;
        for (i = known + 1; i <= n; i++) {
            tmp = (yc[i] - yc[known]) / (i - known);
            if (tmp < slope) {
                slope = tmp;
                ip = i;
            }
        }
        for (i = known; i < ip; i++)
            yf[i] = (yc[ip] - yc[known]) / (ip - known);
    } while ((known = ip) < n);

    sstar = 0.0;
    tstar = 0.0;
    for (i = 0; i < n; i++) {
        tmp = y[i] - yf[i];
        sstar += tmp * tmp;
        tstar += y[i] * y[i];
    }
    ssq = 100 * sqrt(sstar / tstar);
    *pssq = ssq;
    free (yc);
    if (!(*do_derivatives)) return;
    /* get derivatives */
    for (u = 0; u < r; u++) {
        for (i = 0; i < ncol; i++) {
            tmp = 0.0;
            for (s = 0; s < r; s++) {
                if (s > u)
                    k = r * u - u * (u + 1) / 2 + s - u;
                else if (s < u)
                    k = r * s - s * (s + 1) / 2 + u - s;
                if (s != u) {
                    k = pd[k - 1];
                    tmp += ((y[k] - yf[k]) / sstar
                            - y[k] / tstar) * (x[u + r * i] - x[s + r * i]) / y[k];
                }
            }
            der[u + i * r] = tmp * ssq;
        }
    }
}

double fminfn (double *x)
{
    double
        ssq;
    long int
        do_derivatives = 0;

    calc_dist (x);
    VR_mds_fn (VR_y, VR_yf, &VR_n, &ssq, VR_ord2, x, &VR_nr, &VR_nc, 0, &do_derivatives);
    return (ssq);
}

void fmingr(double *x, double *der)
{
    double ssq;
    long int  do_derivatives = 1;

    calc_dist(x);
    VR_mds_fn (VR_y, VR_yf, &VR_n, &ssq, VR_ord2, x, &VR_nr, &VR_nc, der, &do_derivatives);
}

void free_Lmatrix(double **m, int n)
{
    int   i;

    for (i = n - 1; i >= 0; i--) free(m[i]);
    free(m);
}

void vmmin (long int n, double *b)
{
    bool accpoint, enough;
    double *g, *t, *X, *c, **B;
    int     count, funcount, gradcount;
    double  Fmin, f, gradproj;
    int     i, j, ilast, iter = 0;
    double  s, steplength;
    double  D1, D2;

    g = (double *) s_malloc (n * sizeof (double));
    t = (double *) s_malloc (n * sizeof (double));
    X = (double *) s_malloc (n * sizeof (double));
    c = (double *) s_malloc (n * sizeof (double));
    B = Lmatrix (n);
    f = fminfn (b);

    {
        Fmin = f;
        funcount = gradcount = 1;
        fmingr(b, g);
        iter++;
        ilast = gradcount;

        do {
            if (ilast == gradcount) {
                for (i = 0; i < n; i++) {
                    for (j = 0; j < i; j++)
                        B[i][j] = 0.0;
                    B[i][i] = 1.0;
                }
            }

            for (i = 0; i < n; i++) {
                X[i] = b[i];
                c[i] = g[i];
            }
            gradproj = 0.0;
            for (i = 0; i < n; i++) {
                s = 0.0;
                for (j = 0; j <= i; j++) s -= B[i][j] * g[j];
                for (j = i + 1; j < n; j++) s -= B[j][i] * g[j];
                t[i] = s;
                gradproj += s * g[i];
            }

            if (gradproj < 0.0) {       /* search direction is downhill */
                steplength = 1.0;
                accpoint = false;
                do {
                    count = 0;
                    for (i = 0; i < n; i++) {
                        b[i] = X[i] + steplength * t[i];
                        if (VR_reltest + X[i] == VR_reltest + b[i])     /* no change */
                            count++;
                    }
                    if (count < n) {
                        f = fminfn(b);
                        funcount++;
                        accpoint = (f <= Fmin + gradproj * steplength * VR_acctol);

                        if (!accpoint) {
                            steplength *= VR_stepredn;
                        }
                    }
                } while (!(count == n || accpoint));
                enough = (f > VR_abstol) && (f < (1.0 - VR_reltol) * Fmin);
                /* stop if value if small or if relative change is low */
                if (!enough) count = n;
                if (count < n) {        /* making progress */
                    Fmin = f;
                    fmingr(b, g);
                    gradcount++;
                    iter++;
                    D1 = 0.0;
                    for (i = 0; i < n; i++) {
                        t[i] = steplength * t[i];
                        c[i] = g[i] - c[i];
                        D1 += t[i] * c[i];
                    }
                    if (D1 > 0) {
                        D2 = 0.0;
                        for (i = 0; i < n; i++) {
                            s = 0.0;
                            for (j = 0; j <= i; j++)
                                s += B[i][j] * c[j];
                            for (j = i + 1; j < n; j++)
                                s += B[j][i] * c[j];
                            X[i] = s;
                            D2 += s * c[i];
                        }
                        D2 = 1.0 + D2 / D1;
                        for (i = 0; i < n; i++) {
                            for (j = 0; j <= i; j++)
                                B[i][j] += (D2 * t[i] * t[j] - X[i] * t[j] - t[i] * X[j]) / D1;
                        }
                    } else {    /* D1 < 0 */
                        ilast = gradcount;
                    }
                } else {        /* no progress */
                    if (ilast < gradcount) {
                        count = 0;
                        ilast = gradcount;
                    }
                }
            } else {            /* uphill search */
                count = 0;
                if (ilast == gradcount) count = n;
                else ilast = gradcount;
                /* Resets unless has just been reset */
            }

            if (iter >= maxit)
                break;
            if (gradcount - ilast > 2 * n)
                ilast = gradcount;      /* periodic restart */
        } while (count != n || ilast != gradcount);
    }
    final_value = Fmin;

    if (iter < maxit) {
        converged = true;
    } else {
        converged = false;
        stopped_after = iter;
    }

    free (g);
    free (t);
    free (X);
    free (c);
    free_Lmatrix(B, n);
}

void VR_sammon(double *dd, long int *nn, int *kd, double *Y, long int *niter, double *stress, double *aa, double *tol)
{
    int   i, j, k, m, n, nd;
    double *xu, *xv, *e1, *e2;
    double dpj, dq, dr, dt;
    double xd, xx;
    double e, epast, eprev, tot, d, d1, ee, magic;

    n = *nn;
    nd = *kd;
    magic = *aa;

    xu = (double *) s_malloc(nd * n * sizeof (double));
    xv = (double *) s_malloc(nd * sizeof (double));
    e1 = (double *) s_malloc(nd * sizeof (double));
    e2 = (double *) s_malloc(nd * sizeof (double));

    epast = eprev = 1.0;

    /* Error in distances */
    e = tot = 0.0;
    for (j = 1; j < n; j++) {
        for (k = 0; k < j; k++) {
            d = dd[k * n + j];

						tot += d;
            d1 = 0.0;
            for (m = 0; m < nd; m++) {
                xd = Y[j + m * n] - Y[k + m * n];
                d1 += xd * xd;
            }
            ee = d - sqrt(d1);
            e += (ee * ee / d);
        }
    }
    e /= tot;

    epast = eprev = e;

    /* Iterate */
    for (i = 1; i <= *niter; i++) {
CORRECT:
        for (j = 0; j < n; j++) {
            for (m = 0; m < nd; m++)
                e1[m] = e2[m] = 0.0;
            for (k = 0; k < n; k++) {
                if (j == k)
                    continue;
                d1 = 0.0;
                for (m = 0; m < nd; m++) {
                    xd = Y[j + m * n] - Y[k + m * n];
                    d1 += xd * xd;
                    xv[m] = xd;
                }
                dpj = sqrt(d1);

                /* Calculate derivatives */
                dt = dd[k * n + j];
                dq = dt - dpj;
                dr = dt * dpj;
                for (m = 0; m < nd; m++) {
                    e1[m] += xv[m] * dq / dr;
                    e2[m] += (dq - xv[m] * xv[m] * (1.0 + dq / dpj) / dpj) / dr;
                }
            }
            /* Correction */
            for (m = 0; m < nd; m++)
                xu[j + m * n] = Y[j + m * n] + magic * e1[m] / fabs(e2[m]);
        }

        /* Error in distances */
        e = 0.0;
        for (j = 1; j < n; j++)
            for (k = 0; k < j; k++) {
                d = dd[k * n + j];
                d1 = 0.0;
                for (m = 0; m < nd; m++) {
                    xd = xu[j + m * n] - xu[k + m * n];
                    d1 += xd * xd;
                }
                ee = d - sqrt(d1);
                e += (ee * ee / d);
            }
        e /= tot;
        if (e > eprev) {
            e = eprev;
            magic = magic * 0.2;
            if (magic > 1.0e-3) goto CORRECT;

            break;
        }
        magic *= 1.5;
        if (magic > 0.5) magic = 0.5;
        eprev = e;

        /* Move the centroid to origin and update */
        for (m = 0; m < nd; m++) {
            xx = 0.0;
            for (j = 0; j < n; j++)
                xx += xu[j + m * n];
            xx /= n;
            for (j = 0; j < n; j++)
                Y[j + m * n] = xu[j + m * n] - xx;
        }

        if (i % 10 == 0) 
				{

            if (e > epast - *tol)
                break;
            epast = e;
        }
    }

    if (i <= *niter)
        converged = true;
    else
        stopped_after = *niter;
    final_magic = magic;

    *stress = e;
    free (xu);
    free (xv);
    free (e1);
    free (e2);
}

/* eigen.f -- translated by f2c (version 19970805).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

/* Table of constant values */

static doublereal c_b296 = 1.;

doublereal pythag_(doublereal *a, doublereal *b)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2, d__3;

    /* Local variables */
    static doublereal p, r__, s, t, u;


/*     FINDS DSQRT(A**2+B**2) WITHOUT OVERFLOW OR DESTRUCTIVE UNDERFLOW */

/* Computing MAX */
    d__1 = custom_abs(*a), d__2 = custom_abs(*b);
    p = custom_max(d__1,d__2);
    if (p == 0.) {
        goto L20;
    }
/* Computing MIN */
    d__2 = custom_abs(*a), d__3 = custom_abs(*b);
/* Computing 2nd power */
    d__1 = custom_min(d__2,d__3) / p;
    r__ = d__1 * d__1;
L10:
    t = r__ + 4.;
    if (t == 4.) {
        goto L20;
    }
    s = r__ / t;
    u = s * 2. + 1.;
    p = u * p;
/* Computing 2nd power */
    d__1 = s / u;
    r__ = d__1 * d__1 * r__;
    goto L10;
L20:
    ret_val = p;
    return ret_val;
} /* pythag_ */

/* Subroutine */ int tql2_(integer *nm, integer *n, doublereal *d__,
        doublereal *e, doublereal *z__, integer *ierr)
{
    /* System generated locals */
    integer z_dim1, z_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__, f, g, h__;
    static integer i__, j, k, l, m;
    static doublereal p, r__, s, c2, c3;
    static integer l1, l2;
    static doublereal s2;
    static integer ii;
    extern doublereal pythag_(doublereal *, doublereal *);
    static doublereal dl1, el1;
    static integer mml;
    static doublereal tst1, tst2;



/*     THIS SUBROUTINE IS A TRANSLATION OF THE ALGOL PROCEDURE TQL2, */
/*     NUM. MATH. 11, 293-306(1968) BY BOWDLER, MARTIN, REINSCH, AND */
/*     WILKINSON. */
/*     HANDBOOK FOR AUTO. COMP., VOL.II-LINEAR ALGEBRA, 227-240(1971). */

/*     THIS SUBROUTINE FINDS THE EIGENVALUES AND EIGENVECTORS */
/*     OF A SYMMETRIC TRIDIAGONAL MATRIX BY THE QL METHOD. */
/*     THE EIGENVECTORS OF A FULL SYMMETRIC MATRIX CAN ALSO */
/*     BE FOUND IF  TRED2  HAS BEEN USED TO REDUCE THIS */
/*     FULL MATRIX TO TRIDIAGONAL FORM. */

/*     ON INPUT */

/*        NM MUST BE SET TO THE ROW DIMENSION OF TWO-DIMENSIONAL */
/*          ARRAY PARAMETERS AS DECLARED IN THE CALLING PROGRAM */
/*          DIMENSION STATEMENT. */

/*        N IS THE ORDER OF THE MATRIX. */

/*        D CONTAINS THE DIAGONAL ELEMENTS OF THE INPUT MATRIX. */

/*        E CONTAINS THE SUBDIAGONAL ELEMENTS OF THE INPUT MATRIX */
/*          IN ITS LAST N-1 POSITIONS.  E(1) IS ARBITRARY. */

/*        Z CONTAINS THE TRANSFORMATION MATRIX PRODUCED IN THE */
/*          REDUCTION BY  TRED2, IF PERFORMED.  IF THE EIGENVECTORS */
/*          OF THE TRIDIAGONAL MATRIX ARE DESIRED, Z MUST CONTAIN */
/*          THE IDENTITY MATRIX. */

/*      ON OUTPUT */

/*        D CONTAINS THE EIGENVALUES IN ASCENDING ORDER.  IF AN */
/*          ERROR EXIT IS MADE, THE EIGENVALUES ARE CORRECT BUT */
/*          UNORDERED FOR INDICES 1,2,...,IERR-1. */

/*        E HAS BEEN DESTROYED. */

/*        Z CONTAINS ORTHONORMAL EIGENVECTORS OF THE SYMMETRIC */
/*          TRIDIAGONAL (OR FULL) MATRIX.  IF AN ERROR EXIT IS MADE, */
/*          Z CONTAINS THE EIGENVECTORS ASSOCIATED WITH THE STORED */
/*          EIGENVALUES. */

/*        IERR IS SET TO */
/*          ZERO       FOR NORMAL RETURN, */
/*          J          IF THE J-TH EIGENVALUE HAS NOT BEEN */
/*                     DETERMINED AFTER 30 ITERATIONS. */

/*     CALLS PYTHAG FOR  DSQRT(A*A + B*B) . */

/*     QUESTIONS AND COMMENTS SHOULD BE DIRECTED TO BURTON S. GARBOW, */
/*     MATHEMATICS AND COMPUTER SCIENCE DIV, ARGONNE NATIONAL LABORATORY
*/

/*     THIS VERSION DATED AUGUST 1983. */

/*     ------------------------------------------------------------------
*/

/*     unnecessary initialization of C3 and S2 to keep g77 -Wall happy */

    /* Parameter adjustments */
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z__ -= z_offset;
    --e;
    --d__;

    /* Function Body */
    c3 = 0.;
    s2 = 0.;

    *ierr = 0;
    if (*n == 1) {
        goto L1001;
    }

    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
/* L100: */
        e[i__ - 1] = e[i__];
    }

    f = 0.;
    tst1 = 0.;
    e[*n] = 0.;

    i__1 = *n;
    for (l = 1; l <= i__1; ++l) {
        j = 0;
        h__ = (d__1 = d__[l], custom_abs(d__1)) + (d__2 = e[l], custom_abs(d__2));
        if (tst1 < h__) {
            tst1 = h__;
        }
/*     .......... LOOK FOR SMALL SUB-DIAGONAL ELEMENT .......... */
        i__2 = *n;
        for (m = l; m <= i__2; ++m) {
            tst2 = tst1 + (d__1 = e[m], custom_abs(d__1));
            if (tst2 == tst1) {
                goto L120;
            }
/*     .......... E(N) IS ALWAYS ZERO, SO THERE IS NO EXIT */
/*                THROUGH THE BOTTOM OF THE LOOP .......... */
/* L110: */
        }

L120:
        if (m == l) {
            goto L220;
        }
L130:
        if (j == 30) {
            goto L1000;
        }
        ++j;
/*     .......... FORM SHIFT .......... */
        l1 = l + 1;
        l2 = l1 + 1;
        g = d__[l];
        p = (d__[l1] - g) / (e[l] * 2.);
        r__ = pythag_(&p, &c_b296);
        d__[l] = e[l] / (p + d_sign(&r__, &p));
        d__[l1] = e[l] * (p + d_sign(&r__, &p));
        dl1 = d__[l1];
        h__ = g - d__[l];
        if (l2 > *n) {
            goto L145;
        }

        i__2 = *n;
        for (i__ = l2; i__ <= i__2; ++i__) {
/* L140: */
            d__[i__] -= h__;
        }

L145:
        f += h__;
/*     .......... QL TRANSFORMATION .......... */
        p = d__[m];
        c__ = 1.;
        c2 = c__;
        el1 = e[l1];
        s = 0.;
        mml = m - l;
/*     .......... FOR I=M-1 STEP -1 UNTIL L DO -- .......... */
        i__2 = mml;
        for (ii = 1; ii <= i__2; ++ii) {
            c3 = c2;
            c2 = c__;
            s2 = s;
            i__ = m - ii;
            g = c__ * e[i__];
            h__ = c__ * p;
            r__ = pythag_(&p, &e[i__]);
            e[i__ + 1] = s * r__;
            s = e[i__] / r__;
            c__ = p / r__;
            p = c__ * d__[i__] - s * g;
            d__[i__ + 1] = h__ + s * (c__ * g + s * d__[i__]);
/*     .......... FORM VECTOR .......... */
            i__3 = *n;
            for (k = 1; k <= i__3; ++k) {
                h__ = z__[k + (i__ + 1) * z_dim1];
                z__[k + (i__ + 1) * z_dim1] = s * z__[k + i__ * z_dim1] + c__
                        * h__;
                z__[k + i__ * z_dim1] = c__ * z__[k + i__ * z_dim1] - s * h__;
/* L180: */
            }

/* L200: */
        }

        p = -s * s2 * c3 * el1 * e[l] / dl1;
        e[l] = s * p;
        d__[l] = c__ * p;
        tst2 = tst1 + (d__1 = e[l], custom_abs(d__1));
        if (tst2 > tst1) {
            goto L130;
        }
L220:
        d__[l] += f;
/* L240: */
    }
/*     .......... ORDER EIGENVALUES AND EIGENVECTORS .......... */
    i__1 = *n;
    for (ii = 2; ii <= i__1; ++ii) {
        i__ = ii - 1;
        k = i__;
        p = d__[i__];

        i__2 = *n;
        for (j = ii; j <= i__2; ++j) {
            if (d__[j] >= p) {
                goto L260;
            }
            k = j;
            p = d__[j];
L260:
            ;
        }

        if (k == i__) {
            goto L300;
        }
        d__[k] = d__[i__];
        d__[i__] = p;

        i__2 = *n;
        for (j = 1; j <= i__2; ++j) {
            p = z__[j + i__ * z_dim1];
            z__[j + i__ * z_dim1] = z__[j + k * z_dim1];
            z__[j + k * z_dim1] = p;
/* L280: */
        }

L300:
        ;
    }

    goto L1001;
/*     .......... SET ERROR -- NO CONVERGENCE TO AN */
/*                EIGENVALUE AFTER 30 ITERATIONS .......... */
L1000:
    *ierr = l;
L1001:
    return 0;
} /* tql2_ */

/* Subroutine */ int tred2_(integer *nm, integer *n, doublereal *a,
        doublereal *d__, doublereal *e, doublereal *z__)
{
    /* System generated locals */
    integer a_dim1, a_offset, z_dim1, z_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), d_sign(doublereal *, doublereal *);

    /* Local variables */
    static doublereal f, g, h__;
    static integer i__, j, k, l;
    static doublereal scale, hh;
    static integer ii, jp1;



/*     THIS SUBROUTINE IS A TRANSLATION OF THE ALGOL PROCEDURE TRED2, */
/*     NUM. MATH. 11, 181-195(1968) BY MARTIN, REINSCH, AND WILKINSON. */
/*     HANDBOOK FOR AUTO. COMP., VOL.II-LINEAR ALGEBRA, 212-226(1971). */

/*     THIS SUBROUTINE REDUCES A REAL SYMMETRIC MATRIX TO A */
/*     SYMMETRIC TRIDIAGONAL MATRIX USING AND ACCUMULATING */
/*     ORTHOGONAL SIMILARITY TRANSFORMATIONS. */

/*     ON INPUT */

/*        NM MUST BE SET TO THE ROW DIMENSION OF TWO-DIMENSIONAL */
/*          ARRAY PARAMETERS AS DECLARED IN THE CALLING PROGRAM */
/*          DIMENSION STATEMENT. */

/*        N IS THE ORDER OF THE MATRIX. */

/*        A CONTAINS THE REAL SYMMETRIC INPUT MATRIX.  ONLY THE */
/*          LOWER TRIANGLE OF THE MATRIX NEED BE SUPPLIED. */

/*     ON OUTPUT */

/*        D CONTAINS THE DIAGONAL ELEMENTS OF THE TRIDIAGONAL MATRIX. */

/*        E CONTAINS THE SUBDIAGONAL ELEMENTS OF THE TRIDIAGONAL */
/*          MATRIX IN ITS LAST N-1 POSITIONS.  E(1) IS SET TO ZERO. */

/*        Z CONTAINS THE ORTHOGONAL TRANSFORMATION MATRIX */
/*          PRODUCED IN THE REDUCTION. */

/*        A AND Z MAY COINCIDE.  IF DISTINCT, A IS UNALTERED. */

/*     QUESTIONS AND COMMENTS SHOULD BE DIRECTED TO BURTON S. GARBOW, */
/*     MATHEMATICS AND COMPUTER SCIENCE DIV, ARGONNE NATIONAL LABORATORY
*/

/*     THIS VERSION DATED AUGUST 1983. */

/*     ------------------------------------------------------------------
*/

    /* Parameter adjustments */
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z__ -= z_offset;
    --e;
    --d__;
    a_dim1 = *nm;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {

        i__2 = *n;
        for (j = i__; j <= i__2; ++j) {
/* L80: */
            z__[j + i__ * z_dim1] = a[j + i__ * a_dim1];
        }

        d__[i__] = a[*n + i__ * a_dim1];
/* L100: */
    }

    if (*n == 1) {
        goto L510;
    }
/*     .......... FOR I=N STEP -1 UNTIL 2 DO -- .......... */
    i__1 = *n;
    for (ii = 2; ii <= i__1; ++ii) {
        i__ = *n + 2 - ii;
        l = i__ - 1;
        h__ = 0.;
        scale = 0.;
        if (l < 2) {
            goto L130;
        }
/*     .......... SCALE ROW (ALGOL TOL THEN NOT NEEDED) .......... */
        i__2 = l;
        for (k = 1; k <= i__2; ++k) {
/* L120: */
            scale += (d__1 = d__[k], custom_abs(d__1));
        }

        if (scale != 0.) {
            goto L140;
        }
L130:
        e[i__] = d__[l];

        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
            d__[j] = z__[l + j * z_dim1];
            z__[i__ + j * z_dim1] = 0.;
            z__[j + i__ * z_dim1] = 0.;
/* L135: */
        }

        goto L290;

L140:
        i__2 = l;
        for (k = 1; k <= i__2; ++k) {
            d__[k] /= scale;
            h__ += d__[k] * d__[k];
/* L150: */
        }

        f = d__[l];
        d__1 = sqrt(h__);
        g = -d_sign(&d__1, &f);
        e[i__] = scale * g;
        h__ -= f * g;
        d__[l] = f - g;
/*     .......... FORM A*U .......... */
        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
/* L170: */
            e[j] = 0.;
        }

        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
            f = d__[j];
            z__[j + i__ * z_dim1] = f;
            g = e[j] + z__[j + j * z_dim1] * f;
            jp1 = j + 1;
            if (l < jp1) {
                goto L220;
            }

            i__3 = l;
            for (k = jp1; k <= i__3; ++k) {
                g += z__[k + j * z_dim1] * d__[k];
                e[k] += z__[k + j * z_dim1] * f;
/* L200: */
            }

L220:
            e[j] = g;
/* L240: */
        }
/*     .......... FORM P .......... */
        f = 0.;

        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
            e[j] /= h__;
            f += e[j] * d__[j];
/* L245: */
        }

        hh = f / (h__ + h__);
/*     .......... FORM Q .......... */
        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
/* L250: */
            e[j] -= hh * d__[j];
        }
/*     .......... FORM REDUCED A .......... */
        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
            f = d__[j];
            g = e[j];

            i__3 = l;
            for (k = j; k <= i__3; ++k) {
/* L260: */
                z__[k + j * z_dim1] = z__[k + j * z_dim1] - f * e[k] - g *
                        d__[k];
            }

            d__[j] = z__[l + j * z_dim1];
            z__[i__ + j * z_dim1] = 0.;
/* L280: */
        }

L290:
        d__[i__] = h__;
/* L300: */
    }
/*     .......... ACCUMULATION OF TRANSFORMATION MATRICES .......... */
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
        l = i__ - 1;
        z__[*n + l * z_dim1] = z__[l + l * z_dim1];
        z__[l + l * z_dim1] = 1.;
        h__ = d__[i__];
        if (h__ == 0.) {
            goto L380;
        }

        i__2 = l;
        for (k = 1; k <= i__2; ++k) {
/* L330: */
            d__[k] = z__[k + i__ * z_dim1] / h__;
        }

        i__2 = l;
        for (j = 1; j <= i__2; ++j) {
            g = 0.;

            i__3 = l;
            for (k = 1; k <= i__3; ++k) {
/* L340: */
                g += z__[k + i__ * z_dim1] * z__[k + j * z_dim1];
            }

            i__3 = l;
            for (k = 1; k <= i__3; ++k) {
                z__[k + j * z_dim1] -= g * d__[k];
/* L360: */
            }
        }

L380:
        i__3 = l;
        for (k = 1; k <= i__3; ++k) {
/* L400: */
            z__[k + i__ * z_dim1] = 0.;
        }

/* L500: */
    }

L510:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
        d__[i__] = z__[*n + i__ * z_dim1];
        z__[*n + i__ * z_dim1] = 0.;
/* L520: */
    }

    z__[*n + *n * z_dim1] = 1.;
    e[1] = 0.;
    return 0;
} /* tred2_ */

/* Subroutine */ int rs_(integer *nm, integer *n, doublereal *a, doublereal *
        w, integer *matz, doublereal *z__, doublereal *fv1, doublereal *fv2,
        integer *ierr)
{
    /* System generated locals */
    integer a_dim1, a_offset, z_dim1, z_offset;

    /* Local variables */
    extern /* Subroutine */ int tred1_(integer *, integer *, doublereal *,
            doublereal *, doublereal *, doublereal *), tred2_(integer *,
            integer *, doublereal *, doublereal *, doublereal *, doublereal *)
            , tqlrat_(integer *, doublereal *, doublereal *, integer *),
            tql2_(integer *, integer *, doublereal *, doublereal *,
            doublereal *, integer *);



/*     THIS SUBROUTINE CALLS THE RECOMMENDED SEQUENCE OF */
/*     SUBROUTINES FROM THE EIGENSYSTEM SUBROUTINE PACKAGE (EISPACK) */
/*     TO FIND THE EIGENVALUES AND EIGENVECTORS (IF DESIRED) */
/*     OF A REAL SYMMETRIC MATRIX. */

/*     ON INPUT */

/*        NM  MUST BE SET TO THE ROW DIMENSION OF THE TWO-DIMENSIONAL */
/*        ARRAY PARAMETERS AS DECLARED IN THE CALLING PROGRAM */
/*        DIMENSION STATEMENT. */

/*        N  IS THE ORDER OF THE MATRIX  A. */

/*        A  CONTAINS THE REAL SYMMETRIC MATRIX. */

/*        MATZ  IS AN INTEGER VARIABLE SET EQUAL TO ZERO IF */
/*        ONLY EIGENVALUES ARE DESIRED.  OTHERWISE IT IS SET TO */
/*        ANY NON-ZERO INTEGER FOR BOTH EIGENVALUES AND EIGENVECTORS. */

/*     ON OUTPUT */

/*        W  CONTAINS THE EIGENVALUES IN ASCENDING ORDER. */

/*        Z  CONTAINS THE EIGENVECTORS IF MATZ IS NOT ZERO. */

/*        IERR  IS AN INTEGER OUTPUT VARIABLE SET EQUAL TO AN ERROR */
/*           COMPLETION CODE DESCRIBED IN THE DOCUMENTATION FOR TQLRAT */
/*           AND TQL2.  THE NORMAL COMPLETION CODE IS ZERO. */

/*        FV1  AND  FV2  ARE TEMPORARY STORAGE ARRAYS. */

/*     QUESTIONS AND COMMENTS SHOULD BE DIRECTED TO BURTON S. GARBOW, */
/*     MATHEMATICS AND COMPUTER SCIENCE DIV, ARGONNE NATIONAL LABORATORY
*/

/*     THIS VERSION DATED AUGUST 1983. */

/*     ------------------------------------------------------------------
*/

    /* Parameter adjustments */
    --fv2;
    --fv1;
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z__ -= z_offset;
    --w;
    a_dim1 = *nm;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    if (*n <= *nm) {
        goto L10;
    }
    *ierr = *n * 10;
    goto L50;

L10:
    if (*matz != 0) {
        goto L20;
    }
/*     .......... FIND EIGENVALUES ONLY .......... */
    goto L50;
/*     .......... FIND BOTH EIGENVALUES AND EIGENVECTORS .......... */
L20:
    tred2_(nm, n, &a[a_offset], &w[1], &fv1[1], &z__[z_offset]);
    tql2_(nm, n, &w[1], &fv1[1], &z__[z_offset], ierr);
L50:
    return 0;
} /* rs_ */
