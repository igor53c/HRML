#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Att {
	string name;
	string value;
};

struct Tag {
	string name;
	vector<Att> attributes;
	vector<string> contain;
};

string replaceAll(string, string, string);

bool containString(vector<string>, string);

Tag getTag(vector<Tag>, string);

Att getAtt(vector<Att>, string);

int main()
{
	int n, q;

	cin >> n;
	cin >> q;

	vector<Tag> tags;

	cin.ignore();

	for (int i = 0; i < n; i++)
	{
		string line;

		getline(cin, line);

		if (line[1] != '/')
		{
			Tag temp;

			int ind = line.find(' ');

			if (ind == string::npos)
			{
				ind = line.find('>');

				temp.name = line.substr(1, ind - 1);
			}
			else
			{
				temp.name = line.substr(1, ind - 1);

				string otherString = line.substr(ind + 1);

				while (true)
				{
					int ind2 = otherString.find('=');

					if (ind2 == string::npos)
						break;

					Att tempAtt;

					string attr = otherString.substr(0, ind2 - 1);

					otherString = otherString.substr(ind2 + 1);

					attr = replaceAll(attr, " ", "");

					tempAtt.name = attr;

					ind = otherString.find('"');

					otherString = otherString.substr(ind + 1);

					ind2 = otherString.find('"');

					tempAtt.value = otherString.substr(0, ind2);

					temp.attributes.push_back(tempAtt);

					otherString = otherString.substr(ind2 + 1);
				}
			}

			tags.push_back(temp);
		}
		else
		{
			int ind = line.find('>');
			string name = line.substr(2, ind - 2);

			for (int i = tags.size() - 1; i >= 0; i--)
			{
				if (tags[i].name == name)
				{
					tags[i].contain.push_back("null");

					string root;

					for (int j = i - 1; j >= 0; j--)
					{
						if (tags[j].name != name && !containString(tags[j].contain, "null"))
						{
							root = tags[j].name + "." + root;
						}
					}

					tags[i].contain.push_back(root);
				}
			}
		}
	}

	for (int i = 0; i < q; i++)
	{
		string line, root;

		getline(cin, line);

		Tag tag1, alt;

		int ind;

		while (true)
		{
			int ind2 = line.find('.');

			if (ind2 == string::npos)
			{
				break;
			}

			root += line.substr(0, ind2 + 1);

			line = line.substr(ind2 + 1);

			ind = ind2;
		}

		ind = line.find('~');

		tag1 = getTag(tags, line.substr(0, ind));

		Att newAtt = getAtt(tag1.attributes, line.substr(ind + 1));

		if (containString(tag1.contain, root))
		{
			if (!newAtt.name.empty())
				cout << newAtt.value << endl;
			else
				cout << "Not Found!" << endl;
		}
		else
			cout << "Not Found!" << endl;
	}

	return EXIT_SUCCESS;
}

string replaceAll(string s, string old, string replace)
{

	size_t position = 0;

	do
	{
		position = s.find(old, position);

		if (position != string::npos)
		{
			s.replace(position, old.length(), replace);
			position += replace.length();
		}
	} while (position != string::npos);

	return s;
}

bool containString(vector<string> s, string ss)
{
	for (const auto& a : s)
	{
		if (ss == a)
			return true;
	}

	return false;
}

Tag getTag(vector<Tag> tags, string s)
{
	Tag retValue;

	for (auto tag : tags)
	{
		if (tag.name == s)
			return tag;
	}

	return retValue;
}

Att getAtt(vector<Att> atts, string s)
{
	Att retValue;

	for (auto att : atts)
	{
		if (att.name == s)
			return att;
	}

	return retValue;
}