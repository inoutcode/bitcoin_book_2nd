#!/usr/bin/env python
# Proof-of-Work 算法示例

import hashlib
import time

try:
    long        # Python 2
    xrange
except NameError:
    long = int  # Python 3
    xrange = range

max_nonce = 2 ** 32  # 40亿


def proof_of_work(header, difficulty_bits):
    # 计算难度目标
    target = 2 ** (256 - difficulty_bits)

    for nonce in xrange(max_nonce):
        hash_result = hashlib.sha256(str(header) + str(nonce)).hexdigest()

        # 检查是否是目标值以下的有效结果
        if long(hash_result, 16) < target:
            print("Success with nonce %d" % nonce)
            print("Hash is %s" % hash_result)
            return (hash_result, nonce)

    print("Failed after %d (max_nonce) tries" % nonce)
    return nonce


if __name__ == '__main__':
    nonce = 0
    hash_result = ''

    # 难度从0到31位
    for difficulty_bits in xrange(32):
        difficulty = 2 ** difficulty_bits
        print("Difficulty: %ld (%d bits)" % (difficulty, difficulty_bits))
        print("Starting search...")

        # 当前时间
        start_time = time.time()

        # 创建一个包含前一个块的散列的新块
        # 我们伪造一个交易块 —— 只是一个字符串。
        new_block = 'test block with transactions' + hash_result

        # 为新块找到一个有效的nonce
        (hash_result, nonce) = proof_of_work(new_block, difficulty_bits)

        # 记录需要多长时间才能找到结果
        end_time = time.time()

        elapsed_time = end_time - start_time
        print("Elapsed Time: %.4f seconds" % elapsed_time)

        if elapsed_time > 0:

            # 估计每秒的散列计算次数
            hash_power = float(long(nonce) / elapsed_time)
            print("Hashing Power: %ld hashes per second" % hash_power)
