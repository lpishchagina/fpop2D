############################################################################
############################################################################
##                    package installation                                ##
############################################################################
############################################################################

devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)
devtools::install_github("lpishchagina/OptPartitioning2D")
library(OptPartitioning2D)

#############################################################################################
#############################################################################################
##                                         Test1                                           ##
##                                      Time complexity                                    ##
##                            The data without changepoints                                ##
##                                      n = 10000                                          ##
#############################################################################################
#############################################################################################


devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)

###############################
# data generation n = 10000   #
#     without changepoints    #
###############################

n <- 10000
chp <- c(10000)
mu1 <- c(10)
mu2 <- c(0)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

resPELT<- FPOP2D(data[1,], data[2,], penalty, type = 0)
resPELT

#$changepoints
#[1] 10000

#$means1
#[1] 10.00962

#$means2
#[1] -0.01279104

#$globalCost
#[1] -18.42068


#resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 1)
#resFPOP1
# a lot of time


resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2
#$changepoints
#[1] 10000

#$means1
#[1] 10.00962

#$means2
#[1] -0.01279104

#$globalCost
#[1] -18.42068


###############################
#       Function OneStep      #
###############################

#Function OneStep  returns the execution time of a given algorithm

OneStep <- function(data1, data2, penalty, type, func = "FPOP2D")
{
  if (type == 0){t <- system.time(FPOP2D(data1, data2, penalty, type = 0))[[1]]}
  if (type == 1){t <- system.time(FPOP2D(data1, data2, penalty, type = 1))[[1]]}
  if (type == 2){t <- system.time(FPOP2D(data1, data2, penalty, type = 2))[[1]]}
  return(t)
}


#############################################################################################
#############################################################################################
##                               One time complexity test                                  ##
#############################################################################################
#############################################################################################


timePELT <- OneStep(data[1,], data[2,], penalty, type = 0, func = "FPOP2D")
timePELT
#[1] 10.66
timeFPOPt2 <- OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D")
timeFPOPt2
#[1] 0.25

###############################
#          Сomparison         #
###############################

timePELT/timeFPOPt2
#[1] 42.64

###############################
#          Сonclusion         #
###############################
#For the data without changepoints FPOP(type = 2) is faster than PELT



#############################################################################################
#############################################################################################
##                               Time complexity test. Iteration                           ##
#############################################################################################
#############################################################################################


###############################
# data generation n = 100000  #
#     without changepoints    #
###############################

n <- 10000
chp <- c(10000)
mu1 <- c(10)
mu2 <- c(0)
sigma <- 1

penalty <- 2*log(n)

nStep <- 10

timePELT_iter <- 0

timeFPOPt2_iter<- 0

for(i in 1:nStep){
  
  data <- data_gen2D(n, chp, mu1, mu2, sigma)
  
  timePELT_iter<- timePELT_iter + OneStep(data[1,], data[2,], penalty, type = 0, func = "FPOP2D")
  timeFPOPt2_iter<- timeFPOPt2_iter + OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D")
}

###############################
#          Сomparison         #
###############################
timePELT_iter
#[1] 68.55
timeFPOPt2_iter
#[1] 3.66

timePELT_iter/timeFPOPt2_iter
#[1] 18.72951
###############################
#          Сonclusion         #
###############################
#For the data without changepoints FPOP(type = 2) is faster than PELT




#############################################################################################
#############################################################################################
##                                         microbenchmark                                  ##
#############################################################################################
#############################################################################################

############################################################################
############################################################################
##                    package installation                                ##
############################################################################
############################################################################
library(microbenchmark)
library(ggplot2)

res_PELT_FPOPt2 <- microbenchmark( OneStep(data[1,], data[2,], penalty, type = 0, func = "FPOP2D"), OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D"),  times = 5)
res_PELT_FPOPt2

#Unit: seconds
#                                                           expr        min         lq      mean     median         uq    max         neval
#OneStep(data[1, ], data[2, ], penalty, type = 0, func = "FPOP2D") 11371.304 11465.2046 12807.3161 11801.0684 13829.2101 15569.7932     5
#
#OneStep(data[1, ], data[2, ], penalty, type = 2, func = "FPOP2D")   467.173   513.2773   527.7452   545.3618   548.0496   564.8643     5

autoplot(res_PELT_FPOPt2)

#############################################################################################
#############################################################################################
##                                        End Test1                                        ##
#############################################################################################
#############################################################################################
