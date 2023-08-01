#include "optimistic_transaction_db_impl.h"

#include "optimistic_transaction.h"
namespace leveldb {

Status OptimisticTransactionDB::Open(
    const leveldb::Options& options, const std::string& dbname,
    leveldb::OptimisticTransactionDB** dbptr,
    const leveldb::OptimisticTransactionDBOptions& occ_options) {
  DB* db;
  auto s = DB::Open(options, dbname, &db);
  if (s.ok()) {
    *dbptr = new OptimisticTransactionDBImpl(db, occ_options);
  }
  return s;
}

Transaction* OptimisticTransactionDBImpl::BeginTransaction(
    const leveldb::WriteOptions& options,
    const leveldb::OptimisticTransactionDBOptions& occ_options) {
  return new OptimisticTransaction(this);
}

}  // namespace leveldb