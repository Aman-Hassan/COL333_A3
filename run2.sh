chmod -x result
INPUT="$1.graph"
OUT="$1.mapping"
MINSAT="$1.satoutput"
./result $MINSAT < $INPUT > $OUT