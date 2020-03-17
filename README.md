# Software Engineering  Course - Pair Project

[Homework Page](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10429) 

- ## Features


- A console program that can solve the intersection between simple geometric shapes.

## Usage

| **Option** | **Argument Explanation**                                     | **Example**                                |
| :--------- | :----------------------------------------------------------- | :----------------------------------------- |
| `-i `      | An argument to indicate the path to the input file (absolute or relative). | `intersect.exe -i input.txt -o output.txt` |
| `-o `      | An argument to indicate the path to the output file (absolute or relative). | `intersect.exe -i input.txt -o output.txt` |

## Exception Definition

| 异常代码 | 异常名                         | 异常说明                                                     |
| -------- | ------------------------------ | ------------------------------------------------------------ |
| E100     | WrongFormatOfN                 | N值格式错误（第一行有且仅有一个整数，否则即报错）            |
| E101     | InvalidValueOfN                | N值非法（N<1时报错）                                         |
| E200     | WrongFormatOfObjectIdentifier  | 几何对象标识符格式错误（无标识符，或包含非法字符/字符串，大小写敏感） |
| E300     | WrongFormatOfObjectDescription | 几何对象描述错误（输入格式错误，包括行内输入过多/过少，数字输入非法） |
| E301     | CoordinateValueExceed          | 输入坐标分量超限（包括线的两点坐标分量和圆心坐标分量）       |
| E302     | TwoPointsCoincideOfLine        | 线的两点坐标重合（两点坐标不能相同）                         |
| E303     | InvalidRadiusOfCircle          | 圆的半径非法（半径值必须为正，且在规定范围内）               |
| E400     | ObjectInputTooLittle           | 输入几何对象过少（少于N值）                                  |
| E401     | ObjectInputTooMuch             | 输入几何对象过多（多于N值）                                  |
| E500     | InfiniteIntersectionsFound     | 有无穷多交点                                                 |
| E600     | ElementToDeleteNotFound        | 找不到要删除的元素                                           |

## Example

```bash
intersect.exe -i input.txt -o output.txt
```

*input.txt*

```
4
C 1 0 2
C 2 2 1
C 3 -2 6
L -1 4 4 -1
```

*output.txt*

```
6
```



