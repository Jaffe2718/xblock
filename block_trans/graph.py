import random
'''
用于生成和操作数据结构的单向图
'''

def gen_rule(n: int) -> dict:
    '''
    随机生成n个节点的单向图，节点编号从1到n
    图中每个节点的出度为1，出度的目标节点编号随机生成
    不能有孤立的节点，或者孤立的环
    :param n:  节点数量
    :return:   字典形式的图，key为节点编号，value为目标节点编号
    '''
    graph = {}
    nodes = list(range(1, n + 1))
    random.shuffle(nodes)
    # 选择主环的大小，从2到n
    main_loop_size = random.randint(2, n)
    # 生成主环
    for i in range(main_loop_size):
        graph[nodes[i]] = nodes[(i + 1) % main_loop_size]
    # 生成剩余的边，将剩余的节点随机连接到主环上或者已经连接到主环上的节点上
    for i in range(main_loop_size, n):
        graph[nodes[i]] = random.choice(nodes[:main_loop_size])
        main_loop_size += 1
    return graph


def gen_data(n: int) -> list:
    '''
    随机生成n个节点的数据，数据编号从1到n
    :param n:  数据数量
    :return:   数据列表
    '''
    data = list(range(1, n + 1))
    random.shuffle(data)
    return data


def transform(data: list, rule: dict, pos: int) -> list:
    '''
    把data[pos]的数据按照rule进行转换
    :param data:   数据列表
    :param rule:   转换规则
    :param pos:    点击的数字在列表data的位置
    :return:
    '''
    m = data[pos]         # 转换前的数据
    n = data[rule[pos + 1] - 1]   # 转换规则指向位置的数据
    # 交换两个数据在列表中的位置
    data[pos], data[rule[pos + 1] - 1] = n, m
    return data