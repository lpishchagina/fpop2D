#Simple test :

devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)
set.seed (21)
n <- 10
chp <- c(3, 5, 8, 10)
mu1 <- c(0, 1, 0, 1)
mu2 <- c(1, 2, 3, 4)
sigma <- 1
penalty <- 2 * sigma * log(10)

data <- data_gen2D(n, chp, mu1, mu2, sigma)
data
#



resFPOPt1 <- FPOP2D(data[1,], data[2,], penalty, type = 1)
resFPOPt1 
#$changepoints
#
#$means1
#
#$means2
#
#$globalCost
#
plotFPOP2D(data, resFPOPt1$changepoints,resFPOPt1$means1, resFPOPt1$means2)

####################################################################
resFPOPt2 <- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOPt2 
#$changepoints
#
#$means1
#
#$means2
#
#$globalCost
#
plotFPOP2D(data, resFPOPt2$changepoints,resFPOPt2$means1, resFPOPt2$means2)
