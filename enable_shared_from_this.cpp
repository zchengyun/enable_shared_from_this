#include <memory>
#include <iostream>
//std::enable_shared_from_this 能让一个对象（假设其名为 t ，且已被一个 std::shared_ptr 对象 pt 管理）
//安全地生成其他额外的 std::shared_ptr 实例（假设名为 pt1, pt2, ... ） ，它们与 pt 共享对象 t 的所有权。
//若一个类 T 继承 std::enable_shared_from_this<T> ，则会为该类 T 提供成员函数： shared_from_this 。
//当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr<T> 类对象管理时，调用 T::shared_from_this 成员函数，
//将会返回一个新的 std::shared_ptr<T> 对象，它与 pt 共享 t 的所有权。
struct Good : std::enable_shared_from_this<Good> // 继承
{
public:
	std::shared_ptr<Good> getptr() {
		return shared_from_this();
	}
	~Good() { std::cout << "~Good\n" << std::endl; }
};

struct Bad
{
public:
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "~Bad\n"; }
};

int main()
{
	std::shared_ptr<Good> gp1(new Good());
	std::shared_ptr<Good> gp2 = gp1->getptr();
	// 打印gp1和gp2的引用计数
	std::cout << "gp1.use_count() = " << gp1.use_count() << std::endl;
	std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;

	//引发异常bp1，bp2都认为自己独有该Bad指针，释放两次资源
	//std::shared_ptr<Bad> bp1(new Bad());
	//std::shared_ptr<Bad> bp2 = bp1->getptr();
	//std::cout << "gp1.use_count() = " << bp1.use_count() << std::endl;//bp1.use_count() = 1
	//std::cout << "gp2.use_count() = " << bp2.use_count() << std::endl;//bp2.use_count() = 1
}

