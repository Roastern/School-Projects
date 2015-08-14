using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calculator
{
    public partial class Calculator : Form
    {
        //Constant strings for default text and error messages
        const string DEFAULT_TEXT = "0.";
        const string ERROR_MSG = "Cannot compute";

        //Stores whether or not the user has entered any numbers
        bool UNSET = true;

        //Stores whether or not the user wants number grouping
        bool NUMBER_GROUP = false;
        
        //String that will be used to store values into memor
        string _memory = DEFAULT_TEXT;

        //String that will be used to store text when the user presses copy
        string _copy = null;

        //The string that the user is inputting
        string _currentText = DEFAULT_TEXT;

        //The expression last entered by the user, or any notification
        string _previousText = "";

        //An instance of the math parser used to calculate expressions
        MathParserTK.MathParser parser = new MathParserTK.MathParser();

        /// <summary>
        /// Default constructor
        /// Does stuff
        /// </summary>
        public Calculator()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Calculates the given expression using the math parser. 
        /// </summary>
        /// <param name="expression">The expression that needs to be evaulated</param>
        /// <returns></returns>
        private string Calculate(string expression)
        {
            //Stores the result returned by the math parser
            double result = 0.0;
   
            //First attempts to remove any commas from number grouping
            //then passes the cleaned string to the math parser
            try
            {
                expression = RemoveNumericalGroupings(expression);
                result = parser.Parse(expression);
            }
            //If the math parser could not calculate the expression, returns the error message
            catch (Exception e)
            {
                UNSET = true;
                return (ERROR_MSG);
            }

            //If the user wants number grouping, sends the result to the number grouping
            //function and returns it
            if (NUMBER_GROUP)
            {
                return InsertNumericalGroupings(Convert.ToString(result));
            }
            //No number grouping required, returns result as is
            else
                return Convert.ToString(result);
        }

        /// <summary>
        /// Adds number groupings to the given expression string
        /// </summary>
        /// <param name="converted">The expression string which requires grouping</param>
        /// <returns>The passed in string with added number grouping</returns>
        private string InsertNumericalGroupings(string converted)
        {
            //Stores the updated string
            string newCurr = "";

            //Stores the current number that needs grouping
            string currNum = "";

            //Used to store math operators so that they're not lost during parsing
            char lastOp = ' ';

            //Used to store the number that needs grouping as a decimal
            decimal num;

            //Evaluates each character in the string
            //If the character is not a math operator, it adds it to currNum
            //When a math operator is found, it converts currNum to a decimal and stores it in num, then converts num back to a string with correct formatting
            //Finally appends currNum and lastOp to newCurr
            foreach (char c in converted)
            {
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '%')
                {
                    //Try statement is for catching events such as the string being the ERROR_MSG
                    //where there is no number to convert.
                    //If that's the case, returns the string as is
                    try
                    {
                        lastOp = c;
                        num = Convert.ToDecimal(currNum);
                        currNum = num.ToString("#,#.#############################");
                        newCurr += currNum + lastOp;
                        currNum = "";
                    }
                    catch
                    {
                        return converted;
                    }
                }
                else
                    currNum += c;
            }

            //Same reason for try as above
            //However this correctly formats the last number in the passed in string to decimal
            //and appends it to newCurr
            try
            {
                num = Convert.ToDecimal(currNum);
                currNum = num.ToString("#,#.#############################");
                newCurr += currNum;
            }
            catch
            {
                return newCurr + currNum;
            }

            //If newCurr had no numbers in it
            //Sets it back to the default text
            if (newCurr == "")
                newCurr = DEFAULT_TEXT;

            return newCurr;
        }

        /// <summary>
        /// Removes numerical groupings from the given expression string
        /// </summary>
        /// <param name="converted">The expression string to have numerical groupings removed</param>
        /// <returns>The formatted expression string</returns>
        private string RemoveNumericalGroupings(string converted)
        {
            //This function is the same as above, other than the way it converts the decimal back to string
            //Comments omitted as they would be extremely repetitive
            string newCurr = "";
            string currNum = "";
            char lastOp = ' ';
            decimal num;

            foreach (char c in converted)
            {
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '%')
                {
                    try
                    {
                        lastOp = c;
                        num = Convert.ToDecimal(currNum);
                        currNum = num.ToString();
                        newCurr += currNum + " " + lastOp + " ";
                        currNum = "";
                    }
                    catch
                    {
                        return converted;
                    }
                }
                else
                    currNum += c;
            }

            try
            {
                num = Convert.ToDecimal(currNum);
                currNum = num.ToString();
                newCurr += currNum;
            }
            catch
            {
                return newCurr + currNum;
            }

            if (newCurr == "")
                newCurr = DEFAULT_TEXT;

            return newCurr;
        }

        /// <summary>
        /// Sets the _currentText string to the passed in values, while adding/removing formatting
        /// and taking into account the UNSET variable
        /// </summary>
        /// <param name="original">The text to appear first</param>
        /// <param name="append">The text to be appended to original</param>
        private void SetCurrText(string original, string append)
        {
            //If the append text is an error message
            if (append == ERROR_MSG)
            {
                //Flags UNSET as true so any input will erase the error message
                UNSET = true;

                //Clears out the previous text and sets current text to the error message
                _previousText = "";
                _currentText = append;
            }
            //If the append text is not an error message
            else
            {
                //If UNSET is true, ignore the original, only the append text will
                //be displayed in the textbox
                if (UNSET)
                {
                    _currentText = append;
                }
                //If UNSET is not true, set the string to be shown in the text box
                //to be the original + append
                else
                {
                    _currentText = original + append;
                }
            }
            
            //If number grouping is selected, format the text and output in the textbox
            if (NUMBER_GROUP)
            {
                txtInput.Clear();
                txtInput.Text = InsertNumericalGroupings(_previousText) + Environment.NewLine;
                txtInput.Text += InsertNumericalGroupings(_currentText);
            }
            //Otherwise remove the formatting and output in the textbox
            else
            {
                txtInput.Clear();

                if (_previousText != "")
                    txtInput.Text = RemoveNumericalGroupings(_previousText) + Environment.NewLine;
                else
                    txtInput.Text = _previousText + Environment.NewLine;

                //Ensures that if the default text is what is going to be displayed in the textbox,
                //that it displays correctly
                if (_currentText != DEFAULT_TEXT)
                    txtInput.Text += RemoveNumericalGroupings(_currentText);
                else
                {
                    UNSET = true;
                    txtInput.Text += _currentText;
                } 
            }

            //Returns the focus to the equals button, so that no matter what when enter is pressed
            //on the keyboard, the btnEqual_OnClick() event is called
            btnEquals.Focus();
        }

        /// <summary>
        /// Processes key input, either from buttons or keyboard
        /// </summary>
        /// <param name="key">The key that was pressed</param>
        private void ProcessKey(string key)
        {
            if (key != "")
            {
                //If UNSET is true, sets the current text to be just the input key value
                if (UNSET)
                {
                    SetCurrText("", key);

                    //Sets UNSET to false so the next key input wont erase the first
                    UNSET = false;
                }
                //Otherwise, calls SetCurrText passing in the text stored in the textbox plus the new key value
                else
                {
                    SetCurrText(_currentText, key);
                }
            }
        }

        /// <summary>
        /// Processes keyboard key presses
        /// </summary>
        private void Calculator_KeyPress(object sender, KeyPressEventArgs e)
        {
            //If the key is a backspace or delete
            if (e.KeyChar == (char)Keys.Back || e.KeyChar == (char)Keys.Delete)
            {
                e.Handled = true;

                //Calls the btnBackSpace_Click event
                btnBackSpace_Click(sender, e);
            }
            //Otherwise, ensures that the key is valid and makes a call to ProcessKey()
            else
            {
                //Used to store the input key value
                string temp;

                switch (e.KeyChar.ToString())
                {
                    case "1":
                        temp = "1";
                        break;
                    case "2":
                        temp = "2";
                        break;
                    case "3":
                        temp = "3";
                        break;
                    case "4":
                        temp = "4";
                        break;
                    case "5":
                        temp = "5";
                        break;
                    case "6":
                        temp = "6";
                        break;
                    case "7":
                        temp = "7";
                        break;
                    case "8":
                        temp = "8";
                        break;
                    case "9":
                        temp = "9";
                        break;
                    case "0":
                        temp = "0";
                        break;
                    case "/":
                        temp = "/";
                        break;
                    case "*":
                        temp = "*";
                        break;
                    case "-":
                        temp = "-";
                        break;
                    case "+":
                        temp = "+";
                        break;
                    case ".":
                        temp = ".";
                        break;
                    case "(":
                        temp = "(";
                        break;
                    case ")":
                        temp = ")";
                        break;
                    case "^":
                        temp = "^";
                        break;
                    default:
                        temp = "";
                        break;
                }

                e.Handled = true;

                //Adds the valid key value, or an empty string to the ProcessKey() function
                ProcessKey(temp);
            }
        }

        /// <summary>
        /// Event for all buttons that don't perform a calculation or store values to/from memory
        /// </summary>
        private void OnNumber_Click(object sender, EventArgs e)
        {
            //Stores the passed in EventArgs as a button
            Button butt = (Button)sender;

            //Passes the text stored in the button to the ProcessKey() function
            ProcessKey(butt.Text.ToString());
        }

        /// <summary>
        /// Sets previous text to the current text and calls the Calculate() function, passing in the current text
        /// </summary>
        private void btnEquals_Click(object sender, EventArgs e)
        {
            _previousText = _currentText;
            _currentText = Calculate(_currentText);

            //Sets UNSET to true so any new input will replace the given result
            UNSET = true;

            //Calls SetCurrText(), passing in the result provided by Calculate()
            SetCurrText("", _currentText);
        }

        /// <summary>
        /// Resets current text to the default values
        /// </summary>
        private void btnC_Click(object sender, EventArgs e)
        {
            //Sets UNSET to true so any new input will replace the given result
            UNSET = true;

            //Sets current text to the default text
            SetCurrText("", DEFAULT_TEXT);
        }

        /// <summary>
        /// Resets both current text and previous text to default values
        /// </summary>
        private void btnCE_Click(object sender, EventArgs e)
        {
            //Sets UNSET to true so any new input will replace the given result
            UNSET = true;

            //Sets previous text and current text to default values
            _previousText = "";
            SetCurrText("", DEFAULT_TEXT);
        }

        /// <summary>
        /// Handles the backspace/delete events
        /// </summary>
        private void btnBackSpace_Click(object sender, EventArgs e)
        {
            //If UNSET is false, or the current text is not the default text
            //(this makes it so that the user cannot deleted the default 0)
            if (!UNSET || _currentText != DEFAULT_TEXT)
            {
                //So long as current text is not empty
                if (_currentText.Length > 0)
                {
                    //Current text is set to be the current text without the last character
                    _currentText = _currentText.Substring(0, _currentText.Length - 1);
                }

                //If the new string does not contain anything, stores the default text to it
                if (_currentText.Length == 0)
                {
                    _currentText = DEFAULT_TEXT;

                    //Sets UNSET to true so that future input will get ride of the default text
                    UNSET = true;
                }

                //Sets the current text
                SetCurrText("", _currentText);
            }
        }

        /// <summary>
        /// Handles the MC button click even
        /// </summary>
        private void btnMC_Click(object sender, EventArgs e)
        {
            //Displays the message in previous text
            _previousText = "Memory cleared";

            //Clears the value currently stored in memory by setting it to default text
            _memory = DEFAULT_TEXT;

            //Sets unset to true so that any future input will get rid of the default text
            UNSET = true;
            SetCurrText("", _memory);
        }

        /// <summary>
        /// Stores the value (retrieved by caluclating the expression) in current text into
        /// memory
        /// </summary>
        private void btnMS_Click(object sender, EventArgs e)
        {
            //Message displayed in previous text
            _previousText = "Stored to memory";

            //Calculates the expression currently in current text and stores the returned string to memory
            _currentText = RemoveNumericalGroupings(_currentText);
            _memory = Calculate(_currentText);

            //UNSET is set to true and the current text is set to default text
            UNSET = true;
            SetCurrText("", DEFAULT_TEXT);
        }

        /// <summary>
        /// Retrieves the stored value from memory and outputs it in current text
        /// </summary>
        private void btnMR_Click(object sender, EventArgs e)
        {
            //Message displayed in previous text
            _previousText = "Retrieved from memory";

            //If the default text is not what is stored in memory
            if (_memory != DEFAULT_TEXT)
            {
                //Sets current text to whatever is in memory
                UNSET = false;
                SetCurrText("", _memory);
            }
            //Otherwise, sets the current text to default text and UNSET to true
            else
            {
                UNSET = true;
                SetCurrText("", _memory);
            }
        }

        /// <summary>
        /// Adds whatever is in current text to the value stored in memory
        /// </summary>
        private void btnMPlus_Click(object sender, EventArgs e)
        {
            //Previous text shows the addition expression
            _previousText = _memory + " + " + _currentText;

            //Temp stores the expression used to perform the calculation
            //That is, memory + currentText
            string temp = Calculate(_memory + " + " + _currentText);
            
            //So long as the calculation did not result in errors
            if (temp != ERROR_MSG)
            {
                //Stores the new value to memory
                //Outputs value in current text to be displayed in the textbox
                _memory = temp;
                SetCurrText("", _memory);
            }
            //Otherwise
            else
            {
                //Don't change what is in memory, display error message
                SetCurrText("", temp);
            }
        }

        /// <summary>
        /// Subtracts the given value from the value stored in memory
        /// </summary>
        private void btnMSub_Click(object sender, EventArgs e)
        {
            //Sets previous text to reflect what is happening
            _previousText = _memory + " - " + _currentText;

            //Performs the calculation
            string temp = Calculate(_memory + "-" + _currentText);
            
            //So long as the result was not an error
            if (temp != ERROR_MSG)
            {
                //stores the result in memory and outputs to current text
                _memory = temp;
                SetCurrText("", _memory);
            }
            //Sets current text to the error message
            else
            {
                SetCurrText("", temp);
            } 
        }

        /// <summary>
        /// Gets the inverse of whatever is stored in current text
        /// </summary>
        private void btnDivByX_Click(object sender, EventArgs e)
        {
            UNSET = false;

            //Sets previous text to reflect what is happening
            _previousText = "1 / (" + _currentText + ")";

            //Performs the calculation
            string temp = Calculate("1/" + _currentText);
            SetCurrText("", temp);
        }

        /// <summary>
        /// Performs the calucaltion of whatever is in current text and then multiplies the result by -1
        /// </summary>
        private void btnPlusMinus_Click(object sender, EventArgs e)
        {
            UNSET = false;

            //Sets previous text to reflect what is happening
            _previousText = "-1 * (" + _currentText + ")";

            //Performs the calculation
            string temp = Calculate(_currentText);

            //So long as the calculation did not result in error
            if (temp != ERROR_MSG)
            {
                //Multiplies result by -1
                temp = (-1 * Convert.ToDouble(temp)).ToString();
            }

            SetCurrText("", temp);
        }

        /// <summary>
        /// Performs the sqrt function
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSqrt_Click(object sender, EventArgs e)
        {
            //Sets previous text to reflect what is happening
            _previousText = "sqrt(" + _currentText + ")";

            //Performs the calculation
            string temp = Calculate("sqrt(" + _currentText + ")");

            SetCurrText("", temp);
        }

        /// <summary>
        /// Performs the % button functionality as Windows calculator does, since the math 
        /// parser did not handle this operation
        /// </summary>
        private void btnMod_Click(object sender, EventArgs e)
        {
            //Stores the last math operator in current text
            char mathop = ' ';

            //Stores the position of the last math operator in current text
            int pos = 0;

            //Loops through every character in current text
            for (int i = 0; i < _currentText.Length; i++)
            {
                //Searches for a math operator. If one is found, stores it and it's position into correct variables
                if (_currentText[i] == '+' || _currentText[i] ==  '-' || _currentText[i] ==  '*' || _currentText[i] ==  '/')
                {
                    mathop = _currentText[i];
                    pos = i;
                }
            }

            //So long as an operator was found
            if (pos != 0)
            {
                //Stores the values left of the operator into evaluatedString
                string evaluatedString = _currentText.Substring(0, pos);

                //Stores the values right of the operator into percentageString
                string percentageString = "";
                for (int i = pos + 1; i < _currentText.Length; i++)
                {
                    percentageString += _currentText[i];
                }

                //Sets previous text to reflect what is taking place
                _previousText = "(" + evaluatedString + ")" + " " + mathop + " " + percentageString + "%";

                //Sets percentage string to be it's number divided by 100 (the percentage value)
                percentageString = "(" + percentageString + " / 100)";

                //Calculates the evaulatedString and stores the result
                evaluatedString = Calculate(evaluatedString);

                //Encloses evaluatedString with parenthesis to ensure the correct order of operations
                evaluatedString = "(" + evaluatedString + ")";

                //Performs the percentage operation and stores in current text
                _currentText = Calculate(evaluatedString + mathop + "(" + evaluatedString + " * " + percentageString + ")");

                UNSET = true;
                SetCurrText("", _currentText);
            }
            
        }

        /// <summary>
        /// Stores whatever is in current text to the copy string
        /// </summary>
        private void mnuCopy_Click(object sender, EventArgs e)
        {
            //Stores current text into copy string
            _copy = _currentText;

            //Message displayed in previous text
            _previousText = "Text copied";

            //UNSET is set to true and the default text is output into curernt text
            UNSET = true;
            SetCurrText("", DEFAULT_TEXT);
        }

        /// <summary>
        /// If any value is stored in the copy string, outputs it to current text
        /// </summary>
        private void mnuPaste_Click(object sender, EventArgs e)
        {
            //Message displayed in previous text
            _previousText = "Text pasted";
            UNSET = false;

            //Copy is output
            SetCurrText("", _copy);
        }

        /// <summary>
        /// Displays a message box when the about menu item is clicked
        /// </summary>
        private void mnuAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Calculator \n\nBy: Eric Magers\n\nString Parser used for calculations found at http://www.codeproject.com/Tips/381509/Math-Parser-NET-Csharp\n \nAvailable mathematical operations include +, -, /, *, ^, ( )\nIf you wish to perform an operation with negative number, put parenthesis around the negative number:\nex. 5 + (-5)", "About Calculator", MessageBoxButtons.OK);
        }

        /// <summary>
        /// Called when the user selects or deselcts the number grouping option
        /// Either inserts grouping or removed grouping from previous text and current text
        /// </summary>
        private void mnuNumGroup_Click(object sender, EventArgs e)
        {
            //If NUMBER_GROUP is currently true, set to false. If it's false, set to true
            if (NUMBER_GROUP)
                NUMBER_GROUP = false;
            else
                NUMBER_GROUP = true;

            //Calls SetCurrText() to reprint previous and current texts with the chosen formatting
            SetCurrText("", _currentText);
        }
    }
}
