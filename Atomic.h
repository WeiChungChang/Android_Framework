/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_UTILS_ATOMIC_H
#define ANDROID_UTILS_ATOMIC_H

#include "AndroidConfig.h"


#define __ATOMIC_INLINE__ static __inline__ __attribute__((always_inline))


__ATOMIC_INLINE__ int
__atomic_cmpxchg(int old_value, int new_value, volatile int* ptr)
{
    /* We must return 0 on success */
    return __sync_val_compare_and_swap(ptr, old_value, new_value) != old_value;
}

__ATOMIC_INLINE__ int
__atomic_swap(int new_value, volatile int *ptr)
{
    int old_value;
    do {
        old_value = *ptr;
    } while (__sync_val_compare_and_swap(ptr, old_value, new_value) != old_value);
    return old_value;
}

__ATOMIC_INLINE__ int
__atomic_dec(volatile int *ptr)
{
  return __sync_fetch_and_sub (ptr, 1);
}

__ATOMIC_INLINE__ int
__atomic_inc(volatile int *ptr)
{
  return __sync_fetch_and_add (ptr, 1);
}

__ATOMIC_INLINE__ int
__atomic_add(int theMask, volatile int *theValue)
{
  return __sync_fetch_and_add (theValue, theMask);
}

__ATOMIC_INLINE__ int
__atomic_or(int theMask, volatile int *theValue)
{
  return __sync_fetch_and_or (theValue, theMask);
}


#ifdef HAVE_IOS_OS
#include <libkern/OSAtomic.h>
#define android_atomic_inc(a) (OSAtomicIncrement32((int32_t*)(a)) - 1)
#define android_atomic_dec(a) (OSAtomicDecrement32((int32_t*)(a)) + 1)
#define android_atomic_add(a, b) (OSAtomicAdd32((a), (int32_t*)(b)) - (a))
#define android_atomic_and(a, b) OSAtomicAnd32((a), (int32_t*)(b))
#define android_atomic_or(a, b) OSAtomicOr32((a), (uint32_t*)(b))
//OSAtomic return the new value, android needs old value, .. not simple for or/and
//FIXME don't use the return value of or/and
#define android_atomic_cmpxchg(a, b, c) !OSAtomicCompareAndSwap32((a), (b), (c))
#else
//#include <cutils/atomic.h>
//#include <sys/atomics.h>
//#include <stdatomic.h>
#include <atomic>

#define android_atomic_inc(a) __atomic_inc(a)
#define android_atomic_dec(a) __atomic_dec(a)
#define android_atomic_add(a, b) __atomic_add((a), (b))
#define android_atomic_or(a, b) __atomic_or((a), (b))
#define android_atomic_cmpxchg(a, b, c) __atomic_cmpxchg((a), (b), (c))
#endif

template <typename T>
void unusedValue(const T&) {}

#endif // ANDROID_UTILS_ATOMIC_H
