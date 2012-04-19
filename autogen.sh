#!/bin/sh
autoreconf --copy --force --install --verbose || exit 1
intltoolize --copy --force || exit 1
