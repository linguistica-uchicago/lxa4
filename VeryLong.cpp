// Implementation for CVeryLong methods
// Copyright © 2009 The University of Chicago
#include "VeryLong.h"

#include <cmath>
#include "StringFunc.h"
#include "log2.h"

// NB: Only for positive numbers! But with an exponent up to 32K or
// down to -32K (since exponent is based on an int);

int AssignFromVeryLongToDouble(CVeryLong& A, double& b)
{ 
	return (A >> b);	 
}

void	IncrementDoubleByVeryLong(double& Double, CVeryLong& VeryLong )
{	double Temp;
	VeryLong >> Temp;
	Double += Temp;
}

CVeryLong::CVeryLong() 
{ 
	m_Mantissa = 0;
	m_Exponent = 1;
};

CVeryLong::CVeryLong (const CVeryLong& Rhs):
	m_Mantissa(Rhs.m_Mantissa), m_Exponent(Rhs.m_Exponent)
{};

CVeryLong::CVeryLong(const double f)
{	float	Log1; 
//	Q_ASSERT (f >= 0);
	if (f <0 ) {return;}
	if (f==0) {
		m_Mantissa = 0;
		m_Exponent = 1;
		return;
	}
	Log1 = (float) log10(f);
	if (Log1 > 0) {		 
		m_Exponent	= int (Log1);		 	 
		m_Mantissa  = float (f / exp10 ( (float) m_Exponent) );
		return;
	}	
	if (Log1 < 0) {
		Log1 *= -1.0;
		m_Exponent = -1 + -1 * int(Log1);
		m_Mantissa = float (f / exp10 ( (float) m_Exponent));
		return;
	}
	m_Exponent = 0;
	m_Mantissa = 1.0;
	return;
}

CVeryLong::~CVeryLong()
{};

void CVeryLong::SetExponent(int i) {m_Exponent = i;}

void CVeryLong::SetMantissa (float f) {m_Mantissa = f;}

void CVeryLong::operator= (const CVeryLong& Rhs)
{	m_Mantissa = Rhs.GetMantissa();
	m_Exponent = Rhs.GetExponent();
}


int CVeryLong::operator= (const double& f)
{	float	Log1; 
//	Q_ASSERT (f >= 0);
	if (f <0 ) {return 0;}
	if (f==0) {
		m_Mantissa = 0;
		m_Exponent = 1;
		return 1;
	}
	Log1 = (float) log10(f);
	if (f > 1) {		 
		m_Exponent	= int (Log1);
		m_Mantissa  = float (f / exp10 ( (float) m_Exponent) );
		return 1;
	}	
	if (f < 1) {
		Log1 *= -1.0;
		m_Exponent = ( -1 * int(Log1) );
		m_Mantissa = float (f / exp10 ( float(m_Exponent ) ) );
		return 1;
	}
	m_Exponent = 0;
	m_Mantissa = 1.0;
	return 1;
}


CVeryLong CVeryLong::operator+ (const CVeryLong& Rhs)
{	CVeryLong Sum;
	
	if (m_Mantissa == (float) 0) {
		Sum = Rhs;
		return Sum;
	}
	if (Rhs.GetMantissa () == 0) {
		Sum = *this;
		return Sum;
	}

	const int ExponentDifference = Rhs.GetExponent() - m_Exponent;
	if (ExponentDifference == 0 ) {
 		Sum.SetMantissa (m_Mantissa + Rhs.GetMantissa() );
		Sum.SetExponent (m_Exponent);
		return Sum;
	}
	if (ExponentDifference > 0) {
		Sum.SetExponent(Rhs.GetExponent() );
		Sum.SetMantissa ( Rhs.GetMantissa() + 
			m_Mantissa / exp10((float) ExponentDifference) );
		return Sum;		
	} else { //ExponentDifference < 0
		Sum.SetMantissa (m_Mantissa + 
			Rhs.GetMantissa() * exp10( (float) ExponentDifference) );		
		Sum.SetExponent(m_Exponent);
		return Sum;			
	}
};

double operator+= ( double& first, CVeryLong& second)
{
	CVeryLong vlFirst(first);
	vlFirst = vlFirst + second;
	return vlFirst.ToDouble();
}

void CVeryLong::operator+= (const CVeryLong& Rhs)
{	*this = *this + Rhs;
	return;
}



CVeryLong CVeryLong::operator* (const CVeryLong& Rhs)
{	
	CVeryLong	Product;
	float		Temp;
	
	Temp = m_Mantissa * Rhs.GetMantissa();  

	
	if (Temp >= 10) 
	{
		Product.SetMantissa ( Temp/10 ); 
		Product.SetExponent  (1);		 
	} else 
	{		 
		Product.SetMantissa(Temp);
		Product.SetExponent (0);		
	}
	
	Product.SetExponent (Product.GetExponent() + 
		m_Exponent +
		Rhs.GetExponent() ) ;
	return Product;
	
};


CVeryLong	CVeryLong::operator* (const double& Rhs)
{
	CVeryLong	Product,
				vlRhs (Rhs);

	return *this * vlRhs;
	

	

	

}



CVeryLong CVeryLong::operator/ (const CVeryLong& Rhs)
{	float	Log1=0;

	m_Mantissa /= Rhs.GetMantissa(); 
	Log1 = (float) log10(m_Mantissa); 
	if (Log1 < 0) {
		m_Mantissa *= 10; 
		m_Exponent--;		 
	} else if (Log1 > 0) {
		m_Mantissa /= 10;
		m_Exponent++;
	}	

	m_Exponent -= Rhs.GetExponent();
	return *this;
	
};
float	CVeryLong::GetMantissa() const {return m_Mantissa;};
int		CVeryLong::GetExponent() const {return m_Exponent;};

int CVeryLong::operator>> (double  & Rhs)
{
	if (m_Exponent < -308 || m_Exponent > 308) 
		{Rhs = 0;
		return 0;}
	else { 
		Rhs = m_Mantissa * exp10 ( (float) m_Exponent);
		return 1;
	}

}


int CVeryLong::operator> (const CVeryLong& Rhs)
{
	
	if (m_Exponent == Rhs.GetExponent()) 
	{
		return ( m_Mantissa > Rhs.GetMantissa() );
	} 
	else 
	{
		if (m_Exponent > Rhs.GetExponent() ) {
			return 1;
		} else {
			return 0;
		}
	}	
}
int CVeryLong::operator< (const CVeryLong& Rhs)
{	
	if (m_Exponent == Rhs.GetExponent()) 
	{
		return ( m_Mantissa < Rhs.GetMantissa() );
	} else {
		if (m_Exponent < Rhs.GetExponent() ) {
			return 1;
		} else {
			return 0;
		}
	}
}
int CVeryLong::operator> (const double& Rhs) 
{	
	CVeryLong A(Rhs);
	return ( *this > A ) ;
}

int CVeryLong::operator< (const double& Rhs)
{	CVeryLong A(Rhs);
	return ( *this > A );
}
int CVeryLong::operator> (const float & Rhs) 
{	
	if (Rhs == 0 && m_Mantissa > 0 )
	{
		return 1;
	}
	double a = (double) Rhs;
	return  *this > a;
};
int CVeryLong::operator< (const float & Rhs)
{	
	double a = (double) Rhs;
	return  *this < a;
};
 
int CVeryLong::operator== (const double & Rhs)
{
	CVeryLong A(Rhs);
	if (m_Mantissa == A.GetMantissa() &&
		m_Exponent == A.GetExponent() ) {
		return 1;
	} else {
		return 0;
	}
}
int CVeryLong::operator! () 
{	if (m_Mantissa == 0) {	return 1; }
	else    		   {   return 0;  }
}

double CVeryLong::ToDouble()
{
	return m_Mantissa * exp10 ((float) m_Exponent);	


}
QString CVeryLong::Display()
{
	QString Return = DisplayFloat( m_Mantissa ) + " * 10^^ " + DisplayInt( m_Exponent );

	return Return;
}
