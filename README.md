# DiceRobot kills you 3000
[![License](https://img.shields.io/github/license/dynilath/coolq-dicebot.svg)](LICENSE)
[![Build Status](https://img.shields.io/appveyor/ci/dynilath/coolqdicebot.svg)](https://ci.appveyor.com/project/dynilath/coolqdicebot)  
Just a simple dicebot for coolq in development.  
只是一个简单的酷Q骰子机器人。  
![image](/dicebot_test.gif)   
感谢@niunuinui 在文档制作上的帮助。

# 特性
* 所有的骰子指令支持多行输入。  
* 使用硬件随机器，如果硬件随机器不可用，则改用mt19937随机器。  
* 支持coc7的奖惩骰。  
* 可以识别整数、小数、百分数。  

# 安装
点击[下载cpk](https://github.com/dynilath/coolq-dicebot/releases/latest)前往下载本骰子机器人最新cpk。  
点击[获取酷Q](https://cqp.cc/)前往酷Q官网下载酷Q。    
点击[酷Q wiki](https://d.cqp.me/Pro/%E6%96%B0%E6%89%8B%E4%B8%8A%E8%B7%AF)前往酷Qwiki了解如何使用酷Q以及插件如何安装。  
  
# 实例  
QQ：1701687847  
它能够自动接受好友请求和加群邀请。请温柔对待它。  

# 目录
<!-- TOC -->

- [help](#help)
- [基本骰子指令(.roll或.r)](#基本骰子指令roll或r)
    - [骰子基础](#骰子基础)
    - [双/三/四骰取高/低](#双三四骰取高低)
    - [多行输入](#多行输入)
    - [骰子加入算式](#骰子加入算式)
    - [开启/关闭详细结果(.roll source on/off)](#开启关闭详细结果roll-source-onoff)
- [骰子专用的昵称(.name或.n)](#骰子专用的昵称name或n)
    - [不回复地更改昵称(.name silence或.ns)](#不回复地更改昵称name-silence或ns)
- [定义骰子(.set或.s)](#定义骰子set或s)
    - [默认骰子](#默认骰子)
- [定义变量(.var或.v)](#定义变量var或v)
- [展示变量和骰子(.list或.l)](#展示变量和骰子list或l)
    - [全部展示(.list all)](#全部展示list-all)
    - [展示骰子(.list roll或.lr)](#展示骰子list-roll或lr)
    - [展示变量(.list var或.lv)](#展示变量list-var或lv)
- [删除变量和骰子(.delete或.d)](#删除变量和骰子delete或d)
    - [全部删除(.delete all)](#全部删除delete-all)
    - [删除骰子(.delete roll或.dr)](#删除骰子delete-roll或dr)
    - [删除变量(.delete var或.dv)](#删除变量delete-var或dv)
- [为特定规则定制的骰子](#为特定规则定制的骰子)
    - [coc定制骰子(.coc或者.c)](#coc定制骰子coc或者c)
    - [wod定制骰子(.wod或者.w)](#wod定制骰子wod或者w)
    - [FATE定制骰子(.fate或.f)](#fate定制骰子fate或f)
- [手动骰子(.manual或.m)](#手动骰子manual或m)

<!-- /TOC -->

# 使用示范
## help
发送```.help```获取没啥用的帮助信息。
> dynilath：```.help```

> DiceBot：
> ``` 
> DiceBot by dynilath v1.6.0
> 访问项目主页http://github.com/dynilath/coolq-dicebot
> 获得使用说明以及了解更多内容。
> 使用方式简介：
> .r 1d8+1d6+3 普通骰子
> .c coc骰子
> .wo4 owod骰子
> .wn4 nwod骰子
> .f FATE骰子
> 详细指令参考请前往项目主页。
> 如果在使用中遇到了bug，或者有什么功能建议，欢迎在项目主页通过issue反馈，感谢您的帮助。
> ```

## 基本骰子指令(.roll或.r)
### 骰子基础
让我们先骰一个d20试试。  
> dynilath：```.rd20```     
> DiceBot：``` * dynilath 掷骰: d20 = 20```

你只需要在开头写上```.r```再加上骰子（例如```d20```、```4d6```）。  
骰子的基本格式为```XdY```，```X```表示骰子个数，```Y```表示骰子面数。当然，你在TRPG规则书里肯定已经看过无数次了。  

这个结构也可以用下面的文字表示：  
``` . r [骰子个数]d[骰子面数]```  
发送这个消息，骰子机器人就能识别你的消息并回复一个骰子结果。  

在骰子指令后面加上一些文本，可以作为描述。  
> dynilath：```.rd20攻击```     
> DiceBot：``` * dynilath 攻击 掷骰: d20 = 6```

有时候你会需要骰几种不同的骰子，可以发送如下信息。  
> dynilath：```.rd20+d6+2d4```
> DiceBot：``` * dynilath 掷骰: d20 + d6 + 2d4 = [12] + [4] + [4 + 4] = 24```

### 骰子机器人回复格式
骰子机器人发送的信息组成结构如下：  
``` * [你的QQ昵称/群名片] [骰子描述] 掷骰: [骰子指令] = [骰子详细] = [结果]```  
群名片就是你使用骰子所在的群中你的群名片，如果是讨论组则使用昵称。  
骰子描述即你输入的骰子（例如```d20```、```4d6```）。  
结果即最终计算得到的数值。
需要说明的是，```4d6k3```或者```2d6```这样的组视为一个完整的“骰子标志”，它们在输出的时候会被```[   ]```包括起来。    

### 双/三/四骰取高/低
你可以在骰子指令后加上```k[数值]```或者```kl[数值]```来只取部分结果。  
其中```k[数值]```表示保留较高结果，```kl[数值]```表示较低结果。  
下面的例子是骰4d6并保留3个较高的结果（即扔掉较低的那个）。  
> dynilath：```.r4d6k3```       
> DiceBot：``` * dynilath 掷骰: 4d6k3 = [5 + 3 + 5 + 1*] = 13```  

被忽略的数值会在其后面用```*```号标记，它不会算入到总和中。   

### 多行输入
骰子机器人支持一次输入多行，如下所示：
> dynilath：
> ```
> .r 1d20 + 1d6-3+4+11 破邪斩+猛力攻击
> .r 5d4 * 150%
> ```

> DiceBot：
> ```
> * dynilath 破邪斩+猛力攻击 掷骰: 1d20 + 1d6 - 3 + 4 + 11 = [13] + [4] - 3 + 4 + 11 = 29
> * dynilath 掷骰: 5d4 * 150% = [4 + 3 + 1 + 3 + 1] * 150% = 18
> ```

可能下面的场景你会经常遇到：  
> dynilath：
> ```
> .r4d6k3 力量
> .r4d6k3 敏捷
> .r4d6k3 体质
> .r4d6k3 智力
> .r4d6k3 感知
> .r4d6k3 魅力
> ```

> DiceBot：
> ```
> * dynilath 力量 掷骰: 4d6k3 = [3 + 2 + 4 + 1*] = 9
> * dynilath 敏捷 掷骰: 4d6k3 = [3 + 3 + 4 + 1*] = 10
> * dynilath 体质 掷骰: 4d6k3 = [6 + 1* + 2 + 2] = 10
> * dynilath 智力 掷骰: 4d6k3 = [3 + 1* + 4 + 3] = 10
> * dynilath 感知 掷骰: 4d6k3 = [2* + 5 + 4 + 4] = 13
> * dynilath 魅力 掷骰: 4d6k3 = [6 + 1* + 5 + 3] = 14
> ```

输出的顺序完全按照你的输入顺序，并且如果存在不符合规范的行，能够单独忽略。  
> dynilath：
> ```
> .r4d6k3 力量
> 这行是来捣乱的
> .r4d6k3 敏捷
> ```

> DiceBot：
> ```
> * dynilath 力量 掷骰: 4d6k3 = [6 + 1* + 6 + 6] = 18
> * dynilath 敏捷 掷骰: 4d6k3 = [3 + 5 + 2 + 2*] = 10
> ```  

### 骰子加入算式    
不用担心，骰子机器人是支持算式的。  
> dynilath：```.r(((4d6+3)/2+2d20)+4*1d6)*150%```     
> DiceBot：``` * dynilath 掷骰: (((4d6 + 3) / 2 + 2d20) + 4 * 1d6) * 150% = ((([3 + 5 + 4 + 5] + 3) / 2 + [9 + 14]) + 4 * [3]) * 150% = 67.5```  

当然，如果你的算式输入格式有问题，多余的部分会被识别成骰子描述。  
> dynilath：```.r4d6+(((4d6+3)/2+2d20)+4*1d6```     
> DiceBot：``` * dynilath +(((4d6+3)/2+2d20)+4*1d6 掷骰: 4d6 = [5 + 1 + 4 + 3] = 13```  

### 开启/关闭详细结果(.roll source on/off)
你可以使用```.roll source off```来关闭具体每个骰子结果为多少的输出。    
你也可以使用它较短的形式```.rs off```。   
> dynilath：```.roll source off```      
> DiceBot：``` * dynilath 关闭骰子详细输出```  

在这之后，你的骰子指令不会再输出详细每个骰子的结果，只会给出一个最终结果。
> dynilath：```.r(((4d6+3)/2+2d20)+4*1d6)*150%```   
> DiceBot：``` * dynilath 掷骰: (((4d6 + 3) / 2 + 2d20) + 4 * 1d6) * 150% = 90```  

你可以使用```.roll source on```来重新开启详细输出。     
除此之外，即使在```.roll source off```状态下，你也可以使用```.roll source```替换本来的```.r```。    
此时仍然会产生详细输出。你也可以使用它较短的形式```.rs```。   

## 骰子专用的昵称(.name或.n)
使用```.name```指令来指定一个仅在骰子机器人的回复文本中使用的名字。  
你也可以使用它较短的形式```.n```。    
在指令后跟随的文本会被保存起来，并代替之前所述的```[你的QQ昵称/群名片]```部分  
> dynilath：```.n菜鸟PC```      
> DiceBot：``` * dynilath 的新名字是 菜鸟PC```  

在这之后使用骰子指令时，昵称部分会使用这个名字。  
> dynilath：```.r4d6k3 力量```      
> DiceBot：``` * 菜鸟PC 力量 掷骰: 4d6k3 = [5 + 4 + 1* + 4] = 13```  

这个昵称在每个群/讨论组之间是独立的，在A群的设置不会影响在B群的状态。  
昵称保存在数据库中，关闭开启不会取消已经设置的昵称。  
如果需要维护这部分内容，骰子机器人使用sqlite3数据库。在插件目录下可以找到.db文件。  

### 不回复地更改昵称(.name silence或.ns)
除此之外，你也可以使用```.ns```，完整指令为```.name silence```来更改昵称，这个时候骰子机器人不会回复消息。  
> dynilath：
> ```
> .ns 迷诱魔
> .r 1d20+20
> .ns 反pal魅魔
> .r 1d20+24破善斩
> ```

> DiceBot：
> ```
> * 迷诱魔 掷骰: 1d20 + 20 = [7] + 20 = 27
> * 反pal魅魔 破善斩 掷骰: 1d20 + 24 = [9] + 24 = 33
> ```  

当然，这会令```.n silence```失效，如果你一定要把自己的昵称弄成```silence```，请使用```.name silence silence```。

## 定义骰子(.set或.s)
使用```.set```指令来设定一个骰子。  
你也可以使用它较短的形式```.s```。    
> dynilath：```.s 1d20+14 猛力攻击```   
> DiceBot：``` * dynilath 设置骰子指令: 1d20 + 14 为 猛力攻击```  

在你已经设置了一个骰子之后，你可以直接使用```.r[指令名称]```来使用该骰子。
> dynilath：```.r 猛力攻击```   
> DiceBot：``` * dynilath 掷骰: 1d20 + 14 = [14] + 14 = 28```  

你可以可以添加一些描述，但是注意使用空格分隔。  
> dynilath：```.r 猛力攻击 他死定了```  
> DiceBot：``` * dynilath 他死定了 掷骰: 1d20 + 14 = [4] + 14 = 18``` 

注意：骰子指令名称不能使用+-*/和空格。

### 默认骰子
如果你在定义骰子时，没有指定骰子名称，则会设置一个默认骰子。
> dynilath：```.s 4d6+3```  
> DiceBot：``` * dynilath 设置默认骰子指令: 4d6 + 3```  

如果你已经设置了默认骰子，使用```.r```就可以使用默认骰。    
> dynilath：```.r```    
> DiceBot：``` * dynilath 掷骰: 4d6 + 3 = [4 + 4 + 5 + 3] + 3 = 19```  

如果你写了一些没有和其他骰子定义重叠的描述，也会正常识别成描述。
> dynilath：```.r blahblahblah```   
> DiceBot：``` * dynilath blahblahblah 掷骰: 4d6 + 3 = [1 + 6 + 2 + 2] + 3 = 14``` 

## 定义变量(.var或.v)
使用```.var```指令来设定一个变量。  
你也可以使用它较短的形式```.v```。    
> dynilath：```.v 4 1环法术```  
> DiceBot：``` * dynilath 设置: 1环法术 值为 4```  

在你已经设置了一个变量之后，你可以使用```.var +```或```.var -```来修改变量。
> dynilath：```.v -1 1环法术```     
> DiceBot：``` * dynilath 修改: 1环法术 值为 3```  

你可以使用```.var reset```来重置变量为初始值。
> dynilath：```.v reset```      
> DiceBot：``` * dynilath 重置所有值。```  

注意：变量指令名称不能使用+-*/和空格，变量值只能为整数。    

## 展示变量和骰子(.list或.l)
### 全部展示(.list all)
使用```.list all```指令来显示你所保存的所有数据。  
你也可以使用它较短的形式```.l all```，很遗憾这里的```all```并不能缩写成```a```。    
> dynilath：```.lall```

> DiceBot：
> ``` 
> * dynilath 的个人信息如下: 
> 默认骰子: 
> > 4d6 + 3 
> 已设置下列骰子指令: 
> > 法术骰 : 1d20 + 13 
> > 猛力攻击 : 1d20 + 14 
> 已设置下列变量: 
> > 1环法术 : 3 / 4 
> > 2环法术 : 3 / 3 
> > bab : 4 / 4
> ```  

### 展示骰子(.list roll或.lr)
使用```.list roll```指令来只显示你所保存的骰子。    
当然你也可以用```.lr```。  
> dynilath：```.lr```

> DiceBot：
> ``` 
> * dynilath 的个人信息如下: 
> 默认骰子: 
> > 4d6 + 3 
> 已设置下列骰子指令: 
> > 法术骰 : 1d20 + 13 
> > 猛力攻击 : 1d20 + 14 
> ```  

在```.lr```后面加上一些文本，可以筛选指定骰子。  
> dynilath：```.lr猛力```

> DiceBot：
> ``` 
> * dynilath 的个人信息如下: 
> 已设置下列骰子指令: 
> > 猛力攻击 : 1d20 + 14 
> ```  

### 展示变量(.list var或.lv)
类似的，使用```.list var```指令来只显示你所保存的变量。    
当然你也可以用```.lv```。  
> dynilath：```.lv```

> DiceBot：
> ``` 
> * dynilath 的个人信息如下: 
> 已设置下列变量: 
> > 1环法术 : 3 / 4 
> > 2环法术 : 3 / 3 
> > bab : 4 / 4
> ```

在```.lv```后面加上一些文本，可以筛选指定变量。  
> dynilath：```.lv法术```

> DiceBot：
> ``` 
> * dynilath 的个人信息如下: 
> 已设置下列变量: 
> > 1环法术 : 3 / 4 
> > 2环法术 : 3 / 3 
> ```

## 删除变量和骰子(.delete或.d)
### 全部删除(.delete all)
使用```.delete all```指令来显示你所保存的所有数据。  
你也可以使用它较短的形式```.d all```。很遗憾这里的```all```并不能缩写成```a```。      
> dynilath：```.delete all```   
> DiceBot：``` * dynilath 已删除所有骰子指令和变量。```

### 删除骰子(.delete roll或.dr)
使用```.delete roll```指令来删除你所保存的骰子。    
当然你也可以用```.dr```。  
另外，这不会删除你的默认骰子。  
> dynilath：```.dr```   
> DiceBot：``` * dynilath 已删除所有骰子指令。```   

在```.dr```后面加上一些文本，可以删除指定骰子。  
> dynilath：```.dr 属性```  
> DiceBot：``` * dynilath 已删除骰子指令: 属性```   

### 删除变量(.delete var或.dv)
类似的，使用```.delete var```指令来只显示你所保存的变量。    
当然你也可以用```.dv```。  
> dynilath：```.dv```   
> DiceBot：``` * dynilath 已删除所有变量。```   

在```.dv```后面加上一些文本，可以删除指定变量。  
> dynilath：```.dv 1环法术```
> DiceBot：``` * dynilath 已删除变量: 1环法术```  

删除与显示的区别在于，你必须输入完整的名称才能删除该变量。  
而显示时，你只需要指出文本的一部分就可以将它们显示出来。    

## 为特定规则定制的骰子
### coc定制骰子(.coc或者.c)
骰子机器人提供了coc定制的骰子。使用指令为```.coc```。  
你也可以使用它较短的形式```.c```。    
> dynilath：```.c图书馆利用```      
> DiceBot：``` * 反pal魅魔 图书馆利用 掷骰: d100 = 11```  

除此之外，骰子机器人内置了coc7版的奖惩骰。 
使用```b[数值]```来产生奖励骰。
> dynilath：```.cb2斗殴(65)```  
> DiceBot：``` * dynilath 斗殴(65) 掷骰: CoC b2 = [2 + 8* + 3*] [8] = 28```  

使用```p[数值]```来产生惩罚骰。  
> dynilath：```.cp2闪避(50)```  
> DiceBot：``` * dynilath 闪避(50) 掷骰: CoC p2 = [6 + 1* + 6*] [9] = 69``` 

可以自动计算奖惩相抵。  
> dynilath：```.cp5b5p2b3奖罚抵消```    
> DiceBot：``` * dynilath 奖罚抵消 掷骰: CoC p5b5p2b3 = [0 + 7*] [7] = 7```  

### wod定制骰子(.wod或者.w)
骰子机器人提供了wod定制的骰子。使用指令为```.wodn[骰子数量]```和```.wodo[骰子数量]```。  
分别对应nWoD和oWod。  
你也可以使用它们较短的形式```.wn[骰子数量]```和```.wo[骰子数量]```。    

nWoD规则下，默认困难度为8，出10会加骰。
> dynilath：```.wn4```  
> DiceBot：``` * dynilath 掷骰: nWoD = [1* + 8 + 5* + 7*] = 1```  

oWoD规则下，默认困难度为6，出1会扣除一个成功。  
> dynilath：```.wo4```  
> DiceBot：``` * dynilath 掷骰: oWoD = [10 + 10 + 4* + 6] = 3```  

当然，不会扣成负数。  
> dynilath：```.wo4```  
> DiceBot：``` * dynilath 掷骰: oWoD = [3* + 10 + 2* + 9] = 2```  

无论是nWoD还是oWod，都可以加上```d[数值]```以更改困难度。  
> dynilath：```.wo4d8```  
> DiceBot：``` * dynilath 掷骰: oWoD = [3* + 7* + 3* + 8] = 1```  

无论是nWoD还是oWod，都可以加上```b[数值]```以设置奖励骰阈值。这里为了避免错误输入产生过长的结果，当阈值小于6时，取10。    
> dynilath：```.wo4b6```  
> DiceBot：``` * dynilath 掷骰: oWoD = [9 + 4* + 5* + 2* + 5*] = 1```  


### FATE定制骰子(.fate或.f)
骰子机器人提供了fate定制的骰子。使用指令为```.fate```。    
你也可以使用它较短的形式```.f```。    

它在结果上等效于```.r4d3-8```，但显示```-1```肯定会更为合适。
> dynilath：```.f```  
> DiceBot：``` * dynilath 掷骰: FATE = [-1 + 1 + 1 + 0] = 1```  

## 手动骰子(.manual或.m)
手动骰子会产生一些会保存在数据库的骰子数据。  
你可以使用指令操作这些骰子。如同它们真的在那里。
可以使用的指令如下：

* 指令```.m``` ：产生手动骰子，后接骰子，这里不支持算式。
* 指令```.mr```：骰指定骰子，后接骰子序号。
* 指令```.mk```：消灭指定骰子，后接骰子序号。
* 指令```.mka```：清空手动骰子。

> dynilath：
> ```
> .ns手动骰子测试
> .m4d6+2d8找几个骰子
> .mr4重骰第四个
> .mk5杀掉第五个
> .ma2d6增加两个
> .mka全杀掉
> .mr4
> .m1d4
> ```

> DiceBot：
> ```
> * 手动骰子测试 找几个骰子 在桌上放了这些骰子: 4d6+2d8 当前状态: 1(6) + 5(6) + 1(6) + 1(6) + 8(8) + 1(8) = 17
> * 手动骰子测试 重骰第四个 重骰桌上的第 4 个骰子 当前状态: 1(6) + 5(6) + 1(6) + 6(6) + 8(8) + 1(8) = 22
> * 手动骰子测试 杀掉第五个 杀死桌上的第 5 个骰子 当前状态: 1(6) + 5(6) + 1(6) + 6(6) + 1(8) = 14
> * 手动骰子测试 增加两个 在桌上增加了这些骰子: 2d6 当前状态: 1(6) + 5(6) + 1(6) + 6(6) + 1(8) + 4(6) + 5(6) = 23
> * 手动骰子测试 全杀掉 杀掉了所有的骰子 当前状态: 没有骰子了
> * 手动骰子测试 重骰桌上的第 4 个骰子 当前状态: 没有骰子了
> * 手动骰子测试 在桌上放了这些骰子: 1d4 当前状态: 3(4) = 3
> ```
