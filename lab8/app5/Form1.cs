using System;
using System.Drawing;
using System.Windows.Forms;

namespace TextAnalyzerApp
{
    public partial class MainForm : Form
    {
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private Button button1;
        private Label label1;
        private Label label2;
        private Label label3;

        public MainForm()
        {
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            button1 = new Button();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            
            InitializeComponent();

            this.BackgroundImage = Image.FromFile("pim.jpg");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка формы
            this.Text = "Анализатор текста";
            this.Size = new Size(600, 500);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.Padding = new Padding(10);

            // Создание и настройка элементов управления
            label1.Text = "Исходный текст:";
            label1.Location = new Point(10, 10);
            label1.Size = new Size(150, 20);
            label1.Font = new Font("Arial", 9, FontStyle.Bold);

            textBox1.Location = new Point(10, 35);
            textBox1.Size = new Size(560, 100);
            textBox1.Multiline = true;
            textBox1.ScrollBars = ScrollBars.Vertical;
            textBox1.Font = new Font("Arial", 9);

            label2.Text = "Искомое слово:";
            label2.Location = new Point(10, 150);
            label2.Size = new Size(150, 20);
            label2.Font = new Font("Arial", 9, FontStyle.Bold);

            textBox2.Location = new Point(10, 175);
            textBox2.Size = new Size(560, 25);
            textBox2.Font = new Font("Arial", 9);

            button1.Text = "Анализировать текст";
            button1.Location = new Point(10, 210);
            button1.Size = new Size(150, 30);
            button1.Font = new Font("Arial", 9, FontStyle.Bold);
            button1.BackColor = Color.LightBlue;

            label3.Text = "Результат:";
            label3.Location = new Point(10, 250);
            label3.Size = new Size(150, 20);
            label3.Font = new Font("Arial", 9, FontStyle.Bold);

            textBox3.Location = new Point(10, 275);
            textBox3.Size = new Size(560, 150);
            textBox3.Multiline = true;
            textBox3.ScrollBars = ScrollBars.Vertical;
            textBox3.ReadOnly = true;
            textBox3.Font = new Font("Arial", 9);

            // Добавление элементов на форму
            this.Controls.AddRange(new Control[] {
                label1, textBox1, label2, textBox2,
                button1, label3, textBox3
            });

            // Подписка на события
            button1.Click += Button1_Click;
            textBox1.TextChanged += ValidateInputs;
            textBox2.TextChanged += ValidateInputs;
        }

        private void ValidateInputs(object? sender, EventArgs e)
        {
            // Проверка на минимальное количество символов (3 символа)
            bool hasMinChars = textBox1.Text.Trim().Length >= 3 && 
                              textBox2.Text.Trim().Length >= 3;
            
            button1.Enabled = hasMinChars;
            
            if (!hasMinChars)
            {
                button1.BackColor = Color.LightGray;
                button1.Text = "Введите минимум 3 символа";
            }
            else
            {
                button1.BackColor = Color.LightBlue;
                button1.Text = "Анализировать текст";
            }
        }

        private void Button1_Click(object? sender, EventArgs e)
        {
            try
            {
                // Обработка пустых полей
                if (string.IsNullOrWhiteSpace(textBox1.Text))
                {
                    MessageBox.Show("Поле исходного текста не может быть пустым!", 
                                  "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                if (string.IsNullOrWhiteSpace(textBox2.Text))
                {
                    MessageBox.Show("Поле искомого слова не может быть пустым!", 
                                  "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Проверка минимальной длины
                if (textBox1.Text.Trim().Length < 3 || textBox2.Text.Trim().Length < 3)
                {
                    MessageBox.Show("Каждое поле должно содержать минимум 3 символа!", 
                                  "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Анализ текста
                string result = AnalyzeText(textBox1.Text, textBox2.Text);
                textBox3.Text = result;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Произошла ошибка: {ex.Message}", 
                              "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private string AnalyzeText(string text, string searchWord)
        {
            // Разделение текста на предложения
            char[] sentenceSeparators = { '.', '!', '?' };
            string[] sentences = text.Split(sentenceSeparators, StringSplitOptions.RemoveEmptyEntries);

            string result = "";
            
            foreach (string sentence in sentences)
            {
                if (string.IsNullOrWhiteSpace(sentence))
                    continue;

                string trimmedSentence = sentence.Trim();
                if (trimmedSentence.Length == 0)
                    continue;

                // Подсчет вхождений слова в предложении
                int wordCount = CountWordOccurrences(trimmedSentence, searchWord);
                
                // Добавление предложения и количества в результат
                result += $"{trimmedSentence} [{wordCount}]{GetSentenceEnding(text, sentences, sentence)}{Environment.NewLine}";
            }

            return result.TrimEnd();
        }

        private int CountWordOccurrences(string sentence, string searchWord)
        {
            int count = 0;
            string[] words = sentence.Split(new char[] { ' ', ',', ';', ':', '-', '(', ')', '[', ']', '{', '}', '"', '\'' }, 
                                          StringSplitOptions.RemoveEmptyEntries);

            foreach (string word in words)
            {
                // Сравнение без учета регистра
                if (string.Equals(word.Trim(), searchWord.Trim(), StringComparison.OrdinalIgnoreCase))
                {
                    count++;
                }
            }

            return count;
        }

        private string GetSentenceEnding(string originalText, string[] sentences, string currentSentence)
        {
            // Восстановление знака препинания в конце предложения
            int sentenceStart = originalText.IndexOf(currentSentence);
            if (sentenceStart >= 0 && sentenceStart + currentSentence.Length < originalText.Length)
            {
                char nextChar = originalText[sentenceStart + currentSentence.Length];
                if (nextChar == '.' || nextChar == '!' || nextChar == '?')
                {
                    return nextChar.ToString();
                }
            }
            return ".";
        }
    }

    // Класс Program для запуска приложения
    public static class Program
    {
        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}