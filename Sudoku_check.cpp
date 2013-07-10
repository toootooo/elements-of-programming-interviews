#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

bool valid_to_add(const vector<vector<int>> &A, const int &i, const int &j,
                  const int &val) {
  // Check row constraints
  for (int k = 0; k < A.size(); ++k) {
    if (val == A[k][j]) {
      return false;
    }
  }

  // Check column constraints
  for (int k = 0; k < A.size(); ++k) {
    if (val == A[i][k]) {
      return false;
    }
  }

  // Check region constraints
  int region_size = sqrt(A.size());
  int I = i / region_size, J = j / region_size;
  for (int a = 0; a < region_size; ++a) {
    for (int b = 0; b < region_size; ++b) {
      if (val == A[region_size * I + a][region_size * J + b]) {
        return false;
      }
    }
  }
  return true;
}

bool solve_Sudoku_helper(vector<vector<int>> &A, int i, int j) {
  if (i == A.size()) {
    i = 0;  // start a new row
    if (++j == A[i].size()) {
      return true;  // entire matrix has been filled without conflict
    }
  }

  // Skip nonempty entries
  if (A[i][j] != 0) {
    return solve_Sudoku_helper(A, i + 1, j);
  }

  for (int val = 1; val <= A.size(); ++val) {
    // Note: practically, it's substantially quicker to check if entryval
    // conflicts with any of the constraints if we add it at (i,j) before
    // adding it, rather than adding it and then calling is_valid_Sudoku.
    // The reason is that we know we are starting with a valid configuration,
    // and the only entry which can cause a problem is entryval at (i,j).
    if (valid_to_add(A, i, j, val)) {
      A[i][j] = val;
      if (solve_Sudoku_helper(A, i + 1, j)) {
        return true;
      }
    }
  }

  A[i][j] = 0;  // undo assignment
  return false;
}

// @include
// Check if a partially filled matrix has any conflicts
bool is_valid_Sudoku(const vector<vector<int>> &A) {
  // Check row constraints
  for (int i = 0; i < A.size(); ++i) {
    vector<bool> is_present(A.size() + 1, false);
    for (int j = 0; j < A.size(); ++j) {
      if (A[i][j] != 0 && is_present[A[i][j]] == true) {
        return false;
      } else {
        is_present[A[i][j]] = true;
      }
    }
  }

  // Check column constraints
  for (int j = 0; j < A.size(); ++j) {
    vector<bool> is_present(A.size() + 1, false);
    for (int i = 0; i < A.size(); ++i) {
      if (A[i][j] != 0 && is_present[A[i][j]] == true) {
        return false;
      } else {
        is_present[A[i][j]] = true;
      }
    }
  }

  // Check region constraints
  int region_size = sqrt(A.size());
  for (int I = 0; I < region_size; ++I) {
    for (int J = 0; J < region_size; ++J) {
      vector<bool> is_present(A.size() + 1, false);
      for (int i = 0; i < region_size; ++i) {
        for (int j = 0; j < region_size; ++j) {
          if (A[region_size * I + i][region_size * J + j] != 0 &&
              is_present[A[region_size * I + i][region_size * J + j]]) {
            return false;
          } else {
            is_present[A[region_size * I + i][region_size * J + j]] = true;
          }
        }
      }
    }
  }
  return true;
}
// @exclude

bool solve_Sudoku(vector<vector<int>> &A) {
  if (is_valid_Sudoku(A) == false) {
    cout << "Initial configuration violates constraints." << endl;
    return false;
  }

  if (solve_Sudoku_helper(A, 0, 0)) {
    for (int i = 0; i < A.size(); ++i) {
      copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
      cout << endl;
    }
    return true;
  } else {
    cout << "No solution exists." << endl;
    return false;
  }
}

int main(int argc, char *argv[]) {
  vector<vector<int>> A(9, vector<int>(9, 0));
  A[0] = {0, 2, 6, 0, 0, 0, 8, 1, 0};
  A[1] = {3, 0, 0, 7, 0, 8, 0, 0, 6};
  A[2] = {4, 0, 0, 0, 5, 0, 0, 0, 7};
  A[3] = {0, 5, 0, 1, 0, 7, 0, 9, 0};
  A[4] = {0, 0, 3, 9, 0, 5, 1, 0, 0};
  A[5] = {0, 4, 0, 3, 0, 2, 0, 5, 0};
  A[6] = {1, 0, 0, 0, 3, 0, 0, 0, 2};
  A[7] = {5, 0, 0, 2, 0, 4, 0, 0, 9};
  A[8] = {0, 3, 8, 0, 0, 0, 4, 6, 0};
  solve_Sudoku(A);
  return 0;
}
