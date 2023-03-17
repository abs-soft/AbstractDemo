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

#include <cmath>
#include <AbstractSDK.h>

ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Unsigned Integer (8 bits)", ScriptName = "uInt8", Priority = "high"), AABuInt8, uint8_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Unsigned Integer (16 bits)", ScriptName = "uInt16", Priority = "high"), AABuInt16, uint16_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Unsigned Integer (32 bits)", ScriptName = "uInt32", Priority = "high"), AABuInt32, uint32_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Unsigned Integer (64 bits)", ScriptName = "uInt64", Priority = "high"), AABuInt64, uint64_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Integer (8 bits)", ScriptName = "Int8", Priority = "high"), AABInt8, int8_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Integer (16 bits)", ScriptName = "Int16", Priority = "high"), AABInt16, int16_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Integer (32bits)", ScriptName = "Int32", Priority = "high"), AABInt32, int32_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Integer (64 bits)", ScriptName = "Int64", Priority = "high"), AABInt64, int64_t);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Float", ScriptName = "Float", Priority = "high"), AABFloat, float);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Double", ScriptName = "Double", Priority = "high"), AABDouble, double);
ABSTRACT_SDK_VALUE_TYPE_DEFINITION(ABS_SDK_PROPERTIES(DisplayText = "Boolean", ScriptName = "Bool", Priority = "high"), AABBool, bool);

ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABuInt32);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABInt8);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABInt16);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABInt32);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_INTEGER_EDITOR(AABInt64);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_NUMBER_EDITOR(AABFloat);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_NUMBER_EDITOR(AABDouble);
ABSTRACT_SDK_VALUE_TYPE_SUPPORT_BOOLEAN_EDITOR(AABBool);

ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABuInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABuInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABuInt32);

ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt8, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt16, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt32, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABuInt64, AABInt32);

ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABuInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABuInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABuInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABuInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABuInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABuInt32);

ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt8, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABInt32);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt16, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt32, AABInt64);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABInt8);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABInt16);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABInt64, AABInt32);

ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABFloat, AABDouble);
ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE(AABDouble, AABFloat);

namespace AABaseTypesInternal
{
    template<typename T>
    T Add(T lhs, T rhs) { return lhs + rhs; }
    template<typename T>
    T Subtract(T lhs, T rhs) { return lhs - rhs; }
    template<typename T>
    T Multiply(T lhs, T rhs) { return lhs * rhs; }
    template<typename T>
    T Divide(T lhs, T rhs) { return lhs / rhs; }
    template<typename T>
    T Abs(T target) { return target < static_cast<T>(0) ? -target : target; }
    template<typename T>
    T Clamp(T target, T min, T max) { return target > max ? max : (target < min ? min : target); }
    template<typename T>
    T Max(T lhs, T rhs) { return lhs < rhs ? rhs : lhs; }
    template<typename T>
    T Min(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }
    template<typename T>
    T Sqrt(T target) { return sqrt(target); }
    template<typename T>
    T Square(T target) { return target * target; }
    template<typename T>
    T Sign(T target) { return target < static_cast<T>(0) ? static_cast<T>(-1) : (target > static_cast<T>(0) ? static_cast<T>(1) : static_cast<T>(0)); }
    template<typename T>
    T Round(T target) { return round(target); }
    template<typename T>
    T GridSnap(T target, T GridSize) { return round(target / GridSize) * GridSize; }
    template<typename T>
    T Sin(T target) { return sin(target); }
    template<typename T>
    T Cos(T target) { return cos(target); }
    template<typename T>
    T Tan(T target) { return tan(target); }
    template<typename T>
    T ASin(T target) { return asin(target); }
    template<typename T>
    T ACos(T target) { return acos(target); }
    template<typename T>
    T ATan(T target) { return atan(target); }
    template<typename T>
    AABBool Equals(T lhs, T rhs) { return lhs == rhs; }
    template<typename T>
    AABBool NotEqual(T lhs, T rhs) { return lhs != rhs; }
    template<typename T>
    AABBool GreaterThan(T lhs, T rhs) { return lhs > rhs; }
    template<typename T>
    AABBool GreaterThanOrEqualTo(T lhs, T rhs) { return lhs >= rhs; }
    template<typename T>
    AABBool LessThan(T lhs, T rhs) { return lhs < rhs; }
    template<typename T>
    AABBool LessThanOrEqualTo(T lhs, T rhs) { return lhs <= rhs; }
}



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float + float",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math float number",
        ToolTips = "Adds two floats together",
        Priority = "high"))
AABFloat Add(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float - float",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math float number",
        ToolTips = "Subtracts one float from another",
        Priority = "high"))
AABFloat Subtract(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float * float",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math float number",
        ToolTips = "Multiplies two floats together",
        Priority = "high"))
AABFloat Multiply(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float / float",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math float number",
        ToolTips = "Divides one float by another",
        Priority = "high"))
AABFloat Divide(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|float|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math float number",
        ToolTips = "Returns the absolute value of a float",
        Priority = "high"))
AABFloat Abs(AABFloat target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (float)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit float number",
        ToolTips = "Clamps a float between a minimum and a maximum value",
        Priority = "high"))
AABFloat Clamp(AABFloat target, AABFloat min, AABFloat max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (float)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math float number",
        ToolTips = "Returns the maximum value of two floats",
        Priority = "high"))
AABFloat Max(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (float)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math float number",
        ToolTips = "Returns the minimum value of two floats",
        Priority = "high"))
AABFloat Min(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sqrt (float)",
        ScriptName = "Sqrt",
        Category = "InlineMath",
        Keywords = "square root sqrt math float number",
        ToolTips = "Returns the square root of a float",
        Priority = "high"))
AABFloat Sqrt(AABFloat target) { return AABaseTypesInternal::Sqrt(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Square (float)",
        ScriptName = "Square",
        Category = "InlineMath",
        Keywords = "square math float number",
        ToolTips = "Returns the square of a float",
        Priority = "high"))
AABFloat Square(AABFloat target) { return AABaseTypesInternal::Square(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (float)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math float number",
        ToolTips = "Returns the sign of a float (1 if positive, -1 if negative)",
        Priority = "high"))
AABFloat Sign(AABFloat target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Round (float)",
        ScriptName = "Round",
        Category = "InlineMath",
        Keywords = "round math float number",
        ToolTips = "Rounds a float to the nearest integer",
        Priority = "high"))
AABFloat Round(AABFloat target) { return AABaseTypesInternal::Round(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "GridSnap (float)",
        ScriptName = "GridSnap",
        Category = "InlineMath",
        Keywords = "grid snap math float number",
        ToolTips = "Snaps a float to a grid with a specified spacing",
        Priority = "high"))
AABFloat GridSnap(AABFloat target, AABFloat GridSize) { return AABaseTypesInternal::GridSnap(target, GridSize); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sin (float)",
        ScriptName = "Sin",
        Category = "InlineMath",
        Keywords = "sine sin math float number",
        ToolTips = "Returns the sine of a float (in radians)",
        Priority = "high"))
AABFloat Sin(AABFloat target) { return AABaseTypesInternal::Sin(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Cos (float)",
        ScriptName = "Cos",
        Category = "InlineMath",
        Keywords = "cosine cos math float number",
        ToolTips = "Returns the cosine of a float (in radians)",
        Priority = "high"))
AABFloat Cos(AABFloat target) { return AABaseTypesInternal::Cos(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Tan (float)",
        ScriptName = "Tan",
        Category = "InlineMath",
        Keywords = "tangent tan math float number",
        ToolTips = "Returns the tangent of a float (in radians)",
        Priority = "high"))
AABFloat Tan(AABFloat target) { return AABaseTypesInternal::Tan(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ASin (float)",
        ScriptName = "ASin",
        Category = "InlineMath",
        Keywords = "inverse sine asin math float number",
        ToolTips = "Returns the inverse sine of a float (in radians)",
        Priority = "high"))
AABFloat ASin(AABFloat target) { return AABaseTypesInternal::ASin(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ACos (float)",
        ScriptName = "ACos",
        Category = "InlineMath",
        Keywords = "inverse cosine acos math float number",
        ToolTips = "Returns the inverse cosine of a float (in radians)",
        Priority = "high"))
AABFloat ACos(AABFloat target) { return AABaseTypesInternal::ACos(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ATan (float)",
        ScriptName = "ATan",
        Category = "InlineMath",
        Keywords = "inverse tangent atan math float number",
        ToolTips = "Returns the inverse tangent of a float (in radians)",
        Priority = "high"))
AABFloat ATan(AABFloat target) { return AABaseTypesInternal::ATan(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float == float",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison float number",
        ToolTips = "Checks if two float values are equal",
        Priority = "high"))
AABBool Equals(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float != float",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison float number",
        ToolTips = "Checks if two float values are not equal",
        Priority = "high"))
AABBool NotEqual(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float > float",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison float number",
        ToolTips = "Checks if the first float value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float >= float",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison float number",
        ToolTips = "Checks if the first float value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float < float",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison float number",
        ToolTips = "Checks if the first float value is less than the second",
        Priority = "high"))
AABBool LessThan(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "float <= float",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison float number",
        ToolTips = "Checks if the first float value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABFloat lhs, AABFloat rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double + double",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math double number",
        ToolTips = "Adds two doubles together",
        Priority = "high"))
AABDouble Add(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double - double",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math double number",
        ToolTips = "Subtracts one double from another",
        Priority = "high"))
AABDouble Subtract(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double * double",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math double number",
        ToolTips = "Multiplies two doubles together",
        Priority = "high"))
AABDouble Multiply(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double / double",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math double number",
        ToolTips = "Divides one double by another",
        Priority = "high"))
AABDouble Divide(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|double|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math double number",
        ToolTips = "Returns the absolute value of a double",
        Priority = "high"))
AABDouble Abs(AABDouble target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (double)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit double number",
        ToolTips = "Clamps a double between a minimum and a maximum value",
        Priority = "high"))
AABDouble Clamp(AABDouble target, AABDouble min, AABDouble max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (double)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math double number",
        ToolTips = "Returns the maximum value of two doubles",
        Priority = "high"))
AABDouble Max(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (double)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math double number",
        ToolTips = "Returns the minimum value of two doubles",
        Priority = "high"))
AABDouble Min(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sqrt (double)",
        ScriptName = "Sqrt",
        Category = "InlineMath",
        Keywords = "square root sqrt math double number",
        ToolTips = "Returns the square root of a double",
        Priority = "high"))
AABDouble Sqrt(AABDouble target) { return AABaseTypesInternal::Sqrt(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Square (double)",
        ScriptName = "Square",
        Category = "InlineMath",
        Keywords = "square math double number",
        ToolTips = "Returns the square of a double",
        Priority = "high"))
AABDouble Square(AABDouble target) { return AABaseTypesInternal::Square(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (double)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math double number",
        ToolTips = "Returns the sign of a double (1 if positive, -1 if negative)",
        Priority = "high"))
AABDouble Sign(AABDouble target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Round (double)",
        ScriptName = "Round",
        Category = "InlineMath",
        Keywords = "round math double number",
        ToolTips = "Rounds a double to the nearest integer",
        Priority = "high"))
AABDouble Round(AABDouble target) { return AABaseTypesInternal::Round(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "GridSnap (double)",
        ScriptName = "GridSnap",
        Category = "InlineMath",
        Keywords = "grid snap math double number",
        ToolTips = "Snaps a double to a grid with a specified spacing",
        Priority = "high"))
AABDouble GridSnap(AABDouble target, AABDouble GridSize) { return AABaseTypesInternal::GridSnap(target, GridSize); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sin (double)",
        ScriptName = "Sin",
        Category = "InlineMath",
        Keywords = "sine sin math double number",
        ToolTips = "Returns the sine of a double (in radians)",
        Priority = "high"))
AABDouble Sin(AABDouble target) { return AABaseTypesInternal::Sin(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Cos (double)",
        ScriptName = "Cos",
        Category = "InlineMath",
        Keywords = "cosine cos math double number",
        ToolTips = "Returns the cosine of a double (in radians)",
        Priority = "high"))
AABDouble Cos(AABDouble target) { return AABaseTypesInternal::Cos(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Tan (double)",
        ScriptName = "Tan",
        Category = "InlineMath",
        Keywords = "tangent tan math double number",
        ToolTips = "Returns the tangent of a double (in radians)",
        Priority = "high"))
AABDouble Tan(AABDouble target) { return AABaseTypesInternal::Tan(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ASin (double)",
        ScriptName = "ASin",
        Category = "InlineMath",
        Keywords = "inverse sine asin math double number",
        ToolTips = "Returns the inverse sine of a double (in radians)",
        Priority = "high"))
AABDouble ASin(AABDouble target) { return AABaseTypesInternal::ASin(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ACos (double)",
        ScriptName = "ACos",
        Category = "InlineMath",
        Keywords = "inverse cosine acos math double number",
        ToolTips = "Returns the inverse cosine of a double (in radians)",
        Priority = "high"))
AABDouble ACos(AABDouble target) { return AABaseTypesInternal::ACos(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "ATan (double)",
        ScriptName = "ATan",
        Category = "InlineMath",
        Keywords = "inverse tangent atan math double number",
        ToolTips = "Returns the inverse tangent of a double (in radians)",
        Priority = "high"))
AABDouble ATan(AABDouble target) { return AABaseTypesInternal::ATan(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double == double",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison double number",
        ToolTips = "Checks if two double values are equal",
        Priority = "high"))
AABBool Equals(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double != double",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison double number",
        ToolTips = "Checks if two double values are not equal",
        Priority = "high"))
AABBool NotEqual(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double > double",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison double number",
        ToolTips = "Checks if the first double value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double >= double",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison double number",
        ToolTips = "Checks if the first double value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double < double",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison double number",
        ToolTips = "Checks if the first double value is less than the second",
        Priority = "high"))
AABBool LessThan(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "double <= double",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison double number",
        ToolTips = "Checks if the first double value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABDouble lhs, AABDouble rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 + int8",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math int8 integer",
        ToolTips = "Adds two int8 values together",
        Priority = "high"))
AABInt8 Add(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 - int8",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math int8 integer",
        ToolTips = "Subtracts one int8 value from another",
        Priority = "high"))
AABInt8 Subtract(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 * int8",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math int8 integer",
        ToolTips = "Multiplies two int8 values together",
        Priority = "high"))
AABInt8 Multiply(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 / int8",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math int8 integer",
        ToolTips = "Divides one int8 value by another",
        Priority = "high"))
AABInt8 Divide(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|int8|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math int8 integer",
        ToolTips = "Returns the absolute value of an int8 value",
        Priority = "high"))
AABInt8 Abs(AABInt8 target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (int8)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit int8 integer",
        ToolTips = "Clamps an int8 value between a minimum and a maximum value",
        Priority = "high"))
AABInt8 Clamp(AABInt8 target, AABInt8 min, AABInt8 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (int8)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math int8 integer",
        ToolTips = "Returns the maximum value of two int8 values",
        Priority = "high"))
AABInt8 Max(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (int8)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math int8 integer",
        ToolTips = "Returns the minimum value of two int8 values",
        Priority = "high"))
AABInt8 Min(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (int8)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math int8 integer",
        ToolTips = "Returns the sign of an int8 value (1 if positive, -1 if negative)",
        Priority = "high"))
AABInt8 Sign(AABInt8 target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 == int8",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison int8 integer",
        ToolTips = "Checks if two int8 values are equal",
        Priority = "high"))
AABBool Equals(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 != int8",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison int8 integer",
        ToolTips = "Checks if two int8 values are not equal",
        Priority = "high"))
AABBool NotEqual(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 > int8",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison int8 integer",
        ToolTips = "Checks if the first int8 value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 >= int8",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison int8 integer",
        ToolTips = "Checks if the first int8 value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 < int8",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison int8 integer",
        ToolTips = "Checks if the first int8 value is less than the second",
        Priority = "high"))
AABBool LessThan(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int8 <= int8",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison int8 integer",
        ToolTips = "Checks if the first int8 value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABInt8 lhs, AABInt8 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 + int16",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math int16 integer",
        ToolTips = "Adds two int16 values together",
        Priority = "high"))
AABInt16 Add(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 - int16",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math int16 integer",
        ToolTips = "Subtracts one int16 value from another",
        Priority = "high"))
AABInt16 Subtract(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 * int16",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math int16 integer",
        ToolTips = "Multiplies two int16 values together",
        Priority = "high"))
AABInt16 Multiply(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 / int16",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math int16 integer",
        ToolTips = "Divides one int16 value by another",
        Priority = "high"))
AABInt16 Divide(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|int16|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math int16 integer",
        ToolTips = "Returns the absolute value of an int16 value",
        Priority = "high"))
AABInt16 Abs(AABInt16 target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (int16)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit int16 integer",
        ToolTips = "Clamps an int16 value between a minimum and a maximum value",
        Priority = "high"))
AABInt16 Clamp(AABInt16 target, AABInt16 min, AABInt16 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (int16)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math int16 integer",
        ToolTips = "Returns the maximum value of two int16 values",
        Priority = "high"))
AABInt16 Max(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (int16)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math int16 integer",
        ToolTips = "Returns the minimum value of two int16 values",
        Priority = "high"))
AABInt16 Min(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (int16)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math int16 integer",
        ToolTips = "Returns the sign of an int16 value (1 if positive, -1 if negative)",
        Priority = "high"))
AABInt16 Sign(AABInt16 target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 == int16",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison int16 integer",
        ToolTips = "Checks if two int16 values are equal",
        Priority = "high"))
AABBool Equals(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 != int16",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison int16 integer",
        ToolTips = "Checks if two int16 values are not equal",
        Priority = "high"))
AABBool NotEqual(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 > int16",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison int16 integer",
        ToolTips = "Checks if the first int16 value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 >= int16",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison int16 integer",
        ToolTips = "Checks if the first int16 value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 < int16",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison int16 integer",
        ToolTips = "Checks if the first int16 value is less than the second",
        Priority = "high"))
AABBool LessThan(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int16 <= int16",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison int16 integer",
        ToolTips = "Checks if the first int16 value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABInt16 lhs, AABInt16 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 + int32",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math int32 integer",
        ToolTips = "Adds two int32 values together",
        Priority = "high"))
AABInt32 Add(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 - int32",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math int32 integer",
        ToolTips = "Subtracts one int32 value from another",
        Priority = "high"))
AABInt32 Subtract(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 * int32",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math int32 integer",
        ToolTips = "Multiplies two int32 values together",
        Priority = "high"))
AABInt32 Multiply(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 / int32",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math int32 integer",
        ToolTips = "Divides one int32 value by another",
        Priority = "high"))
AABInt32 Divide(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|int32|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math int32 integer",
        ToolTips = "Returns the absolute value of an int32 value",
        Priority = "high"))
AABInt32 Abs(AABInt32 target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (int32)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit int32 integer",
        ToolTips = "Clamps an int32 value between a minimum and a maximum value",
        Priority = "high"))
AABInt32 Clamp(AABInt32 target, AABInt32 min, AABInt32 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (int32)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math int32 integer",
        ToolTips = "Returns the maximum value of two int32 values",
        Priority = "high"))
AABInt32 Max(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (int32)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math int32 integer",
        ToolTips = "Returns the minimum value of two int32 values",
        Priority = "high"))
AABInt32 Min(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (int32)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math int32 integer",
        ToolTips = "Returns the sign of an int32 value (1 if positive, -1 if negative)",
        Priority = "high"))
AABInt32 Sign(AABInt32 target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 == int32",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison int32 integer",
        ToolTips = "Checks if two int32 values are equal",
        Priority = "high"))
AABBool Equals(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 != int32",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison int32 integer",
        ToolTips = "Checks if two int32 values are not equal",
        Priority = "high"))
AABBool NotEqual(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 > int32",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison int32 integer",
        ToolTips = "Checks if the first int32 value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 >= int32",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison int32 integer",
        ToolTips = "Checks if the first int32 value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 < int32",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison int32 integer",
        ToolTips = "Checks if the first int32 value is less than the second",
        Priority = "high"))
AABBool LessThan(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int32 <= int32",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison int32 integer",
        ToolTips = "Checks if the first int32 value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABInt32 lhs, AABInt32 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 + int64",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math int64 integer",
        ToolTips = "Adds two int64 values together",
        Priority = "high"))
AABInt64 Add(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 - int64",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math int64 integer",
        ToolTips = "Subtracts one int64 value from another",
        Priority = "high"))
AABInt64 Subtract(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 * int64",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math int64 integer",
        ToolTips = "Multiplies two int64 values together",
        Priority = "high"))
AABInt64 Multiply(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 / int64",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math int64 integer",
        ToolTips = "Divides one int64 value by another",
        Priority = "high"))
AABInt64 Divide(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "|int64|",
        ScriptName = "Abs",
        Category = "InlineMath",
        Keywords = "absolute value abs math int64 integer",
        ToolTips = "Returns the absolute value of an int64 value",
        Priority = "high"))
AABInt64 Abs(AABInt64 target) { return AABaseTypesInternal::Abs(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (int64)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit int64 integer",
        ToolTips = "Clamps an int64 value between a minimum and a maximum value",
        Priority = "high"))
AABInt64 Clamp(AABInt64 target, AABInt64 min, AABInt64 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (int64)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math int64 integer",
        ToolTips = "Returns the maximum value of two int64 values",
        Priority = "high"))
AABInt64 Max(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (int64)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math int64 integer",
        ToolTips = "Returns the minimum value of two int64 values",
        Priority = "high"))
AABInt64 Min(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Sign (int64)",
        ScriptName = "Sign",
        Category = "InlineMath",
        Keywords = "sign math int64 integer",
        ToolTips = "Returns the sign of an int64 value (1 if positive, -1 if negative)",
        Priority = "high"))
AABInt64 Sign(AABInt64 target) { return AABaseTypesInternal::Sign(target); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 == int64",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison int64 integer",
        ToolTips = "Checks if two int64 values are equal",
        Priority = "high"))
AABBool Equals(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 != int64",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison int64 integer",
        ToolTips = "Checks if two int64 values are not equal",
        Priority = "high"))
AABBool NotEqual(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 > int64",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison int64 integer",
        ToolTips = "Checks if the first int64 value is greater than the second",
        Priority = "high"))
AABBool GreaterThan(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 >= int64",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison int64 integer",
        ToolTips = "Checks if the first int64 value is greater than or equal to the second",
        Priority = "high"))
AABBool GreaterThanOrEqualTo(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 < int64",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison int64 integer",
        ToolTips = "Checks if the first int64 value is less than the second",
        Priority = "high"))
AABBool LessThan(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "int64 <= int64",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison int64 integer",
        ToolTips = "Checks if the first int64 value is less than or equal to the second",
        Priority = "high"))
AABBool LessThanOrEqualTo(AABInt64 lhs, AABInt64 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }


ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 + uint8",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math uint8 unsigned integer",
        ToolTips = "Adds two uint8 values together",
        Priority = "high"))
    AABuInt8 Add(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 - uint8",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math uint8 unsigned integer",
        ToolTips = "Subtracts one uint8 value from another",
        Priority = "high"))
    AABuInt8 Subtract(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 * uint8",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math uint8 unsigned integer",
        ToolTips = "Multiplies two uint8 values together",
        Priority = "high"))
    AABuInt8 Multiply(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 / uint8",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math uint8 unsigned integer",
        ToolTips = "Divides one uint8 value by another",
        Priority = "high"))
    AABuInt8 Divide(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (uint8)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit uint8 unsigned integer",
        ToolTips = "Clamps an uint8 value between a minimum and a maximum value",
        Priority = "high"))
    AABuInt8 Clamp(AABuInt8 target, AABuInt8 min, AABuInt8 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (uint8)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math uint8 unsigned integer",
        ToolTips = "Returns the maximum value of two uint8 values",
        Priority = "high"))
    AABuInt8 Max(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (uint8)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math uint8 unsigned integer",
        ToolTips = "Returns the minimum value of two uint8 values",
        Priority = "high"))
    AABuInt8 Min(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 == uint8",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison uint8 unsigned integer",
        ToolTips = "Checks if two uint8 values are equal",
        Priority = "high"))
    AABBool Equals(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 != uint8",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison uint8 unsigned integer",
        ToolTips = "Checks if two uint8 values are not equal",
        Priority = "high"))
    AABBool NotEqual(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 > uint8",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison uint8 unsigned integer",
        ToolTips = "Checks if the first uint8 value is greater than the second",
        Priority = "high"))
    AABBool GreaterThan(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 >= uint8",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison uint8 unsigned integer",
        ToolTips = "Checks if the first uint8 value is greater than or equal to the second",
        Priority = "high"))
    AABBool GreaterThanOrEqualTo(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 < uint8",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison uint8 unsigned integer",
        ToolTips = "Checks if the first uint8 value is less than the second",
        Priority = "high"))
    AABBool LessThan(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint8 <= uint8",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison uint8 unsigned integer",
        ToolTips = "Checks if the first uint8 value is less than or equal to the second",
        Priority = "high"))
    AABBool LessThanOrEqualTo(AABuInt8 lhs, AABuInt8 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 + uint16",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math uint16 unsigned integer",
        ToolTips = "Adds two uint16 values together",
        Priority = "high"))
    AABuInt16 Add(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 - uint16",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math uint16 unsigned integer",
        ToolTips = "Subtracts one uint16 value from another",
        Priority = "high"))
    AABuInt16 Subtract(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 * uint16",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math uint16 unsigned integer",
        ToolTips = "Multiplies two uint16 values together",
        Priority = "high"))
    AABuInt16 Multiply(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 / uint16",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math uint16 unsigned integer",
        ToolTips = "Divides one uint16 value by another",
        Priority = "high"))
    AABuInt16 Divide(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (uint16)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit uint16 unsigned integer",
        ToolTips = "Clamps an uint16 value between a minimum and a maximum value",
        Priority = "high"))
    AABuInt16 Clamp(AABuInt16 target, AABuInt16 min, AABuInt16 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (uint16)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math uint16 unsigned integer",
        ToolTips = "Returns the maximum value of two uint16 values",
        Priority = "high"))
    AABuInt16 Max(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (uint16)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math uint16 unsigned integer",
        ToolTips = "Returns the minimum value of two uint16 values",
        Priority = "high"))
    AABuInt16 Min(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 == uint16",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison uint16 unsigned integer",
        ToolTips = "Checks if two uint16 values are equal",
        Priority = "high"))
    AABBool Equals(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 != uint16",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison uint16 unsigned integer",
        ToolTips = "Checks if two uint16 values are not equal",
        Priority = "high"))
    AABBool NotEqual(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 > uint16",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison uint16 unsigned integer",
        ToolTips = "Checks if the first uint16 value is greater than the second",
        Priority = "high"))
    AABBool GreaterThan(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 >= uint16",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison uint16 unsigned integer",
        ToolTips = "Checks if the first uint16 value is greater than or equal to the second",
        Priority = "high"))
    AABBool GreaterThanOrEqualTo(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 < uint16",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison uint16 unsigned integer",
        ToolTips = "Checks if the first uint16 value is less than the second",
        Priority = "high"))
    AABBool LessThan(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint16 <= uint16",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison uint16 unsigned integer",
        ToolTips = "Checks if the first uint16 value is less than or equal to the second",
        Priority = "high"))
    AABBool LessThanOrEqualTo(AABuInt16 lhs, AABuInt16 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 + uint32",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math uint32 unsigned integer",
        ToolTips = "Adds two uint32 values together",
        Priority = "high"))
    AABuInt32 Add(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 - uint32",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math uint32 unsigned integer",
        ToolTips = "Subtracts one uint32 value from another",
        Priority = "high"))
    AABuInt32 Subtract(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 * uint32",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math uint32 unsigned integer",
        ToolTips = "Multiplies two uint32 values together",
        Priority = "high"))
    AABuInt32 Multiply(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 / uint32",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math uint32 unsigned integer",
        ToolTips = "Divides one uint32 value by another",
        Priority = "high"))
    AABuInt32 Divide(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (uint32)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit uint32 unsigned integer",
        ToolTips = "Clamps an uint32 value between a minimum and a maximum value",
        Priority = "high"))
    AABuInt32 Clamp(AABuInt32 target, AABuInt32 min, AABuInt32 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (uint32)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math uint32 unsigned integer",
        ToolTips = "Returns the maximum value of two uint32 values",
        Priority = "high"))
    AABuInt32 Max(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (uint32)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math uint32 unsigned integer",
        ToolTips = "Returns the minimum value of two uint32 values",
        Priority = "high"))
    AABuInt32 Min(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 == uint32",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison uint32 unsigned integer",
        ToolTips = "Checks if two uint32 values are equal",
        Priority = "high"))
    AABBool Equals(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 != uint32",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison uint32 unsigned integer",
        ToolTips = "Checks if two uint32 values are not equal",
        Priority = "high"))
    AABBool NotEqual(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 > uint32",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison uint32 unsigned integer",
        ToolTips = "Checks if the first uint32 value is greater than the second",
        Priority = "high"))
    AABBool GreaterThan(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 >= uint32",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison uint32 unsigned integer",
        ToolTips = "Checks if the first uint32 value is greater than or equal to the second",
        Priority = "high"))
    AABBool GreaterThanOrEqualTo(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 < uint32",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison uint32 unsigned integer",
        ToolTips = "Checks if the first uint32 value is less than the second",
        Priority = "high"))
    AABBool LessThan(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint32 <= uint32",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison uint32 unsigned integer",
        ToolTips = "Checks if the first uint32 value is less than or equal to the second",
        Priority = "high"))
    AABBool LessThanOrEqualTo(AABuInt32 lhs, AABuInt32 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 + uint64",
        ScriptName = "Add",
        Category = "InlineMath",
        Keywords = "add + math uint64 unsigned integer",
        ToolTips = "Adds two uint64 values together",
        Priority = "high"))
    AABuInt64 Add(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Add(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 - uint64",
        ScriptName = "Subtract",
        Category = "InlineMath",
        Keywords = "subtract - math uint64 unsigned integer",
        ToolTips = "Subtracts one uint64 value from another",
        Priority = "high"))
    AABuInt64 Subtract(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Subtract(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 * uint64",
        ScriptName = "Multiply",
        Category = "InlineMath",
        Keywords = "multiply * math uint64 unsigned integer",
        ToolTips = "Multiplies two uint64 values together",
        Priority = "high"))
    AABuInt64 Multiply(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Multiply(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 / uint64",
        ScriptName = "Divide",
        Category = "InlineMath",
        Keywords = "divide / math uint64 unsigned integer",
        ToolTips = "Divides one uint64 value by another",
        Priority = "high"))
    AABuInt64 Divide(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Divide(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Clamp (uint64)",
        ScriptName = "Clamp",
        Category = "InlineMath",
        Keywords = "clamp math limit uint64 unsigned integer",
        ToolTips = "Clamps an uint64 value between a minimum and a maximum value",
        Priority = "high"))
    AABuInt64 Clamp(AABuInt64 target, AABuInt64 min, AABuInt64 max) { return AABaseTypesInternal::Clamp(target, min, max); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Max (uint64)",
        ScriptName = "Max",
        Category = "InlineMath",
        Keywords = "max math uint64 unsigned integer",
        ToolTips = "Returns the maximum value of two uint64 values",
        Priority = "high"))
    AABuInt64 Max(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Max(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Min (uint64)",
        ScriptName = "Min",
        Category = "InlineMath",
        Keywords = "min math uint64 unsigned integer",
        ToolTips = "Returns the minimum value of two uint64 values",
        Priority = "high"))
    AABuInt64 Min(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Min(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 == uint64",
        ScriptName = "Equals",
        Category = "InlineMath",
        Keywords = "equals == comparison uint64 unsigned integer",
        ToolTips = "Checks if two uint64 values are equal",
        Priority = "high"))
    AABBool Equals(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::Equals(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 != uint64",
        ScriptName = "NotEqual",
        Category = "InlineMath",
        Keywords = "not equal != comparison uint64 unsigned integer",
        ToolTips = "Checks if two uint64 values are not equal",
        Priority = "high"))
    AABBool NotEqual(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::NotEqual(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 > uint64",
        ScriptName = "GreaterThan",
        Category = "InlineMath",
        Keywords = "greater > comparison uint64 unsigned integer",
        ToolTips = "Checks if the first uint64 value is greater than the second",
        Priority = "high"))
    AABBool GreaterThan(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::GreaterThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 >= uint64",
        ScriptName = "GreaterThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "greater equal >= comparison uint64 unsigned integer",
        ToolTips = "Checks if the first uint64 value is greater than or equal to the second",
        Priority = "high"))
    AABBool GreaterThanOrEqualTo(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::GreaterThanOrEqualTo(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 < uint64",
        ScriptName = "LessThan",
        Category = "InlineMath",
        Keywords = "less < comparison uint64 unsigned integer",
        ToolTips = "Checks if the first uint64 value is less than the second",
        Priority = "high"))
    AABBool LessThan(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::LessThan(lhs, rhs); }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "uint64 <= uint64",
        ScriptName = "LessThanOrEqualTo",
        Category = "InlineMath",
        Keywords = "less equal <= comparison uint64 unsigned integer",
        ToolTips = "Checks if the first uint64 value is less than or equal to the second",
        Priority = "high"))
    AABBool LessThanOrEqualTo(AABuInt64 lhs, AABuInt64 rhs) { return AABaseTypesInternal::LessThanOrEqualTo(lhs, rhs); }



ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Boolean Invert",
        ScriptName = "Invert",
        Category = "InlineMath",
        Keywords = "bool invert ! condition logic",
        ToolTips = "Inverts a boolean value",
        Priority = "high"))
AABBool Invert(AABBool target) { return !target; }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Boolean AND",
        ScriptName = "AND",
        Category = "InlineMath",
        Keywords = "bool and & condition logic",
        ToolTips = "Returns the logical AND of two boolean values.",
        Priority = "high"))
AABBool And(AABBool lhs, AABBool rhs) { return lhs && rhs; }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Boolean OR",
        ScriptName = "OR",
        Category = "InlineMath",
        Keywords = "bool or | condition logic",
        ToolTips = "Returns the logical AND of two boolean values.",
        Priority = "high"))
AABBool Or(AABBool lhs, AABBool rhs) { return lhs || rhs; }
ABSTRACT_SDK_NODE_DEFINITION_INLINE(
    ABS_SDK_PROPERTIES(
        Type = "Evaluation",
        NodeDisplayText = "Boolean XOR",
        ScriptName = "XOR",
        Category = "InlineMath",
        Keywords = "bool xor ^ condition logic",
        ToolTips = "Returns the logical XOR of two boolean values.",
        Priority = "high"))
AABBool XOr(AABBool lhs, AABBool rhs) { return lhs != rhs; }
