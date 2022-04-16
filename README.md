# 基于composite模式实现多种形状相关的操作。
1.  抽象基类形状(Shape).
2. 具体形状有三角形(triangle，用三条边长表示)、正方形(square)、长方形(rectangle)、梯形(trapezium，用上底、下底和左右边长表示)、圆形(round)、复合形状(compoundshape)。这些形状都是由Shape派生。
3. 复合形状是指由多个形状组成的形状，组成复合形状的形状可以是普通形状，也可以是复合形状
