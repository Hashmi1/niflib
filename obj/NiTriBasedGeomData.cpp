/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for licence. */

#include "NiTriBasedGeomData.h"
#include "NiObject.h"

//Definition of TYPE constant
const Type NiTriBasedGeomData::TYPE("NiTriBasedGeomData", &NI_TRI_BASED_GEOM_DATA_PARENT::TYPE );

NiTriBasedGeomData::NiTriBasedGeomData() NI_TRI_BASED_GEOM_DATA_CONSTRUCT {}

NiTriBasedGeomData::~NiTriBasedGeomData() {}

void NiTriBasedGeomData::Read( istream& in, list<uint> & link_stack, unsigned int version ) {
  NI_TRI_BASED_GEOM_DATA_READ
}

void NiTriBasedGeomData::Write( ostream& out, map<NiObjectRef,uint> link_map, unsigned int version ) const {
  NI_TRI_BASED_GEOM_DATA_WRITE
}

string NiTriBasedGeomData::asString( bool verbose ) const {
  NI_TRI_BASED_GEOM_DATA_STRING
}

void NiTriBasedGeomData::FixLinks( const vector<NiObjectRef> & objects, list<uint> & link_stack, unsigned int version ) {
  NI_TRI_BASED_GEOM_DATA_FIXLINKS
}

const Type & NiTriBasedGeomData::GetType() const {
  return TYPE;
};

Vector3 NiTriBasedGeomData::Center() const { return Vector3(); }
float NiTriBasedGeomData::Radius() const { return float(); }