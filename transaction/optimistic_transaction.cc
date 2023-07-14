#include "optimistic_transaction.h"

namespace leveldb {

Status OptimisticTransaction::Prepare() { return Status(); }
Status OptimisticTransaction::Commit() { return Status(); }
Status OptimisticTransaction::Rollback() { return Status(); }
Status OptimisticTransaction::Get(const ReadOptions& options, const Slice& key,
                                  std::string* val) {
  return Status();
}
Status OptimisticTransaction::GetForUpdate(const ReadOptions& options,
                                           const Slice& key, Slice* val,
                                           bool exclusive) {
  return Status();
}
Iterator* OptimisticTransaction::GetIterator() { return nullptr; }
Status OptimisticTransaction::Put(const WriteOptions& options, const Slice& key,
                                  const Slice& val) {
  return Status();
}
Status OptimisticTransaction::Delete(const Slice& key) { return Status(); }
Status OptimisticTransaction::Merge() { return Status(); }
}  // namespace leveldb