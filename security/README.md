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
the project.</li><li><a href="http://ferruh.mavituna.com/sql-injection-cheatsheet-oku/" target="_blank" rel="noopener nofollow">SQL injection cheat sheet</a> - This is a good reference for doing SQL injection</li><li><a href="https://www.owasp.org/index.php/Cross-site_Scripting_(XSS" target="_blank" rel="noopener nofollow">OWASP's guide to cross-site
scripting (XSS)</a>) - Pay
particular attention to the testing guide, for finding XSS vulnerabilities.</li><li><a href="https://www.owasp.org/index.php/Session_hijacking_attack" target="_blank" rel="noopener nofollow">OWASP's guide to session hijacking</a> - Note that they give an example of stealing a session cookie
via XSS, which is in play for the project.</li><li><a href="https://www.owasp.org/index.php/Cross-Site_Request_Forgery_(CSRF" target="_blank" rel="noopener nofollow">OWASP's guide to cross-site request
forgery (CSRF)</a>)</li><li><a href="http://cwe.mitre.org/top25/" target="_blank" rel="noopener nofollow">CWE/SANS top 25 most dangerous
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

