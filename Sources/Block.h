#ifndef __BLOCK__H
#define __BLOCK__H

class Block
{
public:

	Block(ShPrefab * prefab);

	void setPosition(CShVector2 position);
	void setPosition(int x, int y);

	void Update();

private:

	//Prefab et entit� 2d
	ShPrefab		*		m_pBlockPref;
	ShEntity2		*		m_pBlockEntity;

	//Coordonnees, Taille et visibilit�
	CShVector2				m_v2Position;
	CShVector2				m_v2Size;
	bool					m_bShow;

};

#endif //__BLOCK__H