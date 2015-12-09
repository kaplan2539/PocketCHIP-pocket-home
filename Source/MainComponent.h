#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "LauncherBarComponent.h"
#include "SettingsPageComponent.h"
#include "AppsPageComponent.h"
#include "SwitchComponent.h"

class MainContentComponent : public Component, private Button::Listener {
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)

public:
  ScopedPointer<LauncherBarComponent> categoryButtons;

  OwnedArray<Component> pages;
  HashMap<String, Component *> pagesByName;

  StretchableLayoutManager categoryButtonLayout;

  ScopedPointer<LookAndFeel> lookAndFeel;
  ScopedPointer<TextButton> closeButton;

  MainContentComponent();
  ~MainContentComponent();

  void paint(Graphics &) override;
  void resized() override;

private:
  void buttonClicked(Button *) override;
};
