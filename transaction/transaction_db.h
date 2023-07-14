//
// Created by noneback on 2023/7/14.
//

#ifndef LEVELDB_TRANSACTION_DB_H
#define LEVELDB_TRANSACTION_DB_H

#include "db/db_impl.h"

#include "leveldb/db.h"

namespace leveldb {
class TransactionDB {
 public:
  TransactionDB() = delete;
  TransactionDB(DB* db) : db_(db), db_impl_(static_cast<DBImpl*>(db)) {}

  DB* GetBaseDB() { return db_; }

 protected:
  DB* db_;
  DBImpl* db_impl_;
};
}  // namespace leveldb
#endif  // LEVELDB_TRANSACTION_DB_H
