from bitcoin.rpc import RawProxy

p = RawProxy()

# Alice's 交易 ID
txid = "0627052b6f28912f2703066a912ea577f2ce4da4caa5a5fbd8a57286c345c2f2"

# 首先, 获取原始十六进制交易数据
raw_tx = p.getrawtransaction(txid)

# 解码交易数据成JSON对象
decoded_tx = p.decoderawtransaction(raw_tx)

# 打印交易的每个输出
for output in decoded_tx['vout']:
    print(output['scriptPubKey']['addresses'], output['value'])
