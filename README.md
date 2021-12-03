# Bitcoin Adress Swapper
A proof-of-concept application to demonstrate how Bitcoin addresses can be altered by malware.

# Explanation
Due to Bitcoin, and other cryptocurrency, addresses generally being pseudo-random, malware developers have targeted how people most often copy and paste the address. This gives the opportunity to exchange the address while in the victims' clipboard with a different address, with the presumption the victim will deposit cryptocurrency to the address in their clipboard.
<br>
I've emulated this with a console application. Trying it out, you may find it very easy to be fooled if not paying attention.
<br><br>
Example Bitcoin addresses to test:
- `1QHWbgeFNJc5PukTc8jAZoCHD8mLjHAzLA`
- `1N3bMCR9o3mahsnLry1raHB9GBJG`
- `1PCRwXfawZDJXn9yuPxoYwej6wctcvW7xy4`
- `1QHLTLQuXjN31EorfGchfp2wGM1jYdK4`
- `3Y4WNyJbnua2ouGecXzPNxVz6CC7`

# Usage
When the program is ran, the task bar icon and console will be hidden. Close the program by finding it in task manager and ending the process.
<br>
To change what the exchanged clipboard contents are, run the program with the first argument being the string.

# Disclaimer
Needless to say, this code isn't designed to be used maliciously. This program is to go in conjunction with a defense for such attacks I'm developing, which will be released soon (nothing big). While not being a large threat, this program could be used negatively which is not the intended use. Purely learn from samples such as this and don't be a script kiddie.
