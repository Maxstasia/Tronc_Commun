/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main(LIBFT).c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:00:16 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/08 14:48:31 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

void	test_ft_atoi(void)
{
	const char	*tests[] = {
		"42", "-42", "   123", "   +0", "   +123", "   -123", "  \t\n 123", "  \t\n ",
		"++123", "--123", "+-123", "-+123", "2147483647", "-2147483648", "2147483648",
		"-2147483649", "123abc", "abc123", "   123abc", "abc", "0", "   0", "000001",
		"-000001", "-0", "123!@#", "!@#123", "", " ", "     42", "     -42", "     ",
		"    +   ", "2147483647", "-2147483648"
	};

	int	total_tests = sizeof(tests) / sizeof(tests[0]);
	int	test_failed = 0;

    printf("Testing ft_atoi...\n");

    for (int i = 0; i < total_tests; i++) {
		int expected = atoi(tests[i]);
		int result = ft_atoi(tests[i]);

        if (result != expected) {
            printf("Test failed for input \"%s\": Expected %d, Got %d\n", tests[i], expected, result);
            test_failed = 1;
        }
    }

    if (test_failed == 0) {
        printf("test ft_atoi : ✅ réussi ✅​\n");
    } else {
        printf("test ft_atoi : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void print_bytes(const char *label, const char *buffer, size_t size)
{
    printf("%s", label);
    for (size_t i = 0; i < size; i++) {
        printf("\\x%02x", (unsigned char)buffer[i]);
    }
    printf("\n");
}

void test_ft_bzero(void)
{
    int test_failed = 0;
    char test1[] = "Libft test";       // Test 1: Mise à zéro des 4 premiers octets
    char test2[] = "Complete test";    // Test 2: Mise à zéro complète de la chaîne
    char test3[] = "No zero";          // Test 3: Aucun octet mis à zéro

    printf("Testing ft_bzero...\n");

    // Test 1
    ft_bzero(test1, 4);
    char expected1[] = "Libft test";
    bzero(expected1, 4);
    if (memcmp(test1, expected1, sizeof(test1)) != 0) {
        printf("Test 1 failed: Expected ");
        print_bytes("", expected1, sizeof(expected1));
        printf(", Got ");
        print_bytes("", test1, sizeof(test1));
        test_failed = 1;
    }

    // Test 2
    ft_bzero(test2, sizeof(test2));
    char expected2[] = "Complete test";
    bzero(expected2, sizeof(expected2));
    if (memcmp(test2, expected2, sizeof(test2)) != 0) {
        printf("Test 2 failed: Expected ");
        print_bytes("", expected2, sizeof(expected2));
        printf(", Got ");
        print_bytes("", test2, sizeof(test2));
        test_failed = 1;
    }

    // Test 3
    ft_bzero(test3, 0); // Pas de modification attendue
    char expected3[] = "No zero";
    if (memcmp(test3, expected3, sizeof(test3)) != 0) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\"\n", expected3, test3);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_bzero : ✅ réussi ✅​\n");
    } else {
        printf("test ft_bzero : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}








   Libft 

void test_ft_calloc(void)
{
    int test_failed = 0;

    printf("Testing ft_calloc...\n");

    // Test 1 : Allocation de 5 entiers
    int *arr1 = (int *)ft_calloc(5, sizeof(int));
    int *expected1 = (int *)calloc(5, sizeof(int));
    if (!arr1 || !expected1) {
        printf("Test 1 failed: Allocation error\n");
        test_failed = 1;
    } else {
        for (int i = 0; i < 5; i++) {
            if (arr1[i] != expected1[i]) {
                printf("Test 1 failed: Expected %d at index %d, Got %d\n", expected1[i], i, arr1[i]);
                test_failed = 1;
                break;
            }
        }
    }
    free(arr1);
    free(expected1);

    // Test 2 : Allocation de 0 éléments (doit retourner NULL ou une adresse sans erreur)
    int *arr2 = (int *)ft_calloc(0, sizeof(int));
    int *expected2 = (int *)calloc(0, sizeof(int));
    if (arr2 == NULL && expected2 == NULL) {
        // Les deux sont NULL, pas de problème
    } else if (arr2 != NULL && expected2 != NULL) {
        // Allocation valide, testons le contenu
        if (arr2[0] != expected2[0]) {
            printf("Test 2 failed: Expected %d, Got %d\n", expected2[0], arr2[0]);
            test_failed = 1;
        }
    } else {
        printf("Test 2 failed: Expected %p, Got %p\n", expected2, arr2);
        test_failed = 1;
    }
    free(arr2);
    free(expected2);

    // Test 3 : Allocation de 1000 éléments pour vérifier une grande taille
    int *arr3 = (int *)ft_calloc(1000, sizeof(int));
    int *expected3 = (int *)calloc(1000, sizeof(int));
    if (!arr3 || !expected3) {
        printf("Test 3 failed: Allocation error\n");
        test_failed = 1;
    } else {
        for (int i = 0; i < 1000; i++) {
            if (arr3[i] != expected3[i]) {
                printf("Test 3 failed: Expected %d at index %d, Got %d\n", expected3[i], i, arr3[i]);
                test_failed = 1;
                break;
            }
        }
    }
    free(arr3);
    free(expected3);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_calloc : ✅ réussi ✅​\n");
    } else {
        printf("test ft_calloc : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_isalnum(void)
{
    int test_failed = 0;

    printf("Testing ft_isalnum...\n");

    // Test 1 : Test avec un caractère alphabétique
    char c1 = 'a';
    int result1 = ft_isalnum(c1);
    int expected1 = isalnum(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for character '%c'\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère non alphabétique et non numérique
    char c2 = '!';
    int result2 = ft_isalnum(c2);
    int expected2 = isalnum(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for character '%c'\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Test 3 : Test avec un chiffre numérique
    char c3 = '1';
    int result3 = ft_isalnum(c3);
    int expected3 = isalnum(c3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for character '%c'\n", expected3, result3, c3);
        test_failed = 1;
    }

    // Test 4 : Test avec une lettre majuscule
    char c4 = 'Z';
    int result4 = ft_isalnum(c4);
    int expected4 = isalnum(c4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for character '%c'\n", expected4, result4, c4);
        test_failed = 1;
    }

    // Test 5 : Test avec un caractère de ponctuation
    char c5 = '#';
    int result5 = ft_isalnum(c5);
    int expected5 = isalnum(c5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %d, Got %d for character '%c'\n", expected5, result5, c5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_isalnum : ✅ réussi ✅​\n");
    } else {
        printf("test ft_isalnum : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_isalpha(void)
{
    int test_failed = 0;

    printf("Testing ft_isalpha...\n");

    // Test 1 : Test avec une lettre majuscule
    char c1 = 'A';
    int result1 = ft_isalpha(c1);
    int expected1 = isalpha(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for character '%c'\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère numérique
    char c2 = '1';
    int result2 = ft_isalpha(c2);
    int expected2 = isalpha(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for character '%c'\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Test 3 : Test avec une lettre minuscule
    char c3 = 'z';
    int result3 = ft_isalpha(c3);
    int expected3 = isalpha(c3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for character '%c'\n", expected3, result3, c3);
        test_failed = 1;
    }

    // Test 4 : Test avec un caractère spécial
    char c4 = '#';
    int result4 = ft_isalpha(c4);
    int expected4 = isalpha(c4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for character '%c'\n", expected4, result4, c4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_isalpha : ✅ réussi ✅​\n");
    } else {
        printf("test ft_isalpha : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_isascii(void)
{
    int test_failed = 0;

    printf("Testing ft_isascii...\n");

    // Test 1 : Test avec un caractère ASCII valide (65 correspond à 'A')
    int c1 = 65;
    int result1 = ft_isascii(c1);
    int expected1 = isascii(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for value %d\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère en dehors de la plage ASCII (200)
    int c2 = 200;
    int result2 = ft_isascii(c2);
    int expected2 = isascii(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for value %d\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_isascii : ✅ réussi ✅​\n");
    } else {
        printf("test ft_isascii : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_isdigit(void)
{
    int test_failed = 0;

    printf("Testing ft_isdigit...\n");

    // Test 1 : Test avec un caractère numérique (ici '5')
    char c1 = '5';
    int result1 = ft_isdigit(c1);
    int expected1 = isdigit(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for value '%c'\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère non numérique (ici 'a')
    char c2 = 'a';
    int result2 = ft_isdigit(c2);
    int expected2 = isdigit(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for value '%c'\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Test 3 : Test avec un caractère numérique (ici '0')
    char c3 = '0';
    int result3 = ft_isdigit(c3);
    int expected3 = isdigit(c3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for value '%c'\n", expected3, result3, c3);
        test_failed = 1;
    }

    // Test 4 : Test avec un caractère non numérique (ici '#')
    char c4 = '#';
    int result4 = ft_isdigit(c4);
    int expected4 = isdigit(c4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for value '%c'\n", expected4, result4, c4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_isdigit : ✅ réussi ✅​\n");
    } else {
        printf("test ft_isdigit : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_isprint(void)
{
    int test_failed = 0;

    printf("Testing ft_isprint...\n");

    // Test 1 : Test avec un caractère imprimable (65 correspond à 'A')
    int c1 = 65;
    int result1 = ft_isprint(c1);
    int expected1 = isprint(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for value %d\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère non imprimable (10 correspond à '\n')
    int c2 = 10;
    int result2 = ft_isprint(c2);
    int expected2 = isprint(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for value %d\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Test 3 : Test avec un caractère imprimable (32 correspond à un espace)
    int c3 = 32;
    int result3 = ft_isprint(c3);
    int expected3 = isprint(c3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for value %d\n", expected3, result3, c3);
        test_failed = 1;
    }

    // Test 4 : Test avec un caractère non imprimable (127 correspond à DEL)
    int c4 = 127;
    int result4 = ft_isprint(c4);
    int expected4 = isprint(c4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for value %d\n", expected4, result4, c4);
        test_failed = 1;
    }

    // Test 5 : Test avec un caractère imprimable (48 correspond à '0')
    int c5 = 48;
    int result5 = ft_isprint(c5);
    int expected5 = isprint(c5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %d, Got %d for value %d\n", expected5, result5, c5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_isprint : ✅ réussi ✅​\n");
    } else {
        printf("test ft_isprint : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_itoa(void)
{
    int test_failed = 0;

    printf("Testing ft_itoa...\n");

    // Test 1 : Test avec un nombre négatif
    char *result1 = ft_itoa(-12345);
    char expected1[10];
    sprintf(expected1, "%d", -12345);
    if (strcmp(result1, expected1) != 0) {
        printf("Test 1 failed: Expected: %s, Got: %s\n", expected1, result1);
        test_failed = 1;
    }
    free(result1);

    // Test 2 : Test avec un nombre positif
    char *result2 = ft_itoa(12345);
    char expected2[10];
    sprintf(expected2, "%d", 12345);
    if (strcmp(result2, expected2) != 0) {
        printf("Test 2 failed: Expected: %s, Got: %s\n", expected2, result2);
        test_failed = 1;
    }
    free(result2);

    // Test 3 : Test avec zéro
    char *result3 = ft_itoa(0);
    char expected3[] = "0";
    if (strcmp(result3, expected3) != 0) {
        printf("Test 3 failed: Expected: %s, Got: %s\n", expected3, result3);
        test_failed = 1;
    }
    free(result3);

    // Test 4 : Test avec le minimum des entiers (-2147483648)
    char *result4 = ft_itoa(-2147483648);
    char expected4[12];
    sprintf(expected4, "%ld", -2147483648);
    if (strcmp(result4, expected4) != 0) {
        printf("Test 4 failed: Expected: %s, Got: %s\n", expected4, result4);
        test_failed = 1;
    }
    free(result4);

    // Test 5 : Test avec un nombre très petit
    char *result5 = ft_itoa(-1);
    char expected5[] = "-1";
    if (strcmp(result5, expected5) != 0) {
        printf("Test 5 failed: Expected: %s, Got: %s\n", expected5, result5);
        test_failed = 1;
    }
    free(result5);

    // Test 6 : Test avec un nombre très grand
    char *result6 = ft_itoa(2147483647);
    char expected6[12];
    sprintf(expected6, "%d", 2147483647);
    if (strcmp(result6, expected6) != 0) {
        printf("Test 6 failed: Expected: %s, Got: %s\n", expected6, result6);
        test_failed = 1;
    }
    free(result6);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_itoa : ✅ réussi ✅​\n");
    } else {
        printf("test ft_itoa : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_memchr(void)
{
    int test_failed = 0;

    printf("Testing ft_memchr...\n");

    // Test 1 : Recherche du caractère 'f' dans "Libft test"
    char str1[] = "Libft test";
    char *result1 = (char *)ft_memchr(str1, 'f', strlen(str1)); // Casting en char*
    char *expected1 = (char *)memchr(str1, 'f', strlen(str1));  // Casting en char*
    if (result1 != expected1) {
        if (result1 == NULL || expected1 == NULL || str1 != result1) {
            printf("Test 1 failed: Expected '%s', Got '%s'\n", expected1 ? expected1 : "NULL", result1 ? result1 : "NULL");
        }
        test_failed = 1;
    }

    // Test 2 : Recherche d'un caractère non présent dans la chaîne
    char str2[] = "Libft test";
    char *result2 = (char *)ft_memchr(str2, 'z', strlen(str2)); // Casting en char*
    char *expected2 = (char *)memchr(str2, 'z', strlen(str2));  // Casting en char*
    if (result2 != expected2) {
        printf("Test 2 failed: Expected '%s', Got '%s'\n", expected2 ? expected2 : "NULL", result2 ? result2 : "NULL");
        test_failed = 1;
    }

    // Test 3 : Recherche du premier caractère dans une chaîne
    char str3[] = "Libft test";
    char *result3 = (char *)ft_memchr(str3, 'L', strlen(str3)); // Casting en char*
    char *expected3 = (char *)memchr(str3, 'L', strlen(str3));  // Casting en char*
    if (result3 != expected3) {
        printf("Test 3 failed: Expected '%s', Got '%s'\n", expected3 ? expected3 : "NULL", result3 ? result3 : "NULL");
        test_failed = 1;
    }

    // Test 4 : Recherche d'un caractère à la fin de la chaîne
    char str4[] = "Libft test";
    char *result4 = (char *)ft_memchr(str4, 't', strlen(str4)); // Casting en char*
    char *expected4 = (char *)memchr(str4, 't', strlen(str4));  // Casting en char*
    if (result4 != expected4) {
        printf("Test 4 failed: Expected '%s', Got '%s'\n", expected4 ? expected4 : "NULL", result4 ? result4 : "NULL");
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_memchr : ✅ réussi ✅​\n");
    } else {
        printf("test ft_memchr : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_memcmp(void)
{
    int test_failed = 0;

    printf("Testing ft_memcmp...\n");

    // Test 1 : Test de comparaison de deux chaînes identiques
    const char *s1 = "abc";
    const char *s2 = "abc";
    size_t n1 = 3;
    int result1 = ft_memcmp(s1, s2, n1);
    int expected1 = memcmp(s1, s2, n1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for comparing '%s' and '%s' with size %zu\n", expected1, result1, s1, s2, n1);
        test_failed = 1;
    }

    // Test 2 : Test de comparaison de deux chaînes différentes
    const char *s3 = "abc";
    const char *s4 = "abd";
    size_t n2 = 3;
    int result2 = ft_memcmp(s3, s4, n2);
    int expected2 = memcmp(s3, s4, n2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for comparing '%s' and '%s' with size %zu\n", expected2, result2, s3, s4, n2);
        test_failed = 1;
    }

    // Test 3 : Test de comparaison de chaînes avec des tailles différentes
    const char *s5 = "abc";
    const char *s6 = "abcd";
    size_t n3 = 3;  // On compare uniquement les 3 premiers caractères
    int result3 = ft_memcmp(s5, s6, n3);
    int expected3 = memcmp(s5, s6, n3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for comparing '%s' and '%s' with size %zu\n", expected3, result3, s5, s6, n3);
        test_failed = 1;
    }

    // Test 4 : Test avec des mémoires de tailles différentes
    const char *s7 = "abc";
    const char *s8 = "ab";
    size_t n4 = 3;  // Comparer les 3 premiers caractères, mais la seconde chaîne est plus courte
    int result4 = ft_memcmp(s7, s8, n4);
    int expected4 = memcmp(s7, s8, n4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for comparing '%s' and '%s' with size %zu\n", expected4, result4, s7, s8, n4);
        test_failed = 1;
    }

    // Test 5 : Test de comparaison de blocs de mémoire avec des valeurs non nulles
    const char *s9 = "Hello";
    const char *s10 = "Helxo";
    size_t n5 = 5;
    int result5 = ft_memcmp(s9, s10, n5);
    int expected5 = memcmp(s9, s10, n5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %d, Got %d for comparing '%s' and '%s' with size %zu\n", expected5, result5, s9, s10, n5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_memcmp : ✅ réussi ✅​\n");
    } else {
        printf("test ft_memcmp : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_memcpy(void)
{
    int test_failed = 0;

    printf("Testing ft_memcpy...\n");

    // Test 1 : Test de base avec une copie partielle (5 premiers caractères)
    char dest1[10] = "123456789";
    char src1[10] = "abcdefghi";
    ft_memcpy(dest1, src1, 5);
    printf("Test 1: Expected: abcde6789, Got: %s\n", dest1);
    if (strcmp(dest1, "abcde6789") != 0) {
        printf("Test 1 failed: Expected abcde6789, Got %s\n", dest1);
        test_failed = 1;
    }

    // Test 2 : Test avec une source plus courte que la destination
    char dest2[10] = "123456789";
    char src2[6] = "abcde";
    ft_memcpy(dest2, src2, 6);
    printf("Test 2: Expected: abcde6789, Got: %s\n", dest2);
    if (strcmp(dest2, "abcde6789") != 0) {
        printf("Test 2 failed: Expected abcde6789, Got %s\n", dest2);
        test_failed = 1;
    }

    // Test 3 : Test avec une source identique à la destination
    char dest3[10] = "abcdefghi";
    char src3[10] = "abcdefghi";
    ft_memcpy(dest3, src3, 10);
    printf("Test 3: Expected: abcdefghi, Got: %s\n", dest3);
    if (strcmp(dest3, "abcdefghi") != 0) {
        printf("Test 3 failed: Expected abcdefghi, Got %s\n", dest3);
        test_failed = 1;
    }

    // Test 4 : Test avec des tailles différentes (copie de 0 octet)
    char dest4[10] = "123456789";
    char src4[10] = "abcdefghi";
    ft_memcpy(dest4, src4, 0);
    printf("Test 4: Expected: 123456789, Got: %s\n", dest4);
    if (strcmp(dest4, "123456789") != 0) {
        printf("Test 4 failed: Expected 123456789, Got %s\n", dest4);
        test_failed = 1;
    }

    // Test 5 : Test avec des tailles supérieures à la taille de la source (copie partielle d'un tableau trop grand)
    char dest5[15] = "123456789";
    char src5[5] = "abcd";
    ft_memcpy(dest5, src5, 10);
    printf("Test 5: Expected: abcd56789, Got: %s\n", dest5);
    if (strcmp(dest5, "abcd56789") != 0) {
        printf("Test 5 failed: Expected abcd56789, Got %s\n", dest5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_memcpy : ✅ réussi ✅​\n");
    } else {
        printf("test ft_memcpy : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_memmove(void)
{
    int test_failed = 0;

    printf("Testing ft_memmove...\n");

    // Test 1 : Test avec un déplacement dans une zone mémoire qui se chevauche
    char dest1[] = "123456789";
    char expected1[] = "121234567"; // Après ft_memmove
    ft_memmove(dest1 + 2, dest1, 5);
    if (strcmp(dest1, expected1) != 0) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\"\n", expected1, dest1);
        test_failed = 1;
    }

    // Test 2 : Test sans chevauchement
    char dest2[] = "abcdefghij";
    char expected2[] = "abcdefabcdef"; // Après ft_memmove
    ft_memmove(dest2 + 6, dest2, 6);
    if (strcmp(dest2, expected2) != 0) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\"\n", expected2, dest2);
        test_failed = 1;
    }

    // Test 3 : Test avec une zone mémoire source et destination séparée
    char dest3[] = "hello";
    char src3[] = "world";
    char expected3[] = "world";
    ft_memmove(dest3, src3, 5);
    if (strcmp(dest3, expected3) != 0) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\"\n", expected3, dest3);
        test_failed = 1;
    }

    // Test 4 : Test avec un déplacement de 0 octet
    char dest4[] = "abcdef";
    ft_memmove(dest4, dest4, 0);  // Ne devrait rien changer
    char expected4[] = "abcdef";
    if (strcmp(dest4, expected4) != 0) {
        printf("Test 4 failed: Expected \"%s\", Got \"%s\"\n", expected4, dest4);
        test_failed = 1;
    }

    // Test 5 : Test avec des caractères spéciaux
    char dest5[] = "####$$$$$$";
    char expected5[] = "########$$$$$$"; // Après ft_memmove
    ft_memmove(dest5 + 4, dest5, 4);
    if (strcmp(dest5, expected5) != 0) {
        printf("Test 5 failed: Expected \"%s\", Got \"%s\"\n", expected5, dest5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_memmove : ✅ réussi ✅​\n");
    } else {
        printf("test ft_memmove : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_memset(void)
{
    int test_failed = 0;

    printf("Testing ft_memset...\n");

    // Test 1 : Remplir les 5 premiers caractères avec 'x'
    char str1[10] = "abcdefghi";
    char expected1[10] = "xxxxxfghi";
    ft_memset(str1, 'x', 5);
    if (strncmp(str1, expected1, 10) != 0) {
        printf("Test 1 failed: Expected: %s, Got: %s\n", expected1, str1);
        test_failed = 1;
    }

    // Test 2 : Remplir une chaîne vide
    char str2[10] = "";
    char expected2[10] = "xxxxxxx";
    ft_memset(str2, 'x', 7); // Remplir 7 premiers caractères avec 'x'
    if (strncmp(str2, expected2, 10) != 0) {
        printf("Test 2 failed: Expected: %s, Got: %s\n", expected2, str2);
        test_failed = 1;
    }

    // Test 3 : Remplir un tableau de 0's
    char str3[10] = "123456789";
    char expected3[10] = "000000789";
    ft_memset(str3, '0', 6); // Remplir les 6 premiers caractères avec '0'
    if (strncmp(str3, expected3, 10) != 0) {
        printf("Test 3 failed: Expected: %s, Got: %s\n", expected3, str3);
        test_failed = 1;
    }

    // Test 4 : Tester un remplissage complet (tout devient 'z')
    char str4[10] = "abcdefghi";
    char expected4[10] = "zzzzzzzzi";
    ft_memset(str4, 'z', 9); // Remplir tous les caractères avec 'z'
    if (strncmp(str4, expected4, 10) != 0) {
        printf("Test 4 failed: Expected: %s, Got: %s\n", expected4, str4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_memset : ✅ réussi ✅​\n");
    } else {
        printf("test ft_memset : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_putchar_fd(void)
{
    int test_failed = 0;
    char output[100];  // Buffer pour capturer la sortie
    FILE *fp;          // Fichier temporaire pour tester la sortie

    // Test 1: Test avec un caractère 'A' sur la sortie standard (fd = 1)
    fp = freopen("/tmp/test_output.txt", "w", stdout);  // Redirige stdout vers un fichier temporaire
    ft_putchar_fd('A', 1);
    fclose(fp);

    // Comparaison du résultat avec la sortie attendue
    fp = fopen("/tmp/test_output.txt", "r");
    if (fp) {
        fgets(output, sizeof(output), fp);
        fclose(fp);
        if (strcmp(output, "A") != 0) {
            printf("Test 1 failed: Expected 'A', Got '%s'\n", output);
            test_failed = 1;
        }
    }

    // Test 2: Test avec un caractère '\n' sur la sortie standard (fd = 1)
    fp = freopen("/tmp/test_output.txt", "w", stdout);
    ft_putchar_fd('\n', 1);
    fclose(fp);

    // Comparaison du résultat avec la sortie attendue
    fp = fopen("/tmp/test_output.txt", "r");
    if (fp) {
        fgets(output, sizeof(output), fp);
        fclose(fp);
        if (strcmp(output, "\n") != 0) {
            printf("Test 2 failed: Expected '\\n', Got '%s'\n", output);
            test_failed = 1;
        }
    }

    // Test 3: Test avec un caractère spécifique et sortie sur un fichier (fd = 2 pour stderr)
    fp = freopen("/tmp/test_output.txt", "w", stderr);  // Redirige stderr vers un fichier temporaire
    ft_putchar_fd('Z', 2);
    fclose(fp);

    // Comparaison du résultat avec la sortie attendue
    fp = fopen("/tmp/test_output.txt", "r");
    if (fp) {
        fgets(output, sizeof(output), fp);
        fclose(fp);
        if (strcmp(output, "Z") != 0) {
            printf("Test 3 failed: Expected 'Z', Got '%s'\n", output);
            test_failed = 1;
        }
    }

    // Suppression du fichier temporaire après test
    remove("/tmp/test_output.txt");

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_putchar_fd : ✅ réussi ✅​\n");
    } else {
        printf("test ft_putchar_fd : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_putendl_fd(void)
{
    int test_failed = 0;
    char *expected_output = "Hello, libft with newline!\n";
    
    // Rediriger la sortie standard vers un fichier temporaire
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        printf("Test failed: Unable to create temporary file\n");
        return;
    }

    // Sauvegarder l'original stdout
    FILE *original_stdout = stdout;
    stdout = temp_file;  // redirection de stdout vers temp_file

    // Tester la fonction ft_putendl_fd
    ft_putendl_fd("Hello, libft with newline!", 1);

    // Réinitialiser stdout
    stdout = original_stdout;

    // Repositionner le fichier temporaire au début
    fseek(temp_file, 0, SEEK_SET);

    // Lire le contenu du fichier temporaire
    char actual_output[256];
    size_t bytes_read = fread(actual_output, 1, sizeof(actual_output) - 1, temp_file);
    actual_output[bytes_read] = '\0';  // Assurez-vous que la chaîne est terminée par '\0'

    // Comparer la sortie obtenue avec celle attendue
    if (strcmp(actual_output, expected_output) != 0) {
        printf("Test failed: Expected '%s', Got '%s'\n", expected_output, actual_output);
        test_failed = 1;
    }

    // Fermer le fichier temporaire
    fclose(temp_file);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_putendl_fd : ✅ réussi ✅​\n");
    } else {
        printf("test ft_putendl_fd : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_putnbr_fd(void)
{
    int test_failed = 0;

    printf("Testing ft_putnbr_fd...\n");

    // Rediriger la sortie standard vers un fichier temporaire pour la comparaison
    FILE *tmp_file = fopen("test_output.txt", "w+");
    if (!tmp_file)
    {
        printf("Failed to open temporary file for output.\n");
        return;
    }

    // Test 1 : Afficher un nombre positif
    int n1 = 12345;
    ft_putnbr_fd(n1, fileno(tmp_file));  // Rediriger vers le fichier temporaire
    fflush(tmp_file);  // S'assurer que tout est écrit dans le fichier
    rewind(tmp_file);  // Revenir au début du fichier pour lire
    char result1[100];
    fgets(result1, sizeof(result1), tmp_file);
    char expected1[] = "12345";
    if (strcmp(result1, expected1) != 0)
    {
        printf("Test 1 failed: Expected '%s', Got '%s'\n", expected1, result1);
        test_failed = 1;
    }

    // Test 2 : Afficher un nombre négatif
    int n2 = -12345;
    fseek(tmp_file, 0, SEEK_SET);  // Réinitialiser le fichier
    ft_putnbr_fd(n2, fileno(tmp_file));
    fflush(tmp_file);
    rewind(tmp_file);
    char result2[100];
    fgets(result2, sizeof(result2), tmp_file);
    char expected2[] = "-12345";
    if (strcmp(result2, expected2) != 0)
    {
        printf("Test 2 failed: Expected '%s', Got '%s'\n", expected2, result2);
        test_failed = 1;
    }

    // Test 3 : Afficher zéro
    int n3 = 0;
    fseek(tmp_file, 0, SEEK_SET);
    ft_putnbr_fd(n3, fileno(tmp_file));
    fflush(tmp_file);
    rewind(tmp_file);
    char result3[100];
    fgets(result3, sizeof(result3), tmp_file);
    char expected3[] = "0";
    if (strcmp(result3, expected3) != 0)
    {
        printf("Test 3 failed: Expected '%s', Got '%s'\n", expected3, result3);
        test_failed = 1;
    }

    // Test 4 : Vérifier le comportement avec une valeur extrême
    int n4 = 2147483647; // Valeur maximale d'un int
    fseek(tmp_file, 0, SEEK_SET);
    ft_putnbr_fd(n4, fileno(tmp_file));
    fflush(tmp_file);
    rewind(tmp_file);
    char result4[100];
    fgets(result4, sizeof(result4), tmp_file);
    char expected4[] = "2147483647";
    if (strcmp(result4, expected4) != 0)
    {
        printf("Test 4 failed: Expected '%s', Got '%s'\n", expected4, result4);
        test_failed = 1;
    }

    // Test 5 : Vérifier le comportement avec la valeur minimale d'un int
    int n5 = -2147483648; // Valeur minimale d'un int
    fseek(tmp_file, 0, SEEK_SET);
    ft_putnbr_fd(n5, fileno(tmp_file));
    fflush(tmp_file);
    rewind(tmp_file);
    char result5[100];
    fgets(result5, sizeof(result5), tmp_file);
    char expected5[] = "-2147483648";
    if (strcmp(result5, expected5) != 0)
    {
        printf("Test 5 failed: Expected '%s', Got '%s'\n", expected5, result5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0)
    {
        printf("test ft_putnbr_fd : ✅ réussi ✅​\n");
    }
    else
    {
        printf("test ft_putnbr_fd : 👿 ​ça ne marche pas ​👿\n");
    }

    // Fermer le fichier et supprimer le fichier temporaire
    fclose(tmp_file);
    remove("test_output.txt");

	printf("\n\n\n\n\n");
}










void test_ft_putstr_fd(void)
{
    int test_failed = 0;
    char *test_string = "Hello, libft!\n";
    char buffer[128];
    
    // Test 1 : Tester si ft_putstr_fd écrit correctement dans le fichier descriptor 1 (stdout)
    int fd = 1; // Sortie standard (stdout)
    // On va rediriger la sortie vers un tampon
    FILE *fp = fdopen(fd, "w");
    if (fp == NULL) {
        printf("Failed to open file descriptor\n");
        return;
    }

    // Nettoyer le tampon avant le test
    memset(buffer, 0, sizeof(buffer));
    
    // Ecrire avec ft_putstr_fd
    ft_putstr_fd(test_string, fd);
    
    // Capture la sortie standard
    fflush(fp); // Nous forçons l'écriture de tout ce qui est dans le tampon vers la sortie
    fseek(fp, 0, SEEK_SET);
    
    // Lire le contenu de la sortie standard capturée
    fgets(buffer, sizeof(buffer), fp);
    
    // Comparer le résultat attendu
    if (strcmp(buffer, test_string) != 0) {
        printf("Test 1 failed: Expected '%s', Got '%s'\n", test_string, buffer);
        test_failed = 1;
    }

    // Test 2 : Test avec un autre test string
    char *test_string_2 = "Another test string.\n";
    memset(buffer, 0, sizeof(buffer));
    
    ft_putstr_fd(test_string_2, fd);
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);

    if (strcmp(buffer, test_string_2) != 0) {
        printf("Test 2 failed: Expected '%s', Got '%s'\n", test_string_2, buffer);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_putstr_fd : ✅ réussi ✅​\n");
    } else {
        printf("test ft_putstr_fd : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_split(void)
{
    int test_failed = 0;
    
    printf("Testing ft_split...\n");

    // Test 1 : Cas de séparation d'une phrase avec des espaces
    char **result1 = ft_split("Hello World Libft", " ");
    char *expected1[] = {"Hello", "World", "Libft", NULL}; // Résultat attendu
    for (int i = 0; result1[i] && expected1[i]; i++) {
        if (strcmp(result1[i], expected1[i]) != 0) {
            printf("Test 1 failed: Expected %s, Got %s\n", expected1[i], result1[i]);
            test_failed = 1;
        }
    }
    if (result1) {
        for (int i = 0; result1[i]; i++)
            free(result1[i]);
        free(result1);
    }

    // Test 2 : Cas avec des espaces au début et à la fin
    char **result2 = ft_split("   Test Split Function   ", " ");
    char *expected2[] = {"Test", "Split", "Function", NULL}; // Résultat attendu
    for (int i = 0; result2[i] && expected2[i]; i++) {
        if (strcmp(result2[i], expected2[i]) != 0) {
            printf("Test 2 failed: Expected %s, Got %s\n", expected2[i], result2[i]);
            test_failed = 1;
        }
    }
    if (result2) {
        for (int i = 0; result2[i]; i++)
            free(result2[i]);
        free(result2);
    }

    // Test 3 : Cas avec plusieurs espaces entre les mots
    char **result3 = ft_split("Multiple   spaces    between words", " ");
    char *expected3[] = {"Multiple", "spaces", "between", "words", NULL}; // Résultat attendu
    for (int i = 0; result3[i] && expected3[i]; i++) {
        if (strcmp(result3[i], expected3[i]) != 0) {
            printf("Test 3 failed: Expected %s, Got %s\n", expected3[i], result3[i]);
            test_failed = 1;
        }
    }
    if (result3) {
        for (int i = 0; result3[i]; i++)
            free(result3[i]);
        free(result3);
    }

    // Test 4 : Cas avec une chaîne vide
    char **result4 = ft_split("", " ");
    if (result4 && result4[0] != NULL) {
        printf("Test 4 failed: Expected NULL, Got %s\n", result4[0]);
        test_failed = 1;
    }
    free(result4);

    // Test 5 : Cas avec un seul mot sans espace
    char **result5 = ft_split("SingleWord", " ");
    char *expected5[] = {"SingleWord", NULL}; // Résultat attendu
    for (int i = 0; result5[i] && expected5[i]; i++) {
        if (strcmp(result5[i], expected5[i]) != 0) {
            printf("Test 5 failed: Expected %s, Got %s\n", expected5[i], result5[i]);
            test_failed = 1;
        }
    }
    if (result5) {
        for (int i = 0; result5[i]; i++)
            free(result5[i]);
        free(result5);
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_split : ✅ réussi ✅​\n");
    } else {
        printf("test ft_split : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strchr(void)
{
    int test_failed = 0;
    
    printf("Testing ft_strchr...\n");

    // Test 1 : Test avec un caractère existant dans la chaîne
    char *str1 = "Hello, world!";
    char *result1 = ft_strchr(str1, 'w');
    char *expected1 = strchr(str1, 'w');
    if (result1 != expected1) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\" for char 'w'\n", expected1, result1);
        test_failed = 1;
    }

    // Test 2 : Test avec un caractère qui n'existe pas dans la chaîne
    char *result2 = ft_strchr(str1, 'z');
    char *expected2 = strchr(str1, 'z');
    if (result2 != expected2) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\" for char 'z'\n", expected2, result2);
        test_failed = 1;
    }

    // Test 3 : Test avec un caractère au début de la chaîne
    char *result3 = ft_strchr(str1, 'H');
    char *expected3 = strchr(str1, 'H');
    if (result3 != expected3) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\" for char 'H'\n", expected3, result3);
        test_failed = 1;
    }

    // Test 4 : Test avec un caractère nul '\0' à la fin de la chaîne
    char *result4 = ft_strchr(str1, '\0');
    char *expected4 = strchr(str1, '\0');
    if (result4 != expected4) {
        printf("Test 4 failed: Expected \"%s\", Got \"%s\" for char '\\0'\n", expected4, result4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strchr : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strchr : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strdup(void)
{
    int test_failed = 0;

    printf("Testing ft_strdup...\n");

    // Test 1 : Cas de base, dupliquer une chaîne simple
    char *str1 = "Libft";
    char *dup1 = ft_strdup(str1);
    char *expected1 = strdup(str1);
    if (dup1 == NULL || expected1 == NULL || strcmp(dup1, expected1) != 0) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\"\n", expected1, dup1);
        test_failed = 1;
    }
    free(dup1);
    free(expected1);

    // Test 2 : Cas d'une chaîne vide
    char *str2 = "";
    char *dup2 = ft_strdup(str2);
    char *expected2 = strdup(str2);
    if (dup2 == NULL || expected2 == NULL || strcmp(dup2, expected2) != 0) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\"\n", expected2, dup2);
        test_failed = 1;
    }
    free(dup2);
    free(expected2);

    // Test 3 : Cas d'une chaîne contenant des espaces et des caractères spéciaux
    char *str3 = "Libft 42!";
    char *dup3 = ft_strdup(str3);
    char *expected3 = strdup(str3);
    if (dup3 == NULL || expected3 == NULL || strcmp(dup3, expected3) != 0) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\"\n", expected3, dup3);
        test_failed = 1;
    }
    free(dup3);
    free(expected3);

    // Test 4 : Cas d'une chaîne très longue
    char *str4 = "A long string for testing purposes...1234567890";
    char *dup4 = ft_strdup(str4);
    char *expected4 = strdup(str4);
    if (dup4 == NULL || expected4 == NULL || strcmp(dup4, expected4) != 0) {
        printf("Test 4 failed: Expected \"%s\", Got \"%s\"\n", expected4, dup4);
        test_failed = 1;
    }
    free(dup4);
    free(expected4);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strdup : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strdup : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










/* void test_ft_striteri(void)
{
    int test_failed = 0;

    // Message initial
    printf("Testing ft_striteri...\n");

    // Test 1 : Test simple avec un tableau de caractères "abcd"
    char str1[] = "abcd";
    ft_striteri(str1, [](unsigned int i, char *c) { *c += i; });
    if (strcmp(str1, "aceg") != 0) {
        printf("Test 1 failed: Expected aceg, Got: %s\n", str1);
        test_failed = 1;
    }

    // Test 2 : Test avec un tableau vide
    char str2[] = "";
    ft_striteri(str2, [](unsigned int i, char *c) { *c += i; });
    if (strcmp(str2, "") != 0) {
        printf("Test 2 failed: Expected empty string, Got: %s\n", str2);
        test_failed = 1;
    }

    // Test 3 : Test avec une seule lettre
    char str3[] = "z";
    ft_striteri(str3, [](unsigned int i, char *c) { *c += i; });
    if (strcmp(str3, "z") != 0) {
        printf("Test 3 failed: Expected z, Got: %s\n", str3);
        test_failed = 1;
    }

    // Test 4 : Test avec une chaîne contenant des majuscules
    char str4[] = "XYZ";
    ft_striteri(str4, [](unsigned int i, char *c) { *c += i; });
    if (strcmp(str4, "XYC") != 0) {
        printf("Test 4 failed: Expected XYZ, Got: %s\n", str4);
        test_failed = 1;
    }

    // Test 5 : Test avec un tableau où les valeurs sont déjà des chiffres
    char str5[] = "1234";
    ft_striteri(str5, [](unsigned int i, char *c) { *c += i; });
    if (strcmp(str5, "1357") != 0) {
        printf("Test 5 failed: Expected 1357, Got: %s\n", str5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_striteri : ✅ réussi ✅​\n");
    } else {
        printf("test ft_striteri : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
} */










void test_ft_strjoin(void)
{
    int test_failed = 0;

    printf("Testing ft_strjoin...\n");

    // Test 1 : Chaînes classiques (Hello + World)
    char *str1 = "Hello ";
    char *str2 = "World";
    char *joined1 = ft_strjoin(str1, str2);
    char *expected1 = "Hello World";
    if (strcmp(joined1, expected1) != 0) {
        printf("Teste chaînes de caractèr 1 failed: Expected '%s', Got '%s'\n", expected1, joined1);
        test_failed = 1;
    }
    free(joined1);

    // Test 2 : Première chaîne vide
    char *str3 = "";
    char *str4 = "World";
    char *joined2 = ft_strjoin(str3, str4);
    char *expected2 = "World";
    if (strcmp(joined2, expected2) != 0) {
        printf("Test 2 failed: Expected '%s', Got '%s'\n", expected2, joined2);
        test_failed = 1;
    }
    free(joined2);

    // Test 3 : Deuxième chaîne vide
    char *str5 = "Hello ";
    char *str6 = "";
    char *joined3 = ft_strjoin(str5, str6);
    char *expected3 = "Hello ";
    if (strcmp(joined3, expected3) != 0) {
        printf("Teste chaînes de caractèr 3 failed: Expected '%s', Got '%s'\n", expected3, joined3);
        test_failed = 1;
    }
    free(joined3);

    // Test 4 : Deux chaînes vides
    char *str7 = "";
    char *str8 = "";
    char *joined4 = ft_strjoin(str7, str8);
    char *expected4 = "";
    if (strcmp(joined4, expected4) != 0) {
        printf("Test 4 failed: Expected '%s', Got '%s'\n", expected4, joined4);
        test_failed = 1;
    }
    free(joined4);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strjoin : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strjoin : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strlcat(void)
{
    int test_failed = 0;

    printf("Testing ft_strlcat...\n");

    // Test 1 : Test de base, concaténation de chaînes de taille suffisante
    char dest1[20] = "Hello, ";
    size_t result1 = ft_strlcat(dest1, "world!", 20);
    size_t expected1 = strlcat(dest1, "world!", 20);
    if (result1 != expected1 || strcmp(dest1, "Hello, world!") != 0) {
        printf("Test 1 failed: Expected dest = \"Hello, world!\", Got dest = \"%s\", Expected return = %zu, Got return = %zu\n", dest1, expected1, result1);
        test_failed = 1;
    }

    // Test 2 : Test avec buffer destination plus petit que la chaîne source
    char dest2[10] = "Hi, ";
    size_t result2 = ft_strlcat(dest2, "there!", 10);
    size_t expected2 = strlcat(dest2, "there!", 10);
    if (result2 != expected2 || strcmp(dest2, "Hi, ther") != 0) {  // On ne peut pas tout copier, on s'attend à "Hi, ther"
        printf("Test 2 failed: Expected dest = \"Hi, ther\", Got dest = \"%s\", Expected return = %zu, Got return = %zu\n", dest2, expected2, result2);
        test_failed = 1;
    }

    // Test 3 : Test avec taille insuffisante (dest vide)
    char dest3[6] = "";
    size_t result3 = ft_strlcat(dest3, "hello", 6);
    size_t expected3 = strlcat(dest3, "hello", 6);
    if (result3 != expected3 || strcmp(dest3, "hello") != 0) {
        printf("Test 3 failed: Expected dest = \"hello\", Got dest = \"%s\", Expected return = %zu, Got return = %zu\n", dest3, expected3, result3);
        test_failed = 1;
    }

    // Test 4 : Test de la taille exacte de la chaîne concaténée
    char dest4[12] = "Test: ";
    size_t result4 = ft_strlcat(dest4, "12345", 12);
    size_t expected4 = strlcat(dest4, "12345", 12);
    if (result4 != expected4 || strcmp(dest4, "Test: 12345") != 0) {
        printf("Test 4 failed: Expected dest = \"Test: 12345\", Got dest = \"%s\", Expected return = %zu, Got return = %zu\n", dest4, expected4, result4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strlcat : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strlcat : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}











void test_ft_strlcpy(void)
{
    int test_failed = 0;

    printf("Testing ft_strlcpy...\n");

    // Test 1 : Test de base avec une taille suffisante
    char dest1[20];
    size_t result1 = ft_strlcpy(dest1, "Hello", 20);
    size_t expected1 = strlcpy(dest1, "Hello", 20);
    if (result1 != expected1 || strcmp(dest1, "Hello") != 0) {
        printf("Test 1 failed: Expected %zu, Got %zu for dest: '%s'\n", expected1, result1, dest1);
        test_failed = 1;
    }

    // Test 2 : Test avec une taille plus petite que la chaîne source
    char dest2[5];
    size_t result2 = ft_strlcpy(dest2, "Hello", 5);
    size_t expected2 = strlcpy(dest2, "Hello", 5);
    if (result2 != expected2 || strcmp(dest2, "Hell") != 0) { // 4 caractères devraient être copiés
        printf("Test 2 failed: Expected %zu, Got %zu for dest: '%s'\n", expected2, result2, dest2);
        test_failed = 1;
    }

    // Test 3 : Test avec une taille égale à la longueur de la chaîne source
    char dest3[6];
    size_t result3 = ft_strlcpy(dest3, "Hello", 6);
    size_t expected3 = strlcpy(dest3, "Hello", 6);
    if (result3 != expected3 || strcmp(dest3, "Hello") != 0) {
        printf("Test 3 failed: Expected %zu, Got %zu for dest: '%s'\n", expected3, result3, dest3);
        test_failed = 1;
    }

    // Test 4 : Test avec une taille nulle
    char dest4[20];
    size_t result4 = ft_strlcpy(dest4, "Hello", 0);
    size_t expected4 = strlcpy(dest4, "Hello", 0);
    if (result4 != expected4 || dest4[0] != '\0') {
        printf("Test 4 failed: Expected %zu, Got %zu for dest: '%s'\n", expected4, result4, dest4);
        test_failed = 1;
    }

    // Test 5 : Test avec une chaîne vide source
    char dest5[20];
    size_t result5 = ft_strlcpy(dest5, "", 20);
    size_t expected5 = strlcpy(dest5, "", 20);
    if (result5 != expected5 || strcmp(dest5, "") != 0) {
        printf("Test 5 failed: Expected %zu, Got %zu for dest: '%s'\n", expected5, result5, dest5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strlcpy : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strlcpy : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strlen(void)
{
    int test_failed = 0;

    printf("Testing ft_strlen...\n");

    // Test 1 : Test avec une chaîne de caractères de longueur 5
    const char *str1 = "Hello";
    size_t result1 = ft_strlen(str1);
    size_t expected1 = strlen(str1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %zu, Got %zu for string \"%s\"\n", expected1, result1, str1);
        test_failed = 1;
    }

    // Test 2 : Test avec une chaîne vide
    const char *str2 = "";
    size_t result2 = ft_strlen(str2);
    size_t expected2 = strlen(str2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %zu, Got %zu for string \"%s\"\n", expected2, result2, str2);
        test_failed = 1;
    }

    // Test 3 : Test avec une chaîne avec des espaces
    const char *str3 = "   ";
    size_t result3 = ft_strlen(str3);
    size_t expected3 = strlen(str3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %zu, Got %zu for string \"%s\"\n", expected3, result3, str3);
        test_failed = 1;
    }

    // Test 4 : Test avec une chaîne avec un seul caractère
    const char *str4 = "A";
    size_t result4 = ft_strlen(str4);
    size_t expected4 = strlen(str4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %zu, Got %zu for string \"%s\"\n", expected4, result4, str4);
        test_failed = 1;
    }

    // Test 5 : Test avec une chaîne très longue
    const char *str5 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    size_t result5 = ft_strlen(str5);
    size_t expected5 = strlen(str5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %zu, Got %zu for string \"%s\"\n", expected5, result5, str5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strlen : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strlen : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










// Fonction auxiliaire pour transformation
char modify_char(unsigned int i, char c) {
    return c + i;
}

void test_ft_strmapi(void)
{
    int test_failed = 0;

    printf("Testing ft_strmapi...\n");

    // Test 1 : Test avec la chaîne "abcd" et une fonction qui modifie chaque caractère selon son indice
    char *str1 = "abcd";
    char *result1 = ft_strmapi(str1, modify_char);
    char expected1[] = "aceg";  // Fonction attendue : 'a' + 0 = 'a', 'b' + 1 = 'c', 'c' + 2 = 'e', 'd' + 3 = 'g'

    if (strcmp(result1, expected1) != 0) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\"\n", expected1, result1);
        test_failed = 1;
    } else {
        printf("Test 1 passed\n");
    }
    free(result1);

    // Test 2 : Test avec une chaîne vide ""
    char *str2 = "";
    char *result2 = ft_strmapi(str2, modify_char);
    char expected2[] = "";  // La chaîne vide doit rester vide

    if (strcmp(result2, expected2) != 0) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\"\n", expected2, result2);
        test_failed = 1;
    } else {
        printf("Test 2 passed\n");
    }
    free(result2);

    // Test 3 : Test avec une chaîne composée de caractères spéciaux
    char *str3 = "!@#$";
    char *result3 = ft_strmapi(str3, modify_char);
    char expected3[] = "!@#$";  // Les caractères spéciaux ne devraient pas changer avec l'index

    if (strcmp(result3, expected3) != 0) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\"\n", expected3, result3);
        test_failed = 1;
    } else {
        printf("Test 3 passed\n");
    }
    free(result3);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strmapi : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strmapi : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strncmp(void)
{
    int test_failed = 0;

    printf("Testing ft_strncmp...\n");

    // Test 1 : Test avec des chaînes identiques
    const char *str1 = "abc";
    const char *str2 = "abc";
    size_t n1 = 3;
    int result1 = ft_strncmp(str1, str2, n1);
    int expected1 = strncmp(str1, str2, n1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %d, Got %d for comparing '%s' and '%s'\n", expected1, result1, str1, str2);
        test_failed = 1;
    }

    // Test 2 : Test avec des chaînes différentes à la dernière position
    const char *str3 = "abc";
    const char *str4 = "abd";
    size_t n2 = 3;
    int result2 = ft_strncmp(str3, str4, n2);
    int expected2 = strncmp(str3, str4, n2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %d, Got %d for comparing '%s' and '%s'\n", expected2, result2, str3, str4);
        test_failed = 1;
    }

    // Test 3 : Test avec une longueur de comparaison partielle
    const char *str5 = "abcdef";
    const char *str6 = "abcxyz";
    size_t n3 = 4;  // Comparer uniquement les 4 premiers caractères
    int result3 = ft_strncmp(str5, str6, n3);
    int expected3 = strncmp(str5, str6, n3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %d, Got %d for comparing '%s' and '%s' with length %zu\n", expected3, result3, str5, str6, n3);
        test_failed = 1;
    }

    // Test 4 : Test avec des chaînes de longueur différente
    const char *str7 = "abc";
    const char *str8 = "abcdef";
    size_t n4 = 3;  // Comparer les 3 premiers caractères
    int result4 = ft_strncmp(str7, str8, n4);
    int expected4 = strncmp(str7, str8, n4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %d, Got %d for comparing '%s' and '%s'\n", expected4, result4, str7, str8);
        test_failed = 1;
    }

    // Test 5 : Test avec une longueur de comparaison de 0 (devrait toujours être égal)
    const char *str9 = "abc";
    const char *str10 = "abd";
    size_t n5 = 0;  // Comparer les 0 premiers caractères
    int result5 = ft_strncmp(str9, str10, n5);
    int expected5 = strncmp(str9, str10, n5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %d, Got %d for comparing '%s' and '%s' with length 0\n", expected5, result5, str9, str10);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strncmp : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strncmp : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strnstr(void)
{
    int test_failed = 0;

    printf("Testing ft_strnstr...\n");

    // Test 1 : Recherche de la sous-chaîne "world" dans "Hello world"
    const char *haystack1 = "Hello world";
    const char *needle1 = "world";
    char *result1 = ft_strnstr(haystack1, needle1, 11); // La longueur de "Hello world" est 11
    const char *expece chaînes de caractère chaînes de caractèrted1 = strstr(haystack1, needle1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %s, Got %s for haystack '%s' and needle '%s'\n",
               expected1, result1, haystack1, needle1);
        test_failed = 1;
    }

    // Test 2 : Recherche d'une sous-chaîne absente
    const char *haystack2 = "Hello world";
    const char *needle2 = "test";
    char *result2 = ft_strnstr(haystack2, needle2, 11); 
    const char *expected2 = strstr(haystack2, needle2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %s, Got %s for haystack '%s' and needle '%s'\n",
               expected2, result2, haystack2, needle2);
        test_failed = 1;
    }

    // Test 3 : Recherche avec une longueur plus petite que celle du haystack
    const char *haystack3 = "Hello world";
    const char *needle3 = "world";
    char *result3 = ft_strnstr(haystack3, needle3, 5); // Recherche limitée à "Hello"
    const char *expected3 = strstr(haystack3, needle3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %s, Got %s for haystack '%s' and needle '%s'\n",
               expecte chaînes de caractèred3, result3, haystack3, needle3);
        test_failed = 1;
    }

    // Test 4 : Recherche avec une sous-chaîne vide
    const char *haystack4 = "Hello world";
    const char *needle4 = "";
    char *result4 = ft_strnstr(haystack4, needle4, 11); // Recherche d'une chaîne vide
    const char *expected4 = strstr(haystack4, needle4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %s, Got %s for haystack '%s' and needle '%s'\n",
               expected4, result4, haystack4, needle4);
        test_failed = 1;
    }

    // Test 5 : Recherche avec le needle plus long que le haystack
    const char *haystack5 = "Hello";
    const char *needle5 = "Hello world";
    char *result5 = ft_strnstr(haystack5, needle5, 5); // Recherche de "Hello world" dans "Hello"
    const char *expected5 = strstr(haystack5, needle5);
    if (result5 != expected5) {
        printf("Test 5 failed: Expected %s, Got %s for haystack '%s' and needle '%s'\n",
               expected5, result5, haystack5, needle5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strnstr : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strnstr : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strrchr(void)
{
    int test_failed = 0;

    printf("Testing ft_strrchr...\n");

    // Test 1 : Recherche du dernier 'w' dans "Hello, world!"
    char *str1 = "Hello, world!";
    char *result1 = ft_strrchr(str1, 'w');
    char *expected1 = strrchr(str1, 'w');
    if (result1 != expected1) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\" for string \"%s\"\n", expected1, result1, str1);
        test_failed = 1;
    }

    // Test 2 : Recherche d'un caractère non présent dans la chaîne
    char *str2 = "Hello, world!";
    char *result2 = ft_strrchr(str2, 'z');
    char *expected2 = strrchr(str2, 'z');
    if (result2 != expected2) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\" for string \"%s\"\n", expected2, result2, str2);
        test_failed = 1;
    }

    // Test 3 : Recherche du dernier 'o' dans "Hello, world!"
    char *str3 = "Hello, world!";
    char *result3 = ft_strrchr(str3, 'o');
    char *expected3 = strrchr(str3, 'o');
    if (result3 != expected3) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\" for string \"%s\"\n", expected3, result3, str3);
        test_failed = 1;
    }

    // Test 4 : Recherche du caractère nul '\0' à la fin de la chaîne
    char *str4 = "Hello, world!";
    char *result4 = ft_strrchr(str4, '\0');
    char *expected4 = strrchr(str4, '\0');
    if (result4 != expected4) {
        printf("Test 4 failed: Expected \"%s\", Got \"%s\" for string \"%s\"\n", expected4, result4, str4);
        test_failed = 1;
    }

    // Test 5 : Recherche dans une chaîne vide
    char *str5 = "";
    char *result5 = ft_strrchr(str5, 'a');
    char *expected5 = strrchr(str5, 'a');
    if (result5 != expected5) {
        printf("Test 5 failed: Expected \"%s\", Got \"%s\" for string \"%s\"\n", expected5, result5, str5);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strrchr : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strrchr : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_strtrim(void)
{
    int test_failed = 0;
    
    printf("Testing ft_strtrim...\n");

    // Test 1 : Tester une chaîne avec des espaces autour
    char *str1 = "  Hello  ";
    char *set1 = " ";
    char *expected1 = "Hello";
    char *result1 = ft_strtrim(str1, set1);
    if (strcmp(result1, expected1) != 0) {
        printf("Test 1 failed: Expected \"%s\", Got \"%s\" for input \"%s\"\n", expected1, result1, str1);
        test_failed = 1;
    }
    free(result1);  // Libérer la mémoire allouée

    // Test 2 : Tester une chaîne avec un set de caractères plus large
    char *str2 = "abcHelloabc";
    char *set2 = "abc";
    char *expected2 = "Hello";
    char *result2 = ft_strtrim(str2, set2);
    if (strcmp(result2, expected2) != 0) {
        printf("Test 2 failed: Expected \"%s\", Got \"%s\" for input \"%s\"\n", expected2, result2, str2);
        test_failed = 1;
    }
    free(result2);

    // Test 3 : Tester une chaîne sans caractères à couper
    char *str3 = "NoSpaces";
    char *set3 = " ";
    char *expected3 = "NoSpaces";
    char *result3 = ft_strtrim(str3, set3);
    if (strcmp(result3, expected3) != 0) {
        printf("Test 3 failed: Expected \"%s\", Got \"%s\" for input \"%s\"\n", expected3, result3, str3);
        test_failed = 1;
    }
    free(result3);

    // Test 4 : Tester une chaîne entièrement composée de caractères à couper
    char *str4 = "     ";
    char *set4 = " ";
    char *expected4 = "";
    char *result4 = ft_strtrim(str4, set4);
    if (strcmp(result4, expected4) != 0) {
        printf("Test 4 failed: Expected \"%s\", Got \"%s\" for input \"%s\"\n", expected4, result4, str4);
        test_failed = 1;
    }
    free(result4);

    // Test 5 : Tester une chaîne vide
    char *str5 = "";
    char *set5 = " ";
    char *expected5 = "";
    char *result5 = ft_strtrim(str5, set5);
    if (strcmp(result5, expected5) != 0) {
        printf("Test 5 failed: Expected \"%s\", Got \"%s\" for input \"%s\"\n", expected5, result5, str5);
        test_failed = 1;
    }
    free(result5);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_strtrim : ✅ réussi ✅​\n");
    } else {
        printf("test ft_strtrim : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_substr(void)
{
    int test_failed = 0;

    printf("Testing ft_substr...\n");

    // Test 1 : Extraire une sous-chaîne normale
    char *result1 = ft_substr("Hello", 1, 3);
    char *expected1 = "ell";
    if (strcmp(result1, expected1) != 0) {
        printf("Test 1 failed: Expected '%s', Got '%s'\n", expected1, result1);
        test_failed = 1;
    }
    free(result1);

    // Test 2 : Extraire une sous-chaîne avec un index de départ plus grand que la chaîne
    char *result2 = ft_substr("Hello", 10, 3);
    char *expected2 = "";  // Une chaîne vide car l'index est trop grand
    if (strcmp(result2, expected2) != 0) {
        printf("Test 2 failed: Expected '%s', Got '%s'\n", expected2, result2);
        test_failed = 1;
    }
    free(result2);

    // Test 3 : Extraire une sous-chaîne avec une longueur nulle
    char *result3 = ft_substr("Hello", 1, 0);
    char *expected3 = "";  // Une chaîne vide car la longueur est nulle
    if (strcmp(result3, expected3) != 0) {
        printf("Test 3 failed: Expected '%s', Got '%s'\n", expected3, result3);
        test_failed = 1;
    }
    free(result3);

    // Test 4 : Extraire une sous-chaîne qui va jusqu'à la fin de la chaîne source
    char *result4 = ft_substr("Hello", 1, 10);
    char *expected4 = "ello";  // Doit extraire "ello", même si la longueur demandée est plus grande
    if (strcmp(result4, expected4) != 0) {
        printf("Test 4 failed: Expected '%s', Got '%s'\n", expected4, result4);
        test_failed = 1;
    }
    free(result4);

    // Test 5 : Cas où la chaîne est vide
    char *result5 = ft_substr("", 0, 3);
    char *expected5 = "";  // Une chaîne vide
    if (strcmp(result5, expected5) != 0) {
        printf("Test 5 failed: Expected '%s', Got '%s'\n", expected5, result5);
        test_failed = 1;
    }
    free(result5);

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_substr : ✅ réussi ✅​\n");
    } else {
        printf("test ft_substr : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}











void test_ft_tolower(void)
{
    int test_failed = 0;

    printf("Testing ft_tolower...\n");

    // Test 1 : Test avec une lettre majuscule
    char input1 = 'A';
    char result1 = ft_tolower(input1);
    char expected1 = tolower(input1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected %c, Got %c for input %c\n", expected1, result1, input1);
        test_failed = 1;
    }

    // Test 2 : Test avec une lettre minuscule (devrait rester inchangée)
    char input2 = 'a';
    char result2 = ft_tolower(input2);
    char expected2 = tolower(input2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected %c, Got %c for input %c\n", expected2, result2, input2);
        test_failed = 1;
    }

    // Test 3 : Test avec un caractère non-alphabétique (devrait rester inchangé)
    char input3 = '1';
    char result3 = ft_tolower(input3);
    char expected3 = tolower(input3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected %c, Got %c for input %c\n", expected3, result3, input3);
        test_failed = 1;
    }

    // Test 4 : Test avec un autre caractère non-alphabétique (devrait aussi rester inchangé)
    char input4 = '!';
    char result4 = ft_tolower(input4);
    char expected4 = tolower(input4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected %c, Got %c for input %c\n", expected4, result4, input4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_tolower : ✅ réussi ✅​\n");
    } else {
        printf("test ft_tolower : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










void test_ft_toupper(void)
{
    int test_failed = 0;

    printf("Testing ft_toupper...\n");

    // Test 1 : Conversion d'une lettre minuscule en majuscule
    char c1 = 'a';
    char result1 = ft_toupper(c1);
    char expected1 = toupper(c1);
    if (result1 != expected1) {
        printf("Test 1 failed: Expected '%c', Got '%c' for character '%c'\n", expected1, result1, c1);
        test_failed = 1;
    }

    // Test 2 : Lettre déjà en majuscule (ne devrait pas changer)
    char c2 = 'A';
    char result2 = ft_toupper(c2);
    char expected2 = toupper(c2);
    if (result2 != expected2) {
        printf("Test 2 failed: Expected '%c', Got '%c' for character '%c'\n", expected2, result2, c2);
        test_failed = 1;
    }

    // Test 3 : Un caractère non alphabétique (devrait rester inchangé)
    char c3 = '1';
    char result3 = ft_toupper(c3);
    char expected3 = toupper(c3);
    if (result3 != expected3) {
        printf("Test 3 failed: Expected '%c', Got '%c' for character '%c'\n", expected3, result3, c3);
        test_failed = 1;
    }

    // Test 4 : Un caractère spécial (devrait rester inchangé)
    char c4 = '@';
    char result4 = ft_toupper(c4);
    char expected4 = toupper(c4);
    if (result4 != expected4) {
        printf("Test 4 failed: Expected '%c', Got '%c' for character '%c'\n", expected4, result4, c4);
        test_failed = 1;
    }

    // Résultat final
    if (test_failed == 0) {
        printf("test ft_toupper : ✅ réussi ✅​\n");
    } else {
        printf("test ft_toupper : 👿 ​ça ne marche pas ​👿\n");
    }

	printf("\n\n\n\n\n");
}










int main(void)
{
    test_ft_atoi();
    test_ft_bzero();
    test_ft_calloc();
    test_ft_isalnum();
    test_ft_isalpha();
    test_ft_isascii();
    test_ft_isdigit();
    test_ft_isprint();
    test_ft_itoa();
    test_ft_memchr();
    test_ft_memcmp();
    test_ft_memcpy();
    test_ft_memmove();
    test_ft_memset();
    test_ft_putchar_fd();
    test_ft_putendl_fd();
    test_ft_putnbr_fd();
    test_ft_putstr_fd();
    test_ft_split();
    test_ft_strchr();
    test_ft_strdup();
    /* test_ft_striteri(); */
    test_ft_strjoin();
    test_ft_strlcat();
    test_ft_strlcpy();
    test_ft_strlen();
    test_ft_strmapi();
    test_ft_strncmp();
    test_ft_strnstr();
    test_ft_strrchr();
    test_ft_strtrim();
    test_ft_substr();
    test_ft_tolower();
    test_ft_toupper();
    return (0);
}
