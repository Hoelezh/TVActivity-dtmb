#ifndef __MIPS_H__
#define __MIPS_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __ASSEMBLER__
/* aliases for general registers */
#define zero	$0
#define AT	$1		/* assembler temporaries */
#define v0	$2		/* value holders */
#define v1	$3
#define a0	$4		/* arguments */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8		/* temporaries */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16		/* saved registers */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24
#define t9	$25
#define k0	$26		/* kernel registers */
#define k1	$27
#define gp	$28		/* global pointer */
#define sp	$29		/* stack pointer */
#define s8	$30		/* saved reigister */
#define ra	$31		/* return address */

/*----- hardware registers names ---------------------*/
#define r0	$0
#define r1	$at
#define r2	$2
#define r3	$3
#define r4	$4
#define r5	$5
#define r6	$6
#define r7	$7
#define r8	$8
#define r9	$9
#define r10	$10
#define r11	$11
#define r12	$12
#define r13	$13
#define r14	$14
#define r15	$15
#define r16	$16
#define r17	$17
#define r18	$18
#define r19	$19
#define r20	$20
#define r21	$21
#define r22	$22
#define r23	$23
#define r24	$24
#define r25	$25
#define r26	$26
#define r27	$27
#define r28	$28
#define r29	$29
#define r30	$30
#define r31	$31

#define fp  $30
#endif

/* System-control coprocessor (CP0) registers */
#define C0_IBASE		$0	/* Instruction address space base */
#define C0_INDEX		$0	/* Index register */
#define C0_IBOUND		$1	/* Instruction address space bound */
#define C0_RANDOM		$1	/* Random register */
#define C0_DBASE		$2	/* Data address space base */
#define C0_TLBLO0		$2	/* Entry low 0 */
#define C0_DBOUND		$3	/* Data address space bound */
#define C0_TLBLO1		$3	/* Entry low 1 */

#define	C0_PAGEMASK		$5
#define	C0_WIRED		$6

#define C0_BADVADDR		$8	/* Bad Virtual Address */
#define C0_COUNT		$9	/* Timer Counter */
#define C0_TLBHI		$10	/* TLB EntryHi */
#define C0_COMPARE		$11	/* Timer Compare */
#define C0_SR			$12	/* Status Register */
#define C0_STATUS		$12	/* Status Register */
#define C0_CAUSE		$13	/* Cause Register */
#define C0_EPC			$14	/* Exception Program Counter */
#define C0_PRID			$15	/* Processor Revision Identifire */
#if	1 //defined(R4K)||defined(r4k) M6311 and T2 RISC are all R4K compatible
#define C0_CONFIG	$16		/* Device Configuration Information. Read ONLY	*/
#else
#define C0_CONFIG   $3		/* IDT 3081/71/41 specific registers */
#endif	/* R4K	*/
#define C0_CLAG			$17	/* Cache Attributes */
#define C0_CALG			$17	/* Cache Attributes */
#define C0_IWATCH		$18	/* Intruction breakpoint VAddr */
#define C0_DWATCH		$19	/* Data breakpoint VAddr */
#define	C0_XCONTEXT		$20

#define C0_DEBUG		$23	/* Debug Register for DSU */
#define C0_DEPC			$24	/* Debug Exception PC for DSU */

#define C0_ECC			$26	/* S-cache ECC and Primary Parity */
#define C0_CACHEERR		$27	/* Cache Error and Status register */
#define C0_TAGLO		$28	/*  Cache Tag register */
#define C0_TAGHI		$29
#define C0_ERROREPC		$30	/* Error Exception Program Counter */
#define C0_DESAVE		$31	/* Debug Save Register for DSU */

#define CAUSE_EXCMASK	0x7c

#ifdef __cplusplus
}
#endif

#endif
