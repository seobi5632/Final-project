#pragma once
class Barrage : public Component
{
public:
	Barrage();
	VOID Update(VOID);
	VOID setData(Barrage_data* pData);

protected:
	// 이벤트
	VOID OnEnemyBullet_mot_end(Character* pExplosion);
	VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL		 _bFirstPlay;
	FLOAT		 _fSec_count;
	Barrage_data _Data;

};





///////////////////////////////////////////////////////////////
// 클래스  이름 : Barrage
// 첫만든  날짜 : 2009. 9. 26(토)
// 마지막갱신일 : 2009. 9. 26(토)
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : 적이 총알을 쏘개 한다.
// 앞으로 쏘기(밑으로)



