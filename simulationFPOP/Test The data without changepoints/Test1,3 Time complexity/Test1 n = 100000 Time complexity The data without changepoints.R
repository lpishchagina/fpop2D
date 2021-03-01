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
##                                      n = 100000                                         ##
#############################################################################################
#############################################################################################


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
#

#$means1
#

#$means2
#

#$globalCost
#

#resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 1)
#resFPOP1
# a lot of time


resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP1
#$changepoints
#

#$means1
#

#$means2
#

#$globalCost
#


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
#
timeFPOPt2 <- OneStep(data[1,], data[2,], penalty, type = 2, func = "FPOP2D")
timeFPOPt2
#

###############################
#          Сomparison         #
###############################

timePELT/timeFPOPt2
# 

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
#
timeFPOPt2_iter
#

timePELT_iter/timeFPOPt2_iter
#
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
#
#
#

autoplot(res_PELT_FPOPt2)
#############################################################################################
#############################################################################################
##                                        End Test1                                        ##
#############################################################################################
#############################################################################################