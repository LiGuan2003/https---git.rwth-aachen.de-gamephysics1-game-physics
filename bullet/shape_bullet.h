/**************************************************************************/
/*  shape_bullet.h                                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef SHAPE_CUSTOM_H
#define SHAPE_CUSTOM_H

#include "core/math/geometry.h"
#include "core/variant.h"
#include "rid_bullet.h"
#include "servers/physics_server.h"

#if defined(__clang__) && (__clang_major__ >= 13)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-copy-with-user-provided-copy"
#endif

#include <LinearMath/btAlignedObjectArray.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

#if defined(__clang__) && (__clang_major__ >= 13)
#pragma clang diagnostic pop
#endif

/**
	@author AndreaCatania
*/

class ShapeCustom;
class btCollisionShape;
class ShapeOwnerCustom;
class btBvhTriangleMeshShape;

class ShapeCustom : public RIDCustom {
	Map<ShapeOwnerCustom *, int> owners;
	real_t margin;

protected:
	/// return self
	btCollisionShape *prepare(btCollisionShape *p_btShape) const;
	void notifyShapeChanged();

public:
	ShapeCustom();
	virtual ~ShapeCustom();

	btCollisionShape *create_bt_shape(const Vector3 &p_implicit_scale, real_t p_extra_edge = 0);
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0) = 0;

	void add_owner(ShapeOwnerCustom *p_owner);
	void remove_owner(ShapeOwnerCustom *p_owner, bool p_permanentlyFromThisBody = false);
	bool is_owner(ShapeOwnerCustom *p_owner) const;
	const Map<ShapeOwnerCustom *, int> &get_owners() const;

	void set_margin(real_t p_margin);
	real_t get_margin() const;

	/// Setup the shape
	virtual void set_data(const Variant &p_data) = 0;
	virtual Variant get_data() const = 0;

	virtual PhysicsServer::ShapeType get_type() const = 0;

public:
	static class btEmptyShape *create_shape_empty();
	static class btStaticPlaneShape *create_shape_plane(const btVector3 &planeNormal, btScalar planeConstant);
	static class btSphereShape *create_shape_sphere(btScalar radius);
	static class btBoxShape *create_shape_box(const btVector3 &boxHalfExtents);
	static class btCapsuleShapeZ *create_shape_capsule(btScalar radius, btScalar height);
	static class btCylinderShape *create_shape_cylinder(btScalar radius, btScalar height);
	/// IMPORTANT: Remember to delete the shape interface by calling: delete my_shape->getMeshInterface();
	static class btConvexPointCloudShape *create_shape_convex(btAlignedObjectArray<btVector3> &p_vertices, const btVector3 &p_local_scaling = btVector3(1, 1, 1));
	static class btScaledBvhTriangleMeshShape *create_shape_concave(btBvhTriangleMeshShape *p_mesh_shape, const btVector3 &p_local_scaling = btVector3(1, 1, 1));
	static class btHeightfieldTerrainShape *create_shape_height_field(PoolVector<real_t> &p_heights, int p_width, int p_depth, real_t p_min_height, real_t p_max_height);
	static class btRayShapeCustom *create_shape_ray(real_t p_length, bool p_slips_on_slope);
};

class PlaneShapeCustom : public ShapeCustom {
	Plane plane;

public:
	PlaneShapeCustom();

	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(const Plane &p_plane);
};

class SphereShapeCustom : public ShapeCustom {
	real_t radius;

public:
	SphereShapeCustom();

	_FORCE_INLINE_ real_t get_radius() { return radius; }
	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(real_t p_radius);
};

class BoxShapeCustom : public ShapeCustom {
	btVector3 half_extents;

public:
	BoxShapeCustom();

	_FORCE_INLINE_ const btVector3 &get_half_extents() { return half_extents; }
	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(const Vector3 &p_half_extents);
};

class CapsuleShapeCustom : public ShapeCustom {
	real_t height;
	real_t radius;

public:
	CapsuleShapeCustom();

	_FORCE_INLINE_ real_t get_height() { return height; }
	_FORCE_INLINE_ real_t get_radius() { return radius; }
	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(real_t p_height, real_t p_radius);
};

class CylinderShapeCustom : public ShapeCustom {
	real_t height;
	real_t radius;

public:
	CylinderShapeCustom();

	_FORCE_INLINE_ real_t get_height() { return height; }
	_FORCE_INLINE_ real_t get_radius() { return radius; }
	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_margin = 0);

private:
	void setup(real_t p_height, real_t p_radius);
};

class ConvexPolygonShapeCustom : public ShapeCustom {
public:
	btAlignedObjectArray<btVector3> vertices;

	ConvexPolygonShapeCustom();

	virtual void set_data(const Variant &p_data);
	void get_vertices(Vector<Vector3> &out_vertices);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(const Vector<Vector3> &p_vertices);
};

class ConcavePolygonShapeCustom : public ShapeCustom {
	class btBvhTriangleMeshShape *meshShape;

public:
	PoolVector<Vector3> faces;

	ConcavePolygonShapeCustom();
	virtual ~ConcavePolygonShapeCustom();

	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(PoolVector<Vector3> p_faces);
};

class HeightMapShapeCustom : public ShapeCustom {
public:
	PoolVector<real_t> heights;
	int width;
	int depth;
	real_t min_height;
	real_t max_height;

	HeightMapShapeCustom();

	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(PoolVector<real_t> &p_heights, int p_width, int p_depth, real_t p_min_height, real_t p_max_height);
};

class RayShapeCustom : public ShapeCustom {
public:
	real_t length;
	bool slips_on_slope;

	RayShapeCustom();

	virtual void set_data(const Variant &p_data);
	virtual Variant get_data() const;
	virtual PhysicsServer::ShapeType get_type() const;
	virtual btCollisionShape *create_bt_shape(const btVector3 &p_implicit_scale, real_t p_extra_edge = 0);

private:
	void setup(real_t p_length, bool p_slips_on_slope);
};

#endif // SHAPE_CUSTOM_H
