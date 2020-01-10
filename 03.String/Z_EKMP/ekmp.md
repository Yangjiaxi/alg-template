# Z函数(扩展 KMP)

## Z函数

也称作扩展 KMP

一个字符串的Z函数定义为一个与字符串等长的数组`z[]`

其中`z[i]`表示：原字符串`s`与从`i`开始的子串`s[i..]`的最长公共前缀的长度

`z[0]`不是严格定义的，但习惯上强制定义为`0`

e.g.

```javascript
Z("aaabaab") = [0,2,1,0,2,1,0]
```

## 思路

与Manacher算法极为相似：利用对称性与之前计算出的部分，使得当前循环变小。

同样，维护一对子串的边界`(l, r)`，这个子串是目前找到的**最靠右**的子串

对称性：`s[0..r-l] == s[l..r]` (**重要**)

如果当前的`i`超出了`r`，则使用朴素算法扩展`z[i]`

否则，就利用对称性给予`z[i]`以初值，然后再用朴素算法扩展`z[i]`

从对称性可知，`l..i..r`相当于`0..x..r-l`，推算可知`x=i-l`，因此可用`z[i-l]`初始化`z[i]`

注意：如果对称侧所指出的`z[i-l]`超出了`r`的范围，则要用`r-i+1`来初始化`z[i]`，因为在`r`右侧的部分不被先前的计算结果保证。

ps: 真的好像 `Manacher`

pss: 太像了！

## 时间复杂度

`T(n) = O(n)`