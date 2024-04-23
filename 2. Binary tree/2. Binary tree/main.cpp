#include "BinaryTree.h"

using std::cout;
using std::endl;

int main() {
    setlocale(LC_ALL, "Rus");
    // Создаём объект бинарного дерева
    BinaryTree tree;

    // Добавляем узлы в дерево
    tree.AddSearchNode(5);
    tree.AddSearchNode(3);
    tree.AddSearchNode(7);
    tree.AddSearchNode(2);
    tree.AddSearchNode(4);
    tree.AddSearchNode(6);

    // Выводим информацию о дереве
    cout << "Дерево:" << endl;
    tree.PrintTree();

    cout << endl;

    cout << "Сумма всех ключей в дереве: " << tree.GetSumAllKeys() << endl;

    cout << endl;

    cout << "Минимальный ключ в дереве: " << tree.GetMinSearchKey() << endl;
    cout << "Максимальный ключ в дереве: " << tree.GetMaxSearchKey() << endl;

    cout << endl;

    cout << "Количество узлов в дереве: " << tree.GetNumNodes() << endl;
    cout << "Высота дерева: " << tree.GetHeight() << endl;

    cout << endl;

    // Проверяем, является ли дерево сбалансированным
    if (tree.isBalanced()) {
        cout << "Дерево сбалансировано." << endl;
    }
    else {
        cout << "Дерево не сбалансировано." << endl;
    }

    cout << endl;

    // Удаляем узел с ключом 3
    tree.RemoveNode(3);

    cout << "Дерево после удаления:" << endl;
    tree.PrintTree();

    return 0;
}