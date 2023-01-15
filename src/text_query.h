#ifndef ASTEROID_TEXT_QUERY_H_
#define ASTEROID_TEXT_QUERY_H_

#include <fstream>
#include <iostream>
#include <map>
using std::map;
#include <set>
using std::set;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <memory>

namespace asteroid {


class QueryResult;
class TextQuery {
 public:
  using line_no = vector<string>::size_type;
	TextQuery(std::ifstream & is);
	QueryResult query(const std::string& word) const;

 private:
	std::shared_ptr<vector<string>> lines_;
	std::map<std::string, std::shared_ptr<set<line_no>>> word_nos_;
}; // TextQuery


class QueryResult {
	friend std::ostream& Print(std::ostream &os, const QueryResult& qr);
	using NumsSet = std::set<TextQuery::line_no>;

 public:
  QueryResult(const string &word,
              std::shared_ptr<set<TextQuery::line_no>> numbers,
              std::shared_ptr<vector<string>> lines) 
    : word_(word)
    , numbers_(numbers)
    , lines_(lines) {}
  NumsSet::const_iterator Beg() { return numbers_->cbegin(); }  
  NumsSet::const_iterator End() { return numbers_->cend(); }  
  std::shared_ptr<vector<string>> GetFile() const { return lines_; }
  
 private:
	std::string word_;
  std::shared_ptr<std::set<TextQuery::line_no>> numbers_;
	std::shared_ptr<vector<string>> lines_;
}; // QueryResult

std::ostream& Print(std::ostream &os, const QueryResult& qr);

} // asteroid

#endif // ASTEROID_TEXT_QUERY_H_
