
n <- 8
chp <- c(2, 8)
mu1 <- c(2,8)
mu2 <- c(2,1)
sigma <- 0.3

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data

#[,1]      [,2]     [,3]     [,4]     [,5]      [,6]      [,7]      [,8]
#[1,] 1.117346 0.7838427 1.115829 5.150744 4.742782  5.196941 8.2546388 8.1164104
#[2,] 3.055688 3.3488130 2.950066 9.852634 9.995425 10.141932 0.9879179 0.6483118

resPELT<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resPELT




#data generation
n <-100
chp <- c(100)
mu1 <- c(10)
mu2 <- c(5)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data
resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2




# read table
Data_lbl_dif <- readLines(con = 'test.txt', n = -1)

# list
Data_lbl_dif <- strsplit(Data_lbl_dif,split = ' ')

# Matrix  (integer values)
Data_lbl_dif <- sapply(Data_lbl_dif, FUN = function(x) {as.integer(unlist(x))} )

n <- length(Data_lbl_dif)
sum_dif = NULL

for (i in 1: n){
  
  m <- length(Data_lbl_dif[[i]])
  
  sum_dif[i] <- 0
  j <- 2
  while(j <= m){
    sum_dif[i] <- sum_dif[i] + Data_lbl_dif[[i]][j]
    j <- j + 2
  }
}
sum_dif
#[1] 0 1 0 1 2 1 2 1 2 0 1 2 2 1 2 3 2 1 2 3 1 2 3 4 5 4 5 6 5 4 4 2 3 4 4 3 2 2 3 2 3 3 1 2 1 2 3 4 4 3 3 1 1 2 3 0 1 0 1 0 1 2 1 2 1 2 3 4 5 6 7 6 7
#[74] 6 5 4 4 3 4 5 5 3 2 1 2 3 3 4 5 5 3 1 2 3 1 2 2 3 1 1
ma_dif <-max(sum_dif)
ma_dif 
#[1] 7
plot(sum_dif, xlab = "time", ylab = "quantity dif", col = "forestgreen")
lines(sum_dif, col= "forestgreen")
abline(v = chp, lty = 2, col = "grey")




#data generation
n <-1000
chp <- c(50,1000)
mu1 <- c(10,0)
mu2 <- c(5,1)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2




# read table
Data_lbl_dif <- readLines(con = 'test.txt', n = -1)

# list
Data_lbl_dif <- strsplit(Data_lbl_dif,split = ' ')

# Matrix  (integer values)
Data_lbl_dif <- sapply(Data_lbl_dif, FUN = function(x) {as.integer(unlist(x))} )

n <- length(Data_lbl_dif)
sum_dif = NULL

for (i in 1: n){
  
  m <- length(Data_lbl_dif[[i]])
  
  sum_dif[i] <- 0
  j <- 2
  while(j <= m){
    sum_dif[i] <- sum_dif[i] + Data_lbl_dif[[i]][j]
    j <- j + 2
  }
}

max_dif <-max(sum_dif)
max_dif 
#[1] 7
plot(sum_dif, xlab = "time", ylab = "quantity dif", col = "forestgreen")
lines(sum_dif, col= "forestgreen")
abline(v = chp, lty = 2, col = "grey")

