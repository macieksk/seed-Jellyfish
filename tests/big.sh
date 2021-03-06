#! /bin/sh

cd tests
. ./compat.sh

if [ -z "$BIG" ]; then
    echo "Skip big test"
    exit 77
fi

sort > ${pref}.md5sum <<EOF 
f52abd3e2a7cc5089cc8f32cb607c4c5 ${pref}_16.histo
eac5dafa9db7af2c5202dec8c6c33d00 ${pref}_16.stats
EOF

    # $JF count -m 31 -s 4000000000 -o ${pref}_31 -c 4 -p 253 -C -r -t $nCPUs --timing ${pref}_31.timing \
    # seq30g.fa && \
    # $JF histo ${pref}_31_0 > ${pref}_31.histo && \

echo "Generate 30 Gigs of sequence and count k-mers on it" && \
    ([ -f seq30g.fa ] || ${DIR}/generate_sequence -v -o seq30g -r 1000 -s 1602176487 30000000000) && \
    $JF count -m 16 -s 4000000000 -o ${pref}_16 -c 4 -p 253 -C --out-counter-len 2 \
    -t $nCPUs --timing ${pref}_16.timing --stats ${pref}_16.stats $JFPARAM seq30g.fa && \
    $JF histo ${pref}_16_0 > ${pref}_16.histo && \
    check ${pref}.md5sum
RET=$?

echo "16-mer timing"; cat ${pref}_16.timing

exit $RET
