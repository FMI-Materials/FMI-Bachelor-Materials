head(rock)  # display the first 6 observations
attach(rock)

h1 <- hist(area,
           main="Histogram for area of pores space",
           xlab="Area of pores space (px)",
           freq = F,
           breaks=13)
t <- seq(1000, 13000, 0.1)
lines(t, dnorm(t, mean(area), 1850), col="blue")

plot(density(area), main = "Density plot for area of pores space")
polygon(density(area), col="gray")

boxplot(area, main="Area of pores space", sub = paste("No outliner rows"));

h2 <- hist(peri,
           main="Histogram for perimeter of pores space",
           xlab="Perimeter of pores space (px)",
           breaks=13)

plot(density(peri), main="Density plot of perimeter")
polygon(density(peri), col="gray")

boxplot(peri, main="Perimeter in pixels", sub = paste("No outliner rows"));

h3 <- hist(shape,
           main="Histogram for shape of pores space",
           xlab="Perimeter of pores space (px)",
           ylab="Frequency", 
           border="blue",
           breaks=13)
lines(seq(0, 1, by=0.001), dnorm(seq(0, 1, by=0.001), mean(shape), sd(shape)/3.4), col="blue")

plot(density(shape), main="Density plot for shape")
polygon(density(shape), col="gray")

outliers <- boxplot(shape,
                    main="Shape - Perimeter / sqrt (area)", 
                    sub = paste("Outliner rows: ", paste(boxplot.stats(shape)$out, collapse=' and ')
                    ));
# We will check if the ouliers should be taken into consideration. The variables with a large shape of pores, but with a lower 
# permeability will be extracted from the data. Further investigations must be conducted on this variables(for this it must be 
# taken into consideration others parameters, like the nature of the rock and how the pores are arranged and if they are
# connected) and then decided how they influence the fenomen of permeability.


#Checking the three outlier's permeability values, we observed that two of them have the permeability 1300, while the other one
#coresponds with a permeability of 100. So we decided to get rid of it because we consider it will badly affect our model.
rock_initial <- rock
rock <- rock[-c(38),]

h4 <- hist(perm,
           main="Histogram for permeability",
           xlab="Permeability",
           ylab="Frequency", 
           border="blue",
           breaks=13)

plot(density(perm), main="Density plot for permeability")
polygon(density(perm), col="gray")

boxplot(rock_initial$perm, main="Permeability in mili-Darcies", sub = paste("No outliner rows"));

scatter.smooth(x=shape, y = perm, xlab = "Forma", ylab = "Permeabilitatea" , main = " Forma porilor ~ Permeabilitatea");

scatter.smooth(x=shape, y = perm, xlab = "Forma", ylab = "Permeabilitatea" , main = " Forma porilor ~ Permeabilitatea");

library(e1071)
par(mfrow=c(1, 2))
plot(density(shape), main="Density Ploot: Shape", ylab="Frequency"
     , sub= paste("Skewness:", round(e1071::skewness(shape), 2)))
polygon(density(shape), col="red")
plot(density(perm), main="Density Ploot: Permeabillity", ylab="Frequency"
     , sub= paste("Skewness:", round(e1071::skewness(perm), 2)))
polygon(density(perm), col="red")

cor(shape, perm)

linearMod <- lm(perm ~ shape, data=rock) #build linear regression model
print(linearMod)

summary(linearMod)
AIC(linearMod)


modelSummary <- summary(linearMod) #capture model summary as an object
modelCoefficients <- modelSummary$coefficients # model coefficients
beta_estimate <- modelCoefficients["shape", "Estimate"] # get beta estimate for shape
standard_error <- modelCoefficients["shape", "Std. Error"] # gets standard errror for shape
t_value <- beta_estimate/standard_error # calculate t-statistic
p_value <- 2*pt(-abs(t_value), df=nrow(rock)-ncol(rock)) #calculate the p-value
f_statistic <- linearMod$fstatistic[1] # fstatistic
f <- summary(linearMod)$fstatistic 
model_p <- pf(f[1], f[2], f[3], lower=FALSE)

AIC(linearMod)
BIC(linearMod)

trainingRowIndex <- sample(1:nrow(rock), 0.8*nrow(rock))
trainingData <- rock[trainingRowIndex, ]
testData <- rock[-trainingRowIndex, ]

lmMod <- lm(perm ~ shape, data=trainingData)
permPrediction <- predict(lmMod, testData)
summary(lmMod)
AIC(lmMod)

summary(lmMod)
AIC(lmMod)

actuals_preds <- data.frame(cbind(actuals=testData$perm, predicteds = permPrediction))
correlation_accuracy <- cor(actuals_preds, )
correlation_accuracy

min_max_accuracy <- mean(apply(actuals_preds, 1, min) / apply(actuals_preds, 1, max))  
mape <- mean(abs((actuals_preds$predicteds - actuals_preds$actuals)) / actuals_preds$actuals)

library(tidyverse)
library(caret)

trainingData.control <- trainControl(method = "cv", number = 10)

model <- train(perm ~ shape, data = rock, method = "lm",
               trControl = trainingData.control)

print(model)

new <- data.frame(norm = rnorm(47, mean = mean(area), sd = sd(area)))
rock_n_norm <- cbind(rock, new)



trainingRowIndex_m <- sample(1:nrow(rock_n_norm), 0.8 * nrow(rock_n_norm))
trainingData <- rock_n_norm[trainingRowIndex_m, ]
testData <- rock_n_norm[-trainingRowIndex_m, ]

lmMod_m <- lm(perm ~ norm + peri, data = trainingData)
permPred_m <- predict(lmMod_m, testData)

summary(lmMod_m)

actual_preds <- data.frame(cbind(actuals=testData$perm, predicteds=permPred_m))
correlation_accuracy <- cor(actual_preds)
head(actual_preds, 25)

trainingData.control <- trainControl(method = "cv", number = 10)

model <- train(perm ~ norm + peri, data = rock_n_norm, method = "lm",
               trControl = trainingData.control)

model




frepcomgen <- function(n,m){
  mat <- matrix(sample(1:10000, (n + 1) * (m + 1), replace=TRUE) , nrow = n + 1, ncol = m + 1)
  
  #     mat <- matrix(1:(n*m), nrow = n + 1, ncol = m + 1)
  mat[n + 1,] <- 0
  mat[,m + 1] <- 0
  
  for (i in 1 : n){
    s <- 0
    
    for (j in 1 : m){
      s <- s + mat[i, j]
    }
    mat[i, m + 1] <- s
  }
  total <- 0
  for (j in 1: m){
    s <- 0
    
    for (i in 1: n){
      s <- s + mat[i, j]
    }
    total <- total + s
    mat[n + 1,j] <- s
  }
  mat[n + 1, m + 1] <- total
  mat <- mat / total
  #     mat[1,] = NaN
  #     mat[,1] = NaN
  return (mat)
}

res = frepcomgen(2, 3)

fcomplrepcom <- function(mat, n, m){
  mat[1,m+1] = 2 - sum(mat[,m + 1], na.rm = T)
  mat[n + 1, 1] = 2 - sum(mat[n + 1,], na.rm = T)
  
  for (i in 2:m){
    mat[1,i] <- 2 * mat[n + 1, i] - sum(mat[,i], na.rm = T)
  }
  for (i in 1:n){
    mat[i,1] <- 2 * mat[i, m + 1] - sum(mat[i,], na.rm = T)
  }
  return (mat)
}

result <- fcomplrepcom(res, 2, 3)

