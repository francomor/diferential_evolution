%%
%% JCST.cls 2019/10/10 version v1.8
%% 
%% This is the JCST LaTeX class for authors of the Journal of 
%% Computer Science and Technology (http://journal.info.unlp.edu.ar)
%% 
%%
%% Contributors:
%% Facundo Quiroga 
%% Enzo Rucci 
%% 

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{jcst}[ 2019/10/10 Journal of Computer Science and Technology class]

\LoadClass[twocolumn,10pt,a4paper]{article}
\RequirePackage{etoolbox}
\RequirePackage{flushend}


% General format
\RequirePackage{microtype} % better font kerning

% using times font
\RequirePackage{mathptmx}% http://ctan.org/pkg/mathptmx

\pagenumbering{gobble} % remove page numbering
\RequirePackage[a4paper, margin=2.5cm, headheight=0pt, headsep=0pt,  footskip=0pt]{geometry}

% Title
% bold and large title
\title{\Large\bfseries\fontsize{18}{18}\selectfont\centering\@testTitle}
\renewcommand*{\title}[1]{\def\@testTitle{#1}}
\date{} % remove date



% affiliations
\RequirePackage{authblk}
\setcounter{Maxaffil}{0}
\renewcommand\Affilfont{\itshape\small}
\newcommand{\affiliation}[2]{ #1 \\ \smallskip #2}
%    #1 {\large\textperiodcentered} #2

% to avoid footnote splitting into two pages
\interfootnotelinepenalty=10000


% keywords and reception sections
\newcommand{\keywords}[1]{ \medskip \noindent \textbf{Keywords:} #1 }
\newcommand{\palabrasclaves}[1]{ \medskip \noindent \textbf{Palabras claves:} #1 }
\newcommand{\reception}[1]{\medskip \noindent #1 \medskip}

\setlength{\columnsep}{1cm}

%Subsection names and formats

\RequirePackage{sectsty}
\sectionfont{\fontsize{12}{12}\selectfont\bfseries}
\subsectionfont{\fontsize{11}{11}\selectfont}
\subsubsectionfont{\fontsize{10}{10}\selectfont}
\newcommand{\acknowledgements}[1]{\subsubsection*{Acknowledgements}
#1}
\newcommand{\competinginterests}[1]{\subsubsection*{Competing interests}
#1}
\newcommand{\funding}[1]{\subsubsection*{Funding}
#1}
\newcommand{\authorcontributions}[1]{\subsubsection*{Authors' contribution}
#1}
%\sectionfont{\fontsize{10}{12}\selectfont}
\setcounter{secnumdepth}{3} % put numbers till subsubsections

% internet references
\RequirePackage{url}

% algorithms
\RequirePackage{algorithm}% http://ctan.org/pkg/algorithms
\RequirePackage{algpseudocode}% http://ctan.org/pkg/algorithmicx


%bibliography style
\bibliographystyle{ieeetr}


% SPECIFIC TWEAKS
%tables
\RequirePackage{booktabs}
\newcommand {\otoprule }{\midrule [\heavyrulewidth ]} %better tables

%graphics
\RequirePackage{graphicx}

% math
\RequirePackage{amsmath}
\RequirePackage{amsthm}
\RequirePackage{amssymb}

% citation
\RequirePackage{fancybox}


%%% ORCID ICON IN AFFILIATION OR AUTHOR
\RequirePackage{scalerel}
\RequirePackage{authblk}
\RequirePackage{tikz}
\usetikzlibrary{svg.path,calc}

\definecolor{orcidlogocol}{HTML}{A6CE39}
\tikzset{
  blaaa/.pic={
  \fill[orcidlogocol] svg{M256,128c0,70.7-57.3,128-128,128C57.3,256,0,198.7,0,128C0,57.3,57.3,0,128,0C198.7,0,256,57.3,256,128z};
  \fill[white] svg{M86.3,186.2H70.9V79.1h15.4v48.4V186.2z}
               svg{M108.9,79.1h41.6c39.6,0,57,28.3,57,53.6c0,27.5-21.5,53.6-56.8,53.6h-41.8V79.1z M124.3,172.4h24.5c34.9,0,42.9-26.5,42.9-39.7c0-21.5-13.7-39.7-43.7-39.7h-23.7V172.4z}
               svg{M88.7,56.8c0,5.5-4.5,10.1-10.1,10.1c-5.6,0-10.1-4.6-10.1-10.1c0-5.6,4.5-10.1,10.1-10.1C84.2,46.7,88.7,51.3,88.7,56.8z};
}
}

\newcommand\orcidicon[1]{\href{https://orcid.org/#1}{\mbox{
\begin{tikzpicture}[ overlay,remember picture]
\coordinate (A);
\coordinate(B) at ($(A)+(-2.5pt,-0.5pt)$);
\end{tikzpicture}
\begin{tikzpicture}[overlay,remember picture,yscale=0.03,xscale=0.03,transform shape]
\pic at (B) {blaaa};
\end{tikzpicture}
}}}


\RequirePackage{hyperref} %<--- Load after everything else

\newcommand{\orcid}[1]{ \protect\orcidicon{#1}}
%%% 

%%% avoid borders
\hypersetup{%
    pdfborder = {0 0 0}
}