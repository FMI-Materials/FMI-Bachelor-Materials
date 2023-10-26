
# integreaza pdf ca sa obtin valoarea cdf
get_CDF_from_PDF <- function (f, x) {
  tryCatch ({
      integrate (f, 0, x)$value
    },
    error = function (e) {
      print(e)
    }
  )
}

# verific daca functia de densitate este valida
# trebuie sa fie pozitiva
# probabilitatea totala trebuie sa fie 1 -> sigur se intampla ceva
check_density <- function(f, a, b) {
  # verific prima conditie
  for (x in seq(a, b, 0.1)) {
    if (f(x) < 0) {
      print(paste("pdf nu poate sa aiba valori negative",
                  "dar am obtinut", f(x), "in", x, sep=" "))
      return(FALSE)
    }
  }

  # verific a doua conditie
  total <- integral(Vectorize(f), max(-Inf, a), min(b, +Inf))
  if (abs(total - 1) > 0.1) {
    print(paste("probabilitatea cumulata totala trebuie sa fie egala cu 1",
                "dar am obtinut", total, sep=" "))
    return(FALSE)
  }

  return(TRUE)
}

# afisaza graficul densitatii
plot_density <- function(f, a, b, name="") {
  # validez pdf
  if (!check_density(f, a, b)) {
    return()
  }

  # pdf a fost validata
  # afisez graficul pdf

  xs <- seq(a, b, 0.1)
  ys <- c()
  for (x in xs) {
    ys = append(ys, f(x))
  }
  plot(xs, ys, type="l", main=noquote(paste(name, " PDF")), col="red", xlab="x", ylab="y")
}

# o folosesc pentru repartitiile standard carora le stim
# functia de repartitie
# afisaza graficul repartitiei
plot_repartition <- function(F, a, b, name) {
  # calculez si afisez graficul CDF

  xs <- seq(a, b, 0.01)
  ys <- c()
  for (x in xs) {
    ys = append(ys, F(x))
  }
  plot(xs, ys, col="red", type="l", main=noquete(paste(name, " CDF")), xlab="x", ylab="y")
}

# o folosesc pentru repartitiile carora
# nu le stim functia de repartitie
# ne folosim de pdf
# afisaza graficul repartitiei
plot_generic_repartition <- function(f, a, b) {
  # validez pdf
  if (!check_density(f, a, b)) {
    return()
  }

  xs <- seq(a, b, 0.01)
  ys <- c()
  for (x in xs) {
    ys = append(ys, get_CDF_from_PDF(f, x))
  }
  plot(xs, ys, col="red", type="l", main="CDF", xlab="x", ylab="y")
}


# functia primeste ca parametrii numele repartitiei,
# un flag care marcheaza daca vrem graficul densitatii,
# sau al repartitiei, si, in plus, parametrii corespunzatori
# repartitiei selectate
# daca repartitia nu exista, sau daca parametrii nu corespund
# repartitiei alese, se va intoarce un mesaj corespunzator
parse_known_repartition <- function(name, CDF=FALSE, ...) {
  params <- list(...)
  if (name == "uniform") {
    if (!is.null(params$a) && !is.null(params$b)) {
      a <- params$a
      b <- params$b
      if (a >= b) {
        return("parametri incorecti")
      }

      f <- function(x) 1 / (b - a)
      F <- function(x)(x - a) / (b - a)
      if (CDF) {
        plot_repartition(F, a, b, name)
      }
      else {
        plot_density(f, a, b, name)
      }
    }
    else {
      return("parametrii necesari nu au fost pasati")
    }
  }
  else if (name == "exp") {
    if (!is.null(params$lambda)) {
      lambda <- params$lambda
      if (lambda <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) (lambda * exp(1)^(-lambda * x))
      F <- function(x) (1 - exp(1)^(-lambda * x))
      if (CDF) {
        plot_repartition(F, 0, 50, name)
      }
      else {
        plot_density(f, 0, 50, name)
      }
    }
    else {
      return("parametrii necesari nu au fost pasati")
    }
  }
  else if (name == "normal") {
    if (!is.null(params$mu && !is.null(params$sigma))) {
      mu <- params$mu
      sigma <- params$sigma
      if (sigma <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) ((1 / (sigma * sqrt(pi * 2)))*(exp(1)^((-(x - mu)^2)/(2  * sigma ^ 2))))
      F <- function(x) (pnorm(x, mu, sigma))
      if (CDF) {
        plot_repartition(F, -25, 25, name)
      }
      else {
        plot_density(f, -25, 25, name)
      }
    }
    else {
      return("parametrii necesari nu au fost pasati")
    }
  }
  else if (name == "pareto") {
    if (!is.null(params$m) && !is.null(params$alpha)) {
      m <- params$m
      alpha <-params$alpha
      if (alpha <= 0 || m <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) (alpha * m^alpha) / (x ^ (alpha + 1))
      F <- function(x) (1 - (m ^ alpha) / (x ^ alpha))
      if (CDF) {
        plot_repartition(F, m, m + 50, name)
      }
      else {
        plot_density(f, m, m + 50, name)
      }
    }
  }
  else if (name == "cauchy") {
    if (!is.null(params$location && !is.null(params$scale))) {
      location <- params$location
      scale <- params$scale
      if (scale <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) 1 / (pi * scale * (1 + ((x - location) / (scale))^2))
      F <- function(x) (1 / pi) * atan((x - location) / scale) + 1 / 2

      if (CDF) {
        plot_repartition(F, -25, 25, name)
      }
      else {
        plot_density(f, -25, 25, name)
      }
    }
  }
  else if (name == "logistic") {
    if (!is.null(params$mu && !is.null(params$s))) {
      mu <- params$mu
      s <- params$s
      if (s <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) (exp(1) ^ ((mu - x) / s) / (s * (1 + exp(1) ^ (mu - x) / s) ^ 2))
      F <- function(x) 1 / (1 + exp(1) ^ (-(x - mu) / s))

      if (CDF) {
        plot_repartition(F, -25, 25, name)
      }
      else {
        plot_density(f, -25, 25, name)
      }
    }
  }
  else if (name == "weibull") {
    if (!is.null(params$scale && !is.null(params$shape))) {
      scale <- params$scale
      shape <- params$shape
      if (scale <= 0 || shape <= 0) {
        return("parametrii incorecti")
      }

      f <- function(x) {
        if (x >= 0) (shape / scale) * (x / scale) ^ (shape - 1) * (exp(1) ^ (-(x / scale) ^ shape))
        else 0
      }
      F <- function(x) {
        if (x >= 0) 1 - (exp(1) ^ (-(x / scale) ^ shape))
        else 0
      }

      if (CDF) {
        plot_repartition(F, 0, 50, name)
      }
      else {
        plot_density(f, 0, 50, name)
      }
    }
  }
  else {
    print("repartitie necunoscuta")
  }
}

# Example:

# parse_known_repartition("uniform", FALSE, a=0, b=10)
# parse_known_repartition("uniform", TRUE, a=0, b=10)
# parse_known_repartition("exp", FALSE, lambda=2)
# parse_known_repartition("exp", TRUE, lambda=2)
# parse_known_repartition("normal", FALSE, mu=0, sigma=1)
# parse_known_repartition("normal", TRUE, mu=0, sigma=1)
# parse_known_repartition("pareto", FALSE, m=3, alpha=1)
# parse_known_repartition("pareto", TRUE, m=3, alpha=1)
# parse_known_repartition("cauchy", FALSE, location=0, scale=1)
# parse_known_repartition("cauchy", TRUE, location=0, scale=1)
# parse_known_repartition("logistic", FALSE, mu=0, s=1)
# parse_known_repartition("logistic", TRUE, mu=0, s=1)
# parse_known_repartition("weibull", FALSE, scale=1, shape=2)
# parse_known_repartition("weibull", TRUE, scale=1, shape=2)
# plot_generic_repartition(function(x) x / 2, 0, 2)

