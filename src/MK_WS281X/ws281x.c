/*
 * ws281x.c    attiny85    F_CPU = 16000000 Hz
 *
 * Created on: 1/12/2020
 *     Author: MK
*/

#include <avr/io.h>
#include "ws281x.h"

/*
 * ws281x_asm.c
 *
 *  Created on: 30-06-2014
 *      Author: Miroslaw Kardas
 *      F_CPU = 11,0592 MHz
 */
#include <avr/io.h>

#include "ws281x.h"

//     bit = 0                    bit = 1
//  +----+        |        +--------+    |
//  |    |        |        |        |    |
//  |    |        |        |        |    |
//  |    |        |        |        |    |
//  |    |        |        |        |    |
//  |    +--------+        |        +----+
//  400ns   800ns             800ns   400ns

void ws281x_asm_send(void *data, uint16_t datlen, uint8_t pin) {

    uint8_t databyte=0, cnt, pinLO=~pin;
    WS_DIR |= pin;
    datlen *= 3;

#if F_CPU == 11059200

    asm volatile(
    "        lds       %[cnt],%[ws_port]          \n\t"
    "        or        %[pinHI],%[cnt]            \n\t"
    "        and       %[pinLO],%[cnt]            \n\t"
    "mPTL%=:subi       %A6,1                      \n\t"
    "        sbci      %B6,0                      \n\t"
    "        brcs      exit%=                     \n\t"
    "        ld        %[databyte],X+             \n\t"
    "        ldi       %[cnt],8                   \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
    "                  nop                        \n\t"
    "        lsl       %[databyte]                \n\t"
    "        brcs      .+2                        \n\t"
    "        sts       %[ws_port],    %[pinLO]    \n\t"
    "        nop                                  \n\t"

    "        dec       %[cnt]                     \n\t"
    "        sts       %[ws_port],    %[pinLO]    \n\t"
    "        breq      mPTL%=                     \n\t"
    "        rjmp      oPTL%=                     \n\t"
    "exit%=:                                      \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)), [pinHI]"r" (pin),
        [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 12000000

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                    \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8        \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        nop                \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
    "        nop                            \n\t"

    "        dec        %[cnt]                    \n\t"
    "        sts        %[ws_port],    %[pinLO]    \n\t"
    "        breq    mPTL%=                    \n\t"
            "        nop                    \n\t"

    "        rjmp    oPTL%=                    \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)), [pinHI]"r" (pin),
        [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 14745600

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8            \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        rjmp .+0                \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
            "        rjmp .+0                    \n\t"
            "        nop                    \n\t"

    "        dec        %[cnt]                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
    "        breq    mPTL%=                \n\t"
            "        rjmp .+0                \n\t"

    "        rjmp    oPTL%=                \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)),
         [pinHI]"r" (pin), [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 16000000

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8            \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        rjmp .+0                \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
            "        rjmp .+0                    \n\t"
            "        rjmp .+0                \n\t"

    "        dec        %[cnt]                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
    "        breq    mPTL%=                \n\t"
            "        rjmp .+0                    \n\t"

    "        rjmp    oPTL%=                \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)),
         [pinHI]"r" (pin), [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 18432000

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8            \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        rjmp .+0                \n\t"
            "        nop                        \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
            "        rjmp .+0                    \n\t"
            "        rjmp .+0                \n\t"

    "        dec        %[cnt]                    \n\t"
    "        sts        %[ws_port],    %[pinLO]\n\t"
    "        breq    mPTL%=                \n\t"
            "        rjmp .+0                    \n\t"
            "        rjmp .+0                \n\t"

    "        rjmp    oPTL%=                \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)),
         [pinHI]"r" (pin), [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 20000000

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8            \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]    \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"

    "        dec        %[cnt]                \n\t"
    "        sts        %[ws_port],    %[pinLO]    \n\t"
    "        breq    mPTL%=                    \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"
            "        nop                \n\t"

    "        rjmp    oPTL%=                \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)),
         [pinHI]"r" (pin), [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

#if F_CPU == 24000000

    asm volatile(
    "        lds        %[cnt],%[ws_port]    \n\t"
    "        or        %[pinHI],%[cnt]        \n\t"
    "        and        %[pinLO],%[cnt]        \n\t"
    "mPTL%=:subi    %A6,1                \n\t"
    "        sbci    %B6,0                \n\t"
    "        brcs    exit%=                \n\t"
    "        ld        %[databyte],X+        \n\t"
    "        ldi        %[cnt],8            \n\t"

    "oPTL%=:sts        %[ws_port],    %[pinHI]    \n\t"
            "        rjmp .+0        \n\t"
            "        rjmp .+0        \n\t"
            "        rjmp .+0        \n\t"

    "        lsl        %[databyte]            \n\t"
    "        brcs    .+2                    \n\t"
    "        sts        %[ws_port],    %[pinLO]    \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"

    "        dec        %[cnt]                \n\t"
    "        sts        %[ws_port],    %[pinLO]    \n\t"
    "        breq    mPTL%=                    \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"
            "        rjmp .+0            \n\t"

    "        rjmp    oPTL%=                \n\t"
    "exit%=:                            \n\t"
    :    [cnt]"=&d" (cnt)
    :    [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)),
         [pinHI]"r" (pin), [pinLO]"r" (pinLO), [data]"x" (data), [datlen]"r" (datlen)
    );

#endif

}
