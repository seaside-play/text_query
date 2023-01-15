#ifndef ASTEROID_QUERY_BASE_H_
#define ASTEROID_QUERY_BASE_H_

#include <memory>
#include <string>

#include "text_query.h"
#include "query.h"

namespace asteroid {

Query operator~(const Query &operand);
Query operator&(const Query &lhs, const Query &rhs);
Query operator|(const Query &lhs, const Query &rhs);

class QueryBase {
  friend class Query;
 protected:
  using line_no = TextQuery::line_no;
  virtual ~QueryBase() = default;
  virtual QueryResult Eval(const TextQuery &) const = 0;
  virtual std::string Rep(void) const = 0; 
};

class WordQuery : public QueryBase {
  friend class Query;
  WordQuery(const std::string &word) : query_word_(word) {}
  QueryResult Eval(const TextQuery &t) const override { return t.query(query_word_);}
  std::string Rep(void) const override { return query_word_; }
  std::string query_word_;
};

class NotQuery : public QueryBase {
  friend Query operator~(const Query &);
  NotQuery(const Query &query) : query_(query) {}
  QueryResult Eval(const TextQuery &t) const override;
  std::string Rep(void) const override { return "~(" + query_.Rep() + ")"; }
  Query query_;
};


class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(const Query &lhs, const Query &rhs, const std::string &oprt) 
    : lhs_(lhs)
    , rhs_(rhs)
    , operator_(oprt) {}

  std::string Rep(void) const override { 
    return "(" + lhs_.Rep() + " " + operator_ + " " + rhs_.Rep() + ")"; 
  }

  Query lhs_, rhs_;

 private:
  std::string operator_;
};

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);
  AndQuery(const Query &lhs, const Query &rhs) 
      : BinaryQuery(lhs, rhs, "&") {}
  QueryResult Eval(const TextQuery &t) const;
};


class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);
  OrQuery(const Query &lhs, const Query &rhs) 
      : BinaryQuery(lhs, rhs, "|") {}
  QueryResult Eval(const TextQuery &t) const override;
};


} // namesapce astorid

#endif // ASTEROID_QUERY_BASE_H_
