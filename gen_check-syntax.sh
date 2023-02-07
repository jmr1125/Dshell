a=`ls | grep -E ".+\.c(pp)?$"`
files=""
for i in $a; do
    res=`echo $i | grep -E -o "[^.]+"`
    #echo $res
    b=0
    file=""
    ext=""
    for j in $res; do
	if [ $b == 0 ]; then
	    b=1
	    file=$j
	else
	    b=0
	    ext=$j
	fi
    done
    #echo file=$file
    #echo ext=$ext
    files="$files $file"
done

echo "check-syntax:"
printf "\tmake -s main\n"
echo "main:"
printf "\tif [ ! -d check_syntax ];then mkdir check_syntax;fi\n"
for f in $files; do
    printf "\tmake check_syntax/%s\n" $f
done

for f in $files; do
    ffile=`ls|grep -E "^$f\.c(pp)?$"`
    echo "check_syntax/$f: $ffile"
    printf "\tclang++ -fsyntax-only %s\n" $ffile
    printf "\tcd check_syntax&&touch %s\n" $f
done
