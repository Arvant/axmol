/****************************************************************************
Copyright (c) 2007      Scott Lembcke
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axis-project.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

/**
 @file
 based on Chipmunk cpArray.
 ccArray is a faster alternative to NSMutableArray, it does pretty much the
 same thing (stores NSObjects and retains/releases them appropriately). It's
 faster because:
 - it uses a plain C interface so it doesn't incur Objective-c messaging overhead
 - it assumes you know what you're doing, so it doesn't spend time on safety checks
 (index out of bounds, required capacity etc.)
 - comparisons are done using pointer equality instead of isEqual

 There are 2 kind of functions:
 - ccArray functions that manipulates objective-c objects (retain and release are performed)
 - ccCArray functions that manipulates values like if they were standard C structures (no retain/release is performed)
 */

#ifndef AX_ARRAY_H
#define AX_ARRAY_H
/// @cond DO_NOT_SHOW

#include "base/ccMacros.h"
#include "base/CCRef.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

NS_AX_BEGIN

// Easy integration
#define CCARRAYDATA_FOREACH(__array__, __object__) \
    __object__ = __array__->arr[0];                \
    for (ssize_t i = 0, num = __array__->num; i < num; i++, __object__ = __array__->arr[i])

typedef struct _ccArray
{
    ssize_t num, max;
    Ref** arr;
} ccArray;

/** Allocates and initializes a new array with specified capacity */
AX_DLL ccArray* ccArrayNew(ssize_t capacity);

/** Frees array after removing all remaining objects. Silently ignores nil arr. */
AX_DLL void ccArrayFree(ccArray*& arr);

/** Doubles array capacity */
AX_DLL void ccArrayDoubleCapacity(ccArray* arr);

/** Increases array capacity such that max >= num + extra. */
AX_DLL void ccArrayEnsureExtraCapacity(ccArray* arr, ssize_t extra);

/** shrinks the array so the memory footprint corresponds with the number of items */
AX_DLL void ccArrayShrink(ccArray* arr);

/** Returns index of first occurrence of object, NSNotFound if object not found. */
AX_DLL ssize_t ccArrayGetIndexOfObject(ccArray* arr, Ref* object);

/** Returns a Boolean value that indicates whether object is present in array. */
AX_DLL bool ccArrayContainsObject(ccArray* arr, Ref* object);

/** Appends an object. Behavior undefined if array doesn't have enough capacity. */
AX_DLL void ccArrayAppendObject(ccArray* arr, Ref* object);

/** Appends an object. Capacity of arr is increased if needed. */
AX_DLL void ccArrayAppendObjectWithResize(ccArray* arr, Ref* object);

/** Appends objects from plusArr to arr.
 Behavior undefined if arr doesn't have enough capacity. */
AX_DLL void ccArrayAppendArray(ccArray* arr, ccArray* plusArr);

/** Appends objects from plusArr to arr. Capacity of arr is increased if needed. */
AX_DLL void ccArrayAppendArrayWithResize(ccArray* arr, ccArray* plusArr);

/** Inserts an object at index */
AX_DLL void ccArrayInsertObjectAtIndex(ccArray* arr, Ref* object, ssize_t index);

/** Swaps two objects */
AX_DLL void ccArraySwapObjectsAtIndexes(ccArray* arr, ssize_t index1, ssize_t index2);

/** Removes all objects from arr */
AX_DLL void ccArrayRemoveAllObjects(ccArray* arr);

/** Removes object at specified index and pushes back all subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
AX_DLL void ccArrayRemoveObjectAtIndex(ccArray* arr, ssize_t index, bool releaseObj = true);

/** Removes object at specified index and fills the gap with the last object,
 thereby avoiding the need to push back subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
AX_DLL void ccArrayFastRemoveObjectAtIndex(ccArray* arr, ssize_t index);

AX_DLL void ccArrayFastRemoveObject(ccArray* arr, Ref* object);

/** Searches for the first occurrence of object and removes it. If object is not
 found the function has no effect. */
AX_DLL void ccArrayRemoveObject(ccArray* arr, Ref* object, bool releaseObj = true);

/** Removes from arr all objects in minusArr. For each object in minusArr, the
 first matching instance in arr will be removed. */
AX_DLL void ccArrayRemoveArray(ccArray* arr, ccArray* minusArr);

/** Removes from arr all objects in minusArr. For each object in minusArr, all
 matching instances in arr will be removed. */
AX_DLL void ccArrayFullRemoveArray(ccArray* arr, ccArray* minusArr);

//
// // ccCArray for Values (c structures)

typedef struct _ccCArray
{
    ssize_t num, max;
    void** arr;
} ccCArray;

/** Allocates and initializes a new C array with specified capacity */
AX_DLL ccCArray* ccCArrayNew(ssize_t capacity);

/** Frees C array after removing all remaining values. Silently ignores nil arr. */
AX_DLL void ccCArrayFree(ccCArray* arr);

/** Doubles C array capacity */
AX_DLL void ccCArrayDoubleCapacity(ccCArray* arr);

/** Increases array capacity such that max >= num + extra. */
AX_DLL void ccCArrayEnsureExtraCapacity(ccCArray* arr, ssize_t extra);

/** Returns index of first occurrence of value, NSNotFound if value not found. */
AX_DLL ssize_t ccCArrayGetIndexOfValue(ccCArray* arr, void* value);

/** Returns a Boolean value that indicates whether value is present in the C array. */
AX_DLL bool ccCArrayContainsValue(ccCArray* arr, void* value);

/** Inserts a value at a certain position. Behavior undefined if array doesn't have enough capacity */
AX_DLL void ccCArrayInsertValueAtIndex(ccCArray* arr, void* value, ssize_t index);

/** Appends an value. Behavior undefined if array doesn't have enough capacity. */
AX_DLL void ccCArrayAppendValue(ccCArray* arr, void* value);

/** Appends an value. Capacity of arr is increased if needed. */
AX_DLL void ccCArrayAppendValueWithResize(ccCArray* arr, void* value);

/** Appends values from plusArr to arr. Behavior undefined if arr doesn't have
 enough capacity. */
AX_DLL void ccCArrayAppendArray(ccCArray* arr, ccCArray* plusArr);

/** Appends values from plusArr to arr. Capacity of arr is increased if needed. */
AX_DLL void ccCArrayAppendArrayWithResize(ccCArray* arr, ccCArray* plusArr);

/** Removes all values from arr */
AX_DLL void ccCArrayRemoveAllValues(ccCArray* arr);

/** Removes value at specified index and pushes back all subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
AX_DLL void ccCArrayRemoveValueAtIndex(ccCArray* arr, ssize_t index);

/** Removes value at specified index and fills the gap with the last value,
 thereby avoiding the need to push back subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
AX_DLL void ccCArrayFastRemoveValueAtIndex(ccCArray* arr, ssize_t index);

/** Searches for the first occurrence of value and removes it. If value is not found the function has no effect.
 @since v0.99.4
 */
AX_DLL void ccCArrayRemoveValue(ccCArray* arr, void* value);

/** Removes from arr all values in minusArr. For each Value in minusArr, the first matching instance in arr will be
 removed.
 @since v0.99.4
 */
AX_DLL void ccCArrayRemoveArray(ccCArray* arr, ccCArray* minusArr);

/** Removes from arr all values in minusArr. For each value in minusArr, all matching instances in arr will be removed.
 @since v0.99.4
 */
AX_DLL void ccCArrayFullRemoveArray(ccCArray* arr, ccCArray* minusArr);

NS_AX_END

/// @endcond
#endif  // AX_ARRAY_H
