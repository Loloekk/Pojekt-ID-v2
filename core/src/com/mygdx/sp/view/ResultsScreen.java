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

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.stream.Collectors;

public class ResultsScreen implements Screen {
    Game game;
    Screen previousScreen;
    private Stage stage;
    private Skin skin;
    private Label resultLabel;

    public ResultsScreen(Game game,Screen previousScreen) {
        this.game = game;
        this.previousScreen = previousScreen;
    }

    @Override
    public void show() {
        stage = new Stage(new ScreenViewport());
        stage.getRoot().setColor(new Color(0.8f, 0.8f, 1f, 1f));
        Gdx.input.setInputProcessor(stage);

        // Load skin
        skin = new Skin(Gdx.files.internal("uiskin.json"));

// Wczytanie czcionki z pliku, który zawiera polskie litery
        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ARIAL.TTF"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 20; // Rozmiar czcionki
        BitmapFont font = generator.generateFont(parameter);
        generator.dispose();

// Dodanie czcionki do skórki
        skin.add("default-font", font);

        // Create table
        Table table = new Table();
        table.top().right(); // Align to top right

        // Create result label
        resultLabel = new Label("Wynik polecenia psql:", skin);
        resultLabel.setColor(Color.WHITE); // Set text color to white
        // Create a button
        TextButton button = new TextButton("Back", skin);
        button.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                game.setScreen(previousScreen);
            }
        });

        // Add button to table
        table.add(button).pad(10).expand().top().left();
        table.row();
        // Add result label to table
        table.add(resultLabel).pad(10).expand().top().left();



        // Add click listener to button


        // Add table to scroll pane
        ScrollPane scrollPane = new ScrollPane(table, skin);
        scrollPane.setColor(new Color(0.8f, 0.8f, 1f, 1f));
        scrollPane.setFillParent(true);

        // Add scroll pane to stage
        stage.addActor(scrollPane);

        // Execute psql command and display result
        executePsqlCommand();
    }

    private void executePsqlCommand() {
        try {
            // Path to tmp.sql file in assets directory
            File tmpSqlFile = new File(Gdx.files.internal("tmp.sql").file().getAbsolutePath());

            // Command to execute
            String command = "psql -f " + tmpSqlFile.getAbsolutePath();

            // Use ProcessBuilder to execute command
            ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
            processBuilder.redirectErrorStream(true);

            Process process = processBuilder.start();

            // Read command output
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String output = reader.lines().collect(Collectors.joining("\n"));
            int exitCode = process.waitFor();

            // Display command output on label
            Gdx.app.postRunnable(() -> {
                resultLabel.setText(output);
            });

        } catch (Exception e) {
            e.printStackTrace();
            Gdx.app.postRunnable(() -> {
                resultLabel.setText("Błąd podczas wykonywania polecenia psql: " + e.getMessage());
            });
        }
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
    public void pause() {}

    @Override
    public void resume() {}

    @Override
    public void hide() {}

    @Override
    public void dispose() {
        stage.dispose();
        skin.dispose();
    }
}
