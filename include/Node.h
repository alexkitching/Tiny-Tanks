//////////////////////////////////////////////////////////////////////////
// File: <Node.h>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Header file for all Tank classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////


#ifndef _Node_H_
#define _Node_H_

#include "Matrix3.h"
#include <set>


class Vector2;
class Node
{
public:
	// Constructors
	Node();
	virtual ~Node();

	//Functions
	void SetParent(Node* a_parent);
	void AddChild(Node* a_child);
	void RemoveChild(Node* a_child);
	void GetWorldTransform(Matrix3& a_m3Transform);
	void GetLocalTransform(Matrix3& a_m3Transform) const;
	void SetTranslation(const Vector2 a_v2Translation);
	void RotateZ(const float a_fRotation);
	void Scale(const float a_fScale);

protected:

	Matrix3 m3PosRot;
private:
	Node* m_pParent;
	std::set<Node*>m_pChildren;
};

#endif // !_Node_H_