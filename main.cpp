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
    cout << "���������";
    list -> traverse([&](T e) {
        cout << e << " ";
    }); cout << ", Ԫ�ظ�����" << list -> size() << endl;

    cout << "���������";
    list -> traverse_reversed([&](T e) {
        cout << e << " ";
    }); cout << endl;
}


int main() {
    auto list = new DLinkedList<int>();
    auto iter = list -> iter();

    int op;
    auto help_message = R"(
˫������ʵ�֡������������
1) ��β������ add(element)��
2) ��ָ��λ�ò��� add(index, element)��
3) ����ָ���ڵ�Ԫ�� set(index, element)��
4) �Ƴ�ָ��λ��Ԫ�� remove(index)��
5) �Ƴ�Ԫ�� remove(element)��
6) ��ȡָ��λ��Ԫ�� get(index)��
7) �������Ԫ�� clear()��
8) ��ȡָ��Ԫ������ indexOf(element)��
9) ��ȡ������ָ��Ԫ������ lastIndexOf(element)��
10) �Ƿ����ĳԪ�� contains(element)��
11) ������������
0) �˳����ߡ�
)";

    cout << help_message << endl;
    cin >> op;

    while (op < 12 && op > 0) {
        int e, i;

        switch (op) {
            case 1:
                cout << "��������Ԫ�أ�";
                cin >> e;
                list -> add(e);
                traverse_all(list);
                break;
            case 2:
                cout << "�����������������Ԫ�أ�";
                cin >> i >> e;
                list -> add(i, e);
                traverse_all(list);
                break;
            case 3:
                cout << "�����������������Ԫ�أ�";
                cin >> i >> e;
                list -> set(i, e);
                traverse_all(list);
                break;
            case 4:
                cout << "�����Ƴ�Ԫ��������";
                cin >> i;
                list -> remove(static_cast<uint32_t>(i));
                traverse_all(list);
                break;
            case 5:
                cout << "�����Ƴ�Ԫ�أ�";
                cin >> e;
                list -> remove(static_cast<int>(e));
                traverse_all(list);
                break;
            case 6:
                cout << "�����ȡԪ��������";
                cin >> i;
                cout << list -> get(i) << endl;
                break;
            case 7:
                list -> clear();
                break;
            case 8:
                cout << "�����ȡԪ�أ�";
                cin >> i;
                cout << list -> indexOf(i) << endl;
                break;
            case 9:
                cout << "�����ȡԪ�أ�";
                cin >> i;
                cout << list -> lastIndexOf(i) << endl;
                break;
            case 10:
                cout << "�����ѯԪ�أ�";
                cin >> e;
                cout << (list -> contains(e) ? "true" : "false") << endl;
                break;
            case 11:
                iter = list -> iter();
                cout << "����������������";
                for_each(iter.begin(), iter.end(), [&](int e) {
                    cout << e << " ";
                });
                cout << "����ͣ�" << accumulate(iter.begin(), iter.end(), 0);
                cout << endl;

                iter = list -> riter();
                cout << "����������������";
                for_each(iter.begin(), iter.end(), [&](int e) {
                    cout << e << " ";
                });
                cout << "����ͣ�" << accumulate(iter.begin(), iter.end(), 0);
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
