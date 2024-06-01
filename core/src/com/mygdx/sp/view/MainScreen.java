package com.mygdx.sp.view;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.*;
import com.badlogic.gdx.scenes.scene2d.utils.ChangeListener;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.utils.viewport.ScreenViewport;
import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.GetQueries;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class MainScreen implements Screen {
    private Game game;
    private Stage stage;
    private Skin skin;
    Screen screen;

    public MainScreen(Game game) {
        this.game = game;
        screen = this;
    }

    @Override
    public void show() {
        stage = new Stage(new ScreenViewport());
        Gdx.input.setInputProcessor(stage);

        // Załaduj skórkę
        skin = new Skin(Gdx.files.internal("uiskin.json"));

// Wczytanie czcionki z pliku, który zawiera polskie litery
        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ARIAL.TTF"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 20; // Rozmiar czcionki
        BitmapFont font = generator.generateFont(parameter);
        generator.dispose();

// Dodanie czcionki do skórki
        skin.add("default-font", font);

        // Utwórz tabelę
        Table table = new Table();
        table.setFillParent(true); // Ustaw tabelę na całym ekranie
        table.center().top(); // Ustaw wyrównanie do góry i prawej strony
        stage.addActor(table);

        SelectBox<Query> selectBox = new SelectBox<>(skin);
        selectBox.setItems(GetQueries.getQuieres());

        // Utwórz przycisk
        TextButton button = new TextButton("Submit", skin);
        button.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                game.setScreen(new QueryScreen(game, selectBox.getSelected(),screen));
            }
        });

        // Utwórz styl etykiety z czarnym kolorem
        Label.LabelStyle labelStyle = new Label.LabelStyle();
        labelStyle.font = skin.getFont("default-font");
        labelStyle.fontColor = Color.BLACK;

        // Utwórz etykiety z czarnym kolorem tekstu
        Label selectBoxLabel = new Label("Select Query:", labelStyle);

        table.row();
        table.add(selectBoxLabel).pad(10);
        table.row();
        table.add(selectBox).pad(10);
        table.row();
        table.add(button).pad(10);
    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        ScreenUtils.clear(0.8f, 0.8f, 1f, 1f);
        stage.act(Math.min(Gdx.graphics.getDeltaTime(), 1 / 30f));
        stage.draw();
    }

    @Override
    public void resize(int width, int height) {
        stage.getViewport().update(width, height, true);
    }

    @Override
    public void pause() {
    }

    @Override
    public void resume() {
    }

    @Override
    public void hide() {
    }

    @Override
    public void dispose() {
        stage.dispose();
        skin.dispose();
    }

    // Metoda do czytania tekstu z pliku
    private String readTextFromFile(String filename) {
        StringBuilder stringBuilder = new StringBuilder();
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                stringBuilder.append(line).append("\n");
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return stringBuilder.toString();
    }
}
