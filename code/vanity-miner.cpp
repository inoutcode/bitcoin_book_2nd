#include <random>
#include <bitcoin/bitcoin.hpp>

// 要搜索的字符串
const std::string search = "1kid";

// 随机生成密钥
bc::ec_secret random_secret(std::default_random_engine& engine);
// 从EC密钥中生成比特币地址
std::string bitcoin_address(const bc::ec_secret& secret);
// 与要搜索的字符串进行比较（大小写敏感）
bool match_found(const std::string& address);

int main()
{
    // Linux上的 random_device 使用 "/dev/urandom"
    // 注意: 根据具体实现，随机源可能不是足够安全的!
    // 不要在生产环境中使用本例生成的虚荣地址
    std::random_device random;
    std::default_random_engine engine(random());

    // 连续循环...
    while (true)
    {
        // 生成随机私钥.
        bc::ec_secret secret = random_secret(engine);
        // 生成地址
        std::string address = bitcoin_address(secret);
        // 是否与目标字符串匹配 (1kid)
        if (match_found(address))
        {
            // 成功
            std::cout << "Found vanity address! " << address << std::endl;
            std::cout << "Secret: " << bc::encode_base16(secret) << std::endl;
            return 0;
        }
    }
    // 不可能运行到这里
    return 0;
}

bc::ec_secret random_secret(std::default_random_engine& engine)
{
    // 生成新的密钥...
    bc::ec_secret secret;
    // 遍历每个字节设置随机值...
    for (uint8_t& byte: secret)
        byte = engine() % std::numeric_limits<uint8_t>::max();
    // 返回结果.
    return secret;
}

std::string bitcoin_address(const bc::ec_secret& secret)
{
    // 将密钥转换为付款地址
    bc::wallet::ec_private private_key(secret);
    bc::wallet::payment_address payaddr(private_key);
    // 返回加密的形式.
    return payaddr.encoded();
}

bool match_found(const std::string& address)
{
    auto addr_it = address.begin();
    // 比较字符串前缀
    for (auto it = search.begin(); it != search.end(); ++it, ++addr_it)
        if (*it != std::tolower(*addr_it))
            return false;
    // 匹配
    return true;
}
