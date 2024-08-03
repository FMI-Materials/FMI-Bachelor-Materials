fgama <- function(x, a)
{
  x^(a-1)*exp(-x)
}

gama_bhd <- function(n)
{
  if(n<0) stop("Gama e definita pe (0, +inf)")
  if(n==round(n)) return(factorial(n-1))
  if(n==.5) return(sqrt(pi))
  if(n<1)
    return(integrate(fgama, 0, Inf, a=n)$value)
  return((n-1)*gama_bhd(n-1))
}

fbeta <- function(x, a, b)
{
  x^(a-1)*(1-x)^(b-1)
}

integrate(fbeta, 0, 1, a=.3, b=.7)$value

# TEMA: Implementati functie care calculeaza Beta(a, b), folosindu-va de proprietati
# si de integrala gama
beta_bhd <- function(a, b)
{
  if(a+b==1)
    return(pi/sin(a*pi))
  if(a>b)
    return(beta_bhd(b, a))
  return((gama_bhd(a)*gama_bhd(b))/gama_bhd(a+b));
}

beta_bhd(.3,.7)

library(discreteRV)

#### A
xa <- RV(2:3,c(1/5, 4/5))
ya <- RV(c(-3,-2),c(4/5,1/5))

plot(xb)
plot(yb)

# 1
3*xa
xa^(-1)
cos(pi/2 * xa)
ya^2
ya+3

# 2
p1 = 2*xa+3*ya
p2 = 3*xa-ya
p3 = xa^2*ya^2

# 4
P(2*xa+3*ya>1)
P(2*xa+3*ya>1|xa>0)
P(2*xa+3*ya<3|ya<(-2))
P(xa^2*ya^3>3)
P(xa^2*ya^3<=3)
P(2*xa+3*ya<3*xa-ya)

#### B
xb <- RV(c(0,9),c(1/2,1/2))
yb <- RV(c(-3,1),c(1/7, 6/7))

plot(xb)
plot(yb)

# 1
xb-1
xb^(-2)
sin(pi/4*xb)
yb*5
exp(yb)

# 2
xb-yb
cos(pi*xb*yb)
xb^2+3*yb

# 4
P(xb-yb>0)
P(xb-yb<0|xb>0)
P(xb-yb>0|yb<=0)
P(cos(pi*xb*yb)<1/2)
P(xb^2+3*yb>=3)
P(xb-yb<xb^2+3*yb)

#### C

xc <- RV(c(5,8),c(1/2,1/2))
yc <- RV(c(-1,1),c(1/6,5/6))

plot(xc)
plot(yc)

# 1
2*xc
1/(xc^3)
tg(pi * x)
abs(y)

# 2
xc + yc
sin(pi * xc * yc)
1/xc + 1/yc

# 4
P(xc+yc<2)
P(xc+yc>2|xc>5)
P(xc+yc<12|yc<0)
P(sin(pi/2*xc*yc)<=1/2)
P(1/xc+1/yc<1|yc<0)
P(1/xc+1/yc<xc+yc)

#### D
xd <- RV(c(-3,6),c(1/8,7/8))
yd <- RV(c(exp(1),exp(3)),c(1/4,3/4))

plot(xd)
plot(yd)

# 1
2 - xd
xd^3
cos(pi/6 * xd)
1/yd
log(yd)

#2
xd * yd
xd/yd
abs(xd - yd^2)

# 4
P(xd*yd<=exp(4))
P(xd*yd>=7|xd<0)
P(xd*yd<9|yd>3)
P(xd/yd<1)
P(abs(xd-yd^2)>=3)
P(xd/yd<abs(xd-yd^2))





