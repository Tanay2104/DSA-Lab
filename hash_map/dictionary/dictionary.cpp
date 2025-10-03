#include "dictionary.h"


Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
}

Dictionary::~Dictionary()
{
    delete[] A;
}

#define factor 31
#define alpha 0.6180339887
#define TOMBSTONE (char *)0xabcdabcdabcdabcd

int Dictionary::hashValue(char key[])
{
    // function should return fibonacci compression applied to the polynomial hash value
    // to prevent overflow in polynomial rolling hash, we will only store its fractional part

    // observe that {p * {alpha * x} + alpha * y} = {alpha * (p * x + y)} where x, y, p are integers and alpha is a float
    // Hence we have
    // {alpha * (a0 + a1 p^1 + a2 p^2 + ... + an p^n)} = {alpha * a0 + p * {alpha * (a1 + a2 p^1 + ... + an p^n-1)}}
    // which we can compute iteratively

    double fracHashValue = 0;
    for (int i = strlen(key) - 1; i >= 0; i--)
    {
        fracHashValue *= factor;
        fracHashValue += alpha * key[i];
        fracHashValue -= int(fracHashValue);
    }
    return int(N * fracHashValue);
}

int Dictionary::findFreeIndex(char key[])
{
    int hash = hashValue(key);
    for (int i = 0; i < N; i++)
    {
        int index = (hash + i) % N;
        if (A[index].key == nullptr || A[index].key == TOMBSTONE ||
            (A[index].key != TOMBSTONE && strcmp(A[index].key, key) == 0))
        {
            return index;
        }
    }
    return -1;
}

struct Entry *Dictionary::get(char key[])
{
    // find key
    int hash = hashValue(key);
    for (int i = 0; i < N; i++)
    {
        int index = (hash + i) % N;
        if (A[index].key == nullptr)
        {
            return nullptr; // stop at empty slot
        }
        if (A[index].key != TOMBSTONE && strcmp(A[index].key, key) == 0)
        {
            return &A[index];
        }
    }
    return nullptr;
}

bool Dictionary::put(Entry e)
{
    int idx = findFreeIndex(e.key);
    if (idx == -1)
        return false;

    // If overwriting, delete old key
    if (A[idx].key != nullptr && A[idx].key != TOMBSTONE)
    {
        delete[] A[idx].key;
    }

    // Deep copy key
    int len = strlen(e.key);
    A[idx].key = new char[len + 1];
    strcpy(A[idx].key, e.key);
    A[idx].value = e.value;

    return true;
}

bool Dictionary::remove(char key[])
{
    int hash = hashValue(key);
    for (int i = 0; i < N; i++)
    {
        int index = (hash + i) % N;
        if (A[index].key == nullptr)
        {
            return false; // not found
        }
        if (A[index].key != TOMBSTONE && strcmp(A[index].key, key) == 0)
        {
            delete[] A[index].key;
            A[index].key = TOMBSTONE;
            return true;
        }
    }
    return false;
}
