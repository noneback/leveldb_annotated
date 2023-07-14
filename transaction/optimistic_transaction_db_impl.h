//
// Created by noneback on 2023/7/14.
//

#ifndef LEVELDB_OPTIMISTIC_TRANSACTION_DB_IMPL_H
#define LEVELDB_OPTIMISTIC_TRANSACTION_DB_IMPL_H

#include "optimistic_transaction_db.h"

namespace leveldb {

class OptimisticTransactionDBImpl : public OptimisticTransactionDB {
 public:
  OptimisticTransactionDBImpl() = delete;
  OptimisticTransactionDBImpl(DB* db,
                              const OptimisticTransactionDBOptions& occ_options)
      : OptimisticTransactionDB(db) {



    // TODO:
  }
  ~OptimisticTransactionDBImpl() {
    // TODO: fill it
  }

  Transaction* BeginTransaction(
      const WriteOptions& options,
      const OptimisticTransactionDBOptions& occ_options);
};
}  // namespace leveldb
#endif  // LEVELDB_OPTIMISTIC_TRANSACTION_DB_IMPL_H
