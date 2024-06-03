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
import com.badlogic.gdx.utils.viewport.ScreenViewport;
import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class QueryScreen implements Screen
{
    private Game game;
    private Stage stage;
    private Skin skin;
    Query query;
    Screen screen;
    Screen previousScreen;
    public QueryScreen(Game game, Query query, Screen previousScreen)
    {
        this.game = game;
        this.query = query;
        this.previousScreen = previousScreen;
        screen = this;
    }
    @Override
    public void show() {
        stage = new Stage(new ScreenViewport());
        Gdx.input.setInputProcessor(stage);

        skin = new Skin(Gdx.files.internal("uiskin.json"));

        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ARIAL.TTF"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 20;
        BitmapFont font = generator.generateFont(parameter);
        generator.dispose();

        skin.add("default-font", font);


        Table table = new Table();
        table.setFillParent(true); // Ustaw tabelę na całym ekranie
        table.top().left(); // Ustaw wyrównanie do góry i prawej strony
        stage.addActor(table);

        TextButton button = new TextButton("Back", skin);
        button.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                game.setScreen(previousScreen);
            }
        });

        table.add(button).pad(10).top().left();
        table.row();
        Label.LabelStyle labelStyleTitle = new Label.LabelStyle();
        labelStyleTitle.font = skin.getFont("default-font");
        labelStyleTitle.fontColor = Color.BLACK;

        Label.LabelStyle labelStyleFields = new Label.LabelStyle();
        labelStyleFields.font = skin.getFont("default-font");
        labelStyleFields.fontColor = Color.BLACK;

        Label tmp = new Label(query.toString(),labelStyleTitle);
        table.add(tmp).top().left().pad(10).colspan(3);
        table.row();


        List<TextField> list = new ArrayList<>();
        for(String nazwa : query.getFields())
        {
            list.add(new TextField("",skin));
            list.get(list.size()-1).setMessageText(nazwa + "...");

            Label tmpp = new Label(nazwa,labelStyleFields);
            table.add(tmpp).top().left().pad(10);
            table.add(list.get(list.size()-1)).top().width(300).left().pad(10);
            table.row();
        }

        TextButton buttonSubmit = new TextButton("Submit", skin);
        buttonSubmit.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                List<TurboString> input = new ArrayList<>();
                for(TextField textField : list)
                {
                    input.add(new TurboString(textField.getText()));
                }
                if(!query.check(input)) return;
                try {
                    File tmpSqlFile = new File(Gdx.files.internal("tmp.sql").file().getAbsolutePath());

                    if(query.getQuery(input) == null) return;
                    String command = "echo \"" + query.getQuery(input) + "\" > " + tmpSqlFile.getAbsolutePath();
                    System.out.println(query.getQuery(input));
                    ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
                    processBuilder.redirectErrorStream(true);

                    Process process = processBuilder.start();
                    game.setScreen(new ResultsScreen(game,screen));
                } catch (Exception e) {

                }
            }
        });

        table.add(buttonSubmit).pad(10).top().right();

    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
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
}
