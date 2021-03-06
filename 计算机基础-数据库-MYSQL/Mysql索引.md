# 索引

- 使用索引查询数据 : 使用数据结构提高查找数据效率

## 是什么:一种数据结构

- Mysql 中维护了用于查询数据的一系列数据结构
  - 被建立好的数据结构中的每个节点都会指向(或引用)表中的记录
- 可以对数据库中的一些数据建立索引,再次查找的时候通过索引进行查找,可以提高查找效率

## 能做什么(作用):高效获取数据

- 没有建立索引的数据库表,只能自上往下的查找数据
  - 查找效率低

## 优点:

- 可以利用数据结构
  - 提高检索数据的效率,降低 IO 操作成本
  - 降低排序的成本,降低 CPU 消耗

## 缺点:

- 因为数据结构的存在
  - 需要花费额外的空间进行值的存储
  - 每次更新表的时候也需要更新索引,增大更新消耗

## 分类:(默认均使用 B+tree 作为底层结构)

- 聚集索引
- 前缀索引
- 复合索引:为多个列建立一个索引
  - 查找索引时,每个数据值元素都是多个列的值
- 唯一索引:对有唯一值的列建立的索引
  - 需要保证某一列的值是唯一的,这一列允许为空
- 单值索引: 包含某个表中单个列的索引,一个表会有多个单列索引

## 底层实现:

- 一般索引使用的数据结构是 B+树(多路搜索树,不一定是二叉树)

### BTREE 数据结构:

#### 相关概念

1. 叉数:n路b 树的分支数
2. 大节点:包含多个数据节点和指向下层节点的指针的节点
3. 小节点
4. 子节点

BTree又叫多路平衡搜索树，一颗m叉的BTree特性如下：

- 叉数 ≥ 小节点划分数
- 每个非根,非叶子节点的子节点数 ≥ [ceil(m/2)向上取整]
- 每个非叶子节点的子节点数 ≥ 2。
- 所有的叶子节点都在同一层。
- 每个非叶子节点中,[ceil(叉数/2)-1] <= key的数量 <= 叉数-1
- 所以 2 <= n <=4 。当n>4时，中间节点分裂到父节点，两边节点分裂。
- 以5叉BTree为例，

1). 插入前4个字母 C N G A

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944126588.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944126588.png)

2). 插入H，n>4，中间元素G字母向上分裂到新的节点

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944549825.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944549825.png)

3). 插入E，K，Q不需要分裂

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944596893.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944596893.png)

4). 插入M，中间元素M字母向上分裂到父节点G

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944652560.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944652560.png)

5). 插入F，W，L，T不需要分裂

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944686928.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944686928.png)

6). 插入Z，中间元素T向上分裂到父节点中

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944713486.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944713486.png)

7). 插入D，中间元素D向上分裂到父节点中。然后插入P，R，X，Y不需要分裂

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944749984.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944749984.png)

8). 最后插入S，NPQR节点n>5，中间节点Q向上分裂，但分裂后父节点DGMT的n>5，中间节点M向上分裂

![https://gitee.com/yooome/netty-study/raw/main/assets/1555944848294.png](https://gitee.com/yooome/netty-study/raw/main/assets/1555944848294.png)

# B+Tree

## 性质:

1. 数据节点个数:
   1. B+树的每个节点中 最多可以有 分叉数 个数据节点
   2. B  树的每个节点中  最多可以有 分叉数-1 个数据节点
2. 所有的非叶子节点,都可以被视为关键字的索引部分
3. B+树中,由叶子节点来存储数据,,每次查找数据时都通过非叶子节点(作为索引),来进行数据查找
   1. 即,每次查询数据都需要走到b+树的叶子节点,才能找到数据

## MYSQL中的B+TREE

- 对相邻的叶子节点,使用指针相连
  - 更加方便地实行范围搜索,提高区间访问的性能

### 在哪实现:数据库的存储引擎层中

- 每种存储引擎 中的索引结构 不是完全相同的
- 存储引擎 不会支持 所有的 索引结构

### MYSQL 中的索引

- BTREE 索引 (重要)
  - 最常见的索引类型,被大多数存储引擎所支持
  - InnoDB MyISAM Memory 引擎支持
- HASH 索引
  - 仅 Memory 引擎支持,使用场景简单
- R-tree 索引
  - 空间索引,用于地理空间数据类型,使用较少
  - MyISAM引擎支持
- Full-Text 索引
  - 全文索引
  - MyISAM 引擎 支持
  - InnoDB 引擎在 MYSQL5.6 版本后支持

- - 