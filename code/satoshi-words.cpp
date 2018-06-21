/*
  展示中本聪创世区块中的信息
*/
#include <iostream>
#include <bitcoin/bitcoin.hpp>

int main()
{
    // 创建创世区块
    bc::chain::block block = bc::chain::block::genesis_mainnet();
    // 创世区块包含单一的币基交易
    assert(block.transactions().size() == 1);
    // 获取区块中的第一个交易
    const bc::chain::transaction& coinbase_tx = block.transactions()[0];
    // 币基交易 tx 有一个输入
    assert(coinbase_tx.inputs().size() == 1);
    const bc::chain::input& coinbase_input = coinbase_tx.inputs()[0];
    // 将输入脚本转换为其原始形式
    const auto prefix = false;
    const bc::data_chunk& raw_message = coinbase_input.script().to_data(prefix);
    // 转换为std::string
    std::string message(raw_message.begin(), raw_message.end());
    // 展示信息
    std::cout << message << std::endl;
    return 0;
}
