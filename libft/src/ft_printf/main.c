/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:18:46 by nchaize-          #+#    #+#             */
/*   Updated: 2023/12/11 11:04:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "include/ft_printf.h"

int main()
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	char	*s = NULL;

	printf("============= CONVERTER: c ============\n");
	printf("Test 1 : %%c 1 char\n");
	if (printf("%c\n", 'c') == ft_printf("%c\n", 'c'))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n");
	printf("Test 2 : %%c%%c 2 char\n");
	if (printf("%c%c\n", 'c', 'a') == ft_printf("%c%c\n", 'c', 'a'))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : this is a test %%c ...\n");
	if (printf("this is a test %c this is a test\n", 'o') == ft_printf("this is a test %c this is a test\n", 'o'))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : %%c%%c%%c%%c%%c%%c\n");
	if (printf("%c%c%c%c%c%c%c\n", 'a', 'b', 'c', 'd', 'e', 'f', 'g') == ft_printf("%c%c%c%c%c%c%c\n", 'a', 'b', 'c', 'd', 'e', 'f', 'g'))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	//test 5 avec une chaine de caractere pour essayer de casser le truc
	//meme chose test 6 avec un nombre
	printf("\n\n");
	printf("============= CONVERTER: s ============\n\n");
	printf("Test 1 : donut sucre au sucre\n");
	if (printf("%s\n", "donut sucre au sucre") == ft_printf("%s\n", "donut sucre au sucre"))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : donut sucre, au sucre\n");
	if (printf("%s%s\n", "donut sucre ", "au sucre") == ft_printf("%s%s\n", "donut sucre ", "au sucre"))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : experience\n");
	if (printf("this is a test %s this is a test\n", "and this is an experience") == ft_printf("this is a test %s this is a test\n", "and this is an experience"))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : test plus long\n");
	if (printf("test plus complique %s%s et la %s%s ici aussi\n", "la", " aussi", "autant", " mais") == ft_printf("test plus complique %s%s et la %s%s ici aussi\n", "la", " aussi", "autant", " mais"))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	printf("Test 5 : NULL\n");
	if (printf("%s\n", s) == ft_printf("%s\n", s))
		printf("-------test 5 passed-------\n\n");
	else
		printf("-------test 5 failed-------\n\n");
	printf("Test 6 : chaine vide\n");
	if (printf("%s\n", "") == ft_printf("%s\n", ""))
		printf("-------test 6 passed-------\n\n");
	else
		printf("-------test 6 failed-------\n\n");
	printf("\n\n");
	printf("============= CONVERTER: p ============\n\n");
	printf("Test 1 : NULL\n");
	if (printf("%p\n", NULL) == ft_printf("%p\n", NULL))
                printf("-------test 1 passed-------\n\n");
        else
                printf("-------test 1 failed-------\n\n");
	p1 = malloc(16);
        p2 = malloc(16);
        p3 = malloc(16);
        p4 = malloc(16);
	printf("Test 2 : malloc 4 pointeurs\n");
	if (printf("%p %p %p %p\n", p1, p2, p3, p4) == ft_printf("%p %p %p %p\n", p1, p2, p3, p4))
		printf("-------test 2 passed-------\n\n");
        else
                printf("-------test 2 failed-------\n\n");
 	printf("\n\n");
	printf("============= CONVERTER: d & i ============\n\n");
	printf("Test 1 : int max\n");
	if (printf("%d\n", 2147483647) == ft_printf("%d\n", 2147483647))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : basic ints\n");
	if (printf("%i %d\n", 100000, 2147) == ft_printf("%i %d\n", 100000, 2147))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : int entre les tests\n");
	if (printf("this is a test %d this is a test\n", 541223) == ft_printf("this is a test %d this is a test\n", 541223))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : Plus de ints\n");
	if (printf("test plus compliqué %d %d et la %d %d ici aussi\n", 2, -124, 48, -7) == ft_printf("test plus compliqué %d %d et la %d %d ici aussi\n", 2, -124, 48, -7))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	printf("Test 5 : 0\n");
	if (printf("%d\n", 0) == ft_printf("%d\n", 0))
		printf("-------test 5 passed-------\n\n");
	else
		printf("-------test 5 failed-------\n\n");
	printf("\n\n");
	printf("============= CONVERTER: u ============\n\n");
	printf("Test 1 : int max\n");
	if (printf("%u\n", 2147483647) == ft_printf("%u\n", 2147483647))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : un gros unsigned int\n");
	if (printf("%ld %u\n", 4000000000, 2147) == ft_printf("%u %u\n", 4000000000, 2147))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : unsigned int\n");
	if (printf("this is a test %u this is a test\n", 54122300) == ft_printf("this is a test %u this is a test\n", 54122300))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : unsigned int ++\n");
	if (printf("test plus compliqué %u %u et la %u %u ici aussi\n", 2, 124, 48, 7) == ft_printf("test plus compliqué %u %u et la %u %u ici aussi\n", 2, 124, 48, 7))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	printf("Test 5 : 0\n");
	if (printf("%u\n", 0) == ft_printf("%u\n", 0))
		printf("-------test 5 passed-------\n\n");
	else
		printf("-------test 5 failed-------\n\n");
	printf("\n\n");
	printf("============= CONVERTER: x ============\n\n");
	printf("Test 1 : ff\n");
	if (printf("%x\n", 255) == ft_printf("%x\n", 255))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : grand nombre\n");
	if (printf("%x %x\n", 400000000, 2147) == ft_printf("%x %x\n", 400000000, 2147))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : plutot grand nombre + string\n");
	if (printf("this is a test %x this is a test\n", 54122300) == ft_printf("this is a test %x this is a test\n", 54122300))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : plutot grand nombre + string ++\n");
	if (printf("test plus compliqué %x %x et la %x %x ici aussi\n", 2, 124, 48, 7) == ft_printf("test plus compliqué %x %x et la %x %x ici aussi\n", 2, 124, 48, 7))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	printf("Test 5 : 0\n");
	if (printf("%x\n", 0) == ft_printf("%x\n", 0))
		printf("-------test 5 passed-------\n\n");
	else
		printf("-------test 5 failed-------\n\n");
	printf("\n\n");
	printf("============= CONVERTER: X ============\n\n");
	printf("Test 1 : FF\n");
	if (printf("%X\n", 255) == ft_printf("%X\n", 255))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : grand nombre\n");
	if (printf("%X %X\n", 400000000, 2147) == ft_printf("%X %X\n", 400000000, 2147))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : plutot grand nombre + sting\n");
	if (printf("this is a test %X this is a test\n", 54122300) == ft_printf("this is a test %X this is a test\n", 54122300))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
 	printf("Test 4 : plutot grand nombre + string ++\n");
	if (printf("test plus compliqué %X %X et la %X %X ici aussi\n", 2, 124, 48, 7) == ft_printf("test plus compliqué %X %X et la %X %X ici aussi\n", 2, 124, 48, 7))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	printf("\n\n");
	printf("============= CONVERTER: %% ============\n\n");
	printf("Test 1 : 1 signe pourcent '%%'\n");
	if (printf("%%\n") == ft_printf("%%\n"))
		printf("-------test 1 passed-------\n\n");
	else
		printf("-------test 1 failed-------\n\n");
	printf("Test 2 : 2 signed pourcent '%%%%'\n");
	if (printf("%%%%\n") == ft_printf("%%%%\n"))
		printf("-------test 2 passed-------\n\n");
	else
		printf("-------test 2 failed-------\n\n");
	printf("Test 3 : pourcent au milieu\n");
	if (printf("this is a test %% this is a test\n") == ft_printf("this is a test %% this is a test\n"))
		printf("-------test 3 passed-------\n\n");
	else
		printf("-------test 3 failed-------\n\n");
	printf("Test 4 : beaucoup de pourcents\n");
	if (printf("%%%%%%%%%%%%%%\n") == ft_printf("%%%%%%%%%%%%%%\n"))
		printf("-------test 4 passed-------\n\n");
	else
		printf("-------test 4 failed-------\n\n");
	free(p1);
        free(p2);
        free(p3);
        free(p4);
}
