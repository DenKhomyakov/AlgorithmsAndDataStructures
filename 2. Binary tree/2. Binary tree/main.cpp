#include "BinaryTree.h"

using std::cout;
using std::endl;

int main() {
    setlocale(LC_ALL, "Rus");
    // ������ ������ ��������� ������
    BinaryTree tree;

    // ��������� ���� � ������
    tree.AddSearchNode(5);
    tree.AddSearchNode(3);
    tree.AddSearchNode(7);
    tree.AddSearchNode(2);
    tree.AddSearchNode(4);
    tree.AddSearchNode(6);

    // ������� ���������� � ������
    cout << "������:" << endl;
    tree.PrintTree();

    cout << endl;

    cout << "����� ���� ������ � ������: " << tree.GetSumAllKeys() << endl;

    cout << endl;

    cout << "����������� ���� � ������: " << tree.GetMinSearchKey() << endl;
    cout << "������������ ���� � ������: " << tree.GetMaxSearchKey() << endl;

    cout << endl;

    cout << "���������� ����� � ������: " << tree.GetNumNodes() << endl;
    cout << "������ ������: " << tree.GetHeight() << endl;

    cout << endl;

    // ���������, �������� �� ������ ����������������
    if (tree.isBalanced()) {
        cout << "������ ��������������." << endl;
    }
    else {
        cout << "������ �� ��������������." << endl;
    }

    cout << endl;

    // ������� ���� � ������ 3
    tree.RemoveNode(3);

    cout << "������ ����� ��������:" << endl;
    tree.PrintTree();

    return 0;
}