# assembly-search

usage: 	$ assembly-search number-threads dictionary.txt consensus-assembly.fa ... nth-assembly.fa > hits.txt

output: filename    chr-location    feature    index-on-chr  

Optimal solution for finding genomic features within multiple fasta formatted assemblies.

Dictionary and assembly files are line delimited. Program offers *untested* multithread support. In most instances, multithreaded will probably not improve performance. The only time that it should, is if the dictionary file and assemblies are large enough, that it takes less time to launch a thread than it take to complete the computations on the thread.
