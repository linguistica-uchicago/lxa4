// long double workalike
// Copyright © 2009 The University of Chicago
#ifndef VERYLONG_H
#define VERYLONG_H

#include <qstring.h>

int			AssignFromVeryLongToDouble ( class CVeryLong&, double& );
void		IncrementDoubleByVeryLong ( double&, class CVeryLong& );

/// deprecated. Please use “long double” instead.
class CVeryLong 
{
	float	m_Mantissa; //between 1 and 10
	int		m_Exponent; // may be negative

	

public:
				CVeryLong();
				CVeryLong( const CVeryLong& );
				CVeryLong( const double );
				~CVeryLong();
				
	CVeryLong	operator+( const CVeryLong& );	
	CVeryLong	operator*( const CVeryLong& );	
	CVeryLong	operator*( const double& );
	CVeryLong	operator/( const CVeryLong& );
	CVeryLong	operator/( const double& );

	int			operator=( const double & );
	void		operator=( const CVeryLong& );
	int			operator>>( double& );
	void		operator+=( const CVeryLong& );
	int			operator!();

	int			operator>( const CVeryLong& );
	int			operator<( const CVeryLong& );
	int			operator>( const double& );
	int			operator<( const double& );
	int			operator>( const float& );
	int			operator<( const float& );
	int			operator==( const double& );

	QString		Display();
	 
	float		GetMantissa() const;
	void		SetMantissa( float );
	int			GetExponent() const;
	void		SetExponent( int );

	double		ToDouble();

};


#endif // VERYLONG_H
