#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	// 配色デザイン ビビッドブルー P144
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(18, 85, 163));
	color_palette.push_back(ofColor(0, 165, 231));
	color_palette.push_back(ofColor(93, 177, 186));
	color_palette.push_back(ofColor(44, 121, 191));
	color_palette.push_back(ofColor(136, 185, 79));
	color_palette.push_back(ofColor(246, 221, 80));
	color_palette.push_back(ofColor(200, 59, 57));
	//color_palette.push_back(ofColor(255, 255, 255));
	
	int color_index = 0;
	for (int x = 0; x <= ofGetWidth(); x += 40) {

		color_index = (color_index + 1) % color_palette.size();
		ofColor color = color_palette[color_index];

		if (x % 60 == 0) {

			auto y = ofMap(ofNoise(x * 0.005 + ofGetFrameNum() * 0.025), 0, 1, 0, ofGetHeight()) - 30;
			this->draw_arrow(glm::vec2(x, 0), glm::vec2(x, y), 35, color);

			y = ofMap(ofNoise(x * 0.005 + ofGetFrameNum() * 0.025), 1, 0, 0, ofGetHeight()) + 30;
			this->draw_arrow(glm::vec2(x, ofGetHeight()), glm::vec2(x, y), 35, color);
		}
		else {

			auto y = ofMap(ofNoise(x * 0.005 + ofGetFrameNum() * 0.025), 1, 0, 0, ofGetHeight()) + 30;
			this->draw_arrow(glm::vec2(x, ofGetHeight()), glm::vec2(x, y), 35, color);

			y = ofMap(ofNoise(x * 0.005 + ofGetFrameNum() * 0.025), 0, 1, 0, ofGetHeight()) - 30;
			this->draw_arrow(glm::vec2(x, 0), glm::vec2(x, y), 35, color);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	ofPushMatrix();
	ofTranslate(target);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofSetColor(255);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofEndShape();

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}