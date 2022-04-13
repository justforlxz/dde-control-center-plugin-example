# dde-control-center plugin development guide

## 约束

本插件向导仅支持在 V20 系列的控制中心中使用。

## 构建依赖

### Deepin

```shell
sudo apt install cmake g++ dde-control-center-dev libdtkwidget-dev
```

### ArchLinux

```shell
sudo pacman -S cmake gcc dde-control-center dtkwidget
```

## 编译安装与测试

### 编译与安装

```shell
mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

### 测试

安装完成后，退出已经运行的控制中心，在终端重新启动。

```shell
dde-control-center --show
```

如果因为插件的缘故导致控制中心启动会崩溃，可以使用 gdb 直接调试控制中心。

如果想要删除插件，前往 `/usr/lib/dde-control-center/plugins` 目录下删除安装的插件即可。

## 接口文档

### ModuleInterface接口定义

- ModuleInterface(FrameProxyInterface *frameProxy)

  接口描述：构建插件接口，通过此接口提供函数供控制中心主程序调用，各插件需要继承并实现各函数。

- virtual void preInitialize(bool sync = false,FrameProxyInterface::PushType = FrameProxyInterface::PushType::Normal)

  接口描述：会在模块初始化时被调用，用于模块在准备阶段进行资源的初始化，如翻译文件、二级菜单翻译内容、控制中心整体搜索方案等。此接口不允许进行高资源的操作。

- virtual void initialize();

  接口描述：初始化相应插件，参数proxy用于Moudle向Frame信息查询和主动调用。

- virtual const QString name() const;

  接口描述：返回插件的名称，在控制中心中用于代码内部标识。

- virtual const QString displayName() const;

  接口描述：返回插件在控制中心界面菜单上显示的名称。

- virtual QIcon icon() const

  接口描述：返回插件在控制中心界面菜单上显示的图标。

  用法：参考正确使用内嵌图标

- virtual QString translationPath() const

  接口描述：返回插件使用的多语言配置文件的路径，用来提供搜索。

  用法：一般是":/translations/dcc-plugin_%1.ts"，记住%1，控制中心会通过语言环境进行处理。

- virtual void active()

  接口描述：当插件第一次被点击进入时，active会被调用,重载的时候必须声明为slots,否则加载不了。

- virtual void deactive()

  接口描述：当插件被释放时，deactive会被调用，插件重载此函数用来释放各种资源

- virtual QString path() const

  接口描述：插件所在的父模块，在头文件中有对应的宏：

  MAINWINDOW "mainwindow"

  DISPLAY "display"

  DEFAPP "defapp"

  PERSONALIZATION "personalization"
 
  COMMONINFO "commoninfo"
 
  SOUND "sound"

  DATETIME "datetime"
 
  POWER "power"

  KEYBOARD "keyboard"

  SYSTEMINFO "systeminfo"

  MOUSE "mouse"

- virtual QString follow() const

  接口描述：返回插件在界面上显示的位置，如果是非数字的内容，则直接在相应的插件下面显示，若返回的是数字，则直接在此数字序号位置显示。

- virtual void addChildPageTrans()

  接口描述：返回插件二级菜单的翻译内容，在控制中心添加此二级菜单。

  用法：在此处调用FrameProxyInterface::addChildPageTrans方法添加二级菜单的翻译

- virtual void initSearchData() {};

  接口描述：设置插件中需要显示或隐藏的字段。

  用法：一般在此处调用FrameProxyInterface::setWidgetVisible或者FrameProxyInterface::setDetailVisible

### FrameProxyInterface接口定义

- FrameProxyInterface

  控制中心主界面接口，在加载并构建插件接口时，由控制中心传入此接口作为参数。

- virtual void pushWidget(ModuleInterface *const inter, QWidget *const w, PushType type = Normal)

  接口描述：当点击菜单项时,将菜单项对应的界面显示到控制中心主界面上。

- virtual void popWidget(ModuleInterface *const inter)

  接口描述：当点击返回、确定、取消等按钮时，需要将当前界面隐藏时调用此接口，将对应的界面从主界面上隐藏

- virtual void setModuleVisible(const QString &module, bool visible)

  接口描述：设置插件是否允许搜索

- virtual void setWidgetVisible(const QString &module, const QString &widget, bool visible)

  接口描述：设置插件主界面内容是否允许搜索

- virtual void setDetailVisible(const QString &module, const QString &widget, const QString &detail, bool visible)

  接口描述：设置插件二级界面内容是否允许搜索

- virtual void updateSearchData(const QString &module)

  接口描述：当插件界面显示条件发生改变时，需要调用此函数同步更新对应界面内容是否允许搜索

- virtual void addChildPageTrans(const QString &menu, const QString &rran)

  接口描述：添加插件二级菜单对应的翻译内容
