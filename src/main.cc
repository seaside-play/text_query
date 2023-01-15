#include <iostream>
#include <fstream>
#include <string>
using std::string;

#include "text_query.h"
using asteroid::TextQuery;
#include "query_base.h"
using asteroid::Query;
using asteroid::operator&;
using asteroid::operator|;
using asteroid::operator~;

int main(int argc, char* argv[]) {
  Query q = Query("fiery") & Query("bird") | Query("wind"); 
  std::ifstream input("/home/chris/codes/text_query/src/note.txt");
  TextQuery tq(input);
  auto ret = q.Eval(tq);
  asteroid::Print(std::cout, ret);
  //std::cout << q.Rep() << std::endl;                                                           
  return 1;
}

