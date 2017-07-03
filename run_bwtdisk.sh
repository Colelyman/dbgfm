#!/bin/bash
set -eu

# Set the path to bwtdisk
BWTDISK=../bwtdisk

# Prepare the file by concatenating the contigs/sequences into one long string
# separated by $
./bwtdisk-prepare $1 > $1.joined

# Reverse the text, because bwtdisk constructs the BWT of the reverse text by default.
$BWTDISK/text_rev -vvv $1.joined $1.joined.rev

# Generate the BWT.
$BWTDISK/bwte -vvv $1.joined.rev

# Rename the bwt
mv $1.joined.rev.bwt `basename $1 .fa`.bwtdisk

# Remove the intermediary files
rm $1.joined $1.joined.rev
