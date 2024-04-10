use std::collections::HashMap;
use rand::seq::SliceRandom;
use rand::Rng;
use crate::xpack::event;


/**
# 生成游戏规则哈希表
## 概述
1. 随机生成 n 个节点的HashMap，节点编号从 1 到 n，可以理解为单向图；
2. 图中每个节点的出度为 1，出度的目标节点编号随机生成；
3. 不能有孤立的节点，或者孤立的环。

## 参数
- n: 节点数量
## 返回值
- HashMap 形式的单向图，key 为节点编号，value 为目标节点编号
 */
pub fn gen_rule(n: usize) -> HashMap<usize, usize> {
    let mut graph = HashMap::new();
    let mut nodes: Vec<usize> = (1..=n).collect(); // init nodes = [1, 2, ..., n]
    nodes.shuffle(&mut rand::thread_rng());
    // main loop size between [2, n]
    let mut main_loop_size = rand::thread_rng().gen_range(2..=n);
    for i in 0..main_loop_size {
        graph.insert(nodes[i], nodes[(i + 1) % main_loop_size]);
    }
    for i in main_loop_size..n {
        graph.insert(nodes[i], nodes[rand::thread_rng().gen_range(0..main_loop_size)]);
        main_loop_size += 1;
    }
    return graph;
}

/**
# 生成游戏题目
## 概述
- 随机生成数据编号从1到n的数组，然后打乱顺序返回。

## 参数
- n: 数据数量

## 返回值
- 数据列表
*/
pub fn gen_data(n: usize) -> Vec<usize> {
    let mut rng = rand::thread_rng();
    let mut data: Vec<usize> = (1..=n).collect();
    data.shuffle(&mut rng);

    return data;
}

/**
# 交换数据操作
## 概述
- 把数组`data`里面的的数据按照哈希表`rule`进行转换；
- `pos`是点击的数字在数组`data`的索引，从0开始。
- 把`data[pos]`和`data[rule[pos + 1] - 1]`（**即规则HashMap中`pos+1`指向的位置，`+1`为了从1开始查找**）进行交换。

## 参数
- data: 数据列表
- rule: 转换规则
- pos: 点击的数字在列表 data 的位置
*/
pub fn transform(gd: &mut event::GameData, pos: usize) {
    let mut data = gd.data.clone().unwrap();
    let rule = gd.rule.clone().unwrap();
    let m = data[pos];
    let n = data[rule[&(pos + 1)] - 1];
    data[pos] = n;
    data[rule[&(pos + 1)] -1] = m;
    gd.data = Some(data);
}

/**
# 判断游戏是否结束
## 概述
- 判断数组`data`是否为`[1, 2, 3, ..., n]`。
## 参数
- data: 数据列表
## 返回值
- 是否结束
*/
pub fn check_win(data: &Vec<usize>) -> bool {
    let mut flag = true;
    for i in 0..data.len() {
        if data[i] != i + 1 {
            flag = false;
            break;
        }
    }
    return flag;
}