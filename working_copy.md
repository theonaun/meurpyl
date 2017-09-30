---
title: Model Enterprise Usage Rules For The Python Language
---

\[overlay\] ;

Model Enterprise Usage Rules For The Python Language

<span>Revised 2017-09-13</span>\
<span>Version 0.1.0</span>\

<span>Copyright 2017, Theo Naunheim</span>

**License**

Licensed under the Apache License, Version 2.0 (the “License”); you may
not use this file except in compliance with the License. You may obtain
a copy of the License at:

<http://www.apache.org/licenses/LICENSE-2.0>

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an “AS IS” BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

**Trademark**

Anaconda is a registered trademark of Anaconda, Inc. Java is a
registered trademark of the Oracle Corporation. Linux is a registered
trademark of Linus Torvalds. Python and the Python logo are a registered
trademarks of the Python Software Foundation. Use of the Python logo
does not imply endorsement by the Python Software Foundation. C\#, .NET,
PowerShell, and Windows are registered trademarks of the Microsoft
Corporation.

**Authors**

<span> Theo Naunheim &lt;<theonaunheim@gmail.com>&gt;</span>

**Abstract**

Python is an interpreted, general purpose programming language that
excels in data analysis, systems administration, and a variety of other
roles. Because of its flexibility and the speed at which it can be used
to complete projects, Python is increasingly being used within the
financial services sector. Python is unlike more traditional enterprise
languages, such as COBOL, Java, and C\#; consequently it has a unique
risk profile that benefits from individualized treatment. The purpose of
this document is to provide a model set of rules for the governance and
use of the Python language in the financial services context.

Preamble {#preamble .unnumbered}
--------

Corporations are creatures of habit; they do today what they did
yesterday (because what they did yesterday worked). Convention has its
benefits: it is stable, predictable, and even comforting. It is not
completely without cost, however. Companies that fail to innovate
stagnate and die every day.

Enterprise Python shares these trade offs. Unlike COBOL, it does not
have fifty years of enterprise usage. Unlike C\#, it is not backed up
with an army of software engineers and support staff to integrate the
language within existing intrastructure. In its place, Python provides a
fluid and expressive environment that is unparalelled for rapid
development and data science.

Risk managers and information technology employees often recognize these
strengths, but are hesistant to fully accept Python in their
organizations without fuller understanding of the risks involved. In
order to make Python more palatable at the enterprise level, some
tradeoffs must be made. A measure of autonomy is sacrificed for the sake
of control and oversight. Some flexibility is sacrificed for the sake of
stability and uniformity. Empowerment is sacrificed for the sake of
security and mitigating risk.

These rules use the following guiding principles to inform these
trade-offs:

-   **The correct path should be the path of least
    resistance**–employees are more likely to comply if the rules make
    it easy to do so.

-   **Arbitrary is better than indefinite**–having bright line rules
    reduces confusion even if it does not always yield the
    ideal outcome.

-   **Make it as safe as it needs to be (but no safer)**–things cannot
    be made completely safe, but they can be made completely useless.

Finally, the Model Enterprise Usage Rules for the Python Language
(“MEURPyL” or “Meurpyl”) provides a model for a set of baseline
standards governing the Python language. Meurpyl is just that: a
baseline. It is not dogma that is intended to be adopted without
question. Rather, it is intended to function as a base by which
organizations can adapt Python for their own purposes–using what works
and ignoring the rest.

Risk Profile
============

Introduction
------------

This section covers many basic details of the Python language, along
with rudimentary descriptions of various risk types; it may not be
necessary for all readers.

Python has a number of unique characteristics that makes it unlike other
languages within the enterprise space. Among other things, it is
interpreted instead of compiled, it uses syntatically significant
whitespace instead of braces, and it uses a virtual machine specific to
the Python language. These attributes significantly affect the risks
Python presents and the manner in which they can be mitigated.

This section will examine:

1.  Interpretation

    1.  Intentional misuse

    2.  Unintentional misuse

    3.  Model risk

    4.  Governance risk

    5.  Maturity risk

2.  Syntax

3.  Dynamic tyling

4.  Standard library

5.  Packages

Interpretation
--------------

The largest difference between Python and other enterprise languages
from a risk management perspective is that Python can be thought of as
an interpreted language, as opposed to a compiled language. [^1] $^{,}$
[^2] Computing languages can fall on a spectrum of those that are
primarily interpreted (such as R and Python) and those that are
primarily compiled (such as COBOL and C++). The difference is that
compiled languages do a comparatively larger portion of any computation
at the time of compilation, and have minimal runtime environments.
Interpreted languages do most or all of the computations required at
runtime. Though Python is partially interpreted and partially compiled,
for the purposes of these rules Python will be referenced as an
interpreted language.

The risk dynamic with interpreted languages is inherently different from
compiled languages. With compiled languages, it is relatively easy
segregate the development and source code of an application from the
user of an application. A development group can compile the
application’s source code, and the resulting binary can be forwarded to
a completely separate environment for the end user. It is exceedingly
difficult for an end user to modify the compiled binary and cause
unintended behavior. With interpreted languages, the end user of a
program is essentially being given possession of the application’s
source code. A sophisticated end-user could modify this source code
cause unintended behavior. Arguably, one could say that this is
tantamount to the development environment being included on the end
users computer.

### Intentional misuse

One major source of risk with development in any computing language is
intentional misuse. This misuse can manifest itself in any number of
ways, such as through the theft of customer information, embezzlement,
or myriad other negative consequences.

Using foreign packkages people who don’t know.

operations reputational The distinction between interpreted and compiled
becomes important when Managing risk with compiled languages within the
enterprise is accomplished by segregating the The addition of an
interpreter and run time ... Every environment is arguably a development
environment ...

distinction Compiled languages are comparatively easy to secure. The
distinction between interpreted and compiled becomes All languages share
certain risks. The use of any languages brings risk.

Dynamic Typing
--------------

Typing

Syntax
------

Accessability is a double edged sword.

Standard Library
----------------

T

Appendix A
==========

Glossary
========

[^1]: <https://en.wikipedia.org/wiki/Interpreted_language>

[^2]: <https://en.wikipedia.org/wiki/Compiled_language>
