n <- 100
a <- 2
b <- 6
N<- 10000

conf_level <- 0.95
samp <- runif(n, a,b)
true_sd <- sqrt((b-a)^2 / 12)
crit_z <- qnorm(0.975)
lower_bound <- mean(samp) - ((crit_z * true_sd)/ sqrt(n))
upper_bound <-  mean(samp) + ((crit_z * true_sd)/ sqrt(n))

#variance is unknown
samp <- runif(n, a,b)
samp_sd <- sd(samp)
crit_t <- qt(1- (1-conf_level)/2, df = n-1)
lower_bound <- mean(samp) - ((crit_t * sd(samp))/ sqrt(n))
upper_bound <- mean(samp) + ((crit_t * sd(samp))/ sqrt(n))

#part c 

pop_mean <- mean((a + b)/ 2)
count_z <- vector(length=N)
count_t <- vector(length=N)
for(i in 1:N){
  
  samp <- runif(n, a, b)
  
  lower_bound_z <- mean(samp) - ((crit_z * true_sd)/ sqrt(n))
  upper_bound_z <-  mean(samp) + ((crit_z * true_sd)/ sqrt(n))
  
  
  lower_bound_t <- mean(samp) - ((crit_t * sd(samp))/ sqrt(n))
  upper_bound_t <- mean(samp) + ((crit_t * sd(samp))/ sqrt(n))
  
  if(pop_mean < upper_bound_z && pop_mean > lower_bound_z)
    count_z[i] = 1
  
  if(pop_mean < upper_bound_t && pop_mean > lower_bound_t)
    count_t[i] = 1
  
}

sum(count_z)/N
sum(count_t)/N

