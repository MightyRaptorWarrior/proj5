/***********************************************************
 ** File: LList_test.cpp
 ** CMSC 202 - Project 5 standalone templated list tests
 ** Compile with: make ltest; run with: ./ltest
 ** Does not depend on any Dungeon/Item/GameState code.
 ***********************************************************/
#include "LList.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int passed = 0;
int failed = 0;

void Check(bool condition, const string& message) {
    if (condition) {
        ++passed;
        cout << "  \033[32mPASS\033[0m " << message << '\n'; // Outputs Green
    }
    else {
        ++failed;
        cout << "  \033[31mFAIL\033[0m " << message << '\n'; // Outputs Red
    }
}

// A second instantiation makes sure LList is genuinely templated.
struct Record {
    string name;
    int value;
    Record(string n = "", int v = 0) : name(n), value(v) {}
};

ostream& operator<<(ostream& out, const Record& r) {
    return out << r.name << ':' << r.value;
}

void TestEmptyAndSingleton() {
    cout << "\n[1] Empty list / one element\n";
    LList<int> a;
    Check(a.IsEmpty(), "new list is empty");
    Check(a.Size() == 0, "empty size is zero");
    a.Enqueue(11);
    Check(!a.IsEmpty() && a.Size() == 1, "enqueue on empty");
    Check(a.Peek() == 11 && a.GetAt(0) == 11, "peek/get singleton");
    Check(a.Dequeue() == 11, "dequeue only element");
    Check(a.IsEmpty(), "singleton removal returns to empty");
    a.Enqueue(12); // catches stale tail pointers
    Check(a.Pop() == 12 && a.IsEmpty(), "reuse after removing last node");
    a.Push(13);
    Check(a.Dequeue() == 13 && a.IsEmpty(), "push then dequeue");
    a.Clear();
    Check(a.IsEmpty(), "clear empty list safely");
}

void TestQueueAndStack() {
    cout << "\n[2] FIFO and LIFO behavior\n";
    LList<int> q;
    for (int i = 1; i <= 5; ++i) q.Enqueue(i);
    Check(q.Size() == 5, "five enqueues");
    bool fifo = true;
    for (int i = 1; i <= 5; ++i) if (q.Dequeue() != i) fifo = false;
    Check(fifo && q.IsEmpty(), "queue FIFO order");
    LList<int> s;
    for (int i = 1; i <= 5; ++i) s.Push(i);
    bool lifo = true;
    for (int i = 5; i >= 1; --i) if (s.Pop() != i) lifo = false;
    Check(lifo && s.IsEmpty(), "stack LIFO order");
    q.Enqueue(1); q.Enqueue(2); q.Push(0); q.Enqueue(3);
    Check(q.Size() == 4, "mixed push/enqueue size");
    Check(q.Pop() == 0 && q.Dequeue() == 1 && q.Dequeue() == 2 &&
        q.Pop() == 3 && q.IsEmpty(), "mixed operation ordering");
}

void TestIndexesAndRemoval() {
    cout << "\n[3] Index retrieval and deletion\n";
    LList<int> a;
    for (int i = 0; i < 6; i++) a.Enqueue(i * 10);
    Check(a.GetAt(0) == 0 && a.GetAt(3) == 30 && a.GetAt(5) == 50,
        "head/middle/tail GetAt");
    Check(a.RemoveAt(0) == 0 && a.Size() == 5 && a.Peek() == 10,
        "remove head");
    Check(a.RemoveAt(2) == 30 && a.Size() == 4 && a.GetAt(2) == 40,
        "remove middle reconnects links");
    Check(a.RemoveAt(3) == 50 && a.Size() == 3,
        "remove tail");
    a.Enqueue(60);
    Check(a.GetAt(3) == 60 && a.Size() == 4,
        "enqueue works after tail removal");
    Check(a.RemoveAt(3) == 60 && a.RemoveAt(2) == 40 &&
        a.RemoveAt(1) == 20 && a.RemoveAt(0) == 10 && a.IsEmpty(),
        "repeated RemoveAt returns to empty");
    a.Push(99);
    Check(a.Peek() == 99 && a.Size() == 1, "reuse after RemoveAt emptied list");
}
void TestRuleOfThree() {
    cout << "\n[4] Deep copying, assignment, self-assignment\n";
    LList<int> source;
    source.Enqueue(4); source.Enqueue(5); source.Enqueue(6);
    LList<int> copy(source);
    Check(copy.Size() == 3 && copy.GetAt(0) == 4 && copy.GetAt(2) == 6,
        "copy constructor preserves order");
    source.RemoveAt(1);
    source.Push(3);
    Check(copy.Size() == 3 && copy.GetAt(1) == 5 && copy.Peek() == 4,
        "copy does not change when source changes");
    copy.Dequeue();
    Check(source.GetAt(0) == 3 && source.Size() == 3,
        "source does not change when copy changes");
    LList<int> target;
    target.Enqueue(-1); target.Enqueue(-2); target.Enqueue(-3);
    target = source;
    Check(target.Size() == 3 && target.GetAt(0) == 3 && target.GetAt(2) == 6,
        "assignment replaces existing contents");
    source.Clear();
    Check(target.Size() == 3 && target.GetAt(1) == 4,
        "assigned list survives source Clear");
    target = target;
    Check(target.Size() == 3 && target.GetAt(2) == 6,
        "self-assignment preserves elements");
    LList<int> empty;
    target = empty;
    Check(target.IsEmpty() && target.Size() == 0, "assignment from empty");
    empty = copy;
    Check(empty.Size() == 2 && empty.GetAt(0) == 5,
        "assignment into initially empty list");
    LList<int> copiedEmpty(target);
    Check(copiedEmpty.IsEmpty(), "copy construction from empty");
}

void TestTemplateAndDisplay() {
    cout << "\n[5] Other type, const access, Display\n";
    LList<Record> records;
    records.Enqueue(Record("torch", 1));
    records.Enqueue(Record("potion", 30));
    const LList<Record>& constRef = records;
    Check(constRef.Size() == 2 && constRef.GetAt(1).name == "potion",
        "templated user-defined type; const Size/GetAt");
    Check(constRef.Peek().name == "torch" && !constRef.IsEmpty(),
        "const Peek/IsEmpty");
    // Display writes to cout. Check that output contains both values.
    ostringstream captured;
    streambuf* prior = cout.rdbuf(captured.rdbuf());
    records.Display();
    cout.rdbuf(prior);
    Check(captured.str().find("torch") != string::npos &&
        captured.str().find("potion") != string::npos, "Display prints all records");
    Record first = records.RemoveAt(0);
    Check(first.name == "torch" && records.Peek().name == "potion",
        "RemoveAt returns user-defined type");
    LList<string> words;
    words.Push("last"); words.Push("first");
    Check(words.Pop() == "first" && words.Dequeue() == "last",
        "template instantiation with string");
}

void TestStress() {
    cout << "\n[6] Larger sequence / cleanup\n";
    LList<int> a;
    for (int i = 0; i < 1000; ++i) a.Enqueue(i);
    Check(a.Size() == 1000 && a.Peek() == 0 && a.GetAt(999) == 999,
        "1000 element build");
    LList<int> b = a;
    bool correct = true;
    for (int i = 0; i < 1000; ++i) if (a.Dequeue() != i) correct = false;
    Check(correct && a.IsEmpty(), "1000 FIFO removals");
    Check(b.Size() == 1000 && b.GetAt(999) == 999,
        "1000 element deep copy retained");
    b.Clear(); b.Clear();
    Check(b.IsEmpty(), "Clear twice");
}

int main() {
    TestEmptyAndSingleton();
    TestQueueAndStack();
    TestIndexesAndRemoval();
    TestRuleOfThree();
    TestTemplateAndDisplay();
    TestStress();
    cout << "\nRESULT: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}