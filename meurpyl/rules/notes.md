

# Usage

## Experimentation

## Production


# Code Governance

## Package Review

## Internal Code Review


# Infrastructure

## Testing

## Documentation




 M.E.U.R.Py.L. (FinTech)
 
## The Model Enterprise Usage Rules for the Python Language
 
### Preamble
 
Historically, Python has been viewed as the "wild west" of programming
languages by many enterprises. Unlike many languages, it did not have a
discrete compiler that could be locked down separately from its run-time. It
also didn't have mind-numbing syntax to scare people off and keep its user
base (and consequently its risk) down. It's run/fail/repeat workflow was
anathema to many of the of the old guard. It was open-source software without
"official" support provided by a vendor.
 
This mix of factors made it difficult for IT compliance groups to fully
embrace the language, irrespective of its positive qualities. It's easily
accessible. It speeds development time. It makes the expression of ideas
within code fluid and expressive.
 
In order to provide some level of comfort to the enterprise, tradeoffs must be
made. Autonomy is sacrificed for the sake of control and oversight. Flexibility
is sacrificed for the sake of stability and uniformity. Empowerment is
sacrificed for the sake of security and peace of mind.
 
By adopting a set of enterprise rules, it is possible to make Python more
palatable to IT and compliance groups while still preserving many of the
positive qualities that make Python popular with businesses lines.
 
By giving up a relatively small amount of freedom on the part of the end user,
we can provide a comparatively larger gains to stability, control, and
oversight. These rules endeavor to provide a middle path between lawlessness
and draconian control.
 


Risk Profile
	# compile vs interpreted
	# accessability


### Definitions
 
 
### Table of Contents
 
Control vs. Freedom, Stability vs. Flexibility.
 
### Use Cases.
 
### Setup
### Governance
Decouple sensitive data and processing environments.
Snitch shell.
Don't give access to sensitive areas.
Reproducibility ... bus factor.
### Packages
 
License approvals
 
### Source Code Control
 
### Practices


Trainung outreach testing governance specs testing prod

Only documented or supported packages licensing

arbitrary is better than indefinite. male correct path the path of least resistance


classify usage

development
analysis
centralized analysis

Model Enterprise Usage Rule for the Python Language (MERPyL)

Are we OK with public repositories if we can limit the packages?
PyPI
Anaconda.org

Are we OK with crippling Pip/Conda, and only allowing privileged users to install?

Are we OK with the fact that we cannot prevent people from using source code?

Do we need to review everything to what extent? Open source good enough


No repository required if:
a) you wrote it 
b) it is not run on a periodiic basis
c) the code's failure would not ruin anything ... and can be done otherwise.

If it is in a respository in must be reviewed yearly. License goes to the bank.
If it is used for mission critical code, must be reviewed and maintained.
Code must have sufficient documentation to ensure that someone unfamiliar with code should understand it.

Intel Math Kernel Library.

PyPI repository ... sign packages. Source code Mercuria

Preamble
* stability
* safety
* effective
Infrastructure
* pypi
* local 
* centtalized
Oversight
Usage
* 
Acknowledgements


models
meta file
log:

testing requirements

production

administrationi


Separate variable definitions.


4 environs
Data Exp
Data Proc
Sys Adm
Sys Scr
 
 
Here are a list of the risks. Here are the list of the unique things we will be looking at.
 
1. Intentional Misuse
Interp
Dynamic
Ease of use
 
2. Model Risk
 
3. Unintentional Misuse
 
4.

		%Can do things, unlike COBOL.

		%TESTING?

		%https://ithandbook.ffiec.gov/media/274741/ffiec_itbooklet_developmentandacquisition.pdf

		%https://ithandbook.ffiec.gov/media/274793/ffiec_itbooklet_informationsecurity.pdf

		%https://ithandbook.ffiec.gov/media/274825/ffiec_itbooklet_operations.pdf

		%https://ithandbook.ffiec.gov/media/274809/ffiec_itbooklet_management.pdf

		%ISO 9000 standards?

		%https://ithandbook.ffiec.gov/media/274709/ffiec_itbooklet_audit.pdf

	\subsection{Syntax}

		Accessability is a double edged sword.


\iffalse
				\begin{enumerate}
   			\item Interpretation
   			\begin{enumerate}
	   			\item Intentional misuse
	   			\item Unintentional misuse
	   			\item Model risk
	   			\item Governance risk
	   			\item Maturity risk
   			\end{enumerate}
   			\item Syntax
   			\item Dynamic tyling
   			\item Standard library
   			\item Packages
   			\item Language Support

		\end{enumerate}
			Using foreign packkages people who don't know.

			operations reputational
			The distinction between interpreted and compiled becomes important when 
			Managing risk with compiled languages within the enterprise is accomplished by segregating the 
			The addition of an interpreter and run time ...
			Every environment is arguably a development environment ...

			distinction
			Compiled languages are comparatively easy to secure.
			The distinction between interpreted and compiled becomes 
			All languages share certain risks.
			The use of any languages brings risk. 
		\fi
