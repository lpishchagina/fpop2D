
<a id="top"></a>
#  fpop2D Vignette
### Liudmila Pishchagina
### February 11, 2021

## Quick Start

`fpop2D` is an R package written in Rcpp/C++ and developed to change-point detection in 2 bivariate time-series.

The package implements the Functional Pruning Optimal Partitioning algorithm with two types of pruning: "intersection of sets" and "difference of intersection and union of sets". 


We present a basic use of the main functions of the `fpop2D` package. 

We install the package from Github:

```r
#devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)
```

## The function GenData2D

The `data_gen2D` function simulates a bivariate time series with the arguments:

`n`  is a time series length.

`changepoints` is a changepoint vector that gives the last index of each segment.

The last element of `changepoints` always equals to the length of time series `Data`.

`means1` is a vector of means for the first univariate time series.

The length of this vector is equal to the length of `changepoints`.

`means2` is a vector of means for the second univariate time series.

The length of this vector is equal to the length of `changepoints`.

`noise` is a variance of the time series(by default it is equal to `1`).



```r
n <- 100
Data <- data_gen2D(n, changepoints = c(20, 40, 60, 80, 100), means1 = c(0, 1, 0, 1, 0), means2 = c(1, 2, 3, 4, 5), noise = 1)
```
## The function FPOP2D

The `FPOP2D` function returns the result of the segmentation using the parameters:

`data1` is the first univariate time series.

`data2` is the second univariate time series.

`penalty` is a value of penalty (a non-negative real number).

The `penalty` here equals to a classic `2*(noise^2)*log(n)`. 

`type` is a parameter defining the algorithm of segmentation.

The `type` must be either `1` or `2`.

We use Functional Pruning Optimal Partitioning algorithm with the pruning "intersection of sets" when `type = 1`.
 
We use Functional Pruning Optimal Partitioning algorithm with the pruning "difference of intersection and union of sets" when `type = 2`.

We choose a gaussian cost.

```r
resFPOP1 <- FPOP2D(Data[1,], Data[2,], penalty = 2 * log(n) , type = 1)

resFPOP2 <- FPOP2D(Data[1,], Data[2,], penalty = 2 * log(n) , type = 2)
```

```
## resFPOP1$changepoints
## 
## resFPOP1$means1
## 
## resFPOP1$means2
##
## resFPOP1$globalCost
##
```

```
## resFPOP2$changepoints
## 
## resFPOP2$means1
## 
## resFPOP2$means2
##
## resFPOP2$globalCost
##
```

`changepoints` is a  vector of the inferred changepoints.

`means1`  is a vector of the inferred means for the first univariate time series. 

`means2`  is a vector of the inferred means for the second univariate time series. 
  
`globalCost` is the overall gaussian cost of the segmented data. 

## The function plotFPOP2D

The function `plotFPOP2D` plots a graph for each univariate time series of the bivariate series.

The graph shows the univariate time series, the estimated values of means and the inferred segments. 

The function `plotFPOP2D` uses the parameters:

`data` is the bivariate time series.

`changepoints` is a  vector of the inferred changepoints.

`means1`  is a vector of the inferred means for the first univariate time series. 

`means2`  is a vector of the inferred means for the second univariate time series.

```r
plotFPOP2D(data = Data, changepoints = c(20, 40, 60, 80, 100), means1 = c(0, 1, 0, 1, 0), means2 = c(1, 2, 3, 4, 5))
```
[Back to Top](#top)