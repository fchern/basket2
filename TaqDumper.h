//
// Created by cheng on 13/04/19.
//

#ifndef HDFIO_TAQDUMPER_H
#define HDFIO_TAQDUMPER_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 *  This example writes a dataset to a new HDF5 file.
 */
#include <iostream>
#include <string>
#include <vector>
#include "H5Cpp.h"

using namespace H5;

class TaqDumper {

  H5std_string outputFilename;
  H5std_string datasetName;

  int numRows;
  int numCols;

  static const int RANK = 2;

 public:
  TaqDumper(const std::string filename, const std::string datasetName, const int nR, const int nC)
      : outputFilename(filename), datasetName(datasetName), numRows(nR), numCols(nC) {}
  /*
   * Data initialization.
   */
  int dump(const std::vector<std::vector<int> > &big) {
    int *p_data_out = new int[numCols * numRows];
    int rowId = 0;
    for(auto& row :big){
      int colId = 0;
      for (auto item : row){

        p_data_out[rowId * numCols + colId] = item;

        colId ++;
      }
      rowId++;
    }
    for (auto i = 0; i < numCols * numRows; ++i) {
    }

    /*
     * 0 1 2 3 4 5
     * 1 2 3 4 5 6
     * 2 3 4 5 6 7
     * 3 4 5 6 7 8
     * 4 5 6 7 8 9
     */
    // Try block to detect exceptions raised by any of the calls inside it
    try {
      /*
       * Turn off the auto-printing when failure occurs so that we can
       * handle the errors appropriately
       */
      Exception::dontPrint();
      /*
       * Create a new file using H5F_ACC_TRUNC access,
       * default file creation properties, and default file
       * access properties.
       */
      H5File file(outputFilename, H5F_ACC_TRUNC);
      /*
       * Define the size of the array and create the data space for fixed
       * size dataset.
       */
      hsize_t dimsf[2];              // dataset dimensions
      dimsf[0] = numRows;
      dimsf[1] = numCols;
      DataSpace dataspace(RANK, dimsf);
      /*
       * Define datatype for the data in the file.
       * We will store little endian INT numbers.
       */
      IntType datatype(PredType::NATIVE_INT);
      datatype.setOrder(H5T_ORDER_LE);
      /*
       * Create a new dataset within the file using defined dataspace and
       * datatype and default dataset creation properties.
       */
      DataSet dataset = file.createDataSet(datasetName, datatype, dataspace);
      /*
       * Write the data to the dataset using default memory space, file
       * space, and transfer properties.
       */
      dataset.write((void*)p_data_out, PredType::NATIVE_INT);
    }  // end of try block
      // catch failure caused by the H5File operations
    catch (FileIException error) {
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSet operations
    catch (DataSetIException error) {
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSpace operations
    catch (DataSpaceIException error) {
      error.printErrorStack();
      return -1;
    }
      // catch failure caused by the DataSpace operations
    catch (DataTypeIException error) {
      error.printErrorStack();
      return -1;
    }
    return 0;  // successfully terminated
  }
};
#endif //HDFIO_TAQDUMPER_H
