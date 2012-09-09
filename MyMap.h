// ===========================================================================
/*!
 *
 *  MyMapクラスの定義
 *  
 */
// ===========================================================================

#ifndef __MYMAP_H__
#define __MYMAP_H__

// #define __CONSOLE_OUTOUT__ // これをdefineするとDebug情報のコンソール出力を行う
#ifdef __CONSOLE_OUTOUT__
#include <iostream>
#endif
	
using namespace std;

#if 0
	
//#
//#
//#・要素の取得
//#	<< names[10]
//#
//#・要素の追加
//#　	names[10] = "fff";
//#

#endif

// ===========================================================================
/*!
 *	MapDataクラス
 *
 *	int型をkeyとしたマップを実現するためのデータクラス
 */
// ===========================================================================
template <typename TYPE>
class MapData {
public:
	// コンストラクタ
	MapData() {
		key = NULL; // ★newしたこれがたまたま0になっててみたいなのってない？
		type_dat = NULL;
		back = NULL;
		next = NULL;
	}
	// デストラクタ
	virtual ~MapData(){}

	int *key;		// keyへのポインタ
	TYPE *type_dat; // 実データへのポインタ

	MapData <TYPE> *back; // 次のリストへのポインタ
	MapData <TYPE> *next; // 前のリストへのポインタ
	
public:
	// MapDataオブジェクトを生成し、そのポインタを返す
	static MapData <TYPE>* CreateMapData(void)
	{
		// インスタンスを生成
		MapData <TYPE> *pt = new MapData <TYPE>;
		return (pt);
	}
};

// ===========================================================================
/*!
 *	MyMapクラス
 *
 *	MAPを実現するためのクラス
 *	keyを指定してのデータの登録、取得を行うことができる
 */
// ===========================================================================
template <typename TYPE>
class MyMap
{
private:
	MapData <TYPE> *head;
	MapData <TYPE> *tail;
	
	// ===========================================================================
	/*!
	 *  初期化処理を行う
	 *
	 *  \param なし
	 *  \return なし
	 */
	// ===========================================================================
	void Init(void)
	{
		head = NULL;
		tail = NULL;
	}

	// ===========================================================================
	/*!
	 *  終了処理を行う
	 *
	 *  \param なし
	 *  \return なし
	 */
	// ===========================================================================
	void Dispose(void)
	{
		MapData <TYPE> *pt = head;
		MapData <TYPE> *del_pt;

		while( pt != NULL)
		{
			del_pt = pt;
			pt = pt->next;
			delete del_pt->key;
			delete del_pt->type_dat;
			delete del_pt;
		}
	}
	
public:
	// コンストラクタ
	MyMap() {
		Init();
	}
	
	// コンストラクタ2
	MyMap(TYPE data, int key) {
		Init();
		Insert(data, key);
	}

	// デストラクタ
	virtual ~MyMap() {
		Dispose();
	}

	// ===========================================================================
	/*!
	 *  keyを指定して、データを登録する
	 *
	 *  \param[in] data
	 *  \return なし
	 */
	// ===========================================================================
	void Insert(TYPE data, int key)
	{
		// 存在しないkeyが指定された場合、新規登録する
		// 既に存在済みのkeyが指定された場合、上書きする
		MapData <TYPE> *pt = head;

		while (pt != NULL)
		{
			if (*pt->key == key) // key一致
			{
				// 一旦破棄
				delete pt->key;
				delete pt->type_dat;
				// 生成
				pt->key = new int;
				pt->type_dat = new TYPE;
				// 代入
				*pt->key = key;
				*pt->type_dat = data;
				return;
			}
			pt = pt->next;
		}
		// keyが登録されていないので、新規登録 //

		// インスタンスを生成
		pt = MapData<TYPE>::CreateMapData();

		pt->key = new int;
		pt->type_dat = new TYPE;
		// 代入
		*pt->key = key;
		*pt->type_dat = data;
				
		// 初回
		if ( head == NULL && tail == NULL ) {
			head = pt; // あたま
			tail = pt; // おしり
		// 2個目以降
		} else {
			tail->next	= pt;	// 最後尾だったポインタ
			pt->back	= tail;
			pt->next	= NULL;
			tail		= pt;
		}
		
		return;
	}

	// ===========================================================================
	/*!
	 *  Keyと一致したデータを削除する
	 *
	 *  \param[in] リスト番号
	 *  \return bool
	 */
	// ===========================================================================
	bool Delete(int key)
	{	
		// 存在しないkeyが指定された場合 falseを返す
		MapData <TYPE> *pt = head;	// 現在のポインタを参照するために使用

		while( pt != NULL)
		{
			if (*pt->key == key) // key一致
			{
				// 先頭のとき
				if(pt == head) {
					return(DeleteHead());
				}
				// 末尾のとき
				else if (pt == tail) {
					return(DeleteTail());
				}
				// 真ん中のデータのとき
				else {
					pt->back->next = pt->next;	// 前のリストのおしりを付け替え
					pt->next->back = pt->back;	// 次のリストのあたまを付け替え
					delete pt->key;
					delete pt->type_dat;
					delete pt;
				}
				return (true);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "一致データがありません" << endl;	// Debug
#endif
		return (false);
	}

	// ===========================================================================
	/*!
	 *  keyと一致したデータを取得する
	 *
	 *  \param[in] ファイル名を表す文字列へのポインタ
	 *  \return TYPE
	 */
	// ===========================================================================
	TYPE Get(int key)
	{	
		MapData <TYPE> *pt = head;

		while( pt != NULL)
		{
			if (*pt->key == key) { // key一致
				return (*pt->type_dat);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "一致データがありません" << endl;	// Debug
#endif

		return (*pt->type_dat); // 存在しない → exception
	}

	// ===========================================================================
	/*!
	 *  keyと一致したデータを取得する
	 *
	 *  \param[in] ファイル名を表す文字列へのポインタ
	 *  \return TYPE
	 */
	// ===========================================================================
	bool Get(int key, TYPE *data)
	{	
		// 存在しないkeyが指定された場合、falseを返す

		MapData <TYPE> *pt = head;

		while( pt != NULL)
		{
			if (*pt->key == key) { // key一致
				data = pt->type_dat;
				return (true);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "一致データがありません" << endl;	// Debug
#endif
		return (false);
	}
	
	// ===========================================================================
	/*!
	 *  格納データの総数を取得する
	 *
	 *  \param なし
	 *  \return 格納データの総数
	 */
	// ===========================================================================
	unsigned int GetNum(void)
	{
		unsigned int Count = 0;
		MapData <TYPE> *pt = head;

		while( pt != NULL)
		{
			Count++;
			pt = pt->next;
		}
		return (Count);
	}

// ---- Private --------------------------------------------------

private:

	// ===========================================================================
	/*!
	 *  前方のリストを削除する
	 *
	 *  \param なし
	 *  \return bool
	 */
	// ===========================================================================
	bool DeleteHead(void)
	{
		MapData <TYPE> *head_pt = head;	// データ移動用
		int ret = 0;

		// データなし
		if ( head == NULL && tail == NULL ) {
			return (false);
		// データが一つのみ
		} else if( head_pt->next == NULL ) {
			delete head_pt->key;
			delete head_pt->type_dat;
			delete head_pt;
			Init();
		} else {
			// 削除処理
			head->next->back = NULL;		// 以前のbackをNULL
			head = head_pt->next;			// headを移動
			delete head_pt->key;
			delete head_pt->type_dat;
			delete head_pt;
		}
		return (true);
	}

	// ===========================================================================
	/*!
	 *  末尾のリストを削除する
	 *
	 *  \param なし
	 *  \return bool
	 */
	// ===========================================================================
	bool DeleteTail()
	{
		MapData <TYPE> *pt_tail = tail;	// データ移動用
		unsigned int ret = 0;

		// データなし
		if ( head == NULL && tail == NULL ) {
			return (false);
		// データが一つのみ
		} else if( pt_tail->back == NULL ) {
			delete pt_tail->key;
			delete pt_tail->type_dat;
			delete pt_tail;
			Init();
		} else {
			// 削除処理
			tail->back->next = NULL;		// 新しいtailのnext
			tail = pt_tail->back;			// tailを移動
			delete pt_tail->key;
			delete pt_tail->type_dat;
			delete pt_tail;
		}
		return (true);
	}
};

#endif