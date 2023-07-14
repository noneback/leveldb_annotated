#ifndef LEVELDB_TRANSACTION_H
#define LEVELDB_TRANSACTION_H

#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {
class Slice;

enum class TransactionState { RUNNING, STOPPED };

// using TxnID = uint64_t;
// using TxnTimestamp = uint64_t; // txn may time out

class Transaction {
 public:
  Transaction(const Transaction&) = delete;
  void operator=(const Transaction&) = delete;
  virtual ~Transaction() = default;

  virtual Status Prepare() = 0;
  virtual Status Commit() = 0;
  virtual Status Rollback() = 0;
  virtual Status Get(const ReadOptions& options, const Slice& key,
                     std::string* val) = 0;
  virtual Status GetForUpdate(const ReadOptions& options, const Slice& key,
                              Slice* val, bool exclusive = true) = 0;
  virtual Iterator* GetIterator() = 0;
  virtual Status Put(const WriteOptions& options, const Slice& key,
                     const Slice& val) = 0;
  virtual Status Delete(const Slice& key) = 0;
  virtual Status Merge() = 0;

 protected:
  TransactionState state_;
  uint64_t id_;
  uint64_t ts_;
  // TODO: fill it.
  Transaction() {}
};
}  // namespace leveldb

#endif  // LEVELDB_TRANSACTION_H
