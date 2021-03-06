//
// Copyright © 2018 Rodrigo Pelissier. All rights reserved.
//
// This file is part of La Weá Interpreter (C)
//
// La Weá Interpreter (C) is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef LA_WEÁ_INTERPRETER_H
#define LA_WEÁ_INTERPRETER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/// All the valid commands.
typedef enum {
	/// Decrements current cell value by 1.
	maricón,

	/// Decrements current cell value by 2.
	maraco,

	/// Increments current cell value by 1.
	weón,

	/// Increments current cell value by 2.
	aweonao,

	/// Sets current cell value to 0.
	maraca,

	/// Moves back one cell.
	chucha,

	/// Moves forward one cell.
	puta,

	/// If current cell value is 0, moves the instruction pointer after the matching tula command.
	pichula,

	/// If current cell value is not 0, moves the instruction pointer after the matching pichula command.
	tula,

	/// Moves the instruction pointer after the closest tula command, regardless of the current cell value.
	pico,

	/// Prints current cell value to STDOUT as an ASCII character.
	ctm,

	/// Reads ASCII character from STDIN and stores it in the current cell.
	quéweá,

	/// Prints current cell value to STDOUT as an integer.
	chúpala,

	/// Reads integer from STDIN and stores it in the current cell.
	brígido,

	/// Copies current cell value if there is no copy; otherwise, pastes the copied value and resets the copy.
	perkin,

	/// Terminates program.
	mierda
} command_t;

/// The names of all the valid commands.
extern const uint_least32_t command_names[16][8 * sizeof(uint_least32_t)];

/// All the characters a command may be composed of.
extern const uint_least32_t valid_chars[];

/// Keeps track of the length of loop starting commands.
extern int loop_starts_length;

/// Keeps track of the length of loop ending commands.
extern int loop_ends_length;

/**
 * The entry point for interpreting the code.
 * @param file_path the path to the file with the code
 * @note The file must have the .lw extension.
 */
void interpret_la_weá(const char *file_path);

/**
 * A utility function that retrieves the code.
 * @param file_path the path to the file with the code
 * @param code_length a pointer to store the length of the code
 * @return The code, encoded in UTF-32
 */
uint_least32_t *get_code(const char *file_path, size_t *code_length);

/// A utility function that prints a message and exits the program for when the code file cannot be found.
void file_not_found_exit();

/**
 * Checks the validity of the code and retrieves the commands.
 * @param code the code to parse
 * @param code_length the length of the code
 * @param commands_length a pointer to store the number of commands found
 * @return The commands found
 */
command_t *get_commands(const uint_least32_t *code, size_t code_length, int *commands_length);

/**
 * Gets command_t from name and performs some validation.
 * @param cmd_name the name of the command
 * @param cmd_idx the index of the command
 * @param row the row the command was found at
 * @param col the column the command was found at
 * @return The command or -1 if not found
 */
command_t get_command(const uint_least32_t *cmd_name, int cmd_idx, long row, long col);

/**
 * Checks if any command can contain the character.
 * @param c the character to check
 * @return Whether the character was valid
 */
bool validate_char(uint_least32_t c);

/**
 * Runs the code by interpreting the commands.
 * @param commands the commands to run
 * @param commands_length the number of commands to run
 */
void run_commands(const command_t *commands, int commands_length);

/**
 * A utility function to find the appropriate loop starting command.
 * @param commands the array of commands to search in
 * @param commands_length the number of commands in the array
 * @param i the index to start searching at
 * @return The index of the loop starting command or -1 if not found
 */
int find_loop_start(const command_t *commands, int commands_length, int i);

/**
 * A utility function to find the appropriate loop ending command.
 * @param commands the array of commands to search in
 * @param commands_length the number of commands in the array
 * @param i the index to start searching at
 * @return The index of the loop ending command or -1 if not found
 */
int find_loop_end(const command_t *commands, int commands_length, int i);

/**
 * A utility function that prints an error message and exits the program abnormally.
 * @param err_msg the error message to print
 */
void exit_interpreter(const char *err_msg);

#endif
