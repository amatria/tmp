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

#ifndef DB_READER_H
#define DB_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <mpi.h>

#include "db_wrapper.h"

using namespace std;

class DbReader {
 private:
  int _hash_size;
  ifstream _nam;
  ifstream _seq;
  ifstream _acc;
  ifstream _ind;
  int LoadChunk(vector<int> &start_pos, vector<int> &seq_length, vector<unsigned char> &seqs, vector<int> &seq_length_rep, vector<vector<float>> &access, vector<vector<float>> &cond_access, vector<string> &names, vector<int> &suffix_array, vector<vector<int>> &start_hash, vector<vector<int>> &end_hash);
 public:
  DbReader(string db_name, int hash_size) {
    _hash_size = hash_size;
    _nam.open((db_name + ".nam").c_str(), ios::in);
    _seq.open((db_name + ".seq").c_str(), ios::in | ios::binary);
    _acc.open((db_name + ".acc").c_str(), ios::in | ios::binary);
    _ind.open((db_name + ".ind").c_str(), ios::in | ios::binary);
    if (!_nam || !_seq || !_acc || !_ind) {
      cout << "Error: can't open db_file." << endl;
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
  }
  vector<DbWrapper> LoadDatabases();
};

#endif
