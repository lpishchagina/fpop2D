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
## Test9: Time complexity (the plot of the mean running time with respect to data length). ##
##                           non-linear growth                                             ##
#############################################################################################
#############################################################################################

# Object: We show the plot of the mean running time with respect to data length.
#Run T9_nRep times OptPart, PELT, FPOP2D(type = 1) and FPOP2D(tape = 2) algorithms of each value of the vector_n vector of length T9_nStep.
# growth m = sqrt(n)/4) 

###############################
#    data length genetation   #
###############################
T9_nStep <- 10  
T9_vect_n <- seq(from = 1000, to = 10000, length.out = T9_nStep)
T9_vect_n 
#[1]  1000  2000  3000  4000  5000  6000  7000  8000  9000 10000

###############################
#      m genetation           #
###############################
T9_vect_m <- floor(sqrt(T9_vect_n)/4) 
# [1]  7 11 13 15 17 19 20 22 23 25

T9_nRep <- 10

###############################
#    tables initialisation    #
###############################

###################### OptPart ###############################################
T9_resOptPart <- data.frame(matrix(0, T9_nStep, T9_nRep + 1))
colnames(T9_resOptPart) <- c("n", paste0("Rep", 1:T8_nRep))

###################### PELT ##################################################
T9_resPELT <- data.frame(matrix(0, T9_nStep, T9_nRep + 1))
colnames(T9_resPELT) <- c("n", paste0("Rep", 1:T9_nRep))

###################### FPOP type = 1 #########################################
T9_resFPOP2Dt1 <- data.frame(matrix(0, T9_nStep, T9_nRep + 1))
colnames(T9_resFPOP2Dt1) <- c("n", paste0("Rep", 1:T9_nRep))

###################### FPOP type = 2 #########################################
T9_resFPOP2Dt2 <- data.frame(matrix(0, T9_nStep, T9_nRep + 1))
colnames(T9_resFPOP2Dt2) <- c("n", paste0("Rep", 1:T9_nRep))

###############################
#       tables filling        #
###############################

T9_sigma <- 1

for(i in 1:length(T9_vect_n)){
  T9_chp <- c(sort(floor(runif(T9_vect_m[i] - 1,0,T9_vect_n[i]-1))), T9_vect_n[i])
  T9_mu1 <- rpois(T9_vect_m[i], 10)
  T9_mu2 <- rpois(T9_vect_m[i], 5)
  T9_penalty <- 2 * T9_sigma * log(T9_vect_n[i])
  
  T9_data <- data_gen2D(T9_vect_n[i], T9_chp, T9_mu1, T9_mu2, T9_sigma)
  
  T9_resOptPart[i,] <- c(T9_vect_n[i], replicate(T9_nRep, OneStep(T9_data[1,], T9_data[2,], T9_penalty, type = "null", func = "OptPart2D")))
  T9_resPELT[i,] <- c(T9_vect_n[i], replicate(T9_nRep, OneStep(T9_data[1,], T9_data[2,], T9_penalty, type = "pruning", func = "OptPart2D")))
  T9_resFPOPt1[i,] <- c(T9_vect_n[i], replicate(T9_nRep, OneStep(T9_data[1,], T9_data[2,], T9_penalty, type = 1, func = "FPOP2D")))
  T9_resFPOPt2[i,] <- c(T9_vect_n[i], replicate(T9_nRep, OneStep(T9_data[1,], T9_data[2,], T9_penalty, type = 2, func = "FPOP2D")))
}

###################### OptPart ###############################################
T9_resOptPart
#    

###################### PELT ##################################################
T9_resPELT
# 

###################### FPOP type = 1 #########################################
T9_resFPOP2Dt1 

###################### FPOP type = 2 #########################################
T9_resFPOP2Dt2 



###############################
#   mean time in second       #
###############################

###################### OptPart ###############################################
T9_mean_OptPart <- rowMeans(T9_resOptPart[,-1])
#

plot(T9_vect_n, T9_mean_OptPart, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of Optimal Partitioning",  col = "red3")
lines(T9_vect_n, T9_mean_OptPart,  col = "red3")

###################### PELT ##################################################
T9_mean_PELT <- rowMeans(T9_resPELT[,-1])
#
plot(T9_vect_n, T9_mean_PELT, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of PELT", col = "steelblue")
lines(T9_vect_n, T9_mean_PELT, col ="steelblue")

###################### FPOP type = 1 #########################################
T9_mean_FPOPt1 <- rowMeans(T9_resFPOPt1[,-1])
#
plot(T9_vect_n, T9_mean_FPOPt1, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of FPOP(type = 1)", col = "purple4")
lines(T9_vect_n, T9_mean_FPOPt1, col = "purple4")

###################### FPOP type = 2 #########################################
T9_mean_FPOPt2 <- rowMeans(T9_resFPOPt2[,-1])
#
plot(T9_vect_n, T9_mean_FPOPt2, xlab = "data length", ylab = "mean time in second",  main = "Time complexity of FPOP(type = 2)", col = "forestgreen")
lines(T9_vect_n, T9_mean_PELT, col = "forestgreen")


###############################
#  plots: mean time in second #
###############################

######################  plot OptPart #########################################
plot(T9_vect_n, T9_mean_OptPart, xlab = "data length", ylab = "mean time in second",  main = "Time complexity", col = "red3")
lines(T9_vect_n, T9_mean_OptPart, col = "red3")

###################### plot PELT ##############################################
points(T9_vect_n, T9_mean_PELT, col = "steelblue")
lines(T9_vect_n, T9_mean_PELT, col = "steelblue")

###################### plot FPOP type = 1 #####################################
points(T9_vect_n, T9_mean_FPOPt1, col = "purple4")
lines(T9_vect_n, T9_mean_PELT, col = "purple4")

###################### plot FPOP type = 2 #####################################
points(T9_vect_n, T9_mean_FPOPt2, col = "forestgreen")
lines(T9_vect_n, T9_mean_FPOPt2, col = "forestgreen")



############################### legend ########################################
location = "topleft"
labels = c("Optimal Partitioning", "PELT", "FPOP(type = 1)",  "FPOP(type = 2)")
colors = c("red3", "steelblue", "purple4", "forestgreen")
legend(location, labels, fill = colors)

#############################################################################################
#############################################################################################
##                                        End Test9                                        ##
#############################################################################################
#############################################################################################