#ifndef __MATR_H_
#define __MATR_H_
#include <iostream>
#include <cmath>

using namespace std;

/**
 * A 2D matrix
 * @tparam tmp Matrix type
 */
template <typename tmp> class matr {
private:
	int height;
	int width;
	tmp** matrix;

public:
  /**
   * Lets user to input the matrix. Is hardcoded to use random input (for scientific purposes...)
   */
	void input();
	
	explicit matr(int HandW);
	matr(int h, int w);
	matr(const matr<tmp>& other);

	/**
	 * Get matrix height
	 * @return Height of the matrix
	 */
	int GetH() const { return this->height; }

  /**
 * Get matrix width
 * @return Width of the matrix
 */
	int GetW() const { return this->width; }
	/**
	 * Get an element of the matrix at given position
	 * @param height Height of the element
	 * @param width Width of the element
	 * @return Element at given position
	 */
	tmp GetEl(int height, int width) const { return this->matrix[height][width]; }
  /**
   * Set an element of the matrix at given position
   * @param height Height of the element
   * @param width Width of the element
   * @param value Value to be set
   */
	void SetEl(int height, int width, tmp value) { this->matrix[height][width] = value; }


	/**
	 *
	 * @param Right
	 * @return
	 */
	matr<tmp>& operator =(const matr<tmp>& Right);
	
	void transpose();
	tmp decrement(tmp flag = (tmp) 1, tmp minorMultiple = (tmp) 1);
	void normalizeH(int height);
	void normalizeW(int width);
	void show();
	
	~matr();
};	


template<typename tmp>
void matr<tmp>::input() {
	if (this->height <= 0 || this->width <= 0 || this->matrix == nullptr) {
		std::cout << "Input error" << std::endl;
		throw("Matrix input error");
	}
	else {
		tmp t;
		std::cout << "Input matrix " << this->height << "x" << this->width << ":" << std::endl;
			for (int i = 0; i < this->height; i++)
				for (int j = 0; j < this->width; j++) {
					//std::cin >> t;
					t = rand() % 10;
					this->matrix[i][j] = (tmp)(t);
				}
    std::cout << std::endl << "Using random input..." << std::endl;
		std::cout << std::endl << "Input completed." << std::endl;
	}
}

template<typename tmp>
matr<tmp>::matr(int HandW) : matr<tmp>::matr(HandW, HandW) {
}

template<typename tmp>
matr<tmp>::matr(int h, int w) {
	this->height = h;
	this->width = w;
	this->matrix = new tmp * [this->height];

	for (int i = 0; i < this->height; i++)
		this->matrix[i] = new tmp[this->width];
	this->input();
}

template<typename tmp>
matr <tmp>::matr(const matr<tmp>& other) {
	this->height = other.height;
	this->width = other.width;
	this->matrix = new tmp * [this->height];

	for (int i = 0; i < this->height; i++)
		this->matrix[i] = new tmp[this->width];
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			this->matrix[i][j] = other.matrix[i][j];
}

template<typename tmp>
matr<tmp>::~matr() { 
	if (this->matrix != nullptr) {
		for (int i = 0; i < this->height; i++)
			delete[] this->matrix[i];
		delete[] this->matrix;
	}
}

template<typename tmp>
matr<tmp>& matr<tmp>::operator =(const matr<tmp>& Right) {
	
	for (int i = 0; i < this->height; i++)
		delete this->matrix[i];
	delete this->matrix;
	this->height = Right.height;
	this->width = Right.width;
	
	this->matrix = new tmp * [this->height];
	for (int i = 0; i < this->height; i++)
		matrix[i] = new tmp[this->width];

	for (auto i : this->matrix)
		for (auto j : this->matrix[i])
			this->matrix[i][j] = Right[i][j];
	return *this;
}

template<typename tmp>
matr<tmp> operator *(const matr<tmp>& Left, const matr<tmp>& Right) {
	
	tmp skalTMP= 0;		
	matr<tmp> matrTMP(Left.GetH(), Left.GetW());

	for (int i = 0; i < Left.GetW(); i++)					
		for (int j = 0; j < Left.GetH(); j++) {			
			for (int k = 0; k < Left.GetH(); k++)
				skalTMP += Left.GetEl(i, k) * Right.GetEl(k, j);
			matrTMP.SetEl(i, j, skalTMP);
			skalTMP = 0;
		}	
	return matrTMP;
}

template<typename tmp>
matr<tmp> operator +(const matr<tmp> Left, const matr<tmp> Right) {
	matr<tmp> matrTMP(Left.GetH(), Left.GetW());

	for (int i = 0; i < Left.GetH(); i++)
		for (int j = 0; j < Left.GetW(); j++)
			matrTMP.SetEl(i, j, Left.GetEl(i, j) + Right.GetEl(i, j));

	return matrTMP;
}


template<typename tmp>
void matr<tmp>::transpose() {
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			if (i > j) {
				tmp T = this->matrix[i][j];
				this->matrix[i][j] = this->matrix[j][i];
				this->matrix[j][i] = T;
			}
}


template<typename tmp>
matr<tmp> operator +(const matr<tmp> Left, const tmp Right) {
	matr<tmp> matrTMP(Left.GetH(), Left.GetW());
	
	for (int i = 0; i < Left.GetH(); i++)
		for (int j = 0; j < Left.GetW(); j++)
			matrTMP.SetEl(i, j, Left.GetEl(i, j) + Right);
	return matrTMP;
}

template<typename tmp>
matr<tmp> operator *(const matr<tmp> Left, const tmp Right) {
	matr<tmp> matrTMP(Left.GetH(), Left.GetW());

	for (int i = 0; i < Left.GetH(); i++)
		for (int j = 0; j < Left.GetW(); j++)
			matrTMP.SetEl(i, j, Left.GetEl(i, j) * Right);
	return matrTMP;
}

template<typename tmp>
tmp matr<tmp>::decrement(tmp flag, tmp minorMultiple) {
	tmp Deter = 0;																

	if (this->height == 1)																
		return (this->matrix[0][0] * flag * minorMultiple);								
	for (int MatrWidth = 0; MatrWidth < this->width; MatrWidth++) {						
		matr<tmp> TMP(this->height - 1, this->width - 1);
																					
																				
		for (int iMax = 1, iMinor = 0; iMinor < this->height - 1; iMax++, iMinor++)		
			for (int jMax = 0, jMinor = 0; jMinor < this->width - 1; jMax++, jMinor++) {	
				if (jMax != MatrWidth)												
					TMP.matrix[iMinor][jMinor] = this->matrix[iMax][jMax];						
				else																
					jMinor--;														
			}		
		Deter += 																	
			flag *																	
			minorMultiple *
          TMP.decrement((tmp) pow(-1, MatrWidth), this->matrix[0][MatrWidth]);
		Deter += 0;
	}																				
	return Deter;																	
}

template<typename tmp>
void matr<tmp>::normalizeH(int height) {
	for (int i = this->height - 1; i >= 0; i--)
		for (int j = this->width - 1; j >= 0; j--)
			if (i != height)
				this->matrix[i][j] /= this->matrix[height][j];
	for (int i = 0; i < this->width; i++)
		this->matrix[height][i] = 1;
}
template<typename tmp>
void matr<tmp>::normalizeW(int width) {
	for (int i = this->height - 1; i >= 0; i--)
		for (int j = this->width - 1; j >= 0; j--)
			if (j != width)
				this->matrix[i][j] /= this->matrix[i][width];
	for (int i = 0; i < this->height; i++)
		this->matrix[i][width] = 1;
}


template<typename tmp>
void matr<tmp>::show() {
	if (this->height <= 0 || this->width <= 0 || this->matrix == nullptr) {
		std::cout << "An error occured while trying to show() matrix." << std::endl;
		return;
	}

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++)
			std::cout << this->matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
#endif /*__MATR_H_*/