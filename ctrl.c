#include <stdio.h>
#include "main.h"
/**
 * CtrlCHandler - handles Ctrl c
 * @x: void parameter
 * Return: nothing
 */
void CtrlCHandler(int x)
{
	(void)x;
	printf("\n$ ");
}
