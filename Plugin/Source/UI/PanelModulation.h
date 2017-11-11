/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

/*
* Copyright 2017 Xavier Hosxe
*
* Author: Xavier Hosxe (xavier <dot> hosxe
*                      (at) g m a i l <dot> com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "JuceHeader.h"
#include "StepSequencer.h"
#include "EnveloppeFree1.h"
#include "EnveloppeFree2.h"
#include "PanelOfComponents.h"


#define NUMBER_OF_STEP_SEQ 2
#define NUMBER_OF_LFO 3

#define NUMBER_OF_MATRIX_ROW 12
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Introjucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelModulation  : public Component,
                         public Button::Listener,
                         public Slider::Listener,
                         public ComboBox::Listener,
                         public PanelOfComponents
{
public:
    //==============================================================================
    PanelModulation ();
    ~PanelModulation();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked(Button* buttonThatWasClicked);
	void sliderValueChanged(Slider* sliderThatWasMoved);
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged);
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	void buildParameters();
	void updateSliderFromParameter_hook(Slider* slider);
	void updateComboFromParameter_hook(ComboBox* combo);
	void updateUIEnveloppe(String paramName);
	void updateUIStepSequencer(String paramName);
	bool containsThisParameterAsStepSequencer(String name);
	bool containsThisParameterAsEnveloppe(String name);
	void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


	// LFO
	ScopedPointer<TextButton> lfoButton[NUMBER_OF_LFO];
	ScopedPointer<Label> lfoPhaseLabel;
	ScopedPointer<Slider> lfoPhase[NUMBER_OF_LFO];
	ScopedPointer<ComboBox> lfoShape[NUMBER_OF_LFO];
	ScopedPointer<ComboBox> lfoExtMidiSync[NUMBER_OF_LFO];
	ScopedPointer<Slider> lfoFrequency[NUMBER_OF_LFO];
	ScopedPointer<Slider> lfoBias[NUMBER_OF_LFO];
	ScopedPointer<ComboBox> lfoKsynOnOff[NUMBER_OF_LFO];
	ScopedPointer<Slider> lfoKSync[NUMBER_OF_LFO];
	ScopedPointer<Label> lfoFrequencyLabel;
	ScopedPointer<Label> lfoBiasLabel;
	ScopedPointer<Label> lfoKSynLabel;
	ScopedPointer<ComboBox> enveloppeFree2Loop;
	ScopedPointer<Label> enveloppeFree2LoopLabel;


	// MATRIX
	ScopedPointer<Label> matrixRowLabel[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<ComboBox> matrixSource[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<Slider> matrixMultipler[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<ComboBox> matrixDestination[NUMBER_OF_MATRIX_ROW];

	// ENVELOPPES
	ScopedPointer<EnveloppeFree1> enveloppeFree1;
	ScopedPointer<EnveloppeFree2> enveloppeFree2;


	// STEP SEQUENCER
	ScopedPointer<TextButton> stepSeqButton[NUMBER_OF_STEP_SEQ];
	ScopedPointer<StepSequencer> stepSequencer[NUMBER_OF_STEP_SEQ];

	ScopedPointer<Label> stepSeqBPMLabel;
	ScopedPointer<ComboBox> stepSeqExtMidiSync[NUMBER_OF_STEP_SEQ];
	ScopedPointer<Slider> stepSeqBPM[NUMBER_OF_STEP_SEQ];
	ScopedPointer<Label> stepSeqGateLabel;
	ScopedPointer<Slider> stepSeqGate[NUMBER_OF_STEP_SEQ];

	MidiBuffer* eventsToAdd;
	bool initialized;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> matrixGroup;
    ScopedPointer<GroupComponent> lfoGroup;
    ScopedPointer<GroupComponent> env1Group;
    ScopedPointer<GroupComponent> env2Group;
    ScopedPointer<GroupComponent> stepSeqGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelModulation)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
