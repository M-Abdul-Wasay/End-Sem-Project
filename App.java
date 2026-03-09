import javafx.animation.*;
import javafx.application.Application;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.effect.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.*;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import javafx.scene.text.*;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.util.*;

public class App extends Application {

    // ─── Colors ───────────────────────────────────────────────────────────────
    private static final String BG_DARK     = "#0d0d0f";
    private static final String BG_CARD     = "#16161a";
    private static final String BG_INPUT    = "#1c1c22";
    private static final String ACCENT      = "#7c3aed";
    private static final String ACCENT_GLOW = "#9b59f5";
    private static final String TEXT_MAIN   = "#e8e6f0";
    private static final String TEXT_DIM    = "#4a4860";
    private static final String TEXT_MUTED  = "#7a748c";
    private static final String GREEN       = "#22c55e";
    private static final String RED         = "#ef4444";
    private static final String YELLOW      = "#eab308";
    private static final String CURSOR_COL  = "#c084fc";

    // ─── Styles ───────────────────────────────────────────────────────────────
    private static final String STYLE_TIMER_BAR =
            "-fx-accent: "                   + ACCENT_GLOW + ";" +
            "-fx-background-color: "         + BG_INPUT    + ";" +
            "-fx-background-radius: 2;"      +
            "-fx-control-inner-background: " + BG_INPUT    + ";";

    private static final String STYLE_INPUT_BASE =
            "-fx-background-color: " + BG_INPUT  + ";" +
            "-fx-text-fill: "        + TEXT_MAIN + ";" +
            "-fx-prompt-text-fill: " + TEXT_DIM  + ";" +
            "-fx-font-size: 18px;"   +
            "-fx-font-family: 'Courier New';" +
            "-fx-background-radius: 10;" +
            "-fx-border-radius: 10;" +
            "-fx-border-width: 1.5;" +
            "-fx-padding: 12 16 12 16;";

    private static final String STYLE_INPUT_NORMAL  = STYLE_INPUT_BASE + "-fx-border-color: " + TEXT_DIM + ";";
    private static final String STYLE_INPUT_ACTIVE  = STYLE_INPUT_BASE + "-fx-border-color: " + ACCENT   + ";";
    private static final String STYLE_INPUT_CORRECT = STYLE_INPUT_BASE + "-fx-border-color: " + GREEN    + ";";
    private static final String STYLE_INPUT_WRONG   = STYLE_INPUT_BASE + "-fx-border-color: " + RED      + ";";

    private static final String STYLE_STAT_VALUE =
            "-fx-text-fill: "      + TEXT_MAIN + ";" +
            "-fx-font-size: 26px;" +
            "-fx-font-family: 'Courier New';" +
            "-fx-font-weight: bold;";

    private static final String STYLE_STAT_LABEL =
            "-fx-text-fill: "      + TEXT_MUTED + ";" +
            "-fx-font-size: 10px;" +
            "-fx-font-family: 'Courier New';";

    private static final String STYLE_STAT_BOX =
            "-fx-background-color: " + BG_CARD + ";" +
            "-fx-background-radius: 8;";

    private static final String STYLE_TOGGLE_ACTIVE =
            "-fx-background-color: " + ACCENT     + ";" +
            "-fx-text-fill: white;"  +
            "-fx-font-size: 11px;"   +
            "-fx-font-family: 'Courier New';" +
            "-fx-background-radius: 6;" +
            "-fx-padding: 6 14 6 14;" +
            "-fx-cursor: hand;";

    private static final String STYLE_TOGGLE_INACTIVE =
            "-fx-background-color: " + BG_CARD    + ";" +
            "-fx-text-fill: "        + TEXT_MUTED + ";" +
            "-fx-font-size: 11px;"   +
            "-fx-font-family: 'Courier New';" +
            "-fx-background-radius: 6;" +
            "-fx-padding: 6 14 6 14;" +
            "-fx-cursor: hand;";

    private static final String STYLE_RESET_BTN =
            "-fx-background-color: " + BG_CARD    + ";" +
            "-fx-text-fill: "        + TEXT_MUTED + ";" +
            "-fx-font-size: 13px;"   +
            "-fx-font-family: 'Courier New';" +
            "-fx-background-radius: 10;" +
            "-fx-border-color: "     + TEXT_DIM   + ";" +
            "-fx-border-radius: 10;" +
            "-fx-border-width: 1.5;" +
            "-fx-padding: 12 20 12 20;" +
            "-fx-cursor: hand;";

    private static final String STYLE_RESULT_PANEL =
            "-fx-background-color: " + BG_CARD + ";" +
            "-fx-background-radius: 20;" +
            "-fx-border-color: "     + ACCENT  + ";" +
            "-fx-border-radius: 20;" +
            "-fx-border-width: 1.5;" +
            "-fx-padding: 40;";

    private static final String STYLE_PLAY_AGAIN =
            "-fx-background-color: " + ACCENT + ";" +
            "-fx-text-fill: white;"  +
            "-fx-font-size: 15px;"   +
            "-fx-font-family: 'Courier New';" +
            "-fx-background-radius: 10;" +
            "-fx-padding: 12 30 12 30;" +
            "-fx-cursor: hand;";

    private static final String STYLE_WORD_SECTION =
            "-fx-background-color: " + BG_CARD + ";" +
            "-fx-background-radius: 12;";

    private static final String STYLE_SCROLL_PANE =
            "-fx-background-color: " + BG_CARD + ";" +
            "-fx-background-radius: 12;" +
            "-fx-border-color: transparent;";

    private static final String STYLE_TITLE =
            "-fx-text-fill: white;" +
            "-fx-font-size: 36px;"  +
            "-fx-font-family: 'Courier New';" +
            "-fx-font-weight: bold;";

    private static final String STYLE_SUBTITLE =
            "-fx-text-fill: "      + TEXT_MUTED + ";" +
            "-fx-font-size: 13px;" +
            "-fx-font-family: 'Courier New';";

    private static final String STYLE_STATUS =
            "-fx-text-fill: "      + TEXT_MUTED + ";" +
            "-fx-font-size: 13px;" +
            "-fx-font-family: 'Courier New';";

    private static final String STYLE_TIMER_LOW =
            "-fx-text-fill: "      + RED + ";" +
            "-fx-font-size: 26px;" +
            "-fx-font-family: 'Courier New';" +
            "-fx-font-weight: bold;";

    private static final String STYLE_RESULT_TITLE =
            "-fx-text-fill: white;" +
            "-fx-font-size: 28px;"  +
            "-fx-font-family: 'Courier New';" +
            "-fx-font-weight: bold;";

    private static final String STYLE_RESULT_VALUE =
            "-fx-text-fill: "      + ACCENT_GLOW + ";" +
            "-fx-font-size: 30px;" +
            "-fx-font-family: 'Courier New';" +
            "-fx-font-weight: bold;";

    private static final String STYLE_RESULT_SUBLABEL =
            "-fx-text-fill: "      + TEXT_MUTED + ";" +
            "-fx-font-size: 12px;" +
            "-fx-font-family: 'Courier New';";

    // ─── Word Pools ───────────────────────────────────────────────────────────
    private static final String[][] WORD_POOLS = {
        { "the", "quick", "brown", "fox", "jumps", "over", "lazy", "dog",
          "java", "code", "type", "fast", "word", "play", "key", "board",
          "screen", "time", "game", "win", "score", "best", "run", "fun" },
        { "programming", "keyboard", "monitor", "function", "variable",
          "algorithm", "developer", "software", "computer", "network",
          "database", "language", "practice", "accuracy", "velocity",
          "challenge", "champion", "maximum", "terminal", "sequence" },
        { "asynchronous", "polymorphism", "encapsulation", "multithreading",
          "cryptography", "documentation", "infrastructure", "optimization",
          "refactoring", "concatenation", "initialization", "synchronization",
          "authentication", "serialization", "visualization", "implementation" }
    };

    // ─── State ────────────────────────────────────────────────────────────────
    private String[]  currentWords;
    private int       currentWordIndex = 0;
    private int       correctChars     = 0;
    private int       totalTyped       = 0;
    private int       correctWords     = 0;
    private long      startTime;
    private boolean   gameRunning      = false;
    private boolean   gameStarted      = false;
    private int       difficulty       = 0;
    private int       timeLimit        = 60;
    private int       timeLeft;
    private Timeline  countdownTimer;
    private final Random random = new Random();

    // ─── UI refs ──────────────────────────────────────────────────────────────
    private TextFlow    wordDisplay;
    private TextField   inputField;
    private Label       timerLabel;
    private Label       wpmLabel;
    private Label       accuracyLabel;
    private Label       scoreLabel;
    private Label       statusLabel;
    private ProgressBar timerBar;
    private VBox        resultPanel;

    // ─── start ────────────────────────────────────────────────────────────────
    @Override
    public void start(Stage stage) {
        stage.setTitle("⌨  TypeBlitz");
        stage.setMinWidth(900);
        stage.setMinHeight(600);

        StackPane root = new StackPane();
        root.setStyle("-fx-background-color: " + BG_DARK + ";");

        VBox layout = new VBox(0);
        layout.setAlignment(Pos.TOP_CENTER);
        layout.setPadding(new Insets(40, 60, 40, 60));

        statusLabel = new Label("press any key to start");
        statusLabel.setStyle(STYLE_STATUS);

        VBox header      = buildHeader();
        VBox statsBar    = buildStatsBar();
        HBox controls    = buildControls();
        VBox wordSection = buildWordSection();
        HBox inputRow    = buildInputRow();

        VBox.setMargin(header,      new Insets(0, 0, 30, 0));
        VBox.setMargin(statsBar,    new Insets(0, 0, 20, 0));
        VBox.setMargin(controls,    new Insets(0, 0, 24, 0));
        VBox.setMargin(wordSection, new Insets(0, 0, 20, 0));
        VBox.setMargin(inputRow,    new Insets(0, 0, 12, 0));

        layout.getChildren().addAll(header, statsBar, controls, wordSection, inputRow, statusLabel);

        resultPanel = buildResultPanel();
        resultPanel.setVisible(false);

        root.getChildren().addAll(createBackground(), layout, resultPanel);

        stage.setScene(new Scene(root, 900, 620));
        stage.show();

        generateWords();
        setupInputHandler();
        inputField.requestFocus();
    }

    // ─── Background ───────────────────────────────────────────────────────────
    private Pane createBackground() {
        Pane pane = new Pane();
        pane.setMouseTransparent(true);
        for (int i = 0; i < 40; i++) {
            Circle c = new Circle(random.nextDouble() * 2 + 0.5);
            c.setFill(Color.web(ACCENT, 0.08 + random.nextDouble() * 0.07));
            c.setLayoutX(random.nextDouble() * 900);
            c.setLayoutY(random.nextDouble() * 620);

            TranslateTransition tt = new TranslateTransition(
                    Duration.seconds(8 + random.nextDouble() * 10), c);
            tt.setByY(-40 - random.nextDouble() * 60);
            tt.setByX(random.nextDouble() * 20 - 10);
            tt.setAutoReverse(true);
            tt.setCycleCount(Animation.INDEFINITE);
            tt.setDelay(Duration.seconds(random.nextDouble() * 5));
            tt.play();
            pane.getChildren().add(c);
        }
        return pane;
    }

    // ─── Header ───────────────────────────────────────────────────────────────
    private VBox buildHeader() {
        Label title = new Label("TypeBlitz");
        title.setStyle(STYLE_TITLE);
        title.setEffect(new DropShadow(20, Color.web(ACCENT_GLOW, 0.7)));

        Label sub = new Label("how fast can you type?");
        sub.setStyle(STYLE_SUBTITLE);

        VBox box = new VBox(4, title, sub);
        box.setAlignment(Pos.CENTER);
        return box;
    }

    // ─── Stats Bar ────────────────────────────────────────────────────────────
    private VBox buildStatsBar() {
        timerLabel    = makeStatValue("60");
        wpmLabel      = makeStatValue("0");
        accuracyLabel = makeStatValue("100%");
        scoreLabel    = makeStatValue("0");

        timerBar = new ProgressBar(1.0);
        timerBar.setPrefWidth(Double.MAX_VALUE);
        timerBar.setPrefHeight(4);
        timerBar.setStyle(STYLE_TIMER_BAR);

        HBox row = new HBox(20,
                wrapStat(timerLabel,    "time"),
                wrapStat(wpmLabel,      "wpm"),
                wrapStat(accuracyLabel, "accuracy"),
                wrapStat(scoreLabel,    "words"));
        row.setAlignment(Pos.CENTER);

        VBox box = new VBox(10, row, timerBar);
        box.setAlignment(Pos.CENTER);
        return box;
    }

    private Label makeStatValue(String text) {
        Label lbl = new Label(text);
        lbl.setStyle(STYLE_STAT_VALUE);
        return lbl;
    }

    private VBox wrapStat(Label value, String labelText) {
        Label lbl = new Label(labelText);
        lbl.setStyle(STYLE_STAT_LABEL);
        VBox box = new VBox(2, value, lbl);
        box.setAlignment(Pos.CENTER);
        box.setPadding(new Insets(10, 20, 10, 20));
        box.setStyle(STYLE_STAT_BOX);
        return box;
    }

    // ─── Controls ─────────────────────────────────────────────────────────────
    private HBox buildControls() {
        String[] diffNames = { "easy", "medium", "hard" };
        HBox diffRow = new HBox(6);
        diffRow.setAlignment(Pos.CENTER);

        for (int i = 0; i < diffNames.length; i++) {
            final int idx = i;
            ToggleButton btn = new ToggleButton(diffNames[i]);
            btn.setStyle(i == 0 ? STYLE_TOGGLE_ACTIVE : STYLE_TOGGLE_INACTIVE);
            btn.setOnAction(e -> {
                difficulty = idx;
                diffRow.getChildren().forEach(n -> ((ToggleButton) n).setStyle(STYLE_TOGGLE_INACTIVE));
                btn.setStyle(STYLE_TOGGLE_ACTIVE);
                if (!gameRunning) generateWords();
            });
            diffRow.getChildren().add(btn);
        }

        int[] times = { 15, 30, 60, 120 };
        HBox timeRow = new HBox(6);
        timeRow.setAlignment(Pos.CENTER);

        for (int t : times) {
            final int val = t;
            ToggleButton btn = new ToggleButton(t + "s");
            btn.setStyle(t == 60 ? STYLE_TOGGLE_ACTIVE : STYLE_TOGGLE_INACTIVE);
            btn.setOnAction(e -> {
                timeLimit = val;
                timeLeft  = val;
                timeRow.getChildren().forEach(n -> ((ToggleButton) n).setStyle(STYLE_TOGGLE_INACTIVE));
                btn.setStyle(STYLE_TOGGLE_ACTIVE);
                if (!gameRunning) {
                    timerLabel.setText(String.valueOf(timeLimit));
                    timerBar.setProgress(1.0);
                }
            });
            timeRow.getChildren().add(btn);
        }

        HBox row = new HBox(24, diffRow, timeRow);
        row.setAlignment(Pos.CENTER);
        return row;
    }

    // ─── Word Section ─────────────────────────────────────────────────────────
    private VBox buildWordSection() {
        wordDisplay = new TextFlow();
        wordDisplay.setTextAlignment(TextAlignment.LEFT);
        wordDisplay.setPadding(new Insets(20, 24, 20, 24));
        wordDisplay.setLineSpacing(6);
        wordDisplay.setStyle("-fx-background-color: transparent;");

        ScrollPane scroll = new ScrollPane(wordDisplay);
        scroll.setFitToWidth(true);
        scroll.setPrefHeight(130);
        scroll.setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        scroll.setVbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        scroll.setStyle(STYLE_SCROLL_PANE);

        VBox box = new VBox(scroll);
        box.setStyle(STYLE_WORD_SECTION);
        return box;
    }

    // ─── Input Row ────────────────────────────────────────────────────────────
    private HBox buildInputRow() {
        inputField = new TextField();
        inputField.setPromptText("start typing...");
        inputField.setStyle(STYLE_INPUT_NORMAL);
        HBox.setHgrow(inputField, Priority.ALWAYS);

        Button resetBtn = new Button("↺ reset");
        resetBtn.setStyle(STYLE_RESET_BTN);
        resetBtn.setOnAction(e -> resetGame());

        HBox row = new HBox(10, inputField, resetBtn);
        row.setAlignment(Pos.CENTER);
        return row;
    }

    // ─── Result Panel ─────────────────────────────────────────────────────────
    private VBox buildResultPanel() {
        VBox panel = new VBox(20);
        panel.setAlignment(Pos.CENTER);
        panel.setMaxWidth(440);
        panel.setStyle(STYLE_RESULT_PANEL);
        panel.setEffect(new DropShadow(40, Color.web(ACCENT, 0.4)));
        return panel;
    }

    private void showResults() {
        double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;
        int wpm = (int) ((correctWords / elapsed) * 60);
        int acc = totalTyped == 0 ? 100 : (int) ((correctChars * 100.0) / totalTyped);

        resultPanel.getChildren().clear();

        Label done = new Label("time's up! ⌨");
        done.setStyle(STYLE_RESULT_TITLE);

        String gradeText;
        String gradeColor;
        if      (wpm >= 80 && acc >= 95) { gradeText = "S  legendary";  gradeColor = YELLOW;    }
        else if (wpm >= 60 && acc >= 90) { gradeText = "A  excellent";  gradeColor = GREEN;     }
        else if (wpm >= 40 && acc >= 80) { gradeText = "B  good job";   gradeColor = "#38bdf8"; }
        else if (wpm >= 20)              { gradeText = "C  keep going"; gradeColor = YELLOW;    }
        else                             { gradeText = "D  practice!";  gradeColor = RED;       }

        Label gradeLabel = new Label(gradeText);
        gradeLabel.setStyle(
                "-fx-text-fill: "        + gradeColor + ";" +
                "-fx-font-size: 22px;"   +
                "-fx-font-family: 'Courier New';" +
                "-fx-font-weight: bold;");

        Button playAgain = new Button("play again →");
        playAgain.setStyle(STYLE_PLAY_AGAIN);
        playAgain.setOnAction(e -> { resultPanel.setVisible(false); resetGame(); });

        resultPanel.getChildren().addAll(
                done, gradeLabel,
                makeResultStat(wpm + " wpm", "words per minute"),
                makeResultStat(acc + "%",    "accuracy"),
                makeResultStat(String.valueOf(correctWords), "correct words"),
                playAgain);

        resultPanel.setVisible(true);
        resultPanel.setOpacity(0);
        resultPanel.setScaleX(0.85);
        resultPanel.setScaleY(0.85);

        new Timeline(
                new KeyFrame(Duration.ZERO,
                        new KeyValue(resultPanel.opacityProperty(), 0),
                        new KeyValue(resultPanel.scaleXProperty(), 0.85),
                        new KeyValue(resultPanel.scaleYProperty(), 0.85)),
                new KeyFrame(Duration.millis(300),
                        new KeyValue(resultPanel.opacityProperty(), 1.0, Interpolator.EASE_OUT),
                        new KeyValue(resultPanel.scaleXProperty(),  1.0, Interpolator.EASE_OUT),
                        new KeyValue(resultPanel.scaleYProperty(),  1.0, Interpolator.EASE_OUT))
        ).play();
    }

    private VBox makeResultStat(String value, String label) {
        Label v = new Label(value);
        v.setStyle(STYLE_RESULT_VALUE);
        Label l = new Label(label);
        l.setStyle(STYLE_RESULT_SUBLABEL);
        VBox box = new VBox(2, v, l);
        box.setAlignment(Pos.CENTER);
        return box;
    }

    // ─── Game Logic ───────────────────────────────────────────────────────────
    private void generateWords() {
        String[] pool = WORD_POOLS[difficulty];
        List<String> list = new ArrayList<>();
        for (int i = 0; i < 60; i++)
            list.add(pool[random.nextInt(pool.length)]);
        currentWords     = list.toArray(new String[0]);
        currentWordIndex = 0;
        renderWords(null);
    }

    private void renderWords(String typed) {
        wordDisplay.getChildren().clear();
        for (int i = 0; i < currentWords.length; i++) {
            if (i > 0) {
                Text space = new Text(" ");
                space.setFill(Color.web(TEXT_DIM));
                space.setFont(Font.font("Courier New", 20));
                wordDisplay.getChildren().add(space);
            }
            String word = currentWords[i];
            for (int c = 0; c < word.length(); c++) {
                Text ch = new Text(String.valueOf(word.charAt(c)));
                ch.setFont(Font.font("Courier New", FontWeight.NORMAL, 20));

                if (i < currentWordIndex) {
                    ch.setFill(Color.web(GREEN, 0.6));

                } else if (i == currentWordIndex && typed != null) {
                    if (c < typed.length()) {
                        boolean ok = typed.charAt(c) == word.charAt(c);
                        ch.setFill(Color.web(ok ? GREEN : RED));
                        if (!ok) ch.setEffect(new DropShadow(8, Color.web(RED, 0.5)));
                    } else if (c == typed.length()) {
                        ch.setFill(Color.web(CURSOR_COL));
                        ch.setEffect(new DropShadow(10, Color.web(CURSOR_COL, 0.8)));
                        FadeTransition ft = new FadeTransition(Duration.millis(500), ch);
                        ft.setFromValue(1.0); ft.setToValue(0.4);
                        ft.setAutoReverse(true); ft.setCycleCount(2);
                        ft.play();
                    } else {
                        ch.setFill(Color.web(TEXT_MAIN, 0.5));
                    }

                } else if (i == currentWordIndex) {
                    ch.setFill(c == 0 ? Color.web(CURSOR_COL) : Color.web(TEXT_MAIN));
                    if (c == 0) ch.setEffect(new DropShadow(6, Color.web(CURSOR_COL)));

                } else {
                    ch.setFill(Color.web(TEXT_DIM));
                }

                wordDisplay.getChildren().add(ch);
            }
        }
    }

    private void setupInputHandler() {
        inputField.textProperty().addListener((obs, oldVal, newVal) -> {
            if (!gameRunning && !newVal.isEmpty()) startGame();
            if (!gameRunning) return;

            if (newVal.endsWith(" ")) {
                checkWord(newVal.trim());
                inputField.clear();
                return;
            }
            renderWords(newVal);
            updateStats();
        });

        inputField.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.ENTER) {
                String typed = inputField.getText().trim();
                if (!typed.isEmpty()) { checkWord(typed); inputField.clear(); }
            }
        });
    }

    private void checkWord(String typed) {
        if (currentWordIndex >= currentWords.length) return;
        String expected = currentWords[currentWordIndex];
        totalTyped += typed.length();

        int correct = 0;
        for (int i = 0; i < Math.min(typed.length(), expected.length()); i++)
            if (typed.charAt(i) == expected.charAt(i)) correct++;
        correctChars += correct;

        boolean isCorrect = typed.equals(expected);
        if (isCorrect) correctWords++;
        flashInput(isCorrect);

        currentWordIndex++;
        if (currentWordIndex >= currentWords.length - 10) extendWords();
        renderWords(null);
        updateStats();
    }

    private void flashInput(boolean correct) {
        inputField.setStyle(correct ? STYLE_INPUT_CORRECT : STYLE_INPUT_WRONG);
        new Timeline(new KeyFrame(Duration.millis(200),
                e -> inputField.setStyle(STYLE_INPUT_ACTIVE))).play();
    }

    private void extendWords() {
        String[] pool = WORD_POOLS[difficulty];
        List<String> list = new ArrayList<>(Arrays.asList(currentWords));
        for (int i = 0; i < 20; i++)
            list.add(pool[random.nextInt(pool.length)]);
        currentWords = list.toArray(new String[0]);
    }

    private void startGame() {
        gameRunning = true;
        gameStarted = true;
        startTime   = System.currentTimeMillis();
        timeLeft    = timeLimit;
        statusLabel.setText("typing...");
        inputField.setStyle(STYLE_INPUT_ACTIVE);

        countdownTimer = new Timeline(new KeyFrame(Duration.seconds(1), e -> {
            timeLeft--;
            timerLabel.setText(String.valueOf(timeLeft));
            timerBar.setProgress((double) timeLeft / timeLimit);
            if (timeLeft <= 5)  timerLabel.setStyle(STYLE_TIMER_LOW);
            if (timeLeft <= 0)  endGame();
            else                updateStats();
        }));
        countdownTimer.setCycleCount(timeLimit);
        countdownTimer.play();
    }

    private void endGame() {
        gameRunning = false;
        if (countdownTimer != null) countdownTimer.stop();
        inputField.setDisable(true);
        showResults();
    }

    private void resetGame() {
        if (countdownTimer != null) countdownTimer.stop();
        gameRunning      = false;
        gameStarted      = false;
        currentWordIndex = 0;
        correctChars     = 0;
        totalTyped       = 0;
        correctWords     = 0;
        timeLeft         = timeLimit;

        timerLabel.setText(String.valueOf(timeLimit));
        timerLabel.setStyle(STYLE_STAT_VALUE);
        wpmLabel.setText("0");
        accuracyLabel.setText("100%");
        scoreLabel.setText("0");
        timerBar.setProgress(1.0);
        statusLabel.setText("press any key to start");

        inputField.setDisable(false);
        inputField.clear();
        inputField.setStyle(STYLE_INPUT_NORMAL);

        generateWords();
        inputField.requestFocus();
    }

    private void updateStats() {
        if (!gameStarted) return;
        double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;
        if (elapsed > 0)
            wpmLabel.setText(String.valueOf((int) ((correctWords / elapsed) * 60)));
        int acc = totalTyped == 0 ? 100 : (int) ((correctChars * 100.0) / totalTyped);
        accuracyLabel.setText(acc + "%");
        scoreLabel.setText(String.valueOf(correctWords));
    }

    public static void main(String[] args) {
        launch(args);
    }
}