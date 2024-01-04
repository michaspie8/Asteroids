echo 'linie' 
l1=$( ( find ./ -name '*.h' -print0 | xargs -0 cat ) | wc -l) 
l2=$( ( find ./ -name '*.cpp' -print0 | xargs -0 cat ) | wc -l) 
l=$((l1 + l2))
echo "$l"
echo "słowa" 
s1=$( ( find ./ -name '*.h' -print0 | xargs -0 cat ) | wc -w) 
s2=$( ( find ./ -name '*.cpp' -print0 | xargs -0 cat ) | wc -w) 
s=$((s1 + s2))
echo "$s"