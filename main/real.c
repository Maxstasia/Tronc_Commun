/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:14:09 by mstasiak          #+#    #+#             */
/*   Updated: 2025/12/04 11:35:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int     main(void)
{
    int     count = 0;
    char    c = 'A';
    void    *ptr = &c;
    void    *null_ptr = NULL;

    // =========================== BASIC ===========================
    count += printf("--- BASIC ---\n");
    count += printf("%c %c %c\n", 'a', 'z', '9');
    count += printf("Hello 42!\n");
    count += printf("%%\n");

    // =========================== STRINGS ===========================
    count += printf("--- STRINGS ---\n");
    count += printf("%s %s\n", "Salut", "les moussaillons");
    count += printf("%s\n", "");                         // empty string
    //count += printf("%s\n", (char *)NULL);              // (null)

    // =========================== POINTERS ===========================
    count += printf("--- POINTERS ---\n");
    count += printf("%p\n", ptr);
    count += printf("%p\n", null_ptr);                  // (nil) ou 0x0
    count += printf("%p\n", (void *)1);
    count += printf("%p\n", (void *)-1);
    count += printf("%p\n", (void *)LONG_MAX);
    count += printf("%p\n", (void *)ULONG_MAX);

    // =========================== INTEGERS (d & i) ===========================
    count += printf("--- INTEGERS d/i ---\n");
    count += printf("%d %i\n", 42, -42);
    count += printf("%d %d\n", INT_MAX, INT_MIN);
    count += printf("%d %d\n", 0, -0);
    count += printf("%i %i\n", 123456789, -123456789);

    // =========================== UNSIGNED (u) ===========================
    count += printf("--- UNSIGNED u ---\n");
    count += printf("%u\n", 42);
    count += printf("%u\n", 0);
    count += printf("%u\n", UINT_MAX);
    count += printf("%u\n", (unsigned int)-1);          // 4294967295

    // =========================== HEXA LOWER (x) ===========================
    count += printf("--- HEXA x ---\n");
    count += printf("%x\n", 0);
    count += printf("%x\n", 42);
    count += printf("%x\n", 255);
    count += printf("%x\n", UINT_MAX);
    count += printf("%lx\n", 3735928559);                // 0xDEADBEEF
    count += printf("%x\n", 0xabcdef);

    // =========================== HEXA UPPER (X) ===========================
    count += printf("--- HEXA X ---\n");
    count += printf("%X\n", 0);
    count += printf("%lX\n", 3735928559);                // DEADBEAF
    count += printf("%X\n", UINT_MAX);

    // =========================== MIXED & TRICKY ===========================
    count += printf("--- MIXED & TRAPS ---\n");
    count += printf("%c%s%p%d%i%u%x%X%%\n", 'z', "test", ptr, 42, -42, 4242, 0xabc, 0xABC);
    count += printf("%p %d %s %c %x %u %X\n", null_ptr, 0, "", ' ', 0, 0, 0);
    count += printf("Multiple %% %%%% %%%%%%\n");

    // =========================== EDGE CASES THAT CRASH BAD PRINTFS ===========================
    count += printf("--- EDGE CASES THAT KILL ---\n");
    count += printf("%d\n", (int)2147483648U);          // overflow int
    count += printf("%u\n", -1);
    count += printf("%x\n", -1);
    count += printf("%p\n", (void *)0x123456789ABCDEF);
    count += printf("%s%s%s%s%s%s%s%s%s%s\n", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"); // beaucoup d'args
    //count += printf(NULL);                             // format NULL → segfault si pas géré
    count += printf("%%");                               // format incomplet
    count += printf("%%Z");                              // conversion inconnue (doit ignorer ou écrire %Z)
    count += printf("%%k\n");                        // inconnu aussi

	// =========================== HARD TEST ===========================
	/* count += printf("--- HARD TEST ---\n");
	count += printf("%.0s\n", "coucou");          // precision 0 sur string non-null
    count += printf("%10s\n", "hi");              // width sans flag (doit pad avec espaces à gauche)
    count += printf("%-10s\n", "hi");             // - flag (pad à droite)
    count += printf("%.10s\n", "precision test");
    count += printf("%10.5d\n", 42);
    count += printf("%-10.5d\n", -42); */

    // =========================== FINAL COUNT ===========================
    printf("\nTotal tests run: %d\n", count);
    return (0);
}

// compile with:
// gcc -Wall -Wextra -Werror real.c ft_printf.a libft.a -o real
// ./real
