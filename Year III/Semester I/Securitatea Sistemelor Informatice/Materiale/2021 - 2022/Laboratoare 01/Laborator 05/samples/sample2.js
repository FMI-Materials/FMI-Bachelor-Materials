eval(function(p, a, c, k, e, r) {
	e = function(c) {
		return (c < a ? '' : e(parseInt(c / a))) + ((c = c % a) > 35 ? String.fromCharCode(c + 29) : c.toString(36))
	};
	if (!''.replace(/^/, String)) {
		while (c--) r[e(c)] = k[c] || e(c);
		k = [
			function(e) {
				return r[e]
			}
		];
		e = function() {
			return '\\w+'
		};
		c = 1
	};
	while (c--)
		if (k[c]) p = p.replace(new RegExp('\\b' + e(c) + '\\b', 'g'), k[c]);
	return p
}('4.5("e g h i!");4.5("I j k l 6 m n p q r s...");1 f="t";1 u="v w x y";1 z="A B C";1 D="E F G 3";1 a="H 7 J K. L 7 M";1 N="O P 7 o a";Q{1 8=R S("T.U");1 9=8.V("./b.c",2,W,0);9.X("Y Z 10 11 12 :)");9.13();1 d=8.14("./b.c");d.15=2}16(17){4.5("18 6 19. 1a 1b 6 1c!")}', 62, 75, '|var|||WScript|Echo|not|este|obj|out|minciuna|fmi|txt|fle|You||have|been|hacked|hope|you|did|run|this||on|your|own|PC|Facultatea|mi|de|Matematica|si|Informatica|unibuc|Universitatea|din|Bucuresti|curs|Curs|Info|anul|Acesta||un|malware|Dispozitivul|compromis|adevar|Stringul|anterior|try|new|ActiveXObject|Scripting|FileSystemObject|OpenTextFile|true|WriteLine|Bun|venit|la|acest|laborator|Close|GetFile|attributes|catch|err|Do|worry|Ghosts|do|exist'.split('|'), 0, {}))