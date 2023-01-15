#include "query_base.h"

#include <algorithm>
#include <memory>
#include <set>
using std::set;
#include <string>
using std::string;

#include "text_query.h"
#include "query.h"

namespace asteroid {


QueryResult NotQuery::Eval(const TextQuery &t) const {
  auto result = query_.Eval(t);
  auto beg = result.Beg();
  auto end = result.End();
  auto sz = result.GetFile()->size();
  auto ret_nos = std::make_shared<set<line_no>>();
  for (std::size_t i = 0; i != sz; ++i) {
    if (beg == end || *beg != i)
      ret_nos->insert(i);
    else if (beg != end)
      ++beg;
  }
  return QueryResult(Rep(), ret_nos, result.GetFile());
}

QueryResult OrQuery::Eval(const TextQuery &t) const {
  auto left = lhs_.Eval(t);
  auto right = rhs_.Eval(t);
  auto nos = std::make_shared<set<line_no>>(left.Beg(), left.End());
  nos->insert(right.Beg(), right.End());
  return QueryResult(Rep(), nos, left.GetFile());
}

QueryResult AndQuery::Eval(const TextQuery &t) const {
  auto left = lhs_.Eval(t);
  auto right = rhs_.Eval(t);
  auto nos = std::make_shared<set<line_no>>();
  std::set_intersection(left.Beg(), left.End(), right.Beg(), right.End(),
                        std::inserter(*nos, nos->begin()));  
  return QueryResult(Rep(), nos, left.GetFile());
}

Query operator~(const Query &operand) {
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}

Query operator&(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

Query operator|(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}


} // namespace asteroid
