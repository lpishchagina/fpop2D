#Simple examples

devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)

n <- 8
chp <- c(3,6,8)
mu1 <- c(1, 5,8)
mu2 <- c(3, 10,1)
sigma <- 0.3

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data

#[,1]      [,2]     [,3]     [,4]     [,5]      [,6]      [,7]      [,8]
#[1,] 1.117346 0.7838427 1.115829 5.150744 4.742782  5.196941 8.2546388 8.1164104
#[2,] 3.055688 3.3488130 2.950066 9.852634 9.995425 10.141932 0.9879179 0.6483118

resPELT<- FPOP2D(data[1,], data[2,], penalty, type = 0)
resPELT

#$changepoints
#[1] 3 6 8

#$means1
#[1] 1.005673 5.030156 8.185525

#$means2
#[1] 3.1181890 9.9966635 0.8181148

#$globalCost
#[1] -12.47665


resFPOP1<- FPOP2D(data[1,], data[2,], penalty, type = 1)
resFPOP1

#$changepoints
#[1] 3 6 8

#$means1
#[1] 1.005673 5.030156 8.185525

#$means2
#[1] 3.1181890 9.9966635 0.8181148

#$globalCost
#[1] -12.47665


resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2

#$changepoints
#[1] 3 6 8

#$means1
#[1] 1.005673 5.030156 8.185525

#$means2
#[1] 3.1181890 9.9966635 0.8181148

#$globalCost
#[1] -12.47665


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

# Object: We compare the time complexity of PELT(type = 0), FPOP(type = 1), FPOP(type = 2) for one simulation.
#

###############################
#  data generation n = 10000  #
#      linear growth n~k      #
###############################
 

T_n <- 10000
T_chp <- seq(from = 100, to = T_n, by = 100)

T_mu1 <- rpois(T_n/100, 10)

T_mu2 <- rpois(T_n/100, 5)

T_sigma <- 1
T_penalty <- 2 * T_sigma * log(T_n)

T_data <- data_gen2D(T_n, T_chp, T_mu1, T_mu2, T_sigma)

########################PELT##################################################
T_timePELT <- OneStep(T_data[1,], T_data[2,], T_penalty, type = 0, func = "FPOP2D")
T_timePELT
#[1] 0.01

###################### FPOP type = 1 #########################################
T_timeFPOPt1 <- OneStep(T_data[1,], T_data[2,], T_penalty, type = 1, func = "FPOP2D")
T_timeFPOPt1
#[1] 0.7

###################### FPOP type = 2 #########################################
T_timeFPOPt2 <- OneStep(T_data[1,], T_data[2,], T_penalty, type = 2, func = "FPOP2D")
T_timeFPOPt2
#[1] 0.15

###############################
#          Сomparison         #
###############################

# PELT #
T_timeFPOPt1/T_timePELT
#[1] 70
T_timeFPOPt2/T_timePELT
#[1] 15
# FPOP #
T_timeFPOPt1/T_timeFPOPt2
#[1] 4.666667

###############################
#          Сonclusion         #
###############################
#PELT is the best method for data with a linear growth n~m
#FPOP(type = 2) is faster than FPOP(type = 1)



###############################
#  data generation n = 10000  #
#     non-linear growth       #
###############################

T1_n <- 10000
m <- floor(sqrt(T1_n)/4) 
# 25

T1_chp <-  c(sort(floor(runif(m - 1,0,T1_n-1))), T_n)

T1_mu1 <- rpois(m,10)

T1_mu2 <- rpois(m, 5)

T_sigma <- 1
T_penalty <- 2 * T_sigma * log(T1_n)


T1_data <- data_gen2D(T1_n, T1_chp, T1_mu1, T1_mu2, T_sigma)

########################PELT##################################################
T1_timePELT <- OneStep(T1_data[1,], T1_data[2,], T_penalty, type = 0, func = "FPOP2D")
T1_timePELT
#[1] 0.08

###################### FPOP type = 1 #########################################
T1_timeFPOPt1 <- OneStep(T1_data[1,], T1_data[2,], T_penalty, type = 1, func = "FPOP2D")
T1_timeFPOPt1
#[1] 8.98

###################### FPOP type = 2 #########################################
T1_timeFPOPt2 <- OneStep(T1_data[1,], T1_data[2,], T_penalty, type = 2, func = "FPOP2D")
T1_timeFPOPt2
#[1] 0.29

###############################
#          Сomparison         #
###############################

# PELT #
T1_timeFPOPt1/T1_timePELT
#[1] 112.25
T1_timeFPOPt2/T1_timePELT
#[1] 3.625
# FPOP #
T1_timeFPOPt1/T1_timeFPOPt2
#[1] 30.96552

###############################
#          Сonclusion         #
###############################
#PELT is the best method for this data
#FPOP(type = 2) is faster than FPOP(type = 1)