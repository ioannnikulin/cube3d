/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:57:06 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 13:06:30 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_test.h"
#include <math.h>

typedef struct s_testcase_rot
{
	t_vector	src;
	double		by;
	t_vector	exp;
}	t_testcase_rot;

#define START 0
#define SZ 5
//#define DEBUG
#define EPSILON 1e-6

static void rotations_test(void)
{
	t_testcase_rot	tests[SZ] = {
		(t_testcase_rot){
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
			0,
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
		},
		(t_testcase_rot){
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
			M_PI / 2,
			ft_vector_make(ft_point_make(0, 0), ft_point_make(-1, 1)),
		},
		(t_testcase_rot){
			ft_vector_make(ft_point_make(0, 0), ft_point_make(-1, -1)),
			M_PI,
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
		},
		(t_testcase_rot){
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
			M_PI / 36,
			ft_vector_make(ft_point_make(0, 0), ft_point_make(0.9090389553, 1.0833504408)),
		},
		(t_testcase_rot){
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1, 1)),
			- M_PI / 36,
			ft_vector_make(ft_point_make(0, 0), ft_point_make(1.0833504408, 0.9090389553)),
		},
	};

	for (int i = START; i < SZ; i ++)
	{
		t_vector	act;
		bool res;

		act = ft_vector_rot(&tests[i].src, tests[i].by);
		res = ft_vector_eq(&act, &tests[i].exp, EPSILON);
		#ifdef DEBUG
		printf("#%i\n", i);
		if (res == false)
		{
			printf("expected: %f %f %f to %f %f %f,\ngot: %f %f %f to %f %f %f\n"
			, tests[i].src.from.x
			, tests[i].src.from.y
			, tests[i].src.from.z
			, tests[i].src.to.x
			, tests[i].src.to.y
			, tests[i].src.to.z
			, act.from.x
			, act.from.y
			, act.from.z
			, act.to.x
			, act.to.y
			, act.to.z
		);
		}
		#endif
		assert(res == true);
	}
}

void	vectors_test(void)
{
	rotations_test();
}