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
// Ŭ����  �̸� : SceneManager
// ù����  ��¥ : 2009. 9. 3
// ������������ : 2009. 9. 3
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : Scene���� ����, �������� �����Ѵ�.
//

