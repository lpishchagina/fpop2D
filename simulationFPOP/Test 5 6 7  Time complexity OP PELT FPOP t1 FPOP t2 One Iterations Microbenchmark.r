############################################################################
############################################################################
##                    package instalation                                 ##
############################################################################
############################################################################

devtools::install_github("lpishchagina/fpop2D")
library(fpop2D)
devtools::install_github("lpishchagina/OptPartitioning2D")
library(OptPartitioning2D)

############################################################################
############################################################################
##                         Preprocessing                                  ##
############################################################################
############################################################################

###############################
#       Function OneStep      #
###############################

#Function OneStep  returns the execution time of a given algorithm

OneStep <- function(data1, data2, penalty, type, func = "OptPart2D")
{
  if(type == "null"){t <- system.time(OptPart2D(data1, data2, penalty, type = "null"))[[1]]}
  if(type == "pruning"){t <- system.time(OptPart2D(data1, data2, penalty, type = "pruning"))[[1]]}
  if (type == 1){t <- system.time(FPOP2D(data1, data2, penalty, type = 1))[[1]]}
  if (type == 2){t <- system.time(FPOP2D(data1, data2, penalty, type = 2))[[1]]}
  return(t)
}


#############################################################################################
#############################################################################################
##                        Test5: One time complexity test                                  ##
#############################################################################################
#############################################################################################

# Object: We compare the time complexity of OP, PELT, FPOP(type = 1), FPOP(type = 2) for one simulation.
#

###############################
#  data generation n = 5000   #
###############################

T5_n <- 5000
T5_chp <- seq(from = 100, to = T5_n, by = 100)
T5_chp
T5_mu1 <- rpois(T5_n/100, 10)
T5_mu1
T5_mu2 <- rpois(T5_n/100, 5)
T5_mu2
T5_sigma <- 1
T5_penalty <- 2 * T5_sigma * log(T5_n)

T5_data <- data_gen2D(T5_n, T5_chp, T5_mu1, T5_mu2, T5_sigma)


###############################
#    One time complexity      #
###############################

###################### OptPart ##############################################
T5_timeOptPart <- OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "null", func = "OptPart2D")
T5_timeOptPart
#

###################### PELT #################################################
T5_timePELT <- OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "pruning", func = "OptPart2D")
T5_timePELT
#

###################### FPOP type = 1 #########################################
T5_timeFPOPt1 <- OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 1, func = "FPOP2D")
T5_timeFPOPt1
#

###################### FPOP type = 2 #########################################
T5_timeFPOPt2 <- OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 2, func = "FPOP2D")
T5_timeFPOPt2
#

###############################
#          Сomparison         #
###############################

# OptPart #
T5_timeOptPart/T5_timePELT
#

T5_timeOptPart/T5_timeFPOPt1
#
T5_timeOptPart/T5_timeFPOPt2
#

# PELT #
T5_timePELT/T5_timeFPOPt1
#
T5_timePELT/T5_timeFPOPt2
#

# FPOP #

T5_timeFPOPt2/T5_timeFPOPt1
# 

###############################
#          Сonclusion         #
###############################
#

#############################################################################################
#############################################################################################
##                                        End Test5                                        ##
#############################################################################################
#############################################################################################


#############################################################################################
#############################################################################################
##                        Test6: Time complexity test. Iteration                           ##
#############################################################################################
#############################################################################################

# Object: We compare the time complexity of OP, PELT, FPOP(type = 1), FPOP(type = 2) for T6_nStep itetations.
# We use data "T5_data"

T6_nStep <- 10
T6_timeOptPart <- 0
T6_timePELT <- 0
T6_timeFPOPt1 <- 0
T6_timeFPOPt2<- 0
for(i in 1:T6_nStep){T6_timeOptPart <- T6_timeOptPart + OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "null",func = "OptPart2D")}
for(i in 1:T6_nStep){T6_timePELT <- T6_timePELT + OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "pruning", func = "OptPart2D")}
for(i in 1:T6_nStep){T6_timeFPOPt1<- T6_timeFPOPt1 + OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 1, func = "FPOP2D")}
for(i in 1:T6_nStep){T6_timeFPOPt2<- T6_timeFPOPt2 + OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 2, func = "FPOP2D")}

###############################
#          Сomparison         #
###############################

# OptPart #
T6_timeOptPart/T6_timePELT
#

T6_timeOptPart/T6_timeFPOPt1
#

T6_timeOptPart/T6_timeFPOPt2
#

# PELT #
T6_timePELT/T6_timeFPOPt1
#
T6_timePELT/T6_timeFPOPt2
#

# FPOP #

T6_timeFPOPt2/T6_timeFPOPt1
# 

###############################
#          Сonclusion         #
###############################
#
#############################################################################################
#############################################################################################
##                                        End Test6                                        ##
#############################################################################################
#############################################################################################



#############################################################################################
#############################################################################################
##                                  Test7: microbenchmark                                  ##
#############################################################################################
#############################################################################################

############################################################################
############################################################################
##                    package instalation                                 ##
############################################################################
############################################################################

library(microbenchmark)
library("ggplot2")

###############################
#  data generation n = 10000  #
###############################

T7_n <- 10000
T7_chp <- seq(from = 100, to = T7_n, by = 100)
T7_chp
T7_mu1 <- rpois(T7_n/100, 10)
T7_mu1
T7_mu2 <- rpois(T7_n/100, 5)
T7_mu2
T7_sigma <- 1
T7_penalty <- 2 * T7_sigma * log(T7_n)

T7_data <- data_gen2D(T7_n, T7_chp, T7_mu1, T7_mu2, T7_sigma)

###############################
#  microbenchmark n = 5000    #
###############################

############OP PELT###################
T7_resT5_OPPELT <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "pruning", func = "OptPart2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "null", func = "OptPart2D"),  times = 50)
T7_resT5_OPPELT
autoplot(T7_resT5_OPPELT)

############OP FPOP(type = 1) ###################
T7_resT5_OPFPOPt1 <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "null", func = "OptPart2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 1, func = "FPOP2D"),  times = 50)
T7_resT5_OPFPOPt1
autoplot(T7_resT5_OPFPOPt1)

############OP FPOP(type = 2) ###################
T7_resT5_OPFPOPt2 <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "null", func = "OptPart2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT5_OPFPOPt2
autoplot(T7_resT5_OPFPOPt2)

############PELT FPOP(type = 1) ###################
T7_resT5_PELTFPOPt1 <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "pruning", func = "OptPart2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 1, func = "FPOP2D"),  times = 50)
T7_resT5_PELTFPOPt1 
autoplot(T7_resT5_PELTFPOPt1)

############PELT FPOP(type = 2) ###################
T7_resT5_PELTFPOPt2 <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = "pruning", func = "OptPart2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT5_PELTFPOPt2
autoplot(T7_resT5_PELTFPOPt2)

############FPOP(type = 1) FPOP(type = 2)###################
T7_resT5_FPOPt12 <- microbenchmark( OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 1, func = "FPOP2D"), OneStep(T5_data[1,], T5_data[2,], T5_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT5_FPOPt12
autoplot(T7_resT5_FPOPt12)

###############################
#  microbenchmark n = 10000   #
###############################

############OP PELT###################
T7_resT7_OPPELT <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "pruning", func = "OptPart2D"), OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "null", func = "OptPart2D"),  times = 50)
T7_resT7_OPPELT
autoplot(T7_resT5_OPPELT)

############OP FPOP(type = 1) ###################
T7_resT7_OPFPOPt1 <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "null", func = "OptPart2D"), OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = 1, func = "FPOP2D"),  times = 50)
T7_resT7_OPFPOPt1
autoplot(T7_resT5_OPFPOPt1)

############OP FPOP(type = 2) ###################
T7_resT7_OPFPOPt2 <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "null", func = "OptPart2D"), OneStep(T5_data[1,], T7_data[2,], T7_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT7_OPFPOPt2
autoplot(T7_resT5_OPFPOPt2)

############PELT FPOP(type = 1) ###################
T7_resT7_PELTFPOPt1 <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "pruning", func = "OptPart2D"), OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = 1, func = "FPOP2D"),  times = 50)
T7_resT7_PELTFPOPt1 
autoplot(T7_resT5_PELTFPOPt1)

############PELT FPOP(type = 2) ###################
T7_resT7_PELTFPOPt2 <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = "pruning", func = "OptPart2D"), OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT7_PELTFPOPt2
autoplot(T7_resT7_PELTFPOPt2)

############FPOP(type = 1) FPOP(type = 2)###################
T7_resT7_FPOPt12 <- microbenchmark( OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = 1, func = "FPOP2D"), OneStep(T7_data[1,], T7_data[2,], T7_penalty, type = 2, func = "FPOP2D"),  times = 50)
T7_resT5_FPOPt12
autoplot(T7_resT7_FPOPt12)




###############################
#          Сonclusion         #
###############################
#
#############################################################################################
#############################################################################################
##                                        End Test7                                        ##
#############################################################################################
#############################################################################################