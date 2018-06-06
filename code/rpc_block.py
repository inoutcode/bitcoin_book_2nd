from bitcoin.rpc import RawProxy

p = RawProxy()

# Alice的交易所在的区块
blockheight = 277316

# 获得区块的哈希值
blockhash = p.getblockhash(blockheight)

# 根据哈希值检索区块
block = p.getblock(blockhash)

# tx元素包含块中的所有交易ID
transactions = block['tx']

block_value = 0

# 遍历区块中的每个交易ID
for txid in transactions:
    tx_value = 0
    # 使用ID检索原始交易数据
    raw_tx = p.getrawtransaction(txid)
    # 解析交易数据
    decoded_tx = p.decoderawtransaction(raw_tx)
    # 遍历交易的所有输出
    for output in decoded_tx['vout']:
        # 累加交易的输出
        tx_value = tx_value + output['value']

    # 累计到区块的所有输出
    block_value = block_value + tx_value

print("Total value in block: ", block_value)
