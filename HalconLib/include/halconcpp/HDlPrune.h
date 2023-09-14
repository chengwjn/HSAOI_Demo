/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 22.05
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HDLPRUNE
#define HCPP_HDLPRUNE

namespace HalconCpp
{

// Represents an instance of the parameter information for pruning a Deep Neural Network model.
class LIntExport HDlPrune : public HHandle
{

public:

  // Create an uninitialized instance
  HDlPrune():HHandle() {}

  // Copy constructor
  HDlPrune(const HDlPrune& source) : HHandle(source) {}

  // Copy constructor
  HDlPrune(const HHandle& handle);

  // Create HDlPrune from handle, taking ownership
  explicit HDlPrune(Hlong handle);

  bool operator==(const HHandle& obj) const
  {
    return HHandleBase::operator==(obj);
  }

  bool operator!=(const HHandle& obj) const
  {
    return HHandleBase::operator!=(obj);
  }

protected:

  // Verify matching semantic type ('dl_pruning')!
  virtual void AssertType(Hphandle handle) const;

public:



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // create_dl_pruning: Create a pruning data handle.
  explicit HDlPrune(const HDlModel& DLModelHandle, const HString& Mode, const HDict& GenParam);

  // create_dl_pruning: Create a pruning data handle.
  explicit HDlPrune(const HDlModel& DLModelHandle, const char* Mode, const HDict& GenParam);

#ifdef _WIN32
  // create_dl_pruning: Create a pruning data handle.
  explicit HDlPrune(const HDlModel& DLModelHandle, const wchar_t* Mode, const HDict& GenParam);
#endif




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Calculate scores to prune a deep learning model.
  void AddDlPruningBatch(const HDlModel& DLModelHandleToPrune, const HDictArray& DLSampleBatch) const;

  // Create a pruning data handle.
  void CreateDlPruning(const HDlModel& DLModelHandle, const HString& Mode, const HDict& GenParam);

  // Create a pruning data handle.
  void CreateDlPruning(const HDlModel& DLModelHandle, const char* Mode, const HDict& GenParam);

#ifdef _WIN32
  // Create a pruning data handle.
  void CreateDlPruning(const HDlModel& DLModelHandle, const wchar_t* Mode, const HDict& GenParam);
#endif

  // Get information from a pruning data handle.
  HTuple GetDlPruningParam(const HString& GenParamName) const;

  // Get information from a pruning data handle.
  HTuple GetDlPruningParam(const char* GenParamName) const;

#ifdef _WIN32
  // Get information from a pruning data handle.
  HTuple GetDlPruningParam(const wchar_t* GenParamName) const;
#endif

  // Set parameter in a pruning data handle.
  void SetDlPruningParam(const HString& GenParamName, const HTuple& GenParamValue) const;

  // Set parameter in a pruning data handle.
  void SetDlPruningParam(const HString& GenParamName, double GenParamValue) const;

  // Set parameter in a pruning data handle.
  void SetDlPruningParam(const char* GenParamName, double GenParamValue) const;

#ifdef _WIN32
  // Set parameter in a pruning data handle.
  void SetDlPruningParam(const wchar_t* GenParamName, double GenParamValue) const;
#endif

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HHandleBaseArrayRef;

typedef HHandleBaseArrayRef<HDlPrune> HDlPruneArrayRef;
typedef HSmartPtr< HDlPruneArrayRef > HDlPruneArrayPtr;


// Represents multiple tool instances
class LIntExport HDlPruneArray : public HHandleBaseArray
{

public:

  // Create empty array
  HDlPruneArray();

  // Create array from native array of tool instances
  HDlPruneArray(const HDlPrune* classes, Hlong length);

  // Copy constructor
  HDlPruneArray(const HDlPruneArray &tool_array);

  // Destructor
  virtual ~HDlPruneArray();

  // Assignment operator
  HDlPruneArray &operator=(const HDlPruneArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HDlPrune* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HDlPruneArrayPtr *mArrayPtr;
};

}

#endif
