// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef VertexTools_h__
#define VertexTools_h__

#include <boost/preprocessor.hpp>


#define VERTEX_SEQ_TUPLE(seq) BOOST_PP_CAT(VERTEX_SEQ_TUPLE_X seq, 0)
#define VERTEX_SEQ_TUPLE_X(x, y, z) ((x, y, z)) VERTEX_SEQ_TUPLE_Y
#define VERTEX_SEQ_TUPLE_Y(x, y, z) ((x, y, z)) VERTEX_SEQ_TUPLE_Z
#define VERTEX_SEQ_TUPLE_Z(x, y, z) ((x, y, z)) VERTEX_SEQ_TUPLE_X
#define VERTEX_SEQ_TUPLE_X0
#define VERTEX_SEQ_TUPLE_Y0
#define VERTEX_SEQ_TUPLE_Z0

#define VERTEX_DECL_VERTEX(r, data, elem) \
    BOOST_PP_TUPLE_ELEM(3, 0, elem) BOOST_PP_TUPLE_ELEM(3, 1, elem);

#define VERTEX_SEQ_MEMBER(x, y) x::y

#define VERTEX_DECL_VERTEX_ATTRIBUTE(r, data, elem) \
Attribute \
{ \
  BOOST_PP_TUPLE_ELEM(3, 2, elem), \
  sizeof(VERTEX_SEQ_MEMBER(data, BOOST_PP_TUPLE_ELEM(3, 1, elem))), \
  offsetof(data, BOOST_PP_TUPLE_ELEM(3, 1, elem)) \
},


#define VERTEX(val) \
\
struct BOOST_PP_SEQ_HEAD(val)\
{\
  BOOST_PP_SEQ_FOR_EACH(VERTEX_DECL_VERTEX, ~, VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))\
  static const std::array<Attribute, BOOST_PP_SEQ_SIZE(VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))> mAttributeInfo;\
};\
\
const std::array<Attribute, BOOST_PP_SEQ_SIZE(VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))> \
  BOOST_PP_SEQ_HEAD(val)::mAttributeInfo = \
{ \
  BOOST_PP_SEQ_FOR_EACH(VERTEX_DECL_VERTEX_ATTRIBUTE, BOOST_PP_SEQ_HEAD(val), VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val))) \
};

// #undef VERTEX_DECL_VERTEX_ATTRIBUTE
// #undef VERTEX_SEQ_MEMBER
// #undef VERTEX_DECL_VERTEX
// #undef VERTEX_SEQ_TUPLE_Z
// #undef VERTEX_SEQ_TUPLE_Y
// #undef VERTEX_SEQ_TUPLE_X
// #undef VERTEX_SEQ_TUPLE


#endif // VertexTools_h__

