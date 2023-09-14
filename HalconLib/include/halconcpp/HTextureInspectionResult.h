/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 22.05
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HTEXTUREINSPECTIONRESULT
#define HCPP_HTEXTUREINSPECTIONRESULT

namespace HalconCpp
{

// Represents an instance of a texture inspection result.
class LIntExport HTextureInspectionResult : public HHandle
{

public:

  // Create an uninitialized instance
  HTextureInspectionResult():HHandle() {}

  // Copy constructor
  HTextureInspectionResult(const HTextureInspectionResult& source) : HHandle(source) {}

  // Copy constructor
  HTextureInspectionResult(const HHandle& handle);

  // Create HTextureInspectionResult from handle, taking ownership
  explicit HTextureInspectionResult(Hlong handle);

  bool operator==(const HHandle& obj) const
  {
    return HHandleBase::operator==(obj);
  }

  bool operator!=(const HHandle& obj) const
  {
    return HHandleBase::operator!=(obj);
  }

protected:

  // Verify matching semantic type ('texture_inspection_result')!
  virtual void AssertType(Hphandle handle) const;

public:



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // apply_texture_inspection_model: Inspection of the texture within an image.
  explicit HTextureInspectionResult(const HImage& Image, HRegion* NoveltyRegion, const HTextureInspectionModel& TextureInspectionModel);




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Add training images to the texture inspection model.
  static HTuple AddTextureInspectionModelImage(const HImage& Image, const HTextureInspectionModel& TextureInspectionModel);

  // Inspection of the texture within an image.
  HRegion ApplyTextureInspectionModel(const HImage& Image, const HTextureInspectionModel& TextureInspectionModel);

  // Clear a texture inspection result handle and free the allocated memory. 
  static void ClearTextureInspectionResult(const HTextureInspectionResultArray& TextureInspectionResultID);

  // Clear a texture inspection result handle and free the allocated memory. 
  void ClearTextureInspectionResult() const;

  // Get the training images contained in a texture inspection model.
  static HImage GetTextureInspectionModelImage(const HTextureInspectionModel& TextureInspectionModel);

  // Query iconic results of a texture inspection.
  HObject GetTextureInspectionResultObject(const HTuple& ResultName) const;

  // Query iconic results of a texture inspection.
  HObject GetTextureInspectionResultObject(const HString& ResultName) const;

  // Query iconic results of a texture inspection.
  HObject GetTextureInspectionResultObject(const char* ResultName) const;

#ifdef _WIN32
  // Query iconic results of a texture inspection.
  HObject GetTextureInspectionResultObject(const wchar_t* ResultName) const;
#endif

  // Train a texture inspection model.
  static void TrainTextureInspectionModel(const HTextureInspectionModel& TextureInspectionModel);

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HHandleBaseArrayRef;

typedef HHandleBaseArrayRef<HTextureInspectionResult> HTextureInspectionResultArrayRef;
typedef HSmartPtr< HTextureInspectionResultArrayRef > HTextureInspectionResultArrayPtr;


// Represents multiple tool instances
class LIntExport HTextureInspectionResultArray : public HHandleBaseArray
{

public:

  // Create empty array
  HTextureInspectionResultArray();

  // Create array from native array of tool instances
  HTextureInspectionResultArray(const HTextureInspectionResult* classes, Hlong length);

  // Copy constructor
  HTextureInspectionResultArray(const HTextureInspectionResultArray &tool_array);

  // Destructor
  virtual ~HTextureInspectionResultArray();

  // Assignment operator
  HTextureInspectionResultArray &operator=(const HTextureInspectionResultArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HTextureInspectionResult* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HTextureInspectionResultArrayPtr *mArrayPtr;
};

}

#endif
