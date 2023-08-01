
#include "leveldb/options.h"

#include "gtest/gtest.h"
#include "iostream"
#include "optimistic_transaction_db.h"

namespace leveldb {

class TransactionTest : public testing::Test {
 public:
  std::unique_ptr<OptimisticTransactionDB> txn_db;
  std::string dbname;
  Options options;
  OptimisticTransactionDBOptions occ_options;

  TransactionTest() {
    // TODO
  }
};

class TransactionTester {
 public:
  OptimisticTransactionDB* txn_db_;
  std::string dbname_;
  Options options_;
  OptimisticTransactionDBOptions occ_options_;
  TransactionTester(const Options& options, const std::string& dbname,
                    const OptimisticTransactionDBOptions& occ_options)
      : dbname_(std::move(dbname)),
        occ_options_(occ_options),
        options_(options) {}
  Status Init() {
    return OptimisticTransactionDB::Open(options_, dbname_, &txn_db_,
                                         occ_options_);
  }
  ~TransactionTester() { delete txn_db_; }
};

TEST(TransactionTest, SuccessTransaction) {
  WriteOptions write_options;
  ReadOptions read_options;
  Options opts;
  opts.create_if_missing = true;
  OptimisticTransactionDBOptions occ_options;
  std::string val;
  TransactionTester tester(opts, "/tmp/test", occ_options);
  auto s = tester.Init();
  std::cout << "test:" << s.ToString() << std::endl;
  ASSERT_EQ(s.ok(), true);

  auto txn = tester.txn_db_->BeginTransaction(write_options, occ_options);
  ASSERT_NE(txn, nullptr);
  ASSERT_EQ(txn->Put(write_options, "t1", "v1").ok(), true);
  s = txn->Get(read_options, "t1", &val);
  std::cout << "Get: " << s.ToString() << std::endl;
  ASSERT_EQ(s.ok(), true);
  ASSERT_EQ(val, "v1");

  delete txn;
}
}  // namespace leveldb