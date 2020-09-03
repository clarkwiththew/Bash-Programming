# [6 mark] Shell scripting. Please submit solution as Q3.sh
#Macy’s school computer doesn’t have make installed for some reason! She needs your help
#writing a shell script that performs a small but important job of make. She has a lot of TeX
#files (filenames end with “.tex”), and there is a program pdflatex for generating corresponding
#PDF files. Using “A1.tex” as an example, “pdflatex A1.tex” generats “A1.pdf”. Clearly, she
#wants to generate if and only if one of:
#• A1.tex exists but A1.pdf doesn’t
#• both exists, but A1.tex is newer
#“A1.tex” is just an example—this applies to all TeX and PDF files in the current directory.
#Implement a Bourne shell script to do this.
#The command “basename A1.tex .tex” outputs A1 to help you.

pdflatex()
{

SUB=basename $1 .tex
i=0;
for file in $directory; do

 if [[ file == "$SUB.pdf" ]]  ; then
i=1
fi
done
if [[ i==0]]  ; then
touch "$SUB.pdf"
fi
}
