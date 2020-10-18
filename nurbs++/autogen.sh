#!/bin/sh

set -e

ACLOCAL_FLAGS="-I config"

aclocal $ACLOCAL_FLAGS  || \
    aclocal $ACLOCAL_FLAGS -I /usr/local/share/aclocal

# Decide on which system we are builing and use libtoolize accordingly
unameOut="$(uname -s)"
echo "Building on ${unameOut}"
case "${unameOut}" in
Linux*)     libtoolize --force;;
Darwin*)    glibtoolize --force;;
*)          libtoolize --force;;
esac

autoheader
automake --add-missing
autoconf
