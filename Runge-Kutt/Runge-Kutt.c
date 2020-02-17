#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <tgmath.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Point {
    long double x;
    long double y;
    long double y_1;
} Point;

long double set_math_func( Point point , int type ); //input parametr and number of use function
long double set_math_func_sys( Point point , int type , int num ); //input parametr and number of use sys function
long double set_math_real_solution( Point point , int type ); //its test of real solution DD
long double set_math_real_solution_sys( Point point , int type , int num ); ////its test of real solution LODU
void        start_method_line( char *in_file , char *out_file ); //agregate all function to free main() line
void        start_method_sys( char *in_file , char *out_file ); //agregate all function to free main() sys
void        test_method_line( char *in_file , char *out_file ); //testing of my method line
void        test_method_sys( char *in_file , char *out_file ); //testing of my method sys
void        runge_kutt_second_accur( Point *point , int type , long double parm , long double grid ); //iteration of METHOD
void        runge_kutt_forth_accur( Point *point , int type , long double grid ); //iteration of METHOD
void        runge_kutt_second_accur_sys( Point *point , int type , long double parm , long double grid ); //iteration of METHOD
void        runge_kutt_forth_accur_sys( Point *point , int type , long double grid ); //iteration of METHOD

int
main( int argc , char **argv )
{
    if ( argc < 4 ) {
        printf( "!!!INPUT FORMAT!!!\n\n" );
        printf( "arg1 = TYPE OF YOU TASK\n\n");
        printf( "1 - is line DD\n\n" );
        printf( "2 - is sys DD\n\n" );
        printf( "arg2 = INPUT FILE WITH SET FORMAT\n\n");
        printf( "FOR LINE (arg1 = 1)\n/*\n// type\n// method_type\n// parm\n// grid\n// set point x\n// set point y\n// length\n*/\n\n" );
        printf( "FOR SYSTEM (arg1 = 2)\n/*\n// type\n// method_type\n// parm\n// grid\n// set point x\n// set point y\n// set point y_1\n// length\n*/\n\n" );
        printf( "arg3 = OUTPUT FILE WITH SET FORMAT\n\n");
        printf( "!!!INPUT FORMAT!!!\n\n" );
        return 0;
    }
    int select = (int) strtol( argv[1] , NULL , 10 );
    if ( select == 1 ) {
        test_method_line( argv[2] , argv[3] );
    }
    if ( select == 2 ) {
        start_method_sys( argv[2] , argv[3] );
    }
    return 0;
}

long double
set_math_func( Point point , int type )
{
    long double in_x = point.x; //represent types
    long double in_y = point.y; //represent types
    switch( type ) {
        case 1:
        {
            return ( -1 ) * in_y - in_x * in_x; //its only var function
        }
        case 2:
        {
            return 3 - in_y - in_x; //test 1
        }
        case 3:
        {
            return sinl( in_x ) - in_y; //test2
        }
        default:
        {
            break;
        }
    }
    return 0;
}

long double
set_math_real_solution( Point point , int type )
{
    long double in_x = point.x; //represent types
    switch( type ) {
        case 1:
        {
            return (-1) * in_x * in_x + 2 * in_x - 2 + 12 * expl( (-1) * in_x ); //its only var function
        }
        case 2:
        {
            return 4 - in_x - 4 * expl( (-1) * in_x ); //test 1
        }
        case 3:
        {
            return (1.0 / 2) * sinl( in_x ) - (1.0 / 2) * cosl( in_x ) + (21.0 / 2) * expl( (-1) * in_x ); //test2
        }
        default:
        {
            break;
        }
    }
    return 0;
}

/*
// type
// method_type
// parm
// grid
// set point x
// set point y
// length
*/

void
start_method_line( char *in_file , char *out_file )
{
    int type , method_type , count_grid;
    long double parm , grid , SIZE;
    Point point;
    FILE *file = fopen( in_file , "r" ); //read data
    fscanf( file , "%d%d" , &type , &method_type ); //read data
    fscanf( file , "%Lf%d" , &parm , &count_grid ); //read data
    fscanf( file , "%Lf%Lf%Lf" , &(point.x) , &(point.y) , &SIZE ); //read data
    fclose( file ); //read data
    FILE *out = fopen( out_file , "w" ); //write data
    grid = SIZE / count_grid; //step of method
    long double ERROR = -1.0;
    if ( method_type == 1 ) {
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double y = set_math_real_solution( point , type ); //accuracy
            ERROR = fabsl( point.y - y ) > ERROR ? fabsl( point.y - y ) : ERROR; //accuracy
            fprintf( out , "X = %.10Lf , Y = %.10Lf\n" , point.x , point.y ); //print solution
            runge_kutt_second_accur( &point , type , parm , grid ); //METHOD dolve
            point.x += grid; //next iteration
        }
        fprintf( out , "SECOND_ACCURE METHOD MAX ERROR :: %.20Lf\n" , ERROR ); //accuracy
    }
    if ( method_type == 2 ) {
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double y = set_math_real_solution( point , type ); //accuracy
            ERROR = fabsl( point.y - y ) > ERROR ? fabsl( point.y - y ) : ERROR; //accuracy
            fprintf( out , "X = %.10Lf , Y = %.10Lf\n" , point.x , point.y ); //print solution
            runge_kutt_forth_accur( &point , type , grid ); //METHOD dolve
            point.x += grid; //next iteration
        }
        fprintf( out , "FORTH_ACCURE METHOD MAX ERROR :: %.20Lf\n" , ERROR ); //accuracy
    }
    fclose( out ); //write data
}

/*
// type
// set x
// set y
*/

void
test_method_line( char *in_file , char *out_file )
{
    FILE *file = fopen( in_file , "r" );
    int type;
    Point point;
    fscanf( file , "%d%Lf%Lf" , &type , &point.x , &point.y );
    fclose( file );
    FILE *out = fopen( out_file , "w" );
    int count_grid = 10000;
    long double length = 10.0;
    long double grid = length / count_grid;
    Point copy;
    copy.x = point.x;
    copy.y = point.y;
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d __ LENGTH = %.5Lf __ GRID = %.5Lf\n\n" ,
    type , count_grid , length , grid );
    for ( long double parm = 0.1 ; parm < 1.01 ; parm += 0.1 ) {
        fprintf( out , "ALFA = %.2Lf\n" , parm );
        long double ERROR = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double y = set_math_real_solution( point , type ); //accuracy
            ERROR = fabsl( point.y - y ) > ERROR ? fabsl( point.y - y ) : ERROR; //accuracy
            runge_kutt_second_accur( &point , type , parm , grid ); //solution
            point.x += grid; //next iteration
        }
        point.x = copy.x;
        point.y = copy.y;
        fprintf( out , "SECOND_ACCURE METHOD MAX ERROR :: %.30Lf\n" , ERROR ); //accuracy
        fprintf( out , ">________________________________________________________________<\n" );
    }
    fprintf( out , "\n>++++++++++++++++++++++++++++++++++++++++++++++++++++++++<\n\n" );
    fprintf( out , "TYPE = %d __ LENGTH = %.5Lf\n\n" , type , length );
    for ( count_grid = 10 ; count_grid < 100000000 ; count_grid *= 10 ) {
        grid = length / count_grid;
        fprintf( out , "COUNT_GRID = %d __ GRID = %.10Lf\n" , count_grid , grid );
        long double ERROR = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double y = set_math_real_solution( point , type ); //accuracy
            ERROR = fabsl( point.y - y ) > ERROR ? fabsl( point.y - y ) : ERROR; //accuracy
            runge_kutt_forth_accur( &point , type , grid ); //solution
            point.x += grid; //next iteration
        }
        point.x = copy.x;
        point.y = copy.y;
        fprintf( out , "FORTH_ACCURE METHOD MAX ERROR :: %.30Lf\n" , ERROR ); //accuracy
        fprintf( out , ">________________________________________________________________<\n" );
    }
    count_grid = 5;
    length = 2.0;
    long double parm = 0.5;
    grid = length / count_grid;
    fprintf( out , "\nSECOND_ACCURE METHOD\n" );
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d\nLENGTH = %.5Lf __ GRID = %.5Lf __ PARM = %.5Lf\n\n" ,
    type , count_grid , length , grid , parm );
    for ( int i = 0 ; i < count_grid ; i++ ) {
        fprintf( out , "%.10Lf;%.10Lf;%.10Lf\n" , point.x , point.y , set_math_real_solution( point , type ) ); //print solve
        runge_kutt_second_accur( &point , type , parm , grid ); //solution
        point.x += grid; //next iteration
    }
    point.x = copy.x;
    point.y = copy.y;
    count_grid = 5;
    fprintf( out , "\nEND\n\n" );
    fprintf( out , "FORTH_ACCURE METHOD\n" );
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d __ LENGTH = %.5Lf __ GRID = %.5Lf\n\n" ,
    type , count_grid , length , grid );
    for ( int i = 0 ; i < count_grid ; i++ ) {
        fprintf( out , "%.10Lf;%.10Lf;%.10Lf\n" , point.x , point.y , set_math_real_solution( point , type ) ); //print solve
        runge_kutt_forth_accur( &point , type , grid ); //solution
        point.x += grid; //next iteration
    }
    fclose( out );
}

void
runge_kutt_second_accur( Point *point , int type , long double parm , long double grid )
{
    long double cur = 0 , sum = 0; //current memory
    Point cur_p = {}; //save point for use in functions
    cur = set_math_func( *point , type ); //real formula only
    sum += (1 - parm) * cur; //real formula only
    cur_p.x = point->x + grid / ( 2 * parm ); //real formula only
    cur_p.y = point->y + grid / ( 2 * parm ) * cur; //real formula only
    cur = set_math_func( cur_p , type ); //real formula only
    sum += parm * cur; //real formula only
    point->y += grid * sum; //real formula only
}

void
runge_kutt_forth_accur( Point *point , int type , long double grid )
{
    long double K1 , K2 , K3 , K4 , sum; //current memory
    Point cur_p = {}; //save point for use in other functions
    K1 = set_math_func( *point , type ); //real formula only
    cur_p.x = point->x + ( grid / 2 ); //real formula only
    cur_p.y = point->y + ( grid / 2 ) * K1; //real formula only
    K2 = set_math_func( cur_p , type ); //real formula only
    cur_p.y = point->y + ( grid / 2 ) * K2; //real formula only
    K3 = set_math_func( cur_p , type ); //real formula only
    cur_p.x = point->x + grid; //real formula only
    cur_p.y = point->y + grid * K3; //real formula only
    K4 = set_math_func( cur_p , type ); //real formula only
    sum = K1 + 2 * K2 + 2 * K3 + K4; //real formula only
    sum /= 6; //real formula only
    point->y += grid * sum; //real formula only
}

//__________________________________________________________________________________________________

long double
set_math_func_sys( Point point , int type , int num )
{
    long double in_x = point.x; //represent types
    long double in_y = point.y; //represent types
    long double in_y_1 = point.y_1; //represent types
    switch( type ) {
        case 1:
        {
            if ( num == 1 ) {
                return (-2.0) * in_x * in_y * in_y + in_y_1 * in_y_1 - in_x - 1; //its only var function
            } else {
                return 1.0 / in_y_1 / in_y_1 - in_y - in_x / in_y; //its only var function
            }
        }
        case 2:
        {
            if ( num == 1 ) {
                return ( in_y - in_y_1 ) / in_x; //test 1
            } else {
                return ( in_y + in_y_1 ) / in_x; //test 1
            }
        }
        case 3:
        {
            if ( num == 1 ) {
                return in_y_1 - cosl( in_x ); //test2
            } else {
                return in_y + sinl( in_x ); //test2
            }
        }
        case 4:
        {
            if ( num == 1 ) {
                return in_x + in_y; //test3
            } else {
                return in_x - in_y_1; //test3
            }
        }
        default:
        {
            break;
        }
    }
    return 0;
}

long double
set_math_real_solution_sys( Point point , int type , int num )
{
    long double in_x = point.x; //represent types
    switch( type ) {
        case 1:
        {
            if ( num == 1 ) {
                return 0; //its only var function
            } else {
                return 0; //its only var function
            }
        }
        case 2:
        {
            if ( num == 1 ) {
                return in_x * ( cosl( logl( in_x ) ) - sinl( logl( in_x ) ) ); //test1
            } else {
                return in_x * ( cosl( logl( in_x ) ) + sinl( logl( in_x ) ) ); //test1
            }
        }
        case 3:
        {
            if ( num == 1 ) {
                return (-1) * sinl( in_x ); //test2
            } else {
                return 0; //test2
            }
        }
        case 4:
        {
            if ( num == 1 ) {
                return expl( in_x ) - 1 - in_x; //test2
            } else {
                return expl( (-1) * in_x ) - 1 + in_x; //test2
            }
        }
        default:
        {
            break;
        }
    }
    return 0;
}

/*
// type
// method_type
// parm
// grid
// set point x
// set point y
// set point y_1
// length
*/

void
start_method_sys( char *in_file , char *out_file )
{
    int type , method_type , count_grid; //cur memory
    long double parm , grid , SIZE; //cur memory
    Point point; //cur memory
    FILE *file = fopen( in_file , "r" ); //read data
    fscanf( file , "%d%d" , &type , &method_type ); //read data
    fscanf( file , "%Lf%d" , &parm , &count_grid ); //read data
    fscanf( file , "%Lf%Lf%Lf%Lf" , &(point.x) , &(point.y) , &(point.y_1) , &SIZE ); //read data
    fclose( file ); //read data
    FILE *out = fopen( out_file , "w" ); //write data
    grid = SIZE / count_grid; //step of method
    if ( method_type == 1 ) {
        long double ERROR1 = -1.0 , ERROR2 = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double cur = fabsl( set_math_real_solution_sys( point , type , 1 ) - point.y ); //accuracy
            ERROR1 = cur > ERROR1 ? cur : ERROR1; //accuracy
            cur = fabsl( set_math_real_solution_sys( point , type , 2 ) - point.y_1 ); //accuracy
            ERROR2 = cur > ERROR2 ? cur : ERROR2; //accuracy
            fprintf( out , "X = %.10Lf , Y1 = %.10Lf , Y2 = %.10Lf\n" , point.x , point.y , point.y_1 ); //print solution
            runge_kutt_second_accur_sys( &point , type , parm , grid ); //METHOD solve second
            point.x += grid; //next iteration
        }
        fprintf( out , "RUNGE-KUTT SECOND_ACCURE\n" );
        fprintf( out , "ERROR1 = %.10Lf __ ERROR2 = %.10Lf\n" , ERROR1 , ERROR2 );
    }
    if ( method_type == 2 ) {
        long double ERROR1 = -1.0 , ERROR2 = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) { //accuracy
            long double cur = fabsl( set_math_real_solution_sys( point , type , 1 ) - point.y ); //accuracy
            ERROR1 = cur > ERROR1 ? cur : ERROR1; //accuracy
            cur = fabsl( set_math_real_solution_sys( point , type , 2 ) - point.y_1 ); //accuracy
            ERROR2 = cur > ERROR2 ? cur : ERROR2; //accuracy
            fprintf( out , "X = %.10Lf , Y1 = %.10Lf , Y2 = %.10Lf\n" , point.x , point.y , point.y_1 ); //print solution
            runge_kutt_forth_accur_sys( &point , type , grid ); //METHOD solve forth function
            point.x += grid; //next iteration
        }
        fprintf( out , "RUNGE-KUTT FORTH_ACCURE\n" );
        fprintf( out , "ERROR1 = %.10Lf __ ERROR2 = %.10Lf\n" , ERROR1 , ERROR2 );
    }
    fclose( out ); //write data
}

/*
// type
// set x
// set y
// set y_1
*/

void
test_method_sys( char *in_file , char *out_file )
{
    FILE *file = fopen( in_file , "r" );
    int type; //cur memory
    Point point; //cur memory
    fscanf( file , "%d%Lf%Lf%Lf" , &type , &point.x , &point.y , &point.y_1 );
    fclose( file );
    FILE *out = fopen( out_file , "w" );
    int count_grid = 10000; //cur memory
    long double length = 1.0; //cur memory
    long double grid = length / count_grid; //cur memory
    Point copy;
    copy.x = point.x; //save pre sig
    copy.y = point.y; //save pre sig
    copy.y_1 = point.y_1; //save pre sig
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d\nLENGTH = %.5Lf __ GRID = %.5Lf\n\n" ,
    type , count_grid , length , grid );
    for ( long double parm = 0.1 ; parm < 1.01 ; parm += 0.1 ) {
        fprintf( out , "ALFA = %.2Lf\n" , parm );
        long double ERROR1 = -1.0 , ERROR2 = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double cur = fabsl( set_math_real_solution_sys( point , type , 1 ) - point.y ); //accuracy
            ERROR1 = cur > ERROR1 ? cur : ERROR1; //accuracy
            cur = fabsl( set_math_real_solution_sys( point , type , 2 ) - point.y_1 ); //accuracy
            ERROR2 = cur > ERROR2 ? cur : ERROR2; //accuracy
            runge_kutt_second_accur_sys( &point , type , parm , grid ); //METHOD solve second
            point.x += grid; //next iteration
        }
        point.x = copy.x; //save pre sig
        point.y = copy.y; //save pre sig
        point.y_1 = copy.y_1; //save pre sig
        fprintf( out , "SECOND_ACCURE METHOD MAX ERROR\nY1 = %.30Lf;\nY2 = %.30Lf;\n" , ERROR1 , ERROR2 );
        fprintf( out , ">_______________________________________<\n" );
    }
    fprintf( out , "\n>+++++++++++++++++++++++++++++++++++++++<\n\n" );
    fprintf( out , "TYPE = %d __ LENGTH = %.5Lf\n\n" , type , length );
    for ( count_grid = 10 ; count_grid < 100000000 ; count_grid *= 10 ) {
        grid = length / count_grid;
        fprintf( out , "COUNT_GRID = %d __ GRID = %.7Lf\n" , count_grid , grid );
        long double ERROR1 = -1.0 , ERROR2 = -1.0;
        for ( int i = 0 ; i < count_grid ; i++ ) {
            long double cur = fabsl( set_math_real_solution_sys( point , type , 1 ) - point.y ); //accuracy
            ERROR1 = cur > ERROR1 ? cur : ERROR1; //accuracy
            cur = fabsl( set_math_real_solution_sys( point , type , 2 ) - point.y_1 ); //accuracy
            ERROR2 = cur > ERROR2 ? cur : ERROR2; //accuracy
            runge_kutt_forth_accur_sys( &point , type , grid ); //METHOD solve forth function
            point.x += grid; //next iteration
        }
        point.x = copy.x; //save pre sig
        point.y = copy.y; //save pre sig
        point.y_1 = copy.y_1; //save pre sig
        fprintf( out , "FORTH_ACCURE METHOD MAX ERROR\nY1 = %.30Lf;\nY2 = %.30Lf;\n" , ERROR1 , ERROR2 );
        fprintf( out , ">_______________________________________<\n" );
    }
    count_grid = 5;
    length = 2.0;
    long double parm = 0.5;
    grid = length / count_grid;
    fprintf( out , "\nSECOND_ACCURE METHOD\n" );
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d\nLENGTH = %.5Lf __ GRID = %.5Lf __ PARM = %.5Lf\n\n" ,
    type , count_grid , length , grid , parm );
    fprintf( out , "(x , u_m , v_m , u_r , v_r)\n" );
    for ( int i = 0 ; i < count_grid ; i++ ) {
        fprintf( out , "%.10Lf;%.10Lf;%.10Lf;%.10Lf;%.10Lf\n" , point.x , point.y , point.y_1 ,
        set_math_real_solution_sys( point , type , 1 ) , set_math_real_solution_sys( point , type , 2 ) ); //print solve
        runge_kutt_second_accur_sys( &point , type , parm , grid ); //solution
        point.x += grid; //next iteration
    }
    point.x = copy.x; //save pre sig
    point.y = copy.y; //save pre sig
    point.y_1 = copy.y_1; //save pre sig
    count_grid = 5;
    fprintf( out , "\nEND\n\n" );
    fprintf( out , "FORTH_ACCURE METHOD\n" );
    fprintf( out , "TYPE = %d __ COUNT_GRID = %d __ LENGTH = %.5Lf __ GRID = %.5Lf\n\n" ,
    type , count_grid , length , grid );
    fprintf( out , "(x , u_m , v_m , u_r , v_r)\n" );
    for ( int i = 0 ; i < count_grid ; i++ ) {
        fprintf( out , "%.10Lf;%.10Lf;%.10Lf;%.10Lf;%.10Lf\n" , point.x , point.y , point.y_1 ,
        set_math_real_solution_sys( point , type , 1 ) , set_math_real_solution_sys( point , type , 2 ) ); //print solve
        runge_kutt_forth_accur_sys( &point , type , grid ); //solution
        point.x += grid; //next iteration
    }
    fclose( out );
}

void
runge_kutt_second_accur_sys( Point *point , int type , long double parm , long double grid )
{
    long double K1_1 , K2_1; //current memory
    long double K1_2 , K2_2; //current memory
    Point cur_p = {}; //save point for use in other functions
    K1_1 = grid * set_math_func_sys( *point , type , 1 );
    K1_2 = grid * set_math_func_sys( *point , type , 2 );
    cur_p.x = point->x + ( grid / ( 2 * parm ) ); //real formula only
    cur_p.y = point->y + ( K1_1 / ( 2 * parm ) ); //real formula only
    cur_p.y_1 = point->y_1 + ( K1_2 / ( 2 * parm ) ); //real formula only
    K2_1 = grid * set_math_func_sys( cur_p , type , 1 ); //real formula only
    K2_2 = grid * set_math_func_sys( cur_p , type , 2 ); //real formula only
    point->y += ( K1_1 * ( 1 - parm) + K2_1 * parm ); //real formula only
    point->y_1 += ( K1_2 * ( 1 - parm) + K2_2 * parm ); //real formula only
}

void
runge_kutt_forth_accur_sys( Point *point , int type , long double grid )
{
    long double K1_1 , K2_1 , K3_1 , K4_1; //current memory
    long double K1_2 , K2_2 , K3_2 , K4_2; //current memory
    Point cur_p = {}; //save point for use in other functions
    K1_1 = grid * set_math_func_sys( *point , type , 1 ); //real formula only
    K1_2 = grid * set_math_func_sys( *point , type , 2 ); //real formula only
    cur_p.x = point->x + ( grid / 2 ); //real formula only
    cur_p.y = point->y + ( K1_1 / 2 ); //real formula only
    cur_p.y_1 = point->y_1 + ( K1_2 / 2 ); //real formula only
    K2_1 = grid * set_math_func_sys( cur_p , type , 1 ); //real formula only
    K2_2 = grid * set_math_func_sys( cur_p , type , 2 ); //real formula only
    cur_p.y = point->y + ( K2_1 / 2 ); //real formula only
    cur_p.y_1 = point->y_1 + ( K2_2 / 2 ); //real formula only
    K3_1 = grid * set_math_func_sys( cur_p , type , 1 ); //real formula only
    K3_2 = grid * set_math_func_sys( cur_p , type , 2 ); //real formula only
    cur_p.x = point->x + grid; //real formula only
    cur_p.y = point->y + K3_1; //real formula only
    cur_p.y_1 = point->y_1 + K3_2; //real formula only
    K4_1 = grid * set_math_func_sys( cur_p , type , 1 ); //real formula only
    K4_2 = grid * set_math_func_sys( cur_p , type , 2 ); //real formula only
    point->y += ( K1_1 + 2 * K2_1 + 2 * K3_1 + K4_1 ) / 6.0; //real formula only
    point->y_1 += ( K1_2 + 2 * K2_2 + 2 * K3_2 + K4_2 ) / 6.0; //real formula only
}
