//
// Created by 13554 on 2021/12/24.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include "DLinkedList.h"

using namespace std;

template <typename T>
void traverse_all(DLinkedList<T>* list) {
    cout << "正向遍历：";
    list -> traverse([&](T e) {
        cout << e << " ";
    }); cout << ", 元素个数：" << list -> size() << endl;

    cout << "反向遍历：";
    list -> traverse_reversed([&](T e) {
        cout << e << " ";
    }); cout << endl;
}


int main() {
    auto list = new DLinkedList<int>();
    auto iter = list -> iter();

    int op;
    auto help_message = R"(
双向链表实现。请输入操作。
1) 在尾部插入 add(element)。
2) 在指定位置插入 add(index, element)。
3) 设置指定节点元素 set(index, element)。
4) 移除指定位置元素 remove(index)。
5) 移除元素 remove(element)。
6) 获取指定位置元素 get(index)。
7) 清除所有元素 clear()。
8) 获取指定元素索引 indexOf(element)。
9) 获取最后出现指定元素索引 lastIndexOf(element)。
10) 是否包含某元素 contains(element)。
11) 迭代器操作。
0) 退出工具。
)";

    cout << help_message << endl;
    cin >> op;

    while (op < 12 && op > 0) {
        int e, i;

        switch (op) {
            case 1:
                cout << "输入整数元素：";
                cin >> e;
                list -> add(e);
                traverse_all(list);
                break;
            case 2:
                cout << "输入插入索引和整数元素：";
                cin >> i >> e;
                list -> add(i, e);
                traverse_all(list);
                break;
            case 3:
                cout << "输入插入索引和整数元素：";
                cin >> i >> e;
                list -> set(i, e);
                traverse_all(list);
                break;
            case 4:
                cout << "输入移除元素索引：";
                cin >> i;
                list -> remove(static_cast<uint32_t>(i));
                traverse_all(list);
                break;
            case 5:
                cout << "输入移除元素：";
                cin >> e;
                list -> remove(static_cast<int>(e));
                traverse_all(list);
                break;
            case 6:
                cout << "输入获取元素索引：";
                cin >> i;
                cout << list -> get(i) << endl;
                break;
            case 7:
                list -> clear();
                break;
            case 8:
                cout << "输入获取元素：";
                cin >> i;
                cout << list -> indexOf(i) << endl;
                break;
            case 9:
                cout << "输入获取元素：";
                cin >> i;
                cout << list -> lastIndexOf(i) << endl;
                break;
            case 10:
                cout << "输入查询元素：";
                cin >> e;
                cout << (list -> contains(e) ? "true" : "false") << endl;
                break;
            case 11:
                iter = list -> iter();
                cout << "迭代器遍历，正向：";
                for_each(iter.begin(), iter.end(), [&](int e) {
                    cout << e << " ";
                });
                cout << "，求和：" << accumulate(iter.begin(), iter.end(), 0);
                cout << endl;

                iter = list -> riter();
                cout << "迭代器遍历，反向：";
                for_each(iter.begin(), iter.end(), [&](int e) {
                    cout << e << " ";
                });
                cout << "，求和：" << accumulate(iter.begin(), iter.end(), 0);
                cout << endl;
                break;
            default:
                return 0;
        }

        cout << endl << help_message << endl;
        cin >> op;
    }

    return 0;

}
