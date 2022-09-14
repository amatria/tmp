/*
 MIT License

 Copyright (c) 2016 Tsukasa Fukunaga
 Copyright (c) 2021 Iñaki Amatria-Barral, Jorge González-Domínguez, Juan Touriño

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <fstream>

#include <getopt.h>
#include <stdlib.h>

#include "rna_interaction_search_parameters.h"

void RnaInteractionSearchParameters::SetParameters(int argc, char* argv[]) {
  int c;
  extern char *optarg;
  while ((c = getopt(argc, argv, "i:o:d:l:e:y:x:f:g:s:m:p:a:")) != -1) {
    switch (c) {
    case 'i':
      _input_filename = optarg;
      break;

    case 'o':
      _output_filename = optarg;
      break;
      
    case 'd':
      _db_filename = optarg;
      break;

    case 'l':
      _max_seed_length = atoi(optarg);
      break;

    case 'e':
      _hybrid_energy_threshold = atof(optarg);
      break;
   
    case 'f':
      _interaction_energy_threshold = atof(optarg);
      break;

    case 'g':
      _final_threshold = atof(optarg);
      break;

    case 's':
      _output_style = atoi(optarg);
      break;

    case 'x':
      _drop_out_length_w_gap = atoi(optarg);
      break;

    case 'y':
      _drop_out_length_wo_gap = atoi(optarg);
      break;

    case 'm':
      _min_helix_length = atoi(optarg);
      break;

    case 'p':
      _tmp_path = optarg;
      break;

    case 'a':
      _algorithm = ParseSearchAlgorithm(optarg);
      break;

    default:
      cerr << "Error: The argument is invalid command." << endl;
      exit(1);
    }
  }
}

void RnaInteractionSearchParameters::SetDbParameters(){
  ifstream ifs((GetDbFilename()+".bas").c_str(), ios::in | ios::binary);
  if (!ifs){
    cout << "Error: can't open " << GetDbFilename() << ".bas." <<endl;
    exit(1);
  }
  int temp_i = 0;
  ifs.read(reinterpret_cast<char*>(&temp_i), sizeof(int));
  SetHashSize(temp_i);
  ifs.read(reinterpret_cast<char*>(&temp_i), sizeof(int));
  SetRepeatFlag(temp_i);
  ifs.read(reinterpret_cast<char*>(&temp_i), sizeof(int));
  SetMaximalSpan(temp_i);
  ifs.read(reinterpret_cast<char*>(&temp_i), sizeof(int));
  SetMinAccessibleLength(temp_i);
  ifs.close();
}
