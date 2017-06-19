#pragma once

class SceneManager : public GameBase
{
public:
	SceneManager();
	VOID Initialize(VOID);
	VOID Update(VOID);
	VOID Draw(VOID);
	VOID Release(VOID);
protected:
	GameScene* _pGameScene;
};



///////////////////////////////////////////////////////////////
// 클래스  이름 : SceneManager
// 첫만든  날짜 : 2009. 9. 3
// 마지막갱신일 : 2009. 9. 3
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : Scene들의 생성, 삭제등을 관리한다.
//

