// https://leetcode.com/problems/expression-add-operators/
// We use a naive solution. Generate all possible expressions, then evaluate
// these expressions to see whether the result equals target.
// How to generate all expressions: we could insert "", "+", "-", "*" between two characters

class Solution {
    typedef long long ll;
	static ll ConvertNumber(const char* exp, char** exp_end) {
		ll acc = strtoll(exp, exp_end, 10);
		if (errno == ERANGE) {
			throw std::out_of_range(exp);
		}
		return acc;
	}
    static ll Eval(const char* exp) {
		char* end;
		ll acc = ConvertNumber(exp, &end);
        for (; *end != '\0';) {
			exp = end;
            char op = *exp;
            if (op == '+') {
				ll n = ConvertNumber(exp+1, &end);
				// since * has a higher precedence over + and -, we must 
				// look ahead one character to decide the evaluation order.
				while (*end == '*') {
					exp = end;
					ll t = ConvertNumber(exp+1, &end);
					n *= t; // we should also test overflow here if we are careful;)
				}
                acc += n;
            } else if (op == '-') {
                ll n = ConvertNumber(exp+1, &end);
                while (*end == '*') {
					exp = end;
					ll t = ConvertNumber(exp+1, &end);
					n *= t;
				}
                acc -= n;
            } else {
				ll n = ConvertNumber(exp+1, &end);
                acc *= n;
            }
        }
        return acc;
    }
    
    // k: the position we are going to generate operator
    static void GenerateExpAndEval(const string& num, int target, size_t k, string* exp, vector<string>* result) {
        if (num.size() == k) {
			// It's strange that if I don't comment out the catch clause,
			// I will get wrong with test case "2147483648", -2147483648.
			//try {
				ll r = Eval(exp->c_str());
				if (r == target) {
					result->push_back(*exp);
				}
			//} catch (const std::out_of_range&) {
			//}
            return;
        }
        size_t n = exp->size();
        if (exp->back() != '0' || (n > 1 && isdigit((*exp)[n-2]))) {
    		exp->push_back(num[k]);
    		GenerateExpAndEval(num, target, k+1, exp, result);
    		exp->pop_back();
        }

        const char ops[] = {'+', '-', '*'};
        for (auto op: ops) {
			exp->push_back(op);
			exp->push_back(num[k]);
            GenerateExpAndEval(num, target, k+1, exp, result);
			exp->pop_back();
			exp->pop_back();
        }
    }
public:
    vector<string> addOperators(string num, int target) {
        size_t n = num.size();
        vector<string> result;
        if (n == 0) {
			return result;
		}
        string exp(1, num[0]);
        GenerateExpAndEval(num, target, 1u, &exp, &result);
		return result;
    }
};