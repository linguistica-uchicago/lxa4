// Monte Carlo algorithm for computing the denominator Z in a Boltzmann model
// Copyright © 2009 The University of Chicago
#include "MonteCarlo.h"

#include <cstdlib>
#include <Q3TextStream>

MonteCarlo::MonteCarlo(int size)		
{  
	m_Size = size;   
	m_Values.resize(size); 
	m_ReadyForAction = false; 
};

MonteCarlo::MonteCarlo(int size, QString MyFirstPhone)		
{  
	m_Size = size;   
	m_Values.resize(size); 
	m_ReadyForAction = false; 
	m_MyFirstPhone = MyFirstPhone;
};

void MonteCarlo::Dump( Q3TextStream* out )
{
	QString			FirstPhone, 
					SecondPhone;

	int				Size;

	MonteCarlo*		pConditionalMonteCarlo;


	*out << endl <<
		"MonteCarlo dump. Size: " << m_Size; 
	if (m_ReadyForAction ) 
	{
		*out << " Ready for action (normalized). ";
	}
	else
	{
		*out << " Not ready for action (normalized). ";
	}
	if (m_ModelType == UNIGRAM) { *out << endl <<"Model type is Unigram.\n"; };
	if (m_ModelType == BIGRAM)  { *out << endl <<"Model type is Bigram.\n" ;};

	
	*out << endl << "Top level links: ";
	for (int i = 0 ; i < m_Size; i++)
	{
		*out << i << "\t" << m_Keys[i] << "\t" << m_Values[i];
	}
	

	if (m_ModelType == BIGRAM)
	{		
		for (int i = 0; i < GetSize(); i++)
		{			
			Size = GetSize();
			
			pConditionalMonteCarlo = m_MyBigrams.find( m_MyFirstPhone );	
			*out << endl << "<<" << FirstPhone << ">>";		
			
			for (int j = 0; j < pConditionalMonteCarlo->GetSize();j++)
			{
				*out << "\n\t" << j << "\t" << m_Keys[j] << "\t" << m_Values[j];	
			}			
		}
	}






}


QString MonteCarlo::ReturnCharacter( )
{
	using std::rand;

	int i= 0;
	double random;


	if (m_ReadyForAction == false) Normalize();

	random = rand()/(double)0x7fff;

	for ( i = 0; i < m_Size; i++)
	{
//unused variable:
//		double temp ( m_Values[i]) ;
		if ( m_Values[i] > random ) break;
	}
	 
	return m_Keys[i];

}
QString MonteCarlo::ReturnCharacter( QString Char )
{
	using std::rand;

	int i= 0;
	double random;

	MonteCarlo*		pConditionalMonteCarlo;
	pConditionalMonteCarlo = m_MyBigrams.find( Char );	

	random = rand()/(double)0x7fff;

	for ( i = 0; i < m_Size; i++)
	{
//unused variable:
//		double temp ( pConditionalMonteCarlo->m_Values[i]) ;
		if	( pConditionalMonteCarlo->m_Values[i] > random ) break;
	}
	 
	return pConditionalMonteCarlo->m_Keys[i];

}
void	MonteCarlo::Normalize()
{
	double total = 0;
	int			i= 0;
	for (i = 0; i <m_Size; i++)
	{
		total += m_Values[i];
	}

	if (total != 1.0)
	{
		for (i = 0; i <m_Size; i++)
		{
			m_Values[i] /= total;
		}
		for (i = 1; i <m_Size; i++)
		{
			m_Values[i] += m_Values[i-1];
		}
	}
	//check to see if collection includes #; if not, do not say it's ready for action.

	m_ReadyForAction = true;

}

CParse	MonteCarlo::ReturnString(CParse& String)
{
	QString Char, Char2;
	QString temp;
	String.ClearParse();
	String.Append(QChar('#'));
	
	Char = "#";
	while (TRUE)
	{
		Char2 = ReturnCharacter ( Char );
		if (Char2.length() == 0) continue;
		String.Append( Char2);
		temp = String.Display();
		if (Char2 == "#") break;
		Char = Char2;
	}
	
	QString temp2 = String.GetPiece(2).Display();
	
	return String;
}
