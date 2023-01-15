#include "query.h"

#include <iostream>
#include <string>

#include "query_base.h"

namespace asteroid {


Query::Query(const std::string &word) 
    : query_base_(new WordQuery(word)) {}

Query::Query(std::shared_ptr<QueryBase> query_base) 
    : query_base_(query_base) {}

QueryResult Query::Eval(const TextQuery &t) const {
  return query_base_->Eval(t);
}

std::string Query::Rep(void) const {
  return query_base_->Rep();
}

std::ostream& operator<<(std::ostream &os, const Query &query) {
  return os << query.Rep();
}


} // namespace asteroid
