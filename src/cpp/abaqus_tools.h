/**
  ******************************************************************************
  * \file umat.h
  ******************************************************************************
  * The declarations and definitions required for an Abaqus UMAT c++ interface.
  ******************************************************************************
  */

#ifndef ABAQUS_TOOLS_H
#define ABAQUS_TOOLS_H

#include<iostream>
#include<vector>
#include<string.h>
#include<stdio.h>

namespace abaqusTools{

    template< typename T >
    std::vector< std::vector< T > > columnToRowMajor( const T *column_major,  const int &height, const int &width ){
        /*!
         * Convert column major two dimensional arrays to row major.
         *
         * Specifically, convert pointers to Fortran column major arrays to c++ row major vector of vectors.
         *
         * \param *column_major: The pointer to the start of a column major array
         * \param &height: The height of the array, e.g. number of rows
         * \param &width: The width of the array, e.g. number of columns
         * \return row_major: A c++ row major vector of vectors
         */
        std::vector< std::vector< T > > row_major;
        int column_major_index;
        for ( int row = 0; row < height; row++ ){
            std::vector< T > row_vector;
            for ( int col = 0; col < width; col++ ){
                column_major_index = col*height + row;
                row_vector.push_back( *( column_major + column_major_index ) );
            }
            row_major.push_back( row_vector );
        }
        return row_major;
    }
    
    template< typename T >
    void rowToColumnMajor( T *column_major, const std::vector< std::vector< T > > &row_major_array,
                           const int &height, const int &width ){
        /*!
         * Convert row major two dimensional arrays to column major
         *
         * Specifically, c++ row major vector of vectors or arrays to Fortran column major arrays using the column major
         * pointer.
         *
         * \param *column_major: The pointer to the start of a column major array
         * \param &row_major_array: A c++ two dimensional, row major vector of vectors
         * \param &height: The height of the array, e.g. number of rows
         * \param &width: The width of the array, e.g. number of columns
         */
        int column_major_index;
        for ( int row = 0; row < height; row++ ){
            for ( int col = 0; col < width; col++ ){
                column_major_index = col*height + row;
                column_major[column_major_index] = row_major_array[row][col];
            }
        }
    
        return;
    }
    
    template< typename T >
    void rowToColumnMajor( T *column_major, const std::vector< T > &row_major, const int &height, const int &width ){
        /*!
         * Convert row major two dimensional arrays stored as vector to column major array
         *
         * Specifically, c++ row major vector to Fortran column major arrays using the column major pointer.
         *
         * \param *column_major: The pointer to the start of a column major array
         * \param &row_major_array: A c++ two dimensional array stored as row major vector
         * \param &height: The height of the array, e.g. number of rows. The c++ row count (1) for 1D arrays.
         * \param &width: The width of the array, e.g. number of columns. The c++ column count (size) for 1D arrays.
         */
        int row_major_index;
        int column_major_index;
        for ( int row = 0; row < height; row++ ){
            for ( int col = 0; col < width; col++ ){
                row_major_index = row*width + col;
                column_major_index = col*height + row;
                column_major[column_major_index] = row_major[row_major_index];
            }
        }
    }
    
    template< typename T >
    std::vector< T > expandAbaqusNTENSVector( const std::vector< T > &abaqus_vector,
                                              const int &NDI, const int &NSHR ){
        /*!
         * Expand stress and strain type components to full Abaqus vectors.
         *
         * See the Abaqus documentation > Introduction & Spatial Modeling > Conventions chapter > Convention used for stress
         * and strain components.
         *
         * The stress vector components for Abaqus/Standard (UMAT) are
         *
         * \f$ \left ( \sigma_{11}, \sigma_{22}, \sigma_{33}, \tau_{12}, \tau_{13}, \tau_{23} \right ) \f$
         *
         * and the strain vector components match as
         *
         * \f$ \left ( \epsilon_{11}, \epsilon_{22}, \epsilon_{33}, \gamma_{12}, \gamma_{13}, \gamma_{23} \right ) \f$
         *
         * The stress vector components for Abaqus/Explicit (VUMAT) are
         *
         * \f$ \left ( \sigma_{11}, \sigma_{22}, \sigma_{33}, \tau_{12}, \tau_{23}, \tau_{13} \right ) \f$
         *
         * and the strain vector components match as
         *
         * \f$ \left ( \epsilon_{11}, \epsilon_{22}, \epsilon_{33}, \gamma_{12}, \gamma_{23}, \gamma_{13} \right ) \f$
         *
         * where components that are zero-valued by definition, e.g. plane stress, are omitted. The shear strain is the
         * engineering shear strain where
         *
         * \f$ \gamma_{ij} = \epsilon_{ij} + \epsilon_{ji} \f$
         *
         * for both Abaqus/Standard and Abaqus/Explicit.
         *
         * \param &abaqus_vector: an abaqus stress-type vector with no by-definition-zero components. Length NDI + NSHR.
         * \param &NDI: The number of direct components.
         * \param &NSHR: The number of shear components.
         * \returns vector_expansion: c++ type vector of length 6.
         */
    
        //Initialize expanded vector to the appropriate dimensions with zero values
        std::vector< T > vector_expansion( 6, 0 );
    
        //Unpack direct components of Abaqus/Standard stress-type vector
        for ( int index = 0; index < NDI; index++ ){
            vector_expansion[ index ] = abaqus_vector[ index ];
        }
    
        //Unpack shear components of Abaqus/Standard stress-type vector
        for ( int index = 0; index < NSHR; index++ ){
            vector_expansion[ 3 + index ] = abaqus_vector[ NDI + index ];
        }
    
        return vector_expansion;
    }

    template< typename T >
    std::vector< T > contractAbaqusNTENSVector( const std::vector< T > &full_abaqus_vector,
                                                 const int &NDI, const int &NSHR ){
        /*!
         * Contract stress and strain type components from full Abaqus vectors.
         *
         * See the Abaqus documentation > Introduction & Spatial Modeling > Conventions chapter > Convention used for stress
         * and strain components.
         *
         * The stress vector components for Abaqus/Standard (UMAT) are
         *
         * \f$ \left ( \sigma_{11}, \sigma_{22}, \sigma_{33}, \tau_{12}, \tau_{13}, \tau_{23} \right ) \f$
         *
         * and the strain vector components match as
         *
         * \f$ \left ( \epsilon_{11}, \epsilon_{22}, \epsilon_{33}, \gamma_{12}, \gamma_{13}, \gamma_{23} \right ) \f$
         *
         * The stress vector components for Abaqus/Explicit (VUMAT) are
         *
         * \f$ \left ( \sigma_{11}, \sigma_{22}, \sigma_{33}, \tau_{12}, \tau_{23}, \tau_{13} \right ) \f$
         *
         * and the strain vector components match as
         *
         * \f$ \left ( \epsilon_{11}, \epsilon_{22}, \epsilon_{33}, \gamma_{12}, \gamma_{23}, \gamma_{13} \right ) \f$
         *
         * where components that are zero-valued by definition, e.g. plane stress, are omitted. The shear strain is the
         * engineering shear strain where
         *
         * \f$ \gamma_{ij} = \epsilon_{ij} + \epsilon_{ji} \f$
         *
         * for both Abaqus/Standard and Abaqus/Explicit.
         *
         * \param &full_abaqus_vector: a previously expanded abaqus stress-type vector. Length 6.
         * \param &NDI: The number of direct components.
         * \param &NSHR: The number of shear components.
         * \returns vector_contraction: c++ type vector of length NDI + NSHR.
         */
    
        //Initialize contracted vector to the appropriate dimensions
        std::vector< T > vector_contraction( NDI + NSHR );
    
        //Pack non-zero direct components of Abaqus/Standard stress-type vector
        for ( int index = 0; index < NDI; index++ ){
            vector_contraction[ index ] = full_abaqus_vector[ index ];
        }
    
        //Pack non-zero shear components of Abaqus/Standard stress-type vector
        for ( int index = 0; index < NSHR; index++ ){
            vector_contraction[ NDI + index ] = full_abaqus_vector[ 3 + index ];
        }
    
        return vector_contraction;
    }
    
    template< typename T >
    std::vector< std::vector < T > > contractAbaqusStandardNTENSMatrix( const std::vector< std::vector< T > > &full_abaqus_matrix, 
                                                                        const int &NDI, const int &NSHR ){
        /*!
         * Contract NTENS type components from full Abaqus matrixes (6x6).
         *
         * See the Abaqus documentation > Introduction & Spatial Modeling > Conventions chapter > Convention used for stress
         * and strain components.
         *
         * The stress vector components for Abaqus/Standard (UMAT) are
         *
         * \f$ \left ( \sigma_{11}, \sigma_{22}, \sigma_{33}, \tau_{12}, \tau_{13}, \tau_{23} \right ) \f$
         *
         * and the strain vector components match as
         *
         * \f$ \left ( \epsilon_{11}, \epsilon_{22}, \epsilon_{33}, \gamma_{12}, \gamma_{13}, \gamma_{23} \right ) \f$
         *
         * where components that are zero-valued by definition, e.g. plane stress, are omitted. The related matrixes are
         * then
         *
         * TODO: Update LaTeX formatting for a well aligned matrix
         *
         * \f$ \left ( D_{1111}, D_{1122}, D_{1133}, D_{1112}, D_{1113}, D_{1123} \right ) \f$
         * \f$ \left ( D_{symm}, D_{2222}, D_{2233}, D_{2212}, D_{2213}, D_{2223} \right ) \f$
         * \f$ \left ( D_{symm}, D_{symm}, D_{3333}, D_{3312}, D_{3313}, D_{3323} \right ) \f$
         * \f$ \left ( D_{symm}, D_{symm}, D_{symm}, D_{1212}, D_{1213}, D_{1223} \right ) \f$
         * \f$ \left ( D_{symm}, D_{symm}, D_{symm}, D_{symm}, D_{1313}, D_{1323} \right ) \f$
         * \f$ \left ( D_{symm}, D_{symm}, D_{symm}, D_{symm}, D_{symm}, D_{2323} \right ) \f$
         *
         * \param &full_abaqus_matrix: a previously expanded abaqus NTENS matrix. Dimensions 6x6.
         * \param &NDI: The number of direct components.
         * \param &NSHR: The number of shear components.
         * \returns matrix_contraction: c++ type vector of vectors with square shape of size NDI + NSHR.
         */
    
        //Initialize contracted matrix to the appropriate dimensions
        std::vector< std::vector< T > > matrix_contraction( NDI + NSHR, std::vector< T >( NDI + NSHR ) );
    
        //Loop non-zero direct component rows
        for ( int row = 0; row < NDI; row++ ){
            //Loop non-zero direct component columns
            for ( int col = 0; col < NDI; col++ ){
                matrix_contraction[ row ][ col ] = full_abaqus_matrix[ row ][ col ];
            }
            //Loop non-zero shear component columns
            for ( int col = 0; col < NSHR; col++ ){
                matrix_contraction[ row ][ NDI + col ] = full_abaqus_matrix[ row ][ 3 + col ];
            }
        }
    
        //Loop non-zero shear component rows
        for ( int row = 0; row < NSHR; row++ ){
            //Loop non-zero direct component columns
            for ( int col = 0; col < NDI; col++ ){
                matrix_contraction[ NDI + row ][ col ] = full_abaqus_matrix[ 3 + row ][ col ];
            }
            //Loop non-zero shear component columns
            for ( int col = 0; col < NSHR; col++ ){
                matrix_contraction[ NDI + row ][ NDI + col ] = full_abaqus_matrix[ 3 + row ][ 3 + col ];
            }
        }
    
        return matrix_contraction;
    }
    
    char *FtoCString( int stringLength, const char* fString ){
        /*!
         * Converts a Fortran string to C-string. Trims trailing white space during processing.
         *
         * Code excerpt from a c++ Abaqus FILM subroutine in the Abaqus Knowledge Base:
         * https://kb.dsxclient.3ds.com/mashup-ui/page/resultqa?from=search%3fq%3dwriting%2bsubroutine%2bc%252B%252B&id=QA00000008005e&q=writing%20subroutine%20c%2B%2B
         *
         * TODO: update coding style to match project.
         *
         * \param stringLength: The length of the Fortran string.
         * \param *fString: The pointer to the start of the Fortran string.
         */
        int stringLen = stringLength;
        for ( int k1 = stringLength - 1; k1 >= 0; k1-- )
    	{
    	    if ( fString[ k1 ] != ' ' ) break;
    	    stringLen = k1;
    	}
        char* cString  = new char [ stringLen + 1 ];
        memcpy ( cString, fString, stringLen );
        cString[ stringLen ] = '\0';
        return cString;
    }

}

#endif
