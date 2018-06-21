# 在哈希算法的输入中迭代nonce的例子。

from __future__ import print_function
import hashlib

text = "I am Satoshi Nakamoto"

# 从0到19迭代nonce
for nonce in range(20):

    # 将nonce添加到文本的末尾
    input_data = text + str(nonce)

    # 计算输入的SHA-256哈希(文本+nonce)
    hash_data = hashlib.sha256(input_data).hexdigest()

    # 显示输入和散列结果
    print(input_data, '=>', hash_data)
