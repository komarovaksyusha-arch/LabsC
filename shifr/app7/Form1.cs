using System;
using System.Drawing;
using System.Windows.Forms;

namespace MagicSquareCryptoApp
{
    public partial class MainForm : Form
    {
        private Button encryptButton = new Button();
        private Button decryptButton = new Button();
        private TextBox inputTextBox = new TextBox();
        private TextBox outputTextBox = new TextBox();
        private TextBox sizeTextBox = new TextBox();
        private Label inputLabel = new Label();
        private Label outputLabel = new Label();
        private Label sizeLabel = new Label();
        private Label titleLabel = new Label();

        public MainForm()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            // Настройка формы
            this.Text = "Шифрование магическими квадратами";
            this.Size = new Size(650, 600);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.Padding = new Padding(10);

            // Создание и настройка элементов управления
            titleLabel.Text = "ШИФРОВАНИЕ МАГИЧЕСКИМИ КВАДРАТАМИ";
            titleLabel.Location = new Point(10, 10);
            titleLabel.Size = new Size(600, 25);
            titleLabel.Font = new Font("Arial", 12, FontStyle.Bold);
            titleLabel.TextAlign = ContentAlignment.MiddleCenter;

            inputLabel.Text = "Введите текст:";
            inputLabel.Location = new Point(10, 50);
            inputLabel.Size = new Size(150, 20);
            inputLabel.Font = new Font("Arial", 9, FontStyle.Bold);

            inputTextBox.Location = new Point(10, 75);
            inputTextBox.Size = new Size(600, 80);
            inputTextBox.Multiline = true;
            inputTextBox.ScrollBars = ScrollBars.Vertical;
            inputTextBox.Font = new Font("Arial", 9);

            sizeLabel.Text = "Размер квадрата (3, 4, 5...):";
            sizeLabel.Location = new Point(10, 170);
            sizeLabel.Size = new Size(200, 20);
            sizeLabel.Font = new Font("Arial", 9, FontStyle.Bold);

            sizeTextBox.Location = new Point(220, 170);
            sizeTextBox.Size = new Size(100, 25);
            sizeTextBox.Font = new Font("Arial", 9);

            encryptButton.Text = "Зашифровать";
            encryptButton.Location = new Point(10, 210);
            encryptButton.Size = new Size(120, 30);
            encryptButton.Font = new Font("Arial", 9, FontStyle.Bold);
            encryptButton.BackColor = Color.LightGreen;

            decryptButton.Text = "Расшифровать";
            decryptButton.Location = new Point(140, 210);
            decryptButton.Size = new Size(120, 30);
            decryptButton.Font = new Font("Arial", 9, FontStyle.Bold);
            decryptButton.BackColor = Color.LightBlue;

            outputLabel.Text = "Результат:";
            outputLabel.Location = new Point(10, 260);
            outputLabel.Size = new Size(150, 20);
            outputLabel.Font = new Font("Arial", 9, FontStyle.Bold);

            outputTextBox.Location = new Point(10, 285);
            outputTextBox.Size = new Size(600, 250);
            outputTextBox.Multiline = true;
            outputTextBox.ScrollBars = ScrollBars.Vertical;
            outputTextBox.ReadOnly = true;
            outputTextBox.Font = new Font("Arial", 9);

            // Добавление элементов на форму
            this.Controls.AddRange(new Control[] {
                titleLabel, inputLabel, inputTextBox, sizeLabel, sizeTextBox,
                encryptButton, decryptButton, outputLabel, outputTextBox
            });

            // Подписка на события
            encryptButton.Click += EncryptButton_Click;
            decryptButton.Click += DecryptButton_Click;
        }

                private void EncryptButton_Click(object? sender, EventArgs e)
        {
            try
            {
                string text = inputTextBox.Text.Trim();
                string sizeText = sizeTextBox.Text.Trim();

                // Проверка входных данных
                if (string.IsNullOrEmpty(text))
                {
                    MessageBox.Show("Введите текст для шифрования!", "Ошибка", 
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                if (string.IsNullOrEmpty(sizeText) || !int.TryParse(sizeText, out int size) || size < 3)
                {
                    MessageBox.Show("Введите корректный размер квадрата (целое число >= 3)!", "Ошибка", 
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Генерация магического квадрата и шифрование
                int[,] magicSquare = GenerateMagicSquare(size);
                string encryptedText = Encrypt(text, magicSquare);
                
                // Вывод результата с правильными переносами строк
                string result = $"МАГИЧЕСКИЙ КВАДРАТ {size}x{size}:\r\n\r\n" +
                            $"{MagicSquareToString(magicSquare)}\r\n" +
                            $"ИСХОДНЫЙ ТЕКСТ:\r\n{text}\r\n\r\n" +
                            $"ЗАШИФРОВАННЫЙ ТЕКСТ:\r\n{encryptedText}";
                
                outputTextBox.Text = result;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при шифровании: {ex.Message}", "Ошибка", 
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void DecryptButton_Click(object? sender, EventArgs e)
        {
            try
            {
                string text = inputTextBox.Text.Trim();
                string sizeText = sizeTextBox.Text.Trim();

                // Проверка входных данных
                if (string.IsNullOrEmpty(text))
                {
                    MessageBox.Show("Введите текст для дешифрования!", "Ошибка", 
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                if (string.IsNullOrEmpty(sizeText) || !int.TryParse(sizeText, out int size) || size < 3)
                {
                    MessageBox.Show("Введите корректный размер квадрата (целое число >= 3)!", "Ошибка", 
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Генерация магического квадрата и дешифрование
                int[,] magicSquare = GenerateMagicSquare(size);
                string decryptedText = Decrypt(text, magicSquare);
                
                // Вывод результата с правильными переносами строк
                string result = $"МАГИЧЕСКИЙ КВАДРАТ {size}x{size}:\r\n\r\n" +
                            $"{MagicSquareToString(magicSquare)}\r\n" +
                            $"ЗАШИФРОВАННЫЙ ТЕКСТ:\r\n{text}\r\n\r\n" +
                            $"РАСШИФРОВАННЫЙ ТЕКСТ:\r\n{decryptedText}";
                
                outputTextBox.Text = result;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при дешифровании: {ex.Message}", "Ошибка", 
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        static int[,] GenerateMagicSquare(int n)
        {
            if (n < 3)
                throw new ArgumentException("Размер квадрата должен быть не менее 3");

            int[,] square = new int[n, n];

            if (n % 2 == 1)
            {
                return GenerateOddMagicSquare(n);
            }
            else
            {
                return GenerateEvenMagicSquare(n);
            }
        }

        static int[,] GenerateOddMagicSquare(int n)
        {
            int[,] square = new int[n, n];
            int num = 1;
            int i = 0;
            int j = n / 2;

            while (num <= n * n)
            {
                square[i, j] = num++;
                int newi = (i - 1 + n) % n;
                int newj = (j + 1) % n;

                if (square[newi, newj] != 0)
                {
                    i = (i + 1) % n;
                }
                else
                {
                    i = newi;
                    j = newj;
                }
            }

            return square;
        }

        static int[,] GenerateEvenMagicSquare(int n)
        {
            int[,] square = new int[n, n];
            int num = 1;

            // Заполняем квадрат последовательными числами
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    square[i, j] = num++;
                }
            }

            // Простой метод для четных квадратов - транспонирование
            int[,] result = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    result[j, i] = square[i, j];
                }
            }

            return result;
        }

        static string Encrypt(string text, int[,] magicSquare)
        {
            int n = magicSquare.GetLength(0);
            int totalCells = n * n;
            
            // Дополняем текст пробелами до длины, кратной n*n
            while (text.Length % totalCells != 0)
            {
                text += " ";
            }

            char[] result = new char[text.Length];
            int textIndex = 0;

            // Обрабатываем текст блоками по n*n символов
            for (int block = 0; block < text.Length / totalCells; block++)
            {
                char[,] textBlock = new char[n, n];
                int blockStart = block * totalCells;

                // Заполняем блок текстом в порядке магического квадрата
                for (int num = 1; num <= totalCells; num++)
                {
                    var position = FindPosition(magicSquare, num);
                    if (position.i >= 0 && position.j >= 0)
                    {
                        textBlock[position.i, position.j] = text[blockStart + num - 1];
                    }
                }

                // Считываем блок по строкам для шифрования
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        result[textIndex++] = textBlock[i, j];
                    }
                }
            }

            return new string(result);
        }

        static string Decrypt(string text, int[,] magicSquare)
        {
            int n = magicSquare.GetLength(0);
            int totalCells = n * n;
            
            if (text.Length % totalCells != 0)
            {
                throw new ArgumentException("Длина текста должна быть кратной размеру квадрата в квадрате");
            }

            char[] result = new char[text.Length];
            int textIndex = 0;

            // Обрабатываем текст блоками по n*n символов
            for (int block = 0; block < text.Length / totalCells; block++)
            {
                char[,] textBlock = new char[n, n];
                int blockStart = block * totalCells;

                // Заполняем блок из зашифрованного текста (по строкам)
                int index = 0;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        textBlock[i, j] = text[blockStart + index++];
                    }
                }

                // Восстанавливаем оригинальный порядок с помощью магического квадрата
                for (int num = 1; num <= totalCells; num++)
                {
                    var position = FindPosition(magicSquare, num);
                    if (position.i >= 0 && position.j >= 0)
                    {
                        result[textIndex++] = textBlock[position.i, position.j];
                    }
                }
            }

            return new string(result).TrimEnd();
        }

        static (int i, int j) FindPosition(int[,] square, int number)
        {
            int n = square.GetLength(0);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (square[i, j] == number)
                    {
                        return (i, j);
                    }
                }
            }
            return (-1, -1);
        }

                static string MagicSquareToString(int[,] square)
        {
            int n = square.GetLength(0);
            string result = "";
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    result += $"{square[i, j],4}";
                }
                result += "\r\n"; // Заменяем \n на \r\n
            }
            
            return result;
        }
    }

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