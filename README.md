# Salp

Salp is a comprehensive and easy to learn/use linear algebra library for JavaScript.

- It is focused on scientific computing and data science
- Applicable in both NodeJS and browser builds
- (Deliberately) similar to [Matlab](https://de.mathworks.com/products/matlab.html) and [NumPy](https://numpy.org/)
- Supports vectors and matrices
- Supports calculations with integer and floating point numbers (see [How can I use other data types?](#how-can-i-use-other-data-types))

Did you have a question, a feature request or found a problem? Then please feel free to contact me at any time. The best way (for me) is to use the [Github issue tracker](https://github.com/SebastianNiemann/Mantella/issues).

Table of contents:

1. [Installation](#installation)
1. [Getting started](#getting-started)
1. [API](#api)
1. [FAQ](#faq)
1. [Roadmap](#roadmap)

## Installation



## Getting started



## API

Fields:
[nCol](#ncol),
[nElem](#nelem),
[nRow](#nrow)

Creation:
[Mat](#mat),
[empty](#empty),
[grid](#grid),
[identity](#identity),
[linearSpaced](#linspace),
[logSpaced](#logspace),
[lowerTriangular](#lowertriangular),
[ones](#ones),
[randomGamma](#randomgamma),
[randomNormal](#randomnormal),
[randomUniform](#randomuniform),
[repeat](#repeat),
[sample](#sample),
[sequence](#sequence),
[upperTriangular](#uppertriangular),
[zeros](#zeros)

Layout manipulation:
[concatCol](#concatcol),
[concatRow](#concatrow),
[filterCol](#filtercol),
[filterRow](#filterrow),
[flat](#flat),
[groupBy](#groupby),
[insertCol](#insertcol),
[insertRow](#insertrow),
[popCol](#appendcol),
[popRow](#appendrow),
[prependCol](#prependcol),
[prependRow](#prependrow),
[pushCol](#pushcol),
[pushRow](#pushrow),
[removeCol](#removecol),
[removeRow](#removerow),
[resize](#resize),
[shiftCol](#shiftcol),
[shiftRow](#shiftrow),
[sortCol](#sortcol),
[sortRow](#sortrow),
[spliceCol](#splicecol),
[spliceRow](#splicerow),
[split](#splitcol),
[split](#splitrow),
[swapCol](#swapcol),
[swapRow](#swaprow),
[unshiftCol](#unshiftcol),
[unshiftRow](#unshiftrow)

Accessing and indexing:
[col](#col),
[diag](#diag),
[elem](#elem),
[row](#row)

Iterators:
[entries](#entries),
[entriesCol](#entriescol),
[entriesRow](#entriesrow),
[keys](#keys),
[keysCol](#keyscol),
[keysRow](#keysrow),
[values](#values),
[valuesCol](#valuescol),
[valuesRow](#valuesrow)

Inplace operations:
[copyWithin](#copywithin),
[inplace](#inplace),
[inplaceAdd](#inplaceadd),
[inplaceCol](#inplacecol),
[inplaceDivideElem](#inplacedivideelem),
[inplaceMultiplyElem](#inplacemultiplyelem),
[inplaceReverse](#inplacereverse),
[inplaceRotate](#inplacerotate),
[inplaceRow](#inplacerow),
[inplaceShuffle](#inplaceshuffle),
[inplaceSort](#inplacesort),
[inplaceSubtract](#inplacesubtract)

Functional programming:
[count](#count),
[every](#every),
[fill](#fill),
[filter](#filter),
[find](#find),
[findIndex](#findindex),
[forEach](#foreach),
[forEachCol](#foreachrol),
[forEachRow](#foreachrow),
[indexOf](#indexof),
[join](#join),
[lastIndexOf](#lastindexof),
[map](#map),
[mapCol](#mapcol),
[mapRow](#maprow),
[none](#none),
[pop](#pop),
[push](#push),
[reduce](#reduce),
[reduceRight](#reduceright),
[replace](#replace),
[reverse](#reverse),
[rotate](#rotate),
[shift](#shift),
[shuffle](#shuffle),
[slice](#slice),
[some](#some),
[sort](#sort),
[splice](#splice),
[unshift](#unshift)

Logical functions:
[hasInf](#hasinf),
[hasNaN](#hasnan),
[hasNull](#hasnull),
[includes](#includes),
[isApproxEqual](#isapproxequal),
[isBetween](#isbetween),
[isCol](#iscol),
[isEmpty](#isempty),
[isEqual](#isequal),
[isFinite](#isfinite),
[isGreater](#isgreater),
[isGreaterOrEqual](#isgreaterorequal),
[isLess](#isless),
[isLessOrEqual](#islessorequal),
[isMat](#ismat),
[isNaN](#isNaN),
[isPositiveDefinite](#ispositivedefinite),
[isRow](#isrow),
[isSquare](#issquare),
[isSymmetric](#issymmetric),
[isVector](#isvector)

Basic mathematical functions:
[abs](#abs),
[cbrt](#cbrt),
[ceil](#ceil),
[clamp](#clamp),
[clz32](#clz32),
[cube](#cube),
[deg2Rad](#deg2rad),
[erf](#erf),
[exp](#exp),
[exp2](#exp2),
[exp10](#exp10),
[expK](#expk),
[expm1](#expm1),
[floor](#floor),
[fround](#fround),
[gamma](#gamma),
[log](#log),
[log2](#log2),
[log10](#log10),
[log1p](#log1p),
[logK](#logk),
[mod](#mod),
[negate](#negate),
[pow](#pow),
[rad2Deg](#rad2deg),
[reciprocal](#reciprocal),
[remainder](#remainder),
[root](#root),
[round](#round),
[sign](#sign),
[sqrt](#sqrt),
[square](#square),
[trunc](#trunc)

Trigonometric & hyperbolic functions:
[acos](#acos),
[acosh](#acosh),
[acot](#acot),
[acoth](#acoth),
[acsc](#acsc),
[acsch](#acsch),
[asec](#asec),
[asech](#asech),
[asin](#asin),
[asinh](#asinh),
[atan](#atan),
[atan2](#atan2),
[atanh](#atanh),
[cos](#cos),
[cosh](#cosh),
[cot](#cot),
[coth](#coth),
[csc](#csc),
[csch](#csch),
[hypot](#hypot),
[sec](#sec),
[sech](#sech),
[sin](#sin),
[sinc](#sinc),
[sinh](#sinh),
[sinhc](#sinhc),
[tan](#tan),
[tanc](#tanc),
[tanh](#tanh),
[tanhc](#tanhc)

Statistical function:
[centralMoment](#centralmoment),
[change](#change),
[cumulative](#cumulative),
[cumulativeProduct](#cumulativeproduct),
[cumulativeSum](#cumulativesum),
[correlation](#correlation),
[covariance](#covariance),
[decile](#decile),
[difference](#difference),
[histogram](#histogram),
[interquartileRange](#interquartilerange),
[kurtosis](#kurtosis),
[max](#max),
[maxIndex](#maxindex),
[mean](#mean),
[median](#median),
[min](#min),
[minIndex](#minindex),
[mode](#mode),
[percentile](#percentile),
[quantile](#quantile),
[quartile](#quartile),
[range](#range),
[skewness](#skewness),
[standardDeviation](#standarddeviation),
[standardisedCentralMoment](#standardisedcentralmoment),
[variance](#variance)

Set operations:
[setDifference](#setdifference),
[setIntersect](#setintersect),
[setSymmetricDifference](#setsymmetricdifference),
[setUnion](#setunion),
[unique](#unique)

Linear algebra:
[add](#add),
[choleskyDecomposition](#choleskydecomposition),
[conditionNumber](#conditionnumber),
[crossProduct](#crossproduct),
[determinant](#determinant),
[divide](#divide),
[divideElem](#divideelem),
[dotProduct](#dotproduct),
[eigenDecomposition](#eigendecomposition),
[generalisedInverse](#generalisedinverse),
[hessenbergDecomposition](#hessenbergdecomposition),
[inverse](#inverse),
[kroneckerProduct](#kroneckerproduct),
[luDecomposition](#ludecomposition),
[multiply](#multiply),
[multiplyElem](#multiplyelem),
[norm](#norm),
[orthonormalBasis](#orthonormalbasis),
[qrDecomposition](#qrdecomposition),
[qzDecomposition](#qzdecomposition),
[rank](#rank),
[schurDecomposition](#schurdecomposition),
[singularValueDecomposition](#singularvaluedecomposition),
[solveLeastSquare](#solveLeastsquare),
[solveLinear](#solvelinear),
[subtract](#subtract),
[trace](#trace),
[transpose](#transpose)

Output:
[toString](#tostring)

Inner functionality:
[_raw](#_raw),
[_rng](#_rng),
[_scalarAcot](#_scalaracot),
[_scalarAcoth](#_scalaracoth),
[_scalarAcsc](#_scalaracsc),
[_scalarAcsch](#_scalaracsch),
[_scalarAdd](#_scalaradd),
[_scalarAsec](#_scalarasec),
[_scalarAsech](#_scalarasech),
[_scalarCot](#_scalarcot),
[_scalarCoth](#_scalarcoth),
[_scalarCsc](#_scalarcsc),
[_scalarCsch](#_scalarcsch),
[_scalarDivide](#_scalardivide),
[_scalarMultiply](#_scalarmultiply),
[_scalarNegate](#_scalarnegate),
[_scalarRandomNormal](#_scalarrandomnormal),
[_scalarRandomGamma](#_scalarrandomgamma),
[_scalarSec](#_scalarsec),
[_scalarSech](#_scalarsech),
[_scalarSinhc](#_scalarsinhc),
[_scalarSinc](#_scalarsinc),
[_scalarSubtract](#_scalarsubtract),
[_scalarTanc](#_scalartanc)

## FAQ

### How can I use other data types?

Salp can store any type as a data value. Mixed datasets are also possible:

```js
const cities = new Mat([
  // city, area [km^2], coordinates, some districts
  ['Berlin', 891.1, { lat: 52.517, lng: 13.389 }, ['Mitte', 'Spandau']],
  ['Hamburg', 755.2, { lat: 53.565, lng: 10.001 }, ['Altona', 'Harburg']],
  // ...
])

cities.col(0).includes('Berlin')
// true
cities.col(1).mean()
// 823.15
```

However, not all calculations support every data type:

- All functions that only pass data but do not have to interpret it themselves (e.g. [col](#col), [sample](#sample) or [pushRow](#pushrow)) work fine.
    - This also applies to functions like [inplace](#inplace) or [map](#map), because data is only passed on to the user's function.
- All mathematical functions expect only integer and floating point numbers.
- All other functions (e.g. [includes](#includes), [histogram](#histogram) or [groupBy](#setunion)) need at least a reasonable form of equality or distance.

To support new data types (like coordinates) it is therefore sometimes necessary to extend internal calculations like [_scalarIsEqual](#_scalarIsEqual):

```js
// Affects only the local instance
cities._scalarIsEqual = (a, b) => {
  if (a instanceof Coordinate && b instanceof Coordinate) {
    // Own implementation
  } else {
    return cities.__proto__._scalarIsEqual(...arguments)
  }
}

// Affects all instances
const _nativeScalarIsEqual = Mat.prototype._scalarIsEqual
Mat.prototype._scalarIsEqual = (a, b) => {
  if (a instanceof Coordinate && b instanceof Coordinate) {
    // Own implementation
  } else {
    return _nativeScalarIsEqual(...arguments)
  }
}
```

If you are unsure what you would need to add/expand in order to support your data type, feel free to [ask](https://github.com/SebastianNiemann/Mantella/issues/new) anytime.

## Roadmap

- Support of basic matrix functionality
- Support of matrix creations
- Support of matrix layout manipulations
- Support of logical functions
- Support of mathematical, trigonometric & hyperbolic functions
- Support of statistical functions
- Support of set operations
- Support of decompositions, factorisations, inversions and equation solvers
- Support of similarity metrics
- Support of complex numbers
- Support of datetime values
- Support of coordinates
- Acceleration of BLAS/LAPACK-like operations with WebAssembly

---

Distributed under [MIT license](http://opensource.org/licenses/MIT).
