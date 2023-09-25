#define OLC_PGE_APPLICATION
#include "GUIEngine.h"
#include "Kaart.h"

#define SYMBOL_SIZE 6

class ChansarenUI : public olc::PixelGameEngine {

public:
	std::vector<std::vector<std::unique_ptr<olc::Sprite>>> cardSprites;
	ChansarenUI() {
		sAppName = "Chansaren";
	}

public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here
		std::string numbers[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K" };
		std::string colors[4] = { "Spades","Hearts","Clubs","Diamonds"};
		
		for (std::string col : colors) {
			std::vector<std::unique_ptr<olc::Sprite>> temp;
			for (std::string num : numbers) {
				std::unique_ptr<olc::Sprite> spr = std::make_unique<olc::Sprite>("../../../assets/PNG/Cards/card" + col + num + ".png");
				//DrawSprite(10, 10, spr.get());
				temp.push_back(std::move(spr));
			}
			cardSprites.push_back(std::move(temp));
		}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		// Check if the left mouse button is pressed
		if (GetMouse(olc::Mouse::LEFT).bPressed) {
			// Left mouse button is pressed
			// Do something when the left mouse button is clicked
			// Find the closest point using range-based for loops
			olc::vi2d targetPosition = olc::vi2d(mouseX, mouseY);
			//drawDiamondCenterd(targetPosition.x, targetPosition.y, SYMBOL_SIZE, olc::RED);
			drawCardCenterd(targetPosition.x, targetPosition.y,Kaart(ACE,Clubs), SYMBOL_SIZE, olc::RED);
		}
		return true;
	}
private:
	void drawCardCenterd(int x, int y,Kaart kaart, int size, olc::Pixel color) {
		//std::string numbers[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K" };
		//std::string colors[4] = { "Spades","Hearts","Clubs","Diamonds"};
		DrawSprite(x,y,cardSprites.at(kaart.getSymbol()).at(kaart.getValue()-1).get(),0.0000001);
	}
};