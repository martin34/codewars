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

### Web security

<li><a href="https://www.owasp.org/index.php/SQL_Injection" target="_blank" rel="noopener nofollow">OWASP's guide to SQL injection</a> - This is a good overview. You might find the linked page on <a href="https://www.owasp.org/index.php/Testing_for_SQL_Injection_(OTG-INPVAL-005" target="_blank" rel="noopener nofollow">Testing for SQL injection</a>)) to be useful for
the project.</li>
<li><a href="http://ferruh.mavituna.com/sql-injection-cheatsheet-oku/" target="_blank" rel="noopener nofollow">SQL injection cheat sheet</a> - This is a good reference for doing SQL injection</li>
<li><a href="https://www.owasp.org/index.php/Cross-site_Scripting_(XSS" target="_blank" rel="noopener nofollow">OWASP's guide to cross-site
scripting (XSS)</a>) - Pay
particular attention to the testing guide, for finding XSS vulnerabilities.</li>
<li><a href="https://www.owasp.org/index.php/Session_hijacking_attack" target="_blank" rel="noopener nofollow">OWASP's guide to session hijacking</a> - Note that they give an example of stealing a session cookie
via XSS, which is in play for the project.</li>
<li><a href="https://www.owasp.org/index.php/Cross-Site_Request_Forgery_(CSRF" target="_blank" rel="noopener nofollow">OWASP's guide to cross-site request
forgery (CSRF)</a>)</li>
<li><a href="http://cwe.mitre.org/top25/" target="_blank" rel="noopener nofollow">CWE/SANS top 25 most dangerous
software errors</a> - A
little dated, but still relevant; here's the <a href="http://cwe.mitre.org/top25/#Listing" target="_blank" rel="noopener nofollow">brief
listing</a>.</li>

#### SQL Injection 

Data e. g. user input is interpreted as code. 

Countermeasures 

* Sanitze the input e. g. blacklist, whitelist (more safe than blacklisting, but less flexible)
* prepared statements

Additionally you should have different layers of devense e. g. 

* Limit privileges
* Encryped sensitive data --> it is not usable if it is exposed

#### Session hijacking

Attacker obtains cockie (with session identifier) and uses it as identifier to an server.

Points of attack:

* Compromise the server
* Predict the gererated cookie --> random, long
* Network based attacks e. g. Sniff the network, DNS cache poisoning = trick the user to send the cookie to the attacker (use https)

Defend in depth e. g. 
* use additional hidden fields or use referer attribute to check if previous page is reasonable
* timeout 
* delete cookie as soon as seesion ends from users machine

Non-defense:
* Store IP address for session | False positive, because of WIFI, 3G and DHCP IP change | False negative e. g. using a NAT box and having the same IP

#### Cross-site Request Forgery

Scenario:
User is logged in to bank account and cookie is obtained.
He serves in the internet and visits an other page. The attacker page contains a html tag, which causes the browser to perfrom a transaction (could be hided as an image, ...).
Because of the cookie, no authentication is required.
The request comes from the users browser with the correct cookie.
Could be also a spam email sent by the browser.

Protections:

* Check the referer field (request comes from a trusted site) | Problem: not all browser send it
* Include a secret in every link/form --> hard to guess for the attacker

#### Cross-site scripting

**It is possible to alter the cookie via JAVA Script. --> Browsers implement same orgin policy: scripts can only access content with the same origin (domain name)**
Cross-site scripting attacks tick the browser to execute the attacker script as it would come from a different website. --> access to sensitive data

Two types:

1. Stored XSS attack: Malicous scriped is injected to the server e. g. by uploading data with browser (server fails to block content with java script content)
2. Reflected XSS attack: User visits attacker website, in response attacker script and link to attacked website is sent back. User clicks on the link. The attacked website echos back the user input, with the attackers script and the script is executed. This echoing could be part of the functionality e. g. user does a search query and server answers with the input search query and the result. This echoing is the vulnerbility.

Protection:

* Sanitize the input e. g. remove all scrip tags (this is hard to do, because there are various ways and some are browser specific) or better white list

Additional example:
Ruby on rails has good support for exchanging yaml files. It is possible to encode any ruby code in a yaml file. The yaml interpreter can be tricked to execute this code. --> Framework error, input needs to be checked or whitelisted 

### Building secure software

#### Resources

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

#### Thread Model

Make it explicit, what could happen to design an appropriate defence.
Part of architectual risk analysis

--> Model powers of the adversary

Example users:

* Nework user
* Snooping user (same network)
* Co-located user (e. g. software installed via mailware)

The users have differnet capabilities and can therefore attack the system in different ways.

#### Goals/Policies and system requirements

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

#### Avoiding flaws with principles

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

##### Favour simplicity

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

#### Trust with reluctance

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

#### Defense in depth

If one layer is broken, there is still another one protecting the system and the data.
Example:
* Passwords can be stolen, therefore encrypt them (Don't assume, that no compromise is possilbe).
  - Use community resources, insead of writing implementing all defense mechanisms on your own. Additionally validate these resources with tests and reviews.
  - Vet designs public
  - Stay on recent threads and research
  - Don't use broken crypto impl.

#### Monitoring and tracability

Assuming there is no perfect defense, you need to detect an security breach and recover. Afterwards the system needs to be improved to prevent similar incidents.

Methods:

* Important steps must be logged

#### Top 10 design flaws

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

#### Examples from the VSFTP daemon

* Use different processes with different privileges (e. g. file access, root and non-root, ...), exchange data via IPC --> command reader, command processor, trusted computing ground in different processes
* Every user has its own command reader/processor process --> different user can't access other users session
* does not trust executables like /bin/ls, but implements it own directory listing --> small attack surface

## Security testing
### Static analysis and symbolic execution

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

#### Resources

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

#### Basics

Methods:

* Testing
* Auditing
