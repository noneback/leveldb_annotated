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

  Status Put(const WriteOptions& options, const Slice& key,
             const Slice& value) {
    return db_->Put(options, key, value);
  }
  Status Get(const ReadOptions& options, const Slice& key, std::string* value) {
    return db_->Get(options, key, value);
  }
  Status Write(const WriteOptions& options, WriteBatch* updates) {
    return db_->Write(options, updates);
  }
  Status Delete(const WriteOptions& options, const Slice& key) {
    return db_->Delete(options, key);
  }

 protected:
  DB* db_;
  DBImpl* db_impl_;
};
}  // namespace leveldb
#endif  // LEVELDB_TRANSACTION_DB_H
