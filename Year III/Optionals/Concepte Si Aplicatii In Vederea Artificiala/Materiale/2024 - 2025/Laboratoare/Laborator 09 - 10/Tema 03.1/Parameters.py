import os

class Parameters:
    def __init__(self):
        self.base_dir = '../data'
        self.dir_pos_examples = os.path.join(self.base_dir, 'exemplePozitive')
        self.dir_neg_examples = os.path.join(self.base_dir, 'exempleNegative')
        self.dir_save_files = os.path.join(self.base_dir, 'salveazaFisiere')
        if not os.path.exists(self.dir_save_files):
            os.makedirs(self.dir_save_files)
            print('directory created: {} '.format(self.dir_save_files))
        else:
            print('directory {} exists '.format(self.dir_save_files))

        # set the parameters
        self.dim_window = 36  # exemplele pozitive (fete de oameni cropate) au 36x36 pixeli
        self.dim_hog_cell = 6  # dimensiunea celulei
        self.dim_descriptor_cell = 36  # dimensiunea descriptorului unei celule
        self.overlap = 0.3
        self.number_positive_examples = 6713  # numarul exemplelor pozitive
        self.number_negative_examples = 10000  # numarul exemplelor negative
