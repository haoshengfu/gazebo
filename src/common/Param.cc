/*
 * Copyright 2011 Nate Koenig & Andrew Howard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/* Desc: Parameter class
 * Author: Nate Koenig
 * Date: 14 Aug 2008
 */

#include "common/XMLConfig.hh"
#include "common/Exception.hh"
#include "common/Param.hh"
#include "math/Quaternion.hh"
#include "math/Pose.hh"
#include "math/Vector3.hh"
#include "math/Vector4.hh"

using namespace gazebo;
using namespace common;


std::vector<Param*> *Param::params = NULL;

////////////////////////////////////////////////////////////////////////////////
// Constructor
Param::Param(Param *newParam) 
{
  if (params == NULL)
    gzthrow("Param vector is NULL\n");
  params->push_back(newParam);
}

////////////////////////////////////////////////////////////////////////////////
// Destructor
Param::~Param() 
{
}

////////////////////////////////////////////////////////////////////////////////
//  Begin a block of "new ParamT<>"
void Param::Begin(std::vector<Param*> *_params)
{
  if (params != NULL)
    gzthrow("Calling Begin before an End\n");
  params = _params;
}

////////////////////////////////////////////////////////////////////////////////
//  End a block of "new ParamT<>"
void Param::End()
{
  if (params == NULL)
    gzthrow("Calling End before a Begin\n");

  params = NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// The name of the key
std::string Param::GetKey() const
{
  return this->key;
}

////////////////////////////////////////////////////////////////////////////////
/// Get the name of the param's data type
std::string Param::GetTypename() const
{
  return this->typeName;
}

bool Param::IsBool() const
{
  return this->GetTypename() == typeid(bool).name();
}

bool Param::IsInt() const
{
  return this->GetTypename() == typeid(int).name();
}

bool Param::IsUInt() const
{
  return this->GetTypename() == typeid(unsigned int).name();
}

bool Param::IsFloat() const
{
  return this->GetTypename() == typeid(float).name();
}

bool Param::IsDouble() const
{
  return this->GetTypename() == typeid(double).name();
}

bool Param::IsChar() const
{
  return this->GetTypename() == typeid(char).name();
}

bool Param::IsStr() const
{
  return this->GetTypename() == typeid(std::string).name();
}

bool Param::IsVector3() const
{
  return this->GetTypename() == typeid(math::Vector3).name();
}
bool Param::IsVector4() const
{
  return this->GetTypename() == typeid(math::Vector4).name();
}
bool Param::IsQuatern() const
{
  return this->GetTypename() == typeid(math::Quaternion).name();
}
bool Param::IsPose() const
{
  return this->GetTypename() == typeid(math::Pose).name();
}

//////////////////////////////////////////////////////////////////////////////
/// Load the param from an XML config file
void Param::Load(XMLConfigNode *node)
{
  std::ostringstream stream;
  stream << this->GetDefaultAsString();

  std::string input;
  if (node)
    input = node->GetString(this->GetKey(), stream.str(), this->required);
  else
    input = stream.str();

  this->SetFromString( input );
}

