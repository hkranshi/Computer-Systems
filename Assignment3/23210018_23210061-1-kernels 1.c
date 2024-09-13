/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "23210018+23210061",              /* Team name */

    "Anshika Saxena",     /* First member full name */
    "anshika.saxena@iitgn.ac.in",  /* First member email address */

    "Mukul Paras Potta",                   /* Second member full name (leave blank if none) */
    "mukul.potta@iitgn.ac.in"                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];

 	
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
	int i, j;
	
    for (i = 0; i < dim; i += 16) 
	for (j = 0; j < dim; j++) {
	int d=dim-1-j;
		dst[RIDX(d, i , dim)] = src[RIDX(i , j, dim)];
		dst[RIDX(d, i+1, dim)] = src[RIDX(i+1, j, dim)];
		dst[RIDX(d, i+2, dim)] = src[RIDX(i+2, j, dim)];
		dst[RIDX(d, i+3, dim)] = src[RIDX(i+3, j, dim)];
		dst[RIDX(d, i+4, dim)] = src[RIDX(i+4, j, dim)];
		dst[RIDX(d, i+5, dim)] = src[RIDX(i+5, j, dim)];
		dst[RIDX(d, i+6, dim)] = src[RIDX(i+6, j, dim)];
		dst[RIDX(d, i+7, dim)] = src[RIDX(i+7, j, dim)];
		dst[RIDX(d, i+8, dim)] = src[RIDX(i+8, j, dim)];
		dst[RIDX(d, i+9, dim)] = src[RIDX(i+9, j, dim)];
		dst[RIDX(d, i+10, dim)] = src[RIDX(i+10, j, dim)];
		dst[RIDX(d, i+11, dim)] = src[RIDX(i+11, j, dim)];
		dst[RIDX(d, i+12, dim)] = src[RIDX(i+12, j, dim)];
		dst[RIDX(d, i+13, dim)] = src[RIDX(i+13, j, dim)];
		dst[RIDX(d, i+14, dim)] = src[RIDX(i+14, j, dim)];
		dst[RIDX(d, i+15, dim)] = src[RIDX(i+15, j, dim)];
	}
    

 

}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

typedef struct {
    int red;
    int green;
    int blue;
} my_pixel_sum;

my_pixel_sum zero = {0, 0, 0};

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_space_reuse_descr[] = "smooth_space_reuse: Store only the rows and columns needed";
void smooth_space_reuse(int dim, pixel *src, pixel *dst) 
{
   int i, j;
	
#define steps 16
	unsigned int tmp[(steps + 2) * 3 + 3];
	register unsigned int sumr, sumg, sumb;
	int k;

    for (i = 0; i < dim; i += steps) {
		for (k = 0; k < steps + 2; ++k) {
			tmp[k * 3 + 0] = src[RIDX(i + k, 0, dim)].red + src[RIDX(i + k, 1, dim)].red + src[RIDX(i + k, 2, dim)].red;
			tmp[k * 3 + 1] = src[RIDX(i + k, 0, dim)].green + src[RIDX(i + k, 1, dim)].green + src[RIDX(i + k, 2, dim)].green;
			tmp[k * 3 + 2] = src[RIDX(i + k, 0, dim)].blue + src[RIDX(i + k, 1, dim)].blue + src[RIDX(i + k, 2, dim)].blue;
		}
		for (j = 1; j < dim; ++j) {
			sumr = tmp[0 * 3 + 0] + tmp[1 * 3 + 0] + tmp[2 * 3 + 0];
			sumg = tmp[0 * 3 + 1] + tmp[1 * 3 + 1] + tmp[2 * 3 + 1];
			sumb = tmp[0 * 3 + 2] + tmp[1 * 3 + 2] + tmp[2 * 3 + 2];
			for (k = 0; k < steps; ++k) if (i + k + 1 < dim) {
				dst[RIDX(i + k + 1, j, dim)].red = sumr / 9;
				sumr += tmp[(k + 3) * 3 + 0] - tmp[k * 3 + 0];
				dst[RIDX(i + k + 1, j, dim)].green = sumg / 9;
				sumg += tmp[(k + 3) * 3 + 1] - tmp[k * 3 + 1];
				dst[RIDX(i + k + 1, j, dim)].blue = sumb / 9;
				sumb += tmp[(k + 3) * 3 + 2] - tmp[k * 3 + 2];
			}
			for (k = 0; k < steps + 2; ++k) {
				tmp[k * 3 + 0] += src[RIDX(i + k, j + 2, dim)].red - src[RIDX(i + k, j - 1, dim)].red;
				tmp[k * 3 + 1] += src[RIDX(i + k, j + 2, dim)].green - src[RIDX(i + k, j - 1, dim)].green;
				tmp[k * 3 + 2] += src[RIDX(i + k, j + 2, dim)].blue - src[RIDX(i + k, j - 1, dim)].blue;
			}
		}
	}
	for (i = 0; i < dim; ++i) {
		dst[RIDX(i, 0, dim)] = avg(dim, i, 0, src);
		dst[RIDX(0, i, dim)] = avg(dim, 0, i, src);
		dst[RIDX(i, dim - 1, dim)] = avg(dim, i, dim - 1, src);
		dst[RIDX(dim - 1, i, dim)] = avg(dim, dim - 1, i, src);
	}
	

}

char smooth_full_precalc_descr[] = "smooth_full_precalc: Calculates averages from 2D running sums";
void smooth_full_precalc(int dim, pixel *src, pixel *dest) 
{
    int di, dij, di1j, di_1j, dij_1;
    int dim2 = dim * dim;
    my_pixel_sum p11 = zero, p12 = zero, p21 = zero, p22 = zero;
    my_pixel_sum temp2[dim2];

    for (int i=0; i<dim; i++) {
        temp2[i].red = src[i].red;
        temp2[i].green = src[i].green;
        temp2[i].blue = src[i].blue; 
    }
  
   // Do column wise sum 
   for (int i=1; i<dim; i++) {
        dij = di = dim * i;
        di1j = dij + dim;
      for (; dij < di1j; dij++) {
        di_1j = dij - dim;
        temp2[dij].red = src[dij].red + temp2[di_1j].red;
        temp2[dij].green = src[dij].green + temp2[di_1j].green;
        temp2[dij].blue = src[dij].blue + temp2[di_1j].blue; 
      }
    } 
  
   // Do row wise sum 
   for (int i=0; i<dim; i++) {
        dij = di = dim * i;
        dij ++;
      for (; dij - di < dim; dij++) {
        dij_1 = dij - 1;
        temp2[dij].red += temp2[dij_1].red;
        temp2[dij].green += temp2[dij_1].green;
        temp2[dij].blue += temp2[dij_1].blue; 
      }
    }
    // Top Left Corner
    int t1 = 0, t2 = dim+1, t3, t4;
    dest[t1].red = temp2[t2].red >> 2;
    dest[t1].green = temp2[t2].green >> 2;
    dest[t1].blue = temp2[t2].blue >> 2;
    t1 ++; t2 ++;
    // (0, 1) --> First pixel in top edge
    dest[t1].red = temp2[t2].red / 6;
    dest[t1].green = temp2[t2].green / 6;
    dest[t1].blue = temp2[t2].blue / 6;
    t1 += (dim - 1); t2 ++;
    // remainder of Top Edge
    for(int i = 2; i < dim - 1; i ++, t1 ++, t2 ++) {
        dest[i].red = (temp2[t2].red - temp2[t1].red) / 6;
        dest[i].green = (temp2[t2].green - temp2[t1].green) / 6;
        dest[i].blue = (temp2[t2].blue - temp2[t1].blue) / 6;
    }
    // (1, 1) --> First pixel with 8 other surrounding pixels
    dest[dim+1].red = temp2[(dim+1) << 1].red / 9;
    dest[dim+1].green = temp2[(dim+1) << 1].green / 9;
    dest[dim+1].blue = temp2[(dim+1) << 1].blue / 9;
    // Row below Top Edge, first row to have 8 other surrounding pixels
    for(int i = dim + 2; i < (dim << 1) - 1; i ++) {
        dest[i].red = (temp2[i+1+dim].red - temp2[i-2+dim].red) / 9;
        dest[i].green = (temp2[i+1+dim].green - temp2[i-2+dim].green) / 9;
        dest[i].blue = (temp2[i+1+dim].blue - temp2[i-2+dim].blue) / 9;
    }

    // Top Right Corner
    t1 = dim - 1; t2 = t1 + dim; t3 = t2 - 2;
    dest[t1].red = (temp2[t2].red - temp2[t3].red) >> 2;
    dest[t1].green = (temp2[t2].green - temp2[t3].green) >> 2;
    dest[t1].blue = (temp2[t2].blue - temp2[t3].blue) >> 2;
    t1 += dim; t2 += dim; t3 += dim;
    // (1, dim - 1) --> First pixel in Right Edge
    dest[t1].red = (temp2[t2].red - temp2[t3].red) / 6;
    dest[t1].green = (temp2[t2].green - temp2[t3].green) / 6;
    dest[t1].blue = (temp2[t2].blue - temp2[t3].blue) / 6;
    t3 = t1 - dim; t4 = t3 - 2; t1 += (dim << 1); t2 += (dim - 2);
    // remainder of Right Edge
    for(int i = 3 * dim - 1;t1 < dim2; i += dim, t1 += dim, t2 += dim, t3 += dim, t4 +=dim) {
        dest[i].red = (temp2[t1].red - temp2[t2].red - temp2[t3].red + temp2[t4].red) / 6;
        dest[i].green = (temp2[t1].green - temp2[t2].green - temp2[t3].green + temp2[t4].green) / 6;
        dest[i].blue = (temp2[t1].blue - temp2[t2].blue - temp2[t3].blue + temp2[t4].blue) / 6;
    }
    // Bottom Left Corner
    t1 = dim2 - dim; t2 = t1 + 1; t3 = t2 - (dim << 1);
    dest[t1].red = (temp2[t2].red - temp2[t3].red) >> 2;
    dest[t1].green = (temp2[t2].green - temp2[t3].green) >> 2;
    dest[t1].blue = (temp2[t2].blue - temp2[t3].blue) >> 2;
    t3 -= dim;
    // Left Edge
    for(int i = t1 - dim; t3 > 0; i -= dim, t2 -= dim, t3 -= dim) {
        dest[i].red = (temp2[t2].red - temp2[t3].red) / 6;
        dest[i].green = (temp2[t2].green - temp2[t3].green) / 6;
        dest[i].blue = (temp2[t2].blue - temp2[t3].blue) / 6;
    }
    // First Column to have 8 other surrounding pixels
    for(int i = (dim << 1) + 1; i < dim2 - dim; i += dim) {
        dest[i].red = (temp2[i+1+dim].red - temp2[i+1-(dim<<1)].red) / 9;
        dest[i].green = (temp2[i+1+dim].green - temp2[i+1-(dim<<1)].green) / 9;
        dest[i].blue = (temp2[i+1+dim].blue - temp2[i+1-(dim<<1)].blue) / 9;
    }
    // (1, 0) --> First pixel in Left Edge
    dest[dim].red = temp2[t2].red / 6;
    dest[dim].green = temp2[t2].green / 6;
    dest[dim].blue = temp2[t2].blue / 6;

    // Bottom Right Corner
    t1 = t1 + dim - 1; t2 = t1 - 2; t4 = t2 - (dim << 1); t3 = t4 + 2;
    dest[t1].red = (temp2[t1].red - temp2[t2].red - temp2[t3].red + temp2[t4].red) >> 2;
    dest[t1].green = (temp2[t1].green - temp2[t2].green - temp2[t3].green + temp2[t4].green) >> 2;
    dest[t1].blue = (temp2[t1].blue - temp2[t2].blue - temp2[t3].blue + temp2[t4].blue) >> 2;
    t2 --; t4 --;
    // Bottom Edge
    for(int i = t1 - 1; i > dim2 - dim + 1; i --,t1 --,t2 --,t3 --,t4 --) {
        dest[i].red = (temp2[t1].red - temp2[t2].red - temp2[t3].red + temp2[t4].red) / 6;
        dest[i].green = (temp2[t1].green - temp2[t2].green - temp2[t3].green + temp2[t4].green) / 6;
        dest[i].blue = (temp2[t1].blue - temp2[t2].blue - temp2[t3].blue + temp2[t4].blue) / 6;
    }
    // (dim-1, 1) --> Leftmost pixel in Bottom Edge
    dest[t1 - 1].red = (temp2[t1].red - temp2[t3].red) / 6;
    dest[t1 - 1].green = (temp2[t1].green - temp2[t3].green) / 6;
    dest[t1 - 1].blue = (temp2[t1].blue - temp2[t3].blue) / 6; 
    
    // Remainder of the image
    int di1j1, di_2j1, di1j_2, di_2j_2;
    for(int i = 2; i < dim - 1; i ++){
        di = dim * i;
        dij = di + 2;
        di1j1 = dij + dim + 1;
        di_2j1 = dij - (dim << 1) + 1;
        di1j_2 = dij + dim - 2;
        di_2j_2 = dij - (dim << 1) - 2;
        for(int j = 2; j < dim - 1; j ++) {
            p11 = temp2[di1j1];
            p21 = temp2[di_2j1];
            p12 = temp2[di1j_2];
            p22 = temp2[di_2j_2];
            dest[dij].red = (unsigned short)((p11.red 
                                            - p21.red 
                                            - p12.red 
                                            + p22.red) / 9);
            dest[dij].green = (unsigned short)((p11.green 
                                            - p21.green 
                                            - p12.green 
                                            + p22.green) / 9);
            dest[dij].blue = (unsigned short)((p11.blue 
                                            - p21.blue 
                                            - p12.blue 
                                            + p22.blue) / 9);
            dij ++; di1j1 ++; di_2j1 ++; di1j_2 ++; di_2j_2 ++;
        }
    }
}


/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
}

*/
/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth_space_reuse, smooth_space_reuse_descr);
	add_smooth_function(&smooth_full_precalc, smooth_full_precalc_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

