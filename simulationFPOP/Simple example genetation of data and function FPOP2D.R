

devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)


#Simple Example
n <- 10
chp <- c(5,10)
mu1 <- c(0, 10)
mu2 <- c(1,4)
sigma <- 1
penalty <- 2 * sigma * log(10)

data <- data_gen2D(n, chp, mu1, mu2, sigma)
data

######################## PELT ############################################
resPELT <- FPOP2D(data[1,], data[2,], penalty, type = 0)
resPELT
#$changepoints
#[1]  5 10
#$means1
#[1] -0.2002727  9.8805189
#$means2
#[1] 0.9263757 4.5035136
#$globalCost
#[1] -9.21034
plotFPOP2D(data, resPELT$changepoints,resPELT$means1, resPELT$means2)
######################### FPOP type = 1 ##################################
resFPOPt1 <- FPOP2D(data[1,], data[2,], penalty, type = 1)
resFPOPt1 
#$changepoints
#[1]  5 10
#$means1
#[1] -0.2002727  9.8805189
#$means2
#[1] 0.9263757 4.5035136
#$globalCost
#[1] -9.21034
plotFPOP2D(data, resFPOPt1$changepoints,resFPOPt1$means1, resFPOPt1$means2)
#########################FPOP type  = 2 ##################################
resFPOPt2 <- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOPt2 
#$changepoints
#[1]  5 10
#$means1
#[1] -0.2002727  9.8805189
#$means2
#[1] 0.9263757 4.5035136
#$globalCost
#[1] -9.21034
plotFPOP2D(data, resFPOPt2$changepoints,resFPOPt2$means1, resFPOPt2$means2)
