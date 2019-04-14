//
// Created by cheng on 13/04/19.
//

#ifndef HDFIO_TAQLOADER_H
#define HDFIO_TAQLOADER_H

#include <iostream>
#include "H5Cpp.h"
using namespace H5;
class TaqLoader {
  /*
   * Output buffer initialization.
   */
  int i, j, k;
  const H5std_string inputFilename;//("test.h5");
  const H5std_string datasetName;//("x");

  const int numRows;
  const int numCols;

  static const int RANK_OUT = 2;

 public:
  TaqLoader(const std::string filename, const std::string datasetName, const int nR, const int nC)
      : inputFilename(filename), datasetName(datasetName), numRows(nR), numCols(nC) {}

  int load() {
    int *p_data_out = new int[numCols * numRows];
    for (auto i = 0; i < numCols * numRows; ++i) {
      p_data_out[i] = 0;
    }

    /*
     * Try block to detect exceptions raised by any of the calls inside it
     */
    try {
      /*
       * Turn off the auto-printing when failure occurs so that we can
       * handle the errors appropriately
       */
      Exception::dontPrint();
      /*
       * Open the specified file and the specified dataset in the file.
       */
      H5File file(inputFilename, H5F_ACC_RDONLY);
      DataSet dataset = file.openDataSet(datasetName);
      /*
       * Get the class of the datatype that is used by the dataset.
       */
      H5T_class_t type_class = dataset.getTypeClass();
      /*
       * Get class of datatype and print message if it's an integer.
       */
      if (type_class == H5T_INTEGER) {
        std::cout << "Data set has INTEGER type" << std::endl;
        /*
         * Get the integer datatype
         */
        IntType intype = dataset.getIntType();
        /*
         * Get order of datatype and print message if it's a little endian.
         */
        H5std_string order_string;
        H5T_order_t order = intype.getOrder(order_string);
        std::cout << order_string << std::endl;
        /*
         * Get size of the data element stored in file and print it.
         */
        size_t size = intype.getSize();
        std::cout << "Data size is " << size << std::endl;
      }
      /*
       * Get dataspace of the dataset.
       */
      DataSpace dataspace = dataset.getSpace();
      /*
       * Get the number of dimensions in the dataspace.
       */
      int rank = dataspace.getSimpleExtentNdims();
      /*
       * Get the dimension size of each dimension in the dataspace and
       * display them.
       */
      hsize_t dims_out[2];
      int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
      std::cout << "rank " << rank << ", dimensions " <<
                (unsigned long) (dims_out[0]) << " x " <<
                (unsigned long) (dims_out[1]) << std::endl;
      /*
       * Define hyperslab in the dataset; implicitly giving strike and
       * block NULL.
       */
      hsize_t offset[2];   // hyperslab offset in the file
      hsize_t count[2];    // size of the hyperslab in the file
      offset[0] = 0;
      offset[1] = 0;
      count[0] = numRows;
      count[1] = numCols;
      dataspace.selectHyperslab(H5S_SELECT_SET, count, offset);
      /*
       * Define the memory dataspace.
       */
      hsize_t dimsm[2];              /* memory space dimensions */
      dimsm[0] = numRows;
      dimsm[1] = numCols;
      DataSpace memspace(RANK_OUT, dimsm);
      /*
       * Define memory hyperslab.
       */
      hsize_t offset_out[2];   // hyperslab offset in memory
      hsize_t count_out[2];    // size of the hyperslab in memory
      offset_out[0] = 0;
      offset_out[1] = 0;
      count_out[0] = numRows;
      count_out[1] = numCols;
      memspace.selectHyperslab(H5S_SELECT_SET, count_out, offset_out);
      /*
       * Read data from hyperslab in the file into the hyperslab in
       * memory and display the data.
       */
      dataset.read((void *) p_data_out, PredType::NATIVE_INT, memspace, dataspace);
      for (j = 0; j < numRows; j++) {
        for (i = 0; i < numCols; i++)
          std::cout << p_data_out[j * numCols + i] << " ";
        std::cout << std::endl;
      }
      /*
       * 0 0 0 0 0 0 0
       * 0 0 0 0 0 0 0
       * 0 0 0 0 0 0 0
       * 3 4 5 6 0 0 0
       * 4 5 6 7 0 0 0
       * 5 6 7 8 0 0 0
       * 0 0 0 0 0 0 0
       */
    }  // end of try block
      // catch failure caused by the H5File operations
    catch (FileIException error) {
      delete[] p_data_out;
      std::cout << "file exception" << std::endl;
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSet operations
    catch (DataSetIException error) {
      delete[] p_data_out;
      std::cout << "data set exception" << std::endl;
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSpace operations
    catch (DataSpaceIException error) {
      delete[] p_data_out;
      std::cout << "data space exception" << std::endl;
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSpace operations
    catch (DataTypeIException error) {
      delete[] p_data_out;
      std::cout << "data type exception" << std::endl;
      error.printErrorStack();
      return -1;
    }
    delete[] p_data_out;
    return 0;  // successfully terminated
  }

};
#endif //HDFIO_TAQLOADER_H
