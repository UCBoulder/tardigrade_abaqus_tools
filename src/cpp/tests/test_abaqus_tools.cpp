/**
  * \file test_umat.cpp
  *
  * Tests for umat
  */


#define BOOST_TEST_MODULE test_umat
#include <boost/test/included/unit_test.hpp>

#include<vector_tools.h>

#include<abaqus_tools.h>

BOOST_AUTO_TEST_CASE( testColumnToRowMajor ){
    /*!
     * Test column to row major conversion function.
     * Uses c++ vectors and pointers to avoid adding fortran code to project.
     */

    //Fake a Fortran column major array in memory with a c++ row major vector
    std::vector< double > column_major = { 1, 4,
                                           2, 5,
                                           3, 6 };
    double *column_major_pointer = column_major.data();
    const int height = 2;
    const int width = 3;
    std::vector< std::vector< double > > row_major;
    row_major = abaqusTools::columnToRowMajor( column_major_pointer, height, width);
    std::vector< std::vector< double > > answer = { { 1, 2, 3 },
                                                    { 4, 5, 6 } };

    BOOST_CHECK( vectorTools::fuzzyEquals( row_major, answer ) );
}

BOOST_AUTO_TEST_CASE( testRowToColumnMajor ){
    /*!
     * Test row to column major conversion function.
     * Uses c++ vectors and pointers to avoid adding fortran code to project.
     */

    //Test the interface using a c++ vector of vectors
    //Fake a Fortran column major array in memory with a c++ row major vector
    std::vector< double > column_major(6);
    double *column_major_pointer = column_major.data( );
    std::vector< double > expected = { 1, 4,
                                       2, 5,
                                       3, 6 };
    const int height = 2;
    const int width = 3;
    std::vector< std::vector< double > > row_major = { { 1, 2, 3 },
                                                       { 4, 5, 6 } };
    abaqusTools::rowToColumnMajor( column_major_pointer, row_major, height, width );

    BOOST_CHECK( vectorTools::fuzzyEquals( column_major, expected ) );

    //Test the interface using a c++ vector saved in row major order
    //Reset fake Fortran column major array
    column_major = { 0, 0, 0, 0, 0, 0 };
    std::vector< double > row_major_vector = { 1, 2, 3,
                                               4, 5, 6 };
    abaqusTools::rowToColumnMajor( column_major_pointer, row_major_vector, height, width );

    BOOST_CHECK( vectorTools::fuzzyEquals( column_major, expected ) );

    //Test a single row to single column
    //Create a fake Fortran vector in memory with a c++ row major vector
    std::vector< double > fortran_vector(3);
    double *fortran_vector_pointer = fortran_vector.data( );
    std::vector< double > expected_vector = { 1, 2, 3 };
    std::vector< double > cpp_vector = { 1, 2, 3 };
    abaqusTools::rowToColumnMajor( fortran_vector_pointer, cpp_vector, 1, 3 );

    BOOST_CHECK( vectorTools::fuzzyEquals( fortran_vector, expected_vector ) );
}

BOOST_AUTO_TEST_CASE( testExpandAbaqusNTENSVector ){
    /*!
     * Test expansion of stress and strain type components to full Abaqus vectors
     */

     //Initialize common test variables
     int NDI;
     int NSHR;
     std::vector< double > vector_expansion(6, -666.);

     //Test full size vector
     std::vector< double > abaqus_full = { 11, 22, 33, 12, 13, 23 };
     std::vector< double > expected_full = { 11, 22, 33, 12, 13, 23 };
     NDI = 3;
     NSHR = 3;

     vector_expansion = abaqusTools::expandAbaqusNTENSVector( abaqus_full, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( vector_expansion, expected_full ) );

     //Test plane stress vector
     std::fill(vector_expansion.begin(), vector_expansion.end(), -666.);
     std::vector< double > abaqus_plane_stress = { 11, 22, 12 };
     std::vector< double > expected_plane_stress = { 11, 22, 0., 12, 0., 0. };
     NDI = 2;
     NSHR = 1;

     vector_expansion = abaqusTools::expandAbaqusNTENSVector( abaqus_plane_stress, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( vector_expansion, expected_plane_stress ) );
}

BOOST_AUTO_TEST_CASE( testContractAbaqusNTENSVector ){
    /*!
     * Test contraction of stress and strain type components to full Abaqus vectors
     */

     //Initialize common test variables
     int NDI;
     int NSHR;

     //Test full size vector
     std::vector< double > vector_contraction_full(6, -666.);
     std::vector< double > abaqus_full = { 11, 22, 33, 12, 13, 23 };
     std::vector< double > expanded_full = { 11, 22, 33, 12, 13, 23 };
     NDI = 3;
     NSHR = 3;

     vector_contraction_full = abaqusTools::contractAbaqusNTENSVector( expanded_full, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( vector_contraction_full, abaqus_full ) );

     //Test plane stress vector
     std::vector< double > vector_contraction_plane_stress(3, -666.);
     std::vector< double > abaqus_plane_stress = { 11, 22, 12 };
     std::vector< double > expanded_plane_stress = { 11, 22, 0., 12, 0., 0. };
     NDI = 2;
     NSHR = 1;

     vector_contraction_plane_stress = abaqusTools::contractAbaqusNTENSVector( expanded_plane_stress, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( vector_contraction_plane_stress, abaqus_plane_stress ) );

}

BOOST_AUTO_TEST_CASE( testContractAbaqusNTENSMatrix ){
    /*!
     * Test contraction of NTENS matrix components from full Abaqus matrices of size 6x6
     */

     //Initialize common test variables
     int NDI;
     int NSHR;

     //Test full size matrix
     std::vector< std::vector< double > > matrix_contraction_full( 6, std::vector< double >( 6, -666. ) );
     std::vector< std::vector< double > > abaqus_full   = { { 1111, 1122, 1133, 1112, 1113, 1123 },
                                                            { 2211, 2222, 2233, 2212, 2213, 2223 },
                                                            { 3311, 3322, 3333, 3312, 3313, 3323 },
                                                            { 1211, 1222, 1233, 1212, 1213, 1223 },
                                                            { 1311, 1322, 1333, 1312, 1313, 1323 },
                                                            { 2311, 2322, 2333, 2312, 2313, 2323 } };
     std::vector< std::vector< double > > expanded_full = { { 1111, 1122, 1133, 1112, 1113, 1123 },
                                                            { 2211, 2222, 2233, 2212, 2213, 2223 },
                                                            { 3311, 3322, 3333, 3312, 3313, 3323 },
                                                            { 1211, 1222, 1233, 1212, 1213, 1223 },
                                                            { 1311, 1322, 1333, 1312, 1313, 1323 },
                                                            { 2311, 2322, 2333, 2312, 2313, 2323 } };
     NDI = 3;
     NSHR = 3;

     matrix_contraction_full = abaqusTools::contractAbaqusNTENSMatrix( expanded_full, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( matrix_contraction_full, abaqus_full ) );

     //Test plane stress matrix
     std::vector< std::vector< double > > matrix_contraction_plane_stress( 3, std::vector< double >( 3, -666. ) );
     std::vector< std::vector< double > > abaqus_plane_stress   = { { 1111, 1122, 1112 },
                                                                    { 2211, 2222, 2212 },
                                                                    { 1211, 1222, 1212 } };
     std::vector< std::vector< double > > expanded_plane_stress = { { 1111, 1122, 0.00, 1112, 0.00, 0.00 },
                                                                    { 2211, 2222, 0.00, 2212, 0.00, 0.00 },
                                                                    { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 },
                                                                    { 1211, 1222, 0.00, 1212, 0.00, 0.00 },
                                                                    { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 },
                                                                    { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 } };
     NDI = 2;
     NSHR = 1;

     matrix_contraction_plane_stress = abaqusTools::contractAbaqusNTENSMatrix( expanded_plane_stress, NDI, NSHR );

     BOOST_CHECK( vectorTools::fuzzyEquals( matrix_contraction_plane_stress, abaqus_plane_stress ) );

}

BOOST_AUTO_TEST_CASE( testExpandFullNTENSTensor ){
    /*!
     * Test expansion of full stress and strain type tensors from full Abaqus vectors
     */

     //Initialize common test variables
     std::vector< int > result( 9 );
     std::vector< int > abaqus_standard = { 11, 22, 33, 12, 13, 23 };
     std::vector< int > abaqus_explicit = { 11, 22, 33, 12, 23, 13 };
     std::vector< int > expected = { 11, 12, 13,
                                     12, 22, 23,
                                     13, 23, 33 };

     //Check full tensor expansion for Abaqus/Standard
     result = abaqusTools::expandFullNTENSTensor( abaqus_standard, true );
     BOOST_CHECK( result == expected );

     //Check full tensor expansion for Abaqus/Explicit
     result = abaqusTools::expandFullNTENSTensor( abaqus_explicit, false );
     BOOST_CHECK( result == expected );

     //Test overloaded variation with contracted vector input
     //Check full tensor expansion for Abaqus/Standard
     result = abaqusTools::expandFullNTENSTensor( abaqus_standard, 3, 3, true );
     BOOST_CHECK( result == expected );

     //Check full tensor expansion for Abaqus/Explicit
     result = abaqusTools::expandFullNTENSTensor( abaqus_explicit, 3, 3, false );
     BOOST_CHECK( result == expected );

}

BOOST_AUTO_TEST_CASE( testContractFullNTENSTensor ){

     //Initialize common test variables
     std::vector< int > result( 6 );
     std::vector< int > full_tensor = { 11, 12, 13,
                                        12, 22, 23,
                                        13, 23, 33 };
     std::vector< int > abaqus_standard = { 11, 22, 33, 12, 13, 23 };
     std::vector< int > abaqus_explicit = { 11, 22, 33, 12, 23, 13 };

     //Check full tensor contraction for Abaqus/Standard
     result = abaqusTools::contractFullNTENSTensor( full_tensor, true );
     BOOST_CHECK( result == abaqus_standard );

     //Check full tensor contraction for Abaqus/Explicit
     result = abaqusTools::contractFullNTENSTensor( full_tensor, false );
     BOOST_CHECK( result == abaqus_explicit );

     //Test overloaded variation with contracted vector input
     //Check full tensor contraction for Abaqus/Standard
     result = abaqusTools::contractFullNTENSTensor( full_tensor, 3, 3, true );
     BOOST_CHECK( result == abaqus_standard );

     //Check full tensor contraction for Abaqus/Explicit
     result = abaqusTools::contractFullNTENSTensor( full_tensor, 3, 3, false );
     BOOST_CHECK( result == abaqus_explicit );

}

BOOST_AUTO_TEST_CASE( testContractFullNTENSMatrix ){

     //Initialize common test variables
     std::vector< std::vector< int > > result( 6, std::vector< int >( 6 ) );
                                                         // 0     1     2     3     4     5     6     7     8
     std::vector< std::vector< int > > full_matrix = { { 1111, 1112, 1113, 1121, 1122, 1123, 1131, 1132, 1133 },   // 0
                                                       { 1211, 1212, 1213, 1221, 1222, 1223, 1231, 1232, 1233 },   // 1
                                                       { 1311, 1312, 1313, 1321, 1322, 1323, 1331, 1332, 1333 },   // 2
                                                       { 2111, 2112, 2113, 2121, 2122, 2123, 2131, 2132, 2133 },   // 3
                                                       { 2211, 2212, 2213, 2221, 2222, 2223, 2231, 2232, 2233 },   // 4
                                                       { 2311, 2312, 2313, 2321, 2322, 2323, 2331, 2332, 2333 },   // 5
                                                       { 3111, 3112, 3113, 3121, 3122, 3123, 3131, 3132, 3133 },   // 6
                                                       { 3211, 3212, 3213, 3221, 3222, 3223, 3231, 3232, 3233 },   // 7
                                                       { 3311, 3312, 3313, 3321, 3322, 3323, 3331, 3332, 3333 } }; // 8
                                                                        //  0     4     8     1     2     5
     std::vector< std::vector< int > > full_abaqus_standard_matrix = { { 1111, 1122, 1133, 1112, 1113, 1123 },   // 0
                                                                       { 2211, 2222, 2233, 2212, 2213, 2223 },   // 4
                                                                       { 3311, 3322, 3333, 3312, 3313, 3323 },   // 8
                                                                       { 1211, 1222, 1233, 1212, 1213, 1223 },   // 1
                                                                       { 1311, 1322, 1333, 1312, 1313, 1323 },   // 2
                                                                       { 2311, 2322, 2333, 2312, 2313, 2323 } }; // 5

     //Check full matrix contraction for Abaqus/Standard
     result = abaqusTools::contractFullNTENSMatrix( full_matrix );
     BOOST_CHECK( result == full_abaqus_standard_matrix );

     //Test overloaded variation with contracted NTENSxNTENS matrix output
     //Check full matrix contraction for Abaqus/Standard
     //Sign of life test. The tests for NDI and NSHR less than 3 are performed in contractAbaqusNTENSMatrix.
     result = abaqusTools::contractFullNTENSMatrix( full_matrix, 3, 3 );
     BOOST_CHECK( result == full_abaqus_standard_matrix );

}
