/* Preconversion assistant
 * Copyright (C) 2026 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#define program_name "windows-pca" EXEEXT

static void __attribute__((noreturn))
usage (int status)
{
  if (status != EXIT_SUCCESS)
    fprintf (stderr, "Try ‘%s --help’ for more information.\n",
             program_name);
  else {
    printf ("%s: Virt-v2v / QEMU Preconversion Assistant\n"
            "Prepare Windows guests for conversion by virt-v2v\n"
            "https://github.com/libguestfs/preconversion-assistant\n"
            "Copyright (C) 2026 Red Hat Inc.\n"
            "\n"
            "Usage:\n"
            "  %s [--options]\n"
            "\n"
            "Options:\n"
            "  -V|--version         Display version and exit\n"
            "\n"
            "For more information, see the manpage %s(1).\n",
            program_name, program_name, program_name);
  }
  exit (status);
}

static void
display_short_options (const char *format)
{
  while (*format) {
    if (*format != ':')
      printf ("-%c\n", *format);
    ++format;
  }
  exit (EXIT_SUCCESS);
}

static void
display_long_options (const struct option *long_options)
{
  while (long_options->name) {
    if (strcmp (long_options->name, "long-options") != 0 &&
        strcmp (long_options->name, "short-options") != 0)
      printf ("--%s\n", long_options->name);
    long_options++;
  }
  exit (EXIT_SUCCESS);
}

int
main (int argc, char *argv[])
{
  enum { HELP_OPTION = CHAR_MAX + 1 };
  static const char options[] = "V";
  static const struct option long_options[] = {
    { "help", 0, 0, HELP_OPTION },
    { "long-options", 0, 0, 0 },
    { "short-options", 0, 0, 0 },
    { "version", 0, 0, 'V' },
    { 0, 0, 0, 0 }
  };
  int c;
  int option_index;

  for (;;) {
    c = getopt_long (argc, argv, options, long_options, &option_index);
    if (c == -1) break;

    switch (c) {
    case 0:			/* options which are long only */
      if (strcmp (long_options[option_index].name, "long-options") == 0)
        display_long_options (long_options);
      else if (strcmp (long_options[option_index].name, "short-options") == 0)
        display_short_options (options);
      else {
        fprintf (stderr,
                 "unknown long option: %s (%d)",
                 long_options[option_index].name, option_index);
        exit (EXIT_FAILURE);
      }
      break;

    case 'V':
      printf ("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION_FULL);
      exit (EXIT_SUCCESS);

    case HELP_OPTION:
      usage (EXIT_SUCCESS);

    default:
      usage (EXIT_FAILURE);
    }
  }

  if (optind != argc)
    usage (EXIT_FAILURE);

  exit (EXIT_SUCCESS);
}
