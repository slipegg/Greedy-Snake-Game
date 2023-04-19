# 贪吃蛇图像版

2020年大一下时期的C++高程大作业——贪吃蛇。实现了5种难度：入门版、进阶版、高级版、趣味版、智障版。

全是自己写的，慢慢从字符串版本迭代到了图形版本，还是有一定的工程量的，但是现在看来写的还是不够规范。

## 入门版

正常的贪吃蛇模式。

![image](https://user-images.githubusercontent.com/65942634/233053004-778abe93-81b4-4325-a395-fbbf060fbc15.png)

## 进阶版

贪吃蛇死了之后会变成墙，直到没有空间可以生成蛇为止就失败。

![image](https://user-images.githubusercontent.com/65942634/233053811-fb85adf2-b924-4a9f-be03-40389d8db2ef.png)

## 高级版

贪吃蛇死后会变成食物。死掉5次就算失败。

![image](https://user-images.githubusercontent.com/65942634/233054219-fc6934e4-1279-4757-9c21-6c771bade958.png)

## 趣味版

游戏规则:血量为0时，游戏结束
有右上加速区,有左下减速区
注意会出现道具吃灭火器左上加z滴血吃雪人左上扣2滴血
上万软墙，碰到蛇长-4卞为通墙，碰到扣2滴血

![image](https://user-images.githubusercontent.com/65942634/233054684-ff0add9a-9580-45b3-839c-19a9e251342c.png)

## 智障版

游戏中会有2条机器蛇，他们会自动去吃身边的最近的食物。

![image](https://user-images.githubusercontent.com/65942634/233055100-2f3193d7-53fe-402c-99e0-384aee87e96c.png)

## 其他界面

菜单界面：

![image](https://user-images.githubusercontent.com/65942634/233052932-bdd6c0ca-c467-4281-9b6b-0563770c41d6.png)

难度选择界面：

![image](https://user-images.githubusercontent.com/65942634/233053084-6b91bdb1-7a7d-46d4-8957-53d75cb04d0b.png)

最高分数界面：

![image](https://user-images.githubusercontent.com/65942634/233056040-21b8d559-e06c-42c1-a863-06d7974d86bd.png)

历史记录界面：

![image](https://user-images.githubusercontent.com/65942634/233056096-d2ce1648-137d-495a-a6a1-21e787f49cc6.png)
