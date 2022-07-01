# CutePlus Todo

- [CutePlus Todo](#cuteplus-todo)
  - [程序功能介绍](#程序功能介绍)
  - [项目各模块与类设计细节](#项目各模块与类设计细节)
    - [模块设计](#模块设计)
      - [MainWidget](#mainwidget)
      - [ListPart](#listpart)
      - [TaskPart](#taskpart)
      - [ListDetailWidget](#listdetailwidget)
      - [TaskDetailWidget](#taskdetailwidget)
      - [QNotify](#qnotify)
    - [类设计](#类设计)
      - [ListItem](#listitem)
      - [TaskItem](#taskitem)
  - [项目总结与反思](#项目总结与反思)
    - [耦合与解耦](#耦合与解耦)
    - [图形界面程序的设计原则](#图形界面程序的设计原则)
    - [注重阅读文档](#注重阅读文档)
    - [最开始的架构](#最开始的架构)

## 程序功能介绍

一个简单的任务清单工具，用户可以按需要创建不同的任务列表，并采用不同的颜色主题，便于管理任务。

> 运行截图：
> 
> ![1656594967305.png](https://img1.imgtp.com/2022/06/30/KfgSTxqH.png)

## 项目各模块与类设计细节

### 模块设计

![1656585122877.png](https://img1.imgtp.com/2022/06/30/qUbab4xd.png)

#### MainWidget

`MainWidget`是整个程序的主窗口，所有模块通过`MainWidget`进行通信，并作为`MainWidget`的子部件存在。

#### ListPart

`ListPart`是位于主窗口左部的子窗口，分为上下两个部分：`ListWidget`以及`addListBtn`。主要功能是显示各个ListItem条目，并响应用户针对ListItem的操作，可以向主窗口发射出`currentListItemChanged(ListItem*)`来表示当前ListItem条目的更改，并使得`TaskPart`实时显示出当前ListItem条目下所有的TaskItem信息；`callWarningTip(QString)`示意主窗口显示出对应的提醒信息；`callListDetailWidget(ListItem*)`使主窗口右部的层叠窗口（`stackedWidget`）切换到`ListDetailWidget`界面来调整ListItem的参数信息，并且将界面的内容初始化为所传达ListItem的内容，方便用户修改。并且支持`void addListItem(ListItem*,QString,QColor,QIcon)`以及`void modifyListItem(ListItem*,QString,QColor,QIcon)`的槽函数用于新建或是修改ListItem条目。

#### TaskPart

`Taskpart`是位于主窗口右部层叠窗口中用于显示ListItem中各个TaskItem条目信息的子模块listWidget，同时包含了QMenu右键菜单以及新建TaskItem的部件。右键菜单包括删除以及移动TaskItem位置的QAction。listWidget子部件继承了`void mouseDoubleClick(QMouseEvent*)`等虚函数，因此可以通过双击的位置来判断是否发射`callTaskDetailWidget(TaskItem*)`信号，进而使得主窗口的层叠窗口切换到`TaskDetailWidget`界面，从而修改任务的具体信息。当然也有`callWarningTip(QString)`信号来指示主窗口显示提醒信息。

#### ListDetailWidget

`ListDetailWidget`是位于主窗口右侧层叠窗口中的用于新建以及修改ListItem的模块，可以通过主窗口的`callListDetailWidget(ListItem*)`槽函数来切换。其添加或修改信息分别是通过`commitAdd(ListItem*,QString,QColor,QIcon)`和`commitModify(ListItem*,QString,QColor,QIcon))`信号来传达到ListPart部件的。在用户需要结束显示时，会向主窗口释放出`finish()`信号，而主窗口在接收到信号之后，会自动切换到相对应的界面。

#### TaskDetailWidget

`TaskDetailWidget`也是位于主窗口右侧层叠窗口中用于修改TaskItem信息的模块，可以通过主窗口的`callTaskDetailWidget(TaskItem*)`槽函数来切换。其修改信息是通过将`setTaskItemSignal(TaskItem*,QString,QString))`信号传递给TaskPart的槽函数`setTaskItem(TaskItem*,QString,QString))`来实现的。同样有着`finish()`信号来进行切换操作。

#### QNotify

`QNotify`是消息显示模块。可以通过调用`QNotify::notify(QString message, QNotify::Kind, int msec)`函数来在主窗口的右上角显示出一条消息。具体是通过重写`void paintEvent(QPaintEvent *)`函数同时根据时间不断更新画面来实现的。源代码来自[这里](https://github.com/mnafees/QNotify)，本项目只是对其进行了简单的修改后直接使用。

### 类设计

#### ListItem

ListItem用于存储任务列表，采用了对QObject以及QListWidgetItem的多重继承。含有一个QString对象作为列表名称，一个QIcon对象作为列表的图标，一个QColor对象作为列表主题色。这些信息都可以通过`ListDetailWidget`进行修改。同时，含有一个`QList<TaskItem *>tasks`成员变量负责存储列表中所有任务的指针。每当ListPart中ListItem条目切换时，MainWidget会将tasks更新（依据切换条目前的TaskPart中存储的所有TaskItem信息）。ListItem类重载了流插入以及流提取运算符，因此在读取和存储数据时，只需要很简单的文件操作即可。

#### TaskItem

TaskItem用于存储具体的任务信息，同样是采用了对QObject以及QListWidgetItem的多重继承。含有一个QString对象作为任务名称，一个QString对象作为任务详细描述，一个QDateTime对象作为任务创建时间。需要注意的是，TaskItem并不是可以直接显示在TaskPart的TreeWidget上的，还需要通过新建一个TaskItemWidget来作为显示界面，并调用QTreeWidget的setItemWidget函数来指派。因此在清空TaskItem指针时，必须要预先通过QTreeWidget的itemWidget函数来获得并析构其对应的TaskItemWidget。

## 项目总结与反思

### 耦合与解耦

在最开始我在进行初稿设计时，各种部件全部杂糅在一起，信号和槽函数分布和处理极其混乱。直到阅读到Qt中的`Model-View-Delegate`架构后才意识到把各个部件和功能，数据和显示剥离开来的重要性：将各个部件分散开来并实现相应的封装，提供相应的接口以供其他部件调用，分而治之。不过有些遗憾的是，最初我是打算采用自定义Model以及Delegate来进行数据和图形界面的分离的，但是最后考虑到QListWidget和QTreeWidget良好的封装以及对setItemWidget函数的支持后最终还是选择了利用现有的后者。当然，代码量的简化所造成的后果是TaskItem和TaskItemWidget二者之间藕断丝连的关系。但好在项目本身是比较简单，因此部分的耦合是可以接受的。

### 图形界面程序的设计原则

之前阅读有关GUI程序设计的书籍时，偶然看到了一个原则：“***尽量避免打扰用户***”。像是`QMessageBox::warning(...)`这样子的函数，用户在见到这样子的提醒框后，并没有选择的余地，只能点击*确定*，这是没有任何用处的，程序要做的是提醒，而非对用户无意义的打扰，因此在设计程序时，我特意将所有需要调用提醒的代码处保留注释，等待最后统一将调用提醒的方式设置成发送`callWarningTip(QString)`信号，使MainWidget进行统一调度，并在边缘出显示出一个自动关闭的警示框。

同时还有“***使显示尽可能简洁，避免一片乱麻的界面***”。毕竟将很多并不常用的选项全部罗列出来对于用户来说只是负担，所以在设计此程序的时候，我将很多并不太可能会用到的用户接口放在了右键菜单中，如此一来页面也美观了不少。

### 注重阅读文档

像是Qt这种GUI程序设计框架，最开始的学习门槛个人感觉还是很高的，毕竟它的库的复杂度以及深度广度是远远高于STL的，因此最开始学习的时候我是按照一个又一个简单的例子来学习的，并且也要好好研读其对于各个类的说明文档。说明文档的帮助是很大的，毕竟网络上教程都只是片面的，对于原理的讲解并不深入，而且也无法保证是符合官方推荐的用法的。

### 最开始的架构

最初始的架构是非常重要的，最初我写了很多TaskList的初版项目，但是无一例外，都是因为越写越乱而导致被弃。最后我是预先写了一个大致的框架，然后再依据这些框架为各个部件指配相应需要实现的函数，即，先确立好骨架，再慢慢的缝补皮肉。