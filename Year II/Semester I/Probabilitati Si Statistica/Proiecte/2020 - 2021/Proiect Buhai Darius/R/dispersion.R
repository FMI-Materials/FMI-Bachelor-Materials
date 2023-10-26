# Calculate dispersion
dispersion <- function(f){
   m = medium(f)
   f_new <- function(x){
     (x - m)^2
   }
   medium(f_new)
}
