#pragma once
#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
class CCalculateFFT
{
	
public:
	static const double PI;
	typedef std::complex<double> Complex;
	typedef std::valarray<Complex> CArray;

	// Cooley–Tukey FFT (in-place, divide-and-conquer)
	// Higher memory requirements and redundancy although more intuitive
	void fft(CArray& x)
	{
		const size_t N = x.size();
		if (N <= 1) return;

		// divide
		CArray even = x[std::slice(0, N / 2, 2)];
		CArray  odd = x[std::slice(1, N / 2, 2)];

		// conquer
		fft(even);
		fft(odd);

		// combine
		for (size_t k = 0; k < N / 2; ++k)
		{
			Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
			x[k] = even[k] + t;
			x[k + N / 2] = even[k] - t;
		}
	}

	// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
	// Better optimized but less intuitive
	// !!! Warning : in some cases this code make result different from not optimased version above (need to fix bug)
	// The bug is now fixed @2017/05/30 
	void fft(CArray &x)
	{
		// DFT
		unsigned int N = x.size(), k = N, n;
		double thetaT = 3.14159265358979323846264338328L / N;
		Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
		while (k > 1)
		{
			n = k;
			k >>= 1;
			phiT = phiT * phiT;
			T = 1.0L;
			for (unsigned int l = 0; l < k; l++)
			{
				for (unsigned int a = l; a < N; a += n)
				{
					unsigned int b = a + k;
					Complex t = x[a] - x[b];
					x[a] += x[b];
					x[b] = t * T;
				}
				T *= phiT;
			}
		}
		// Decimate
		unsigned int m = (unsigned int)log2(N);
		for (unsigned int a = 0; a < N; a++)
		{
			unsigned int b = a;
			// Reverse bits
			b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
			b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
			b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
			b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
			b = ((b >> 16) | (b << 16)) >> (32 - m);
			if (b > a)
			{
				Complex t = x[a];
				x[a] = x[b];
				x[b] = t;
			}
		}
		//// Normalize (This section make it not working correctly)
		//Complex f = 1.0 / sqrt(N);
		//for (unsigned int i = 0; i < N; i++)
		//	x[i] *= f;
	}

	// inverse fft (in-place)
	void ifft(CArray& x)
	{
		// conjugate the complex numbers
		x = x.apply(std::conj);

		// forward fft
		fft(x);

		// conjugate the complex numbers again
		x = x.apply(std::conj);

		// scale the numbers
		x /= x.size();
	}

	int main()
	{
		const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
		CArray data(test, 8);

		// forward fft
		fft(data);

		std::cout << "fft" << std::endl;
		for (int i = 0; i < 8; ++i)
		{
			std::cout << data[i] << std::endl;
		}

		// inverse fft
		ifft(data);

		std::cout << std::endl << "ifft" << std::endl;
		for (int i = 0; i < 8; ++i)
		{
			std::cout << data[i] << std::endl;
		}
		return 0;
	}
public:
	void PrepareInput(const std::vector<double> & vdIn, std::vector<double> & vdReady)
	{
		std::vector<double>::size_type nNum = vdIn.size(),nNewNum,i;
		if (nNum < 4)
		{
			nNewNum = 4;
		}
		else
		{
			double po = (double)log((double)nNum) / log(2.0f);
			nNewNum = (std::vector<double>::size_type)pow(2.0f, (int)(po + 0.9995));
		}
		ASSERT(nNewNum >= nNum);
		vdReady.resize(nNewNum);
		for (i = 0; i < nNum; i++)
		{
			vdReady[i] = vdIn[i];
		}
		for (; i < nNewNum; i++)
		{
			vdReady[i] = 0;
		}
	}
	void RealToComplex(const std::vector<double> & vdReal, std::valarray<Complex> & voComplex)
	{
		std::vector<double>::size_type i,nNum = vdReal.size();
		voComplex.resize(nNum);
		for (i = 0; i < nNum; i++)
		{
			voComplex[i].real(vdReal[i]);
			voComplex[i].imag(0);
		}
	}
	void ComplexToReal(const std::valarray<Complex> & voComplex, std::vector<double> & vdReal)
	{
		std::vector<double>::size_type i, nNum = voComplex.size();
		vdReal.resize(nNum);
		for (i = 0; i < nNum; i++)
		{
			vdReal[i] = sqrt(voComplex[i].real()*voComplex[i].real() + voComplex[i].imag()*voComplex[i].imag());
		}
	}
};
const double CCalculateFFT::PI = 3.141592653589793238460;