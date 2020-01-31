# 莫比乌斯反演

## 引入

定义函数

$$
F(n) = \sum_{d|n}f(d)
$$

因此

$$
\begin{aligned}
F(1) & =f(1)\\
F(2) & =f(1)+f(2)\\
F(3) & =f(1)+f(3) \\
F(4) & =f(1)+f(2)+f(4)\\
F(5) & =f(1)+f(5)\\
F(6) & =f(1)+f(2)+f(3)+f(6)\\
F(7) & =f(1)+f(7)\\
F(8) & =f(1)+f(2)+f(4)+f(8)\\
F(9) & =f(1)+f(3)+f(9) \\
\end{aligned}
$$

反推有

$$
\begin{aligned}
f(1) & = F(1)\\
f(2) & = F(2)-F(1)\\
f(3) & = F(3)-F(1)\\
f(4) & = F(4)-F(2)\\
f(5) & = F(5)-F(1)\\
f(6) & = F(6)-F(3)-F(2)+F(1)\\
f(7) & = F(7)-F(1)\\
f(8) & = F(8)-F(4)\\
f(9) & = F(9)-F(3)
\end{aligned}
$$

则有反演公式**猜想**

$$
f(n) = \sum_{d|n}\mu(d)F(\frac{n}{d})
$$

其中$\mu(\cdot)$为莫比乌斯函数

## 莫比乌斯函数

$$
\mu(d)=
\begin{cases}
1 & d=1 \\
(-1)^k & d=p_1p_2\cdots p_k \\
0 & \text{otherwise}
\end{cases}
$$

对case-2解释：对自然数$d$进行素数分解后，其因子项的最高次数为$1$，$k$为互异素因子的个数。

因此，有$\mu(d)$

$$
\begin{aligned}
& \mu(1) & = &&1\\
& \mu(2) & = &&-1\\
& \mu(3) & = &&-1\\
& \mu(4:2^2) & = &&0\\
& \mu(5) & = &&-1\\
& \mu(6) & = &&1\\
& \mu(7) & = &&-1\\
& \mu(8:2^2*2) & = &&0\\
& \mu(9:3^2) & = &&0\\
\end{aligned}
$$

## 性质

### 1. 因子的莫比乌斯函数和

$$
\begin{aligned}
\sum_{d|n}\mu(d)
& =
\begin{cases}
1 & n = 1\\
0 & \text{otherwise} \\
\end{cases} \\
& = [n=1] \\
& = \varepsilon(n)

\end{aligned}

$$

对情况2的证明：

对于自然数$n>1$，可以分解为

$$n=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$$

则因子$d$可以表示为

$$
d=p_{t_1}^{a_{t_1}}\cdots p_{t_r}^{a_{t_r}}
$$

若要$\mu(d) \not={0}$，则$t_k=1$，则

$$
d'=p_{t_1}\cdots p_{t_r}
$$

设$d'$由$r$个互异素因子的乘积构成，则$d'$的产生方案有$\binom{k}{r}$种，其中$k$为$n$的互异素因子总个数

于是原式变为

$$
\sum_{d|n}\mu(d)=\sum\mu(d')=\sum_{r=0}^{k}(-1)^r\binom{k}{r}
$$

根据二项式定理知

$$
(a+b)^n=\sum_{i=0}^n\binom{n}{i}a^{n-i}b^i
$$

取$a=1, b=-1$，代入即可得证：若$n>1$，有

$$
\sum_{d|n}\mu(d)=0 \quad \blacksquare
$$

### 2. 积性函数

若$\gcd(a, b)=1$，则$\mu(ab)=\mu(a)\cdot\mu(b)$

由于$a, b$没有相同的质因子，该结论易得

由于莫比乌斯函数具有积性函数的性质，则可以利用线性筛在$\text{O}(n)$的复杂度下求出

## 莫比乌斯反演定理

### 证明

$$
\begin{aligned}
& F(n) = \sum_{d|n}f(d) \\
\implies & f(n) = \sum_{d|n}\mu(d)F(\frac{n}{d})
\end{aligned}
$$

证明：

$$
\begin{aligned}
f(n)
&\coloneqq \sum_{d|n}\mu(d)F(\frac{n}{d})\\
&= \sum_{d|n}\mu(d)\sum_{k|\frac{n}{d}}f(k) \\
&= \sum_{d|n}f(d)\sum_{k|\frac{n}{d}}\mu(k) \\
&= \sum_{d|n}f(d)[\frac{n}{d}=1] \\
&= \sum_{d|n}f(d)[d=n] \\
&= f(n) \quad \blacksquare
\end{aligned}
$$

### 应用

观察$f(n)$的形式

$$
f(n)= \sum_{d|n}\mu(d)F(\frac{n}{d})
$$

对于某一$n$，若$f(n)$不易求得，但$n$的约数$\{d\}$与约数的函数和$F(n) = \sum_{d|n}f(d)$易于求得，则可以通过对$F(n)$进行莫比乌斯反演来求得$f(n)$

### 1. 包含函数等式的真假项

$$
\begin{aligned}
& \mathbb{I}[f(n) = 1] \\
=& \varepsilon(f(n)) \\
=& \sum_{d|f(n)} \mu(d)
\end{aligned}
$$

例如：

求$\sum_{x=a}^b\sum_{y=c}^d\mathbb{I}[\gcd{(x, y)}=k]$，其中$a,b,c,d,k$为参数

利用容斥原理，将结果转化为

$$
\begin{aligned}
& Q(a\to{b}, c\to{d}) \\
& = Q(b, d) + Q(a, c) - Q(a, d) - Q(b, c) \\
\end{aligned}
$$

其中

$$
Q(m,n) = \sum_{x=1}^m\sum_{y=1}^n\mathbb{I}[\gcd{(x, y)}=k]
$$

由于$\gcd(x, y)=k \implies \gcd(\frac{x}{k}, \frac{y}{k})=1$

因此

$$
Q(m,n) = \sum_{x=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{y=1}^{\lfloor\frac{n}{k}\rfloor}\mathbb{I}[\gcd{(x, y)}=1]
$$

使用$\varepsilon(\cdot)$变化

$$
Q(m,n) = \sum_{x=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{y=1}^{\lfloor\frac{n}{k}\rfloor}\varepsilon(\gcd{(x, y)}=1)
$$

引入莫比乌斯反演

$$
Q(m,n) = \sum_{x=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{y=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{d|\gcd{(x, y)}}\mu(d)
$$

假设$m\le n$

考虑这个三重求和式子所表达的语义：对于范围内的$(x, y)$，若$d|\gcd(x, y)$，即$x, y$均为$d$的倍数，则将$\mu(d)$的贡献纳入

那么，通过交换语义来交换求和符号的顺序：对于一个范围内的$d(1\le d\le \lfloor\frac{m}{k}\rfloor)$，若在一个二维范围内$x, y$均为$d$的倍数，则将$\mu(d)$的贡献纳入

则原式变为

$$
Q(m,n) = \sum_{d=1}^{\lfloor\frac{m}{k}\rfloor}\mu(d)\sum_{x=1}^{\lfloor\frac{m}{k}\rfloor}\mathbb{I}[d|x]\sum_{y=1}^{\lfloor\frac{n}{k}\rfloor}\mathbb{I}[d|y]
$$

后面两个求和符号表达的语义为：范围$(1, \lfloor \cdot \rfloor)$内，$d$的倍数的个数，因此可以化简为

$$
Q(m,n) = \sum_{d=1}^{\lfloor\frac{m}{k}\rfloor}\mu(d)\lfloor \frac{m}{kd}\rfloor\lfloor \frac{n}{kd}\rfloor
$$

使用数论分块即可求解

### 2. 一维gcd和

$$
\sum_{i=1}^n\gcd(i, n)
$$

同理，枚举$\forall{d}$满足

$$d=\gcd(i, n)$$

其贡献需要乘以$d$的出现次数，即导致$\gcd(i,n)=d$的$i$的数量

考虑$d$等同于形式

$$
gcd(\frac{i}{d}, \frac{n}{d}) = 1
$$

其中$n$为输入参数，$i$为变量，其范围$1\le i \le n$，因此该式的含义为：$1$到$\frac{n}{d}$中，与$\frac{n}{d}$互质的数

因此可以转换为对$\frac{n}{d}$的欧拉函数的计算

$$
\text{Count}(d)=\varphi(\frac{n}{d})
$$

因此，$d$的贡献为

$$
d\cdot\varphi(\frac{n}{d})
$$

代回原式，可得

$$
\sum_{i=1}^n\gcd(i, n) = \sum_{d|n}d\cdot \varphi(\frac{n}{d})\qquad \blacksquare
$$

### 3. 一维lcm和

$$
\sum_{i=1}^n\text{lcm}(i, n)
$$

使用恒等式进行变形

$$
\text{LHS}=\sum_{i=1}^n\frac{i\cdot n}{\gcd(i, n)}
$$

提取边界$i=n$，有

$$
\text{LHS}=n+\sum_{i=1}^{n-1}\frac{i\cdot n}{\gcd(i, n)}
$$

考虑等式$\gcd(i, n) = \gcd(n-i, n)$的对称性，则可以化为

$$
\begin{aligned}
&\text{LHS}\\
&=n+\frac{1}{2}[\sum_{i=1}^{n-1}\frac{i\cdot n}{\gcd(i, n)}+\sum_{i=1}^{n-1}\frac{(n-i)\cdot n}{\gcd(n-i, n)}]\\
&=n+\frac{1}{2}\sum_{i=1}^{n-1}\frac{n^2}{\gcd(i, n)} \\
&=\frac{1}{2}n +\frac{1}{2}\sum_{i=1}^n\frac{n^2}{\gcd(i, n)}\\
\end{aligned}
$$

同理，枚举$d=\gcd(i, n)$，每个$d$的贡献次数同理为$\varphi(\frac{n}{d})$，因此可化为

$$
\begin{aligned}
&\text{LHS}\\
&=\frac{1}{2}n +\frac{1}{2}\sum_{d|n}\frac{n^2\cdot\varphi(\frac{n}{d})}{d}\\
&=\frac{1}{2}n +\frac{1}{2}n\sum_{d|n}\frac{n\cdot\varphi(\frac{n}{d})}{d}\\
\end{aligned}
$$

考虑因子$d$与$\frac{n}{d}$的等价性，则可以化简

$$
\begin{aligned}
&\text{LHS}\\
&=\frac{1}{2}n +\frac{1}{2}n\sum_{d|n}d\cdot\varphi(d)\\
&=\frac{1}{2}n(1+\sum_{d|n}d\cdot \varphi(d)) \\
\end{aligned}
$$

因此

$$
\sum_{i=1}^n\text{lcm}(i, n) = \frac{1}{2}n(1+\sum_{d|n}d\cdot \varphi(d)) \qquad \blacksquare
$$

### 4. 二维gcd和

设$n\le m$

$$
\sum_{i=1}^n\sum_{j=1}^m\gcd(i, j)
$$

同理，枚举$d=\gcd(i, j)$，由于$d$同时为$i, j$的因数，且由于欧拉函数性质

$$
n=\sum_{d|n}\varphi(d)
$$

因此

$$
\gcd(i, j)= \sum_{d|i, d|j}\varphi(d)
$$

代回原式

$$
\begin{aligned}
& \text{LHS} \\
&= \sum_{i=1}^n\sum_{j=1}^m\sum_{d|i, d|j}\varphi(d)
\end{aligned}
$$

更改求和顺序

$$
\begin{aligned}
& \text{LHS} \\
&= \sum_{d=1}^n\varphi(d)\sum_{i=1}^n\sum_{j=1}^m\mathbb{I}[d|i]\mathbb{I}[d|j]\\
&= \sum_{d=1}^n\varphi(d)\lfloor\frac{n}{d}\rfloor \lfloor\frac{m}{d}\rfloor\\
\end{aligned}
$$

因此

$$
\sum_{i=1}^n\sum_{j=1}^m\gcd(i, j) = \sum_{d=1}^n\varphi(d)\lfloor\frac{n}{d}\rfloor \lfloor\frac{m}{d}\rfloor \qquad \blacksquare
$$

### 5. 二维lcm和

设$n\le m$

$$
\sum_{i=1}^n\sum_{j=1}^m\text{lcm}(i, j)
$$

进行恒等变形

$$
\begin{aligned}
& \text{LHS} \\
&= \sum_{i=1}^n\sum_{j=1}^m\frac{i\cdot j}{\gcd(i, j)}
\end{aligned}
$$

同理枚举$d=\gcd(i,j)$

$$
\begin{aligned}
& \text{LHS} \\
&= \sum_{d=1}^n d\sum_{i=1}^n\sum_{j=1}^m i\cdot j\cdot\mathbb{I}[\gcd(i, j)=d] \\
&= \sum_{d=1}^n d\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor} i\cdot j\cdot\mathbb{I}[\gcd(i, j)=1] \\
&= \sum_{d=1}^n d\cdot \alpha(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)
\end{aligned}
$$

其中，定义

$$
\alpha(n, m) = \sum_{i=1}^{n}\sum_{j=1}^{m} i\cdot j\cdot\mathbb{I}[\gcd(i, j)=1]
$$

使用莫比乌斯反演$\varepsilon(\cdot)$

$$
\begin{aligned}
&\alpha(n, m) \\
& = \sum_{i=1}^{n}\sum_{j=1}^{m} i\cdot j\cdot\varepsilon(\gcd(i, j)) \\
&= \sum_{d=1}^n\mu(d)\sum_{d|i}^ni\sum_{d|j}^mj \\
&= \sum_{d=1}^nd^2\cdot\mu(d)\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}i\cdot j \\
&= \sum_{d=1}^nd^2\cdot\mu(d)\cdot\beta(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor) \\
\end{aligned}
$$

其中，定义

$$
\begin{aligned}
& \beta(n, m)\\
& = \sum_{i=1}^n\sum_{j=1}^mi\cdot j\\
& = \frac{m(m+1)}{2}\cdot \frac{n(n+1)}{2}
\end{aligned}
$$

没有循环运算，可以直接求得

因此，整理可得

$$
\begin{aligned}
& \sum_{i=1}^n\sum_{j=1}^m\text{lcm}(i, j) = \sum_{d=1}^n d\cdot \alpha(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor) \\ \\
& \alpha(n, m) =\sum_{d=1}^nd^2\cdot\mu(d)\cdot\beta(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor) \\ \\
& \beta(n, m) = \frac{m(m+1)}{2}\cdot \frac{n(n+1)}{2} \qquad \blacksquare
\end{aligned} \\
$$
