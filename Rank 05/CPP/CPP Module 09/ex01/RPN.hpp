#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

class RPN
{
	private:
		std::stack<double> _stack;
		
		RPN(RPN const &src);
		RPN &operator=(RPN const &rhs);
		
		bool	isOperator(char c) const;
		bool	isDigit(char c) const;
		double	performOperation(double a, double b, char op);

	public:
		RPN(void);
		~RPN(void);
		
		void	calculate(std::string const &expression);
};

#endif
