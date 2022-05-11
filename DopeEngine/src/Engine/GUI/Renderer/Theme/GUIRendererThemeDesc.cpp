#include "GUIRendererThemeDesc.h"

namespace DopeEngine
{
	GUIRendererThemeDesc::GUIRendererThemeDesc()
	{
        Alpha = 1.0f;            
        DisabledAlpha = 0.60f;           
        WindowPadding = { 8,8 };     
        WindowRounding = 0.0f;             
        WindowBorderSize = 1.0f;
        WindowMinSize = { 32,32 };   
        WindowTitleAlign = { 0.0f, 0.5f };
        //WindowMenuButtonPosition = ImGuiDir_Left;
        ChildRounding = 0.0f;
        ChildBorderSize = 1.0f;
        PopupRounding = 0.0f;
        PopupBorderSize = 1.0f;
        FramePadding = {4,3};
        FrameRounding = 0.0f;
        FrameBorderSize = 0.0f;
        ItemSpacing = { 8,4 };
        ItemInnerSpacing = { 4,4 };
        CellPadding = {4,2};
        TouchExtraPadding = {0,0};
        IndentSpacing = 21.0f; 
        ColumnsMinSpacing = 6.0f;
        ScrollbarSize = 14.0f;   
        ScrollbarRounding = 9.0f; 
        GrabMinSize = 10.0f;  
        GrabRounding = 0.0f;    
        LogSliderDeadzone = 4.0f;    
        TabRounding = 4.0f;         
        TabBorderSize = 0.0f;         
        TabMinWidthForCloseButton = 0.0f;    
      //  ColorButtonPosition = ImGuiDir_Right;  
        ButtonTextAlign = { 0.5f, 0.5f };
        SelectableTextAlign = {0,0};
        DisplayWindowPadding = {19,19};   
        DisplaySafeAreaPadding = { 3,3 };   
        MouseCursorScale = 1.0f;            
        EnableAntiAliasedLines = true;           
        EnableAntiAliasedLinesUseTex = true;          
        EnableAntiAliasedFill = true;            
        CurveTessellationTol = 1.25f;           
        CircleTessellationMaxError = 0.30f;

        /*
        * Set colors
        */
        TextColor = { 0.90f, 0.90f, 0.90f, 1.00f };
        TextDisabledColor = {0.60f, 0.60f, 0.60f, 1.00f};
        WindowBackgroundColor = {0.00f, 0.00f, 0.00f, 0.85f};
        ChildBackgroundColor = {0.00f, 0.00f, 0.00f, 0.00f};
        PopupBackgroundColor = {0.11f, 0.11f, 0.14f, 0.92f};
        BorderColor = {0.50f, 0.50f, 0.50f, 0.50f};
        BorderShadowColor = {0.00f, 0.00f, 0.00f, 0.00f};
        FrameBackgroundColor = {0.43f, 0.43f, 0.43f, 0.39f};
        FrameBackgroundHovoredColor = {0.47f, 0.47f, 0.69f, 0.40f};
        FrameBackgroundActiveColor = {0.42f, 0.41f, 0.64f, 0.69f};
        TitleBackgroundColor = {0.27f, 0.27f, 0.54f, 0.83f};
        TitleBackgroundActiveColor = {0.32f, 0.32f, 0.63f, 0.87f};
        TitleBackgroundCollapsedColor = {0.40f, 0.40f, 0.80f, 0.20f};
        MenuBarBackgroundColor = {0.40f, 0.40f, 0.55f, 0.80f};
        ScrollbarBackgroundColor = {0.20f, 0.25f, 0.30f, 0.60f};
        ScrollbarGrabColor = {0.40f, 0.40f, 0.80f, 0.30f};
        ScrollbarHovoredColor = {0.40f, 0.40f, 0.80f, 0.40f};
        ScrollbarGrabActiveColor = {0.41f, 0.39f, 0.80f, 0.60f};
        CheckMarkColor = {0.90f, 0.90f, 0.90f, 0.50f};
        SliderGrabColor = {1.00f, 1.00f, 1.00f, 0.30f};
        SliderGrabActiveColor = {0.41f, 0.39f, 0.80f, 0.60f};
        ButtonColor = {0.35f, 0.40f, 0.61f, 0.62f};
        ButtonHoveredColor = {0.40f, 0.48f, 0.71f, 0.79f};
        ButtonActiveColor = {0.46f, 0.54f, 0.80f, 1.00f};
        HeaderColor = {0.40f, 0.40f, 0.90f, 0.45f};
        HeaderHoveredColor = {0.45f, 0.45f, 0.90f, 0.80f};
        HeaderActiveColor = {0.53f, 0.53f, 0.87f, 0.80f};
        SeparatorColor = {0.50f, 0.50f, 0.50f, 0.60f};
        SeparatorHoveredColor = {0.60f, 0.60f, 0.70f, 1.00f};
        SeparatorActiveColor = {0.70f, 0.70f, 0.90f, 1.00f};
        ResizeGripColor = {1.00f, 1.00f, 1.00f, 0.10f};
        ResizeGripHoveredColor = {0.78f, 0.82f, 1.00f, 0.60f};
        ResizeGripActiveColor = {0.78f, 0.82f, 1.00f, 0.90f};
        //colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f};
        TabHoveredColor = HeaderHoveredColor;
       // colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f};
       // colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f};
        //colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f};
        DockingPreviewColor = HeaderColor * ColorRgbaFloat(1.0f, 1.0f, 1.0f, 0.7f);
        DockingEmptyBackgroundColor = {0.20f, 0.20f, 0.20f, 1.00f};
        PlotLinesColor = {1.00f, 1.00f, 1.00f, 1.00f};
        PlotLinesHoveredColor = {0.90f, 0.70f, 0.00f, 1.00f};
        PlotHistogramColor = {0.90f, 0.70f, 0.00f, 1.00f};
        PlotHistogramHoveredColor = {1.00f, 0.60f, 0.00f, 1.00f};
        TableHeaderBackgroundColor = {0.27f, 0.27f, 0.38f, 1.00f};
        TableBorderStrongColor = {0.31f, 0.31f, 0.45f, 1.00f};   // Prefer using Alpha=1.0 here
        TableBorderLightColor = {0.26f, 0.26f, 0.28f, 1.00f};   // Prefer using Alpha=1.0 here
        TablewRowBackgroundColor = {0.00f, 0.00f, 0.00f, 0.00f};
        TableRowBackgroundAltColor = {1.00f, 1.00f, 1.00f, 0.07f};
        TextSelectedBackgroundColor = {0.00f, 0.00f, 1.00f, 0.35f};
        DragDropTargetColor = {1.00f, 1.00f, 0.00f, 0.90f};
        NavigationHighlightColor =HeaderHoveredColor;
        NavigationWindowingHightlightColor = {1.00f, 1.00f, 1.00f, 0.70f};
        NavigationWindowingDimBackgroundColor = {0.80f, 0.80f, 0.80f, 0.20f};
        ModalWindowDimBackgroundColor = {0.20f, 0.20f, 0.20f, 0.35f};
	}

}