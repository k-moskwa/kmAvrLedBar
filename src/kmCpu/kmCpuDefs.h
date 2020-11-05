/*
 * CpuDefs.h
 *
 * Created: 10/7/2019 12:43:36 PM
 *  Author: km
 */ 

#ifndef KM_CPUDEFS_H_
#define KM_CPUDEFS_H_

/// AVR CPU Series 0
#if \
	defined(__AVR_ATmega8__) \
	|| defined(__AVR_ATmega8A__) \
	|| defined(__AVR_ATmega16__) \
	|| defined(__AVR_ATmega16A__) \
	|| defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega32A__)
#define AVR_CPU_SERIES_0
#endif

#if \
	defined(__AVR_ATmega8__) \
	|| defined(__AVR_ATmega8A__) \
	|| defined(__AVR_ATmega16__) \
	|| defined(__AVR_ATmega16A__)
#define AVR_CPU_LAYOUT_28
#endif

#if \
	defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega32A__)
#define AVR_CPU_LAYOUT_40
#endif

/// AVR CPU Series 4
#if \
	defined(__AVR_ATmega644__) \
	|| defined(__AVR_ATmega644P__)
#define AVR_CPU_SERIES_4
#define AVR_CPU_SERIES_48
#endif

#if \
defined(__AVR_ATmega644__) \
|| defined(__AVR_ATmega644P__)
#define AVR_CPU_LAYOUT_40
#endif

/// AVR CPU Series 8
#if \
    defined(__AVR_ATmega328__) \
    || defined(__AVR_ATmega328P__)
#define AVR_CPU_SERIES_8
#define AVR_CPU_SERIES_48
#endif

#if \
    defined(__AVR_ATmega328__) \
    || defined(__AVR_ATmega328P__)
#define AVR_CPU_LAYOUT_28
#endif

#endif /* KM_CPUDEFS_H_ */
