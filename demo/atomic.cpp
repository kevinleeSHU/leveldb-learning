#include <iostream>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    auto status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    
    std::string key1("apple");
    std::string key2("orange");
    std::string value("A");
    auto s = db->Put(leveldb::WriteOptions(), key1, value);
    s = db->Get(leveldb::ReadOptions(), key1, &value);
    if (s.ok()) {
        std::cout << "key = " << key1 <<
                    " value = " << value << std::endl;
    }

    if (status.ok()) {
        leveldb::WriteBatch batch;
        batch.Delete(key1);
        batch.Put(key2, value);
        s = db->Write(leveldb::WriteOptions(), &batch);
    }

    std::string res;
    status = db->Get(leveldb::ReadOptions(), key2, &res);
    if (status.ok()) {
        std::cout << "key = " << key2 <<
                    " value = " << res << std::endl;
    }

    delete db;
    return 0;
}

