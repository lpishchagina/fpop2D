#Examples


n <- 8
chp <- c(3,6,8)
mu1 <- c(1, 5,8)
mu2 <- c(3, 10,1)
sigma <- 0.3

penalty <- 2*log(n)
data1 <- data_gen2D(n, chp, mu1, mu2, sigma)
data1



resFPOP1<- FPOP2D(data1[1,], data1[2,], penalty, type= 1)
resFPOP1
