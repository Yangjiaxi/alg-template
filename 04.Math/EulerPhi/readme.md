# 欧拉函数

欧拉函数：$\varphi(n)$，表示小于等于$n$的数中，与$n$互质的数的个数

$$
\varphi(n) = \sum_{x=1}^{n}\mathbb{I}[\text{gcd}(n, x) = 1]
$$

考虑自然数的质数分解定理

$$
n = p_1^{k_1}p_2^{k_2}\cdots p_r^{k_r}
$$

有积形式

$$
\varphi(n) = n\prod_{p_i | n}(1 - \frac{1}{p_i})
$$

例如

$$
\begin{aligned}
& 24 = 2^3 * 3^1\\
& \varphi(24) = 24 * (1 - 1 / 2) * (1 - 1 / 3) = 8 \\ \\
& 98 = 2^1*7^2 \\
& \varphi(98) = 98 * (1 - 1 / 2) * (1 - 1 / 7) = 42 \\
\end{aligned}
$$

## 性质

- $\varphi(1) = 1$
- 对于质数$n$，有$\varphi(n) = n-1$
- 「积性函数」 若$\text{gcd}(a, b) = 1$，有$\varphi(ab) = \varphi(a)\varphi(b)$
- 一般有：$\varphi(ab) = \varphi(a)\varphi(b)\frac{d}{\varphi(d)}$，其中$d = \text{gcd}(a, b)$
- 若$n$为奇数，则$\varphi(2n)=\varphi(n)$
