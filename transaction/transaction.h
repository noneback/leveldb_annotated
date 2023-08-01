#ifndef LEVELDB_TRANSACTION_H
#define LEVELDB_TRANSACTION_H

#include "db/dbformat.h"

#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {
class Slice;

enum class TransactionState { RUNNING, STOPPED };

// using TxnID = uint64_t;
// using TxnTimestamp = uint64_t; // txn may time out

struct TrackRequest {
  std::string key;
  SequenceNumber seq = 0;
  bool read_only = true;
};

class TrackedInfo {
 public:
  uint64_t num_writes_ = 0;
  uint64_t num_reads_ = 0;
  SequenceNumber seq_ = 0;
  bool read_only_ = false;
  TrackedInfo(const SequenceNumber& seq) : seq_(seq) {}
};

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
                              std::string* val, bool exclusive = true) = 0;
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
