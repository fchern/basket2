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
//
//      This example reads hyperslab from the SDS.h5 file into
//      two-dimensional plane of a three-dimensional array.  Various
//      information about the dataset in the SDS.h5 file is obtained.
//
#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif
using std::cout;
using std::endl;
#include <string>
#include "H5Cpp.h"
#include "TaqLoader.h"
#include "TaqDumper.h"
using namespace H5;
const H5std_string FILE_NAME("SDS.h5");
const H5std_string DATASET_NAME("IntArray");

const int NX = 5;        // output buffer dimensions
const int NY = 6;

const int RANK_OUT = 2;

int main(void) {

  /*
  TaqDumper dumper(FILE_NAME, DATASET_NAME , NX, NY);


  std::vector<std::vector<int>> t;
  for(auto i = 0; i < NX; ++i){
    std::vector<int> temp;
    for(auto k = 0; k < NY; ++k){
     temp.push_back (k);
    }
    t.push_back(temp);
  }
  dumper.dump(t);
  */

  TaqLoader loader(FILE_NAME, DATASET_NAME , NX, NY);
  loader.load();
}
