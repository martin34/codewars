SQL Union statement to combine statements

Inner queries:
SQL> SELECT * 
   FROM CUSTOMERS 
   WHERE ID IN (SELECT ID 
         FROM CUSTOMERS 
         WHERE SALARY > 4500) ;

SQL statement ends with ";"

Perform exploits on BadStore to find answers to the following questions; once you have, complete the on-line assessment.

* One of the BadStore pages has a hidden form field that establishes a new user's privilege level. What is the name of this field?
  Analyse network traffic, edit form with role field and resend it.
  "role"

* How many items for purchase are in BadStore's database? Use SQL injection on the quick search form field to find out.
  Use: 
```
' OR 1=1 --  '
```
--> 16 items in table including test item

* What operations are suppliers permitted to do once they have logged into the "suppliers only" area? Use SQL injection to bypass authentication, or find a way to create an account as a supplier.

* Log in as joe@supplier.com --- this is possible in a variety of ways, including SQL injection. Then look at his previous orders and answer the question: What credit card number did he use to make a purchase of $46.95? Multiple answers are possible, but we will accept all of them.
```
joe@supplier.com ' -- 
```
--> 4111 1111 1111 1111, 5500 0000 0000 0004

* Get administrator privileges and then use the admin action to look at the user database. There are two users whose emails have the form XXX@whole.biz; what is the XXX portion of either of the two users? For example, if one of the users is jackie@whole.biz, the right answer is jackie. (The answer is case-sensitive.)
Use admin with an user with admin privileges action in url: http://www.badstore.net/cgi-bin/badstore.cgi?action=admin
fred@whole.biz
landon@whole.biz

* BadStore uses cookies to implement a session key, once you've authenticated, and for tracking the contents of the cart, once you've added something to it. You can figure out the cookies in use by BadStore in various ways. One way is to do an XSS attack on the guest book. Get the guest book to run the code <script>alert(document.cookie)</script> and it will tell you the current cookies. (Be sure you have popups enabled on your browser or this won't work.) Alternatively, you can examine the cookies directly using Firefox developer tools. Recall that cookies are pairs key=value. What is the key of the session cookie?
Both works easily: bWUyQGZvby5jb206NDU1NTIzZDg2YThhMWFiN2M3ZDMzMjA4ZmUwMjE5ZTc6bWUyOlU%3D%0A
```
<script>var l = document.cookie; for each (var c in l){ alert(decodeURIComponent(c))}</script>
```
Or simply use firefox storage tab (web developer tools):
--> SSOid

* What is the key of the cookie used for the cart?
--> CartID

* BadStore's session cookie format is poorly designed because it is uses a predictable structure. In particular, it is an encoded string (with a URL-encoded newline at the end) of the form XXX:YYY:ZZZ:U. What are the XXX, YYY, and ZZZ portions of this string?
bWUyQGZvby5jb206NDU1NTIzZDg2YThhMWFiN2M3ZDMzMjA4ZmUwMjE5ZTc6bWUyOlU%3D%0A --> decode url --> decode base64 --> me2@foo.com:455523d86a8a1ab7c7d33208fe0219e7:me2:U == email:password as md5 hash:fullname

* BadStore's cart cookie is also an encoded string with a predictable structure XXX:YYY:... etc., and it probably contains information it shouldn't. Which field of the decoded string could an attacker change to give himself a discount on an item's price?

Cart:
<TABLE BORDER=1><TR><TH>ItemNum</TH> <TH>Item</TH> <TH>Description</TH> <TH>Price</TH> <TH>Image</TH> <TH>Order</TH></TR><TR><TD>1011</TD> <TD>Money</TD> <TD>There's never enough</TD> <TD>$9500.00</TD> <TD ALIGN="CENTER"><IMG SRC=/images/1011.jpg></TD> <TD ALIGN="CENTER"><INPUT type=checkbox checked name='cartitem' value=1011></TD></TR></TABLE>
Cookie: 
1561019566%3A1%3A9500%3A1011 --> decode url --> 1561019566:1:9500:1011 == ?:number of items:price:item number
