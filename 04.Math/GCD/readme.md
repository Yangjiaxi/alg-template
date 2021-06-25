# 最大公约数

Greatest Common Divisor, GCD

## 欧几里得算法

设$a, b (a > b)$，则有

$$
\text{gcd}(a, b) =
\begin{cases}
b & a = b * k \\
\text{gcd}(b, a \bmod b) & a = b*k+c
\end{cases} \\
$$

情况1显而易见，情况2需要证明

$$
\begin{aligned}
& \text{Prove}: \\
& \because a = b*k+c \\
& \therefore c = a \bmod b \\
\\
& \text{Part.1:} \\
& \text{Let} \ d: d|a,\ d|b \\
& \therefore \frac{a}{d} = \frac{b*k}{d} + \frac{c}{d} \\
& \therefore \frac{c}{d} =  \frac{a}{d}-\frac{b*k}{d} \\
& \because \frac{a}{d}, \frac{b*k}{d} \in \mathbb{N} \\
& \therefore \frac{c}{d} \in \mathbb{N} \\
& \therefore \forall{d}:d|a,d|b \implies d|(a \bmod b)\\
\\
& \text{Part.2:} \\
& \text{Let} \ d: d|b,\ d|(a \bmod b) \\
& \therefore \frac{a}{d} = \frac{b*k}{d} + \frac{a \bmod b}{d} \\
& \because \frac{a \bmod b}{d}, \frac{b*k}{d} \in \mathbb{N} \\
& \therefore \frac{a}{d} \in \mathbb{N} \\
& \therefore \forall{d}:d|a,d|(a \bmod b) \implies d|a \\
\end{aligned}
$$

这说明了 $(a, b)$ 与 $(b, a \bmod b)$ 拥有相同的约数（因子），又因为最大公约数为约数之一，则两者的最大公约数相同

因此：

$$
\begin{aligned}
& \text{Let}:a = b*k+c \\
& \text{gcd}(a, b) \equiv gcd(b, a \bmod b) \blacksquare
\end{aligned}
$$

## 最小公倍数

Least Common Multiple, LCM

由于 $\text{lcm}(a, b) * \text{gcd}(a, b) = a * b$

先算出最大公约数，即可得到最小公倍数

设$p_i(1\le i\le s)$为$x$的升序因子，则$x$可唯一地表示为：

自然数引理：

$$
\begin{aligned}
x
& = p_1^{k_1}p_2^{k_2}\cdots p_s^{k_s}\\
& = \prod_{i=1}^{s}p_{i}^{k_{i}}
\end{aligned}
$$

证明：

$$
\begin{aligned}
& a = \prod_{i=1}^{s}p_{i}^{k_{a_i}}\\
& b = \prod_{i=1}^{s}p_{i}^{k_{b_i}} \\
& \therefore \text{gcd}(a, b) = \prod_{i=1}^{s}p_{i}^{\min(k_{a_i}, k_{b_i})} \\
& \therefore \text{lcm}(a, b) = \prod_{i=1}^{s}p_{i}^{\max(k_{a_i}, k_{b_i})} \\
& \because a+b = \min(a, b) + \max(a, b) \\
& \therefore \text{lcm}(a, b)*\text{gcd}(a, b) \\
& \quad = \prod_{i=1}^{s}p_{i}^{k_{a_i}+k_{b_i}}  \\
& \quad = \prod_{i=1}^{s}p_{i}^{k_{a_i}}*\prod_{i=1}^{s}p_{i}^{k_{b_i}}  \\
& \quad = a * b \\
& \therefore \text{lcm}(a, b) = \frac{a*b}{\text{gcd}(a, b)}
\end{aligned}
$$

## 扩展欧几里得定理

Extended Euclidean algorithm, ExGCD

已知整数$a$、$b$，扩展欧几里得算法可以在求得$a$、$b$的最大公约数的同时，能找到整数$x$、$y$（其中一个很可能是负数），使它们满足贝祖等式

$$
ax+by = \text{gcd}(a, b)
$$

算法：

$$
\begin{aligned}
& \text{Given}: ax_1 + by_1 = \text{gcd}(a, b) \\
& \text{Let}: bx_2+ (a \bmod b)y_2 = \text{gcd}(b, a \bmod b) \\ \\
& \because \text{gcd}(a, b) \equiv \text{gcd}(b, a \bmod b) \\
& \therefore ax_1 + by_1 = bx_2+ (a \bmod b)y_2 = \text{gcd}(a, b) \\
& \because a \bmod b = a - \lfloor\frac{a}{b}\rfloor*b \\
& \therefore ax_1 + by_1 \\
& \quad = bx_2+ (a - \lfloor\frac{a}{b}\rfloor*b)y_2 \\
& \quad = ay_2 + b(x_2 - \lfloor\frac{a}{b}\rfloor y_2) \\
& \therefore
\begin{cases}
x_1 =& y_2 \\
y_1 =& x_2 - \lfloor\frac{a}{b}\rfloor y_2
\end{cases}
\end{aligned}
$$
