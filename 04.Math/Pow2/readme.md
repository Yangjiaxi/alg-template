# 快速幂

## 普通快速幂

```javascript
a^n =
A. n = 0     => 1
B. n = 2*k   => (a^(n/2)) * (a^(n/2))
C. n = 2*k+1 => (a^(n/2)) * (a^(n/2)) * a
```

分治即可

## 取模快速幂

`a*b mod m === ((a mod m) * (b mod m)) mod m`

### 如果b是素数

根据费马小定理：

$a$是整数，$m$是质数，根据

$$
a^{m-1} \equiv 1 \pmod m
$$

设

$$
b = (m-1) * k + c \\
c = b \bmod (m-1)
$$

则有

$$
\begin{aligned}
& a^b &\bmod m \\
&= a^{(m-1)*k+c} &\bmod m \\
&= (a^{(m-1)*k} \bmod m) * (a^c \bmod m) &\bmod m \\
&= ((\underline{a^{m-1} \bmod m})^k\bmod m) * (a^c \bmod m) &\bmod m \\
&= (1)^k * (a^c \bmod m) &\bmod m\\
&= a^c &\bmod m\\
&= a^{b \bmod (m-1)} &\bmod m\\
\end{aligned}
$$

因此，可用$a^{b \bmod (m-1)}$加速计算
