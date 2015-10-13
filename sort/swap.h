#ifndef SWAP_H_
#define SWAP_H_

template <typename T>
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

#endif
