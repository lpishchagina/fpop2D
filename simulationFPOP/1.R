n <-50
chp <- c(3,6,10,20,50)
mu1 <- c(1, 5,8,0,7)
mu2 <- c(3, 10,1,6,0)
sigma <- 0.3

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data
resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2

n <-50
chp <- c(50)
mu1 <- c(10)
mu2 <- c(3)
sigma <- 1

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data
resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2

n <-8
chp <- c(3,6,8)
mu1 <- c(1, 5,8)
mu2 <- c(3, 10,1)
sigma <- 0.3

penalty <- 2*log(n)

data <- data_gen2D(n, chp, mu1, mu2, sigma)

data
resFPOP2<- FPOP2D(data[1,], data[2,], penalty, type = 2)
resFPOP2
