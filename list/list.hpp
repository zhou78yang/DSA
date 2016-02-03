#include <cstdlib>
#include "listnode.h"

#ifndef LIST_H_
#define LIST_H_

<<<<<<< HEAD
typedef int				Rank;								// ÁĞ±íµÄÖÈ

=======
#include "list_node.h"
typedef  int    Rank;               // ç»“ç‚¹çš„ç§©


// åˆ—è¡¨æ¨¡æ¿ç±»
>>>>>>> 385612237ee3b2211a443370842b941d317370a7
template <typename T>
class List
{
protected:
<<<<<<< HEAD
	int  _size;												// ¹æÄ£
	Posi<T> header, trailer;								// Í·ÉÚ±øºÍÎ²ÉÚ±ø

protected:
	void init();											// ÁĞ±í³õÊ¼»¯
	int  clear();											// Çå³ıËùÓĞ½áµã
	void copyNodes(Posi<T>, int);							// ¸´ÖÆÄ³´®½áµã
	void merge(Posi<T> &, int, List<T> &, Posi<T>, int);	// ¹é²¢
	void mergeSort(Posi<T> &, int);							// ¹é²¢ÅÅĞò
	void selectionSort(Posi<T> &, int);						// Ñ¡ÔñÅÅĞò
	void insertionSort(Posi<T> &, int);						// ²åÈëÅÅĞò
	int partition(Posi<T> &, int, Posi<T> &);				// ¿ìÅÅ·Ö¶Î
	void quickSort(Posi<T> &, int);							// ¿ìËÙÅÅĞò

public:
	// ¹¹Ôìº¯Êı
	List(){ init(); }										// Ä¬ÈÏ
	List(const List<T> &L){	copyNodes(L.first(), L._size); }// ÁĞ±í¸´ÖÆ¹¹Ôì
	List(const List<T> &L, Rank r, int n){ copyNodes(L.getNode(r), n); }
	List(Posi<T> p, int n){ copyNodes(p, n); }				// ½áµãĞÎÊ½¹¹Ôì
	// Îö¹¹º¯Êı
	~List(){ clear(); delete header, trailer; }		
	
	// Ö»¶Á·ÃÎÊ½Ó¿Ú
	Rank size() const{ return _size; }						// ¹æÄ£
	bool empty() const{ return _size <= 0; }				// ÅĞ¶ÏÊÇ·ñÎª¿Õ
	Posi<T> first() const{ return header->succ; }			// Ê×½áµãÎ»ÖÃ
	Posi<T> last() const{ return trailer->pred; }			// Ä©½áµãÎ»ÖÃ
	bool valid(Posi<T> p) const
	{
		return p && (trailer != p) && (header != p);		// ÅĞ¶ÏpÊÇ·ñºÏ·¨
	}
	int  disordered() const;								// ÅĞ¶ÏÊÇ·ñÓĞĞò
	Posi<T> find(const T &e) const;							// ÎŞĞòÁĞ±í²éÕÒ
	Posi<T> find(const T &e, Posi<T> p, int n) const;		// ÎŞĞòË³´Î²éÕÒ
	Posi<T> find(const T &e, int n, Posi<T> p) const;		// ÎŞĞòÄæÏò²éÕÒ
	Posi<T> search(const T &e) const;						// ÓĞĞòÁĞ±í²éÕÒ
	Posi<T> search(const T &e, Posi<T> p, int n) const;		// ÓĞĞòË³´Î²éÕÒ
	Posi<T> search(const T &e, int n, Posi<T> p) const;		// ÓĞĞòÄæÏò²éÕÒ
	Posi<T> selectMax(Posi<T> p, int n);					// Çø¼ä×î´óÖµ
	Posi<T> selectMax(){ return selectMax(header->succ, _size); }// ÁĞ±í×î´óÖµ

	// ¿ÉĞ´·ÃÎÊ½Ó¿Ú
	T &operator [] (Rank r) const;							// ÖØÔØÏÂ±êÔËËã·û
	Posi<T> &getNode(Rank r) const;							// »ñÈ¡ÁĞ±í½áµã
	Posi<T> insertAsFirst(const T &e);						// ×÷ÎªÊ×½áµã²åÈë
	Posi<T> insertAsLast(const T &e);						// ×÷ÎªÄ©½áµã²åÈë
	Posi<T> insertA(Posi<T> p, const T &e);					// ½«e²åÈëµ½pºó
	Posi<T> insertB(Posi<T> p, const T &e);					// ½«e²åÈëµ½pÇ°
	T remove(Posi<T> p);									// É¾³ı½áµãp
	void merge(List<T> &L)
	{
		merge(header->succ, _size, L, L.first(), L._size);	// È«ÁĞ±í¹é²¢
	}
	void sort(Posi<T> p, int n);							// ÁĞ±íÇø¼äÅÅĞò
	void sort(){ sort(first(), _size); }					// ÁĞ±íÈ«¾ÖÅÅĞò
	int  deduplicate();										// ÎŞĞòÈ¥ÖØ
	int  uniquify();										// ÓĞĞòÈ¥ÖØ
	void reverse();											// Ç°ºóµ¹ÖÃ

	// ±éÀú
	void traverse(void(*)(T &));							// º¯ÊıÖ¸Õë±éÀú
	template <typename VST> void traverse(VST &);			// º¯ÊıÒıÓÃ±éÀú

};// List


///////////////////////////////////////////////////////////////////////////
// protected²¿·Ö

template <typename T>
void List<T>::init()
{
	// ¶ÔÁĞ±í½øĞĞ³õÊ¼»¯
	header = new ListNode<T>();
	trailer = new ListNode<T>();
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ);
	return oldSize;
}

template <typename T>
void List<T>::copyNodes(Posi<T> p, int n)
{
	init();	// ³õÊ¼»¯ÁĞ±í
	while (0 < n--)
	{
		insertAsLast(p->data);	// Ë³´Î²åÈë
		p = p->succ;
	}
}

template <typename T>
int List<T>::partition(Posi<T> &p, int n, Posi<T> &q)
{
	// pÎªÎ´ÅÅĞò×ÓĞòÁĞÆğµã£¬nÎª×ÓĞòÁĞ³¤¶È
	// ×îÖÕpÖ¸ÏòÇ°°ë¶ÎÆğµã£¬qÖ¸Ïòºó°ë¶ÎÆğµã
	int m = 0;	// ¼ÆËã±ÈpĞ¡µÄ½áµã¸öÊı
	Posi<T> head = p->pred;	// ¼ÇÂ¼Í·½áµã
	q = p->succ;
	for (int i = 1; i < n; i++)
	{
		// ½øĞĞn-1´Î±È¶Ô£¬½«±ÈpĞ¡µÄ½áµã²åÈëµ½pÇ°
		q = q->succ;
		if (p->data > q->pred->data)
		{
			insertB(p, remove(q->pred));
			m++;
		}
	}
	q = p->succ;	// qÎªºó°ë¶ÎÆğµã
	p = head->succ;	// p»Ö¸´Îª×ÓÁĞ±íÆğµã
	return m;	// ·µ»ØºóÒ»¶Î×ÓÁĞ±íµÄ³¤¶È
}

template <typename T>
void List<T>::quickSort(Posi<T> &p, int n)
{
	// ¿ìËÙÅÅĞò£¬¶Ô´Óp¿ªÊ¼µÄn¸ö½áµã½øĞĞÅÅĞò
	// ÒªÇóp×îÖÕÖ¸ÏòÓĞĞòÁĞ±íµÄÆğµã
	if (n < 2) return;
	Posi<T> q;	// ÓÉÓÚList·ÃÎÊµÄ²»±ãĞÔ£¬¹ÊÓÃqÀ´»ñÈ¡ºó°ë¶ÎÆğµã
	int m = partition(p, n, q);	// m´æ´¢Ç°°ë¶Î³¤¶È
	quickSort(p, m); 
	quickSort(q, n - m - 1);
}

template <typename T>
void List<T>::merge(Posi<T> &p, int la, List<T> &L, Posi<T> b, int lb)
{
	// pÎªÁĞ±íÖĞµÄÄ³¸ö½áµã£¬laÎª×ÓÁĞ±í³¤¶È
	// bÎªÁĞ±íLÖĞµÄÄ³¸ö½áµã£¬lbÎª×ÓÁĞ±í³¤¶È
	Posi<T> head = p->pred;	// ¼ÇÂ¼¹é²¢Çø¼äµÄÇ°½áµã
	Posi<T> a = p;	// pµÄÖµ¿½±´
	while (lb > 0)
	{
		if (la > 0 && (a->data <= b->data))
		{
			a = a->succ; la--;
			if (a == b) break;
		}
		else
		{
			b = b->succ; lb--;
			insertB(a, L.remove(b->pred));	// ²åÈëµ½aÇ°
		}			
	}
	p = head->succ;	// ½«p»Ö¸´Îª¹é²¢Çø¼äµÄÊ×½áµã
}

template <typename T>
void List<T>::mergeSort(Posi<T> &p, int n)
{
	// ¹é²¢ÅÅĞò£¬ÊµÏÖ´Óp¿ªÊ¼µÄn¸ö½áµãµÄÅÅĞò
	if (n < 2) return;
	int m = n / 2;
	Posi<T> q = p;
	for (int i = 0; i < m; i++) q = q->succ;// ¾ù·ÖÁĞ±í
	mergeSort(p, m); mergeSort(q, n - m);	// »®·ÖÁ½¶ÎÅÅĞò
	merge(p, m, *this, q, n - m);	// ¹é²¢
}

template <typename T>
void List<T>::selectionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred; Posi<T> tail = p;	// Í·¡¢Î²½áµã
	for (int i = 0; i < n; i++) tail = tail->succ;	// ´ıÅÅÇø¼ä[p, tail)
	while (1 < n)
	{
		Posi<T> q = selectMax(head->succ, n);// ´ıÅÅÇø¼äÖĞµÄ×î´óÖµ
		insertB(tail, remove(q));	// ½«×î´óÖµ²åÈëµ½Î´ÅÅĞò²¿·ÖÄ©Î²
		tail = tail->pred; n--;		// ÊÕËõÎ´ÅÅĞò²¿·Ö
	}
}

template <typename T>
void List<T>::insertionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred, tail = p, q = p->succ;	// Í·¡¢Î²¡¢´ı²åÈë½áµã
	for (int i = 0; i < n; i++) tail = tail->succ;	// tailÎªÄ©½áµãµÄºó¼Ì
	while (q != tail)
	{
		Posi<T> r = q->pred;
		while (r != head && r->data > q->data) r = r->pred;	// ÕÒµ½²åÈëÎ»ÖÃ
		insertA(r, q->data);	// ²åÈëµ½rµÄºóÃæ
		q = q->succ; remove(q->pred);	// qÖ¸ÏòÏÂÒ»¸ö£¬²¢É¾³ıÖ®Ç°²åÈë½áµã
	}
}


///////////////////////////////////////////////////////////////////////////
// Ö»¶Á·ÃÎÊ½Ó¿Ú

template <typename T>
int List<T>::disordered() const
{
	int c = 0;	// ÄæĞòÊı¼ÇÂ¼
	Posi<T> p = first();
	while (trailer != p->succ)
	{
		if (p->data > p->succ->data) c++;
	}
	return c;
}

template <typename T>
Posi<T> List<T>::find(const T &e) const
{
	// ÄæÏò²éÕÒ
	return find(e, _size, trailer);
}

template <typename T>
Posi<T> List<T>::find(const T &e, Posi<T> p, int n) const
{
	// ²éÕÒpµÄn¸ö£¨Õæ£©ºó¼Ì£¬¼´p×÷ÎªheaderµÄÁ´±í
	while (0 < n--)
	{
		if (e == (p = p->succ)->data) return p;
	}
	return NULL;;
}

template <typename T>
Posi<T> List<T>::find(const T &e, int n, Posi<T> p) const
{
	// ²éÕÒpµÄn¸ö£¨Õæ£©Ç°Çı£¬¼´p×÷ÎªtrailerµÄÁ´±í
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e) const
{
	return search(e, _size, trailer);	// ÄæÏòËÑË÷
}

template <typename T>
Posi<T> List<T>::search(const T &e, Posi<T> p, int n) const
{
	while (0 < n-- && (p = p->succ)->data < e);
	return p->data == e ? p : NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e, int n, Posi<T> p) const
{
	while (0 < n-- && (p = p->pred)->data > e);
	return p->data == e ? p : NULL;
}

template <typename T>
Posi<T> List<T>::selectMax(Posi<T> p, int n)
{
	// ÌôÑ¡´Óp¿ªÊ¼µÄn¸öÔªËØµÄ×î´óÖµ
	Posi<T> max = p;
	while (1 < n--)
	{
		if ((p = p->succ)->data > max->data) max = p;
	}
	return max;
}


/////////////////////////////////////////////////////////////////////////
// ¿ÉĞ´·ÃÎÊ½Ó¿Ú

template <typename T>
T &List<T>::operator [] (Rank r) const
{
	// ÁĞ±íÖĞ½áµãµÄÖµµÄÓ³Éä£¬Ğ§ÂÊµÍÏÂ£¬¾¡Á¿ÉÙÓÃ
	Posi<T> p = first();	// ´ÓÊ×½áµã³ö·¢
	while (0 < r--) p = p->succ;	// Ë³ÊıµÚr¸ö½áµã
	return p->data;	// ·µ»Ø½áµãÄÚÈİ
}

template <typename T>
Posi<T> &List<T>::getNode(Rank r) const
{
	// ·µ»ØÁĞ±íµÄ½áµã
	Posi<T> p = first();
	while (0 < r--) p = p->succ;
	return p;
}

template <typename T>
Posi<T> List<T>::insertAsFirst(const T &e)
{ 
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
Posi<T> List<T>::insertAsLast(const T &e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template <typename T>
Posi<T> List<T>::insertA(Posi<T> p, const T &e)
{
	// insert after
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
Posi<T> List<T>::insertB(Posi<T> p, const T &e)
{
	// insert before
	_size++;
	return p->insertAsPred(e);
}

template <typename T>
T List<T>::remove(Posi<T> p)
{
	T e = p->data;	// Êı¾İ±¸·İ
	p->pred->succ = p->succ;	// pÇ°ÇıµÄºó¼Ì±äÎªpµÄºó¼Ì
	p->succ->pred = p->pred;	// pºó¼ÌµÄÇ°Çı±äÎªpµÄÇ°Çı
	delete p;	// ÊÍ·ÅpµÄ¿Õ¼ä
	_size--;	// ¹æÄ£¼õĞ¡
	return e;
}

template <typename T>
void List<T>::sort(Posi<T> p, int n)
{
	// ¶ÔÆğÊ¼Î»ÖÃÎªpµÄn¸öÔªËØ½øĞĞÅÅĞò
	quickSort(p, n); return;
	switch (rand() % 3)
	{
	// Ëæ»úÑ¡ÔñÅÅĞò·½Ê½
	case 1: insertionSort(p, n); break;
	case 2: selectionSort(p, n); break;
	case 3: quickSort(p, n); break;
	default: mergeSort(p, n); break;
	}

}

template <typename T>
int List<T>::deduplicate()
{
	// ÎŞĞòÁĞ±íµÄÈ¥ÖØ²Ù×÷
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header; Rank r = 0;
	while (trailer != (p = p->succ))
	{
		Posi<T> q = find(p->data, r, p);// ²éÕÒpÇ°µÄr¸öÔªËØ
		q ? remove(q) : r++;	// Èôq´æÔÚÔòÉ¾³ıq
	}
	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
	// ÓĞĞòÁĞ±íµÄÈ¥ÖØ²Ù×÷
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header->succ; Posi<T> q;
	while (trailer != (q = p->succ))
	{
		// ·´¸´¿¼²éÏàÁÚ½áµã¶ÔpºÍq
		if (p->data == q->data) remove(q);
		else p = q;
	}
	return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void(*visit)(T &))
{
	for (auto p = first(); p != trailer; p = p->succ) visit(p->data);
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit)
{
	for (auto p = first(); p != trailer; p = p->succ) visit(p->data);
}
=======
    int _size;                      // è§„æ¨¡
    ListNodePosi header;            // å¤´å“¨å…µ
    ListNodePosi trailer;           // å°¾å“¨å…µ

protected:
    void init();                    // åˆ—è¡¨åˆå§‹åŒ–
    int  clear();                   // æ¸…é™¤æ‰€æœ‰ç»“ç‚¹
    void copyNodes(ListNodePosi, int);// å¤åˆ¶åˆ—è¡¨ä¸­è‡ªä½ç½®Pèµ·çš„né¡¹
    void merge(ListNodePosi&, int, List<T>&, ListNodePosi, int); // å½’å¹¶
    void mergeSort(ListNodePosi&, int); // å¯¹ä»på¼€å§‹çš„nä¸ªç»“ç‚¹è¿›è¡Œå½’å¹¶æ’åº
    void selectionSort(ListNodePosi, int); // å¯¹ä»på¼€å§‹çš„nä¸ªç»“ç‚¹è¿›è¡Œé€‰æ‹©æ’åº
    void insertionSort(ListNodePosi, int); // å¯¹ä»på¼€å§‹çš„nä¸ªç»“ç‚¹è¿›è¡Œæ’å…¥æ’åº

public:
    // æ„é€ å‡½æ•°
    List() { init(); }                  // é»˜è®¤æ„é€ å‡½æ•°
    List(const List<T> &L);             // æ•´ä½“å¤åˆ¶åˆ—è¡¨L
    List(const List<T> &L, Rank r, int n);// å¤åˆ¶åˆ—è¡¨Lä¸­è‡ªrå¼€å§‹çš„nä¸ªç»“ç‚¹
    List(ListNodePosi p, int n);        // å¤åˆ¶åˆ—è¡¨ä¸­è‡ªä½ç½®pèµ·çš„né¡¹
    // ææ„å‡½æ•°
    ~List();

    // åªè¯»è®¿é—®æ¥å£
    Rank size() const { return _size; } // è§„æ¨¡
    bool empty() const { return _size <= 0; } // åˆ¤æ–­æ˜¯å¦ä¸ºç©º
    T &operator [](Rank r) const;// é‡è½½ï¼Œæ”¯æŒå¯»ç§©è®¿é—®
    ListNodePosi first() const { return header->next; }
    ListNodePosi last() const { return trailer->pre; }
    bool valid(ListNodePosi p) const    // åˆ¤æ–­pç»“ç‚¹æ˜¯å¦å¯ç”¨
    { return p && (p != header) && (p != trailer); }
    int disordered() const; // åˆ¤æ–­æ˜¯å¦æœ‰åº
    ListNodePosi find(const T &e) const;// æ— åºåˆ—è¡¨æ•´ä½“æŸ¥æ‰¾
    ListNodePosi find(const T &e, ListNodePosi p, int n) const;// æ— åºåˆ—è¡¨åŒºé—´æŸ¥æ‰¾
    ListNodePosi search(const T &e) const;// æœ‰åºåˆ—è¡¨æ•´ä½“æŸ¥æ‰¾
    ListNodePosi search(const T &e, ListNodePosi p, int n) const;// æœ‰åºåˆ—è¡¨åŒºé—´æŸ¥æ‰¾
    ListNodePosi max() const;// è·å–æ•´ä½“æœ€å¤§å€¼
    ListNodePosi max(ListNodePosi p, int n) const;// åœ¨påçš„nä¸ªç»“ç‚¹ä¸­é€‰å–æœ€å¤§å€¼

    // å¯å†™è®¿é—®æ¥å£
    ListNodePosi insertAsFirst(const T &e);     // å°†eä½œä¸ºé¦–ç»“ç‚¹æ’å…¥
    ListNodePosi insertAsLast(const T &e);      // å°†eä½œä¸ºå°¾ç»“ç‚¹æ’å…¥
    ListNodePosi insertA(ListNodePosi p, const T &e);// å°†eä½œä¸ºpçš„åç»§æ’å…¥
    ListNodePosi insertB(ListNodePosi p, const T &e);// å°†eä½œä¸ºpçš„å‰é©±æ’å…¥
    T remove(ListNodePosi p);                   // åˆ é™¤ç»“ç‚¹p
    void merge(List<T> &L);                     // æ’å…¥ä¸€ä¸ªåˆ—è¡¨
    void sort();                                // åˆ—è¡¨æ’åº
    void sort(ListNodePosi p, int n);           // åˆ—è¡¨åŒºé—´æ’åº
    int  deduplicate();                         // æ— åºå»é‡
    int  uniquify();                            // æœ‰åºå»é‡
    void reverse();                             // åè½¬åˆ—è¡¨

    // éå†
    void traverse(void (*)(T&));                // å‡½æ•°æŒ‡é’ˆä¼ å…¥éå†
    template <typename VST> void traverse(VST&);// å‡½æ•°å¼•ç”¨ä¼ å…¥éå†
>>>>>>> 385612237ee3b2211a443370842b941d317370a7


<<<<<<< HEAD
#endif
=======

template <typename T>
void List<T>::init()
{
    header = new ListNode();
    trailer = new ListNode();
    header->pre = NULL; header->next = trailer;
    trailer->pre = header; trailer->next = NULL;
    _size = 0;
}

template <typename T>
int List<T>::clear()
{
    while(header->next != trailer)
    {
        ListNodePosi tmp = header->next->next;
        delete header->next;
        header->next = tmp;
    }
    trailer->pre = header;
}

template <typename T>
void copyNodes(ListNodePosi p, int n)
{
    init();// åˆå§‹åŒ–åˆ—è¡¨
    while(n--)
    {
        insertAsLast(p->data);
        p = p->next;
    }
}


#endif
>>>>>>> 385612237ee3b2211a443370842b941d317370a7
