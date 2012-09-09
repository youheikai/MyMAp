// ===========================================================================
/*!
 *
 *  MyMap�N���X�̒�`
 *  
 */
// ===========================================================================

#ifndef __MYMAP_H__
#define __MYMAP_H__

// #define __CONSOLE_OUTOUT__ // �����define�����Debug���̃R���\�[���o�͂��s��
#ifdef __CONSOLE_OUTOUT__
#include <iostream>
#endif
	
using namespace std;

#if 0
	
//#
//#
//#�E�v�f�̎擾
//#	<< names[10]
//#
//#�E�v�f�̒ǉ�
//#�@	names[10] = "fff";
//#

#endif

// ===========================================================================
/*!
 *	MapData�N���X
 *
 *	int�^��key�Ƃ����}�b�v���������邽�߂̃f�[�^�N���X
 */
// ===========================================================================
template <typename TYPE>
class MapData {
public:
	// �R���X�g���N�^
	MapData() {
		key = NULL; // ��new�������ꂪ���܂���0�ɂȂ��ĂĂ݂����Ȃ̂��ĂȂ��H
		type_dat = NULL;
		back = NULL;
		next = NULL;
	}
	// �f�X�g���N�^
	virtual ~MapData(){}

	int *key;		// key�ւ̃|�C���^
	TYPE *type_dat; // ���f�[�^�ւ̃|�C���^

	MapData <TYPE> *back; // ���̃��X�g�ւ̃|�C���^
	MapData <TYPE> *next; // �O�̃��X�g�ւ̃|�C���^
	
public:
	// MapData�I�u�W�F�N�g�𐶐����A���̃|�C���^��Ԃ�
	static MapData <TYPE>* CreateMapData(void)
	{
		// �C���X�^���X�𐶐�
		MapData <TYPE> *pt = new MapData <TYPE>;
		return (pt);
	}
};

// ===========================================================================
/*!
 *	MyMap�N���X
 *
 *	MAP���������邽�߂̃N���X
 *	key���w�肵�Ẵf�[�^�̓o�^�A�擾���s�����Ƃ��ł���
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
	 *  �������������s��
	 *
	 *  \param �Ȃ�
	 *  \return �Ȃ�
	 */
	// ===========================================================================
	void Init(void)
	{
		head = NULL;
		tail = NULL;
	}

	// ===========================================================================
	/*!
	 *  �I���������s��
	 *
	 *  \param �Ȃ�
	 *  \return �Ȃ�
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
	// �R���X�g���N�^
	MyMap() {
		Init();
	}
	
	// �R���X�g���N�^2
	MyMap(TYPE data, int key) {
		Init();
		Insert(data, key);
	}

	// �f�X�g���N�^
	virtual ~MyMap() {
		Dispose();
	}

	// ===========================================================================
	/*!
	 *  key���w�肵�āA�f�[�^��o�^����
	 *
	 *  \param[in] data
	 *  \return �Ȃ�
	 */
	// ===========================================================================
	void Insert(TYPE data, int key)
	{
		// ���݂��Ȃ�key���w�肳�ꂽ�ꍇ�A�V�K�o�^����
		// ���ɑ��ݍς݂�key���w�肳�ꂽ�ꍇ�A�㏑������
		MapData <TYPE> *pt = head;

		while (pt != NULL)
		{
			if (*pt->key == key) // key��v
			{
				// ��U�j��
				delete pt->key;
				delete pt->type_dat;
				// ����
				pt->key = new int;
				pt->type_dat = new TYPE;
				// ���
				*pt->key = key;
				*pt->type_dat = data;
				return;
			}
			pt = pt->next;
		}
		// key���o�^����Ă��Ȃ��̂ŁA�V�K�o�^ //

		// �C���X�^���X�𐶐�
		pt = MapData<TYPE>::CreateMapData();

		pt->key = new int;
		pt->type_dat = new TYPE;
		// ���
		*pt->key = key;
		*pt->type_dat = data;
				
		// ����
		if ( head == NULL && tail == NULL ) {
			head = pt; // ������
			tail = pt; // ������
		// 2�ڈȍ~
		} else {
			tail->next	= pt;	// �Ō���������|�C���^
			pt->back	= tail;
			pt->next	= NULL;
			tail		= pt;
		}
		
		return;
	}

	// ===========================================================================
	/*!
	 *  Key�ƈ�v�����f�[�^���폜����
	 *
	 *  \param[in] ���X�g�ԍ�
	 *  \return bool
	 */
	// ===========================================================================
	bool Delete(int key)
	{	
		// ���݂��Ȃ�key���w�肳�ꂽ�ꍇ false��Ԃ�
		MapData <TYPE> *pt = head;	// ���݂̃|�C���^���Q�Ƃ��邽�߂Ɏg�p

		while( pt != NULL)
		{
			if (*pt->key == key) // key��v
			{
				// �擪�̂Ƃ�
				if(pt == head) {
					return(DeleteHead());
				}
				// �����̂Ƃ�
				else if (pt == tail) {
					return(DeleteTail());
				}
				// �^�񒆂̃f�[�^�̂Ƃ�
				else {
					pt->back->next = pt->next;	// �O�̃��X�g�̂������t���ւ�
					pt->next->back = pt->back;	// ���̃��X�g�̂����܂�t���ւ�
					delete pt->key;
					delete pt->type_dat;
					delete pt;
				}
				return (true);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "��v�f�[�^������܂���" << endl;	// Debug
#endif
		return (false);
	}

	// ===========================================================================
	/*!
	 *  key�ƈ�v�����f�[�^���擾����
	 *
	 *  \param[in] �t�@�C������\��������ւ̃|�C���^
	 *  \return TYPE
	 */
	// ===========================================================================
	TYPE Get(int key)
	{	
		MapData <TYPE> *pt = head;

		while( pt != NULL)
		{
			if (*pt->key == key) { // key��v
				return (*pt->type_dat);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "��v�f�[�^������܂���" << endl;	// Debug
#endif

		return (*pt->type_dat); // ���݂��Ȃ� �� exception
	}

	// ===========================================================================
	/*!
	 *  key�ƈ�v�����f�[�^���擾����
	 *
	 *  \param[in] �t�@�C������\��������ւ̃|�C���^
	 *  \return TYPE
	 */
	// ===========================================================================
	bool Get(int key, TYPE *data)
	{	
		// ���݂��Ȃ�key���w�肳�ꂽ�ꍇ�Afalse��Ԃ�

		MapData <TYPE> *pt = head;

		while( pt != NULL)
		{
			if (*pt->key == key) { // key��v
				data = pt->type_dat;
				return (true);
			}
			pt = pt->next;
		}
#ifdef __CONSOLE_OUTOUT__
		cout << "��v�f�[�^������܂���" << endl;	// Debug
#endif
		return (false);
	}
	
	// ===========================================================================
	/*!
	 *  �i�[�f�[�^�̑������擾����
	 *
	 *  \param �Ȃ�
	 *  \return �i�[�f�[�^�̑���
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
	 *  �O���̃��X�g���폜����
	 *
	 *  \param �Ȃ�
	 *  \return bool
	 */
	// ===========================================================================
	bool DeleteHead(void)
	{
		MapData <TYPE> *head_pt = head;	// �f�[�^�ړ��p
		int ret = 0;

		// �f�[�^�Ȃ�
		if ( head == NULL && tail == NULL ) {
			return (false);
		// �f�[�^����̂�
		} else if( head_pt->next == NULL ) {
			delete head_pt->key;
			delete head_pt->type_dat;
			delete head_pt;
			Init();
		} else {
			// �폜����
			head->next->back = NULL;		// �ȑO��back��NULL
			head = head_pt->next;			// head���ړ�
			delete head_pt->key;
			delete head_pt->type_dat;
			delete head_pt;
		}
		return (true);
	}

	// ===========================================================================
	/*!
	 *  �����̃��X�g���폜����
	 *
	 *  \param �Ȃ�
	 *  \return bool
	 */
	// ===========================================================================
	bool DeleteTail()
	{
		MapData <TYPE> *pt_tail = tail;	// �f�[�^�ړ��p
		unsigned int ret = 0;

		// �f�[�^�Ȃ�
		if ( head == NULL && tail == NULL ) {
			return (false);
		// �f�[�^����̂�
		} else if( pt_tail->back == NULL ) {
			delete pt_tail->key;
			delete pt_tail->type_dat;
			delete pt_tail;
			Init();
		} else {
			// �폜����
			tail->back->next = NULL;		// �V����tail��next
			tail = pt_tail->back;			// tail���ړ�
			delete pt_tail->key;
			delete pt_tail->type_dat;
			delete pt_tail;
		}
		return (true);
	}
};

#endif