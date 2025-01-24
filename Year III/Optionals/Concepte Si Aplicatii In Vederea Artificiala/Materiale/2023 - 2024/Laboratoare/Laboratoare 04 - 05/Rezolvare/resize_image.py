import sys
import cv2 as cv
import numpy as np

from parameters import Parameters
from select_path import select_path


def compute_energy(img):
    """
    calculeaza energia la fiecare pixel pe baza gradientului
    :param img: imaginea initiala
    :return:E - energia
    """
    # urmati urmatorii pasi:
    # 1. transformati imagine in grayscale
    # 2. folositi filtru sobel pentru a calcula gradientul in directia X si Y
    # 3. calculati magnitudinea pentru fiecare pixel al imaginii
    E = np.zeros((img.shape[0], img.shape[1]))

    img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    grad_x = cv.Sobel(img_gray, ddepth=cv.CV_16S, dx=1, dy=0)
    grad_y = cv.Sobel(img_gray, ddepth=cv.CV_16S, dx=0, dy=1)
    abs_x = np.abs(grad_x)
    abs_y = np.abs(grad_y)
    E = abs_x + abs_y

    return E


def show_path(img, path, color):
    new_image = img.copy()
    for row, col in path:
        new_image[row, col] = color

    E = compute_energy(img)
    new_image_E = img.copy()
    new_image_E[:, :, 0] = E.copy()
    new_image_E[:, :, 1] = E.copy()
    new_image_E[:, :, 2] = E.copy()

    for row, col in path:
        new_image_E[row, col] = color
    cv.imshow("path img", np.uint8(new_image))
    cv.imshow("path E", np.uint8(new_image_E))
    cv.waitKey(100)


def delete_path(img, path):
    """
    elimina drumul vertical din imagine
    :param img: imaginea initiala
    :path - drumul vertical
    return: updated_img - imaginea initiala din care s-a eliminat drumul vertical
    """
    updated_img = np.zeros((img.shape[0], img.shape[1] - 1, img.shape[2]), np.uint8)
    for i in range(img.shape[0]):
        col = path[i][1]
        updated_img[i, :col] = img[i, :col].copy()
        updated_img[i, col:] = img[i, col + 1 :].copy()

    return updated_img


def decrease_width(params: Parameters, num_pixels):
    img = params.image.copy()  # copiaza imaginea originala
    for i in range(num_pixels):
        print(
            "Eliminam drumul vertical numarul %i dintr-un total de %d."
            % (i + 1, num_pixels)
        )

        # calculeaza energia dupa ecuatia (1) din articol
        E = compute_energy(img)
        path = select_path(E, params.method_select_path)
        if params.show_path:
            show_path(img, path, params.color_path)
        img = delete_path(img, path)

    cv.destroyAllWindows()
    return img


def decrease_height(params: Parameters, num_pixels):
    params.image = np.rot90(params.image, k=3)
    new_image = decrease_width(params, params.num_pixels_height)
    new_image = np.rot90(new_image)
    return new_image


def amplify_content(params: Parameters):
    original_image = params.image.copy()
    scaled_image = cv.resize(
        original_image,
        (0, 0),
        fx=params.factor_amplification,
        fy=params.factor_amplification,
    )
    params.num_pixels_width = scaled_image.shape[1] - original_image.shape[1]
    params.num_pixels_height = scaled_image.shape[0] - original_image.shape[0]
    params.image = scaled_image
    resized_image = decrease_width(params, params.num_pixels_width)
    params.image = resized_image
    resized_image = decrease_height(params, params.num_pixels_height)
    params.image = original_image
    return resized_image


def delete_object(params: Parameters, x0, y0, w, h):
    img = params.image.copy()
    if w < h:
        num_pixels = w
        for i in range(num_pixels):
            print(
                "Eliminam drumul vertical numarul %i dintr-un total de %d."
                % (i + 1, num_pixels)
            )

            # calculeaza energia dupa ecuatia (1) din articol
            E = compute_energy(img)
            E2 = np.zeros(E.shape)
            E2[y0 : y0 + h, x0 : x0 + w] = -10000
            E = E + E2
            w = w - 1
            path = select_path(E, params.method_select_path)
            if params.show_path:
                show_path(img, path, params.color_path)
            img = delete_path(img, path)
    else:
        num_pixels = h
        img = np.rot90(img, k=3)
        for i in range(num_pixels):
            print(
                "Eliminam drumul orizontal numarul %i dintr-un total de %d."
                % (i + 1, num_pixels)
            )

            # calculeaza energia dupa ecuatia (1) din articol
            E = compute_energy(img)
            E2 = np.zeros(E.shape[1], E.shape[0])
            E2[y0 : y0 + h, x0 : x0 + w] = -10000
            E = E + E2
            h = h - 1
            path = select_path(E, params.method_select_path)
            if params.show_path:
                show_path(img, path, params.color_path)
            img = delete_path(img, path)
        img = np.rot90(img, k=1)

    return img


def resize_image(params: Parameters):
    if params.resize_option == "micsoreazaLatime":
        # redimensioneaza imaginea pe latime
        return decrease_width(params, params.num_pixels_width)

    elif params.resize_option == "micsoreazaInaltime":
        return decrease_height(params, params.num_pixels_height)

    elif params.resize_option == "amplificaContinut":
        return amplify_content(params)

    elif params.resize_option == "eliminaObiect":
        x0, y0, w, h = cv.selectROI(np.uint8(params.image))
        return delete_object(params, x0, y0, w, h)

    else:
        print("The option is not valid!")
        sys.exit(-1)
