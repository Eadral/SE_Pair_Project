# 软件工程结对项目

  [作业要求](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10466)

## 功能


- `bin\intersect.exe`  CLI程序，计算交点数量
- `bin\GUI.exe`  GUI程序

## 使用方法

`bin\intersect.exe`

| 选项  | 参数                       | 样例                                       |
| :---- | :------------------------- | :----------------------------------------- |
| `-i ` | 输入文件路径（相对或绝对） | `intersect.exe -i input.txt -o output.txt` |
| `-o ` | 输出文件路径（相对或绝对） | `intersect.exe -i input.txt -o output.txt` |

`bin\GUI.exe`  

![image-20200324111051492](C:\Study\S6\Software\SE_Pair_Project\README.assets\image-20200324111051492.png)

- Import：导入文本描述文件
- Add：添加图形
- Remove：删除图形 （可在列表中进行选择）
- 左侧画布支持鼠标滚轮缩放以及拖拽



## 异常定义

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

## 样例

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



