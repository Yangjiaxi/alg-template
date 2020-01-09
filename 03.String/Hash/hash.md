# 基于哈希的字符串匹配

> 其实就是 Java 的 Comparable（小声比比）

基本思想：将字母表的闭包域内的对象（字符串）映射到正整数值域，使其易于比较。

对于两个字符串 `sa` 与 `sb` 有其哈希 `ha` 与 `hb` ：

- 若`ha != hb`，则 `sa != sb`
- 若`ha == hb`，则无法直接确定字符串是否相等

魔数：13331, 10007

题目描述：给出一字符串与n个查询，每个查询为[l, r]区间，返回每个区间不重复的子串个数

基本思路：

定义字符串的映射表示：

$$
\text{F}(str[i...i+T-1]) = \sum_{k=i}^{i+T-1}str_k * \text{SEED}^{i+T-1-k} \\
$$

定义一些辅助序列：

$$
\begin{aligned}
P_i & = \text{SEED}^i \\
S_i &= S_{i-1} * \text{SEED} + \text{str}_{i-1} \\
\therefore S_i &= \sum_{k=0}^{i-1} \text{str}_k * \text{SEED} ^{i-1-k}
\end{aligned}
$$

从下标 $a$ 开始，长度为 $L$ 的子串：

$$
\begin{aligned}
S_a &= \sum_{k=0}^{a-1} \text{str}_k * \text{SEED} ^{a-1-k} \\
S_{a+L} &= \sum_{k=0}^{a+L-1} \text{str}_k * \text{SEED} ^{a+L-1-k} \\
\end{aligned}
$$

因此：

$$
\begin{aligned}
S_{a+L} - S_a * P_L &= \sum_{k=0}^{a+L-1} \text{str}_k * \text{SEED} ^{a+L-1-k} - \sum_{k=0}^{a-1} \text{str}_k * \text{SEED} ^{a+L-1-k} \\
&= \sum_{k=a}^{a+L-1} \text{str}_k * \text{SEED} ^{a+L-1-k}
\end{aligned}
$$

相当于从下标 $a$ 开始重新计算

因此：预先计算 $P$ 与 $S$，即可快速求得从 $a$ 开始，长度为 $L$ 的子串的映射。
