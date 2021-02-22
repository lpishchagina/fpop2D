devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)

###############################
# data generation n = 100000  #
#     without changepoints    #
###############################

n <- 100000
chp <- c(100000)
mu1 <- c(10)
mu2 <- c(0)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

resPELT<- FPOP2D(data[1,], data[2,], penalty, type = 0)
resPELT

#$changepoints
#[1] 1e+05

#$means1
#[1] 9.998827

#$means2
#[1] 0.002264522

#$globalCost
#[1] -23.02585

#resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 1)
#resFPOP1
# a lot of time


resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP1
#$changepoints
#[1] 1e+05

#$means1
#[1] 10.00353

#$means2
#[1] 0.001748395

#$globalCost
#[1] -23.02585


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
#[1] 39.64
timeFPOPt2 <- OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D")
timeFPOPt2
#[1] 7.27

###############################
#          Сomparison         #
###############################

timePELT/timeFPOPt2
# [1] 5.452545

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

n <- 100000
chp <- c(100000)
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
#[1] 583.62
timeFPOPt2_iter
#[1] 71.59

timePELT_iter/timeFPOPt2_iter
#[1] 8.152256
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
##                    package instalation                                 ##
############################################################################
############################################################################
library(microbenchmark)
library(ggplot2)

res_PELT_FPOPt2 <- microbenchmark( OneStep(data[1,], data[2,], penalty, type = 0, func = "FPOP2D"), OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D"),  times = 5)
res_PELT_FPOPt2

#Unit: seconds
#                                                           expr        min         lq      mean     median         uq    max         neval
#OneStep(data[1, ], data[2, ], penalty, type = 0, func = "FPOP2D") 225.184003 268.611685 329.42547 299.072430 425.805488  428.45374     5
#OneStep(data[1, ], data[2, ], penalty, type = 2, func = "FPOP2D")   7.644421   7.747608  11.76002   7.816514   8.106411  27.48514      5
#

autoplot(res_PELT_FPOPt2)
