from bitcoin.rpc import RawProxy

# 与本地Bitcoin Core节点创建连接
p = RawProxy()

# 运行 getblockchaininfo 命令, 将返回数据保存到info中
info = p.getblockchaininfo()

# 打印info中的blocks内容
print(info['blocks'])
