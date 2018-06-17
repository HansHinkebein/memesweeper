#pragma once

#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "RectI.h"

class Memefield
{
	class Square
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};

		void SpawnMeme();
		bool HasMeme() const;
		void Draw(Graphics& gfx, const Vei2& screenpos) const;
		void Reveal();
		bool IsRevealed() const;

	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};

public:
	Memefield( int nMemes );
	void Draw( Graphics& gfx ) const;
	void OnClickreveal( const Vei2& screenPos);

private:
	Square& SquareAt( const Vei2& fieldPos );
	const Square& SquareAt( const Vei2& fieldPos ) const;
	const RectI GetRect() const;
	Vei2 ScreenToGrid( const Vei2& screenpos );

private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	static constexpr int nSquares = ( width * height );
	Square field[ nSquares ];
};