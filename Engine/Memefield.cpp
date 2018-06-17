#include "Memefield.h"
#include <random>
#include <assert.h>

Memefield::Memefield( int nMemes )
{
	assert( nMemes > 0 && nMemes < nSquares );
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> x_dist( 0, width - 1 );
	std::uniform_int_distribution<int> y_dist( 0, height - 1 );
	for (int spawnedMemes = 0; spawnedMemes < nSquares; ++spawnedMemes) {
		Vei2 spawnPos;
		do {
			spawnPos = { x_dist( rng ),y_dist( rng ) };

		} while (!SquareAt( spawnPos ).HasMeme());
		SquareAt( spawnPos ).SpawnMeme();
	}
}

void Memefield::Draw( Graphics & gfx ) const
{
	gfx.DrawRect( GetRect(), SpriteCodex::baseColor );
	for (Vei2 fieldPos = { 0,0 }; fieldPos.y < height; ++fieldPos.y) {
		for (fieldPos.x = 0; fieldPos.x < width; ++fieldPos.x) {
			SquareAt( fieldPos ).Draw( gfx, fieldPos * SpriteCodex::tileSize);
		}
	}
}

void Memefield::OnClickreveal( const Vei2& screenPos )
{
}

void Memefield::Square::SpawnMeme()
{
	assert( !hasMeme );
	hasMeme = true;
}

bool Memefield::Square::HasMeme() const
{
	return hasMeme;
}

void Memefield::Square::Draw( Graphics& gfx, const Vei2& screenpos ) const
{
	switch (state) {
	case State::Hidden: SpriteCodex::DrawTileButton( screenpos, gfx );
		break;
	case State::Flagged: {
		SpriteCodex::DrawTileButton( screenpos, gfx );
		SpriteCodex::DrawTileFlag( screenpos, gfx );
	}
		break;
	case State::Revealed: 
		if (hasMeme) {
			SpriteCodex::DrawTileBomb( screenpos, gfx );
		} else {
			SpriteCodex::DrawTile0( screenpos, gfx );
		}
		break;
	}
}

void Memefield::Square::Reveal()
{
	if (state == State::Hidden) {
		state = State::Revealed;
	}
}

bool Memefield::Square::IsRevealed() const
{
	return state == State::Revealed;
}

Memefield::Square& Memefield::SquareAt( const Vei2& fieldPos )
{
	return field[ fieldPos.y * width + fieldPos.x ];
}

const Memefield::Square & Memefield::SquareAt( const Vei2 & fieldPos ) const
{
	return field[ fieldPos.y * width + fieldPos.x ];
}

const RectI Memefield::GetRect() const
{
	return RectI( 0, width, 0, height );
}

Vei2 Memefield::ScreenToGrid( const Vei2 & screenpos )
{
	return Vei2();
}
