/*
  ==============================================================================

    StepSequencer.cpp
    Created: 7 Apr 2014 9:40:09pm
    Author:  xhosxe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "StepSequencer.h"

//==============================================================================
StepSequencer::StepSequencer(int numberOfValues, int maxValue, int nrpnBase)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	this->numberOfValues = numberOfValues;
	this->maxValue = maxValue;
	this->values = new int[numberOfValues];
	for (int k=0; k < numberOfValues; k++) {
		this->values[k] = (float) maxValue / numberOfValues * k;
	}
	this->nrpnBase = nrpnBase;
}

StepSequencer::~StepSequencer()
{
	if (this->values != nullptr) {
		delete this->values;
	}
}

void StepSequencer::paint (Graphics& g)
{
	float width = (float)getWidth() / numberOfValues;
	for (int k = 0; k < numberOfValues; k++) {
	    float height = (float)getHeight() * values[k] / (maxValue - 1) ;
	    float red = 205.0f - height * 150.0f / getHeight() ;
	    float blue = 255.0f;
        float green = 255.0f - height * 178.0f / getHeight();
        g.setColour ( Colour(red, green, blue));
		g.fillRect((float)k * width, (float)getHeight() - height, width, height);
	}
    for (int k = 0; k < numberOfValues; k++) {
		g.setColour (Colours::grey);
		g.drawVerticalLine(width * (k +1), 0, getHeight());

		g.setColour (Colours::darkgrey);
		g.drawText(String(values[k]), (float) k * width, getHeight() - 20, width, 10, Justification::centred, true);
	}
//	g.setColour (Colours::red);
//	g.drawText(String(debugValue), 10, 10 , 50, 10, Justification::centred, true);

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

int  StepSequencer::limitX(int x) {
	return x < 0 ? 0 : (x > numberOfValues ? numberOfValues : x);
}
int  StepSequencer::limitY(int y) {
	return y < 0 ? 0 : (y > maxValue ? maxValue : y);
}


void StepSequencer::updateValues(const MouseEvent& event) {
	if (event.mods.isRightButtonDown()) {
		int x = limitX(event.x * numberOfValues / getWidth());
		setValues(x, 0);
	} else {
		int x = limitX(event.x * numberOfValues / getWidth());
		int y = limitY((float) maxValue * (getHeight() - event.y) / getHeight() + .5);
		setValues(x, y);
	}
	return ;
}

void StepSequencer::mouseDown (const MouseEvent &event)  {
	if (event.getNumberOfClicks() != 1) {
		return;
	}
	updateValues(event);
}

void StepSequencer::mouseUp (const MouseEvent &event)  {
}

void StepSequencer::mouseDrag (const MouseEvent &event)  {
	updateValues(event);
}

void StepSequencer::mouseDoubleClick (const MouseEvent& event) {
	if (!event.mods.isLeftButtonDown()) {
		return;
	}
	int x = limitX(event.x * numberOfValues / getWidth());
	setValues(x, maxValue);
}

void StepSequencer::mouseWheelMove (const MouseEvent& event, const MouseWheelDetails& wheel) {
//	debugValue = wheel.deltaY;
	if (wheel.deltaY == 0) {
		return;
	}
	int x = event.x * numberOfValues / getWidth();
	int y = values[x] + (wheel.deltaY > 0 ? 1 : -1) * (wheel.isReversed ? -1 : 1);
	y = y < 0 ? 0 : (y > maxValue ? maxValue : y);
	setValues(x, y);
}


void StepSequencer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void StepSequencer::sendNrpn (int nrpnParam, int nrpnValue) {
	if (midiOutput != nullptr) {
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 99, (nrpnParam >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 98, (nrpnParam & 0xFF)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 6, (nrpnValue >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 38, (nrpnValue & 0xFF)));
	}
}

void StepSequencer::setValues(int x, int y) {
	if (values[x] != y && y >= 0 && y < maxValue) {
		sendNrpn(nrpnBase + x, y);
		values[x] = y;
		repaint();
	}
}

void StepSequencer::handleIncomingNrpn(int param, int value) {
	int x = param - nrpnBase;
	if (values[x] != value && value >= 0 && value < maxValue) {
		values[x] = value;
		repaint();
	}
}

