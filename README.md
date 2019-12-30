# Salp

Salp is a comprehensive and easy to learn/use linear algebra library for JavaScript.

- It is focused on scientific computing and data science
- Applicable in both NodeJS and browser builds
- (Deliberately) similar to [Matlab](https://de.mathworks.com/products/matlab.html) and [NumPy](https://numpy.org/)
- Supports vectors and matrices
- Supports calculations with integer and floating point numbers (see [How can I use other data types?](#how-can-i-use-other-data-types))

Did you have a question, a feature request or found a problem? Then please feel free to contact me at any time. The best way (for me) is to use the [Github issue tracker](https://github.com/SebastianNiemann/Mantella/issues).

Table of contents:

1. [API](#api)
1. [FAQ](#faq)
1. [Roadmap](#roadmap)

## API

Fields:
[nCol](#nCol),
[nElem](#nElem),
[nRow](#nRow)

Creation:
[Mat](#mat),
[empty](#empty),
[grid](#grid),
[identity](#identity),
[linearSpaced](#linspace),
[logSpaced](#logspace),
[lowerTriangular](#lowertriangular),
[ones](#ones),
[randomGamma](#randomGamma),
[randomNormal](#randomNormal),
[randomUniform](#randomUniform),
[repeat](#repeat),
[sample](#sample),
[sequence](#sequence),
[upperTriangular](#uppertriangular),
[zeros](#zeros)

Layout manipulation:
[concatCol](#concatCol),
[concatRow](#concatRow),
[filterCol](#filterCol),
[filterRow](#filterRow),
[flat](#flat),
[insertCol](#insertcol),
[insertRow](#insertrow),
[popCol](#appendcol),
[popRow](#appendrow),
[prependCol](#prependcol),
[prependRow](#prependrow),
[pushCol](#appendcol),
[pushRow](#appendrow),
[removeCol](#removecol),
[removeRow](#removerow),
[resize](#resize),
[shiftCol](#shiftCol),
[shiftRow](#shiftRow),
[sortCol](#sortCol),
[sortRow](#sortRow),
[spliceCol](#shiftCol),
[spliceRow](#shiftCol),
[swapCol](#swapCol),
[swapRow](#swapRow),
[unshiftCol](#shiftCol),
[unshiftRow](#shiftCol)

Accessing and indexing:
[col](#col),
[diag](#diag),
[elem](#elem),
[row](#row)

Iterators:
[entries](#entries),
[entriesCol](#entriesCol),
[entriesRow](#entriesRow),
[keys](#keys),
[keysCol](#keysCol),
[keysRow](#keysRow),
[values](#values),
[valuesCol](#valuesCol),
[valuesRow](#valuesRow)

Inplace operations:
[copyWithin](#copyWithin),
[inplace](#inplace),
[inplaceAdd](#inplaceAdd),
[inplaceCol](#inplaceCol),
[inplaceDivideElem](#inplaceDivideElem),
[inplaceMultiplyElem](#inplaceMultiplyElem),
[inplaceReverse](#inplaceReverse),
[inplaceRotate](#inplaceRotate),
[inplaceRow](#inplaceRow),
[inplaceShuffle](#inplaceShuffle),
[inplaceSort](#inplaceSort),
[inplaceSubtract](#inplaceSubtract)

Functional programming:
[count](#count),
[every](#every),
[fill](#fill),
[filter](#filter),
[find](#find),
[findIndex](#findIndex),
[forEach](#forEach),
[forEachCol](#forEachCol),
[forEachRow](#forEachRow),
[indexOf](#indexOf),
[join](#join),
[lastIndexOf](#lastIndexOf),
[map](#map),
[mapCol](#mapCol),
[mapRow](#mapRow),
[none](#none),
[pop](#pop),
[push](#push),
[reduce](#reduce),
[reduceRight](#reduceRight),
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
[deg2Rad](#deg2Rad),
[erf](#erf),
[exp](#exp),
[exp2](#exp2),
[exp10](#exp10),
[expK](#expK),
[expm1](#expm1),
[floor](#floor),
[fround](#fround),
[gamma](#gamma),
[log](#log),
[log2](#log2),
[log10](#log10),
[log1p](#log1p),
[logK](#logK),
[mod](#mod),
[negate](#negate),
[pow](#pow),
[rad2Deg](#rad2Deg),
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
[cumulativeProduct](#cumulativeProduct),
[cumulativeSum](#cumulativeSum),
[correlation](#correlation),
[covariance](#covariance),
[decile](#decile),
[difference](#difference),
[histogram](#histogram),
[interquartileRange](#interquartilerange),
[kurtosis](#kurtosis),
[max](#max),
[maxIndex](#maxIndex),
[mean](#mean),
[median](#median),
[min](#min),
[minIndex](#minIndex),
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
[choleskyDecomposition](#choleskyDecomposition),
[conditionNumber](#conditionNumber),
[crossProduct](#crossProduct),
[determinant](#determinant),
[divide](#divide),
[divideElem](#divideElem),
[dotProduct](#dotProduct),
[eigenDecomposition](#eigenDecomposition),
[generalisedInverse](#generalisedInverse),
[hessenbergDecomposition](#hessenbergDecomposition),
[inverse](#inverse),
[kroneckerProduct](#kroneckerProduct),
[luDecomposition](#luDecomposition),
[multiply](#multiply),
[multiplyElem](#multiplyElem),
[norm](#norm),
[orthonormalBasis](#orthonormalBasis),
[qrDecomposition](#qrDecomposition),
[qzDecomposition](#qzDecomposition),
[rank](#rank),
[schurDecomposition](#schurDecomposition),
[singularValueDecomposition](#singularValueDecomposition),
[solveLeastSquare](#solveLeastSquare),
[solveLinear](#solveLinear),
[subtract](#subtract),
[trace](#trace),
[transpose](#transpose)

Output:
[toString](#tostring)

Inner functionality:
[._raw](#_raw),
[._rng](#_rng),
[_scalarTanc](#_scalarTanc),
[_scalarSinhc](#_scalarSinhc),
[_scalarSinc](#_scalarSinc),
[_scalarSec](#_scalarSec),
[_scalarSech](#_scalarSech),
[_scalarCsc](#_scalarCsc),
[_scalarCsch](#_scalarCsch),
[_scalarCot](#_scalarCot),
[_scalarCoth](#_scalarCoth),
[_scalarAsec](#_scalarAsec),
[_scalarAcsc](#_scalarAcsc),
[_scalarAcsch](#_scalarAcsch),
[_scalarAcot](#_scalarAcot),
[_scalarAcoth](#_scalarAcoth),
[_scalarAsech](#_scalarAsech),
[_scalarRandomNormal](#_scalarRandomNormal),
[_scalarRandomGamma](#_scalarRandomGamma),
[_scalarNegate](#_scalarNegate),
[_scalarAdd](#_scalarAdd),
[_scalarSubtract](#_scalarSubtract),
[_scalarMultiply](#_scalarMultiply),
[_scalarDivide](#_scalarDivide)

## FAQ

### How can I use other data types?

Salp can store any type as a data value. Mixed datasets are also possible:

```js
const mat = new Mat([
  // city, area [km^2], coordinates, some districts
  ['Berlin', 891.1, { lat: 52.517, lng: 13.389 }, ['Mitte', 'Spandau']],
  ['Hamburg', 755.2, { lat: 53.565, lng: 10.001 }, ['Altona', 'Harburg']],
  // ...
])

mat.col(0).includes('Berlin')
// true
mat.col(1).mean()
// 823.15
```

However, not all calculations support every data type:

- All functions that only pass data but do not have to interpret it themselves (e.g. [col](#col), [sample](#sample) or [pushRow](#pushrow)) work fine.
    - This also applies to functions like [inplace](#inplace) or [map](#map), because data is only passed on to the user's function.
- All mathematical functions expect only integer and floating point numbers.
- All other functions (e.g. [includes](#includes), [histogram](#histogram) or [setUnion](#setunion)) need at least a reasonable form of equality or distance.

To support new data types (like coordinates) it is therefore sometimes necessary to extend internal calculations like [_scalarIsEqual](#_scalarIsEqual):

```js
const _nativeScalarIsEqual = salp._scalarIsEqual

salp._scalarIsEqual = (a, b) => {
  if (a instanceof Coordinate && b instanceof Coordinate) {
    // Own implementation
  } else {
    return _nativeScalarIsEqual(...arguments);
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
