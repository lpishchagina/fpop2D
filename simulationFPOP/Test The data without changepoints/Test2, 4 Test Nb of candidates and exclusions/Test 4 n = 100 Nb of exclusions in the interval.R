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
##                                         Test4                                           ##
##                 The quantity of exclusions stored over time                             ##
##                            The data withoutchangepoints                                 ##
#############################################################################################
#############################################################################################


###############################
#     matrix "lbl_excl"       #
###############################

#"lbl_excl"  is the matrix with n rows.
#Each row contains a sequence of pairs of integer numbers for the moment t (t = 1:n).
#Each pair contains two values: candidate of changepoint and quantity of exclusion for this candidate.
## The values of matrix "lbl_excl" is contained in the papier "Test The data without changepoints".

# read matrix
lbl_excl <- readLines(con = 'test.txt', n = -1)
lbl_excl <- strsplit(lbl_excl,split = ' ')
lbl_excl <- sapply(lbl_excl, FUN = function(x) {as.integer(unlist(x))})

###############################
# matrix "matrix_exclusion"   #
###############################

#"matrix_exclusion"  is the matrix with  "length(lbl_excl) - 1" rows and "length(lbl_excl)" columns.
#Each position contains the number of exclusions for the given label(the row number) at the time t(the column number).
#If the element does not exist, position and value "NA".
matrix_exclusion <- matrix(NA,nrow = length(lbl_excl) - 1, ncol= length(lbl_excl))

for (i in 2:length(lbl_excl)){
  j<- 1
  while (j <= length(lbl_excl[[i]])){
    matrix_exclusion[lbl_excl[[i]][j],i] <- lbl_excl[[i]][j+1]
    j <- j+2
  }
}


###############################
#     list "list_exclusion"   #
###############################

#"list_exclusion"  is the list with  "length(lbl_excl) - 1" list elements.
#Each list "list_exclusion[[label]]" contains the number of exclusions for the given label.
#If label do not have exclusions this list have  a length = 0.

list_exclusion <-lapply(seq_len(nrow(matrix_exclusion)), function(i) matrix_exclusion[i,])
for (i in  1:length(list_exclusion)){
   list_exclusion [[i]] = list_exclusion [[i]][!is.na(list_exclusion [[i]])]
}

###############################
#     max_quantity_exclusion  #
#     max_length_interval     #
###############################
# max_quantity_exclusion is the range of the number of exclusions 
# max_length_interval is the range of  the interval length 


max_quantity_exclusion = 0
# 6 for 100; 12 for 1000

max_length_interval = 0
# 33 for 100; 12 for 186
for (i in  1:length(list_exclusion)){
  if (length(list_exclusion [[i]]) != 0){
    max_length_interval = max(max_length_interval,length(list_exclusion[[i]]))
    max_quantity_exclusion = max(max_quantity_exclusion, list_exclusion[[i]])
  }
}
max_quantity_exclusion
max_length_interval
############################################
# plot "Number of exclusions for interval" #
############################################
#colors of plots
palet = colorRampPalette(c("grey","steelblue","purple4")) 
colors = palet(length(list_exclusion))
#we define empty plot
plot(c(0, max_length_interval), c(0,max_quantity_exclusion),main = "The number of exclusion in the interval", xlab = "Time interval", ylab =  "Number of exclusions", type = "n")
#Plots for all labels
t  = c(1:max_length_interval)
for (i in  1:length(list_exclusion)){
  if (length(list_exclusion [[i]]) != 0){
    y <- unlist(list_exclusion [[i]])
    y <- jitter(y,0.8)
    points(c(y,0), col = colors[i])
    lines(c(y,0), col = colors[i])
  }
}

#calculation for the mean plot

#initialization of list
mean_plot = list(NULL) 
n_plot = 0
for (i in 1:max_length_interval) {
  mean_plot[i] = 0
}
 

#sum calculation for t
for (i in 1:length(list_exclusion)){
  if (length(list_exclusion [[i]]) != 0){
     n_plot = n_plot+1
    for (j in 1:length(list_exclusion[[i]])){
      mean_plot[[j]]= mean_plot[[j]] + list_exclusion[[i]][j]
    }
  }
}
#value of mean for t
for (i in 1:max_length_interval) {
  mean_plot[[i]] = mean_plot[[i]]/n_plot
}
#list -> vector
v_mean_plot <- unlist(mean_plot)

#Plots for all labels
points(c(v_mean_plot, 0),col = "red3")
lines(c(v_mean_plot, 0),col = "red3", lwd = 3)

############################### legend ########################################
location = "topright"
labels = c("Mean number of exclusions")
colors = c("red3")
legend(location, labels, fill = colors)

v_mean_plot

#############################################################################################
#############################################################################################
##                                        End Test 4                                       ##
#############################################################################################
#############################################################################################
