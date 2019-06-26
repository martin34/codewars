# Low level software security

## Resources

[C Memory Layout](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
[C Vulnerbilities](https://security.web.cern.ch/security/recommendations/en/codetools/c.shtml)
[C++ Vulnerbilities](https://security.web.cern.ch/security/recommendations/en/codetools/cpp.shtml)
* File Handles 
* Buffer overflow
* Never use malloc and free (instead new and delete)
* Never use C style arrays and functions like fscanf
[How buffer overflows work](http://arstechnica.com/security/2015/08/how-security-flaws-work-the-buffer-overflow/)
[PC Assembly Language](http://www.drpaulcarter.com/pcasm/)
[Smashing the Stack for Fun and Profit](http://insecure.org/stf/smashstack.html)
[Exploiting Format String Vulnerabilities](http://crypto.stanford.edu/cs155/papers/formatstring-1.2.pdf)
[Basic Integer Overflows](http://phrack.org/issues/60/10.html)


# Building secure software

## Resources

<li><a href="http://web.mit.edu/Saltzer/www/publications/protection/" target="_blank" rel="noopener nofollow">Protection of Information in
Computer Systems</a>, by
Saltzer and Shroeder. Classic paper from 1975 that is still highly relevant
today.</li>
<li>Bruce Schneier's <a href="https://www.schneier.com/essays/archives/1999/11/a_plea_for_simplicit.html" target="_blank" rel="noopener nofollow">plea for simplicity</a> in computer systems.</li>
<li><a href="http://cybersecurity.ieee.org/center-for-secure-design/avoiding-the-top-10-security-flaws.html" target="_blank" rel="noopener nofollow">Top 10 Security Design Flaws</a>, brought to you be the <a href="http://cybersecurity.ieee.org/center-for-secure-design.html" target="_blank" rel="noopener nofollow">IEEE Center on Secure Design</a></li>
<li><a href="https://security.appspot.com/vsftpd.html" target="_blank" rel="noopener nofollow">Very Secure FTPD</a>; here is some description of VSFTPD's <a href="https://security.appspot.com/vsftpd/DESIGN.txt" target="_blank" rel="noopener nofollow">design</a>,
<a href="https://security.appspot.com/vsftpd/IMPLEMENTATION.txt" target="_blank" rel="noopener nofollow">implementation</a>, and assumptions of <a href="https://security.appspot.com/vsftpd/TRUST.txt" target="_blank" rel="noopener nofollow">trust</a>
(and their impact on the implementation).</li>
<li>Gary McGraw's book, <a href="http://www.swsec.com/" target="_blank" rel="noopener nofollow">Software Security: Building Security In</a></li>

Testing phases in developmet:

1. Requiremnet --> Security requirement, Abuse Cases, Architectual risk analysis
2. Design --> security-oriented design
3. Implementation --> code review (with tools)
4. Testing --> risk based security testing, penetration testing

**Hardware is also important for security, but not so flexible to change durring development**

## Thread Model

Make it explicit, what could happen to design an appropriate defence.
Part of architectual risk analysis

--> Model powers of the adversary

Example users:

* Nework user
* Snooping user (same network)
* Co-located user (e. g. software installed via mailware)

The users have differnet capabilities and can therefore attack the system in different ways.

## Goals/Policies and system requirements

Typical goals:

* Confidentiality (and privacy and anonymity)
Sensitive information is not leaked. Also side channel leaks e. g. if someone has on account, a loggin failure is reported quicker than if it is without an account.
* Integrity (Sensitive information must not be damaged)
* Availability

Supporting mecanisam to reach this goals:

* Authentication (indentify actor e. g. human, or bot, customer, visitor)
How?
Does user know password, have the fingerprint, has the smartphone?
* Authorization (when is a principle e. g. humon, customer allowed to do something)
* Auditability (retain enough informatin to determine if and a how a breach of the system happened e. g. protecting the log files)

What influences the security requirements?

* Regulations
* General organzational policies
* Policies arrising from thread modelling and experience
* Design of abuse cases

### Avoiding flaws with principles

Flaw == problem in design
Bug == problem in implementation

Design happens on various levels, some are very close to the implementation. All of them can be flawed.
Software design is an iterative process. 
You start with some priciples and rules. Then do an risk based anlysis. This leads to the creatation/change of the rules and priciples, which have to be analysed again. 

Categories of principles:

* prevention
* mitigation (reduce the harm, if an unknown defect is exploited)
* detection and recovery e. g. monitoring and snapshots of states

**Core Priciples**

* Favour simplicity
  - use fail-safe defaults
  - do not expect expert users
* trust with reluctance
  - employ a small trusted computing base
  - grant the least privilege possible (promote privacy, compartmentalize)
* defend in depth
  - use community resources, no security by obscurity
* monitor and trace

### Favour simplicity

Goal: It is so simple, that it is obviously correct.
Why: This makes it easy to analyse, to develop and to correct errors.
Methods:

* Use fail-safe defaults
Legth of cryptographic keys: If the user can choose one, give him the safest choice as default
Password: Don't provide default passwords.
Which content is allowed: White-list the safe things e. g. don't reder images from unknown sources
* Do not expect expert users
Favour simple user interfaces, which present a obvious secure choice.
Don't ask users to often to make security decisions, they will get bored and click alwaiys yes.
Explain to the user, what effect their decisions have e. g. show them how their profile looks from the view of others.
* password: hard to guess, easy to remember e. g. meaningfull sentance instead of cryptic password
Additionally: Password meter, password manager

### Trust with reluctance

Improving security by reducing the need to trust:
* by using a better design
* by using a better implementation process
* by not making unnecessary assumptions e. g. not trusting third party libraries without performing tests and reviews

Methods:

* Keep a small trusted computing base (necessary system components that must work to maintain security)
If it is small, it is easy to argue and test, that it is safe.
* Lease privileges: Don't give a part of the system more privileges than it needs. So if it is compromised, the problem is not as big. (Similar to need to know). **Trust is transitive.** E. g. if you would allow in an e-mail programm vim as an editor, the user could run arbitrary shell commands.
* Input validation: Only trust validated imput.
* Promote privacy: Limiting access of system components to private data --> less components which could lead to security problems.
* Compartmentalization == Sandboxing --> Less possible ways to attack e. g. seccomp-bpf in linux (restricts permissions of a probramm to read, write, exit, sigreturn)

### Defense in depth

If one layer is broken, there is still another one protecting the system and the data.
Example:
* Passwords can be stolen, therefore encrypt them (Don't assume, that no compromise is possilbe).
  - Use community resources, insead of writing implementing all defense mechanisms on your own. Additionally validate these resources with tests and reviews.
  - Vet designs public
  - Stay on recent threads and research
  - Don't use broken crypto impl.

### Monitoring and tracability

Assuming there is no perfect defense, you need to detect an security breach and recover. Afterwards the system needs to be improved to prevent similar incidents.

Methods:

* Important steps must be logged

### Top 10 design flaws

* Assume trust, rather than explicitly give it or award it.
* Use an authentication mechanism that can be bypassed or tampered with (e. g. mobile app which doesn't check ssl certificate, because it was turned off durring development, authentication tokens with long timeouts --> likly that stoolen cookies cause harm)
* Authorize without considering sufficient context.
* Confuse data and control instructions, and
* process control instructions from untrusted sources.
* Fail to validate data explicitly and comprehensively.
* Fail to use cryptography correctly 
  - don't implement your own cyptography
  - encryption protects confidentiality, but not integrity (data can be changed)
  - hashing protects integrity, but not confidentiality (someone could have seen, what it contains)
  - generate proper keys (sufficient size, don't hard code them in accessable binaries)
  - sufficient randomness in the system?
* Fail to identify sensitive data and how to handle it (e. g. file on the iPhone containing all the safed location points; properly identify, when data is expesed; how does the data and exposure change over time)
* Ignore the users.
* Integrate external components without considering their attack surface (e. g. using bash on servers to start programms)
* Rigidly constrain future changes to objects and actors.  

### Examples from the VSFTP daemon

* Use different processes with different privileges (e. g. file access, root and non-root, ...), exchange data via IPC --> command reader, command processor, trusted computing ground in different processes
* Every user has its own command reader/processor process --> different user can't access other users session
* does not trust executables like /bin/ls, but implements it own directory listing --> small attack surface

### Real world study
www.bsimm.com

# Security testing
## Static analysis and symbolic execution

<li><a href="http://www.pl-enthusiast.net/2015/03/03/noninterference/" target="_blank" rel="noopener nofollow">What is noninteference, and how do
we enforce it?</a> - A blog entry Mike wrote
about using static analysis to find information leaks; relates to the lecture
material on <em>implicit flows</em> and <em>tainting analysis</em></li>
<li><a href="http://cacm.acm.org/magazines/2010/2/69354-a-few-billion-lines-of-code-later/fulltext" target="_blank" rel="noopener nofollow">A Few Billion Lines of Code Later:
Using Static Analysis to Find Bugs in the Real World</a> - An article by the Coverity team on their experience writing
and deploying a commercial static analysis tool</li>
<li><a href="http://users.ece.cmu.edu/~ejschwar/bib/schwartz_2010_dynamic-abstract.html" target="_blank" rel="noopener nofollow">All You Ever Wanted to Know About
Dynamic Taint Analysis and Forward Symbolic Execution (but might have been
afraid to ask)</a> - mathematical
presentation of these analyses and their variations</li>

### Resources

Static analyzers 

<li>Coverity's free <a href="http://www.coverity.com/press-releases/coverity-launches-code-spotter-in-free-beta-version-to-speed-defect-detection-in-java-code/" target="_blank" rel="noopener nofollow">Code Spotter</a> and <a href="https://scan.coverity.com/" target="_blank" rel="noopener nofollow">Coverity Scan</a> initiatives</li>
<li><a href="http://clang-analyzer.llvm.org/" target="_blank" rel="noopener nofollow">Clang Analyzer</a> - A static analyzer built on the LLVM framework for C and C++ programs</li>
<li><a href="http://www.mlsec.org/joern/" target="_blank" rel="noopener nofollow">Joern</a> - A static analyzer for C and C++ programs</li>
<li><a href="http://findbugs.sourceforge.net/" target="_blank" rel="noopener nofollow">FindBugs</a> - A static analyzer for Java programs</li>

Symbolic executors

<li><a href="http://klee.github.io/" target="_blank" rel="noopener nofollow">KLEE</a> - A symbolic executor for LLVM bitcode (primarily supporting C and C++)</li>
<li><a href="https://bitbucket.org/khooyp/otter" target="_blank" rel="noopener nofollow">Otter</a> - A source-level symbolic executor for C code</li>
<li><a href="http://research.microsoft.com/en-us/projects/pex/" target="_blank" rel="noopener nofollow">Pex</a> - A symbolic executor for .NET</li>
<li><a href="http://channel9.msdn.com/blogs/peli/automated-whitebox-fuzz-testing-with-sage" target="_blank" rel="noopener nofollow">SAGE</a> - A 10-minute video on the SAGE whitebox fuzz tester (based on symbolic execution)</li>

SMT solvers (used by various of the above tools)

<li><a href="http://z3.codeplex.com/" target="_blank" rel="noopener nofollow">Z3</a> - developed at Microsoft Research</li>
<li><a href="http://yices.csl.sri.com/" target="_blank" rel="noopener nofollow">Yices</a> - developed at SRI</li>
<li><a href="https://sites.google.com/site/stpfastprover/" target="_blank" rel="noopener nofollow">STP</a> - developed by Vijay Ganesh, now @ Waterloo</li>
<li><a href="http://www.cs.nyu.edu/acsys/cvc3/" target="_blank" rel="noopener nofollow">CVC3</a> - developed primarily at NYU</li>

### Basics

Methods:

* Testing
* Auditing
* Static analysis

### Flow anlysis

Specifiy parts of pogram, which get untrasted data and parts which need trusted. Analysis will find possible parts, between both, which should not exist.
Label trusted parts, untrusted parts and sanitiscers. The probramm will find possible problems.

## Symbolic execution

Symbolic executor tries to follow all possible path to find bugs. This is very time and resource consuming, but can help to find bugs. 
--> Important addition for sanitzer part of the program?

Examples:

* KLEE (LLVM, free)
* Mergepoint (used for LINUX)
* SAGE (Microsoft)

## Penetration Testing and fuzz testing

Resources:


<li><a href="http://www.rand.org/pubs/reports/R609-1/index2.html" target="_blank" rel="noopener nofollow">Ware report</a> - introduced the idea of penetration testing, as well as many
other foundational ideas in systems security</li>
<li><a href="http://www.iacertification.org/cpt_certified_penetration_tester.html" target="_blank" rel="noopener nofollow">CPT (pen testing) certification</a> - establish your credentials as a pen tester</li>
<li><a href="https://www.defcon.org/html/links/dc-ctf.html" target="_blank" rel="noopener nofollow">Defcon CTF contest</a> - be the first to find vulnerabilities in other competitors'
systems and patch them in your own</li>

Pentration:

Analyce a complete programm/system for secirity problems. 
Seperate/specialized team with specialized tools. 
Given similar rights/knowledge a attacker could have.
Tester needs to know a lot about the target domain e. g. web, ... including common weaknesses, misconfigurations and designs.
"70 %" is about messing with parameters e. g. urls.
"10 %" default passwords.
"10 %" about hidden files and directories.
"10 %" about others e. g. bypass authentication , replay, insecure web services, accessable configuration pages.

Advantage: 
"Real" security issues are found --> feel good factor.

Disadvantage:
If no problems are found, it does not mean that there are none. 
Not all problems will be found (probably).

Tools:

<li><a href="http://nmap.org/" target="_blank" rel="noopener nofollow">NMAP</a> - "network mapper" scans network to find what's
connected to it</li>
<li><a href="https://code.google.com/p/zaproxy/" target="_blank" rel="noopener nofollow">Zap</a>
- web proxy and automatic vulnerability scanner</li>
<li><a href="http://portswigger.net/burp" target="_blank" rel="noopener nofollow">Burp suite</a> - Several pen testing tools (some versions are free)</li>
<li><a href="http://www.offensive-security.com/metasploit-unleashed/Main_Page" target="_blank" rel="noopener nofollow">Metasploit</a> - customizable platform for developing, testing, and using
exploit code.</li>
<li><a href="http://www.kali.org/" target="_blank" rel="noopener nofollow">Kali</a> - Linux distribution with pre-installed pen testing tools.</li>

Fuzz testing:

Generate random input und test the system e. g. for memery error, non-termination, ...
Complements functional testing e. g. derive input from legitimate tests.

Different kinds:

* Black box testing 
* Grammer based; operator defines grammer, more likely to cover big parts of the program, than black box testing
* White box testing; Tool generates input, based on program analysis, often easy to use and computational expensive

Often file based or network based.

Fuzzing in combination with address sanitizers (ASAN) or memory checkers e. g. valgrind makes it easier to find the bug. The program terminates at the place of the bug e. g. buffer overflow and not later e. g. when overwritten memory is reused.


Tools:

SAGE (Microsoft) uses symbolic execution to generate fuzzing input.

<li><a href="https://github.com/aoh/radamsa" target="_blank" rel="noopener nofollow">Radamsa</a>
- mutation-based black-box fuzzer</li>
<li><a href="https://github.com/ouspg/blab" target="_blank" rel="noopener nofollow">Blab</a>
- grammar-based fuzzer</li>
<li><a href="http://lcamtuf.coredump.cx/afl/" target="_blank" rel="noopener nofollow">American Fuzzy Lop (AFL)</a> - mutation-based, white-box fuzzer, observers the noraml program flow and mutates the recored inputs</li>
<li><a href="http://caca.zoy.org/wiki/zzuf" target="_blank" rel="noopener nofollow">CERT basic fuzzing framework (Zzuf)</a> - found many high-profile bugs</li>
<li><a href="https://github.com/OpenRCE/sulley" target="_blank" rel="noopener nofollow">Sulley</a> - lots of extras to manage fuzzing as part of pen testing</li>
<li><a href="http://resources.infosecinstitute.com/intro-to-fuzzing/" target="_blank" rel="noopener nofollow">SPIKE</a> - network fuzzing framework</li>

