

import numpy as np
import glob

if __name__ == '__main__':
    path = "../datasets/txt_files/wind_pressure_200/Lead_33_*.txt"
    data_ensembles=[]
    for filename in glob.glob(path):
        data = np.loadtxt(filename)
        data_ensembles.append(data)
    print(np.shape(data_ensembles))