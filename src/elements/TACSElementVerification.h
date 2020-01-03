/*
  This file is part of TACS: The Toolkit for the Analysis of Composite
  Structures, a parallel finite-element code for structural and
  multidisciplinary design optimization.

  Copyright (C) 2014 Georgia Tech Research Corporation

  TACS is licensed under the Apache License, Version 2.0 (the
  "License"); you may not use this software except in compliance with
  the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0
*/

#ifndef TACS_ELEMENT_VERIFICATION_H
#define TACS_ELEMENT_VERIFICATION_H

#include "TACSElement.h"

/**
  Assign variables randomly to an array. This is useful for
  testing various things.
 */
void TacsGenerateRandomArray( TacsReal *array, int size,
                              TacsReal lower=-1.0,
                              TacsReal upper=1.0 );
void TacsGenerateRandomArray( TacsComplex *array, int size,
                              TacsComplex lower=-1.0,
                              TacsComplex upper=1.0 );

/*
  Find the largest absolute value of the difference between the
  arrays a and b
*/
double TacsGetMaxError( TacsScalar *a, TacsScalar *b, int size,
                        int *max_index );

/*
  Find the maximum relative error between a and b and return the
*/
double TacsGetMaxRelError( TacsScalar *a, TacsScalar *b, int size,
                           int *max_index );

/*
  Print out the values and the relative errors
*/
void TacsPrintErrorComponents( FILE *fp, const char *descript,
                               TacsScalar *a, TacsScalar *b,
                               int size );

/*
  Perturb the input variables in the forward sense
*/
void TacsForwardDiffPerturb( TacsScalar *out, int size,
                             const TacsScalar *orig,
                             const TacsScalar *pert,
                             double dh );

/*
  Perturb the variables in the backward sense
*/
void TacsBackwardDiffPerturb( TacsScalar *out, int size,
                              const TacsScalar *orig,
                              const TacsScalar *pert,
                              double dh );

/*
  Form the forward approximation
*/
void TacsFormDiffApproximate( TacsScalar *forward,
                              const TacsScalar *backward,
                              int size,
                              TacsScalar dh );

/**
  Test the residual implementation against the Lagrangian equations
  of motion. This relies on the element implementation of the kinetic
  and potential energies.

  @param element The element object
  @param time Simulation time
  @param Xpts The element nodal variables
  @param vars The element state variables
  @param dvars The time derivatives of the state variables
  @param ddvars The second time derivatives of the state variables
  @param dh The finite-difference step size
  @param test_print_level The output level
  @param test_fail_atol The test absolute tolerance
  @param test_fail_rtol The test relative tolerance
*/
int TacsTestElementResidual( TACSElement *element,
                             int elemIndex,
                             double time,
                             const TacsScalar Xpts[],
                             const TacsScalar vars[],
                             const TacsScalar dvars[],
                             const TacsScalar ddvars[],
                             double dh=1e-7,
                             int test_print_level=2,
                             double test_fail_atol=1e-5,
                             double test_fail_rtol=1e-5 );

/**
  Test the Jacobian matrix implementation against the residual.

  @param element The element object
  @param time Simulation time
  @param Xpts The element nodal variables
  @param vars The element state variables
  @param dvars The time derivatives of the state variables
  @param ddvars The second time derivatives of the state variables
  @param dh The finite-difference step size
  @param test_print_level The output level
  @param test_fail_atol The test absolute tolerance
  @param test_fail_rtol The test relative tolerance
*/
int TacsTestElementJacobian( TACSElement *element,
                             int elemIndex,
                             double time,
                             const TacsScalar Xpts[],
                             const TacsScalar vars[],
                             const TacsScalar dvars[],
                             const TacsScalar ddvars[],
                             int col=-1,
                             double dh=1e-7,
                             int test_print_level=2,
                             double test_fail_atol=1e-5,
                             double test_fail_rtol=1e-5 );

/**
  Test the adjoint-residual product implementation

  @param element The element object
  @param dvLen The length of the design variable array
  @param x The design variable array
  @param time Simulation time
  @param Xpts The element nodal variables
  @param vars The element state variables
  @param dvars The time derivatives of the state variables
  @param ddvars The second time derivatives of the state variables
  @param dh The finite-difference step size
  @param test_print_level The output level
  @param test_fail_atol The test absolute tolerance
  @param test_fail_rtol The test relative tolerance
*/
int TacsTestAdjResProduct( TACSElement *element,
                           int elemIndex,
                           int dvLen,
                           const TacsScalar *x,
                           double time,
                           const TacsScalar Xpts[],
                           const TacsScalar vars[],
                           const TacsScalar dvars[],
                           const TacsScalar ddvars[],
                           double dh=1e-7,
                           int test_print_level=2,
                           double test_fail_atol=1e-5,
                           double test_fail_rtol=1e-5 );

/**
  Test the adjoint-residual product implementation

  @param element The element object
  @param time Simulation time
  @param Xpts The element nodal variables
  @param vars The element state variables
  @param dvars The time derivatives of the state variables
  @param ddvars The second time derivatives of the state variables
  @param dh The finite-difference step size
  @param test_print_level The output level
  @param test_fail_atol The test absolute tolerance
  @param test_fail_rtol The test relative tolerance
*/
int TacsTestAdjResXptProduct( TACSElement *element,
                              int elemIndex,
                              double time,
                              const TacsScalar Xpts[],
                              const TacsScalar vars[],
                              const TacsScalar dvars[],
                              const TacsScalar ddvars[],
                              double dh=1e-7,
                              int test_print_level=2,
                              double test_fail_atol=1e-5,
                              double test_fail_rtol=1e-5 );

/**
  Test if the basis function derivatives are implemented correct

  @param basis The TACSElementBasis to check
  @param dh The finite-difference step size
  @param test_print_level The output level
  @param test_fail_atol The test absolute tolerance
  @param test_fail_rtol The test relative tolerance
*/
int TacsTestElementBasis( TACSElementBasis *basis,
                          double dh=1e-7,
                          int test_print_level=2,
                          double test_fail_atol=1e-5,
                          double test_fail_rtol=1e-5 );

#endif // TACS_ELEMENT_VERIFICATION_H