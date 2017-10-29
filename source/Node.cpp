//////////////////////////////////////////////////////////////////////////
// File: <Node.cpp>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Source file for the Node class.>
/////////////////////////////////////////////////////////////////////////

#include "Node.h"
#include "Vector3.h"
#include "Vector2.h"

// Constructor
Node::Node()
{
	m_pParent = nullptr;
	m3PosRot = Matrix3::Identity;
}

// Destructor (Virtual since node is used as a base class.)
Node::~Node()
{
	for (auto iter = m_pChildren.begin(); iter != m_pChildren.end(); ++iter)
	{
		RemoveChild(*iter);
	}
	m_pParent = nullptr;
}

// Function to set this node's parent.
void Node::SetParent(Node* a_parent)
{
	if (a_parent == this)
		return;

	if (m_pParent != nullptr)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = a_parent;
	m_pParent->AddChild(this);
}

// Function to add a child to the node.
void Node::AddChild(Node* a_child)
{
	auto iter = m_pChildren.find(a_child);
	// Children are stored in a set. One of the features of a set is easy searching for an item
	// this allows us to see if the child already exists in the set of children. 
	// If it exists already we will not add it to the set multiple times.
	if (iter == m_pChildren.end())
	{
		m_pChildren.emplace(a_child);
	}
}

// Remove a child from our node hierarchy
void Node::RemoveChild(Node* a_child)
{
	// If we can find the child remove it, a successful find returns an iterator to the object
	// we are looking for. An unsuccessful find returns an iterator that is one item past the end of the set.
	auto iter = m_pChildren.find(a_child);
	if (iter != m_pChildren.end())
	{
		m_pChildren.erase(iter);
	}
}

// Where is this node in the world
// This requires us to transform (multiply) this node by any parents it may have (and their parents in turn).
void Node::GetWorldTransform(Matrix3 & a_m3Transform)
{
	if (m_pParent)
	{
		m_pParent->GetWorldTransform(a_m3Transform);
		a_m3Transform = m3PosRot * a_m3Transform;
	}
	else
	{
		a_m3Transform = m3PosRot;
	}
}

// Get the local transform for our point
void Node::GetLocalTransform(Matrix3 & a_m3Transform) const
{
	a_m3Transform = m3PosRot;
}

// Sets our translation
void Node::SetTranslation(const Vector2 a_v2Translation)
{
	m3PosRot.SetRow(2, Vector3(a_v2Translation));
}

// Rotate this node around it's z axis
void Node::RotateZ(const float a_fRotation)
{
	Matrix3 m3Rotation = Matrix3::Identity;
	m3Rotation.Rotate(a_fRotation);
	m3PosRot = m3Rotation * m3PosRot;
}

void Node::Scale(const float a_fScale)
{
	Vector3 translation = Vector3::Zero;
	translation = m3PosRot.GetRow(2);

	Matrix3 scale = Matrix3::Identity;
	scale.Scale(a_fScale, a_fScale);
	m3PosRot = scale * m3PosRot;

	m3PosRot.SetRow(2, translation);
}
