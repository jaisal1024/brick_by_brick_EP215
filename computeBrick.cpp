/* Property of Jaisal Friedman, October 2019 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
typedef vector<int> row;

vector<row> rows;
vector<vector<int> > alignments;

//compute all unique rows of 2,3 bricks.
void computeRows(row r, int width) {
  int pos;
  if (r.empty())
    pos = 0;
  else
    pos = r.back();
  if (pos+1 < width){
    if (pos+2 == width || pos+3 == width){
      rows.push_back(r);
      return;
    } else {
      // add 2-brick
      r.push_back(pos+2);
      computeRows(r, width);
      // replace with 3-brick
      r.back()++;
      computeRows(r, width);
    }
  }
  return;
}

void printAlignment(){
  for (int i = 0; i < alignments.size(); ++i)
    {
        for (int j = 0; j < alignments[i].size(); ++j)
        {
            cout << alignments[i][j] << ' ';
        }
        cout << std::endl;
    }
}

//compute a matrix of rows that align for each row
void computeAlignment(){
  alignments.resize(rows.size());

  for (size_t i = 0; i < rows.size(); i++) {
    for (size_t j = i+1; j < rows.size(); j++) {
      bool valid = true;
      auto item_i = rows[i].begin();
      auto item_j = rows[j].begin();
      // compute intersection of the two sets
      while (item_i != rows[i].end() && item_j != rows[j].end() && valid) {
        if (*item_i > *item_j) {
          item_j++;
        } else if (*item_i < *item_j){
          item_i++;
        } else {
          valid = false;
        }
      }
      if (valid) {
        alignments[i].push_back(j);
        alignments[j].push_back(i);
      }
    }
  }
  return;
}

void printDP(vector<long long> dp){
  for (int i = 0; i < dp.size(); ++i)
    {
            cout << dp[i] << ' ';
    }
    cout << endl;
}

//compute combinations
unsigned long long computeCombinations(int height){
  unsigned long long combinations = 0;
  // initialize memoized vector dp
  vector<unsigned long long> dp(rows.size(), 1);
  // loop through each column of wall
  for (size_t i = 1; i < height; i++) {
    //store updated values for each iteration, before copying
    vector<unsigned long long> dp_copy(rows.size(), 0);
    for (size_t j = 0; j < alignments.size(); j++) {
      //compute sum of unique number of ways of laying bricks for an alignment set
      unsigned long long sum = 0;
      for (auto k: alignments[j]) {
        sum += dp[k];
      }
      dp_copy[j] = sum;
    }
    //copy new memoized results for next layer
    for (size_t n = 0; n < dp.size(); n++) {
      dp[n] = dp_copy[n];
    }
  }
  //sum all memoized results across alignment set for the answer
  unsigned long long result = 0;
  for (auto n: dp){
    result += n;
  }
  return result;
}


int main(int argc, char const *argv[]) {
    //* Read Height and Width of Wall from CLI
    //declare input flags & variable
    int width = -1, height = -1;

    //check if you are given the proper number of terminal inputs
    if (argc != 5) {
        cout << "Please invoke the program in the CLI form: mymachine-promt >> ./computeBrick -w <width> -h <height>" << endl;
        return -1;
    }
    //check inputs to get height and width in the array argv
    for (int i = 0; i < argc; i++) {
        if (*argv[i] == '-' && *(argv[i] + 1) == 'w') {
            width = atoi(argv[i + 1]);
        } else if (*argv[i] == '-' && *(argv[i] + 1) == 'h')
            height = atoi(argv[i + 1]);
    }
    //catch bad inputs or improper invokation
    if (width < 0 || height < 0) {
      cout << "Please invoke the program in the CLI form: mymachine-promt >> ./computeBrick -w <width> -h <height>" << endl;
      return -1;
    }

    row startRow;
    computeRows(startRow, width);
    computeAlignment();
    unsigned long long combinations = computeCombinations(height);

    cout << combinations << endl;
    return 0;

  }
