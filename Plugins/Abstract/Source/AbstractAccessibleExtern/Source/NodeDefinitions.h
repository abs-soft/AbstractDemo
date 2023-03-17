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

#include "ValueTypeDefinitions.h"

// Syntax:
// ABSTRACT_SDK_NODE_DEFINITION()
// <return_value_type_name> ExampleFunction(
//     <input_value_type_0> <input_param_name_0>,
//     ... ,
//     <input_value_type_n_1> <input_param_name_n_1>);

// Example:
// ABSTRACT_SDK_NODE_DEFINITION() Execution Test(Integer i);

// ABSTRACT_SDK_NODE_DEFINITION() Boolean AbsClassExists(ABSClass absClass);

// ABSTRACT_SDK_NODE_DEFINITION() String StringConcatenate(String lhs, String rhs);
// ABSTRACT_SDK_NODE_DEFINITION() String IntegerToString(Integer value);
// ABSTRACT_SDK_NODE_DEFINITION() String NumberToString(Number value);
// ABSTRACT_SDK_NODE_DEFINITION() String BooleanToString(Boolean value);

// ABSTRACT_SDK_NODE_DEFINITION() Boolean IntegerEquals(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean IntegerGreaterThan(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean IntegerGreaterThanOrEqualTo(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean IntegerLessThan(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean IntegerLessThanOrEqualTo(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Integer IntegerClamp(Integer min, Integer max, Integer input);

// ABSTRACT_SDK_NODE_DEFINITION() Boolean NumberEquals(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean NumberGreaterThan(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean NumberGreaterThanOrEqualTo(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean NumberLessThan(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean NumberLessThanOrEqualTo(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Number NumberClamp(Number min, Number max, Number input);

// ABSTRACT_SDK_NODE_DEFINITION() Boolean BooleanAND(Boolean lhs, Boolean rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean BooleanOR(Boolean lhs, Boolean rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean BooleanXOR(Boolean lhs, Boolean rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Boolean BooleanInvert(Boolean input);

// ABSTRACT_SDK_NODE_DEFINITION() Integer IntegerAdd(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Integer IntegerSubtract(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Integer IntegerMultiply(Integer lhs, Integer rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Integer IntegerDivide(Integer lhs, Integer rhs);

// ABSTRACT_SDK_NODE_DEFINITION() Integer Ceiling(Number input);
// ABSTRACT_SDK_NODE_DEFINITION() Integer Floor(Number input);

// ABSTRACT_SDK_NODE_DEFINITION() Number NumberAdd(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Number NumberSubtract(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Number NumberMultiply(Number lhs, Number rhs);
// ABSTRACT_SDK_NODE_DEFINITION() Number NumberDivide(Number lhs, Number rhs);

// ABSTRACT_SDK_NODE_DEFINITION() Number CastToNumber(Integer input);
