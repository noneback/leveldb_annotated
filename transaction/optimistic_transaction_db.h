//
// Created by noneback on 2023/7/14.
//

#ifndef LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
#define LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
#include <unordered_set>

#include "leveldb/db.h"
#include "leveldb/status.h"

#include "transaction.h"
#include "transaction_db.h"

namespace leveldb {

class OptimisticTransactionDBOptions {};

class OptimisticTransactionDB : TransactionDB {
 public:
  friend class Transaction;
  using TransactionDB::Get;
  using TransactionDB::Put;
  static Status Open(const Options& options, const std::string& dbname,
                     OptimisticTransactionDB** dbptr,
                     const OptimisticTransactionDBOptions& occ_options);

  virtual ~OptimisticTransactionDB() {}

  OptimisticTransactionDB(DB* db) : TransactionDB(db) {}
  OptimisticTransactionDB(const OptimisticTransactionDB&) = delete;

  void operator=(const OptimisticTransactionDB&) = delete;

  virtual Transaction* BeginTransaction(
      const WriteOptions& options, const OptimisticTransactionDBOptions&
                                       occ_options) = 0;  // fire a transaction
  
  SequenceNumber GetCurrentSeqNum() { return db_impl_->GetLastSeqNum(); }

  bool SetExclusive(const Slice& key) {
    if (exclusive_tracker_.count(key.ToString()) >= 1) {
      return false;
    }
    exclusive_tracker_.insert(key.ToString());
    return true;
  }

 private:
  std::set<const std::string> exclusive_tracker_;  // TODO: make it unordered
};

}  // namespace leveldb

#endif  // LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
