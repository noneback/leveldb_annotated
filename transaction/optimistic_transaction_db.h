//
// Created by noneback on 2023/7/14.
//

#ifndef LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
#define LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
#include "leveldb/db.h"
#include "leveldb/status.h"

#include "transaction.h"
#include "transaction_db.h"

namespace leveldb {

class OptimisticTransactionDBOptions {};

class OptimisticTransactionDB : TransactionDB {
 public:
  friend class Transaction;
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
  SequenceNumber GetCurrentSeqNum() {
    return static_cast<const SnapshotImpl*>(db_impl_->GetSnapshot())
        ->sequence_number();
  }

 private:
};

}  // namespace leveldb

#endif  // LEVELDB_OPTIMISTIC_TRANSACTION_DB_H
