class _ATextBox :
	public _AButton
{
protected:
	string m_strFormatted;
	int m_nLeftBuffer;
	int m_nRightBuffer;
	bool m_bEditable;

	void constructBase()
	{
		set(m_strFormatted, 1, 0, m_nFGColor + m_nBGColor);

		if (m_bEditable)
			switch (m_nState)
			{
			case DEFAULT:
				setFGColor(FG_DARKGREY);
				setBGColor(BG_BLACK);
				break;
			case MOUSE_OVER:
				setFGColor(FG_DARKGREY);
				setBGColor(BG_BLACK);
				if (m_bMouseOver)
					drawThinBorder(m_nBGColor + FG_LIGHTGREY);

				break;
			case LEFT_PRESSED:
				setFGColor(FG_WHITE);
				setBGColor(BG_BLACK);
				break;
			case LEFT_RELEASED:
				setFGColor(FG_DARKGREY);
				setBGColor(BG_BLACK);
				drawThinBorder(m_nBGColor + FG_WHITE);
				break;
			}
	}

	bool isWordBreakChar(char chChar)
	{
		string strWordBreaks = " ,.:;'";
		for (int nI = 0; nI < strWordBreaks.size(); nI++)
			if (strWordBreaks[nI] == chChar)
				return true;
		return false;
	}

	string getNextChunk(string strText, int nPos)
	{
		string strChunk = "";
		while (nPos < strText.size())
		{
			strChunk += strText[nPos];
			if (isWordBreakChar(strText[nPos]))
				return strChunk;
			if (isWordBreakChar(strText[nPos + 1]))
				return strChunk;
			nPos++;
		}
		return strChunk;
	}

	string Indent(int nIndent)
	{
		string strIndent = "";
		for (int nI = 0; nI < nIndent; nI++)
			strIndent += ' ';
		return strIndent;
	}

	string formatText(string strText)
	{
		int left_buffer = 2;
		int right_buffer = 2;
		int total_width = Size.X;
		int usable_width = total_width - left_buffer - right_buffer;
		int usable_width_left = usable_width;
		int nPos = 0;

		string strFormatted = "";

		strFormatted.append(Indent(left_buffer));
		while (nPos < strText.size())
		{
			string chunk = getNextChunk(strText, nPos);
			if (usable_width_left >= chunk.size())
			{
				strFormatted.append(chunk);
				usable_width_left -= chunk.size();
			}
			else
			{
				strFormatted.append(Indent(usable_width_left));
				strFormatted.append(Indent(right_buffer));
				strFormatted.append(Indent(left_buffer));
				usable_width_left = usable_width;
				strFormatted.append(chunk);
				usable_width_left -= chunk.size();
			}
			nPos += chunk.size();
		}
		return strFormatted;
	}

	void onEvent(_Event *pEvent)
	{
		_AButton::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
		case CONSOLE_MOUSE_EVENT:
		{
			if (m_nState == LEFT_RELEASED		//	if state = selected/active
				&& !m_bMouseOver				//	!mouse_over && mouse click
				&& pEvent->get<MouseEvent>()->getState().bLeftButtonDown)
				setState(DEFAULT);
			break;
		}

		case CONSOLE_KEYBOARD_EVENT:
		{
			if (m_bActive && m_bEditable)
			{
				if (pEvent->get<KeyboardEvent>()->isKeyDown())
				{
					char chKey = pEvent->get<KeyboardEvent>()->getKey();
					switch (chKey)
					{
					case 8:	//	backspace
						if (m_strText.size() > 2);
						{
							m_strText.erase(m_strText.begin() + (m_strText.size() - 1));
							m_strFormatted = formatText(m_strText);
						}
						break;
						//	case "enter"
						//	case "tab"
						//	handle punctuation bugs
					default:
						m_strText = m_strText + chKey;
						m_strFormatted = formatText(m_strText);
						break;
					}

				}
			}
			break;
		}
		}
	}

public:
	_ATextBox(int nWidth, int nHeight, int nPosX, int nPosY) :
		m_strFormatted(""),
		m_bEditable(false),
		_AButton(nWidth, nHeight, nPosX, nPosY)
	{
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, CONSOLE_MOUSE_EVENT);
	};

	void setEditable(bool bEditable)
	{
		m_bEditable = bEditable;
	}

	void scroll()
	{
		int nHeightFormatted = m_strFormatted.size() / Size.X;
		float scrollPercent = getComponent<_AScrollBar>()->getScrollPosition();
		float textScrollPercent = scrollPercent * nHeightFormatted;
		int Start = textScrollPercent * Size.X;
		string scrolled = m_strText.substr(Start);
		m_strFormatted = formatText(scrolled);
	}

	void setText(string strText)
	{
		m_strText = strText;
		m_strFormatted = formatText(strText);
	}

};

