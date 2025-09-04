\section{Problem Statement}

In this work, we compute the area of a plane figure bounded by three curves:
$$f_1(x)=0.35x^2-0.95x+2.7 \ \ \ \ \ \ \ f_2(x)=3x+1 \ \ \ \ \ \ \ f_3(x)=\frac{1}{x+2}$$

To solve the problem, we perform the following steps:
\begin{itemize}
	\item Determine the integration limits analytically by finding the intersection intervals for each pair of functions;
	\item Implement the combined method (secant and tangent method) to find the x-coordinates of the intersection points of the curves;
	\item Implement Simpson’s method for numerical computation of the area of the given figure.
	\item Test the implemented functions to validate their correctness.
\end{itemize}

\newpage


\section{Mathematical Justification}

This section analyzes the methods used: the combined method (secants and tangents) for root finding and Simpson’s method for numerical integration.

\subsection{Combined method (secants and tangents)}

Suppose we need to find a root of the equation $F(x)=f_1(x)-f_2(x)=0 $
on the interval $[a,b]$. According to \cite{math}, for the combined method to converge, the function on the chosen interval must satisfy:
\begin{itemize}
	\item $F(x)$ is continuous and continuously differentiable on $[a,b]$;
	\item $F(a)F(b)<0$ (the root lies within the interval);
	\item $F'(x)$ is monotonic and does not change sign on $[a,b]$.
\end{itemize}

\subsection*{Algorithm of the method:}
At each step $k$ we have the current interval $[a_k,b_k]$ with $F(a_k)F(b_k)<0$. To construct the next interval:
\begin{enumerate}
	\item Build the secant-method approximation:
	\begin{equation}\label{eq:chor}
		x_k^\text{(chor)}=\frac{a_k\,F(b_k)-b_k\,F(a_k)}{F(b_k)-F(a_k)}
	\end{equation}
	\item Determine the point $d_k$ for the tangent method:
	\begin{equation}\label{eq:sec}
		d_k = 
		\begin{cases}
			b_k, F'(x)F''(x)>0 \text{ on }[a_k,b_k]\\
			a_k, \text{otherwise}
		\end{cases}
	\end{equation}
	Compute the approximation
	\begin{equation}\label{eq:sec_1}
		x_k^\text{(sec)}=d_k-\frac{F(d_k)}{F'(d_k)}
	\end{equation}
	\item Choose the next interval $[a_{k+1},b_{k+1}]$ so that
	$F(a_{k+1})\,F(b_{k+1})<0$, for example $$[a_{k+1},b_{k+1}]=\bigl[\min(x_k^\text{(chor)},x_k^\text{(sec)}),\max(x_k^\text{(chor)},x_k^\text{(sec)})\bigr]$$
\end{enumerate}

The process stops when $|b_{k+1}-a_{k+1}|<\varepsilon_1$.

\subsection*{Choice of initial intervals:}

The intervals for root search are determined by analyzing the function plots (Fig.~\ref{plot1}) and verifying the conditions:
\begin{enumerate}
	\item $F(a)F(b)<0$
	\item $F'(x)\neq 0$
	\item $F'(x)$ is monotonic on $[a,b]$
\end{enumerate}

Where $F(x) = f_i(x) - f_j(x),  i \neq j$. After analyzing the graphs, we obtained the following intervals for each pair of functions:
$$
\begin{aligned}
	f_1(x)=f_2(x)\ &\to [0,1]\\
	f_1(x)=f_3(x)\ &\to [-1.96,0]\\
	f_2(x)=f_3(x)\ &\to [-1,0]
\end{aligned}
$$
Let us check that they satisfy all necessary conditions of the method.

\subsection*{Mathematical justification of the chosen root-search intervals}

To apply the combined method (secants and tangents), one must choose intervals $[a, b]$ such that:
\begin{enumerate}
	\item The function $F(x) = f_i(x) - f_j(x)$ is continuous on $[a, b]$.
	\item $F(a)F(b) < 0$, i.e., the function values at the endpoints have different signs — by the Bolzano–Cauchy theorem, there is at least one root on this interval.
	\item $F'(x)$ does not vanish and does not change sign on $[a, b]$ (monotonic derivative).
\end{enumerate}

We verify these conditions for each function pair:

\subsubsection*{1. $f_1(x)$ and $f_2(x)$}

Consider $F_{12}(x) = f_1(x) - f_2(x) = 0.35x^2 - 3.95x + 1.7$.

\begin{itemize}
	\item $F_{12}(x)$ is continuous on all of $\mathbb{R}$.
	\item Check the signs on $[0, 1]$: \\
	$ F_{12}(0) = 0.35 \cdot 0^2 - 3.95 \cdot 0 + 1.7 = 1.7 $ \\
	$ F_{12}(1) = 0.35 \cdot 1^2 - 3.95 \cdot 1 + 1.7 = 0.35 - 3.95 + 1.7 = -1.9 $
	\item $F_{12}(0) \cdot F_{12}(1) = 1.7 \cdot (-1.9) < 0$, hence there is a root on $[0, 1]$.
	\item Derivative $F_{12}'(x) = 0.7x - 3.95$ on $[0, 1]$: \\
	$ F_{12}'(0) = -3.95$, \\
	$\quad F_{12}'(1) = 0.7 - 3.95 = -3.25 $ \\
	The derivative is negative and does not change sign; the function is strictly decreasing.
\end{itemize}

\subsubsection*{2. $f_1(x)$ and $f_3(x)$}

Consider $F_{13}(x) = f_1(x) - f_3(x) = 0.35x^2 - 0.95x + 2.7 - \frac{1}{x+2}$.

\begin{itemize}
	\item $F_{13}(x)$ is continuous for $x > -2$.
	\item Check on $[-1.96, 0]$: \\
	$ F_{13}(-1.96) \approx 0.35 \cdot (-1.96)^2 - 0.95 \cdot (-1.96) + 2.7 - \frac{1}{-1.96+2} \approx 0.35 \cdot 3.8416 + 1.862 + 2.7 - \frac{1}{0.04} \approx 1.3446 + 1.862 + 2.7 - 25 \approx 5.9066 - 25 \approx -19.0934 $ \\
	$ F_{13}(0) = 0.35 \cdot 0^2 - 0.95 \cdot 0 + 2.7 - \frac{1}{2} = 2.7 - 0.5 = 2.2 $
	\item $F_{13}(-1.96) \cdot F_{13}(0) < 0$.
	\item Derivative $ F_{13}'(x) = 0.7x - 0.95 + \frac{1}{(x+2)^2} $ on $[-1.96, 0]$: the denominator is positive, $x$ ranges from $-1.96$ to $0$, therefore $F_{13}'(x)$ does not vanish and does not change sign.
\end{itemize}

\subsubsection*{3. $f_2(x)$ and $f_3(x)$}

$F_{23}(x) = f_2(x) - f_3(x) = 3x + 1 - \frac{1}{x+2}$.

\begin{itemize}
	\item $F_{23}(x)$ is continuous for $x > -2$.
	\item Check on $[-1, 0]$:
	$F_{23}(-1) = 3 \cdot (-1) + 1 - \frac{1}{-1+2} = -3 + 1 - 1 = -3$ \\
	$F_{23}(0) = 0 + 1 - \frac{1}{2} = 1 - 0.5 = 0.5$
	\item $F_{23}(-1) \cdot F_{23}(0) = -3 \cdot 0.5 = -1.5 < 0$.
	\item Derivative: $F_{23}'(x) = 3 + \frac{1}{(x+2)^2}$ is always positive on $[-1, 0]$, hence strictly increasing.
\end{itemize}

Thus, for all chosen intervals the necessary conditions are satisfied: the function is continuous, values at the endpoints have opposite signs, and the derivative does not vanish or change sign. This guarantees existence and uniqueness of the root on each interval.

\begin{figure}[h]
	\centering
	\begin{tikzpicture}
		\begin{axis}[grid=both,
			axis lines=middle,
			restrict x to domain=-2.5:4,
			restrict y to domain=-0.5:8,
			axis equal,
			legend cell align=left,
			scale=2,]
			
			\addplot[green,samples=256,thick] {(0.35*x^2 - 0.95*x + 2.7)};
			\addlegendentry{$f_1(x) = 0.35x^2 - 0.95x + 2.7$}
			
			\addlegendimage{empty legend}\addlegendentry{}
			
			\addplot[blue,samples=256,thick] {3*x + 1};
			\addlegendentry{$f_2(x) = 3x + 1$}
			
			\addlegendimage{empty legend}\addlegendentry{}
			
			\addplot[red,samples=256,thick] {1/(x + 2)};
			\addlegendentry{$f_3(x) = \frac{1}{x + 2}$}
		\end{axis}
		
	\end{tikzpicture}
	\caption{Plane figure bounded by the graphs of the given equations}
	\label{plot1}
\end{figure}
\subsection{Simpson’s Method}

Let us approximate the integral $I=\int_a^b f(x)dx$
using Simpson’s method. According to \cite{math}, we require $f\in C^4[a,b]$. To compute the integral, split $[a,b]$ into an even number $n$ of equal subintervals of length
$$
h=\frac{b-a}{n},\quad x_i=a+i\,h,\;i=0,1,\dots,n
$$
On every other subinterval $[x_{i-1},x_{i+1}]$ we approximate $f(x)$ by a parabola passing through $(x_{i-1},f_{i-1})$, $(x_i,f_i)$, $(x_{i+1},f_{i+1})$ and obtain Simpson’s formula:
\begin{equation}\label{eq:simpson}
	\int_a^b f(x)\,dx = \frac{h}{3}\Bigl[f_0+4\sum_{\substack{i=1\\ i\text{ odd}}}^{n-1}f_i+2\sum_{\substack{i=2\\ i\text{ even}}}^{n-2}f_i+f_n\Bigr] + R
\end{equation}
where $R$ is the remainder term:
\begin{equation} \label{eq:simpson_ost1}
	R = -\frac{(b-a)}{180}\,h^4\,f^{(4)}(\xi),	\qquad \xi\in[a,b]
\end{equation}
or equivalently:
\begin{equation} \label{eq:simpson_ost2}
	R = -\frac{(b-a)^5}{2880\,n^4}\,f^{(4)}(\xi)
\end{equation}

\subsection{Choice of \(\varepsilon_1\) and \(\varepsilon_2\)}

In the program, the required final accuracy is \(10^{-4}\). To ensure that the total errors from root finding and numerical integration stay within this bound, we introduce stricter internal tolerances:
\[
\varepsilon_1 = \varepsilon_2 = 10^{-6}.
\]

\subsection{Justification for the internal tolerances \(\varepsilon_1\) and \(\varepsilon_2\)}

To ensure overall accuracy not worse than \(10^{-4}\), we must account for error accumulation at each stage. Therefore, stricter internal tolerances \(\varepsilon_1\) and \(\varepsilon_2\) are chosen to guarantee the final accuracy requirement.

\subsubsection{Justification for \(\varepsilon_1\)}

Let \(x^*\) be the exact solution of \(F(x) = 0\), and \(x_{k+1}\) be the approximation after the \(\text{(k+1)}\)-th iteration. Then, by properties of the method, the root error is related to the interval length:
\[
|x_{k+1} - x^*| \le \frac{b_{k+1} - a_{k+1}}{2}.
\]
To ensure error no more than \(\varepsilon_x\), we need:
\[
\frac{b_{k+1} - a_{k+1}}{2} < \varepsilon_x,
\]
where \(\varepsilon_x\) is the allowable error in the root. Given the final accuracy \(10^{-4}\) and the internal tolerance \(\varepsilon_1 = 10^{-6}\), we have:
\[
|x_{k+1} - x^*| < \frac{\varepsilon_1}{2} = 5 \times 10^{-7}.
\]
This is much smaller than the required final accuracy, providing a buffer for floating-point arithmetic and iteration error accumulation.

\subsubsection{Justification for \(\varepsilon_2\)}

For numerical integration by Simpson’s method, the remainder term is:
\[
R = -\frac{(b - a)^5}{2880\, n^4} f^{(4)}(\xi),
\]
where \(M = \max_{x \in [a, b]} |f^{(4)}(x)|\). To guarantee the integration error does not exceed \(\varepsilon_2\), we need:
\[
|R| \le \frac{(b - a)^5 M}{2880\, n^4} < \varepsilon_2.
\]
Hence the minimum number of subintervals:
\[
n \ge \left( \frac{(b - a)^5 M}{2880\, \varepsilon_2} \right)^{1/4}.
\]
When \(M\) is unknown, the Runge rule is used:
\[
|I_n - I_{2n}| \approx \frac{1}{15} |I_{2n} - I_{4n}| < \varepsilon_2,
\]
which provides error control and ensures the final error does not exceed \(10^{-4}\), accounting for possible accumulation.

\newpage

\section{Experimental Results}
Using the implemented program, we compute the coordinates of the intersection points of the curves and compile a table, also showing them on a plot (Fig.~\ref{plot2})

\begin{table}[htbp]
	\centering
	\begin{tabular}{|c|c|c|}
		\hline
		Curves & $x$ & $y$ \\
		\hline
		1 and 2 & 0.4482  & 2.3445 \\
		2 and 3 & -0.1529 & 0.5414 \\
		1 and 3 & -1.8211 & 5.5909 \\
		\hline
	\end{tabular}
	\caption{Coordinates of the intersection points}
	\label{table1}
\end{table}

\begin{figure}[htbp]
	\centering
	\begin{tikzpicture}
		\begin{axis}[grid=both,
			axis lines=middle,
			restrict x to domain=-2.5:4,
			restrict y to domain=-0.5:8,
			axis equal,
			legend cell align=left,
			scale=2,
			xticklabels={,,},
			yticklabels={,,}]
			
			\addplot[green,samples=256,thick,name path=A] {0.35*x^2 - 0.95*x + 2.7};
			\addlegendentry{ $f_1(x) = 0.35x^2 - 0.95x + 2.7$}
			
			\addlegendimage{empty legend}\addlegendentry{}
			
			\addplot[blue,domain=-0.5:4,samples=256,thick,name path=B] {3*x + 1};
			\addlegendentry{$f_2(x) = 3x + 1$}
			
			\addlegendimage{empty legend}\addlegendentry{}
			
			\addplot[red,samples=256,thick,name path=C] {1/(x+2)};
			\addlegendentry{$f_3(x) = \frac{1}{x + 2}$}
			
			\addlegendimage{empty legend}\addlegendentry{}
			
			\addplot[blue!20,samples=256] fill between[of=A and C,soft clip={domain=-1.8211:-0.1529}];
			\addplot[blue!20,samples=256] fill between[of=A and B,soft clip={domain=-0.1529:0.4482}];
			\addlegendentry{$S=5.0236$}
			
			% 1. Пересечение f1 и f2: (0.4482, 2.3445)
			\addplot[black, mark=*, mark size=2pt] coordinates {(0.4482, 2.3445)};
			\node[above right] at (axis cs:0.4482, 2.3445) {\scriptsize $(0.4482, 2.3445)$};
			
			% 2. Пересечение f2 и f3: (-0.1529, 0.5414)
			\addplot[black, mark=*, mark size=2pt] coordinates {(-0.1529, 0.5414)};
			\node[below left] at (axis cs:-0.1529, 0.5414) {\scriptsize $(-0.1529, 0.5414)$};
			
			% 3. Пересечение f1 и f3: (-1.8211, 5.5909)
			\addplot[black, mark=*, mark size=2pt] coordinates {(-1.8211, 5.5909)};
			\node[above right] at (axis cs:-1.8211, 5.5909) {\scriptsize $(-1.8211, 5.5909)$};
			
		\end{axis}
	\end{tikzpicture}
	\caption{Plane figure bounded by the graphs of the given equations}
	\label{plot2}
\end{figure}

\newpage

\section{Program Structure and Function Specification}

This section describes the program architecture, its components, and their interaction. The program is divided into several modules, each responsible for a specific aspect of functionality.

\subsection{Overall architecture}
The program consists of the following modules:
\begin{itemize}
	\item Header file with declarations (\texttt{functions.h})
	\item Main build module (\texttt{main.c})
	\item Module with implemented numerical methods (\texttt{compute.c})
	\item Test build module (\texttt{test\_mode.c})
	\item Assembly module implementing evaluation of the assignment functions and their derivatives at a point (\texttt{func.asm})
\end{itemize}

\subsection{Detailed description of project files}

\subsubsection{compute.c}
\textbf{Purpose}: Implementation of numerical methods and testing.  
\begin{itemize}
	\item \texttt{test\_root()}:
	for testing the \texttt{root} function
	\begin{itemize}
		\item Automatically determines the offset to access derivatives via \texttt{funcs[0](0)}
		\item Output format: absolute and relative error
	\end{itemize}
	\item \texttt{test\_integral()}:
	for testing the \texttt{integral} function
	\begin{itemize}
		\item Compares the result with a reference up to 1e-4
	\end{itemize}
	\item \texttt{root()} implements root finding using the combined method
	\item \texttt{integral()} implements adaptive Simpson for computing the integral. Function specifics:
	\begin{itemize}
		\item Initial partition: \( n = 2 \)
		\item Runge factor: \( p = 1/15 \)
		\item Maximum partition: \( 5 \times 10^6 \) (to avoid an infinite loop)
	\end{itemize}
\end{itemize}

\subsubsection{functions.h}
\begin{itemize}
	\item global variables:
	\begin{itemize}
	\item array \texttt{funcs}:
		\begin{itemize}
			\item In main mode: 7 elements \([idx, f1, f2, f3, df1, df2, df3]\)
			\item In test mode: 9 elements \([idx, test\_f1-4, test\_df1-4]\)
		\end{itemize}
	\item \texttt{EPSILON}
	\item \texttt{root\_iteration} — counting the number of iterations in \texttt{root}
	\end{itemize}
	\item function prototypes
\end{itemize}

\subsubsection{test\_mode.c}
\begin{itemize}
	\item test functions
	\item \texttt{main()} — prints testing results
\end{itemize}

\subsubsection{main.c}
\begin{itemize}
	\item \texttt{calc\_intersection()} — computes intersections in the main mode
	\item \texttt{main()} — main function with command-line support
\end{itemize}

\subsubsection{func.asm}
\begin{itemize}
	\item functions to compute values of $f1$, $f2$, $f3$ at a point
	\item functions to compute values of the derivatives $df1$, $df2$, $df3$ at a point
\end{itemize}

\subsubsection{Graphical representation of the structure}

The structure of the program and interaction of its components can be represented by the following diagram:

\begin{center}
	\begin{tikzpicture}[
		every node/.style={draw, rectangle, align=center},
		header/.style={fill=blue!20, minimum width=2.5cm, minimum height=0.8cm},
		c/.style={fill=green!20, minimum width=2.5cm, minimum height=0.8cm},
		asm/.style={fill=red!20, minimum width=2.5cm, minimum height=0.8cm},
		exe/.style={fill=yellow!20, minimum width=2.5cm, minimum height=0.8cm, rounded corners},
		func/.style={draw, rectangle, minimum width=2.5cm, align=left}
		]
		
		% Header file and ASM
		\node[header] (functions) at (0,4) {functions.h};
		\node[asm] (func_asm) at (-4, 4) {
			\begin{tabular}{l}
				func.asm \\
				\\
				$f_i()$ \\
				$df_i()$
			\end{tabular}
		};
		
		% Main module
		\node[c] (main) at (-3,1) {
			\begin{tabular}{l}
				main.c \\
				\\
				calc\_intersection()
			\end{tabular}
		};
		
		% Compute module
		\node[c] (compute) at (0,7) {
			\begin{tabular}{l}
				compute.c \\
				\\
				root() \\
				integral() \\
				simpson() \\
				test\_root() \\
				test\_integral()
			\end{tabular}
		};
		
		% Test module
		\node[c] (test) at (3, 1) {
			\begin{tabular}{l}
				test\_mode.c \\
				\\
				$test\_f_i()$ \\
				$test\_df_i()$
			\end{tabular}
		};
		
		% Executables
		\node[exe] (main_exe) at (-3,-2.5) {integral.exe};
		\node[exe] (test_exe) at (3,-2.5) {integral\_test.exe};
		
		% Dependencies
		\draw[->] (functions) -- (main);
		\draw[->] (functions) -- (test);
		
		\draw[->] (compute) -- (main);
		\draw[->] (compute) -- (test);
		
		\draw[->] (func_asm) -- (main);
		\draw[->] (func_asm) -- (test);
		
		% Executables
		\draw[->] (main) -- (main_exe);
		\draw[->] (test) -- (test_exe);
		
	\end{tikzpicture}
\end{center}

\newpage

\section{Program Build (Makefile)}

The project Makefile controls the compilation process, defining compilers, flags, and module dependencies. Below is a description of its key components consistent with your Makefile structure.

\subsection{Compilers and flags}

At the beginning of the Makefile, the compilers and their parameters are set:
\begin{itemize}
	\item \texttt{CC = gcc -m32 -no-pie -fno-pie} — C compiler with options:
	\begin{itemize}
		\item \texttt{-m32} — build 32-bit code for compatibility with the assembly module;
		\item \texttt{-no-pie}, \texttt{-fno-pie} — disable PIE, important for correct linking with assembly.
	\end{itemize}
	\item \texttt{NASM = nasm} — NASM assembler for building assembly files.
\end{itemize}

\subsubsection{C compilation flags}

Several groups of flags are used:
\begin{itemize}
	\item \texttt{CFLAGS\_COMMON} — enables a wide range of warnings (\texttt{-Wall}, \texttt{-Werror}, \texttt{-Wformat-security}, etc.) to improve code quality and safety.
	\item \texttt{CFLAGS\_SANITIZE} — enables sanitizers for detecting undefined behavior (\texttt{-fsanitize=undefined}, \texttt{-fsanitize-undefined-trap-on-error}).
	\item \texttt{CFLAGS} — combines common flags and sanitizers.
	\item \texttt{CFLAGS\_TEST} — similar to \texttt{CFLAGS\_COMMON}, but adds \texttt{TEST\_MODE} definition for compiling tests.
	\item \texttt{-g} — add debug information.
	\item \texttt{-std=gnu99} — C language standard.
	\item \texttt{-O2} — level 2 optimization.
\end{itemize}

\subsubsection{NASM flags}

\begin{itemize}
	\item \texttt{NASMFLAGS = -fwin32} — build assembly code as 32-bit Windows object files.
\end{itemize}

\subsection{Build targets}

The Makefile defines the following main targets:
\begin{itemize}
	\item \texttt{all} — build the main program and the test program, then remove object files.
	\item \texttt{main} — build the main program (\texttt{integral}).
	\item \texttt{test} — build and run the test program (\texttt{integral\_test}).
	\item \texttt{clean} — remove all object files (\texttt{*.o}).
\end{itemize}

\subsection{Build rules}

\begin{itemize}
	\item \texttt{integral}: built from \texttt{main.o}, \texttt{compute.o}, \texttt{func.o} using \texttt{CC} and \texttt{CFLAGS}, linked with the math library (\texttt{-lm}).
	\item \texttt{integral\_test}: built from \texttt{test\_mode.o}, \texttt{compute.o} using \texttt{CFLAGS\_TEST}.
	\item \texttt{func.o}: built from \texttt{func.asm} using NASM.
\end{itemize}

\subsection{Features}

\begin{itemize}
	\item Use of strict compilation flags and sanitizers improves reliability and safety.
	\item Automated test run via the \texttt{test} target.
	\item Cleanup of intermediate files after building both main and test programs.
\end{itemize}

\subsection{Module dependencies}

The main dependencies between modules can be represented by the following diagram:

\begin{center}
	\begin{tikzpicture}[
		every node/.style={draw, rectangle, minimum width=2.5cm, minimum height=0.8cm, align=center},
		header/.style={fill=blue!20},
		c/.style={fill=green!20},
		asm/.style={fill=red!20},
		exe/.style={fill=yellow!20, rounded corners}
		]
		
		% Header files
		\node[header] (functions) at (0,2) {functions.h};
		
		% C source files and ASM
		\node[c] (main) at (-4,0) {main.c};
		\node[c] (compute) at (-1.3,0) {compute.c};
		\node[c] (test) at (1.3,0) {test\_mode.c};
		\node[asm] (func) at (4,0) {func.asm};
		
		% Executables
		\node[exe] (main_exe) at (-2.5,-2) {integral.exe};
		\node[exe] (test_exe) at (2.5,-2) {integral\_test.exe};
		
		% Dependencies from header
		\draw[->] (functions) -- (main);
		\draw[->] (functions) -- (compute);
		\draw[->] (functions) -- (test);
		\draw[->] (functions) -- (func);
		
		% Dependencies to executables
		\draw[->] (main) -- (main_exe);
		\draw[->] (compute) -- (main_exe);
		\draw[->] (func) -- (main_exe);
		
		\draw[->] (test) -- (test_exe);
		\draw[->] (compute) -- (test_exe);
		
	\end{tikzpicture}
\end{center}

Where:
\begin{itemize}
	\item \texttt{functions.h} — header file with function declarations:
	\begin{itemize}
		\item Declarations of main functions: \texttt{root}, \texttt{integral}
		\item Declarations of \texttt{f1}, \texttt{f2}, \texttt{f3} and their derivatives
		\item Definition of \texttt{func} as a function pointer type
		\item Constant \texttt{EPSILON} for computation accuracy
	\end{itemize}
	
	\item \texttt{main.c} — main program module:
	\begin{itemize}
		\item \texttt{main} — entry point, command-line argument handling
		\item \texttt{calc\_intersection} — computing curve intersections
		\item \texttt{test\_root} — root-finding tests
		\item \texttt{test\_integral} — integral computation tests
	\end{itemize}
	
	\item \texttt{compute.c} — numerical methods:
	\begin{itemize}
		\item \texttt{root} — combined method for root finding
		\item \texttt{integral} — definite integral computation
		\item \texttt{simpson} — Simpson’s method for numerical integration
		\item Global variable \texttt{root\_iterations} for counting iterations
	\end{itemize}
	
	\item \texttt{test\_mode.c} — testing module:
	\begin{itemize}
		\item Test functions: \texttt{test\_f1}, \texttt{test\_f2}, \texttt{test\_f3}, \texttt{test\_f4}
		\item Their derivatives: \texttt{test\_df1}, \texttt{test\_df2}, \texttt{test\_df3}, \texttt{test\_df4}
	\end{itemize}
	
	\item \texttt{func.asm} — assembly module:
	\begin{itemize}
		\item Main functions: \texttt{f1}, \texttt{f2}, \texttt{f3}
		\item First derivatives: \texttt{df1}, \texttt{df2}, \texttt{df3}
	\end{itemize}
	
	\item \texttt{integral.exe} — main executable
	\item \texttt{integral\_test.exe} — test executable
\end{itemize}

\subsection{Build specifics}

When building the test mode, a special \texttt{-DTEST\_MODE} flag is added to include test functions in the program. This allows maintaining a single code base for both the main program and tests.
\newpage
\section{Debugging and Testing the Program}

To verify program correctness, we consider three test functions for which roots and definite integrals on given intervals are computed analytically:
\begin{align}
	f_1(x) &= x^2 + 5x + 6 \label{eq:test1}\\
	f_2(x) &= \sin x \label{eq:test2}\\
	f_3(x) &= x^3 - 1 \label{eq:test3}
\end{align}

For each function, we find the intersections with the $Ox$ axis (i.e., zeros of the function), and analytically compute the definite integral on the corresponding interval.

\subsection{Function \texorpdfstring{$f_1(x) = x^2 + 5x + 6$}{f₁(x) = x² + 5x + 6}}

Solve:
\[
x^2 + 5x + 6 = (x + 2)(x + 3) = 0
\Rightarrow x = -2, -3
\]

Compute the definite integral on $[-4, -2]$:
\[
\int_{-4}^{-2} (x^2 + 5x + 6)\,dx =
\left.\left( \frac{x^3}{3} + \frac{5x^2}{2} + 6x \right)\right|_{-4}^{-2}
\]

Substitute:
\[
= \left( -\frac{8}{3} + 10 - 12 \right) - \left( -\frac{64}{3} + 40 - 24 \right)
= \frac{2}{3} \approx 0.6667
\]

\subsection{Function \texorpdfstring{$f_2(x) = \sin x$}{f₂(x) = sin x}}

Zeros are given by:
\[
\sin x = 0 \Rightarrow x = \pi n,\quad n \in \mathbb{Z}
\]

Compute the integral on $[1, 2]$:
\[
\int_0^\pi \sin x\,dx = -\cos x \Big|_0^\pi = -(-1) - (-1) = 2
\]

\subsection{Function \texorpdfstring{$f_3(x) = x^3 - 1$}{f₃(x) = x³ - 1}}

Zero:
\[
x^3 - 1 = 0 \Rightarrow x = 1
\]

Compute the integral on $[0, 2]$:
\[
\int_{0}^2 (x^3 - 1)\,dx = \left. \left(\frac{x^4}{4} - x\right) \right|_{0}^{2} = \left(\frac{16}{4} - 2\right) - \left(\frac{0}{4} - 0\right) = (4 - 2) - 0 = 2
\]

\subsection{Choice of intervals for root search}

For each test function we provide the derivative, determine its sign on the corresponding interval, and indicate the interval used for root search.
\begin{itemize}
	\item \textbf{$f_1(x) = x^2 + 5x + 6$} \\
	Derivative: $f_1'(x) = 2x + 5$ \\
	On $[-4, -3]$: \\
	$f_1'(-4) = 2 \cdot (-4) + 5 = -3$ \\
	$f_1'(-3) = 2 \cdot (-3) + 5 = -1$ \\
	Derivative is negative. On $[-2.4, -1.5]$: \\
	$f_1'(-2.4) = 2 \cdot (-2.4) + 5 = 0.2$ \\
	$f_1'(-1.5) = 2 \cdot (-1.5) + 5 = 2.0$ \\
	Derivative is positive. On each subinterval the sign is constant.
	
	\item \textbf{$f_2(x) = \sin x$} \\
	Derivative: $f_2'(x) = \cos x$ \\
	On $[3, 4]$: \\
	$f_2'(3) = \cos 3 \approx -0.990$ \\
	$f_2'(4) = \cos 4 \approx -0.654$\\
	Derivative is negative on the entire interval.
	
	\item \textbf{$f_3(x) = x^3 - 1$} \\
	Derivative: $f_3'(x) = 3x^2$ \\
	On $[0.5, 1.5]$: \\
	$f_3'(0.5) = 3 \cdot (0.5)^2 = 0.75$ \\
	$f_3'(1.5) = 3 \cdot (1.5)^2 = 6.75$ \\
	Derivative is strictly positive.
\end{itemize}

\textbf{Intervals used for root search:}
\begin{itemize}
	\item For $f_1(x)$: $[-4, -3]$ (root $x = -3$), $[-2.5, -1.5]$ (root $x = -2$)
	\item For $f_2(x)$: $[3, 4]$ (root $x = \pi \approx 3.1416$)
	\item For $f_3(x)$: $[0.5, 1.5]$ (root $x = 1$)
\end{itemize}

Thus, for each test the derivative does not change sign on the chosen interval, which matches the conditions for applying the combined method.

\subsection{Conclusions}
We compare the program results with the theoretical ones and present them in a table.
\begin{table}[h] 
	\centering
	\label{tab:2}
	\caption{Results of theoretical calculations for testing}
	\begin{tabular}{|c|c|c|c|c|}
		\hline
		\textbf{Function} & \textbf{Roots (theor.)} & \textbf{Roots (prog.)} & \textbf{Integral (theor.)} & \textbf{Integral (prog.)} \\
		\hline
		$x^2 + 5x + 6$ & $-3,-2$ & $-3,-2$ & $\frac{2}{3}$ & $0.6667$ \\
		$\sin x$ & $\pi n, n \in \mathbb{Z}$ & $3.1416$ & $2$ & $2$ \\
		$x^3 - 1$ & $1$ & $1$ & $2$ & $2$ \\
		\hline
	\end{tabular}
\end{table}
\newpage

The functions \texttt{root} and \texttt{integral} work correctly and achieve the required accuracy.

\section{Analysis of Mistakes Made}

\begin{itemize}
	\item missing \texttt{finit} instruction at the start of the assembly functions that compute values and derivatives of the given functions
	\item refinement of the \texttt{integral} function to reuse previously computed values
	\item missing function prototypes
	\item using second derivatives in the \texttt{root} function
\end{itemize}

\newpage
\begin{raggedright}
	\addcontentsline{toc}{section}{References}
	\begin{thebibliography}{99}
		\bibitem{math} Ilyin V. A., Sadovnichy V. A., Sendov Bl. Kh. Mathematical Analysis. Vol. 1 —
		Moscow: Nauka, 1985.
	\end{thebibliography}
\end{raggedright}

\end{document}
