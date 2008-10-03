/*
    Ypsilon Scheme System
    Copyright (c) 2004-2008 Y.FUJITA / LittleWing Company Limited.
    See license.txt for terms and conditions of use
*/

#ifndef OBJECT_FACTORY_H_INCLUDED
#define OBJECT_FACTORY_H_INCLUDED

#include "core.h"
#include "object.h"

#define INTERNAL_PRIVATE_THRESHOLD      (OBJECT_SLAB_THRESHOLD / 2)

#define VERIFY_DATUM(x)     do { assert(!CELLP(x) || heap->is_collectible(x)); } while(0)

scm_symbol_t        make_symbol(object_heap_t* heap, const char* name);
scm_symbol_t        make_symbol(object_heap_t* heap, const char* name, int len);
scm_symbol_t        make_symbol_inherent(object_heap_t* heap, const char* name, int code);
scm_string_t        make_string(object_heap_t* heap, const char* name);
scm_string_t        make_string(object_heap_t* heap, const char* name, int len);
scm_string_t        make_string_literal(object_heap_t* heap, const char* name);
scm_string_t        make_string_literal(object_heap_t* heap, const char* name, int len);
scm_string_t        make_string(object_heap_t* heap, int n,char c);
scm_vector_t        make_vector(object_heap_t* heap, scm_obj_t lst);
scm_vector_t        make_vector(object_heap_t* heap, int n, scm_obj_t obj);
scm_bvector_t       make_bvector(object_heap_t* heap, int n);
scm_bvector_t       make_bvector_mapping(object_heap_t* heap, void* p, int n);
scm_values_t        make_values(object_heap_t* heap, int n);
scm_cont_t          make_cont(object_heap_t* heap, scm_obj_t rec, void* cont);
scm_hashtable_t     make_hashtable(object_heap_t* heap, int type, int n);
scm_hashtable_t     make_generic_hashtable(object_heap_t* heap, scm_vector_t handlers);
scm_environment_t   make_environment(object_heap_t* heap, const char* name);
scm_subr_t          make_subr(object_heap_t* heap, subr_proc_t adrs, scm_obj_t doc);
scm_closure_t       make_closure(object_heap_t* heap, int nargs, int rest, void* env, scm_obj_t code, scm_obj_t doc);
scm_closure_t       make_closure(object_heap_t* heap, scm_closure_t tmpl, void* env);
scm_flonum_t        make_flonum(object_heap_t* heap, double num);
scm_bignum_t        make_bignum(object_heap_t* heap, int n);
scm_bignum_t        make_bignum(object_heap_t* heap, scm_bignum_t bn);
scm_complex_t       make_complex(object_heap_t* heap, double real, double imag);
scm_complex_t       make_complex(object_heap_t* heap, scm_obj_t real, scm_obj_t imag);
scm_rational_t      make_rational(object_heap_t* heap, scm_obj_t numerator, scm_obj_t denominator);
scm_gloc_t          make_gloc(object_heap_t* heap, scm_environment_t environment, scm_symbol_t symbol);
scm_tuple_t         make_tuple(object_heap_t* heap, int n, scm_obj_t obj);
scm_weakmapping_t   make_weakmapping(object_heap_t* heap, scm_obj_t key, scm_obj_t value);
scm_weakhashtable_t make_weakhashtable(object_heap_t* heap, int n);
scm_obj_t           make_list(object_heap_t* heap, int len, ...);
scm_port_t          make_std_port(object_heap_t* heap, fd_t fd, scm_obj_t name, int direction, int file_options, int buffer_mode, scm_obj_t transcoder);
scm_port_t          make_file_port(object_heap_t* heap, scm_obj_t name, int direction, int file_options, int buffer_mode, scm_obj_t transcoder);
scm_port_t          make_bytevector_port(object_heap_t* heap, scm_obj_t name, int direction, scm_obj_t bytes, scm_obj_t transcoder);
scm_port_t          make_custom_port(object_heap_t* heap, scm_obj_t name, int direction, scm_obj_t handlers, scm_obj_t transcoder);
scm_port_t          make_transcoded_port(object_heap_t* heap, scm_obj_t name, scm_port_t port, scm_bvector_t transcoder);
scm_port_t          make_temp_file_port(object_heap_t* heap, scm_obj_t name, int buffer_mode, scm_obj_t transcoder);

void    rehash_hashtable(object_heap_t* heap, scm_hashtable_t ht, int n);
void    rehash_weakhashtable(object_heap_t* heap, scm_weakhashtable_t ht, int n);
void    inplace_rehash_hashtable(object_heap_t* heap, scm_hashtable_t ht);
void    inplace_rehash_weakhashtable(object_heap_t* heap, scm_weakhashtable_t ht);
void    clear_hashtable(object_heap_t* heap, scm_hashtable_t ht, int n);
void    clear_weakhashtable(object_heap_t* heap, scm_weakhashtable_t ht, int n);
void    clear_volatile_hashtable(scm_hashtable_t ht);
void    clear_volatile_weakhashtable(scm_weakhashtable_t ht);
void*   new_heapenv_rec(object_heap_t* heap, size_t size);
void*   new_heapcont_rec(object_heap_t* heap, size_t size);
void    finalize(object_heap_t* heap, void* obj);

scm_hashtable_t     copy_hashtable(object_heap_t* heap, scm_hashtable_t ht, bool immutable);
scm_weakhashtable_t copy_weakhashtable(object_heap_t* heap, scm_weakhashtable_t ht, bool immutable);

inline void*
new_heapenv_rec(object_heap_t* heap, size_t size)
{
    scm_hdr_t* hdr = (scm_hdr_t*)heap->allocate_collectible(sizeof(scm_hdr_t) + size);
    *hdr = scm_hdr_heapenv | (size << HDR_HEAPENV_SIZE_SHIFT);
    return hdr + 1;
}

inline void*
new_heapcont_rec(object_heap_t* heap, size_t size)
{
    scm_hdr_t* hdr = (scm_hdr_t*)heap->allocate_collectible(sizeof(scm_hdr_t) + size);
    *hdr = scm_hdr_heapcont | (size << HDR_HEAPCONT_SIZE_SHIFT);
    return hdr + 1;
}

inline scm_pair_t
make_pair(object_heap_t* heap, scm_obj_t car, scm_obj_t cdr)
{
    VERIFY_DATUM(car);
    VERIFY_DATUM(cdr);
    scm_pair_t obj = (scm_pair_t)heap->allocate_cons();
    CAR(obj) = car;
    CDR(obj) = cdr;
    return obj;
}

#endif