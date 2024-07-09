#pragma once

#include "Math/Structs.h"
#include <functional>

struct UITexture;
struct UIMesh
{
	UITexture* Texture = nullptr;
	ColorRGBA Color;
	// source rect (The part of the mesh to be rendered)
};

/// <summary>
/// The base class for every object on the application
/// </summary>
class UIItem
{
public:
	UIItem();
	UIItem(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1),
		const UIMesh& mesh = UIMesh());
	UIItem(const UIItem& item) = default;
	virtual ~UIItem() = default;

	virtual void Draw() = 0;

	/// <summary>
	/// Sets a parent for this item
	/// </summary>
	/// <param name="parent"> The item to be attached </param>
	void Attach(UIItem* parent);
	/// <summary>
	/// Removes all the children from this item
	/// </summary>
	void DettachChildren();
	/// <summary>
	/// Remove the parent of this item (Also remove it from the children list of its parent)
	/// </summary>
	void Dettach();
	/// <summary>
	/// Executes a function to every successor of this item
	/// </summary>
	/// <param name="function"> The function to be executed on every member of the family tree </param>
	void ForEachOnFamilyTree(const std::function<void(UIItem* item)>& function);
	/// <summary>
	/// Moves this item deltaVector amount
	/// </summary>
	/// <param name="deltaVector"> The amount of movement to be applied </param>
	void Translate(const Vector2f& deltaVector);
	/// <summary>
	/// Moves this item into the given vector
	/// </summary>
	/// <param name="positionVector"> The new item position </param>
	void SetPosition(const Vector2f& positionVector);
	/// <summary>
	/// Rotates this item
	/// </summary>
	/// <param name="degrees"> The rotation amount in degrees </param>
	void Rotate(UIFloat degrees);

	/// <summary>
	/// Activates/Deactivates the item
	/// </summary>
	/// <param name="active"> Activation flag </param>
	void SetActive(bool active);
	/// <summary>
	/// Get this item's active status
	/// </summary>
	/// <returns> True if active, otherwise False </returns>
	inline UIBool GetActive() const { return m_Active; }

	/// <summary>
	/// Sets the size of the item
	/// </summary>
	/// <param name="size"> A vector that represents the desired size </param>
	inline virtual void SetSize(const Vector2f& size) { m_Size = size; }
	/// <summary>
	/// Sets the item's mesh color
	/// </summary>
	/// <param name="color"> The color to be adressed </param>
	inline virtual void SetColor(const ColorRGBA& color) { m_Mesh.Color = color; }
	/// <summary>
	/// Sets the item's depth value
	/// </summary>
	/// <param name="value"> The depth value to be adressed </param>
	inline void SetDepthValue(UIFloat value) { m_ChangedDepthValue = true; m_DepthValue = value; }
	/// <summary>
	/// Don't use: Status update
	/// </summary>
	/// <param name="flag"> The flag for the depth value status update </param>
	inline void SetChangedDepthValue(UIBool flag) { m_ChangedDepthValue = flag; }

	/// <summary>
	/// Getter for transform
	/// </summary>
	/// <returns> The item's transform </returns>
	inline Transform GetTransform() const { return m_Transform; }
	/// <summary>
	/// Getter for depth value
	/// </summary>
	/// <returns> The item's depth value </returns>
	inline UIFloat GetDepthValue() const { return m_DepthValue; }
	/// <summary>
	/// Getter for size
	/// </summary>
	/// <returns> The item's size </returns>
	inline Vector2f GetSize() const { return m_Size; }
	/// <summary>
	/// Getter for the parent
	/// </summary>
	/// <returns> The item's parent </returns>
	inline UIItem* GetParent() { return m_Parent; }
	/// <summary>
	/// Getter for children
	/// </summary>
	/// <returns> The item's children </returns>
	inline UIVector<UIItem*>& GetChildren() { return m_Children; }
	/// <summary>
	/// Getter for the color
	/// </summary>
	/// <returns> The item's mesh color </returns>
	inline ColorRGBA GetColor() const { return m_Mesh.Color; }
	/// <summary>
	/// Status check
	/// </summary>
	/// <returns> If the depth value has changed </returns>
	inline UIBool isDepthValueChanged() const { return m_ChangedDepthValue; }
	
	/// <summary>
	/// Child validation
	/// </summary>
	/// <param name="subject"> The item to be checked </param>
	/// <returns> True if the subject is a child of this item, otherwise False </returns>
	bool IsChildOf(UIItem* subject);
	/// <summary>
	/// Ancestor validation
	/// </summary>
	/// <param name="subject"> The item to be checked </param>
	/// <returns> True if the subject is an ancestor of this item, otherwise False </returns>
	bool IsAncestorOf(UIItem* subject);
	/// <summary>
	/// Successor validation
	/// </summary>
	/// <param name="subject"> The item to be checked </param>
	/// <returns> True if the subject is a successor of this item, otherwise False </returns>
	bool IsSuccessorOf(UIItem* subject);
private:
	void AddChild(UIItem* child);
	bool IsSuccessorOfRecursive(UIItem* current, UIItem* subject);
protected:
	void AddMesh(const UIMesh& mesh);
protected:
	Transform m_Transform;
	UIFloat m_DepthValue;
	Vector2f m_Size;
	UIBool m_Active;
	UIMesh m_Mesh;
	UIBool m_ChangedDepthValue = false;

	UIItem* m_Parent;
	UIVector<UIItem*> m_Children;

	friend class Application;
};

class UIWidget : public UIItem
{
public:
	UIWidget() = default;
	UIWidget(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1), const UIMesh& mesh = UIMesh())
		: UIItem(position, size, mesh) {}
	virtual ~UIWidget() = default;

	virtual void Update() = 0;
};