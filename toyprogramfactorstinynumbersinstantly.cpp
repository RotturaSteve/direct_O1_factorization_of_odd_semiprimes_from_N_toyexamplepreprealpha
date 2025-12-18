//DOES NOT WORK //  ---------------- hiddeous toy program but its purpose is just to show the idea which works on tiny test cases & should scale


/// DOES NOT WORK, INCLUDED HERE TO STORE FORMULA I'M LOOKING AT /////

// JUST TO EXPRESS THE FORMULA I INVENTED
////////// INFERS a solution to PI is a solution to factoring is a solution for compressing uncompressible data maybe too.

// PROGRAM: prove direct SOME NUMBERS HAVE factoring ~O(1) formula works for very small numbers and this imho says it scales to any sized number with mpfr ;
// BASED ON: The Rottura Algorithms, #3, Theorem: all odd composites are hollow squares -> factoring by ((2 * Q) - 1) per geometry
// FORMULA: [ (2*sqrt(N/PI))+sqrt(Z^2-N) ] is a factor case bifurcated true for either rounding up or down to integer of [2*sqrt(N/PI)] portion.
// PRE-PRE-ALPHA: tested with 51,95,187,2059 and works with those, chosen because their geometries are radically difference and 52's unbalanced;
// WARNINGS: not even a pre-alpha, just tested a few numbers so far;
//
//          literally [     fac2_P=(Z=ceil(sqrtl(N/PI))*2) + (L = k = sqrt(Z^2-N))   
//              OR    [     fac2_P=(Z=floor(sqrtl(N/PI))*2) + (L = k = sqrt(Z^2-N))  
//          IS the factor, provided N target is composite of odds... BUT requires mpfr precision for numbers of any interest.
//          detectible without type-cast issues by q= FLOOR(Z-L+1/2); ? (q*q)+(2.0*(q-1.0)*q)+((q-1.0)*(q-1.0))+(2.0*(L*q)) + (2.0*(L*(q-1))) == N ;;
//

//     printf("This example only works for small numbers due to precision, using mpfr will give it the precision to do 'any' number composite of semiprimes\n");
//     printf("I haven't corrected it to stop false-positives, if your number is too big it starts to say it worked when it didn't, and numbers have to be tiny\n");
//     printf("However, there's no reason to believe this won't scale up to huge N with mpfr, etc.\n");


//
// O(1) factor :=: [ (Z=CEIL(sqrt(N/PI))*2)+(L=k=sqrt((Z^2)-N)) OR (Z=FLOOR(sqrt(N/PI))*2)+(L=k=sqrt((Z^2)-N)) @ q= FLOOR(Z-L+1/2); on odd hollow square q^2+2q(q-1)+(q-1)(q-1)+2Lq+2L(q-1) ;
//  but requires total floating point precision beyond the type used; note L can be derived from q alone as: [ L = ((N/4.0) - (q*q) + q - 0.25 ) / (q-.5) ]
// 
// in short [ (2*sqrt(N/PI))+sqrt(Z^2-N) ] is a factor case bifurcated true for either rounding up or down to integer of [2*sqrt(N/PI)] portion.
//
// ((fac-sqrt(Z^2-N))/2)^2 = N/PI leads to solution for PI to the digits-of-N-precision.
//
//  COMPRESSION: being able factor by data regions+(region-1) treated as composites leads to only storing least two of L,q,k and control bits.
//
//


#include <stdio.h>
#include <inttypes.h>
#include <math.h>
int main(int argc,char*argv[])
{
    printf("WARN: This example only works for small numbers due to precision, using mpfr will give it the precision to do 'any' number composite of semiprimes\n");
    printf("\n");
    printf("O(1) factor :=: [ (Z=CEIL(sqrt(N/PI))*2)+(L=k=sqrt((Z^2)-N)) OR (Z=FLOOR(sqrt(N/PI))*2)+(L=k=sqrt((Z^2)-N)) @ q= FLOOR(Z-L+1/2); \n");
    printf("                on odd hollow square [ q^2+2q(q-1)+(q-1)(q-1)+2Lq+2L(q-1) ] @ [ L == ((N/4.0) - (q*q) + q - 0.25 ) / (q-.5) ]\n");
    printf("                The form is { [ (2*sqrt(N/PI))+sqrt(Z^2-N) ] } with [2*sqrt(N/PI)] portion to either ceiling or floor.\n");
    printf("PI solution :=: ((fac-sqrt(Z^2-N))/2)^2 = N/PI leads to solution for PI to the digits of N digits-~.\n");
    printf("\n");
    
    long double N,Z,n1,n2,L,k,q,NN,fac1_P,fac1_Q,fac2_P,fac2_Q,NN_1,NN_2,qq1,qq2;
    N=187.0;
    
    if (argc>=2) { sscanf(argv[1],"%Lf",&N); if (log10(N)+1>5) { printf("Target too big for demo\n");exit(1);} printf("Target N = %.17Lf (%s)\n",N,argv[1]); }    
    
    fac2_P=(Z=ceill(sqrtl(N/M_PIl))*(long double)2.0) + (L = k = sqrtl((Z*Z)-N)) ;
    fac2_Q=(Z-k);
    q = floorl(((Z-L)+1.0)/2.0);
    NN_2 = (q*q)+(2.0*(q-1.0)*q)+((q-1.0)*(q-1.0))+(2.0*(L*q)) + (2.0*(L*(q-1))); // fyi, & avoids floating comparator bugs in gcc ;;
    
    fac1_P=(Z=floorl(sqrtl(N/M_PIl))*(long double)2.0) + (L = k = sqrtl((Z*Z)-N));
    fac1_Q=(Z-k);
    q = floorl(((Z-L)+1.0)/2.0);
    NN_1 = (q*q)+(2.0*(q-1.0)*q)+((q-1.0)*(q-1.0))+(2.0*(L*q)) + (2.0*(L*(q-1))); // fyi, & avoids floating comparator bugs in gcc ;;
    
    if (NN_1==N)//if ((__uint128_t)fabsl(fac1_P)*(__uint128_t)fabsl(fac1_Q) == (__uint128_t)N) // gcc comparators doubles to equal even on fabsl wrong so we used typecase to int-type
    { 
        Z=floorl(sqrtl(N/M_PIl))*(long double)2.0; 
        L = k = sqrtl((Z*Z)-N);                
        q = ((Z-L)+1.0)/2.0;        
        NN = (q*q)+(2.0*(q-1.0)*q)+((q-1.0)*(q-1.0))+(2.0*(L*q)) + (2.0*(L*(q-1))); // just an fyi

        printf("FACTORED BY FLOOR: %.17Lf * %.17Lf = %.0Lf (ceiling fractional, q==%.0Lf, L==%.0Lf)\n",   fac1_P,fac1_Q , N,q,L); 
    }
    else 
    { 
        if (NN_2==N)//if ((__uint128_t)fabsl(fac2_P)*(__uint128_t)fabsl(fac2_Q) == (__uint128_t)N) 
        {
            Z=ceill(sqrtl(N/M_PIl))*(long double)2.0;
            L = k = sqrtl((Z*Z)-N);
            q = ((Z-L)+1)/2.0;                    
            NN = (q*q)+(2.0*(q-1.0)*q)+((q-1.0)*(q-1.0))+(2.0*(L*q)) + (2.0*(L*(q-1))); // just an fyi
            
            printf("FACTORED BY CEILING: %.0Lf * %.0Lf == %.0Lf (floor fractional, q==%.0Lf, L==%.0Lf)\n",   fac2_P,fac2_Q , N,q,L); 
        }
        else
        {
            printf("Number %Lf may exceed precision of demo OR not have had odd factors\n",N);            
        }        
    }
    
printf("\n");

exit(1);    


} // () main

