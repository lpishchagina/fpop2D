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
##                                         Test2                                          ##
##The number of candidate changepoints and quantity of exclusions stored over time by FPOP ##
##                            The data withoutchangepoints                                 ##
#############################################################################################
#############################################################################################

############################################################################
############################################################################
##                    One simulation                                      ##
############################################################################
############################################################################

###############################
# data generation n = 1000    #
#     without changepoints    #
###############################

n <-1000
chp <- c(1000)
mu1 <- c(10)
mu2 <- c(5)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

###############################
#         FPOP type = 2       #
###############################

res_1_FPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
res_1_FPOP2

#$changepoints
#[1] 1000

#$means1
#[1]9.983292

#$means2
#[1]4.927654

#$globalCost
#[1]-13.81551

###############################
#     matrix "lbl_excl"       #
###############################

#"lbl_excl"  is the matrix with n rows.
#Each row contains a sequence of pairs of integer numbers for the moment t (t = 1:n).
#Each pair contains two values: candidate of changepoint and quantity of exclusion for this candidate.
## The values of matrix "lbl_excl" is contained in the file "Test 10 n = 1000 Table lbl_nb_exclusion the data without changepoint.txt"

# read matrix
lbl_excl <- readLines(con = 'test.txt', n = -1)
lbl_excl <- strsplit(lbl_excl,split = ' ')
lbl_excl <- sapply(lbl_excl, FUN = function(x) {as.integer(unlist(x))})

##########################################################################
#   The number of candidate changepoints and quantity of exclusions      #
##########################################################################

#"nb_canditates"  is a number of candidate changepoints.
#"nb_exclusions"  is a quantity of exclusions.

nb_exclusions = NULL
nb_canditates = NULL

for (i in 1: length(lbl_excl)){
  nb_exclusions[i] <- 0
  nb_canditates[i] <- length(lbl_excl[[i]])/2
  j <- 2
  while(j <= length(lbl_excl[[i]])){
    nb_exclusions[i] <- nb_exclusions[i] + lbl_excl[[i]][j]
    j <- j + 2
  }
}
#nb_canditates
#nb_exclusions
max_nb_canditates <- max(nb_canditates)
max_nb_canditates
#[1] 12
mean_nb_canditates <- round(mean(nb_canditates))
mean_nb_canditates
#[1] 6
max_nb_exclusions <- max(nb_exclusions)
max_nb_exclusions
#[1] 86
mean_nb_exclusions <- round(mean(nb_exclusions))
mean_nb_exclusions
#[1] 25

###############################
# plot "Number of candidates" #
###############################
plot(nb_canditates, xlab = "Time", ylab = "Number of candidates being considered", col = "red3")
lines(nb_canditates, col= "red3")
abline(v = chp, lty = 2, col = "grey")
abline(h = mean_nb_canditates, lty = 2, col = "grey")
abline(h = max_nb_canditates, lty = 2, col = "grey")

###############################
# plot "Number of exclusions" #
###############################
plot(nb_exclusions, xlab = "Time", ylab = "Number of exclusions", col = "steelblue")
lines(nb_exclusions, col= "steelblue")
abline(v = chp, lty = 2, col = "grey")
abline(h = mean_nb_exclusions, lty = 2, col = "grey")
abline(h = max_nb_exclusions, lty = 2, col = "grey")

################################################################################
################################################################################

###############################
# data generation n = 100     #
#   without changepoints      #
###############################

n1 <-100
chp <- c(100)
mu1 <- c(10)
mu2 <- c(5)
sigma <- 1

penalty <- 2*log(n1)

data1 <- data_gen2D(n1, chp, mu1, mu2, sigma)

###############################
#         FPOP type = 2       #
###############################

res_2_FPOP2<- FPOP2D(data1[1,], data1[2,], penalty, type = 2)
res_2_FPOP2

#$changepoints
#[1] 100

#$means1
#[1] 10.08092

#$means2
#[1] 5.049389

#$globalCost
#[1] -9.21034

###############################
#     matrix "lbl_excl1"      #
###############################

#"lbl_excl1"  is the matrix with n rows.
#Each row contains a sequence of pairs of integer numbers for the moment t (t = 1:n).
#Each pair contains two values: candidate of changepoint and quantity of exclusion for this candidate.
## The values of matrix "lbl_excl1" is contained in the file "Test 10 n = 100 Table lbl_nb_exclusion the data without changepoint.txt"

# read matrix
lbl_excl1 <- readLines(con = 'test.txt', n = -1)
lbl_excl1 <- strsplit(lbl_excl1,split = ' ')
lbl_excl1 <- sapply(lbl_excl1, FUN = function(x) {as.integer(unlist(x))})

##########################################################################
#   The number of candidate changepoints and quantity of exclusions      #
##########################################################################

#"nb_canditates1"  is a number of candidate changepoints.
#"nb_exclusions1"  is a quantity of exclusions.

nb_exclusions1 = NULL
nb_canditates1 = NULL
for (i in 1: length(lbl_excl1)){
  nb_exclusions1[i] <- 0
  nb_canditates1[i] <- length(lbl_excl1[[i]])/2
  j <- 2
  while(j <= length(lbl_excl1[[i]])){
    nb_exclusions1[i] <- nb_exclusions1[i] + lbl_excl1[[i]][j]
    j <- j + 2
  }
}
#nb_canditates1
#nb_exclusions1
max_nb_canditates1 <- max(nb_canditates1)
max_nb_canditates1
#[1] 6
mean_nb_canditates1 <- round(mean(nb_canditates1))
mean_nb_canditates1
#[1] 3
max_nb_exclusions1 <- max(nb_exclusions1)
max_nb_exclusions1
#[1] 20
mean_nb_exclusions1 <- round(mean(nb_exclusions1))
mean_nb_exclusions1
#[1] 7

###############################
# plot "Number of candidates" #
###############################
plot(nb_canditates1, xlab = "Time", ylab = "Number of candidates being considered", col = "red3")
lines(nb_canditates1, col= "red3")
abline(v = chp, lty = 2, col = "grey")
abline(h = mean_nb_canditates1, lty = 2, col = "grey")
abline(h = max_nb_canditates1, lty = 2, col = "grey")

###############################
# plot "Number of exclusions" #
###############################
plot(nb_exclusions1, xlab = "Time", ylab = "Number of exclusions", col = "steelblue")
lines(nb_exclusions1, col= "steelblue")
abline(v = chp, lty = 2, col = "grey")
abline(h = mean_nb_exclusions1, lty = 2, col = "grey")
abline(h = max_nb_exclusions1, lty = 2, col = "grey")


############################################################################
############################################################################
##                      Iteration                                         ##
############################################################################
############################################################################

nb_Iter = 10
n3 <-1000
chp <- c(1000)
mu1 <- c(10)
mu2 <- c(5)
sigma <- 1

penalty <- 2*log(n3)

matrix_candidates <- matrix(0, nrow = n3, ncol = nb_Iter)
matrix_exclusions <- matrix(0, nrow = n3, ncol = nb_Iter)

k = 1
while (k <= nb_Iter){
  # data generation n = 1000
  data3 <- data_gen2D(n3, chp, mu1, mu2, sigma)
  # FPOP type = 2
  res_3_FPOP2<- FPOP2D(data3[1,], data3[2,], penalty, type = 2)
  # Matrix(integer values)
  lbl_excl3 <- readLines(con = 'test.txt', n = -1)
  lbl_excl3 <- strsplit(lbl_excl3,split = ' ')
  lbl_excl3 <- sapply(lbl_excl3, FUN = function(x) {as.integer(unlist(x))})
  
  #number of canditates and exclusions
  nb_exclusions3 = NULL
  nb_canditates3 = NULL
  
  for (i in 1:length(lbl_excl3)){
    nb_exclusions3[i] = 0
    nb_canditates3[i] = length(lbl_excl3[[i]])/2
    j = 2
    while(j <= length(lbl_excl3[[i]])){
      nb_exclusions3[i] = nb_exclusions3[i] + lbl_excl3[[i]][j]
      j = j + 2
    } 
  }
  matrix_candidates[,k] = nb_canditates3
  matrix_exclusions[,k] = nb_exclusions3
  k = k + 1
}
#matrix_candidates
#matrix_exclusions

for (i in 1:length(lbl_excl3)){
  mean_matrix_candidates[i] = round(mean(matrix_candidates[i,]))
  mean_matrix_exclusions[i] = round(mean(matrix_exclusions[i]))
}
#mean_matrix_candidates
#mean_matrix_exclusions


max_mean_matrix_candidates <- max(mean_matrix_candidates)
max_mean_matrix_candidates
#[1] 9
mean_mean_matrix_candidates <- round(mean(mean_matrix_candidates))
mean_mean_matrix_candidates
#[1] 6
max_mean_matrix_exclusions <- max(mean_matrix_exclusions)
max_mean_matrix_exclusions
#[1] 89
mean_mean_matrix_exclusions <- round(mean(mean_matrix_exclusions))
mean_mean_matrix_exclusions
#[1] 23

###############################
# plot "Number of candidates" #
###############################
plot(mean_matrix_candidates, xlab = "Time", ylab = "Number of candidates(mean) being considered", col = "red3")
lines(mean_matrix_candidates, col= "red3")
abline(v = chp, lty = 2, col = "grey")

###############################
# plot "Number of exclusions" #
###############################
plot(mean_matrix_exclusions, xlab = "Time", ylab = "Number(mean) of exclusions", col = "steelblue")
lines(mean_matrix_exclusions, col= "steelblue")
abline(v = chp, lty = 2, col = "grey")


#############################################################################################
#############################################################################################
##                                        End Test 2                                       ##
#############################################################################################
#############################################################################################