//
// Created by noneback on 2023/7/14.
//

#ifndef LEVELDB_OPTIMISTIC_TRANSACTION_H
#define LEVELDB_OPTIMISTIC_TRANSACTION_H
#include "db/db_impl.h"
#include "db/dbformat.h"
#include "db/snapshot.h"
#include <vector>

#include "leveldb/write_batch.h"

#include "optimistic_transaction_db.h"
#include "transaction.h"
namespace leveldb {
class OptimisticTransaction : public Transaction {
 public:
  explicit OptimisticTransaction(OptimisticTransactionDB* db) : txn_db_(db) {
    seq_number_ = txn_db_->GetCurrentSeqNum();
  }

  ~OptimisticTransaction() override = default;

  OptimisticTransaction(const OptimisticTransaction&) = delete;
  void operator=(const OptimisticTransaction&) = delete;
  
  Status Prepare() override;
  Status Commit() override;
  Status Rollback() override;
  Status Get(const ReadOptions& options, const Slice& key,
             std::string* val) override;
  Status GetForUpdate(const ReadOptions& options, const Slice& key, Slice* val,
                      bool exclusive) override;
  Iterator* GetIterator() override;
  Status Put(const WriteOptions& options, const Slice& key,
             const Slice& val) override;
  Status Delete(const Slice& key) override;
  Status Merge() override;

 private:
  OptimisticTransactionDB* txn_db_;
  WriteBatch batch_;
  SequenceNumber seq_number_;
  std::vector<Slice*> modify_tracker_;

  // TODO:
  // 1. batch buffer, hold kv pair each transaction, atomic.
  // 2. seqID, to isolate data between txns.
  // 3. modify track list, track modified keys to resolve conflict.
};

}  // namespace leveldb
#endif  // LEVELDB_OPTIMISTIC_TRANSACTION_H
