// Implementation of CLexicon’s core methods
// Copyright © 2009 The University of Chicago
#include "Lexicon.h"

#include "Config.h"
#include <iostream>
#include <memory>
#include <Q3TextStream>
#include <QMessageBox>
#include <QTime>
#include <QList>
#include <QString>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "LPreferences.h"
#include "DLHistory.h"
#include "StateEmitHMM.h"
#include "CorpusWord.h"
#include "Linker.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Stem.h"
#include "CorpusWordCollection.h"
#include "SignatureCollection.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "generaldefinitions.h"
#include "ScrubRules.h"
#include "Typedefs.h"
#include "Slice.h"

class CCorpusWord;


namespace {
	QString escapes(QString start)
	{
		QString end = start;

		end.replace( "[", "\\[" );
		end.replace( "]", "\\]" );
		end.replace( "(", "\\(" );
		end.replace( ")", "\\)" );
		end.replace( "!", "\\!" );
		end.replace( "?", "\\?" );
		end.replace( "^", "\\^" );
		end.replace( "$", "\\$" );

		return end;
	}

	eStemType FindType( QString word )
	{
		int HyphenCount = 0;
		int PuncCount = 0;
		int NumberPunc = 0;
		int DigitCount = 0;

		int Length = word.length();

		for ( int i = 0; i < Length; i++)
		{
			if( word[i].category() == QChar::Punctuation_Dash )
			{
				HyphenCount++;
			}

			if( word[i].isPunct() )
			{
				PuncCount++;
			}

			if( word[i] == '.' ||
				word[i] == ',' ||
				word[i].category() == QChar::Symbol_Currency ||
				word[i].isNumber() )
			{
				NumberPunc ++;
			}

			if( word[i].isDigit() )
			{
				DigitCount++;
			}
		}

		if( DigitCount == 0 && HyphenCount == 0 && PuncCount == 0 )
		{
			return NORMAL;
		}

		if( Length > 2 && HyphenCount == 1 && PuncCount == 1 )
		{
			if( DigitCount > 0 && DigitCount == Length - 1 ) return NUMBER;
			return BIWORD_COMPOUND;
		}

		if( DigitCount > 0 && DigitCount + NumberPunc >= Length )
		{
			return NUMBER;
		}

		if( Length > 3 && HyphenCount > 1 && PuncCount == HyphenCount )
		{
			return MULTIPLE_COMPOUND;
		}

		return UNKNOWN;
	}

	namespace primes {
		const int NUM_PRIMES = 1229;
		const int NUM_PRIME_STEPS = 38;
		const int LARGE_NON_PRIME = 99460729;
		const int LARGER_PRIME = 99460747;
		const int LARGEST_PRIME_STEP = 10000019;

		int getNextPrime( int number )
		{
			int i, j;
			int primes[NUM_PRIMES] = {	2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
										31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
										73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
										127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
										179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
										233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
										283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
										353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
										419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
										467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
										547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
										607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
										661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
										739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
										811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
										877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
										947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
										1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
										1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
										1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
										1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
										1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
										1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
										1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
										1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
										1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
										1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733,
										1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
										1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
										1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
										1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053,
										2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
										2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213,
										2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
										2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357,
										2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
										2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531,
										2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
										2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
										2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
										2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819,
										2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903,
										2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999,
										3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
										3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181,
										3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257,
										3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331,
										3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
										3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511,
										3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571,
										3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643,
										3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
										3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821,
										3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907,
										3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989,
										4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
										4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139,
										4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231,
										4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297,
										4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
										4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493,
										4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583,
										4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657,
										4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
										4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
										4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937,
										4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003,
										5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,
										5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179,
										5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279,
										5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387,
										5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,
										5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521,
										5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639,
										5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693,
										5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,
										5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857,
										5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
										5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053,
										6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,
										6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221,
										6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301,
										6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367,
										6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,
										6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571,
										6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673,
										6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761,
										6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,
										6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917,
										6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997,
										7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
										7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,
										7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297,
										7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411,
										7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499,
										7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,
										7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643,
										7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723,
										7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829,
										7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,
										7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017,
										8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111,
										8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219,
										8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291,
										8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387,
										8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501,
										8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573, 8581, 8597,
										8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677,
										8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741,
										8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831,
										8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929,
										8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001, 9007, 9011,
										9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109,
										9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199,
										9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277, 9281, 9283,
										9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377,
										9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439,
										9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533,
										9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631,
										9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719, 9721, 9733,
										9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811,
										9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887,
										9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973 };

			if( number >= LARGE_NON_PRIME ) return LARGER_PRIME;

			if( number > primes[ NUM_PRIMES - 1 ] )
			{
				for( i = 0; i < number; i++ )
				{
					for( j = 0; j < NUM_PRIMES; j++ )
					{
						if( ( number + i ) % j == 0 ) continue;
						if( j * j >= number + i ) return number + i;
					}
				}
			}
			else
			{
				for( i = 0; i < NUM_PRIMES; i++ )
				{
					if( primes[i] > number ) return primes[i];
				}
			}

			return 0;
		}

		int getPrevPrime( int number )
		{
			int i, j;
			int primes[NUM_PRIMES] = {	2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
										31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
										73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
										127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
										179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
										233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
										283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
										353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
										419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
										467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
										547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
										607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
										661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
										739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
										811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
										877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
										947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
										1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
										1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
										1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
										1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
										1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
										1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
										1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
										1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
										1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
										1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733,
										1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
										1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
										1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
										1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053,
										2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
										2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213,
										2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
										2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357,
										2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
										2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531,
										2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
										2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
										2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
										2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819,
										2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903,
										2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999,
										3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
										3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181,
										3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257,
										3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331,
										3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
										3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511,
										3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571,
										3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643,
										3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
										3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821,
										3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907,
										3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989,
										4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
										4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139,
										4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231,
										4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297,
										4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
										4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493,
										4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583,
										4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657,
										4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
										4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
										4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937,
										4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003,
										5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,
										5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179,
										5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279,
										5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387,
										5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,
										5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521,
										5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639,
										5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693,
										5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,
										5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857,
										5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
										5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053,
										6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,
										6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221,
										6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301,
										6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367,
										6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,
										6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571,
										6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673,
										6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761,
										6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,
										6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917,
										6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997,
										7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
										7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,
										7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297,
										7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411,
										7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499,
										7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,
										7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643,
										7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723,
										7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829,
										7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,
										7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017,
										8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111,
										8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219,
										8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291,
										8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387,
										8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501,
										8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573, 8581, 8597,
										8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677,
										8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741,
										8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831,
										8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929,
										8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001, 9007, 9011,
										9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109,
										9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199,
										9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277, 9281, 9283,
										9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377,
										9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439,
										9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533,
										9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631,
										9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719, 9721, 9733,
										9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811,
										9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887,
										9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973 };

			if( number > LARGER_PRIME ) return LARGER_PRIME;

			if( number > primes[ NUM_PRIMES - 1 ] )
			{
				for( i = number - 1; i >= primes[ NUM_PRIMES - 1 ]; i-- )
				{
					for( j = 0; j < NUM_PRIMES; j++ )
					{
						if( i % j == 0 ) continue;
						if( j * j >= i ) return i;
					}
				}
			}
			else
			{
				for( i = NUM_PRIMES - 1; i >= 0; i-- )
				{
					if( primes[i] < number ) return primes[i];
				}
			}

			return 0;
		}

		int getNextPrimeStep( int number )
		{
			int prime_steps[NUM_PRIME_STEPS] = { 17, 37, 67,
												 131, 257, 521,
												 1031, 2053, 4099, 8209,
												 10007, 20011, 30011, 40009, 50021, 60013, 70001, 80021, 90001,
												 100003, 200003, 300007, 400009, 500009, 600011, 700001, 800011, 900001,
												 1000003, 2000003, 3000017, 4000037, 5000011, 6000011, 7000003, 8000009, 9000011,
												 10000019 };

			for( int i = 0; i < NUM_PRIME_STEPS; i++ )
			{
				if( prime_steps[i] > number ) return prime_steps[i];
			}

			return getNextPrime( number );
		}

		int getPrevPrimeStep( int number )
		{
			if( number < 17 ) return 17;

			int prime_steps[NUM_PRIME_STEPS] = { 17, 37, 67,
												 131, 257, 521,
												 1031, 2053, 4099, 8209,
												 10007, 20011, 30011, 40009, 50021, 60013, 70001, 80021, 90001,
												 100003, 200003, 300007, 400009, 500009, 600011, 700001, 800011, 900001,
												 1000003, 2000003, 3000017, 4000037, 5000011, 6000011, 7000003, 8000009, 9000011,
												 10000019 };

			for( int i = NUM_PRIME_STEPS - 1; i >= 0; i-- )
			{
				if( prime_steps[i] < number ) return prime_steps[i];
			}

			return getPrevPrime( number );
		}
	}
	using namespace primes;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/** \page page1 How to add a variable to the User Preference Window
  
  \section sec The main screen
  In the Lexicon.cpp file, the main constructor function: 

  CLexicon( LinguisticaMainWindow* pDoc )
  
  has a   block of code following the comment: 
  Set parameter defaults for all lexicon functions; 
  each line takes the form:

  m_ParamDefaults["Main\\MinimumMorphemeLength"] = "2".
  
  These lines create the entries in the Windows Registry which can be used for Linguistica to read from
  in various functions. So you have to do two things: add a line to this block of code, and also
  add a line of code in a function where you want a variable to get its value from the Registry. Such
  a line of code would look like this:

  int LoopLimit = m_pLexicon->GetIntParameter( "CheckSignatures\\LoopLimit", 1 ); 	

  You'll be calling a Linguisitica function "GetIntParameter", which returns an int from a hash.

  If you want to get a QString rather than an int, you use the function "GetStringParameter".

*/


CLexicon::CLexicon(LinguisticaMainWindow* pDoc)
	: m_pDoc(pDoc),
	m_ParamDefaults(),	// initialized below

	m_Corpus(),
	m_pCorpusWords(new CCorpusWordCollection(this)),
	m_CorpusMap(),



	m_pMiniLexica(new Q3PtrVector<CMiniLexicon>(4)) /* initialized below */,
	m_ActiveMini(-1),
	m_WordUpdates(),
	// Global morpheme collections
	m_AllPrefixes(),	// initialized below
	m_AllPrefixSigs(),	// initialized below
	m_AllStems(),	// initialized below
	m_AllSuffixes(),	// initialized below
	m_AllSuffixSigs(),	// initialized below
	m_AllWords(),	// initialized below

	m_pCompounds(new CCompoundCollection(this)),
	m_pLinkers(new CLinkerCollection(this)),
	m_CompoundUpdates(),

	m_pInFilter(),
	m_pOutFilter(),

	m_NumberOfCharacterTypes(26),
	m_tokenCount(0),
	m_pDLHistory(new CDLHistory(this)),
	m_DescriptionLength(),

        m_pSEDWords(new CWordCollection()),

	m_HMM(NULL)
{
	// Set parameter defaults for all lexicon functions
	m_ParamDefaults["Neighbors\\DifferenceThreshold"] = "2";
	m_ParamDefaults["Main\\MinimumMorphemeLength"] = "2";
	m_ParamDefaults["Main\\MinimumStemLength"] = "3";
	m_ParamDefaults["Main\\MaximumPrefixLength"] = "5";
	m_ParamDefaults["Main\\MinimumPrefixLength"] = "2";
	m_ParamDefaults["Main\\MaximumSuffixLength"] = "5";
	m_ParamDefaults["Main\\MinimumSuffixLength"] = "2";
	m_ParamDefaults["Main\\MinimumSignatureLength"] = "1";
	m_ParamDefaults["Main\\MaxSuccessorFreqScoreByNeighbor"] = "1";
	m_ParamDefaults["Main\\MinimumNumberOfStemsInSignature"] = "1";
	m_ParamDefaults["Main\\MinimumSuccessorFrequency"] = "6";
	m_ParamDefaults["Main\\VerboseDisplayFlag"] = "1";
	m_ParamDefaults["Main\\MaximumNumberOfMiniLexica"] = "1";
	m_ParamDefaults["CheckSignatures\\LoopLimit"] = "1";
	m_ParamDefaults["CheckSignatures\\StemCountThreshold"] = "2";
	m_ParamDefaults["PredecessorFrequency\\MaxNeighborPredecessorCount"] = "1";
	m_ParamDefaults["PredecessorFrequency\\MinimumNumberOfAppearancesOfPrefix"] = "3";
	m_ParamDefaults["PredecessorFrequency\\MinimumNumberOfStemsInSignature"] = "2";
	m_ParamDefaults["PredecessorFrequency\\MinimumLengthOfSignature"] = "2";
	m_ParamDefaults["PredecessorFrequency\\LengthOfAStrongSignature"] = "4";
	m_ParamDefaults["PredecessorFrequency\\LargeNumberOfStems"] = "25";
	m_ParamDefaults["PredecessorFrequency\\MinimumNumberOfPrefixes"] = "2";
	m_ParamDefaults["PredecessorFrequency\\MaximumPrefixLength"] = "5";
	m_ParamDefaults["SuccessorFreq1\\MaxNeighborSuccessorCount"] = "1";
	m_ParamDefaults["SuccessorFreq1\\MinimumNumberOfAppearancesOfSuffix"] = "3";
	m_ParamDefaults["SuccessorFreq1\\MinimumNumberOfStemsInSignature"] = "2";
	m_ParamDefaults["SuccessorFreq1\\MinimumLengthOfSignature"] = "2";
	m_ParamDefaults["SuccessorFreq1\\LengthOfAStrongSignature"] = "4";
	m_ParamDefaults["SuccessorFreq1\\LargeNumberOfStems"] = "25";
	m_ParamDefaults["SuccessorFreq1\\MaxSuccessorFreqScoreByNeighbor"] = "1";
	m_ParamDefaults["TakeSignaturesFindStems\\SizeThreshold"] = "2";
	m_ParamDefaults["TakeSignaturesFindStems\\StemCountThreshold"] = "2";
	m_ParamDefaults["TakeSignaturesFindStems\\SignatureRobustnessThreshold"] = "10";
	m_ParamDefaults["FromStemsFindSuffixes\\RobustnessThreshold"] = "10";
	m_ParamDefaults["FromStemsFindSuffixes\\MinimumNumberOfOccurrences"] = "3";
	m_ParamDefaults["Compounds\\MaximumLinkerLength"] = "0";
	m_ParamDefaults["SignatureDL\\CorpusBasedAffixCount"] = "0";
	m_ParamDefaults["SignatureDL\\CorpusBasedStemCount"] = "1";
	m_ParamDefaults["HMM\\NumberOfStates"] = "2";
	m_ParamDefaults["HMM\\NumberOfIterations"] = "25";
	m_ParamDefaults["EarleyParser\\MaximumParseDepth"] = "6";
	m_ParamDefaults["Boltzmann\\NumberOfSamples"] = "100";
	m_ParamDefaults["Symbols\\Vowels"] = "a e i o u A E I O U";

	m_CorpusMap.setAutoDelete(false);	// m_pCorpusWords owns these
	m_pMiniLexica->setAutoDelete(true);
//	m_WordUpdates.setAutoDelete(false);	// mini-lexica own these -- no autodelete in Qt4's QList
	m_AllPrefixes.setAutoDelete(true);
	m_AllPrefixSigs.setAutoDelete(true);
	m_AllStems.setAutoDelete(true);
	m_AllSuffixes.setAutoDelete(true);
	m_AllSuffixSigs.setAutoDelete(true);
	m_AllWords.setAutoDelete(true);

	m_SuffixalBiSignatures = NULL;
	m_PrefixalBiSignatures = NULL; 

	// Compare default parameters to user params
	QMap<QString, QString> params;
	CLPreferences& prefs = *m_pDoc->GetPreferences();

	prefs.GetDictionaryPreference("Lxa_Parameters", &params);
	for (QMap<QString, QString>::const_iterator iter = m_ParamDefaults.begin();
			iter != m_ParamDefaults.end(); ++iter) {
		const QString key = iter.key();

		if (!params.contains(key))
			params.insert(key, iter.value());
	}
	prefs.SetDictionaryPreference("Lxa_Parameters", params);
}

CLexicon::~CLexicon()
{
	// The mini-lexicon destructor requires a valid lexicon to
	// work with, and in particular the preceding mini-lexica
	// must still be valid.  It would be nice to just use the
	// Q3PtrVector destructor, but it deletes its items in the
	// wrong order (first-to-last instead of last-to-first).
	for (int i = m_pMiniLexica->size() - 1; i >= 0; --i)
		m_pMiniLexica->remove(static_cast<unsigned int>(i));

	delete m_pMiniLexica;
	delete m_pCorpusWords;
	delete m_pCompounds;
	delete m_pLinkers;
	delete m_pInFilter;
	delete m_pOutFilter;
	delete m_pDLHistory;
	delete m_pSEDWords;
	delete m_HMM;

}


void CLexicon::AddToScreen( QString text )
{
  m_pDoc->m_commandLine->setText( text );
}


void CLexicon::ClearScreen()
{
  m_pDoc->m_commandLine->setText ("");
}

void CLexicon::FindSuffixalBiSignatures()
{
	CCorpusWord* 		pWord;
	CSignature* 		pSig;	
	m_SuffixalBiSignatures = new CSignatureCollection();
	
	for (int i = 0; i < m_pCorpusWords->GetCount(); i++) {
		pWord = m_pCorpusWords->GetAt(i);		
	}
}	

void CLexicon::FindPrefixes( bool AutoLayer )
{
  CMiniLexicon* mini;
  int index = 0;

 //unused variable:  const int LayerCount = GetIntParameter( "Main\\MaximumNumberOfMiniLexica", 1 );

  if( m_ActiveMini >= 0 )
  {
    if( LogFileOn() )
    {
       *GetLogFileStream() << endl << endl 
                      << QString("MINI-LEXICON %1").arg(m_ActiveMini+1) << endl;
    }

    if( !(*m_pMiniLexica)[m_ActiveMini]->FindPrefixes() )
    {
      // The active mini may already have a suffix analysis
      if( (*m_pMiniLexica)[m_ActiveMini]->GetStems()->GetCount() )
      {
        index = NewMiniLexicon();
        mini = GetMiniLexicon( index );
        if( mini && mini->SetAffixLocation( STEM_INITIAL ) )
          mini->AddToWordCollection( GetMiniLexicon( m_ActiveMini )->GetWords() );
      }
      else
      {
        mini = (*m_pMiniLexica)[m_ActiveMini];
        mini->SetAffixLocation( STEM_INITIAL );
      }

      mini->FindPrefixes();

      SetActiveMiniIndex( index );
    }

    if( AutoLayer )
    {
      while (1)
      {
        index = NewMiniLexicon();
        mini = GetMiniLexicon( index );
        mini->AddToWordCollection( GetMiniLexicon( index-1 )->GetWords() );
        mini->AddToWordCollection( GetMiniLexicon( index-1 )->GetStems() );

/*        if( LogFileOn() )
        {
          *GetLogFileStream() << endl << endl << "================================================================" << endl
                        << QString("MINI-LEXICON %1").arg(index+1) << endl
                        << "================================================================" << endl << endl;
        }
*/
        mini->FindPrefixes();

        if( mini && mini->GetSignatures()->GetSize() < 1 )
        {
          DeleteMiniLexicon( index );
          break;
        }
      }
    }
  }
}


void CLexicon::FindSuffixes( bool AutoLayer )
{
	if (m_ActiveMini < 0)
		// No mini-lexicon selected
		return;

	// XXX. Log which mini-lexicon this is

	CMiniLexicon& active_mini = *GetMiniLexicon(m_ActiveMini);

	if (active_mini.FindSuffixes() == 0) {
		int index;
		// The active mini may already have a prefix analysis
		if (active_mini.GetStems()->GetCount() != 0) {
			index = NewMiniLexicon();
			CMiniLexicon* pMini = GetMiniLexicon(index);
			pMini->AddToWordCollection(active_mini.GetWords());
		} else {
			index = m_ActiveMini;
			active_mini.SetAffixLocation( STEM_FINAL );
		}

		CMiniLexicon& mini = *GetMiniLexicon(index);
		mini.FindSuffixes();
		mini.CalculateDescriptionLength();
		SetActiveMiniIndex(index);
	}

	// avoid infinite loop
	// XXX. Add a better termination condition.
	const unsigned int layer_max = 100;

	if (AutoLayer)
		for (unsigned int layer = layer_max; layer != 0; --layer) {
			int index = NewMiniLexicon();
			CMiniLexicon& mini = *GetMiniLexicon(index);
			CMiniLexicon& prev = *GetMiniLexicon(index - 1);

			mini.AddToWordCollection(prev.GetWords());
			mini.AddToWordCollection(prev.GetStems());

			// XXX. Log which mini-lexicon this is.

			mini.FindSuffixes();

			if (mini.GetSignatures()->GetSize() == 0) {
				DeleteMiniLexicon(index);
				break;
			}
		}
}

int CLexicon::Tokenize( QStringList& lines, StringToInt& tokens )
{
	QString token;
	int token_count = 0;

	foreach (QString line_text, lines) {
		QTextStream line(&line_text, QIODevice::ReadOnly);
		while (!line.atEnd()) {
			line >> token;
			// If the tokenization becomes more sophisticated than 'break at space', this is where it should be defined
			tokens[token]++;
			token_count++;
		}
	}
	return token_count;
}



int CLexicon::ReadDX1File(QString FileName, int NumberOfWords )
{
	QString		line;
	CParse		prsLine;
//unused variable:		
//  int			token_count = 0;
	CSS			Spelling;
//unused variable:
//	int			corpuscount = 0;
	CStem*		pWord;
	CWordCollection*	Words;
	CCorpusWord* pCorpusWord;


	m_pDoc->setStatusBar1( QString ("Reading dictionary word list.") );
	ClearAll();

	if (NumberOfWords < 0) { NumberOfWords = 1000000; }

	// Add the base mini lexicon
	CMiniLexicon* mini = new CMiniLexicon( this, 0 );
	m_ActiveMini = 0;
	m_pMiniLexica->insert( 0, mini );
	m_pMiniLexica->setAutoDelete( true );
	Words = mini->GetWords();

	Q_ASSERT( !FileName.isEmpty() );
	QFile File( FileName );
	if (!File.open(QIODevice::ReadOnly))
		return 1;

	Q3TextStream stream(&File);

	// Unicode or ASCII encoding? Depends on corpus file.
	stream.setEncoding ( Q3TextStream::Locale );

	m_pDoc->BeginCountDown();

	int wordcount = 1;
	for (; wordcount < NumberOfWords + 1; ++wordcount) {
		if (stream.atEnd())
			break;
		QString line = stream.readLine().simplifyWhiteSpace();

		// Add line to corpus
		m_Corpus.append( line );

		prsLine.Collapse(CSS (line) );

		// Add to mini word list
		pWord = *Words <<   prsLine[1].Display();
		//pWord->SetCorpusCount( prsLine[2] );
		pWord->SetCorpusCount ( 1 );

		// Add corpus word
		pCorpusWord = *m_pCorpusWords << pWord->GetKey();
		m_CorpusMap.insert( prsLine[1].Display(), pCorpusWord );
		m_pCorpusWords->IncrementCorpusCount( pWord->GetCorpusCount() - 1 ); // already incremented one in operator<<
		pCorpusWord->IncrementCorpusCount( pWord->GetCorpusCount() - 1 );

		// Remove the two non phonology pieces and set
		// the phonology tier
		prsLine.RemovePiece(1);
		prsLine.RemovePiece(1);
		pWord->SetPhonology_Tier1 ( &prsLine );
	}
	return wordcount; 
}



int CLexicon::ReadCorpus(QString FileName, int NumberOfWords)
{
	Q_ASSERT(!FileName.isEmpty());

	QTime t;
	t.start();

	if (FileName.right(4) == ".dx1")
		return ReadDX1File(FileName, NumberOfWords);

	m_pDoc->setStatusBar1(QString("Reading corpus "));
	m_tokenCount = 0;

	const int MinStemLength = GetIntParameter( "Main\\MinimumStemLength", 3 );
	// XXX. use Lower_Case preference?

	// Remove everything from Lexicon
	m_pCorpusWords->Empty();
	ClearAll();

	// Add the base mini lexicon
	std::auto_ptr<CMiniLexicon> new_mini(new CMiniLexicon(this, 0));
	CMiniLexicon* mini = new_mini.get();
	m_ActiveMini = 0;
	Q_ASSERT(m_pMiniLexica->autoDelete());
	m_pMiniLexica->insert(0, new_mini.release());
	CWordCollection* Words = mini->GetWords();

	// Set up filters
	m_pInFilter = 0;
	m_pOutFilter = 0;
	QStringList items;
	m_pDoc->GetPreferences()->GetStringListPreference(
			"Character_Combinations", &items);
	SetFilters(&items);

	// Read file.
	{
		Q_ASSERT(!FileName.isEmpty());
		QFile File(FileName);
		if (!File.open(QIODevice::ReadOnly))
			return -1;

		QTextStream stream(&File);
		stream.setCodec(QTextCodec::codecForName("UTF-8"));
		Q_ASSERT(stream.autoDetectUnicode());

		m_pDoc->setStatusBar1("Reading word tokens from corpus...");
		m_pDoc->BeginCountDown();

		while (!stream.atEnd() && m_tokenCount <= NumberOfWords) {
			m_pDoc->CountDownOnStatusBar(m_tokenCount,
					NumberOfWords, NumberOfWords/100);

			QString line = stream.readLine().trimmed();

			// Deal with line-final dashes
			if (line.endsWith("-")) {
				QString action = m_pDoc->GetPreferences()
					->GetPreference("Line_Final_Dash");
				if (action.isEmpty())
					action = "Join_With_Dash";

				if (action == "Do_Not_Join")
					// Do nothing:
					// dashes should be handled by scrubbing.
					;
				else if (!stream.atEnd()) {
					QString next;
					stream >> next;

					if (action == "Join_Without_Dash")
						line.truncate(line.length() - 1);

					line += next;
				}
			}

			m_tokenCount += line.count(' ') + 1;
			m_Corpus.append(line);
		}
	}

	// Tokenize
	QMap<QString, int> types;
	Tokenize(m_Corpus, types);

	// Prepare scrubbing
	QStringList scrubRules;
	m_pDoc->GetPreferences()->GetStringListPreference(
		"Scrub_Replacements", &scrubRules);

	QMap<QString, QString> replacements;
	QStringList regExps;
	QRegExp preceding, internal, following;
	const QString arrow_str = " --> ";
	for (QStringList::const_iterator iter = scrubRules.begin();
			iter != scrubRules.end(); ++iter) {
		const QString rule = *iter;
		int arrow = rule.lastIndexOf(arrow_str);

		if (arrow != -1) {
			Q_ASSERT(arrow >= 0);
			Q_ASSERT(rule.lastIndexOf(arrow_str, arrow - 1) == -1);

			const QString lhs = rule.left(arrow);
			const QString rhs = rule.mid(arrow + arrow_str.size());
			regExps.append(lhs);
			replacements.replace(lhs, rhs);
			continue;
		}

		regExps.append(rule);
		if (rule == SCR_REMOVE_PRECEDING_PUNCT) {
			++iter;
			preceding = QRegExp(QString("^[%1]+")
					.arg(escapes(*iter)));
		} else if (rule == SCR_REMOVE_INTERNAL_PUNCT) {
			++iter;
			internal = QRegExp(QString("(\\S)[%1]+(\\S)")
					.arg(escapes(*iter)));
		} else if (rule == SCR_REMOVE_FOLLOWING_PUNCT) {
			++iter;
			following = QRegExp(QString("[%1]+$")
					.arg(escapes(*iter)));
		}
	}

	m_pDoc->setStatusBar1( "Processing word types..." );
	m_pDoc->BeginCountDown();

	// Process types individually
	int words = 0;
	int maxNumberOfRoots = 2;
	QMap<QChar,int>	allChars;
        QList<CStem*> dashCompounds, dashComponents;
	for (QMap<QString, int>::const_iterator iter = types.begin();
			iter != types.end(); ++iter, ++words) {
		QString word = iter.key();
		if (word.isEmpty())
			continue;

		m_pDoc->CountDownOnStatusBar(words,
			types.size(), types.size()/100);

		// Scrub word
		const QRegExp numeral("[0-9]");
		foreach (QString regexp, regExps) {
			if (regexp == SCR_MAKE_LOWER_CASE)
				word = word.lower();
			else if (regexp == SCR_REMOVE_NUMBERS)
				word.replace(numeral, "");
			else if (regexp == SCR_REMOVE_PRECEDING_PUNCT)
				word.replace(preceding, "");
			else if (regexp == SCR_REMOVE_INTERNAL_PUNCT)
				word.replace(internal, "\\1\\2");
			else if (regexp == SCR_REMOVE_FOLLOWING_PUNCT)
				word.replace(following, "");
			else
				word.replace(QRegExp(regexp),
					replacements[regexp]);
		}

		// Combine n-graph combos into single character
		word = Filter(m_pInFilter, word);

		if (word.isEmpty())
			continue;

		// Process words with internal dashes according to user preferences
		int dashPos = word.indexOf('-');
		const bool hasDash = (dashPos != -1);

		const QString wordInternalDash = m_pDoc->GetPreferences()
				->GetPreference("Word_Internal_Dash");
		const QString wordWithDash = m_pDoc->GetPreferences()
				->GetPreference("Word_With_Dash");

		bool pieceTooShort = false;
		if (hasDash) {
			QStringList pieces = QStringList::split('-', word, true);
			foreach (QString piece, pieces) {
				if (piece.size() < MinStemLength) {
					pieceTooShort = true;
					break;
				}
			}
		}

		const bool split_at_dash =
			(wordWithDash == "Include_Substrings_Only" ||
			wordWithDash == "Include_Full_Word_And_Substrings");
		if (hasDash && !pieceTooShort && split_at_dash) {
			int dashCount = word.count('-');
			if (dashCount > maxNumberOfRoots)
				maxNumberOfRoots = dashCount + 1;

			QString components = word;

			for (; !components.isEmpty();
					dashPos = components.indexOf('-')) {
				QString component;

				if (dashPos != -1) {
					component = components.left(dashPos);
					components = components.mid(dashPos + 1);
				} else {
					component = components;
					components = "";
				}

				if (!component.isEmpty()) {
					dashPos = components.indexOf('-');
					continue;
				}

				foreach (QChar ch, component)
					++allChars[ch];

				CStem stem(component, mini);
				CStem* pWord = *Words << stem;
				// operator<< already incremented the corpus
				// counts by 1, but that wasn’t right --- so
				// we adjust.
				Words->IncrementCorpusCount(iter.value() - 1);
				pWord->IncrementCorpusCount(iter.value() - 1);

				pWord->SetWordType(FindType(component));
				pWord->IncrementCompoundCount();
				dashComponents.append(pWord);
				*m_pSEDWords << stem;
			}
		}

		if (!hasDash || wordWithDash != "Include_Substrings_Only") {
			if (hasDash && wordInternalDash == "Remove")
				word = word.replace('-', "");

			foreach (QChar ch, word)
				++allChars[ch];

			CStem stem(word, mini);
			CStem* pWord = *Words << stem;
			// operator<< already incremented the corpus
			// counts by 1, but that wasn’t right --- so
			// we adjust.
			Words->IncrementCorpusCount(iter.value() - 1);
			pWord->IncrementCorpusCount(iter.value() - 1);

			pWord->SetWordType(FindType(word));
			if (hasDash && wordInternalDash != "Remove" &&
					!pieceTooShort)
				dashCompounds.append(pWord);
			*m_pSEDWords << stem;

			CCorpusWord* pCorpusWord =
				*m_pCorpusWords << pWord->GetKey();
			// operator<< already incremented the corpus
			// counts by 1, but that wasn’t right.
			m_pCorpusWords->IncrementCorpusCount(iter.value() - 1);
			pCorpusWord->IncrementCorpusCount(iter.value() - 1);

			pCorpusWord->SetMorpheme(1, pWord);
			m_CorpusMap.insert(iter.key(), pCorpusWord);
		}
	}

	// Connect compounds to word components and create parses
	if (!dashCompounds.isEmpty() && !dashComponents.isEmpty()) {
		FromStemsFindFlatCompounds(&dashCompounds,
			&dashComponents, "-", maxNumberOfRoots);
//		m_pCompounds->FindMostProbableParse();
	}

	m_NumberOfCharacterTypes = allChars.count();

	Words->GetTrie()->Alphabetize();
	// phonology: move this eventually to the menu -- JG
	mini->GetWords()->DoPhonology();

	m_pDoc->EndCountDown();
	m_pDoc->setStatusBar1("");
	m_pDoc->setStatusBar2("");

	Words->SetSortStyle(KEY);

  //Moved code to FindSlicesSlot in linguisticamainwindow
  /*
        //experiment with Slices: summer 2009. JG.
        if (FALSE)
        {
            SliceCollection MySlices;
            StringInventory MyStringInventory;
            m_pDoc->setStatusBar1("Finding slices...");
            MyStringInventory.addwordcollection(Words, MySlices, m_pDoc);

            if (LogFileOn()) { MySlices.writetolog(*GetLogFileStream());}

            MySlices.FindWordPairs(m_pDoc, this);

        }
  */

	// Add description length to history
	const QString mini_name("Mini-Lexicon 1");
	const QString remark("Before analysis; words only");
	m_pDLHistory->append(mini_name, remark, mini);

	std::cout << "ReadCorpus:: Time elapsed: " <<
		t.elapsed() << "ms." << std::endl;
	return 0;
}

int CLexicon::RereadCorpus(QString FileName, int NumberOfWords)
{
	Q_ASSERT(!FileName.isEmpty());
	ClearAll();
	return ReadCorpus(FileName, NumberOfWords);
}



void CLexicon::ClearAll()
{
	CMiniLexicon* mini;
	
	// Clear all MiniLexica
	for( int i = m_pMiniLexica->size()-1; i >= 0; i-- )
	{
		mini = m_pMiniLexica->take(i);
		if( mini )
		{
			mini->ClearAll();
			delete mini;
		}
	}
	
	m_AllPrefixes	.clear();
	m_AllPrefixSigs	.clear();
	m_AllStems		.clear();
	m_AllSuffixes	.clear();
	m_AllSuffixSigs	.clear();
	m_AllWords		.clear();
	m_pCompounds	->Empty(); delete m_pCompounds;
	m_pCompounds	= new CCompoundCollection( this );
	m_pLinkers		->Empty(); delete m_pLinkers;
	m_pLinkers		= new CLinkerCollection( this );
	m_Corpus		.clear();
	m_CorpusMap		.clear();
	m_pCorpusWords	->Empty();
	
	if( m_pDLHistory ) delete m_pDLHistory;
	m_pDLHistory	= new CDLHistory( this );
	if ( m_HMM) 
	{	
		delete m_HMM;
		m_HMM = NULL;
	}
}


CCorpusWord*  CLexicon::FindAWord( CStem* pStem, CSuffix* pSuffix )
{
	QString Word = pStem->Display();

	if ( !pSuffix->GetKey().IsNULL() )
	{
		Word += pSuffix->Display();
	}

	return *m_pCorpusWords ^= Word;
}


int CLexicon::ReadProjectFile( QString FileName )
{
	Q_ASSERT( !FileName.isEmpty() );
	QFile   file( FileName );

	QString	buffer;

	int    	usedTokens,
			types,
			minis;

	if( file.exists() && file.open( QIODevice::ReadOnly ) )
	{
		Q3TextStream inf(&file);
		inf.setEncoding ( Q3TextStream::Locale );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> m_tokenCount;

		buffer = inf.readLine();	// end of read tokens line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> usedTokens;

		buffer = inf.readLine();	// end of used tokens line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> types;

		buffer = inf.readLine();	// end of types line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> m_NumberOfCharacterTypes;

		buffer = inf.readLine();	// end of characters line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> minis;

		buffer = inf.readLine();	// end of minis line
		Q_ASSERT( buffer.length() == 0 );

		file.close();
	}

	return minis;
}


void CLexicon::OutputStats( QString FileName )
{
	Q_ASSERT( !FileName.isEmpty() );
	QFile file( FileName );

	int i;

	int slash = FileName.findRev( "\\" );
	if( slash < 0 ) slash = FileName.findRev( "/" );
	int dot = FileName.findRev( ".prj" );

	if( file.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream    outf( &file );
		outf.setEncoding ( Q3TextStream::Unicode );

		outf <<
			"# LEXICON (\'" + FileName.mid( slash+1, dot-3-slash ) + "\')" << endl <<
			"# Number of word tokens read: \n\t" << GetTokenCount() << endl <<
			"# Number of word tokens used: \n\t" << m_pCorpusWords->GetCorpusCount() << endl <<
			"# Number of word types: \n\t" << m_pCorpusWords->GetCount() << endl <<
			"# Number of character types: \n\t" << m_NumberOfCharacterTypes << endl <<
			"# Number of mini-lexica: \n\t" << GetMiniCount() << endl << endl;

		for( i = 0; i < GetMiniSize(); i++ )
		{
			CMiniLexicon* mini = GetMiniLexicon(i);
			if( !mini ) continue;

			outf << "# ------------------------" << endl <<
				QString( "# MINI-LEXICON %1" ).arg( i+1 ) << endl <<
				"# Number of words: \n\t" << mini->GetWords()->GetCount() << endl <<
				"# Number of stems: \n\t" << mini->GetStems()->GetCount() << endl;

			if( mini->GetSuffixes() ) 
			{
				outf << "# Number of regular suffixes: \n\t" << mini->GetSuffixes()->GetCount() << endl << 
					"# Number of signatures with regular suffixes: \n\t" << mini->GetSignatures()->GetCount() << endl << endl;
			}
			if( mini->GetPrefixes() ) 
			{
				outf << "# Number of regular prefixes: \n\t  " << mini->GetPrefixes()->GetCount() << endl << 
					"# Number of signatures with regular prefixes: \n\t" << mini->GetSignatures()->GetCount() << endl << endl;
			}
		}

		file.close();
	}
}


void CLexicon::SetFilters( QStringList* items )
{
	// Note: this function is private because we don't want to change
	// the filters after words have already been read into the lexicon
	// if we do, then they may filter out to display and log incorrectly
	if( m_pInFilter ) delete m_pInFilter;
	if( m_pOutFilter ) delete m_pOutFilter;

	m_pInFilter = new StringToString;
	m_pOutFilter = new StringToString;

	int pound, i = 0;
	QString item;
	for ( QStringList::Iterator it = items->begin(); it != items->end(); ++it )
	{
		// Remove comments
		pound = (*it).find('#');
		if( pound >= 0 ) item = (*it).left( pound ).stripWhiteSpace();
		else item = *it;

		// Do nothing if the remaining string has spaces
		// or nothing
		if( item.length() == 0 || item.find(' ') >= 0 ) break;

		// Insert into both filters
		QString character = QChar( FILTER_BASE + i );
		m_pInFilter->insert( item, character );
		m_pOutFilter->insert( character, item );
		i++;
	}
}

CMiniLexicon* CLexicon::GetMiniLexicon(int i)
{
	if (i == -1)
		return 0;

	Q_ASSERT(i >= 0 &&  i < GetMiniSize());
	return (*m_pMiniLexica)[i];
}

void CLexicon::SetActiveMiniIndex( int i )
{
	int j;

	if( i < 0 || GetMiniLexicon(i) ) m_ActiveMini = i;
	else
	{
		for( j = i-1; j >= 0; j-- )
		{
			if( GetMiniLexicon(j) ) 
			{
				m_ActiveMini = j;
				return;
			}
		}
		for( j = i+1; j < GetMiniSize(); j++ )
		{
			if( GetMiniLexicon(j) ) 
			{
				m_ActiveMini = j;
				return;
			}
		}
	}
}

int CLexicon::GetIntParameter(QString param, int iDefault)
{
	QMap<QString, QString> m;
	m_pDoc->GetPreferences()->GetDictionaryPreference(
				"Lxa_Parameters", &m);

	const QMap<QString, QString>::const_iterator iter =
		m.constFind(param);
	if (iter == m.constEnd())
		return iDefault;

	// see CLPreferences::GetIntPreference()
	bool ok;
	const int rv = iter.value().toInt(&ok);
	if (!ok)
		return iDefault;
	return rv;
}

QString CLexicon::GetStringParameter(QString param)
{
	QMap<QString, QString> m;
	m_pDoc->GetPreferences()->GetDictionaryPreference(
				"Lxa_Parameters", &m);

	const QMap<QString, QString>::const_iterator iter =
		m.constFind(param);
	if (iter == m.constEnd())
		return QString();

	return iter.value();
}

void CLexicon::MakeBrokenCorpus( QString outputFileName )
{
	Q_ASSERT( !outputFileName.isEmpty() );
	QFile outFile( outputFileName );

	CCorpusWord*	pCorpusWord;

	if( outFile.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream	out( &outFile );
		out.setEncoding( Q3TextStream::Unicode );

		for( QStringList::Iterator lineIt = m_Corpus.begin(); lineIt != m_Corpus.end(); ++lineIt )
		{
			QStringList line = QStringList::split( " ", *lineIt );

			for( QStringList::Iterator wordIt = line.begin(); wordIt != line.end(); ++wordIt )
			{
				pCorpusWord = m_CorpusMap.find( *wordIt );
				
				if( pCorpusWord ) out << pCorpusWord->Display( '+', m_pOutFilter ) << " ";
				else out << *wordIt;
			}

			out << endl;
		}
	}
}




int CLexicon::NewMiniLexicon()
{
  int pos;  

  for( pos = m_pMiniLexica->size()-1; pos >= 0; pos-- )
  {
	  if( (*m_pMiniLexica)[pos] )
	  {
		  break;
	  }
  }
  pos++;

  CMiniLexicon* mini = new CMiniLexicon( this, pos );

	if (pos >= 0 && static_cast<unsigned int>(pos) >=
			m_pMiniLexica->size())
		m_pMiniLexica->resize(m_pMiniLexica->size()*2);

  m_pMiniLexica->insert( pos, mini );

  return pos;
}


void CLexicon::DeleteMiniLexicon( int pos )
{
	int next, last;

	if( pos == 0 )
	{
		 QMessageBox::information( NULL, QString( "Linguistica" ), QString( "Sorry, you cannot delete the first mini-lexicon. If you want \nto clear all data, use \'Clear Lexicon\' in the \'Edit\' menu." ) );
		 return;
	}

	m_pMiniLexica->remove(pos);

	for( last = m_pMiniLexica->size()-1; last >= 0; last-- )
	{
		if( (*m_pMiniLexica)[last] )
		{
			break;
		}
	}

	if( last < (static_cast <int> (m_pMiniLexica->size()))/2 - 1 ) m_pMiniLexica->resize( m_pMiniLexica->size()/2 );

	if( pos-1 >= 0 && (*m_pMiniLexica)[pos-1] ) SetActiveMiniIndex( pos - 1 );
	else 
	{
		for( next = pos; next <= last; next++ )
		{
			if( (*m_pMiniLexica)[next] )
			{
				SetActiveMiniIndex( next );
			}
		}
	}
}

void CLexicon::ClearMiniLexicon( int pos )
{
  (*m_pMiniLexica)[pos]->ClearAll();
}

int CLexicon::GetCorpusCount() { return m_pCorpusWords->GetCorpusCount(); }

// All Stems
////////////////////////////////////////////////////////////////////

QList<CStem*>* CLexicon::GetStemSet( const CStringSurrogate& stem )
{
	return m_AllStems.find( stem.Display() );
}


bool CLexicon::InsertStem( CStem* stem )
{
	if( !stem ) return FALSE;

	// Get or create the set
        QList<CStem*>* set = m_AllStems.find( stem->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllStems.count() >= m_AllStems.size() )
		{
			m_AllStems.resize( getNextPrimeStep( m_AllStems.size() ) );
		}

                set = new QList<CStem*>();
		m_AllStems.insert( stem->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( stem ) >= 0 ) return FALSE;

	// Insert the stem
	set->prepend( stem );

	return TRUE;
}


bool CLexicon::RemoveStem( CStem* stem )
{
	if( !stem ) return FALSE;

	// Get the set
        QList<CStem*>* set = m_AllStems.find( stem->Display() );
	if( !set ) return FALSE;

	// Remove the stem
	if( !set->remove( stem ) ) return FALSE;

	// Remove the set also if there are no more stems
	if( set->isEmpty() ) 
	{
		m_AllStems.remove( stem->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllStems.size() ) );
		if( static_cast <int> ( m_AllStems.count() ) < smaller_size )
		{
			m_AllStems.resize( smaller_size );
		}
	}

	return TRUE;
}


// All Suffixes
////////////////////////////////////////////////////////////////////

QList<CSuffix*>* CLexicon::GetSuffixSet( const CStringSurrogate& suffix )
{
	return m_AllSuffixes.find( suffix.Display() );
}


bool CLexicon::InsertSuffix( CSuffix* suffix )
{
	if( !suffix ) return FALSE;

	// Get or create the set
        QList<CSuffix*>* set = m_AllSuffixes.find( suffix->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllSuffixes.count() >= m_AllSuffixes.size() )
		{
			m_AllSuffixes.resize( getNextPrimeStep( m_AllSuffixes.size() ) );
		}

                set = new QList<CSuffix*>();
		m_AllSuffixes.insert( suffix->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( suffix ) >= 0 ) return FALSE;

	// Insert the suffix
	set->prepend( suffix );

	return TRUE;
}


bool CLexicon::RemoveSuffix( CSuffix* suffix )
{
	if( !suffix ) return FALSE;

	// Get the set
        QList<CSuffix*>* set = m_AllSuffixes.find( suffix->Display() );
	if( !set ) return FALSE;

	// Remove the suffix
	if( !set->remove( suffix ) ) return FALSE;

	// Remove the set also if there are no more suffixes
	if( set->isEmpty() ) 
	{
		m_AllSuffixes.remove( suffix->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllSuffixes.size() ) );
		if( static_cast <int> ( m_AllSuffixes.count() ) < smaller_size )
		{
			m_AllSuffixes.resize( smaller_size );
		}
	}

	return TRUE;
}


// All Suffix Signatures
////////////////////////////////////////////////////////////////////

QList<CSignature*>* CLexicon::GetSuffixSigSet( const CStringSurrogate& sig )
{
	return m_AllSuffixSigs.find( sig.Display() );
}


bool CLexicon::InsertSuffixSig( CSignature* sig )
{
	if( !sig ) return FALSE;

	// Get or create the set
        QList<CSignature*>* set = m_AllSuffixSigs.find( sig->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllSuffixSigs.count() >= m_AllSuffixSigs.size() )
		{
			m_AllSuffixSigs.resize( getNextPrimeStep( m_AllSuffixSigs.size() ) );
		}

                set = new QList<CSignature*>();
		m_AllSuffixSigs.insert( sig->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( sig ) >= 0 ) return FALSE;

	// Insert the signature
	set->prepend( sig );

	return TRUE;
}


bool CLexicon::RemoveSuffixSig( CSignature* sig )
{
	if( !sig ) return FALSE;

	// Get the set
        QList<CSignature*>* set = m_AllSuffixSigs.find( sig->Display() );
	if( !set ) return FALSE;

	// Remove the signature
	if( !set->remove( sig ) ) return FALSE;

	// Remove the set also if there are no more signatures
	if( set->isEmpty() ) 
	{
		m_AllSuffixSigs.remove( sig->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllSuffixSigs.size() ) );
		if( static_cast <int> (m_AllSuffixSigs.count()) < smaller_size )
		{
			m_AllSuffixSigs.resize( smaller_size );
		}
	}

	return TRUE;
}


// All Prefixes
////////////////////////////////////////////////////////////////////

QList<CPrefix*>* CLexicon::GetPrefixSet( const CStringSurrogate& prefix )
{
	return m_AllPrefixes.find( prefix.Display() );
}


bool CLexicon::InsertPrefix( CPrefix* prefix )
{
	if( !prefix ) return FALSE;

	// Get or create the set
        QList<CPrefix*>* set = m_AllPrefixes.find( prefix->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllPrefixes.count() >= m_AllPrefixes.size() )
		{
			m_AllPrefixes.resize( getNextPrimeStep( m_AllPrefixes.size() ) );
		}

                set = new QList<CPrefix*>();
		m_AllPrefixes.insert( prefix->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( prefix ) >= 0 ) return FALSE;

	// Insert the prefix
	set->prepend( prefix );

	return TRUE;
}


bool CLexicon::RemovePrefix( CPrefix* prefix )
{
	if( !prefix ) return FALSE;

	// Get the set
        QList<CPrefix*>* set = m_AllPrefixes.find( prefix->Display() );
	if( !set ) return FALSE;

	// Remove the prefix
	if( !set->remove( prefix ) ) return FALSE;

	// Remove the set also if there are no more prefixes
	if( set->isEmpty() ) 
	{
		m_AllPrefixes.remove( prefix->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllPrefixes.size() ) );
		if(static_cast <int> ( m_AllPrefixes.count()) < smaller_size )
		{
			m_AllPrefixes.resize( smaller_size );
		}
	}

	return TRUE;
}


// All Prefix Signatures
////////////////////////////////////////////////////////////////////

QList<CSignature*>* CLexicon::GetPrefixSigSet( const CStringSurrogate& sig )
{
	return m_AllPrefixSigs.find( sig.Display() );
}


bool CLexicon::InsertPrefixSig( CSignature* sig )
{
	if( !sig ) return FALSE;

	// Get or create the set
        QList<CSignature*>* set = m_AllPrefixSigs.find( sig->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllPrefixSigs.count() >= m_AllPrefixSigs.size() )
		{
			m_AllPrefixSigs.resize( getNextPrimeStep( m_AllPrefixSigs.size() ) );
		}

                set = new QList<CSignature*>();
		m_AllPrefixSigs.insert( sig->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( sig ) >= 0 ) return FALSE;

	// Insert the signature
	set->prepend( sig );

	return TRUE;
}


bool CLexicon::RemovePrefixSig( CSignature* sig )
{
	if( !sig ) return FALSE;

	// Get the set
        QList<CSignature*>* set = m_AllPrefixSigs.find( sig->Display() );
	if( !set ) return FALSE;

	// Remove the signature
	if( !set->remove( sig ) ) return FALSE;

	// Remove the set also if there are no more signatures
	if( set->isEmpty() ) 
	{
		m_AllPrefixSigs.remove( sig->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllPrefixSigs.size() ) );
		if( static_cast <int> (m_AllPrefixSigs.count()) < smaller_size )
		{
			m_AllPrefixSigs.resize( smaller_size );
		}
	}

	return TRUE;
}


// All Words
////////////////////////////////////////////////////////////////////

QList<CStem*>* CLexicon::GetWordSet( const CStringSurrogate& word )
{
	return m_AllWords.find( word.Display() );
}


bool CLexicon::InsertWord( CStem* word )
{
	if( !word ) return FALSE;

	// Get or create the set
        QList<CStem*>* set = m_AllWords.find( word->Display() );
	if( !set ) 
	{
		// Make sure the dictionary is large enough
		if( m_AllWords.count() >= m_AllWords.size() )
		{
			m_AllWords.resize( getNextPrimeStep( m_AllWords.size() ) );
		}

                set = new QList<CStem*>();
		m_AllWords.insert( word->Display(), set );
	}

	// Do not insert duplicates
        if( set->indexOf( word ) >= 0 ) return FALSE;

	// Insert the stem
	set->prepend( word );

	return TRUE;
}


bool CLexicon::RemoveWord( CStem* word )
{
	if( !word ) return FALSE;

	// Get the set
        QList<CStem*>* set = m_AllWords.find( word->Display() );
	if( !set ) return FALSE;

	// Remove the stem
	if( !set->remove( word ) ) return FALSE;

	// Remove the set also if there are no more stems
	if( set->isEmpty() ) 
	{
		m_AllWords.remove( word->Display() );
	
		// Shrink the dictionary if it's too large
		int smaller_size = getPrevPrimeStep( getPrevPrimeStep( m_AllWords.size() ) );
		if( static_cast <int> (m_AllWords.count()) < smaller_size )
		{
			m_AllWords.resize( smaller_size );
		}
	}

	return TRUE;
}


bool CLexicon::LogFileOn()
{
	return m_pDoc->LogFileOn();
}


QTextStream* CLexicon::GetLogFileStream()
{
	return m_pDoc->GetLogFileStream();
}

StateEmitHMM* CLexicon::GetHMM()
{
	return m_HMM;
}

StateEmitHMM* CLexicon::CreateNewHMM()
{
	if (m_HMM) { delete m_HMM;} 
	m_HMM = new StateEmitHMM (this);
	return m_HMM;
}
void CLexicon::UpdateCompound( QString compound )
{
	if( m_CompoundUpdates.find( compound ) == m_CompoundUpdates.end() )
	{
		m_CompoundUpdates.append( compound );
	}
}


void CLexicon::UpdateWord( CStem* pWord )
{
        if( m_WordUpdates.indexOf( pWord ) < 0 )
	{
		m_WordUpdates.append( pWord );
	}
}


void CLexicon::DoWordUpdates()
{
	CStem* pStem,
		 * qStem,
		 * rStem;

	CPrefix* pPrefix;
	CSuffix* pSuffix;
	CCompound* pCompound;

	CCorpusWord*            pCorpusWord;
	int                     myMiniIndex, start, end;
	bool                    startValid, endValid;
	int*                    wPieces, * sPieces;
        QList<CStem*>*        myWords;
        QList<CStem*>         wordQueue;

    m_pCorpusWords->SetUpdateFlags( FALSE );

    while( !m_WordUpdates.isEmpty() )
	{
                pStem = m_WordUpdates.takeAt(0);

 		// Check if this word has already been updated
		pCorpusWord = *m_pCorpusWords ^= pStem->GetKey();
		if( !pCorpusWord || pCorpusWord->IsUpdated() ) continue;

		// If it's also a compound, override
		pCompound = *m_pCompounds ^= pStem->GetKey();
		if( pCompound )
		{
			pCorpusWord->SetUpdated( TRUE );
			continue;
		}

		wordQueue.append( pStem );
		while( !wordQueue.isEmpty() )
		{
                        qStem = wordQueue.takeAt(0);

			if( pStem->GetMyMini()->GetPrefixes() )
			{
				pPrefix = *pStem->GetMyMini()->GetPrefixes() ^= pStem->GetPrefix();
			}
			else pPrefix = NULL;

			if( pStem->GetMyMini()->GetSuffixes() )
			{
				pSuffix = *pStem->GetMyMini()->GetSuffixes() ^= pStem->GetSuffix();
			}
			else pSuffix = NULL;

			if( pStem->GetMyMini()->GetStems() )
			{
				CSS cssStem = pStem->GetStem();
				rStem = *pStem->GetMyMini()->GetStems() ^= cssStem;
			}
			else rStem = NULL;

            // Update this stem in the corpus if it exists
			// as a word
			pCorpusWord = *m_pCorpusWords ^= qStem->GetKey();
			if( pCorpusWord )
			{
 				if( pCorpusWord->IsUpdated() ) continue;
				pCorpusWord->SetUpdated();

				wPieces = pCorpusWord->GetPieces();
				sPieces = pStem->GetPieces();

				start = pCorpusWord->Display().find( pStem->Display() );
				end = start + pStem->GetKeyLength();

				startValid = FALSE;
				endValid = FALSE;
				for (int i = 0; i <= pCorpusWord->Size(); ++i) {
					if( start == wPieces[i] ) startValid = TRUE;
					if( end == wPieces[i] ) endValid = TRUE;
				}

				Q_ASSERT( startValid && endValid );
				if( startValid && endValid )
				{
					for (int i = 0, j = 0;
							i <= pCorpusWord->Size() &&
							j <= pStem->Size(); ++i) {
						if( wPieces[i] > start )
						{
							j++;
							if( j > pStem->Size() ) break;

							if( wPieces[i] < sPieces[j] ) 
							{
								pCorpusWord->MergePieces(i);
 								break;
							}
							else if( sPieces[j] < wPieces[i] ) 
							{
								pCorpusWord->CutRightBeforeHere( sPieces[j] );
 								if( pSuffix )
								{
 									pCorpusWord->SetMorpheme( i, rStem );
									pCorpusWord->SetMorpheme( i+1, pSuffix );
								}
								else if( pPrefix )
								{
									pCorpusWord->SetMorpheme( i, pPrefix );
									pCorpusWord->SetMorpheme( i+1, rStem );
								}
								break;
							}
						}
					}
				}
			}

			// Add "parent" "words"
			myMiniIndex = qStem->GetMyMini()->GetIndex();
			Q_ASSERT( myMiniIndex >= 0 );
			Q_ASSERT( myMiniIndex < static_cast <int> ( m_pMiniLexica->size()) );

			for (unsigned int i = 0; i < m_pMiniLexica->size(); ++i) {
				if (myMiniIndex >= 0 &&
						static_cast<unsigned int>(myMiniIndex) == i)
					continue;
				if( (*m_pMiniLexica)[i] == NULL ) continue;

				rStem = *(*m_pMiniLexica)[i]->GetStems() ^= qStem->GetKey();

				if( !rStem ) continue;

				myWords = rStem->GetWordPtrList();

                                //for( rStem = myWords->first(); rStem; rStem = myWords->next() )
                                for (int z = 0; z < myWords->size(); z++)
                                {       rStem = myWords->at (z);
 					wordQueue.append( rStem );
				}
			}
		}
	}

	QString compound;

	// Update from compounds list
	for( QStringList::Iterator it = m_CompoundUpdates.begin(); it != m_CompoundUpdates.end(); ++it )
	{
		compound = (*it);
		pCompound = *m_pCompounds ^= CSS( compound );
		pCorpusWord = *m_pCorpusWords ^= CSS( compound );

 
		if( !pCorpusWord ) 
		{
			// This happens when the last component is a stem
			// found in the suffix analysis of one of the 
			// mini-lexica or the first component is a stem
			// found in the prefix analysis of one of the
			// mini-lexica

			wordQueue.clear();

			// Add all stems containing this compound to the queue
			for (unsigned int i = 0; i < m_pMiniLexica->size(); ++i) {
				if( (*m_pMiniLexica)[i] == NULL ) continue;

				rStem = *(*m_pMiniLexica)[i]->GetStems() ^= compound;

				if( !rStem ) continue;

				myWords = rStem->GetWordPtrList();

                                //for( rStem = myWords->first(); rStem; rStem = myWords->next() )
                                for (int y = 0; y < myWords->size(); y++)
                                {       rStem = myWords->at(y);
					wordQueue.append( rStem );
				}
			}

			// Update all ancestor corpus words
			while( !wordQueue.isEmpty() )
			{
                                pStem = wordQueue.takeAt(0);
				
				// Update this stem in the corpus if it exists
				// as a word
				pCorpusWord = *m_pCorpusWords ^= pStem->GetKey();
				if( pCorpusWord )
				{
 					if( pCorpusWord->IsUpdated() ) continue;
					pCorpusWord->SetUpdated();

					start = pCorpusWord->Display().find( compound );
					end = start + compound.length();

					wPieces = pCorpusWord->GetPieces();

					startValid = FALSE;
					endValid = FALSE;
					for (int i = 0; i <= pCorpusWord->Size(); ++i) {
						if( start == wPieces[i] ) startValid = TRUE;
						if( end == wPieces[i] ) endValid = TRUE;
					}

					// We need to match the cuts in the compound
					// to the substring of the corpus word or remove 
					// cuts in the substring if pCompound doesn't 
					// exist. Also, we need to add parents of each 
					// word to the queue and do those too.
					if( startValid && endValid )
					{
						if( pCompound )
						{
 							sPieces = pCompound->GetPieces();
							for (int i = 0, j = 0;
								i <= pCorpusWord->Size() && j <= pCompound->Size(); i++ )
							{
								if( wPieces[i] > start )
								{
									j++;
									if( j > pCompound->Size() ) break;

									if( wPieces[i] < sPieces[j] ) 
									{
										pCorpusWord->MergePieces(i);
                                    }
									else if( sPieces[j] < wPieces[i] ) 
									{
 
										pCorpusWord->CutRightBeforeHere( sPieces[j] );
                                    }
								}
							}
						
							// Now set the morphemes of the corpus word
							// equal to those of the compound
							for (int i = 1; i <= pCompound->Size(); ++i) {
								if( pCompound->GetComponent(i) ) pCorpusWord->SetMorpheme( i, pCompound->GetComponent(i)->at(0) );
								else if( pCompound->GetLinker(i) ) pCorpusWord->SetMorpheme( i, pCompound->GetLinker(i) );
							}
						}
						else
						{
							int first = -1;
							for (int i = 0; i <= pCorpusWord->Size(); ++i) {
								if( wPieces[i] > start && wPieces[i] < end )
								{
									pCorpusWord->MergePieces(i);
//qDebug( pCorpusWord->Display('.') ); 
									if( first < 0 ) first = i;
								}
							}
						
							// Now set the morpheme of the corpus word
							// equal to the stem or word the old compound
							// came from
							StemSet* pStemSet = GetAllStems()->find( compound );
							if( !pStemSet ) pStemSet = GetAllWords()->find( compound );
							if( pStemSet ) pCorpusWord->SetMorpheme( first, pStemSet->at(0) );
						}
					}
				}
			}

			continue;
		}

		if( !pCompound )
		{
			// Compound deleted, remove all cuts
			pCorpusWord->SimplifyParseStructure();
		}
		else
		{
			// Make cuts match compound
			pCorpusWord->CopyParseStructure( pCompound );
		}
//if( pCompound ) qDebug( pCompound->Display( '.' ) );
	}

	m_CompoundUpdates.clear();
}
