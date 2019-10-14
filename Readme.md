* 起因
  * 原本是想学习asio中的tcp回显，却意外在示例程序集中看到了chat。编译成功后觉得在命令行中使用没意思，而且因为服务器的消息转发并未忽略发送者，所以在终端会同时显示两条一模一样的消息，感觉有些别扭。虽然前期有修改一份不对发送者转发的服务端副本来解决消息重复的问题，但仍旧有一种添加界面的冲动。
* 问题（未解决）
  * 虽然程序由Windows端编写并提交，但却是在Ubuntu开始着手的，所以没有选择Windows下的GUI框架，而是使用了在上课时老师提到的GTK框架。由于初次接触，很多方面不熟悉，只能现学现卖，依靠神奇的百度（谷歌虽好，但舍不得fangqiangruanjian的花费）完善代码，所以结构很是杂乱。如若某位仁兄对代码结构有什么好的建议，可以发issue留下意见，或者您觉得代码实在写的太烂的，也可以在issue区骂我，我也不介意。
  * 开始阶段程序无论如何都无法运行成功，后来将窗口的show函数和gtk_main()扔到另一个线程之后程序才勉强开始运行，但至今不知道为什么。如果某位有缘进到这个repo的好人恰好知道原因，小的请求您心情好的时候一定要发个issue让我开开眼界啊（文字式磕头(ಥ _ ಥ)）。
* 问题（已解决）
  * Windows的GTK+开发环境配置废了一些时间。最开始，为了使用强大的VS进行开发，特意从搜索结果中采用了能够与VS集成的vcpkg，但是由于图标问题，最终的界面窗口图标全部缺失。因此，我考虑转向MINGW。有趣的是，原本因为多次配置VS CODE失败而对找一个能够对接MINGW的IDE的我，因为在教室瞥了一眼同学的电脑桌面，瞬间想起还有Code::blocks可以用。所以最终的配置是：Code::blocks+msys2(gtk官方推荐使用msys2，因为其携带的pacman管理器可以很方便的下载gtk包以及依赖，而且官网的安装向导还有现成的命令行提供)。
  * 首次编译不出意外地失败了，以为没有为code::blocks配置gtk+环境，Windows版的CB可以在”项目——>属性“页面最后的库中直接选择，因为它已经为我们引入了pkg-config能够识别的所有包。只是很遗憾Linux版的CB没有自动引入pkg-config，而我的项目最终是要转移回Ubuntu的，所以最后是在构建选项的“编译器其他选项”和“连接器其他选项”中添加了pkg-conig字段。
  * 当我脱离CB，尝试直接双击可执行文件运行程序时，发生了错误，*“无法定位程序输入点inflateReset2于动态链接库libpng16-16.dll”* ，最终在一篇两年前的CSDN博客末尾发现了问题源头：由于libpng16-16.dll依赖另一个动态链接库zlib1.dll，而我的环境变量路径中还有其它同名文件，而且由于库版本不同，导致定位失败，最终将mingw64/bin对应的路径提到环境变量首位，使得程序能够第一时间命中正确的库，确保了程序的正确运行。
* 后期
  * 修改message结构以及解包机制，增加用户名与时间戳，让chat看上去更像一个聊天程序，而不仅仅是tcp回显的扩充。

剩下的等我哪天心情好再继续写......