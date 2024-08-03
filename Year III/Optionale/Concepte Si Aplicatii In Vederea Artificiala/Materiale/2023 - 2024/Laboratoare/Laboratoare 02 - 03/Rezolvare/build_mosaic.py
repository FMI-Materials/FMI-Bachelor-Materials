import os

import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
from add_pieces_mosaic import *
from parameters import *


def load_pieces(params: Parameters):
    # citeste toate cele N piese folosite la mozaic din directorul corespunzator
    # toate cele N imagini au aceeasi dimensiune H x W x C, unde:
    # H = inaltime, W = latime, C = nr canale (C=1  gri, C=3 color)
    # functia intoarce pieseMozaic = matrice N x H x W x C in params
    # pieseMoziac[i, :, :, :] reprezinta piesa numarul i

    # citeste imaginile din director
    files = os.listdir(params.small_images_dir)
    images = [
        cv.imread(os.path.join(params.small_images_dir, file))
        for file in files
        if file.endswith(params.image_type)
    ]
    if params.show_small_images:
        for i in range(10):
            for j in range(10):
                plt.subplot(10, 10, i * 10 + j + 1)
                # OpenCV reads images in BGR format, matplotlib reads images in RBG format
                im = images[i * 10 + j].copy()
                # BGR to RGB, swap the channels
                im = im[:, :, [2, 1, 0]]
                plt.imshow(im)
        plt.show()

    params.small_images = np.array(images)


def compute_dimensions(params: Parameters):
    # calculeaza dimensiunile mozaicului
    # obtine si imaginea de referinta redimensionata avand aceleasi dimensiuni
    # ca mozaicul

    # completati codul
    # TODO: sterge
    hs, ws, _ = params.small_images[0].shape
    h, w, _ = params.image.shape

    # calculeaza automat numarul de piese pe verticala
    params.num_pieces_vertical = int(
        np.round((h * params.num_pieces_horizontal * ws) / (w * hs))
    )
    # redimensioneaza imaginea
    params.image_resized = cv.resize(
        params.image,
        (ws * params.num_pieces_horizontal, hs * params.num_pieces_vertical),
    )

    print(np.shape(params.image_resized))
    print(params.num_pieces_vertical)


def build_mosaic(params: Parameters):
    # incarcam imaginile din care vom forma mozaicul
    load_pieces(params)
    # calculeaza dimensiunea mozaicului
    compute_dimensions(params)

    img_mosaic = None
    if params.layout == "caroiaj":
        if params.hexagon is True:
            img_mosaic = add_pieces_hexagon(params)
        else:
            img_mosaic = add_pieces_grid(params)
    elif params.layout == "aleator":
        img_mosaic = add_pieces_random(params)
    else:
        print("Wrong option!")
        exit(-1)

    return img_mosaic
