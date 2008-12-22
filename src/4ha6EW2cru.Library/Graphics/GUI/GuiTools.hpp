#ifndef __GUITOOLS_H
#define __GUITOOLS_H


class GuiTools
{

public:

	/*! Casts a Widget to a Window */
	static MyGUI::Window* FromLua_ToWindow( MyGUI::Widget* widget )
	{
		return static_cast< MyGUI::Window* >( widget );
	};

	/*! Casts a Widget to a Window */
	static MyGUI::StaticTextPtr FromLua_ToStaticText( MyGUI::WidgetPtr widget )
	{
		return ( MyGUI::StaticTextPtr ) widget;
	};

	/*! Casts a Widget to a Button */
	static MyGUI::ButtonPtr FromLua_ToButton( MyGUI::WidgetPtr widget )
	{
		return static_cast< MyGUI::ButtonPtr >( widget );
	};

};

#endif