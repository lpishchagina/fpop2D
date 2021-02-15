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
## Test8: Time complexity (the plot of the mean running time with respect to data length). ##
##                            linear growth n~k                                            ##
#############################################################################################
#############################################################################################

# Object: We show the plot of the mean running time with respect to data length.
#Run T8_nRep times OptPart, PELT, FPOP2D(type = 1) and FPOP2D(tape = 2) algorithms of each value of the vector_n vector of length T8_nStep.
#linear growth n~k.

###############################
#    data length genetation   #
###############################
T8_nStep <- 10  
T8_vect_n <- seq(from = 1000, to = 10000, length.out = T8_nStep)
T8_vect_n 
#[1]  1000  2000  3000  4000  5000  6000  7000  8000  9000 10000
T8_nRep <- 10


###############################
#    tables initialisation    #
###############################

###################### OptPart ###############################################
T8_resOptPart <- data.frame(matrix(0, T8_nStep, T8_nRep + 1))
colnames(T8_resOptPart) <- c("n", paste0("Rep", 1:T8_nRep))

###################### PELT ##################################################
T8_resPELT <- data.frame(matrix(0, T8_nStep, T8_nRep + 1))
colnames(T8_resPELT) <- c("n", paste0("Rep", 1:T8_nRep))

###################### FPOP type = 1 #########################################
T8_resFPOP2Dt1 <- data.frame(matrix(0, T8_nStep, T8_nRep + 1))
colnames(T8_resFPOP2Dt1) <- c("n", paste0("Rep", 1:T8_nRep))

###################### FPOP type = 2 #########################################
T8_resFPOP2Dt2 <- data.frame(matrix(0, T8_nStep, T8_nRep + 1))
colnames(T8_resFPOP2Dt2) <- c("n", paste0("Rep", 1:T8_nRep))


###############################
#       tables filling        #
###############################

T8_sigma <- 1

for(i in 1:length(T8_vect_n)){
  T8_chp <- seq(from = 100, to = T8_vect_n[i], by = 100)
  T8_mu1 <- rpois(T8_vect_n[i]/100, 10)
  T8_mu2 <- rpois(T8_vect_n[i]/100, 5)
  T8_penalty <- 2 * T8_sigma * log(T8_vect_n[i])
  
  T8_data <- data_gen2D(T8_vect_n[i], T8_chp, T8_mu1, T8_mu2, T8_sigma)
  
  T8_resOptPart[i,] <- c(T8_vect_n[i], replicate(T8_nRep, OneStep(T8_data[1,], T8_data[2,], T8_penalty, type = "null",func = "OptPart2D")))
  T8_resPELT[i,] <- c(T8_vect_n[i], replicate(T8_nRep, OneStep(T8_data[1,], T8_data[2,], T8_penalty, type = "pruning",func = "OptPart2D")))
  T8_resFPOPt1[i,] <- c(T8_vect_n[i], replicate(T8_nRep, OneStep(T8_data[1,], T8_data[2,], T8_penalty, type = 1, func = "FPOP2D")))
  T8_resFPOPt2[i,] <- c(T8_vect_n[i], replicate(T8_nRep, OneStep(T8_data[1,], T8_data[2,], T8_penalty, type = 2, func = "FPOP2D")))
}

###################### OptPart ###############################################
T8_resOptPart
#    

###################### PELT ##################################################
T8_resPELT
# 

###################### FPOP type = 1 #########################################
T8_resFPOP2Dt1 

###################### FPOP type = 2 #########################################
T8_resFPOP2Dt2 



###############################
#   mean time in second       #
###############################

###################### OptPart ###############################################
T8_mean_OptPart <- rowMeans(T8_resOptPart[,-1])
#

plot(T8_vect_n, T8_mean_OptPart, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of Optimal Partitioning",  col = "red3")
lines(T8_vect_n, T8_mean_OptPart,  col = "red3")

###################### PELT ##################################################
T8_mean_PELT <- rowMeans(T8_resPELT[,-1])
#
plot(T8_vect_n, T8_mean_PELT, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of PELT", col = "steelblue")
lines(T8_vect_n, T8_mean_PELT, col="steelblue")

###################### FPOP type = 1 #########################################
T8_mean_FPOPt1 <- rowMeans(T8_resFPOPt1[,-1])
#
plot(T8_vect_n, T8_mean_FPOPt1, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of FPOP(type = 1)", col = "purple4")
lines(T8_vect_n, T8_mean_FPOPt1, col= "purple4")

###################### FPOP type = 2 #########################################
T8_mean_FPOPt2 <- rowMeans(T8_resFPOPt2[,-1])
#
plot(T8_vect_n, T8_mean_FPOPt2, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of FPOP(type = 2)", col = "forestgreen")
lines(T8_vect_n, T8_mean_PELT, col= "forestgreen")


###############################
#  plots: mean time in second #
###############################

######################  plot OptPart #########################################
plot(T8_vect_n, T8_mean_OptPart, xlab = "data length", ylab = "mean time in second",  main = "Time complexity", col="red3")
lines(T8_vect_n, T8_mean_OptPart, col="red3")

###################### plot PELT ##############################################
points(T8_vect_n, T8_mean_PELT, col = "steelblue")
lines(T8_vect_n, T8_mean_PELT, col = "steelblue")

###################### plot FPOP type = 1 #####################################
points(T8_vect_n, T8_mean_FPOPt1, col = "purple4")
lines(T8_vect_n, T8_mean_PELT, col = "purple4")

###################### plot FPOP type = 2 #####################################
points(T8_vect_n, T8_mean_FPOPt2, col = "forestgreen")
lines(T8_vect_n, T8_mean_FPOPt2, col = "forestgreen")



############################### legend ########################################
location = "topleft"
labels = c("Optimal Partitioning", "PELT", "FPOP(type = 1)",  "FPOP(type = 2)")
colors = c("red3", "steelblue", "purple4", "forestgreen")
legend(location, labels, fill = colors)

#############################################################################################
#############################################################################################
##                                        End Test8                                        ##
#############################################################################################
#############################################################################################