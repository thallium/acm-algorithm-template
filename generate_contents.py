import os
import glob

rootDir = './code'

sections = [ o for o in os.listdir(rootDir) if os.path.isdir(os.path.join(rootDir, o))]
sections.sort()
# sections = ['Bits', 'Graph']

with open('contents.tex', 'w') as fp:
    for section in sections:
        fp.write(f'\\section{{{section}}}\n')
        files = [ o for o in os.listdir(os.path.join(rootDir, section)) ]
        files.sort()
        for f in files:
            escaped = f.replace('_', '\\_');
            fp.write(f'\\subsection{{{escaped}}}\n')
            # print(f'\\raggedbottom\\lstinputlisting[style=cpp]{{{os.path.join(rootDir, section, f)}}}')
            fp.write(f'\\lstinputlisting[style=cpp]{{{os.path.join(rootDir, section, f)}}}\n')
        # print(files)
