#ifndef ASTEROID_QUERY_H_
#define ASTEROID_QUERY_H_

#include <memory>
#include <string>

#include "text_query.h"

namespace asteroid {


class TextQuery;
class QueryBase;
class Query {
  friend Query operator~(const Query &);
  friend Query operator&(const Query &, const Query &);
  friend Query operator|(const Query &, const Query &);

 public:
  Query(const std::string &word);
  QueryResult Eval(const TextQuery &t) const;
  std::string Rep(void) const;

 private:        
  Query(std::shared_ptr<QueryBase> query_base);
  std::shared_ptr<QueryBase> query_base_;
};

std::ostream& operator<<(std::ostream &os, const Query &query);

} // namespace asteroid

#endif // ASTEROID_QUERY_H_  
