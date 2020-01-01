# Salp

Salp is a comprehensive and easy to learn/use linear algebra library for JavaScript.

- It is focused on scientific computing and data science
- Applicable in both NodeJS and browser builds
- (Deliberately) similar to [Matlab](https://de.mathworks.com/products/matlab.html) and [NumPy](https://numpy.org)
- Supports dense vectors and matrices
- Supports calculations with integer and floating point numbers (see [How can I use other data types?](#how-can-i-use-other-data-types))

Do you have a question, a feature request or found a problem? Then please feel free to contact me at any time. The best way (for me) is to use the [Github issue tracker](https://github.com/SebastianNiemann/Mantella/issues).

Table of contents:

1. [Installation](#installation)
1. [Getting started](#getting-started)
1. [API](#api)
1. [FAQ](#faq)
1. [Roadmap](#roadmap)

## Installation

Salp supports the latest two LTS versions of NodeJS and Browsers with >0.5% market share (based on [Browserslist](https://browserl.ist/?q=%3E+0.5%25)) by default.

> If you need to support other/older browsers or NodeJS versions, I can recommend [Babel](https://babeljs.io) to compile a suitable version according to your own requirements.

### Module bundlers & NodeJS

Using the [NPM package](https://www.npmjs.com/package/salp) is the recommended installation method for both frontends and backends.

[![NPM](https://img.shields.io/npm/v/salp?style=flat-square
)](https://www.npmjs.com/package/salp)

```
npm install salp
```

Most module bundler resolvers support both `main` and the unofficial `module` field of Salp's `package.json`, which will automatically load the correct version, depending on whether you use `import` (ES6 module)

```js
import salp from 'salp'
// import salp from 'salp/dist/salp.js' // (explicit form)

// ... your source code
```

or `require` (CommonJS):

```js
const salp = require('salp')
// const salp = require('salp/dist/salp.cjs.js') // (explicit form)

// ... your source code
```

Alternatively, if it is not automatically detected, the explicit form can be used to choose the correct variant manually.

### HTML embedding

Besides the generation of a frontend version [via a module bundler](#module-bundlers--nodejs), there are two options for direct embedding in HTML pages.

Modern browsers with [ES6 module support](https://caniuse.com/#feat=es6-module) can `import` Salp directly from a content delivery network (CDN):

[![jsDelivr](https://img.shields.io/npm/v/salp?label=jsdelivr&style=flat-square)](https://cdn.jsdelivr.net/npm/salp@latest/dist/)

```html
<script type="module">
import salp from 'https://cdn.jsdelivr.net/npm/salp@latest/dist/salp.js'

// ... your source code
</script>
```

Alternatively, for browsers with no ES6 module support, a precompiled [IIFE](https://developer.mozilla.org/en-US/docs/Glossary/IIFE) variant is available:

```html
<!-- Adds a globally accessible variable (being the module object), named 'salp' -->
<script src="https://cdn.jsdelivr.net/npm/salp@latest/dist/salp.iife.js"></script>
<script>
// ... your source code
</script>
```

## Getting started

In the following you will learn about common use cases and concepts for getting started with Salp:

- [Loading data & creating matrices](#loading-data--creating-matrices)
- [Calculations & data analysis](#calculations--data-analysis)
- [Saving your results](#saving-your-results)
- [Troubleshooting](#troubleshooting)

For a complete list of all functions, see the [API documentation](#api).

### Loading data & creating matrices

- file (e.g. csv)

```js
import fs from 'fs'

data = fs.readFileSync('data.csv', 'utf8')
matrix = salp.fromCSV(data)
```

- arrayOfArray (database)

```js
// Could be the result of a database request
data = [
  [8, 1, 6],
  [3, 5, 7],
  [4, 9, 2],
]

matrix = new salp.Mat(data)
```

```js
data = [[8, 1, 6]]
rowVector = new salp.Mat(data)
```

- array (other libs)

```js
data = [8, 1, 6, 3, 5, 7, 4, 9, 2]
colVector = new salp.Mat(data)
```

```js
matrix = colVector.resize(3, 3) // rows, cols
// [
//   [8, 3, 4],
//   [1, 5, 9],
//   [6, 7, 2],
// ]
```

```js
matrix = matrix.transpose()
// [
//   [8, 1, 6],
//   [3, 5, 7],
//   [4, 9, 2],
// ]
```

### Calculations & data analysis

- calculations
- pipeline
- statistics

```js

```

### Saving your results

- toCSV
- raw

```js
import fs from 'fs'



fs.writeFileSync('./data.csv', matrix.toCSV())
```

```js

```

### Troubleshooting

```js
console.log(matrix.toString())
// console.log(String(matrix)) // (alternative)
```

```js
salp._verbosity = ['errors', 'warnings', 'notices']
```
- verbosity

```js

```

### Advanced functionality

```js

```

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
[ungroup](#ungroup),
[zeros](#zeros)

Layout manipulation:
[concatCol](#concatcol),
[concatRow](#concatrow),
[filterCol](#filtercol),
[filterRow](#filterrow),
[flat](#flat),
[groupByCol](#groupbycol),
[groupByRow](#groupbyrow),
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
[splitCol](#splitcol),
[splitRow](#splitrow),
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
[hasInfinite](#hasinf),
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
[isRow](#isrow),
[isSquare](#issquare),
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

Input:
[fromCOO](#loadcoo),
[fromCSV](#loadcsv),
[fromPGM](#loadpgm)

Output:
[toCOO](#tocoo),
[toCSV](#tocsv),
[toPGM](#topgm),
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

If you are unsure what you would need to add/expand in order to support your data type, feel free to [ask me](https://github.com/SebastianNiemann/Mantella/issues/new) anytime.

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
