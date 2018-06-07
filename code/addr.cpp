#include <bitcoin/bitcoin.hpp>

int main()
{
    // base16格式的私钥
    bc::ec_secret decoded;
    bc::decode_base16(decoded,
        "038109007313a5807b2eccc082c8c3fbb988a973cacf1a7df9ce725c31b14776");

    bc::wallet::ec_private secret(
        decoded, bc::wallet::ec_private::mainnet_p2kh);

    // 生成公钥
    bc::wallet::ec_public public_key(secret);
    std::cout << "Public key: " << public_key.encoded() << std::endl;

    // 生成比特币地址
    // 一般可以使用:
    //    bc::wallet::payment_address payaddr =
    //        public_key.to_payment_address(
    //            bc::wallet::ec_public::mainnet_p2kh);
    //  const std::string address = payaddr.encoded();

    // 计算用于P2PKH地址的公钥哈希值 .
    bc::data_chunk public_key_data;
    public_key.to_data(public_key_data);
    const auto hash = bc::bitcoin_short_hash(public_key_data);

    bc::data_chunk unencoded_address;
    // 预留25字节空间
    //   [ version:1  ]
    //   [ hash:20    ]
    //   [ checksum:4 ]
    unencoded_address.reserve(25);
    // 版本号字节, 0 代表普通的 BTC 地址 (P2PKH).
    unencoded_address.push_back(0);
    // 哈希值
    bc::extend_data(unencoded_address, hash);
    // 计算哈希值的校验和并放入前4个字节
    bc::append_checksum(unencoded_address);
    // 最后使用base58编码
    assert(unencoded_address.size() == 25);
    const std::string address = bc::encode_base58(unencoded_address);

    std::cout << "Address: " << address << std::endl;
    return 0;
}
