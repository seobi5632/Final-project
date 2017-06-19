#pragma once
class Barrage : public Component
{
public:
	Barrage();
	VOID Update(VOID);
	VOID setData(Barrage_data* pData);

protected:
	// �̺�Ʈ
	VOID OnEnemyBullet_mot_end(Character* pExplosion);
	VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL		 _bFirstPlay;
	FLOAT		 _fSec_count;
	Barrage_data _Data;

};





///////////////////////////////////////////////////////////////
// Ŭ����  �̸� : Barrage
// ù����  ��¥ : 2009. 9. 26(��)
// ������������ : 2009. 9. 26(��)
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : ���� �Ѿ��� � �Ѵ�.
// ������ ���(������)



