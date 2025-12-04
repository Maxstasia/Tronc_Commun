/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main(ft_printf).c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:14:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/12/04 10:31:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int     ft_printf(const char *format, ...);

int     main(void)
{
    int     count = 0;
    char    c = 'A';
    void    *ptr = &c;
    void    *null_ptr = NULL;

    // =========================== BASIC ===========================
    count += ft_printf("--- BASIC ---\n");
    count += ft_printf("%c %c %c\n", 'a', 'z', '9');
    count += ft_printf("Hello 42!\n");
    count += ft_printf("%%\n");

    // =========================== STRINGS ===========================
    count += ft_printf("--- STRINGS ---\n");
    count += ft_printf("%s %s\n", "Salut", "les moussaillons");
    count += ft_printf("%s\n", "");                         // empty string
    count += ft_printf("%s\n", (char *)NULL);              // (null)

    // =========================== POINTERS ===========================
    count += ft_printf("--- POINTERS ---\n");
    count += ft_printf("%p\n", ptr);
    count += ft_printf("%p\n", null_ptr);                  // (nil) ou 0x0
    count += ft_printf("%p\n", (void *)1);
    count += ft_printf("%p\n", (void *)-1);
    count += ft_printf("%p\n", (void *)LONG_MAX);
    count += ft_printf("%p\n", (void *)ULONG_MAX);

    // =========================== INTEGERS (d & i) ===========================
    count += ft_printf("--- INTEGERS d/i ---\n");
    count += ft_printf("%d %i\n", 42, -42);
    count += ft_printf("%d %d\n", INT_MAX, INT_MIN);
    count += ft_printf("%d %d\n", 0, -0);
    count += ft_printf("%i %i\n", 123456789, -123456789);

    // =========================== UNSIGNED (u) ===========================
    count += ft_printf("--- UNSIGNED u ---\n");
    count += ft_printf("%u\n", 42);
    count += ft_printf("%u\n", 0);
    count += ft_printf("%u\n", UINT_MAX);
    count += ft_printf("%u\n", (unsigned int)-1);          // 4294967295

    // =========================== HEXA LOWER (x) ===========================
    count += ft_printf("--- HEXA x ---\n");
    count += ft_printf("%x\n", 0);
    count += ft_printf("%x\n", 42);
    count += ft_printf("%x\n", 255);
    count += ft_printf("%x\n", UINT_MAX);
    count += ft_printf("%x\n", 3735928559);                // 0xDEADBEEF
    count += ft_printf("%x\n", 0xabcdef);

    // =========================== HEXA UPPER (X) ===========================
    count += ft_printf("--- HEXA X ---\n");
    count += ft_printf("%X\n", 0);
    count += ft_printf("%X\n", 3735928559);                // DEADBEAF
    count += ft_printf("%X\n", UINT_MAX);

    // =========================== MIXED & TRICKY ===========================
    count += ft_printf("--- MIXED & TRAPS ---\n");
    count += ft_printf("%c%s%p%d%i%u%x%X%%\n", 'z', "test", ptr, 42, -42, 4242, 0xabc, 0xABC);
    count += ft_printf("%p %d %s %c %x %u %X\n", null_ptr, 0, "", ' ', 0, 0, 0);
    count += ft_printf("Multiple %% %%%% %%%%%%\n");

    // =========================== EDGE CASES THAT CRASH BAD PRINTFS ===========================
    count += ft_printf("--- EDGE CASES THAT KILL ---\n");
    count += ft_printf("%d\n", (int)2147483648U);          // overflow int
    count += ft_printf("%u\n", -1);
    count += ft_printf("%x\n", -1);
    count += ft_printf("%p\n", (void *)0x123456789ABCDEF);
    count += ft_printf("%s%s%s%s%s%s%s%s%s%s\n", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"); // beaucoup d'args
    count += ft_printf(NULL);                             // format NULL → segfault si pas géré
    count += ft_printf("%");                               // format incomplet
    count += ft_printf("%Z");                              // conversion inconnue (doit ignorer ou écrire %Z)
    count += ft_printf("%k\n", 42);                        // inconnu aussi

	// =========================== HARD TEST ===========================
	count += ft_printf("--- HARD TEST ---\n");
	count += ft_printf("%.0s\n", "coucou");          // precision 0 sur string non-null
    count += ft_printf("%10s\n", "hi");              // width sans flag (doit pad avec espaces à gauche)
    count += ft_printf("%-10s\n", "hi");             // - flag (pad à droite)
    count += ft_printf("%.10s\n", "precision test");
    count += ft_printf("%10.5d\n", 42);
    count += ft_printf("%-10.5d\n", -42);

    // =========================== FINAL COUNT ===========================
    ft_printf("\nTotal tests run: %d\n", count);
    return (0);
}



// compile with:
// gcc -Wall -Wextra -Werror main(ft_printf).c ft_printf.a libft.a -o test_printf
// ./test_printf

// Compare with standard printf:
// ./test_printf > mine
// gcc real.c -o real && ./real > original
// diff mine original
