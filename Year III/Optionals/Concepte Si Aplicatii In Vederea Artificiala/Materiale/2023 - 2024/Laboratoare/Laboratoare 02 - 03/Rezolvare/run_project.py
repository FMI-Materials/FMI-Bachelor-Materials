"""
    PROIECT MOZAIC
"""

# Parametrii algoritmului sunt definiti in clasa Parameters.
from parameters import Parameters
from build_mosaic import build_mosaic
import cv2 as cv


# numele imaginii care va fi transformata in mozaic
image_path = "./../data/imaginiTest/dragan.jpeg"
params = Parameters(image_path)

# directorul cu imagini folosite pentru realizarea mozaicului
params.small_images_dir = "./../data/colectie/"
# tipul imaginilor din director
params.image_type = "png"
# numarul de piese ale mozaicului pe orizontala
# pe verticala vor fi calcultate dinamic a.i sa se pastreze raportul
params.num_pieces_horizontal = 100
# afiseaza piesele de mozaic dupa citirea lor
params.show_small_images = False
# modul de aranjarea a pieselor mozaicului
# optiuni: 'aleator', 'caroiaj'
params.layout = "caroiaj"
# criteriul dupa care se realizeaza mozaicul
# optiuni: 'aleator', 'distantaCuloareMedie'
# params.criterion = "aleator"
params.criterion = "distantaCuloareMedie"
# daca params.layout == 'caroiaj', sa se foloseasca piese hexagonale
params.hexagon = False
img_mosaic = build_mosaic(params)
img_mosaic = cv.resize(img_mosaic, (1000, 657))
cv.imshow("image", img_mosaic)
cv.waitKey(0)
# cv.imwrite('test.png', img_mosaic)
# cv.imwrite('mozaic.png', img_mosaic)
