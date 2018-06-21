#include <bitcoin/bitcoin.hpp>

bc::hash_digest create_merkle(bc::hash_list& merkle)
{
    if (merkle.empty())
        return bc::null_hash;
    else if (merkle.size() == 1)
        return merkle[0];

    // 只要有多于1个哈希，循环继续
    while (merkle.size() > 1)
    {
        // 如果哈希值数量为奇数，复制列表中最后一个哈希值
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        // 列表大小为偶数
        assert(merkle.size() % 2 == 0);

        // 新的哈希值列表
        bc::hash_list new_merkle;
        // 每次计算两个
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // 连接两个哈希值
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
                decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            // 散列
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            // 将哈希值添加到列表
            new_merkle.push_back(new_root);
        }
        // 替换为新的列表
        merkle = new_merkle;

        // 调试 输出 -------------------------------------
        std::cout << "Current merkle hash list:" << std::endl;
        for (const auto& hash: merkle)
            std::cout << "  " << bc::encode_base16(hash) << std::endl;
        std::cout << std::endl;
        // --------------------------------------------------
    }
    // 最终以一个哈希值结束，即 merkle root
    return merkle[0];
}

int main()
{
    bc::hash_list tx_hashes{{
        bc::hash_literal("0000000000000000000000000000000000000000000000000000000000000000"),
        bc::hash_literal("0000000000000000000000000000000000000000000000000000000000000011"),
        bc::hash_literal("0000000000000000000000000000000000000000000000000000000000000022"),
    }};
    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    std::cout << "Result: " << bc::encode_base16(merkle_root) << std::endl;
    return 0;
}
