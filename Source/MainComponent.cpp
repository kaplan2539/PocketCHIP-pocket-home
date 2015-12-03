#include "MainComponent.h"

static const int categoryButtonHeight = 50;
static const int categoryPadding = 10;

static ScopedPointer<DrawableButton> createCategoryButton(const std::string name,
                                                          const char* svgData,
                                                          const char* svgDataSel) {
  ScopedPointer<DrawableButton> button;
  ScopedPointer<Drawable> icon, iconSel;
  ScopedPointer<XmlElement> iconSvg (XmlDocument::parse (svgData));
  ScopedPointer<XmlElement> iconSelSvg (XmlDocument::parse (svgDataSel));

  if (iconSvg != nullptr)
    icon = Drawable::createFromSVG (*iconSvg);

  if (iconSelSvg != nullptr)
    iconSel = Drawable::createFromSVG (*iconSelSvg);

  button = new DrawableButton (name, DrawableButton::ImageFitted);
  button->setImages(icon, 0, 0, 0, iconSel);
  button->setRadioGroupId(4444);
  button->setClickingTogglesState (true);
  button->setColour(DrawableButton::backgroundOnColourId, Colour(0xffffffff));

  return button;
};

MainContentComponent::MainContentComponent() {
  settingsPage = ScopedPointer<SettingsPageComponent>(new SettingsPageComponent());
  addAndMakeVisible(settingsPage.get());

  appButton = createCategoryButton("Apps", BinaryData::appsIcon_svg,
                                   BinaryData::appsIcon_sel_svg);
  addAndMakeVisible(appButton);

  gamesButton = createCategoryButton("Games", BinaryData::gamesIcon_svg,
                                     BinaryData::gamesIcon_sel_svg);
  addAndMakeVisible(gamesButton);

  settingsButton = createCategoryButton("Settings", BinaryData::settingsIcon_svg,
                                        BinaryData::settingsIcon_sel_svg);
  addAndMakeVisible(settingsButton);

  categoryButtonLayout.setItemLayout(0, 0, -1.0, -1.0);
  categoryButtonLayout.setItemLayout(1, categoryButtonHeight+categoryPadding,
                                     categoryButtonHeight+categoryPadding, categoryButtonHeight);
  categoryButtonLayout.setItemLayout(2, categoryButtonHeight+categoryPadding,
                                     categoryButtonHeight+categoryPadding, categoryButtonHeight);
  categoryButtonLayout.setItemLayout(3, categoryButtonHeight+categoryPadding,
                                     categoryButtonHeight+categoryPadding, categoryButtonHeight);
  categoryButtonLayout.setItemLayout(4, 0, -1.0, -1.0);

  setSize(480, 245);
}

MainContentComponent::~MainContentComponent() {}

void MainContentComponent::paint(Graphics &g) {
  g.fillAll(Colour(0xffffffff));

  g.setFont(Font(16.0f));
  g.setColour(Colours::black);
  g.drawText("Herro PokeCHIP", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized() {
  settingsPage->setBounds(getLocalBounds());

  auto bounds = getLocalBounds().reduced(categoryPadding);

  Component *categoryButtons[] = { nullptr, appButton.get(), gamesButton.get(),
                                   settingsButton.get(), nullptr };
  categoryButtonLayout.layOutComponents(categoryButtons, 5, bounds.getX(),
                                        bounds.getY() + categoryPadding,
                                        bounds.getWidth(), categoryButtonHeight, false, true);

}
