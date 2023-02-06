import vtk
import sys
# parse the prob data and output them into the vtk format
from vtkmodules.vtkCommonDataModel import vtkStructuredPoints
import numpy as np
from vtk.util import numpy_support

def writeStructuredDs(fname, ds):
    writer = vtk.vtkStructuredPointsWriter()
    writer.SetFileName(fname)
    writer.SetFileVersion(42)
    writer.SetInputData(ds)
    writer.Update()
    writer.Write()  

if __name__ == "__main__":
    n=len(sys.argv)
    if n!= 2:
        exit(0)

    file_name = sys.argv[1]

    fo=open(file_name, "r")
    for line in fo:
        line_strip=line.strip()
        prob_data = [float(n) for n in line_strip.split(",")]
    fo.close()

    print(len(prob_data))
    
    # create the grid and set to cell
     
    numpyarray = np.asarray(prob_data)

    print(numpyarray)

    
    xdim=240
    ydim=121
    zdim=1
    structured_dataset = vtkStructuredPoints()
    structured_dataset.SetDimensions(xdim, ydim, zdim)
    structured_dataset.SetOrigin(0, 0, 0)

    # the default array name is unknown

    vtkarray = numpy_support.numpy_to_vtk(numpyarray)
    vtkarray.SetName("cross_prob")

    print(vtkarray)
   
    structured_dataset.GetCellData().AddArray(vtkarray)
    writeStructuredDs("wind_cross_prob.vtk",structured_dataset)
