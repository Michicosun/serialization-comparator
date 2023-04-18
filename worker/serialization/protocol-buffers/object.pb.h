// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: object.proto

#ifndef PROTOBUF_INCLUDED_object_2eproto
#define PROTOBUF_INCLUDED_object_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_object_2eproto 

namespace protobuf_object_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_object_2eproto
namespace protobuf_serialization {
class Object;
class ObjectDefaultTypeInternal;
extern ObjectDefaultTypeInternal _Object_default_instance_;
class Object_MapEntry_DoNotUse;
class Object_MapEntry_DoNotUseDefaultTypeInternal;
extern Object_MapEntry_DoNotUseDefaultTypeInternal _Object_MapEntry_DoNotUse_default_instance_;
}  // namespace protobuf_serialization
namespace google {
namespace protobuf {
template<> ::protobuf_serialization::Object* Arena::CreateMaybeMessage<::protobuf_serialization::Object>(Arena*);
template<> ::protobuf_serialization::Object_MapEntry_DoNotUse* Arena::CreateMaybeMessage<::protobuf_serialization::Object_MapEntry_DoNotUse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace protobuf_serialization {

// ===================================================================

class Object_MapEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<Object_MapEntry_DoNotUse, 
    ::std::string, ::google::protobuf::uint64,
    ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT64,
    0 > {
public:
  typedef ::google::protobuf::internal::MapEntry<Object_MapEntry_DoNotUse, 
    ::std::string, ::google::protobuf::uint64,
    ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT64,
    0 > SuperType;
  Object_MapEntry_DoNotUse();
  Object_MapEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const Object_MapEntry_DoNotUse& other);
  static const Object_MapEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const Object_MapEntry_DoNotUse*>(&_Object_MapEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) final;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class Object : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf_serialization.Object) */ {
 public:
  Object();
  virtual ~Object();

  Object(const Object& from);

  inline Object& operator=(const Object& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Object(Object&& from) noexcept
    : Object() {
    *this = ::std::move(from);
  }

  inline Object& operator=(Object&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Object& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Object* internal_default_instance() {
    return reinterpret_cast<const Object*>(
               &_Object_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Object* other);
  friend void swap(Object& a, Object& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Object* New() const final {
    return CreateMaybeMessage<Object>(NULL);
  }

  Object* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Object>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Object& from);
  void MergeFrom(const Object& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Object* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  // repeated uint64 array = 2;
  int array_size() const;
  void clear_array();
  static const int kArrayFieldNumber = 2;
  ::google::protobuf::uint64 array(int index) const;
  void set_array(int index, ::google::protobuf::uint64 value);
  void add_array(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      array() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_array();

  // map<string, uint64> map = 3;
  int map_size() const;
  void clear_map();
  static const int kMapFieldNumber = 3;
  const ::google::protobuf::Map< ::std::string, ::google::protobuf::uint64 >&
      map() const;
  ::google::protobuf::Map< ::std::string, ::google::protobuf::uint64 >*
      mutable_map();

  // string str = 1;
  void clear_str();
  static const int kStrFieldNumber = 1;
  const ::std::string& str() const;
  void set_str(const ::std::string& value);
  #if LANG_CXX11
  void set_str(::std::string&& value);
  #endif
  void set_str(const char* value);
  void set_str(const char* value, size_t size);
  ::std::string* mutable_str();
  ::std::string* release_str();
  void set_allocated_str(::std::string* str);

  // uint64 number = 4;
  void clear_number();
  static const int kNumberFieldNumber = 4;
  ::google::protobuf::uint64 number() const;
  void set_number(::google::protobuf::uint64 value);

  // double floating_number = 5;
  void clear_floating_number();
  static const int kFloatingNumberFieldNumber = 5;
  double floating_number() const;
  void set_floating_number(double value);

  // bool boolean = 6;
  void clear_boolean();
  static const int kBooleanFieldNumber = 6;
  bool boolean() const;
  void set_boolean(bool value);

  // @@protoc_insertion_point(class_scope:protobuf_serialization.Object)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > array_;
  mutable int _array_cached_byte_size_;
  ::google::protobuf::internal::MapField<
      Object_MapEntry_DoNotUse,
      ::std::string, ::google::protobuf::uint64,
      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
      ::google::protobuf::internal::WireFormatLite::TYPE_UINT64,
      0 > map_;
  ::google::protobuf::internal::ArenaStringPtr str_;
  ::google::protobuf::uint64 number_;
  double floating_number_;
  bool boolean_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_object_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Object

// string str = 1;
inline void Object::clear_str() {
  str_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Object::str() const {
  // @@protoc_insertion_point(field_get:protobuf_serialization.Object.str)
  return str_.GetNoArena();
}
inline void Object::set_str(const ::std::string& value) {
  
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:protobuf_serialization.Object.str)
}
#if LANG_CXX11
inline void Object::set_str(::std::string&& value) {
  
  str_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:protobuf_serialization.Object.str)
}
#endif
inline void Object::set_str(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:protobuf_serialization.Object.str)
}
inline void Object::set_str(const char* value, size_t size) {
  
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:protobuf_serialization.Object.str)
}
inline ::std::string* Object::mutable_str() {
  
  // @@protoc_insertion_point(field_mutable:protobuf_serialization.Object.str)
  return str_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Object::release_str() {
  // @@protoc_insertion_point(field_release:protobuf_serialization.Object.str)
  
  return str_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Object::set_allocated_str(::std::string* str) {
  if (str != NULL) {
    
  } else {
    
  }
  str_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), str);
  // @@protoc_insertion_point(field_set_allocated:protobuf_serialization.Object.str)
}

// repeated uint64 array = 2;
inline int Object::array_size() const {
  return array_.size();
}
inline void Object::clear_array() {
  array_.Clear();
}
inline ::google::protobuf::uint64 Object::array(int index) const {
  // @@protoc_insertion_point(field_get:protobuf_serialization.Object.array)
  return array_.Get(index);
}
inline void Object::set_array(int index, ::google::protobuf::uint64 value) {
  array_.Set(index, value);
  // @@protoc_insertion_point(field_set:protobuf_serialization.Object.array)
}
inline void Object::add_array(::google::protobuf::uint64 value) {
  array_.Add(value);
  // @@protoc_insertion_point(field_add:protobuf_serialization.Object.array)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
Object::array() const {
  // @@protoc_insertion_point(field_list:protobuf_serialization.Object.array)
  return array_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
Object::mutable_array() {
  // @@protoc_insertion_point(field_mutable_list:protobuf_serialization.Object.array)
  return &array_;
}

// map<string, uint64> map = 3;
inline int Object::map_size() const {
  return map_.size();
}
inline void Object::clear_map() {
  map_.Clear();
}
inline const ::google::protobuf::Map< ::std::string, ::google::protobuf::uint64 >&
Object::map() const {
  // @@protoc_insertion_point(field_map:protobuf_serialization.Object.map)
  return map_.GetMap();
}
inline ::google::protobuf::Map< ::std::string, ::google::protobuf::uint64 >*
Object::mutable_map() {
  // @@protoc_insertion_point(field_mutable_map:protobuf_serialization.Object.map)
  return map_.MutableMap();
}

// uint64 number = 4;
inline void Object::clear_number() {
  number_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Object::number() const {
  // @@protoc_insertion_point(field_get:protobuf_serialization.Object.number)
  return number_;
}
inline void Object::set_number(::google::protobuf::uint64 value) {
  
  number_ = value;
  // @@protoc_insertion_point(field_set:protobuf_serialization.Object.number)
}

// double floating_number = 5;
inline void Object::clear_floating_number() {
  floating_number_ = 0;
}
inline double Object::floating_number() const {
  // @@protoc_insertion_point(field_get:protobuf_serialization.Object.floating_number)
  return floating_number_;
}
inline void Object::set_floating_number(double value) {
  
  floating_number_ = value;
  // @@protoc_insertion_point(field_set:protobuf_serialization.Object.floating_number)
}

// bool boolean = 6;
inline void Object::clear_boolean() {
  boolean_ = false;
}
inline bool Object::boolean() const {
  // @@protoc_insertion_point(field_get:protobuf_serialization.Object.boolean)
  return boolean_;
}
inline void Object::set_boolean(bool value) {
  
  boolean_ = value;
  // @@protoc_insertion_point(field_set:protobuf_serialization.Object.boolean)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_serialization

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_object_2eproto