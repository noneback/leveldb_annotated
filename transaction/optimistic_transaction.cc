#include "optimistic_transaction.h"

namespace leveldb {
const uint32_t kTxnMaxKeyNum = 10000;

// 2PC
Status OptimisticTransaction::Prepare() { return Status(); }
Status OptimisticTransaction::Rollback() { return Status(); }
Status OptimisticTransaction::Commit() {
  // TODO: finish it.
  return Status();
}

Status OptimisticTransaction::Get(const ReadOptions& options, const Slice& key,
                                  std::string* val) {
  return txn_db_->Get(options, key, val);
}

Status OptimisticTransaction::GetForUpdate(const ReadOptions& options,
                                           const Slice& key, std::string* val,
                                           bool exclusive) {
  // TODO: what is the exclusive for?? Need a tracer at txndb level
  if (exclusive && !txn_db_->SetExclusive(key)) {
    return Status();
  }
  // 1. add key into tracker
  // 2. get it from batch, then memtable, then disk
  TrackKey(key.data(), true, txn_db_->GetCurrentSeqNum());  // TODO: check it
  auto it = index_.find(key.data());
  if (it != index_.end()) {
    // find in index_, just return it.
    *val = it->second;
    return Status::OK();
  }
  // get from db
  return txn_db_->Get(options, key, val);
}
Iterator* OptimisticTransaction::GetIterator() { return nullptr; }
Status OptimisticTransaction::Put(const WriteOptions& options, const Slice& key,
                                  const Slice& val) {
  // 1. add key into tracker
  // 2. write to batches, with index
  if (index_.size() >= kTxnMaxKeyNum) {
    return Status::NotSupported("TooManyKeys");
  }

  TrackKey(key.data(), false, txn_db_->GetCurrentSeqNum());
  batch_.Put(key, val);
  index_.insert(std::make_pair(key.data(), val.data()));
  return Status::OK();
}

Status OptimisticTransaction::Delete(const Slice& key) {
  // 1. add key into tracker
  // 2. write to batches, with index
  if (index_.size() >= kTxnMaxKeyNum) {
    return Status::NotSupported("TooManyKeys");
  }

  TrackKey(key.data(), false, txn_db_->GetCurrentSeqNum());
  // TODO: check
  batch_.Delete(key);
  index_.erase(key.data());
  return Status::OK();
}

// TODO: what do we mean by merge?
Status OptimisticTransaction::Merge() { return Status(); }
}  // namespace leveldb