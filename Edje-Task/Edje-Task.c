#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <tgmath.h>
#include <fcntl.h>
#include <unistd.h>

// test1
// long double s_a_1 = 1.0; //alfa1
// long double s_a_2 = -2.0; //alfa2
// long double s_point_1 = 1.0; //point start fo frst edje
// long double s_sig_1 = 0.6; //sig in start point 1
// long double s_point_2 = 1.3;  //point start fo scnd edje
// long double s_sig_2 = 1; //sig in start point 2
// test2
// long double s_a_1 = 1.0; //alfa1
// long double s_a_2 = 1.0; //alfa2
// long double s_point_1 = 0.5; //point start fo frst edje
// long double s_sig_1 = 1.0; //sig in start point 1
// long double s_point_2 = 1.5;  //point start fo scnd edje
// long double s_sig_2 = 3; //sig in start point 2
// test3
// long double s_a_1 = 1.0; //alfa1
// long double s_a_2 = 1.0; //alfa2
// long double s_point_1 = 1.0; //point start fo frst edje
// long double s_sig_1 = 1.0; //sig in start point 1
// long double s_point_2 = 1.5;  //point start fo scnd edje
// long double s_sig_2 = 4; //sig in start point 2
// test4
long double s_a_1 = -1.0; //alfa1
long double s_a_2 = 1.0; //alfa2
long double s_point_1 = 0; //point start fo frst edje
long double s_sig_1 = 0; //sig in start point 1
long double s_point_2 = 1;  //point start fo scnd edje
long double s_sig_2 = 1; //sig in start point 2

// y''-0.5y'+3y=2x^2, y(1) - 2y'(1) = 0.6, y(1.3) = 1 //test1
// y''+1.5y'-5y=3x-1, y(0.5) + y'(0.5) = 1, y(1.5) = 3 //test2
// y''+1.5y'-5y=3x^3 + 8, y(1) + y'(1) = 1, y(1.5) = 4 //test3


inline long double task_1_real_solv( long double x ); //real solution of DD you can made it
inline long double q( long double x ); //q function its y koef
inline long double p( long double x ); //p function its y' koef
inline long double f( long double x ); //right part of DD
void               task_1( int count_grid ); //solve function

int
main( int argc , char **argv )
{
    if ( argc <= 1 ) { //help
        printf( "!!!README!!!\n" );
        printf( "YOU SHOULD SWAP P , Q , F function\n" );
        printf( "START PARAMETRS LIKE IN COMMENTS\n" );
        printf( "arg1 = count_grid\n" );
        printf( "arg2 = 1 solve , 2 test all\n" );
        printf( "!!!README!!!\n" );
    }
    if ( strtol( argv[2] , NULL , 10 ) == 1 ) {
        int count_grid = (int) strtol( argv[1] , NULL , 10 );
        task_1( count_grid );
    } else {
        for ( int i = 10 ; i < 10000000 ; i *= 10 ) {
            task_1( i );
        }
    }
    return 0;
}

inline long double
task_1_real_solv( long double x )
{
    /*
    return 2.0/3.0 *(x * x + 1.0/3.0 *x + 0.704467 * exp(x / 4) *sin(sqrt(47)*x/4) +
    0.927242*exp(x/4)*cos(sqrt(47)*x/4) -0.611111); //test1
    */
    /*
    return 0.02 + 0.324268 * expl( -3.1085 * x ) + 0.347255 * expl( 1.6085 * x ) - 0.6 * x;
    */
    /*
    return -2.1292 + 33.5105 * expl( -3.1085 * x ) + 0.951122 * expl( 1.6085 * x ) -
    1.044 * x - 0.54 * x * x - 0.6 * x * x * x; //test3
    */
    return expl(x - 1);

}

inline long double
p( long double x )
{
    // return (-1.0) / 2; //test1
    // return 3.0 / 2; //test2
    // return 1.5; //test3
    return -1;
}

inline long double
q( long double x )
{
    // return 3.0; //test1
    // return -5.0; //test2
    // return -5.0; //test3
    return 0;
}

inline long double
f( long double x )
{
    // return 2.0 * x * x; //test1
    // return 3.0 * x - 1;
    // return 3.0 * x * x * x + 8.0; //test3
    return 0;
}

void
task_1( int count_grid )
{
    long double A , B , C , D; //cur memory
    long double B_0 , C_0 , D_0; //cur memory
    long double A_F , B_F , C_F , D_F; //cur memory
    long double a = s_point_1 , b = s_point_2; //cur memory and set sig
    long double grid = ( b - a ) / count_grid; //cur memory and set sig
    long double x = a - grid / 2.0; //cur memory and set sig
    //_______________________________________
    long double *alfa = calloc( count_grid + 1 , sizeof( *alfa ) ); //get memory
    long double *beta = calloc( count_grid + 1 , sizeof( *beta ) ); //get memory
    long double *solv = calloc( count_grid + 1 , sizeof( *solv ) ); //get memory
    //_______________________________________
    B_0 = ( ( s_a_1 / 2.0 ) + ( s_a_2 / grid ) ); //set sig
    C_0 = ( ( s_a_1 / 2.0 ) - ( s_a_2 / grid ) ); //set sig
    D_0 = s_sig_1; //set sig
    alfa[0] = (-1) * B_0 / C_0; //write koef
    beta[0] = D_0 / C_0; //write koef
    //_______________________________________
    for ( int i = 1 ; i < count_grid ; i++ ) { //calc koef
        x += grid; //next iteration
        A = 1.0 / ( grid * grid ) - p( x ) / ( 2.0 * grid ); //set sig
        B = 1.0 / ( grid * grid ) + p( x ) / ( 2.0 * grid ); //set sig
        C = q( x ) - 2.0 / ( grid * grid ); //set sig
        D = f( x ); //set sig
        alfa[i] = (-1) * B / ( A * alfa[i - 1] + C ); //write koef
        beta[i] = ( D - A * beta[i - 1] ) / ( A * alfa[i - 1] + C ); //write koef
    }
    //_______________________________________
    x += grid; //next iteration
    A_F = 1.0 / ( grid * grid ) - p( x ) / grid; //set sig
    B_F = 2.0 / ( grid * grid ); //set sig
    C_F = p( x ) / grid + q( x ) - 3.0 / ( grid * grid ); //set sig
    D_F = f( x ); //set sig
    alfa[count_grid] = (-1) * B_F / ( A_F * alfa[count_grid - 1] + C_F ); //write koef
    beta[count_grid] = ( D_F - A_F * beta[count_grid - 1] ) / ( A_F * alfa[count_grid - 1] + C_F ); //write koef
    solv[count_grid] = s_sig_2; //write solve
    //_______________________________________
    for ( int i = count_grid - 1 ; i >= 0 ; i-- ) {
        solv[i] = alfa[i + 1] * solv[i + 1] + beta[i + 1]; //write solve
    }
    //_______________________________________
    printf( "%.10Lf;%.10Lf;%.10Lf\n" , x + ( grid / 2 ) , solv[count_grid] ,
    task_1_real_solv( x + ( grid / 2 ) ) );  //print info
    long double ERROR = -1.0; //cur memory
    for ( int i = count_grid - 1 ; i >= 0 ; i-- ) { //write all information
        long double cur = fabsl( solv[i] - task_1_real_solv( x ) );
        ERROR = cur > ERROR ? cur : ERROR;
        printf( "%.10Lf;%.10Lf;%.10Lf\n" , x , solv[i] , task_1_real_solv( x ) ); //print info
        x -= grid; //pre iteration
    }
    // printf( "COUNT_GRID :: %d\nGRID :: %.8Lf\nMAX ERROR :: %.20Lf\n" , count_grid , grid , ERROR ); //print info
    //_______________________________________
    free( alfa ); //free memory
    free( beta ); //free memory
    free( solv ); //free memory
}
