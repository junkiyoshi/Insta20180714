#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofSetColor(239);

	this->font_size = 350;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<ofPoint> points;
	vector<int> sizes;

	string word = "EX";
	ofPoint word_size(this->font.stringWidth(word), this->font.stringHeight(word));
	int sample_count = 80;

	vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);
	for (int word_index = 0; word_index < word.size(); word_index++) {

		vector<ofPolyline> outline = word_path[word_index].getOutline();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);
				point += ofPoint(word_size.x * -0.5, word_size.y * 0.5);
				point += ofPoint(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

				points.push_back(point);
				sizes.push_back(1);
			}
		}

		ofPopMatrix();
	}

	for (int i = 0; i < 192; i++) {

		ofPoint point(ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetHeight()));
		points.push_back(point);
		sizes.push_back(1);
	}

	for (int out_index = 0; out_index < points.size(); out_index++) {

		for (int in_index = out_index + 1; in_index < points.size(); in_index++) {

			if (points[out_index].distance(points[in_index]) < 35) {

				ofDrawLine(points[out_index], points[in_index]);
				sizes[out_index]++;
				sizes[in_index]++;
			}
		}
	}

	for (int i = 0; i < points.size(); i++) {

		ofDrawCircle(points[i], sizes[i]);
	}

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}