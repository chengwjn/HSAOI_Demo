/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 22.05
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HOCRSVM
#define HCPP_HOCRSVM

namespace HalconCpp
{

// Represents an instance of a SVM OCR classifier.
class LIntExport HOCRSvm : public HHandle
{

public:

  // Create an uninitialized instance
  HOCRSvm():HHandle() {}

  // Copy constructor
  HOCRSvm(const HOCRSvm& source) : HHandle(source) {}

  // Copy constructor
  HOCRSvm(const HHandle& handle);

  // Create HOCRSvm from handle, taking ownership
  explicit HOCRSvm(Hlong handle);

  bool operator==(const HHandle& obj) const
  {
    return HHandleBase::operator==(obj);
  }

  bool operator!=(const HHandle& obj) const
  {
    return HHandleBase::operator!=(obj);
  }

protected:

  // Verify matching semantic type ('ocr_svm')!
  virtual void AssertType(Hphandle handle) const;

public:

  // Deep copy of all data represented by this object instance
  HOCRSvm Clone() const;



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // read_ocr_class_svm: Read a SVM-based OCR classifier from a file.
  explicit HOCRSvm(const HString& FileName);

  // read_ocr_class_svm: Read a SVM-based OCR classifier from a file.
  explicit HOCRSvm(const char* FileName);

#ifdef _WIN32
  // read_ocr_class_svm: Read a SVM-based OCR classifier from a file.
  explicit HOCRSvm(const wchar_t* FileName);
#endif

  // create_ocr_class_svm: Create an OCR classifier using a support vector machine.
  explicit HOCRSvm(Hlong WidthCharacter, Hlong HeightCharacter, const HString& Interpolation, const HTuple& Features, const HTuple& Characters, const HString& KernelType, double KernelParam, double Nu, const HString& Mode, const HString& Preprocessing, Hlong NumComponents);

  // create_ocr_class_svm: Create an OCR classifier using a support vector machine.
  explicit HOCRSvm(Hlong WidthCharacter, Hlong HeightCharacter, const HString& Interpolation, const HString& Features, const HTuple& Characters, const HString& KernelType, double KernelParam, double Nu, const HString& Mode, const HString& Preprocessing, Hlong NumComponents);

  // create_ocr_class_svm: Create an OCR classifier using a support vector machine.
  explicit HOCRSvm(Hlong WidthCharacter, Hlong HeightCharacter, const char* Interpolation, const char* Features, const HTuple& Characters, const char* KernelType, double KernelParam, double Nu, const char* Mode, const char* Preprocessing, Hlong NumComponents);

#ifdef _WIN32
  // create_ocr_class_svm: Create an OCR classifier using a support vector machine.
  explicit HOCRSvm(Hlong WidthCharacter, Hlong HeightCharacter, const wchar_t* Interpolation, const wchar_t* Features, const HTuple& Characters, const wchar_t* KernelType, double KernelParam, double Nu, const wchar_t* Mode, const wchar_t* Preprocessing, Hlong NumComponents);
#endif




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Select an optimal combination of features to classify OCR data from a (protected) training file.
  HTuple SelectFeatureSetTrainfSvmProtected(const HTuple& TrainingFile, const HTuple& Password, const HTuple& FeatureList, const HString& SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

  // Select an optimal combination of features to classify OCR data from a (protected) training file.
  HTuple SelectFeatureSetTrainfSvmProtected(const HString& TrainingFile, const HString& Password, const HString& FeatureList, const HString& SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

  // Select an optimal combination of features to classify OCR data from a (protected) training file.
  HTuple SelectFeatureSetTrainfSvmProtected(const char* TrainingFile, const char* Password, const char* FeatureList, const char* SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

#ifdef _WIN32
  // Select an optimal combination of features to classify OCR data from a (protected) training file.
  HTuple SelectFeatureSetTrainfSvmProtected(const wchar_t* TrainingFile, const wchar_t* Password, const wchar_t* FeatureList, const wchar_t* SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);
#endif

  // Selects an optimal combination of features to classify OCR  data.
  HTuple SelectFeatureSetTrainfSvm(const HTuple& TrainingFile, const HTuple& FeatureList, const HString& SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

  // Selects an optimal combination of features to classify OCR  data.
  HTuple SelectFeatureSetTrainfSvm(const HString& TrainingFile, const HString& FeatureList, const HString& SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

  // Selects an optimal combination of features to classify OCR  data.
  HTuple SelectFeatureSetTrainfSvm(const char* TrainingFile, const char* FeatureList, const char* SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);

#ifdef _WIN32
  // Selects an optimal combination of features to classify OCR  data.
  HTuple SelectFeatureSetTrainfSvm(const wchar_t* TrainingFile, const wchar_t* FeatureList, const wchar_t* SelectionMethod, Hlong Width, Hlong Height, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score);
#endif

  // Clear an SVM-based OCR classifier.
  static void ClearOcrClassSvm(const HOCRSvmArray& OCRHandle);

  // Clear an SVM-based OCR classifier.
  void ClearOcrClassSvm() const;

  // Deserialize a serialized SVM-based OCR classifier.
  void DeserializeOcrClassSvm(const HSerializedItem& SerializedItemHandle);

  // Serialize a SVM-based OCR classifier
  HSerializedItem SerializeOcrClassSvm() const;

  // Read a SVM-based OCR classifier from a file.
  void ReadOcrClassSvm(const HString& FileName);

  // Read a SVM-based OCR classifier from a file.
  void ReadOcrClassSvm(const char* FileName);

#ifdef _WIN32
  // Read a SVM-based OCR classifier from a file.
  void ReadOcrClassSvm(const wchar_t* FileName);
#endif

  // Write an OCR classifier to a file.
  void WriteOcrClassSvm(const HString& FileName) const;

  // Write an OCR classifier to a file.
  void WriteOcrClassSvm(const char* FileName) const;

#ifdef _WIN32
  // Write an OCR classifier to a file.
  void WriteOcrClassSvm(const wchar_t* FileName) const;
#endif

  // Compute the features of a character.
  HTuple GetFeaturesOcrClassSvm(const HImage& Character, const HString& Transform) const;

  // Compute the features of a character.
  HTuple GetFeaturesOcrClassSvm(const HImage& Character, const char* Transform) const;

#ifdef _WIN32
  // Compute the features of a character.
  HTuple GetFeaturesOcrClassSvm(const HImage& Character, const wchar_t* Transform) const;
#endif

  // Classify a related group of characters with an OCR classifier.
  HTuple DoOcrWordSvm(const HRegion& Character, const HImage& Image, const HString& Expression, Hlong NumAlternatives, Hlong NumCorrections, HString* Word, double* Score) const;

  // Classify a related group of characters with an OCR classifier.
  HTuple DoOcrWordSvm(const HRegion& Character, const HImage& Image, const char* Expression, Hlong NumAlternatives, Hlong NumCorrections, HString* Word, double* Score) const;

#ifdef _WIN32
  // Classify a related group of characters with an OCR classifier.
  HTuple DoOcrWordSvm(const HRegion& Character, const HImage& Image, const wchar_t* Expression, Hlong NumAlternatives, Hlong NumCorrections, HString* Word, double* Score) const;
#endif

  // Classify multiple characters with an SVM-based OCR classifier.
  HTuple DoOcrMultiClassSvm(const HRegion& Character, const HImage& Image) const;

  // Classify a single character with an SVM-based OCR classifier.
  HTuple DoOcrSingleClassSvm(const HRegion& Character, const HImage& Image, const HTuple& Num) const;

  // Approximate a trained SVM-based OCR classifier by a reduced SVM.
  HOCRSvm ReduceOcrClassSvm(const HString& Method, Hlong MinRemainingSV, double MaxError) const;

  // Approximate a trained SVM-based OCR classifier by a reduced SVM.
  HOCRSvm ReduceOcrClassSvm(const char* Method, Hlong MinRemainingSV, double MaxError) const;

#ifdef _WIN32
  // Approximate a trained SVM-based OCR classifier by a reduced SVM.
  HOCRSvm ReduceOcrClassSvm(const wchar_t* Method, Hlong MinRemainingSV, double MaxError) const;
#endif

  // Train an OCR classifier with data from a (protected) training file.
  void TrainfOcrClassSvmProtected(const HTuple& TrainingFile, const HTuple& Password, double Epsilon, const HTuple& TrainMode) const;

  // Train an OCR classifier with data from a (protected) training file.
  void TrainfOcrClassSvmProtected(const HString& TrainingFile, const HString& Password, double Epsilon, const HString& TrainMode) const;

  // Train an OCR classifier with data from a (protected) training file.
  void TrainfOcrClassSvmProtected(const char* TrainingFile, const char* Password, double Epsilon, const char* TrainMode) const;

#ifdef _WIN32
  // Train an OCR classifier with data from a (protected) training file.
  void TrainfOcrClassSvmProtected(const wchar_t* TrainingFile, const wchar_t* Password, double Epsilon, const wchar_t* TrainMode) const;
#endif

  // Train an OCR classifier.
  void TrainfOcrClassSvm(const HTuple& TrainingFile, double Epsilon, const HTuple& TrainMode) const;

  // Train an OCR classifier.
  void TrainfOcrClassSvm(const HString& TrainingFile, double Epsilon, const HString& TrainMode) const;

  // Train an OCR classifier.
  void TrainfOcrClassSvm(const char* TrainingFile, double Epsilon, const char* TrainMode) const;

#ifdef _WIN32
  // Train an OCR classifier.
  void TrainfOcrClassSvm(const wchar_t* TrainingFile, double Epsilon, const wchar_t* TrainMode) const;
#endif

  // Compute the information content of the preprocessed feature vectors of an SVM-based OCR classifier.
  HTuple GetPrepInfoOcrClassSvm(const HTuple& TrainingFile, const HString& Preprocessing, HTuple* CumInformationCont) const;

  // Compute the information content of the preprocessed feature vectors of an SVM-based OCR classifier.
  HTuple GetPrepInfoOcrClassSvm(const HString& TrainingFile, const HString& Preprocessing, HTuple* CumInformationCont) const;

  // Compute the information content of the preprocessed feature vectors of an SVM-based OCR classifier.
  HTuple GetPrepInfoOcrClassSvm(const char* TrainingFile, const char* Preprocessing, HTuple* CumInformationCont) const;

#ifdef _WIN32
  // Compute the information content of the preprocessed feature vectors of an SVM-based OCR classifier.
  HTuple GetPrepInfoOcrClassSvm(const wchar_t* TrainingFile, const wchar_t* Preprocessing, HTuple* CumInformationCont) const;
#endif

  // Return the number of support vectors of an OCR classifier.
  Hlong GetSupportVectorNumOcrClassSvm(HTuple* NumSVPerSVM) const;

  // Return the index of a support vector from a trained OCR classifier that is based on support vector machines.
  double GetSupportVectorOcrClassSvm(const HTuple& IndexSupportVector) const;

  // Return the parameters of an OCR classifier.
  void GetParamsOcrClassSvm(Hlong* WidthCharacter, Hlong* HeightCharacter, HString* Interpolation, HTuple* Features, HTuple* Characters, HString* KernelType, double* KernelParam, double* Nu, HString* Mode, HString* Preprocessing, Hlong* NumComponents) const;

  // Return the parameters of an OCR classifier.
  void GetParamsOcrClassSvm(Hlong* WidthCharacter, Hlong* HeightCharacter, HString* Interpolation, HString* Features, HTuple* Characters, HString* KernelType, double* KernelParam, double* Nu, HString* Mode, HString* Preprocessing, Hlong* NumComponents) const;

  // Create an OCR classifier using a support vector machine.
  void CreateOcrClassSvm(Hlong WidthCharacter, Hlong HeightCharacter, const HString& Interpolation, const HTuple& Features, const HTuple& Characters, const HString& KernelType, double KernelParam, double Nu, const HString& Mode, const HString& Preprocessing, Hlong NumComponents);

  // Create an OCR classifier using a support vector machine.
  void CreateOcrClassSvm(Hlong WidthCharacter, Hlong HeightCharacter, const HString& Interpolation, const HString& Features, const HTuple& Characters, const HString& KernelType, double KernelParam, double Nu, const HString& Mode, const HString& Preprocessing, Hlong NumComponents);

  // Create an OCR classifier using a support vector machine.
  void CreateOcrClassSvm(Hlong WidthCharacter, Hlong HeightCharacter, const char* Interpolation, const char* Features, const HTuple& Characters, const char* KernelType, double KernelParam, double Nu, const char* Mode, const char* Preprocessing, Hlong NumComponents);

#ifdef _WIN32
  // Create an OCR classifier using a support vector machine.
  void CreateOcrClassSvm(Hlong WidthCharacter, Hlong HeightCharacter, const wchar_t* Interpolation, const wchar_t* Features, const HTuple& Characters, const wchar_t* KernelType, double KernelParam, double Nu, const wchar_t* Mode, const wchar_t* Preprocessing, Hlong NumComponents);
#endif

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HHandleBaseArrayRef;

typedef HHandleBaseArrayRef<HOCRSvm> HOCRSvmArrayRef;
typedef HSmartPtr< HOCRSvmArrayRef > HOCRSvmArrayPtr;


// Represents multiple tool instances
class LIntExport HOCRSvmArray : public HHandleBaseArray
{

public:

  // Create empty array
  HOCRSvmArray();

  // Create array from native array of tool instances
  HOCRSvmArray(const HOCRSvm* classes, Hlong length);

  // Copy constructor
  HOCRSvmArray(const HOCRSvmArray &tool_array);

  // Destructor
  virtual ~HOCRSvmArray();

  // Assignment operator
  HOCRSvmArray &operator=(const HOCRSvmArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HOCRSvm* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HOCRSvmArrayPtr *mArrayPtr;
};

}

#endif