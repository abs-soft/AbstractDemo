/*
Copyright 2023 Abstract Software, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <gmtl/Math.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <AbstractSDK.h>
#include "AABaseTypes.h"

ABSTRACT_SDK_VALUE_TYPE_DEFINITION_SIZED_EXTERN(ABS_SDK_PROPERTIES(DisplayText = "Vector", ScriptName = "Vector", Priority = "high"), AAFVector, 24);

// gmtl::Vec3d

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Make Vector",
        Category = "InlineMathVector",
        Keywords = "make vector math",
        ToolTips = "Creates a new vector",
        Priority = "high"))
AAFVector MakeVector(AABDouble X, AABDouble Y, AABDouble Z)
{
    gmtl::Vec3d result = { X, Y, Z };
    return AAFVector::Convert(result);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get X of Vector",
        Category = "InlineMathVector",
        Keywords = "get x vector math",
        ToolTips = "Gets the X value of a vector",
        Priority = "high"))
AABDouble GetX(const AAFVector& target)
{
    return target.GetConst<gmtl::Vec3d>()[0];
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Y of Vector",
        Category = "InlineMathVector",
        Keywords = "get y vector math",
        ToolTips = "Gets the Y value of a vector",
        Priority = "high"))
AABDouble GetY(const AAFVector& target)
{
    return target.GetConst<gmtl::Vec3d>()[1];
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Z of Vector",
        Category = "InlineMathVector",
        Keywords = "get z vector math",
        ToolTips = "Gets the Z value of a vector",
        Priority = "high"))
AABDouble GetZ(const AAFVector& target)
{
    return target.GetConst<gmtl::Vec3d>()[2];
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Component-wise Equal",
        Category = "InlineMathVector",
        ToolTip = "Checks whether all components of vectors A and B are the same, within a tolerance.",
        Keywords = "component equal == vector math",
        Priority = "high"))
AABBool AllComponentsEqual(const AAFVector& A, const AAFVector& B, float Tolerance)
{
    return Abs(GetX(A) - GetY(B)) <= Tolerance &&
        Abs(GetX(A) - GetZ(B)) <= Tolerance &&
        Abs(GetY(A) - GetZ(B)) <= Tolerance;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Bound Vector to Box",
        Category = "InlineMathVector",
        ToolTip = "Get a copy of the target vector, clamped inside of a box",
        Keywords = "bound box vector math",
        Priority = "high"))
AAFVector BoundToBox(const AAFVector& target, const AAFVector& Min, const AAFVector& Max)
{
    return MakeVector(
        Clamp(GetX(target), GetX(Min), GetX(Max)),
        Clamp(GetY(target), GetY(Min), GetY(Max)),
        Clamp(GetZ(target), GetZ(Min), GetZ(Max)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Bound Vector to Cube",
        Category = "InlineMathVector",
        ToolTip = "Get a copy of the target vector, clamped inside of a cube",
        Keywords = "bound cube vector math",
        Priority = "high"))
AAFVector BoundToCube(const AAFVector& target, AABDouble Radius)
{
    return MakeVector(
        Clamp(GetX(target), -Radius, Radius),
        Clamp(GetY(target), -Radius, Radius),
        Clamp(GetZ(target), -Radius, Radius));
}

// Add a vector to this and clamp the result in a cube.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// Execution AddBounded(AAFVector& target, const AAFVector& V, AABDouble Radius)
// {
//     target = BoundToCube(target + V, Radius);
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Vectors are Coincident",
        Category = "InlineMathVector",
        ToolTip = "See if two normal vectors are coincident (nearly parallel and point in the same direction).",
        Keywords = "coincident vector math",
        Priority = "high"))
AABBool Coincident(const AAFVector& Normal1, const AAFVector& Normal2, AABDouble ParallelCosineThreshold)
{
    return gmtl::dot(Normal1.GetConst<gmtl::Vec3d>(), Normal2.GetConst<gmtl::Vec3d>()) >= ParallelCosineThreshold;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Component of Vector",
        Category = "InlineMathVector",
        ToolTip = "Gets a specific component of the vector.",
        Keywords = "component get vector math",
        Priority = "high"))
AABDouble Component(const AAFVector& target, AABInt32 Index)
{
    return target.GetConst<gmtl::Vec3d>()[Index];
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Component-wise Max",
        Category = "InlineMathVector",
        ToolTip = "Gets the component-wise max of two vectors.",
        Keywords = "component max vector math",
        Priority = "high"))
AAFVector ComponentMax(const AAFVector& target, const AAFVector& Other)
{
    return MakeVector(
        Max(GetX(target), GetX(Other)),
        Max(GetY(target), GetY(Other)),
        Max(GetZ(target), GetZ(Other)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Component-wise Min",
        Category = "InlineMathVector",
        ToolTip = "Gets the component-wise min of two vectors.",
        Keywords = "component min vector math",
        Priority = "high"))
AAFVector ComponentMin(const AAFVector& target, const AAFVector& Other)
{
    return MakeVector(
        Min(GetX(target), GetX(Other)),
        Min(GetY(target), GetY(Other)),
        Min(GetZ(target), GetZ(Other)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Component-wise Divide",
        Category = "InlineMathVector",
        ToolTip = "Gets the component-wise divide of two vectors.",
        Keywords = "component divide / vector math",
        Priority = "high"))
AAFVector ComponentDivide(const AAFVector& target, const AAFVector& Other)
{
    return MakeVector(
        Divide(GetX(target), GetX(Other)),
        Divide(GetY(target), GetY(Other)),
        Divide(GetZ(target), GetZ(Other)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Component-wise Multiply",
        Category = "InlineMathVector",
        ToolTip = "Gets the component-wise multiply of two vectors.",
        Keywords = "component multiply * vector math",
        Priority = "high"))
AAFVector ComponentMultiply(const AAFVector& target, const AAFVector& Other)
{
    return MakeVector(
        Multiply(GetX(target), GetX(Other)),
        Multiply(GetY(target), GetY(Other)),
        Multiply(GetZ(target), GetZ(Other)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Vector * Float",
        Category = "InlineMathVector",
        ToolTip = "Multiply a vector and a float",
        Keywords = "multiply * vector math float",
        Priority = "high"))
AAFVector Multiply(const AAFVector& target, AABDouble scale)
{
    return MakeVector(
        Multiply(GetX(target), scale),
        Multiply(GetY(target), scale),
        Multiply(GetZ(target), scale));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Vector + Vector",
        Category = "InlineMathVector",
        ToolTip = "Add two vectors",
        Keywords = "add + vector math float",
        Priority = "high"))
    AAFVector Add(const AAFVector& lhs, const AAFVector& rhs)
{
    return MakeVector(
        Add(GetX(lhs), GetX(rhs)),
        Add(GetY(lhs), GetY(rhs)),
        Add(GetZ(lhs), GetZ(rhs)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Vector - Vector",
        Category = "InlineMathVector",
        ToolTip = "Subtract one vector from another",
        Keywords = "subtract - vector math float",
        Priority = "high"))
AAFVector Subtract(const AAFVector& lhs, const AAFVector& rhs)
{
    return MakeVector(
        Subtract(GetX(lhs), GetX(rhs)),
        Subtract(GetY(lhs), GetY(rhs)),
        Subtract(GetZ(lhs), GetZ(rhs)));
}

// See if two planes are coplanar.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AABBool Coplanar(
//     const AAFVector& Base1,
//     const AAFVector& Normal1,
//     const AAFVector& Base2,
//     const AAFVector& Normal2,
//     AABDouble ParallelCosineThreshold)
// {
//     if (!IsParallel(Normal1, Normal2, ParallelCosineThreshold))
//     {
//         return false;
//     }
//     else if (Abs(PointPlaneDist(Base2, Base1, Normal1)) > THRESH_POINT_ON_PLANE)
//     {
//         return false;
//     }
//     else
//     {
//         return true;
//     }
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Cosine Angle 2D",
        Category = "InlineMathVector",
        ToolTip = "Returns the cosine of the angle between this vector and another projected onto the XY plane (no Z).",
        Keywords = "cos angle 2d vector math",
        Priority = "high"))
AABDouble CosineAngle2D(const AAFVector& target, AAFVector B)
{
    gmtl::Vec3d A = { target.GetConst<gmtl::Vec3d>() };
    A[2] = 0.0f;
    B.Get<gmtl::Vec3d>()[2] = 0.0f;
    gmtl::normalize(A);
    gmtl::normalize(B.Get<gmtl::Vec3d>());
    return gmtl::dot(A, B.GetConst<gmtl::Vec3d>());
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Create Orthonormal Basis",
        Category = "InlineMathVector",
        ToolTip = "Create an orthonormal basis from a basis with at least two orthogonal vectors.",
        Keywords = "make ortho basis vector math",
        Priority = "high"))
Execution CreateOrthonormalBasis(
    AAFVector& XAxis,
    AAFVector& YAxis,
    AAFVector& ZAxis)
{
    XAxis.Get<gmtl::Vec3d>() -= gmtl::dot(XAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>()) / gmtl::dot(ZAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>()) * ZAxis.Get<gmtl::Vec3d>();
    YAxis.Get<gmtl::Vec3d>() -= gmtl::dot(YAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>()) / gmtl::dot(ZAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>()) * ZAxis.Get<gmtl::Vec3d>();

    if (gmtl::lengthSquared(XAxis.Get<gmtl::Vec3d>()) < gmtl::GMTL_VEC_EQUAL_EPSILON * gmtl::GMTL_VEC_EQUAL_EPSILON)
    {
        gmtl::cross(XAxis.Get<gmtl::Vec3d>(), YAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>());
    }

    if (gmtl::lengthSquared(YAxis.Get<gmtl::Vec3d>()) < gmtl::GMTL_VEC_EQUAL_EPSILON * gmtl::GMTL_VEC_EQUAL_EPSILON)
    {
        gmtl::cross(YAxis.Get<gmtl::Vec3d>(), XAxis.Get<gmtl::Vec3d>(), ZAxis.Get<gmtl::Vec3d>());
    }

    gmtl::normalize(XAxis.Get<gmtl::Vec3d>());
    gmtl::normalize(YAxis.Get<gmtl::Vec3d>());
    gmtl::normalize(ZAxis.Get<gmtl::Vec3d>());
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Cross Product",
        Category = "InlineMathVector",
        ToolTip = "Calculate the cross product of two vectors.",
        Keywords = "cross product vector math",
        Priority = "high"))
AAFVector CrossProduct(const AAFVector& A, const AAFVector& B)
{
    gmtl::Vec3d result;
    gmtl::cross(result, A.GetConst<gmtl::Vec3d>(), B.GetConst<gmtl::Vec3d>());
    return AAFVector::Convert(result);
}

// // Converts a vector containing degree values to a vector containing radian values.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector DegreesToRadians(const AAFVector& DegVector)
// {
//     //
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Distance",
        Category = "InlineMathVector",
        ToolTip = "Calculate the distance between two vectors.",
        Keywords = "distance vector math",
        Priority = "high"))
AABDouble Distance(const AAFVector& V1, const AAFVector& V2)
{
    const gmtl::Vec3d diff = V1.GetConst<gmtl::Vec3d>() - V2.GetConst<gmtl::Vec3d>();
    return gmtl::length(diff);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Distance Squared",
        Category = "InlineMathVector",
        ToolTip = "Calculate the distance squared between two vectors.",
        Keywords = "distance squared vector math",
        Priority = "high"))
AABDouble DistanceSquared(const AAFVector& V1, const AAFVector& V2)
{
    const gmtl::Vec3d diff = V1.GetConst<gmtl::Vec3d>() - V2.GetConst<gmtl::Vec3d>();
    return gmtl::lengthSquared(diff);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Distance Squared 2D",
        Category = "InlineMathVector",
        ToolTip = "Calculate the distance squared between two vectors projected onto the XY plane (no Z).",
        Keywords = "distance squared 2d vector math",
        Priority = "high"))
AABDouble DistanceSquared2D(const AAFVector& V1, const AAFVector& V2)
{
    return Square(GetX(V1) - GetX(V2)) + Square(GetY(V1) - GetY(V2));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Distance 2D",
        Category = "InlineMathVector",
        ToolTip = "Calculate the distance between two vectors projected onto the XY plane (no Z).",
        Keywords = "distance 2d vector math",
        Priority = "high"))
AABDouble Distance2D(const AAFVector& V1, const AAFVector& V2)
{
    return Sqrt(DistanceSquared2D(V1, V2));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Dot Product",
        Category = "InlineMathVector",
        ToolTip = "Calculate the dot product of two vectors.",
        Keywords = "dot product vector math",
        Priority = "high"))
AABDouble DotProduct(const AAFVector& A, const AAFVector& B)
{
    return gmtl::dot(A.GetConst<gmtl::Vec3d>(), B.GetConst<gmtl::Vec3d>());
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Equals",
        Category = "InlineMathVector",
        ToolTip = "Check against another vector for equality, within specified error limits.",
        Keywords = "equals vector math",
        Priority = "high"))
AABBool Equals(const AAFVector& target, const AAFVector& V, AABDouble Tolerance)
{
    return Abs(GetX(target) - GetX(V)) < Tolerance &&
        Abs(GetY(target) - GetY(V)) < Tolerance &&
        Abs(GetZ(target) - GetZ(V)) < Tolerance;
}

// EvaluateBezier(FindBestAxisVectors(GenerateClusterCenters

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Component-wise Absolute Value",
        Category = "InlineMathVector",
        ToolTip = "Get a copy of this vector with absolute value of each component.",
        Keywords = "get abs vector math",
        Priority = "high"))
AAFVector GetAbs(const AAFVector& target)
{
    return MakeVector(
        Abs(GetX(target)),
        Abs(GetY(target)),
        Abs(GetZ(target)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Max Absolute Value of Vector Components",
        Category = "InlineMathVector",
        ToolTip = "Get the maximum absolute value of the vector's components.",
        Keywords = "abs max vector math",
        Priority = "high"))
AABDouble GetAbsMax(const AAFVector& target)
{
    return Max(
        Max(Abs(GetX(target)), Abs(GetY(target))),
        Abs(GetZ(target)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Min Absolute Value of Vector Components",
        Category = "InlineMathVector",
        ToolTip = "Get the minimum absolute value of the vector's components.",
        Keywords = "abs min vector math",
        Priority = "high"))
AABDouble GetAbsMin(const AAFVector& target)
{
    return Min(
        Min(Abs(GetX(target)), Abs(GetY(target))),
        Abs(GetZ(target)));
}

// ABSTRACT_SDK_NODE_DEFINITION_INLINE(
//     ABS_SDK_PROPERTIES(
//         NodeDisplayText = "Get Clamped Vector",
//         Category = "InlineMathVector",
//         ToolTip = "Create a copy of this vector, with its maximum magnitude clamped to MaxSize."))
// AAFVector GetClampedToMaxSize(const AAFVector& target, AABDouble MaxSize)
// {
//     return MakeVector(
//         Min(GetX(target), MaxSize),
//         Min(GetY(target), MaxSize),
//         Min(GetZ(target), MaxSize));
// }
// 
// ABSTRACT_SDK_NODE_DEFINITION_INLINE(
//     ABS_SDK_PROPERTIES(
//         NodeDisplayText = "Get Clamped Vector 2D",
//         Category = "InlineMathVector",
//         ToolTip = "Create a copy of this vector, with the maximum 2D magnitude clamped to MaxSize. Z is unchanged."))
// AAFVector GetClampedToMaxSize2D(const AAFVector& target, AABDouble MaxSize)
// {
//     return MakeVector(
//         Min(GetX(target), MaxSize),
//         Min(GetY(target), MaxSize),
//         GetZ(target));
// }
// 
// ABSTRACT_SDK_NODE_DEFINITION_INLINE(
//     ABS_SDK_PROPERTIES(
//         NodeDisplayText = "Get Clamped Vector to Size",
//         Category = "InlineMathVector",
//         ToolTip = "Create a copy of this vector, with its magnitude clamped between Min and Max."))
// AAFVector GetClampedToSize(const AAFVector& target, AABDouble Min, AABDouble Max)
// {
//     return MakeVector(
//         Clamp(GetX(target), Min, Max),
//         Clamp(GetY(target), Min, Max),
//         Clamp(GetZ(target), Min, Max));
// }
// 
// // Create a copy of this vector, with the 2D magnitude clamped between Min and Max. Z is unchanged.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector GetClampedToSize2D(const AAFVector& target, AABDouble Min, AABDouble Max)
// {
//     return MakeVector(
//         Clamp(GetX(target), Min, Max),
//         Clamp(GetY(target), Min, Max),
//         GetZ(target));
// }

// Get a specific component of the vector, given a specific axis by enum
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AABDouble GetComponentForAxis(const AAFVector& target, EAxis::Type Axis)
// {
//     return target.GetConst<gmtl::Vec3d>()[static_cast<int>(Axis) - 1];
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Max Component",
        Category = "InlineMathVector",
        ToolTip = "Get the maximum value of the vector's components.",
        Keywords = "component max vector math",
        Priority = "high"))
AABDouble GetMax(const AAFVector& target)
{
    return Max(
        Max(GetX(target), GetY(target)),
        GetZ(target));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Min Component",
        Category = "InlineMathVector",
        ToolTip = "Get the minimum value of the vector's components.",
        Keywords = "component min vector math",
        Priority = "high"))
AABDouble GetMin(const AAFVector& target)
{
    return Min(
        Min(GetX(target), GetY(target)),
        GetZ(target));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Normalized",
        Category = "InlineMathVector",
        ToolTip = "Gets a normalized copy of the vector, checking it is safe to do so based on the length.",
        Keywords = "normal vector math",
        Priority = "high"))
AAFVector GetSafeNormal(AAFVector target, AABDouble Tolerance)
{
    if (gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>()) > Square(Tolerance))
    {
        gmtl::normalize(target.Get<gmtl::Vec3d>());
    }

    return AAFVector::Convert(target);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Normalized 2D",
        Category = "InlineMathVector",
        ToolTip = "Gets a normalized copy of the 2D components of the vector, checking it is safe to do so.",
        Keywords = "normal 2d vector math",
        Priority = "high"))
AAFVector GetSafeNormal2D(AAFVector target, AABDouble Tolerance)
{
    target.Get<gmtl::Vec3d>()[2] = 0.0f;
    if (gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>()) > Square(Tolerance))
    {
        gmtl::normalize(target.Get<gmtl::Vec3d>());
    }

    return AAFVector::Convert(target);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Sign Vector",
        Category = "InlineMathVector",
        ToolTip = "Get a copy of the vector as sign only.",
        Keywords = "sign vector math",
        Priority = "high"))
AAFVector GetSignVector(const AAFVector& target)
{
    return MakeVector(
        Sign(GetX(target)),
        Sign(GetY(target)),
        Sign(GetZ(target)));
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Normalized (Unsafe)",
        Category = "InlineMathVector",
        ToolTip = "Calculates normalized version of vector without checking for zero length.",
        Keywords = "normal unsafe vector math",
        Priority = "high"))
AAFVector GetUnsafeNormal(AAFVector target)
{
    gmtl::normalize(target.Get<gmtl::Vec3d>());
    return target;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Get Normalized (Unsafe) 2D",
        Category = "InlineMathVector",
        ToolTip = "Calculates normalized 2D version of vector without checking for zero length.",
        Keywords = "normal unsafe 2d vector math",
        Priority = "high"))
AAFVector GetUnsafeNormal2D(AAFVector target)
{
    target.Get<gmtl::Vec3d>()[2] = 0.0f;
    gmtl::normalize(target.Get<gmtl::Vec3d>());
    return target;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Grid Snap",
        Category = "InlineMathVector",
        ToolTip = "Gets a copy of this vector snapped to a grid.",
        Keywords = "grid snap vector math",
        Priority = "high"))
AAFVector GridSnap(const AAFVector& target, AABDouble GridSize)
{
    return MakeVector(
        GridSnap(GetX(target), GridSize),
        GridSnap(GetY(target), GridSize),
        GridSnap(GetZ(target), GridSize));
}

// Convert a direction vector into a 'heading' angle.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AABDouble HeadingAngle(const AAFVector& target)
// {
//     AAFVector PlaneDir = PlaneDir.GetSafeNormal();
//     AABDouble Angle = Acos(GetX(PlaneDir));
// 
//     if (GetY(PlaneDir) < 0.0f)
//     {
//         Angle *= -1.0f;
//     }
// 
//     return Angle;
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Is Nearly Zero",
        Category = "InlineMathVector",
        ToolTip = "Checks whether vector is near to zero within a specified tolerance.",
        Keywords = "zero vector math",
        Priority = "high"))
AABBool IsNearlyZero(const AAFVector& target, AABDouble Tolerance)
{
    return
        Abs(GetX(target)) <= Tolerance &&
        Abs(GetY(target)) <= Tolerance &&
        Abs(GetZ(target)) <= Tolerance;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Is Normalized",
        Category = "InlineMathVector",
        ToolTip = "Checks whether vector is normalized.",
        Keywords = "normal vector math",
        Priority = "high"))
AABBool IsNormalized(const AAFVector& target)
{
    return Abs(1.0f - gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>())) < gmtl::GMTL_VEC_EQUAL_EPSILON;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Is Uniform",
        Category = "InlineMathVector",
        ToolTip = "Check whether X, Y and Z are nearly equal.",
        Keywords = "uniform vector math",
        Priority = "high"))
AABBool IsUniform(const AAFVector& target, AABDouble Tolerance)
{
    return Abs(GetX(target) - GetY(target)) <= Tolerance &&
        Abs(GetX(target) - GetZ(target)) <= Tolerance &&
        Abs(GetY(target) - GetZ(target)) <= Tolerance;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Is Unit",
        Category = "InlineMathVector",
        ToolTip = "Check if the vector is of unit length, with specified tolerance.",
        Keywords = "unit 1 vector math",
        Priority = "high"))
AABBool IsUnit(const AAFVector& target, AABDouble LengthSquaredTolerance)
{
    return Abs(1.0f - gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>())) < gmtl::GMTL_VEC_EQUAL_EPSILON;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Is Zero",
        Category = "InlineMathVector",
        ToolTip = "Checks whether all components of the vector are exactly zero.",
        Keywords = "zero 0 vector math",
        Priority = "high"))
AABBool IsZero(const AAFVector& target)
{
    return GetX(target) == 0.0f &&
        GetY(target) == 0.0f &&
        GetZ(target) == 0.0f;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Mirror by Vector",
        Category = "InlineMathVector",
        ToolTip = "Mirror a vector about a normal vector.",
        Keywords = "mirror transform vector math",
        Priority = "high"))
AAFVector MirrorByVector(const AAFVector& target, const AAFVector& MirrorNormal)
{
    gmtl::Vec3d result =
        target.GetConst<gmtl::Vec3d>() -
        MirrorNormal.GetConst<gmtl::Vec3d>() *
        (2.0f * gmtl::dot(target.GetConst<gmtl::Vec3d>(), MirrorNormal.GetConst<gmtl::Vec3d>()));
    return AAFVector::Convert(result);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Normalize In-Place",
        Category = "InlineMathVector",
        ToolTip = "Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.",
        Keywords = "normal vector math",
        Priority = "high"))
AABBool Normalize(AAFVector& target, AABDouble Tolerance)
{
    if (gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>()) > Square(Tolerance))
    {
        gmtl::normalize(target.Get<gmtl::Vec3d>());
        return true;
    }
    else
    {
        return false;
    }
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Orthogonal",
        Category = "InlineMathVector",
        ToolTip = "See if two normal vectors are nearly orthogonal (perpendicular), meaning the angle between them is close to 90 degrees.",
        Keywords = "ortho vector math",
        Priority = "high"))
AABBool Orthogonal(
    const AAFVector& Normal1,
    const AAFVector& Normal2,
    AABDouble OrthogonalCosineThreshold)
{
    return Abs(gmtl::dot(Normal1.GetConst<gmtl::Vec3d>(), Normal2.GetConst<gmtl::Vec3d>())) <= OrthogonalCosineThreshold;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Parallel",
        Category = "InlineMathVector",
        ToolTip = "See if two normal vectors are nearly parallel, meaning the angle between them is close to 0 degrees.",
        Keywords = "parallel compare vector math",
        Priority = "high"))
AABBool Parallel(
    const AAFVector& Normal1,
    const AAFVector& Normal2,
    AABDouble ParallelCosineThreshold)
{
    return Abs(gmtl::dot(Normal1.GetConst<gmtl::Vec3d>(), Normal2.GetConst<gmtl::Vec3d>())) >= ParallelCosineThreshold;
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Distance between Point and Plane",
        Category = "InlineMathVector",
        ToolTip = "Calculate the signed distance (in the direction of the normal) between a point and a plane.",
        Keywords = "distance vector math",
        Priority = "high"))
AABDouble PointPlaneDist(
    const AAFVector& Point,
    const AAFVector& PlaneBase,
    const AAFVector& PlaneNormal)
{
    return gmtl::dot(Point.GetConst<gmtl::Vec3d>() - PlaneBase.GetConst<gmtl::Vec3d>(), PlaneNormal.GetConst<gmtl::Vec3d>());
}

// // Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector PointPlaneProject(
//     const AAFVector& Point,
//     const AAFVector& A,
//     const AAFVector& B,
//     const AAFVector& C)
// {
//     return Point - PointPlaneDist(Point, PlaneBase, PlaneNorm) * PlaneNorm;
// }
// 
// // Calculate the projection of a point on the given plane.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector PointPlaneProject(const AAFVector& Point, const FPlane& Plane)
// {
//     //
// }
// 
// // Calculate the projection of a point on the plane defined by PlaneBase and PlaneNormal.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector PointPlaneProject(
//     const AAFVector& Point,
//     const AAFVector& PlaneBase,
//     const AAFVector& PlaneNormal)
// {
//     //
// }

// // Compare two points and see if they're within specified distance.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AABBool PointsAreNear(
//     const AAFVector& Point1,
//     const AAFVector& Point2,
//     AABDouble Dist)
// {
//     //
// }

// // Compare two points and see if they're the same, using a threshold.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// bool PointsAreSame(const AAFVector& P, const AAFVector& Q)
// {
//     //
// }

// // Projects 2D components of vector based on Z.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector Projection(const AAFVector& target)
// {
//     //
// }
// 
// // Gets a copy of this vector projected onto the input vector.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector ProjectOnTo(const AAFVector& target, const AAFVector& A)
// {
//     //
// }
// 
// // Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector ProjectOnToNormal(const AAFVector& target, const AAFVector& Normal)
// {
//     //
// }
// 
// // Converts a vector containing radian values to a vector containing degree values.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector RadiansToDegrees(const AAFVector& RadVector)
// {
//     //
// }
// 
// // Gets the reciprocal of this vector, avoiding division by zero.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector Reciprocal(const AAFVector& target)
// {
//     //
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Rotate Around Axis",
        Category = "InlineMathVector",
        ToolTip = "Rotates around Axis (assumes Axis.Size() == 1)."),
        Keywords = "rotat vector math",
        Priority = "high")
AAFVector RotateAngleAxis(
    const AAFVector& target,
    AABDouble AngleDeg,
    const AAFVector& Axis)
{
    const AABDouble angle = gmtl::Math::deg2Rad(AngleDeg);
    const AABDouble sin = Sin(AngleDeg);
    const AABDouble cos = Cos(AngleDeg);
    const AABDouble x = GetX(Axis);
    const AABDouble y = GetY(Axis);
    const AABDouble z = GetZ(Axis);
    const AABDouble xx  = x * x;
    const AABDouble yy  = y * y;
    const AABDouble zz  = z * z;
    const AABDouble xy  = x * y;
    const AABDouble yz  = y * z;
    const AABDouble zx  = z * x;
    const AABDouble xsin  = GetX(Axis) * sin;
    const AABDouble ysin  = GetY(Axis) * sin;
    const AABDouble zsin  = GetZ(Axis) * sin;

    const AABDouble invCosRatio = 1.0f - cos;

    return MakeVector(
        (invCosRatio * xx + cos) * x + (invCosRatio * xy - zsin) * y + (invCosRatio * zx + ysin) * z,
        (invCosRatio * xy + zsin) * x + (invCosRatio * yy + cos) * y + (invCosRatio * yz - xsin) * z,
        (invCosRatio * zx - ysin) * x + (invCosRatio * yz + xsin) * y + (invCosRatio * zz + cos) * z);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Set Components In-Place",
        Category = "InlineMathVector",
        ToolTip = "Set the values of the vector directly.",
        Keywords = "set vector math",
        Priority = "high"))
Execution Set(
    AAFVector& target,
    AABDouble InX,
    AABDouble InY,
    AABDouble InZ)
{
    target.Get<gmtl::Vec3d>()[0] = InX;
    target.Get<gmtl::Vec3d>()[1] = InY;
    target.Get<gmtl::Vec3d>()[2] = InZ;
}

// Set a specified componet of the vector, given a specific axis by enum
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// void SetComponentForAxis(
//     AAFVector& target,
//     EAxis::Type Axis,
//     float Component)
// {
//     //
// }

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Length",
        Category = "InlineMathVector",
        ToolTip = "Get the length (magnitude) of this vector.",
        Keywords = "length size vector math",
        Priority = "high"))
AABDouble Length(const AAFVector& target)
{
    return gmtl::length(target.GetConst<gmtl::Vec3d>());
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Length Squared",
        Category = "InlineMathVector",
        ToolTip = "Get the squared length of this vector.",
        Keywords = "length size squared vector math",
        Priority = "high"))
AABDouble LengthSquared(const AAFVector& target)
{
    return gmtl::lengthSquared(target.GetConst<gmtl::Vec3d>());
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Length Squared 2D",
        Category = "InlineMathVector",
        ToolTip = "Get the squared length of the 2D components of this vector.",
        Keywords = "length size squared 2d vector math",
        Priority = "high"))
AABDouble LengthSquared2D(const AAFVector& target)
{
    return Square(target.GetConst<gmtl::Vec3d>()[0]) + Square(target.GetConst<gmtl::Vec3d>()[1]);
}

ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        NodeDisplayText = "Length 2D",
        Category = "InlineMathVector",
        ToolTip = "Get the length of the 2D components of this vector.",
        Keywords = "legth size 2d vector math",
        Priority = "high"))
AABDouble Length2D(const AAFVector& target)
{
    return Sqrt(LengthSquared2D(target));
}

// // Get a short textural representation of this vector, for compact readable logging.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// FString ToCompactString(const AAFVector& target)
// {
//     //
// }

// ToDirectionAndLength

// Const   FString     ToString()
// Get a textual representation of this vector.

// Static  float   Triple
// (
//     const AAFVector& X,
//     const AAFVector& Y,
//     const AAFVector& Z
// )
// Triple product of three vectors: X dot (Y cross Z).

// // Calculate the projection of a vector on the plane defined by PlaneNormal.
// ABSTRACT_SDK_NODE_DEFINITION_INLINE()
// AAFVector VectorPlaneProject(
//     const AAFVector& V,
//     const AAFVector& PlaneNormal)
// {
//     //
// }
