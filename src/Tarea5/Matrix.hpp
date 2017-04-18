#ifndef _ANPI_MATRIX_HPP
#define _ANPI_MATRIX_HPP

#include <cstddef>
#include <cstring>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

namespace anpi
{

  /**
   * Row-major simple matrix class
   */
  template<typename T>
  class Matrix {

  private:
    /// All matrix data
    T* _data;
    /// Number of rows
    size_t _rows;
    /// Number of columns
    size_t _cols;

  public:
    /// Construct an empty matrix
    Matrix();
    
    /**
     * Construct a matrix rows x cols and initialize all
     * elements with the given value     
     */
    Matrix(const size_t rows,
	   const size_t cols,
	   const T initVal=T());

    /**
     * Construct a matrix rows x cols and initialize all
     * elements with the memory content at the given pointer
     */
    Matrix(const size_t rows,
	   const size_t cols,
	   const T *const initMem);

    /**
     * COnstruct a square identity matrix
     */
    Matrix(const size_t size);

    /**
     * Copy constructor will do a deep copy on the given matrix
     */
    Matrix(const Matrix<T>& other);
    
    /** 
     * Release all memory
     */
    ~Matrix();

    /**
     * Deep copy another matrix
     */
    Matrix<T>& operator=(const Matrix<T>& other);
    
    /// Return pointer to a given row
    inline T* operator[](const size_t row) {return _data + row*_cols;}

    /// Return read-only pointer to a given row
    const T* operator[](const size_t row) const {return _data + row*_cols;}

    /// Return reference to the element at the r row and c column
	T& operator()(const size_t row,const size_t col) {
	  return *(_data + (row*_cols + col));
	}

	/// Return const reference to the element at the r row and c column
	const T& operator()(const size_t row,const size_t col) const {
	  return *(_data + (row*_cols + col));
	}

    /**
     * Returns the adition of this matrix and another of the same size
     */
    Matrix<T>& operator+(Matrix<T>& B);

    /**
	 * Returns the subtraction of this matrix and another of the same size
	 */
	Matrix<T>& operator-(Matrix<T>& B);

    /**
     * Returns the multiplication of two matrix
     */
    Matrix<T>& operator*(Matrix<T>&B);

    /**
     * Allocate memory for the given number of rows and cols
     */
    void allocate(const size_t row,
		  const size_t col);

    /**
     * Fill all elements of the matrix with the given value
     */
    void fill(const T val);

    /**
     * Fill all elements of the matrix with the given memory block
     *
     * The user must ensure that the given memory block has enough elements
     */
    void fill(const T* mem);

    /*
     * To scale the matrix with an scalar
     */
    void scale(const T scal);

    /*
     * returns this matrix without the first column and row of the matrix, one dimension less
     */
    Matrix<T>& subMatrix(unsigned const int degree);

    /*
	 * returns this matrix with one more column and one more row, one dimension more
	 */
	Matrix<T>& upMatrix(unsigned const int degree);

    /**
     * Number of rows
     */
    inline size_t rows() const { return _rows; }

    /**
     * Number of columns
     */
    inline size_t cols() const { return _cols; }

    /**
     * Pointer to data block
     */
    inline T* data() { return _data; }

    /**
     * Pointer to data block
     */
    inline const T* data() const { return _data; }
    
    /**
     * Calculates the transposed matrix and returns it
     */
    Matrix<T>& transposed();

    /**
     * Prints the matrix content
     */
    void showMatrix();

    void initializeMatrix(T* refMatrix, int size);
  }; // class Matrix


  struct WrongSize:std::exception {
    const char* what() const noexcept {return "Different size of matrix, operation cancelled\n";}
  };


  // --------------
  // Implementation
  // --------------

  template<typename T>
  Matrix<T>::Matrix() : _data(0),_rows(0),_cols(0) {}
 
  template<typename T>
  Matrix<T>::Matrix(const size_t r,
		    const size_t c,
		    const T initVal)
    : _data(0),_rows(0),_cols(0)  {
    allocate(r,c);
    fill(initVal);
  }

  /**
   * Construct a matrix rows x cols and initialize all
   * elements with the memory content at the given pointer
   */
  template<typename T>
  Matrix<T>::Matrix(const size_t r,
		    const size_t c,
		    const T *const initMem)
    : _data(0),_rows(0),_cols(0)  {
    allocate(r,c);
    fill(initMem);
  }
  

  template<typename T>
  Matrix<T>::Matrix(const size_t size){
	 // : _data(0),_rows(0),_cols(0)  {
	  _rows = size;
	  _cols = size;
	  allocate(size,size);
	  fill(0.0);
	  for(unsigned int i=0; i<_rows; i++){
		  (*this)(i,i)=1;
	  }
  }

  template<typename T>
  Matrix<T>::Matrix(const Matrix<T>& other)
    : _data(0),_rows(0),_cols(0) {
    allocate(other._rows,other._cols);
    fill(other.data());
  }
  
  template<typename T>
  Matrix<T>::~Matrix() {
    delete[] _data;
    _data=0;
    _rows=0;
    _data=0;
  }
  
  template<typename T>
  Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    allocate(other._rows,other._cols);
    fill(other.data());
    return *this;
  }

  template<typename T>
  Matrix<T>& Matrix<T>::operator+(Matrix<T>& B){
	  if(this->_cols!=(&B)->cols() && this->rows()!=(&B)->rows()){
		  throw WrongSize();
	  }else {
		  Matrix<T>*ans = new Matrix<T>(this->_rows, this->_cols, 0.0);
		  for(unsigned int i=0;i<this->rows();i++){
			  for(unsigned int j=0;j<this->cols();j++){
				  (*ans)(i,j)=((*this)(i,j))+(B(i,j));
			  }
		  }
		  return *ans;
	  }
  }

//  T* end = _data + (_rows*_cols);
//  for (T* ptr = _data;ptr!=end;++ptr) {
//    *ptr = val;
//  }
  template<typename T>
    Matrix<T>& Matrix<T>::operator-(Matrix<T>& B){
  	  if(this->_cols!=(&B)->cols() && this->rows()!=(&B)->rows()){
  		  throw WrongSize();
  	  }else {
  		  Matrix<T>*ans = new Matrix<T>(this->_rows, this->_cols, 0.0);

  		  for(unsigned int i=0;i<this->rows();i++){
  			  for(unsigned int j=0;j<this->cols();j++){
  				  (*ans)(i,j)=((*this)(i,j))-(B(i,j));
  			  }
  		  }
  		  return *ans;
  	  }
    }

  template<typename T>
  Matrix<T>& Matrix<T>::operator *(Matrix<T>& B){
	  if(this->rows()!=(&B)->cols()){
		throw WrongSize();
	  }else {
			T tmp;
			Matrix<T>* ans = new Matrix<T>(this->cols(),(B).rows(),0.0);
			for(unsigned int a=0; a<rows();a++){
				for(unsigned int b=0; b<B.cols(); b++){
					for(unsigned int c=0; c<rows();c++){
						tmp += (*this)(a,c)*(B(c,b));
					}
					(*ans)(a,b)=tmp;
					tmp=0;
				}
			}
			return *ans;
		}
	}

  template<typename T>
  void Matrix<T>::allocate(const size_t r,
		      const size_t c) {
    delete[] _data;
    _data = new T[r*c];
    _rows=r;
    _cols=c;
  }

  template<typename T>
  void Matrix<T>::fill(const T val) {
    T* end = _data + (_rows*_cols);
    for (T* ptr = _data;ptr!=end;++ptr) {
      *ptr = val;
    }
  }

  template<typename T>
  void Matrix<T>::fill(const T* mem) {
    std::memcpy(_data,mem,sizeof(T)*_rows*_cols);
  }

  template<typename T>
  void Matrix<T>::scale(const T scal){
	  T* end = _data + (_rows*_cols);
	  for (T* ptr = _data;ptr!=end;++ptr) {
		*ptr = (*ptr)*scal;
	  }
  }

  template<typename T>
  Matrix<T>& Matrix<T>::subMatrix(unsigned const int degree){
	  if(this->cols()!=this->rows()){
		  throw WrongSize();
	  }else{
		  Matrix<double>*sub = new Matrix<double>(this->rows()-degree,this->cols()-degree,0.0);
		  for(unsigned int i=degree; i<this->rows(); i++){
			  for(unsigned int j=degree; j<this->cols(); j++){
				  (*sub)(i-degree,j-degree)=(*this)(i,j);
			  }
		  }
		  return *sub;
	  }
  }

  template<typename T>
    Matrix<T>& Matrix<T>::upMatrix(unsigned const int degree){
	  if(this->cols()!=this->rows()){
	  		  throw WrongSize();
	  }else{
		  Matrix<double>*sub = new Matrix<double>(this->rows()+degree,this->cols()+degree,0.0);
		  for(unsigned int i=0; i<this->rows(); i++){
			  for(unsigned int j=0; j<this->cols(); j++){
				  (*sub)(i+degree,j+degree)=(*this)(i,j);
			  }
		  }
		  return *sub;
	  }
  }


  template<typename T>
  Matrix<T>& Matrix<T>::transposed(){
	  Matrix<T>* ans = new Matrix<T>((*this));
	  for(unsigned int y=0; y<_rows; y++){
		  for(unsigned int x=y+1; x<_cols; x++){
			  (*ans)(x,y)=(*this)(y,x);
			  (*ans)(y,x)=(*this)(x,y);
		  }
	  }
	  return *ans;
  }

  template<typename T>
  void Matrix<T>::showMatrix(){
	  for(unsigned int y=0; y<_rows; y++){
		  for(unsigned int x=0; x<_cols; x++){
			  cout<<setw(14)<<(*this)(x,y);
		  }
		  cout<<endl;
	  }
  }

  template<typename T>
  void Matrix<T>::initializeMatrix(T* refMatrix, int size){
	  for(int i=0; i<size;i++){
		  for(int j=0; j<size; j++){
			  (*this)(i,j) = refMatrix[i*size+j];
		  }
	  }
  }
} // namespace ANPI


#endif
