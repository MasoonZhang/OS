#include "syscall.h"

#define _syscall0(NUMBER) ({                                        \
		int retval;                                         \
 		asm volatile(                                       \
			"pushl %[number]; int $0x80; addl $4, %%esp" \
			: "=a" (retval)                             \
			: [number] "i" (NUMBER)                     \
			: "memory"                                  \
		);                                                  \
		retval;                                             \
})

#define _syscall1(NUMBER, ARG0) ({                             \
		int retval;                                                \
		asm volatile(                                              \
			"pushl %[arg0];"     \
			"pushl %[number]; int $0x80; addl $8, %%esp"       \
			: "=a" (retval)                                    \
			: [number] "i" (NUMBER),                           \
			  [arg0] "g" (ARG0)                                \
			: "memory"                                         \
		);                                                         \
		retval;                                                    \
})

#define _syscall2(NUMBER, ARG0, ARG1) ({                             \
		int retval;                                                \
		asm volatile(                                              \
			"pushl %[arg1]; pushl %[arg0];"     \
			"pushl %[number]; int $0x80; addl $12, %%esp"       \
			: "=a" (retval)                                    \
			: [number] "i" (NUMBER),                           \
			  [arg0] "g" (ARG0),                               \
			  [arg1] "g" (ARG1)                                \
			: "memory"                                         \
		);                                                         \
		retval;                                                    \
})

#define _syscall3(NUMBER, ARG0, ARG1, ARG2) ({                             \
		int retval;                                                \
		asm volatile(                                              \
			"pushl %[arg2]; pushl %[arg1]; pushl %[arg0];"     \
			"pushl %[number]; int $0x80; addl $16, %%esp"       \
			: "=a" (retval)                                    \
			: [number] "i" (NUMBER),                           \
			  [arg0] "g" (ARG0),                               \
			  [arg1] "g" (ARG1),                               \
			  [arg2] "d" (ARG2)                                \
			: "memory"                                         \
		);                                                         \
		retval;                                                    \
})

uint32_t getpid() {
	return _syscall0(SYS_GETPID);
}
