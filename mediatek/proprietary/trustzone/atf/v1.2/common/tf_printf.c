/*
 * Copyright (c) 2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <arch_helpers.h>
#include <debug.h>
#include <log.h>
#include <mt_cpuxgpt.h>
#include <platform.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#define ATF_SCHED_CLOCK_UNIT 1000000000 //ns
#define TIMESTAMP_BUFFER_SIZE 32
int (*log_lock_acquire)();
int (*log_write)(unsigned char);
int (*log_lock_release)();

/***********************************************************
 * The tf_printf implementation for all BL stages
 ***********************************************************/
static void unsigned_num_print(unsigned long int unum, unsigned int radix)
{
	/* Just need enough space to store 64 bit decimal integer */
	unsigned char num_buf[20];
	int i = 0, rem;

	do {
		rem = unum % radix;
		if (rem < 0xa)
			num_buf[i++] = '0' + rem;
		else
			num_buf[i++] = 'a' + (rem - 0xa);
	} while (unum /= radix);

	while (--i >= 0){
		if (log_write)
			(*log_write)(num_buf[i]);
		putchar(num_buf[i]);
	}
}

static void string_print(const char *str)
{
	while (*str){
		if (log_write)
			(*log_write)(*str);
		putchar(*str++);
	}
}

/* reverse:  reverse string s in place */
static void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa:  convert n to characters in s */
static int utoa(unsigned int n, char s[])
{
	int i;

	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	s[i] = '\0';
	reverse(s);
	return i;
}
static int ltoa(unsigned long long n, char s[], unsigned add_zero)
{
	int i = 0;

	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */

	while(add_zero && i < 6){
		s[i++] = '0'; /* add '0' for log readability */
	}
	s[i] = '\0';

	reverse(s);

	return i;
}
/*******************************************************************
 * Reduced format print for Trusted firmware.
 * The following formats are supported by this print
 * %x - 32 bit hexadecimal format
 * %llx and %lx -64 bit hexadecimal format
 * %s - string format
 * %d or %i - signed 32 bit decimal format
 * %u - unsigned 32 bit decimal format
 * %ld and %lld - signed 64 bit decimal format
 * %lu and %llu - unsigned 64 bit decimal format
 * Exits on all other formats.
 *******************************************************************/
#define dcache_check()	\
	unsigned long sec_sctlr_el3 = read_sctlr_el3();	\
	if ((sec_sctlr_el3 & 0x4) == 0) {	\
		/* Data Cache is disable in secure world */	\
		/* panic(); */	\
		return;	\
	}

extern uint64_t normal_time_base;
static char timestamp_buf[TIMESTAMP_BUFFER_SIZE] __attribute__((aligned(8)));
void tf_printf(const char *fmt, ...)
{
	va_list args;
	int bit64;
	int64_t num;
	uint64_t unum;
	uint64_t tmpunum;
	char *str;
	unsigned long long cur_time;
	unsigned long long sec_time;
	unsigned long long ns_time;
	int 	count;
	char	*timestamp_bufptr = timestamp_buf;
	unsigned int digit = 0;
	unsigned int tmpdigit = 0;

	/* try get buffer lock */
	if (log_lock_acquire){
		dcache_check();
		(*log_lock_acquire)();
	}

	/* in ATF boot time, tiemr for cntpct_el0 is not initialized
	 * so it will not count now.
	 */
	cur_time = atf_sched_clock();
	sec_time = cur_time / ATF_SCHED_CLOCK_UNIT;
	ns_time = (cur_time % ATF_SCHED_CLOCK_UNIT)/1000;

	*timestamp_bufptr++ = '[';
	*timestamp_bufptr++ = 'A';
	*timestamp_bufptr++ = 'T';
	*timestamp_bufptr++ = 'F';
	*timestamp_bufptr++ = ']';
	*timestamp_bufptr++ = '(';
	count = utoa(platform_get_core_pos(read_mpidr()), timestamp_bufptr);
	timestamp_bufptr += count;
	*timestamp_bufptr++ = ')';
	if(MT_LOG_KTIME){
		*timestamp_bufptr++ = 'K';
		*timestamp_bufptr++ = ':';
	}
	*timestamp_bufptr++ = '[';
	count = ltoa(sec_time, timestamp_bufptr, 0);
	timestamp_bufptr += count;
	*timestamp_bufptr++ = '.';
	count = ltoa(ns_time, timestamp_bufptr, 1);
	timestamp_bufptr += count;
	*timestamp_bufptr++ = ']';
	*timestamp_bufptr++ = '\0';

	timestamp_buf[TIMESTAMP_BUFFER_SIZE - 1] = '\0';
	count = 0;
	while (timestamp_buf[count])
	{
		/* output char to ATF log buffer */
		if (log_write)
			(*log_write)(timestamp_buf[count]);
		putchar(timestamp_buf[count]);
		count++;
	}

	va_start(args, fmt);
	while (*fmt) {
		bit64 = 0;

		if (*fmt == '%') {
			fmt++;
			/* Check the format specifier */
loop:
			switch (*fmt) {
			case '0': /* Print leading '0' */
				if(*(fmt+1) > '0' && *(fmt+1) <= '9') {
					fmt++;
					if(*(fmt) == '1' && *(fmt+1) > '0' && *(fmt+1) <= '6') {
						fmt++;
						digit = *fmt - '0' + 10;
					}
					else {
						digit = *fmt - '0';
					}
				}
				fmt++;
				goto loop;
				break;
			case 'i': /* Fall through to next one */
			case 'd':
				if (bit64)
					num = va_arg(args, int64_t);
				else
					num = va_arg(args, int32_t);

				if (num < 0) {
					putchar('-');
					if (log_write)
						(*log_write)('-');
					unum = (unsigned long int)-num;
				} else
					unum = (unsigned long int)num;

				/* Print leading '0' if any */
				if(digit){
					tmpunum = unum / 10;
					tmpdigit = 1;
					while ((tmpunum)){
						tmpunum /= 10;
						tmpdigit++;
					}
					digit = digit > tmpdigit ? (digit - tmpdigit) : 0;
					for (tmpdigit=0; tmpdigit < digit; tmpdigit++) {
						putchar('0');
						if (log_write)
							(*log_write)('0');
					}
				}
				unsigned_num_print(unum, 10);
				break;
			case 's':
				str = va_arg(args, char *);
				string_print(str);
				break;
			case 'x':
				if (bit64)
					unum = va_arg(args, uint64_t);
				else
					unum = va_arg(args, uint32_t);

				/* Print leading '0' if any */
				if(digit){
					tmpunum = unum >> 4;
					tmpdigit = 1;
					while ((tmpunum)){
						tmpunum = tmpunum>> 4;
						tmpdigit++;
					}
					digit = digit > tmpdigit ? (digit - tmpdigit) : 0;
					for (tmpdigit=0; tmpdigit < digit; tmpdigit++) {
						putchar('0');
						if (log_write)
							(*log_write)('0');
					}
				}
				unsigned_num_print(unum, 16);
				break;
			case 'l':
				bit64 = 1;
				fmt++;
				goto loop;
			case 'u':
				if (bit64)
					unum = va_arg(args, uint64_t);
				else
					unum = va_arg(args, uint32_t);

				/* Print leading '0' if any */
				if(digit){
					tmpunum = unum / 10;
					tmpdigit = 1;
					while ((tmpunum)){
						tmpunum /= 10;
						tmpdigit++;
					}
					digit = digit > tmpdigit ? (digit - tmpdigit) : 0;
					for (tmpdigit=0; tmpdigit < digit; tmpdigit++) {
						putchar('0');
						if (log_write)
							(*log_write)('0');
					}
				}
				unsigned_num_print(unum, 10);
				break;
			default:
				/* Exit on any other format specifier */
				goto exit;
			}
			digit=0;
			fmt++;
			continue;
		}
		if (log_write)
			(*log_write)(*fmt);
		putchar(*fmt++);
	}
exit:
	va_end(args);

	/* release buffer lock */
	if (log_lock_release)
		(*log_lock_release)();
}


void bl31_log_service_register(int (*lock_get)(),
    int (*log_putc)(unsigned char),
    int (*lock_release)())
{
    log_lock_acquire = lock_get;
    log_write = log_putc;
    log_lock_release = lock_release;
}

