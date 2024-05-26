/**************************************************************************/
/*  bullet_types_converter.h                                              */
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

#ifndef CUSTOM_TYPES_CONVERTER_H
#define CUSTOM_TYPES_CONVERTER_H

#include "core/math/basis.h"
#include "core/math/transform.h"
#include "core/math/vector3.h"
#include "core/typedefs.h"

#if defined(__clang__) && (__clang_major__ >= 13)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-copy-with-user-provided-copy"
#endif

#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

#if defined(__clang__) && (__clang_major__ >= 13)
#pragma clang diagnostic pop
#endif

/**
	@author AndreaCatania
*/

// Custom to Godot
extern void C_TO_G(btVector3 const &inVal, Vector3 &outVal);
extern void INVERT_C_TO_G(btVector3 const &inVal, Vector3 &outVal);
extern void C_TO_G(btMatrix3x3 const &inVal, Basis &outVal);
extern void INVERT_C_TO_G(btMatrix3x3 const &inVal, Basis &outVal);
extern void C_TO_G(btTransform const &inVal, Transform &outVal);

// Godot TO Custom
extern void G_TO_C(Vector3 const &inVal, btVector3 &outVal);
extern void INVERT_G_TO_C(Vector3 const &inVal, btVector3 &outVal);
extern void G_TO_C(Basis const &inVal, btMatrix3x3 &outVal);
extern void INVERT_G_TO_C(Basis const &inVal, btMatrix3x3 &outVal);
extern void G_TO_C(Transform const &inVal, btTransform &outVal);

extern void UNSCALE_BT_BASIS_CUSTOM(btTransform &scaledBasis);

#endif // CUSTOM_TYPES_CONVERTER_H
