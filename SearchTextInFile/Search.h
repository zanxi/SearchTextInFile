#pragma once

#include "libh.h"

void ex()
{


	/*namespace fs = boost::filesystem;
	boost::regex reg(std::string("\.+.") + argv[1]);
	for (fs::directory_iterator iter = fs::directory_iterator(fs::current_path());
		iter != fs::directory_iterator(); ++iter)
	{
		if (boost::regex_match(iter->path().generic_string(), reg))
		{
			fs::remove(iter->path());
		}
	}*/

	std::string haystack = "It is like looking for a needle in a haystack";
	std::string needle = "needle";

	bool found = boost::algorithm::contains(haystack, needle);

	if (found) {
		std::cout << "String found" << std::endl;
	}
	else {
		std::cout << "String not found" << std::endl;
	}


	regex re("<\\s*A\\s+(?:[^>]*?\\s+)?href\\s*=\\s*\"([^\"]*)\"", std::regex_constants::icase);
	string subject("<head><title>Search engines</title></head><body><a href=\"https://yandex.ru\">Yandex</a><a href=\"https://google.com\"></a></body>");
	vector<string> result(sregex_token_iterator(subject.begin(), subject.end(), re, 1),
		sregex_token_iterator());

	for (auto& s : result) cout << s << endl;

	//*********************************************

	std::string s = "Some people, when confronted with a problem, think "
		"\"I know, I'll use regular expressions.\" "
		"Now they have two problems.";

	std::regex self_regex("REGULAR EXPRESSIONS",
		std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(s, self_regex)) {
		std::cout << "Text contains the phrase 'regular expressions'\n";
	}

	std::regex word_regex("(\\w+)");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), word_regex);
	auto words_end = std::sregex_iterator();

	std::cout << "Found wwwwwwwwwwwwww "
		<< std::distance(words_begin, words_end)
		<< " words\n";

	const int N = 6;
	std::cout << "Words longer than " << N << " characters:\n";
	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		if (match_str.size() > N) {
			std::cout << "  " << match_str << '\n';
		}
	}

	std::regex long_word_regex("(\\w{7,})");
	std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
	std::cout << new_s << '\n';

	//**********************************************

	const char* first = "abcd";
	const char* last = first + strlen(first);
	std::cmatch mr;
	std::regex rx("abc");
	std::regex_constants::match_flag_type fl =
		std::regex_constants::match_default;

	std::cout << "search(f, f+1, \"abc\") == " << std::boolalpha
		<< regex_search(first, first + 1, rx, fl) << std::endl;

	std::cout << "search(f, l, \"abc\") == " << std::boolalpha
		<< regex_search(first, last, mr, rx) << std::endl;
	std::cout << "  matched: \"" << mr.str() << "\"" << std::endl;

	std::cout << "search(\"a\", \"abc\") == " << std::boolalpha
		<< regex_search("a", rx) << std::endl;

	std::cout << "search(\"xabcd\", \"abc\") == " << std::boolalpha
		<< regex_search("xabcd", mr, rx) << std::endl;
	std::cout << "  matched: \"" << mr.str() << "\"" << std::endl;

	std::cout << "search(string, \"abc\") == " << std::boolalpha
		<< regex_search(std::string("a"), rx) << std::endl;

	std::string str("abcabc");
	std::match_results<std::string::const_iterator> mr2;
	std::cout << "search(string, \"abc\") == " << std::boolalpha
		<< regex_search(str, mr2, rx) << std::endl;
	std::cout << "  matched: \"" << mr2.str() << "\"" << std::endl;

	//**********************************************

	std::string s1("{1,2,3}{4,5,6}{7,8,9}");
	std::regex e(R"~((\d+),(\d+),(\d+))~");

	std::cout << s1 << std::endl;

	std::sregex_iterator iter(s1.begin(), s1.end(), e);
	std::sregex_iterator end;

	while (iter != end)
	{
		std::cout << "size: " << iter->size() << std::endl;

		std::cout << "expression match #" << 0 << ": " << (*iter)[0] << std::endl;
		for (unsigned i = 1; i < iter->size(); ++i)
		{
			std::cout << "capture submatch #" << i << ": " << (*iter)[i] << std::endl;
		}
		++iter;
	}

	//*****************************************************

	std::string lines[] = { "Roses are #ff0000",
						   "violets are #0000ff",
						   "all of my base are belong to you" };

	std::regex color_regex("#([a-f0-9]{2})"
		"([a-f0-9]{2})"
		"([a-f0-9]{2})");

	// simple match
	for (const auto& line : lines) {
		std::cout << line << ": " << std::boolalpha
			<< std::regex_search(line, color_regex) << '\n';
	}
	std::cout << '\n';

	// show contents of marked subexpressions within each match
	std::smatch color_match;
	for (const auto& line : lines) {
		if (std::regex_search(line, color_match, color_regex)) {
			std::cout << "matches for '" << line << "'\n";
			std::cout << "Prefix: '" << color_match.prefix() << "'\n";
			for (size_t i = 0; i < color_match.size(); ++i)
				std::cout << i << ": " << color_match[i] << '\n';
			std::cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
		}
	}

	// repeated search (see also std::regex_iterator)
	std::string log(R"(
        Speed:	366
        Mass:	35
        Speed:	378
        Mass:	32
        Speed:	400
	Mass:	30)");
	std::regex r(R"(Speed:\t\d?)");
	std::smatch sm;
	std::cout << " RRRRRRRRRRRRR '" << "\'\n\n";
	while (regex_search(log, sm, r))
	{
		std::cout << sm.str() << '\n';
		log = sm.suffix();
	}

	// C-style string demo
	std::cmatch cm;
	if (std::regex_search("this is a test", cm, std::regex("test")))
		std::cout << "\nFound " << cm[0] << " at position " << cm.prefix().length();

	//*********************************************

}

void ex2()
{

	const std::string s = "Quick brown fox.";

	std::regex words_regex("[^\\s]+");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	std::cout << "Found "
		<< std::distance(words_begin, words_end)
		<< " words:\n";

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		std::cout << match_str << '\n';
	}

	//*********************************************


}

void ex3()
{
	std::string s("this subject has a submarine as a subsequence");
	std::smatch m;
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (std::regex_search(s, m, e)) {
		for (auto x : m) std::cout << x << " ";
		std::cout << std::endl;
		s = m.suffix().str();
	}

	//*******************************************

}

void ex4()
{
	const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
	const regex r(R"((\w+):(\w+);)");
	smatch m;

	if (regex_search(input, m, r)) {
		assert(m.size() == 3);
		assert(m[0].str() == "PQR:2;");                // Entire match
		assert(m[1].str() == "PQR");                   // Substring that matches 1st group
		assert(m[2].str() == "2");                     // Substring that matches 2nd group
		assert(m.prefix().str() == "ABC:1->   ");      // All before 1st character match
		assert(m.suffix().str() == ";;   XYZ:3<<<");   // All after last character match

		// for (string &&str : m) { // Alternatively. You can also do
		//     cout << str << endl;
		// }
	}
}

void ex5()
{
	/*char str[1000];
	regex_t pr;
	int err = regcomp(&pr, ".*ß[à-å]*[1-9].*", REG_EXTENDED | REG_ICASE);
	if (err) {
		regerror(err, &pr, str, 100);
		puts(str);
		exit(1);
	}

	while (fputs("enter: ", stderr), fgets(str, 1000, stdin)) {
		printf("match = %d\n", regexec(&pr, str, 0, 0, 0));
	}*/

	//************************

	string string1 = "qqqsqq=sqqqq;";
	//enum states state = s1;

	regex statement("[a-zA-Z]+[=][a-zA-Z0-9]+[;]");
	regex rg_left_letter("[a-zA-Z]");
	regex rg_equal("[=]");
	regex rg_right_letter("[a-zA-Z0-9]");
	regex rg_semicolon("[;]");

	//for (const auto &s : string1) {

	for (int i = 0; i < string1.size(); i++) {
		cout << "Current Value: " << string1[i] << endl;
		// step(&state, s);
		if (regex_match(string1.substr(i, 1), rg_left_letter)) {
			cout << "matching: " << string1[i] << endl;
		}
		else {
			cout << "not matching: " << string1[i] << endl;
		}

		// cout << "Step Executed with sate: " << state << endl;
	}
	cout << endl;

}

void ex6()
{
	//const std::string target_path("/my/directory/");
	//const boost::regex my_filter("somefiles.*\.txt");

	//std::vector< std::string > all_matching_files;

	//boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
	//for (boost::filesystem::directory_iterator i(target_path); i != end_itr; ++i)
	//{
	//	// Skip if not a file
	//	if (!boost::filesystem::is_regular_file(i->status())) continue;

	//	boost::smatch what;

	//	// Skip if no match for V2:
	//	if (!boost::regex_match(i->leaf(), what, my_filter)) continue;
	//	// For V3:
	//	//if( !boost::regex_match( i->path().filename().string(), what, my_filter ) ) continue;

	//	// File matches, store it
	//	all_matching_files.push_back(i->leaf());
	//}
}