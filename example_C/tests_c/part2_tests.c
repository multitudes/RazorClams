/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:27:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/04/03 09:36:51 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "razorclam_tests.h"
// add the necessary includes

/*
This is a test function. It should return NULL if the test passes
debug will print to the log
log_err will print to the error log
my_assert will check a condition and return an error message if it fails
run_test will run a test function and return the error message if it fails
RUN_TESTS will run all the tests and print the results
*/
const char* test_example() {
	// write tests.
	// use my_assert(condition, message); or debug(message); see readme

	return NULL;
}

const char *all_tests()
{
	// necessary to start the test suite
	suite_start();
	
	// run the tests
	
	return NULL;
}

// works as a main
RUN_TESTS(all_tests);