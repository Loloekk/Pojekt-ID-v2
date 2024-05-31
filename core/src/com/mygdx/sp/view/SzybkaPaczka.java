package com.mygdx.sp.view;

import com.badlogic.gdx.Game;


public class SzybkaPaczka extends Game {
	@Override
	public void create() {
		setScreen(new MainScreen(this));
	}
}