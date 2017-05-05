#include "jsonloader.h"

#include <string>
#include <fstream>
#include <iostream>

#include "noisepack.h"
#include "noise/module/module.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

using namespace noise;
using namespace module;
using namespace std;
using namespace rapidjson;

class JSonLoader
{
  private:
    string m_json;
    //string m_jsonString;
    Document m_doc;
    bool m_haveError;
    bool m_verbose;
    NoisePack *m_pack;

    void parseJson();
    Module *formAndCollect(const Value &value);
    Module *formOneNoise(const Value &value);
    //Generators
    Module *createBillow(const Value &value);
    Module *createCheckboard(const Value &value);
    Module *createConst(const Value &value);
    Module *createCylinders(const Value &value);
    Module *createPerlin(const Value &value);
    Module *createRidgedMulti(const Value &value);
    Module *createSpheres(const Value &value);
    Module *createVoronoi(const Value &value);
    //Modifiers
    Module *createAbs(const Value &value);
    Module *createClamp(const Value &value);
    Module *createCurve(const Value &value);
    Module *createExponent(const Value &value);
    Module *createInvert(const Value &value);
    Module *createScaleBias(const Value &value);
    Module *createTerrace(const Value &value);
    //Combiner
    Module *createAdd(const Value &value);
    Module *createMax(const Value &value);
    Module *createMin(const Value &value);
    Module *createMultiply(const Value &value);
    Module *createPower(const Value &value);
    //Selector
    Module *createBlend(const Value &value);
    Module *createSelect(const Value &value);
    //Transformer
    Module *createDisplace(const Value &value);
    Module *createRotatePoint(const Value &value);
    Module *createScalePoint(const Value &value);
    Module *createTranslatePoint(const Value &value);
    Module *createTurbulence(const Value &value);

    bool fillSources(Module *module, const Value &value, const size_t &count);

    bool getBool(const Value &value, const string &name, const bool &def);
    double getDouble(const Value &value, const string &name, const double &def);
    string getString(const Value &value, const string &name, const string &def);
    Value::ConstArray getArray(const Value &value, const string &name);
    NoiseQuality getQuality(const Value &value, const string &name, const NoiseQuality &def);
  public:
    JSonLoader(const string &json);
    NoisePack *get();
};

NoisePack *loadModule(const char *filename)
{
  if (!filename) return std::nullptr_t();
  ifstream in(filename);
  string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
  if (content.empty())
  {
    cout << "File is empty." << endl;
    return std::nullptr_t();
  }

  JSonLoader reader(content);

  return reader.get();
}

NoisePack *createModule(const char *json)
{
  if (!json) return std::nullptr_t();
  JSonLoader reader(json);

  return reader.get();
}

void JSonLoader::parseJson()
{
  const ParseResult ok = m_doc.Parse<0>(m_json.c_str());

  if (!ok)
  {
    cout << "Json parse error: " << GetParseError_En(ok.Code()) << " (" << ok.Offset() << ")" << endl;
    m_haveError = true;
    return;
  }
  if (!m_doc.IsObject())
  {
    cout << "Json document not object" << endl;
    m_haveError = true;
    return;
  }
}

Module *JSonLoader::formAndCollect(const Value &value)
{
  Module *module = formOneNoise(value);
  m_pack->modules.push_back(module);
  return module;
}

Module *JSonLoader::formOneNoise(const Value &value)
{
  const string type = getString(value, "type", "");

  if (type.empty()) return nullptr_t();

  //Generators
  if (type == "billow") return createBillow(value);
  if (type == "checkboard") return createCheckboard(value);
  if (type == "const") return createConst(value);
  if (type == "cylinders") return createCylinders(value);
  if (type == "perlin") return createPerlin(value);
  if (type == "ridgedmulti") return createRidgedMulti(value);
  if (type == "spheres") return createSpheres(value);
  if (type == "voronoi") return createVoronoi(value);
  //Modifiers
  if (type == "abs") return createAbs(value);
  if (type == "clamp") return createClamp(value);
  if (type == "curve") return createCurve(value);
  if (type == "exponent") return createExponent(value);
  if (type == "invert") return createInvert(value);
  if (type == "scalebias") return createScaleBias(value);
  if (type == "terrace") return createTerrace(value);
  //Combiner
  if (type == "add") return createAdd(value);
  if (type == "max") return createMax(value);
  if (type == "min") return createMin(value);
  if (type == "multiply") return createMultiply(value);
  if (type == "power") return createPower(value);
  //Selector
  if (type == "blend") return createBlend(value);
  if (type == "select") return createSelect(value);
  //Transformer
  if (type == "displace") return createDisplace(value);
  if (type == "rotatepoint") return createRotatePoint(value);
  if (type == "scalepoint") return createScalePoint(value);
  if (type == "translatepoint") return createTranslatePoint(value);
  if (type == "turbulence") return createTurbulence(value);

  cout << "Unknown type:" << type << endl;

  return nullptr_t();
}

Module *JSonLoader::createBillow(const Value &value)
{
  Billow *billow = new Billow();

  billow->SetFrequency(getDouble(value, "frequency", billow->GetFrequency()));
  billow->SetLacunarity(getDouble(value, "lacunarity", billow->GetLacunarity()));
  billow->SetNoiseQuality(getQuality(value, "quality", billow->GetNoiseQuality()));
  billow->SetOctaveCount(static_cast<int>(getDouble(value, "octave", billow->GetOctaveCount())));
  billow->SetPersistence(getDouble(value, "persistence", billow->GetPersistence()));
  billow->SetSeed(static_cast<int>(getDouble(value, "seed", billow->GetSeed())));

  return billow;
}

Module *JSonLoader::createCheckboard(const Value &/*value*/)
{
  return new Checkerboard();
}

Module *JSonLoader::createConst(const Value &value)
{
  Const *constm = new Const();

  constm->SetConstValue(getDouble(value, "const", constm->GetConstValue()));

  return constm;
}

Module *JSonLoader::createCylinders(const Value &value)
{
  Cylinders *cylinders = new Cylinders();

  cylinders->SetFrequency(getDouble(value, "frequency", cylinders->GetFrequency()));

  return cylinders;
}

Module *JSonLoader::createPerlin(const Value &value)
{
  Perlin *perlin = new Perlin();

  perlin->SetFrequency(getDouble(value, "frequency", perlin->GetFrequency()));
  perlin->SetLacunarity(getDouble(value, "lacunarity", perlin->GetLacunarity()));
  perlin->SetNoiseQuality(getQuality(value, "quality", perlin->GetNoiseQuality()));
  perlin->SetOctaveCount(static_cast<int>(getDouble(value, "octave", perlin->GetOctaveCount())));
  perlin->SetPersistence(getDouble(value, "persistence", perlin->GetPersistence()));
  perlin->SetSeed(static_cast<int>(getDouble(value, "seed", perlin->GetSeed())));

  return perlin;
}

Module *JSonLoader::createRidgedMulti(const Value &value)
{
  RidgedMulti *ridged = new RidgedMulti();

  ridged->SetFrequency(getDouble(value, "frequency", ridged->GetFrequency()));
  ridged->SetLacunarity(getDouble(value, "lacunarity", ridged->GetLacunarity()));
  ridged->SetNoiseQuality(getQuality(value, "quality", ridged->GetNoiseQuality()));
  ridged->SetOctaveCount(static_cast<int>(getDouble(value, "octave", ridged->GetOctaveCount())));
  ridged->SetSeed(static_cast<int>(getDouble(value, "seed", ridged->GetSeed())));

  return ridged;
}

Module *JSonLoader::createSpheres(const Value &value)
{
  Spheres *spheres = new Spheres();

  spheres->SetFrequency(getDouble(value, "frequency", spheres->GetFrequency()));

  return spheres;
}

Module *JSonLoader::createVoronoi(const Value &value)
{
  Voronoi *voronoi = new Voronoi();

  voronoi->EnableDistance(getBool(value, "distance", voronoi->IsDistanceEnabled()));
  voronoi->SetDisplacement(getDouble(value, "displacement", voronoi->GetDisplacement()));
  voronoi->SetFrequency(getDouble(value, "frequency", voronoi->GetFrequency()));
  voronoi->SetSeed(static_cast<int>(getDouble(value, "seed", voronoi->GetSeed())));

  return voronoi;
}

Module *JSonLoader::createAbs(const Value &value)
{
  Abs *abs = new Abs();

  fillSources(abs, value, abs->GetSourceModuleCount());

  return abs;
}

Module *JSonLoader::createClamp(const Value &value)
{
  Clamp *clamp = new Clamp();

  clamp->SetBounds(getDouble(value, "lower", clamp->GetLowerBound()),
                   getDouble(value, "upper", clamp->GetUpperBound()));
  fillSources(clamp, value, clamp->GetSourceModuleCount());

  return clamp;
}

Module *JSonLoader::createCurve(const Value &value)
{
  //application must add a minimum of four control points to the curve.
  Value::ConstArray array = getArray(value, "points");
  if (array.Empty())
  {
    cout << "Have not points array is empty" << endl;
    m_haveError = true;
    return nullptr_t();
  }
  if (array.Size() < 4)
  {
    cout << "Array not have 4 points" << endl;
    m_haveError = true;
    return nullptr_t();
  }

  Curve *curve = new Curve();
  curve->ClearAllControlPoints();

  for (const Value &point : array)
  {
    curve->AddControlPoint(getDouble(point, "input", 0.0), getDouble(point, "output", 0.0));
  }

  fillSources(curve, value, curve->GetSourceModuleCount());

  return curve;
}

Module *JSonLoader::createExponent(const Value &value)
{
  Exponent *exp = new Exponent();

  exp->SetExponent(getDouble(value, "exponent", exp->GetExponent()));

  fillSources(exp, value, exp->GetSourceModuleCount());

  return exp;
}

Module *JSonLoader::createInvert(const Value &value)
{
  Invert *invert = new Invert();

  fillSources(invert, value, invert->GetSourceModuleCount());

  return invert;
}

Module *JSonLoader::createScaleBias(const Value &value)
{
  ScaleBias *bias = new ScaleBias();

  fillSources(bias, value, bias->GetSourceModuleCount());

  bias->SetScale(getDouble(value, "scale", bias->GetScale()));
  bias->SetBias(getDouble(value, "bias", bias->GetBias()));

  return bias;
}

Module *JSonLoader::createTerrace(const Value &value)
{
  //An application must add a minimum of two control points to the curve.
  Value::ConstArray array = getArray(value, "points");
  if (array.Empty())
  {
    cout << "Have not points array is empty" << endl;
    m_haveError = true;
    return nullptr_t();
  }
  if (array.Size() < 2)
  {
    cout << "Array not have 2 points" << endl;
    m_haveError = true;
    return nullptr_t();
  }

  Terrace *terr = new Terrace();
  terr->ClearAllControlPoints();

  for (const Value &point : array)
  {
    terr->AddControlPoint(point.GetDouble());
  }

  terr->InvertTerraces(getBool(value, "invert", terr->IsTerracesInverted()));

  fillSources(terr, value, terr->GetSourceModuleCount());

  return terr;
}

Module *JSonLoader::createAdd(const Value &value)
{
  Add *add = new Add();

  fillSources(add, value, add->GetSourceModuleCount());

  return add;
}

Module *JSonLoader::createMax(const Value &value)
{
  Max *max = new Max();

  fillSources(max, value, max->GetSourceModuleCount());

  return max;
}

Module *JSonLoader::createMin(const Value &value)
{
  Min *min = new Min();

  fillSources(min, value, min->GetSourceModuleCount());

  return min;
}

Module *JSonLoader::createMultiply(const Value &value)
{
  Multiply *mult = new Multiply();

  fillSources(mult, value, mult->GetSourceModuleCount());

  return mult;
}

Module *JSonLoader::createPower(const Value &value)
{
  Power *power = new Power();

  fillSources(power, value, power->GetSourceModuleCount());

  return power;
}

Module *JSonLoader::createBlend(const Value &value)
{
  Blend *blend = new Blend();

  fillSources(blend, value, blend->GetSourceModuleCount());

  return blend;
}

Module *JSonLoader::createSelect(const Value &value)
{
  Select *select = new Select();

  fillSources(select, value, select->GetSourceModuleCount());

  select->SetBounds(getDouble(value, "lower", select->GetLowerBound()),
                    getDouble(value, "upper", select->GetUpperBound()));
  select->SetEdgeFalloff(getDouble(value, "falloff", select->GetEdgeFalloff()));

  return select;
}

Module *JSonLoader::createDisplace(const Value &value)
{
  Displace *disp = new Displace();

  fillSources(disp, value, disp->GetSourceModuleCount());

  return disp;
}

Module *JSonLoader::createRotatePoint(const Value &value)
{
  RotatePoint *rotate = new RotatePoint();

  rotate->SetXAngle(getDouble(value, "x", rotate->GetXAngle()));
  rotate->SetYAngle(getDouble(value, "y", rotate->GetYAngle()));
  rotate->SetZAngle(getDouble(value, "x", rotate->GetZAngle()));

  fillSources(rotate, value, rotate->GetSourceModuleCount());

  return rotate;
}

Module *JSonLoader::createScalePoint(const Value &value)
{
  ScalePoint *scale = new ScalePoint();

  scale->SetXScale(getDouble(value, "x", scale->GetXScale()));
  scale->SetYScale(getDouble(value, "y", scale->GetYScale()));
  scale->SetZScale(getDouble(value, "x", scale->GetZScale()));

  fillSources(scale, value, scale->GetSourceModuleCount());

  return scale;
}

Module *JSonLoader::createTranslatePoint(const Value &value)
{
  TranslatePoint *translate = new TranslatePoint();

  translate->SetXTranslation(getDouble(value, "x", translate->GetXTranslation()));
  translate->SetYTranslation(getDouble(value, "y", translate->GetYTranslation()));
  translate->SetZTranslation(getDouble(value, "x", translate->GetZTranslation()));

  fillSources(translate, value, translate->GetSourceModuleCount());

  return translate;
}

Module *JSonLoader::createTurbulence(const Value &value)
{
  Turbulence *tur = new Turbulence();

  tur->SetFrequency(getDouble(value, "frequency", tur->GetFrequency()));
  tur->SetPower(getDouble(value, "power", tur->GetPower()));
  tur->SetRoughness(getDouble(value, "roughness", tur->GetRoughnessCount()));
  tur->SetSeed(getDouble(value, "seed", tur->GetSeed()));

  fillSources(tur, value, tur->GetSourceModuleCount());

  return tur;
}

bool JSonLoader::fillSources(Module *module, const Value &value, const size_t &count)
{
  Value::ConstArray array = getArray(value, "sources");

  if (array.Empty())
  {
    cout << "Have not sources array is empty" << endl;
    m_haveError = true;
    return false;
  }
  if (array.Size() < count)
  {
    cout << "Array not have " << count << " sources" << endl;
    m_haveError = true;
    return false;
  }
  if (m_verbose && array.Size() > count) cout << "Array have to many items need 2 have:" << array.Size() << endl;

  for (size_t i = 0; i < count; i++)
  {
    module->SetSourceModule(i, *formAndCollect(array[i]));
  }
  return true;
}

bool JSonLoader::getBool(const Value &value, const string &name, const bool &def)
{
  if (value.HasMember(name.c_str()) && value[name.c_str()].IsBool()) return value[name.c_str()].GetBool();
  if (m_verbose) cout << "Expect bool member:" << name << endl;
  if (value.HasMember(name.c_str()) && (value[name.c_str()].IsDouble() || value[name.c_str()].IsInt64())) return value[name.c_str()].GetDouble();
  if (m_verbose) cout << "Have not bool member:" << name << endl;
  return def;
}

double JSonLoader::getDouble(const Value &value, const string &name, const double &def)
{
  if (value.HasMember(name.c_str()) && (value[name.c_str()].IsDouble() || value[name.c_str()].IsInt64())) return value[name.c_str()].GetDouble();
  if (m_verbose) cout << "Have not double member:" << name << endl;
  return def;
}

string JSonLoader::getString(const Value &value, const string &name, const string &def)
{
  if (value.HasMember(name.c_str()) && value[name.c_str()].IsString()) return value[name.c_str()].GetString();
  if (m_verbose) cout << "Have not string member:" << name << endl;
  return def;
}

Value::ConstArray JSonLoader::getArray(const Value &value, const string &name)
{
  if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray()) return value[name.c_str()].GetArray();
  if (m_verbose) cout << "Have not array member:" << name << endl;
  const Value a(kArrayType);
  Value::ConstArray def = a.GetArray();
  return def;
}

NoiseQuality JSonLoader::getQuality(const Value &value, const string &name, const NoiseQuality &def)
{
  const string quality = getString(value, name, "");
  if (quality.empty()) return def;
  if (quality == "fast") return QUALITY_FAST;
  if (quality == "standart" || quality == "standard" || quality == "std") return QUALITY_STD;
  if (quality == "best") return QUALITY_BEST;
  cout << "Unknown quality:" << quality;
  return def;
}

JSonLoader::JSonLoader(const string &json)
  : m_json(json),
    m_haveError(false),
    m_verbose(true)
{
}

NoisePack *JSonLoader::get()
{
  parseJson();
  if (m_haveError) return nullptr_t();
  m_pack = new NoisePack();
  m_pack->main = formAndCollect(m_doc);
  return m_pack;
}

void releaseModule(NoisePack *module)
{
  if (module)
  {
    for (size_t i = 0; i < module->modules.size(); i++)
    {
      delete module->modules[i];
    }
    delete module;
  }
}
