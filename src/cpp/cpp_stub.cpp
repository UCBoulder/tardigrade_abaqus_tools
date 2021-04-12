/**
  ******************************************************************************
  * \file abaqus_tools.cpp
  ******************************************************************************
  * A C++ library for printing messages to stdout. Used as a stub repo example.
  ******************************************************************************
  */

#include<abaqus_tools.h>

namespace cppStub{

    /// Say hello
    /// @param message The message to print
    void sayHello(std::string message) {
        std::cout << "Hello " << message << std::endl;
    }

    void abaqusInterface( double *STRESS,       double *STATEV,       double *DDSDDE,       double &SSE,          double &SPD,
                          double &SCD,          double &RPL,          double *DDSDDT,       double *DRPLDE,       double &DRPLDT,
                          const double *STRAN,  const double *DSTRAN, const double *TIME,   const double &DTIME,  const double &TEMP,
                          const double &DTEMP,  const double *PREDEF, const double *DPRED,  const char *CMNAME,   const int &NDI,
                          const int &NSHR,      const int &NTENS,     const int &NSTATV,    const double *PROPS,  const int &NPROPS,
                          const double *COORDS, const double *DROT,   double &PNEWDT,       const double &CELENT, const double *DFGRD0,
                          const double *DFGRD1, const int &NOEL,      const int &NPT,       const int &LAYER,     const int &KSPT,
                          const int *JSTEP,     const int &KINC ){
    /*!
     * A template Abaqus UMAT c++ interface that performs Fortran to C++ type conversions, calculates the material
     * model's expected input, handles tensor shape changes, and calls a c++ material model.
     */

    //Define the tensor spatial dimensions
    const int spatialDimensions = 3;

    //Map FORTRAN UMAT variables to C++ types as necessary. Use case sensitivity to distinguish.
    //TODO: Decide if case sensitive variable names is a terrible idea or not
    //Vectors can be created directly with pointer arithmetic
    std::vector< double > stress( STRESS, STRESS + NTENS );
    std::vector< double > statev( STATEV, STATEV + NSTATV );
    std::vector< double > ddsddt( DDSDDT, DDSDDT + NTENS );
    std::vector< double > drplde( DRPLDE, DRPLDE + NTENS );
    const std::vector< double > strain( STRAN, STRAN + NTENS );
    const std::vector< double > dstrain( DSTRAN, DSTRAN + NTENS );
    const std::vector< double > time( TIME, TIME + 2 );
    const std::vector< double > predef( PREDEF, PREDEF + 1 );
    const std::vector< double > dpred( DPRED, DPRED + 1 );
    const std::string cmname( abaqusTools::FtoCString( 80, CMNAME ) );
    const std::vector< double > props( PROPS, PROPS + NPROPS );
    const std::vector< double > coords( COORDS, COORDS + spatialDimensions );
    const std::vector< int > jstep( JSTEP, JSTEP + 4 );
    //Fortran two-dimensional arrays require careful column to row major conversions to c++ types
    std::vector< std::vector< double > > ddsdde = abaqusTools::columnToRowMajor( DDSDDE, NTENS, NTENS );
    const std::vector< std::vector< double > > drot = abaqusTools::columnToRowMajor( DROT, spatialDimensions, spatialDimensions );
    const std::vector< std::vector< double > > dfgrd0 = abaqusTools::columnToRowMajor( DFGRD0, spatialDimensions, spatialDimensions );
    const std::vector< std::vector< double > > dfgrd1 = abaqusTools::columnToRowMajor( DFGRD1, spatialDimensions, spatialDimensions );

    //Call the constitutive model c++ interface
    if ( KINC == 1 && NOEL == 1 && NPT == 1 ){
        dummyMaterialModel( stress, statev,  ddsdde, SSE,    SPD,
                            SCD,    RPL,     ddsddt, drplde, DRPLDT,
                            strain, dstrain, time,   DTIME,  TEMP,
                            DTEMP,  predef,  dpred,  cmname, NDI,
                            NSHR,   NTENS,   NSTATV, props,  NPROPS,
                            coords, drot,    PNEWDT, CELENT, dfgrd0,
                            dfgrd1, NOEL,    NPT,    LAYER,  KSPT,
                            jstep,  KINC );
    }

    //Re-pack C++ objects into FORTRAN memory to return values to Abaqus
    //Scalars were passed by reference and will update correctly
    //Vectors don't require row/column major considerations, but do require re-packing to the Fortran pointer
    abaqusTools::rowToColumnMajor( STRESS, stress, 1, NTENS );
    abaqusTools::rowToColumnMajor( DDSDDT, ddsddt, 1, NTENS );
    abaqusTools::rowToColumnMajor( DRPLDE, drplde, 1, NTENS );
    abaqusTools::rowToColumnMajor( STATEV, statev, 1, NSTATV );
    //Arrays require vector of vector to column major conversion
    abaqusTools::rowToColumnMajor(DDSDDE, ddsdde, spatialDimensions, spatialDimensions);

    }

    void dummyMaterialModel( floatVector &stress,             floatVector &statev,        floatMatrix &ddsdde,       floatType &SSE,            floatType &SPD,
                             floatType &SCD,                  floatType &RPL,             floatVector &ddsddt,       floatVector &drplde,       floatType &DRPLDT,
                             const floatVector &strain,       const floatVector &dstrain, const floatVector &time,   const floatType &DTIME,    const floatType &TEMP,
                             const floatType &DTEMP,          const floatVector &predef,  const floatVector &dpred,  const std::string &cmname, const int &NDI,
                             const int &NSHR,                 const int &NTENS,           const int &NSTATV,         const floatVector &props,  const int &NPROPS,
                             const floatVector &coords,       const floatMatrix &drot,    floatType &PNEWDT,         const floatType &CELENT,   const floatMatrix &dfgrd0,
                             const floatMatrix &dfgrd1,       const int &NOEL,            const int &NPT,            const int &LAYER,          const int &KSPT,
                             const std::vector< int > &jstep, const int &KINC ){
        /*!
         * A template Abaqus c++ UMAT using c++ STL types. Variables in all caps reference ABAQUS FORTRAN
         * memory directly. Variables in lower case are native c++ type conversions stored separately from the original
         * ABAQUS FORTRAN memory.
         */

        //Call functions of constitutive model to do things
        sayHello( "Abaqus" );

        return;
    }

}
