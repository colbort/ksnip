/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "SnippingAreaSettings.h"

SnippingAreaSettings::SnippingAreaSettings(KsnipConfig *config) :
	mConfig(config),
	mFreezeImageWhileSnippingCheckbox(new QCheckBox(this)),
	mSnippingAreaRulersCheckbox(new QCheckBox(this)),
	mSnippingAreaPositionAndSizeInfoCheckbox(new QCheckBox(this)),
	mSnippingAreaMagnifyingGlassCheckbox(new QCheckBox(this)),
	mAllowResizingRectSelectionCheckbox(new QCheckBox(this)),
	mShowSnippingAreaInfoTextCheckbox(new QCheckBox(this)),
	mSnippingCursorSizeLabel(new QLabel(this)),
	mSnippingCursorColorLabel(new QLabel(this)),
	mSnippingCursorSizeCombobox(new NumericComboBox(1, 2, 3)),
	mSnippingCursorColorButton(new ColorButton(this)),
	mLayout(new QGridLayout(this))
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

SnippingAreaSettings::~SnippingAreaSettings()
{
	delete mFreezeImageWhileSnippingCheckbox;
	delete mSnippingAreaPositionAndSizeInfoCheckbox;
	delete mSnippingAreaRulersCheckbox;
	delete mSnippingAreaMagnifyingGlassCheckbox;
	delete mAllowResizingRectSelectionCheckbox;
	delete mShowSnippingAreaInfoTextCheckbox;
	delete mSnippingCursorSizeLabel;
	delete mSnippingCursorColorLabel;
	delete mSnippingCursorColorButton;
	delete mSnippingCursorSizeCombobox;
}

void SnippingAreaSettings::saveSettings()
{
	mConfig->setFreezeImageWhileSnippingEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
	mConfig->setSnippingAreaMagnifyingGlassEnabled(mSnippingAreaMagnifyingGlassCheckbox->isChecked());
	mConfig->setSnippingAreaRulersEnabled(mSnippingAreaRulersCheckbox->isChecked());
	mConfig->setSnippingAreaPositionAndSizeInfoEnabled(mSnippingAreaPositionAndSizeInfoCheckbox->isChecked());
	mConfig->setAllowResizingRectSelection(mAllowResizingRectSelectionCheckbox->isChecked());
	mConfig->setShowSnippingAreaInfoText(mShowSnippingAreaInfoTextCheckbox->isChecked());
	mConfig->setSnippingCursorColor(mSnippingCursorColorButton->color());
	mConfig->setSnippingCursorSize(mSnippingCursorSizeCombobox->value());
}

void SnippingAreaSettings::initGui()
{
	auto const fixedButtonSize = 70;

	mFreezeImageWhileSnippingCheckbox->setText(tr("Freeze Image while snipping"));
	mFreezeImageWhileSnippingCheckbox->setToolTip(tr("When enabled will freeze the background while\n"
													 "selecting a rectangular region. It also changes\n"
													 "the behavior of delayed screenshots, with this\n"
													 "option enabled the delay happens before the\n"
													 "snipping area is shown and with the option disabled\n"
													 "the delay happens after the snipping area is shown.\n"
													 "This feature is always disabled for Wayland and always\n"
													 "enabled for MacOs."));
	connect(mFreezeImageWhileSnippingCheckbox, &QCheckBox::stateChanged, this, &SnippingAreaSettings::freezeImageWhileSnippingStateChanged);

	mSnippingAreaMagnifyingGlassCheckbox->setText(tr("Show magnifying glass on snipping area"));
	mSnippingAreaMagnifyingGlassCheckbox->setToolTip(tr("Show a magnifying glass which zooms into\n"
														"the background image. This option only works\n"
														"with 'Freeze Image while snipping' enabled."));

	mSnippingAreaRulersCheckbox->setText(tr("Show Snipping Area rulers"));
	mSnippingAreaRulersCheckbox->setToolTip(tr("Horizontal and vertical lines going from\n"
											   "desktop edges to cursor on snipping area."));

	mSnippingAreaPositionAndSizeInfoCheckbox->setText(tr("Show Snipping Area position and size info"));
	mSnippingAreaPositionAndSizeInfoCheckbox->setToolTip(tr("When left mouse button is not pressed the position\n"
															"is shown, when the mouse button is pressed,\n"
															"the size of the select area is shown left\n"
															"and above from the captured area."));

	mAllowResizingRectSelectionCheckbox->setText(tr("Allow resizing rect area selection by default"));
	mAllowResizingRectSelectionCheckbox->setToolTip(tr("When enabled will, after selecting a rect\n"
													   "area, allow resizing the selection. When\n"
													   "done resizing the selection can be confirmed\n"
													   "by pressing return."));

	mShowSnippingAreaInfoTextCheckbox->setText(tr("Show Snipping Area info text"));

	mSnippingCursorColorLabel->setText(tr("Snipping Area cursor color") + QLatin1Literal(":"));
	mSnippingCursorColorLabel->setToolTip(tr("Sets the color of the snipping area cursor."));
	mSnippingCursorColorButton->setMinimumWidth(fixedButtonSize);
	mSnippingCursorColorButton->setToolTip(mSnippingCursorColorLabel->toolTip());
	mSnippingCursorSizeLabel->setText(tr("Snipping Area cursor thickness") + QLatin1Literal(":"));
	mSnippingCursorSizeLabel->setToolTip(tr("Sets the thickness of the snipping area cursor."));
	mSnippingCursorSizeCombobox->setMinimumWidth(fixedButtonSize);
	mSnippingCursorSizeCombobox->setToolTip(mSnippingCursorSizeLabel->toolTip());

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mFreezeImageWhileSnippingCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mSnippingAreaMagnifyingGlassCheckbox, 1, 1, 1, 3);
	mLayout->addWidget(mSnippingAreaRulersCheckbox, 2, 0, 1, 3);
	mLayout->addWidget(mSnippingAreaPositionAndSizeInfoCheckbox, 3, 0, 1, 3);
	mLayout->addWidget(mAllowResizingRectSelectionCheckbox, 4, 0, 1, 3);
	mLayout->addWidget(mShowSnippingAreaInfoTextCheckbox, 5, 0, 1, 3);
	mLayout->setRowMinimumHeight(6, 15);
	mLayout->addWidget(mSnippingCursorSizeLabel, 7, 0, 1, 2);
	mLayout->addWidget(mSnippingCursorColorButton, 7, 2, Qt::AlignLeft);
	mLayout->addWidget(mSnippingCursorColorLabel, 8, 0, 1, 2);
	mLayout->addWidget(mSnippingCursorSizeCombobox, 8, 2, Qt::AlignLeft);

	setTitle(tr("Snipping Area"));
	setLayout(mLayout);
}

void SnippingAreaSettings::freezeImageWhileSnippingStateChanged()
{
	mSnippingAreaMagnifyingGlassCheckbox->setEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
}

void SnippingAreaSettings::loadConfig()
{
	mFreezeImageWhileSnippingCheckbox->setChecked(mConfig->freezeImageWhileSnippingEnabled());
	mFreezeImageWhileSnippingCheckbox->setEnabled(!mConfig->isFreezeImageWhileSnippingEnabledReadOnly());
	mSnippingAreaMagnifyingGlassCheckbox->setChecked(mConfig->snippingAreaMagnifyingGlassEnabled());
	mSnippingAreaMagnifyingGlassCheckbox->setEnabled(!mConfig->isSnippingAreaMagnifyingGlassEnabledReadOnly());
	mSnippingAreaRulersCheckbox->setChecked(mConfig->snippingAreaRulersEnabled());
	mSnippingAreaPositionAndSizeInfoCheckbox->setChecked(mConfig->snippingAreaPositionAndSizeInfoEnabled());
	mAllowResizingRectSelectionCheckbox->setChecked(mConfig->allowResizingRectSelection());
	mShowSnippingAreaInfoTextCheckbox->setChecked(mConfig->showSnippingAreaInfoText());
	mSnippingCursorColorButton->setColor(mConfig->snippingCursorColor());
	mSnippingCursorSizeCombobox->setValue(mConfig->snippingCursorSize());

	freezeImageWhileSnippingStateChanged();
}
