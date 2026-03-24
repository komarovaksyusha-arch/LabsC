using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Drawing;

namespace EmailValidatorApp
{
    public partial class MainForm : Form
    {
        private Button button1;
        private Button button2;
        private TextBox textBox1;
        private OpenFileDialog openFileDialog1;
        private Label label1;

        public MainForm()
        {
            // Инициализация всех полей перед использованием
            button1 = new Button();
            button2 = new Button();
            textBox1 = new TextBox();
            openFileDialog1 = new OpenFileDialog();
            label1 = new Label();
            
            InitializeComponent();

            this.BackgroundImage = Image.FromFile("cheese.jpg");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка формы
            this.Text = "Валидатор email адресов";
            this.Size = new Size(500, 400);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.Padding = new Padding(10);

            // Настройка button1
            button1.Text = "Выбрать файл и проверить email";
            button1.Location = new Point(10, 10);
            button1.Size = new Size(200, 30);
            button1.Font = new Font("Arial", 9, FontStyle.Bold);
            button1.BackColor = Color.LightGreen;

            // Настройка button2
            button2.Text = "Очистить";
            button2.Location = new Point(220, 10);
            button2.Size = new Size(100, 30);
            button2.Font = new Font("Arial", 9);
            button2.BackColor = Color.LightCoral;

            // Настройка label1
            label1.Text = "Результат проверки:";
            label1.Location = new Point(10, 50);
            label1.Size = new Size(150, 20);
            label1.Font = new Font("Arial", 9, FontStyle.Bold);

            // Настройка textBox1
            textBox1.Location = new Point(10, 75);
            textBox1.Size = new Size(460, 250);
            textBox1.Multiline = true;
            textBox1.ScrollBars = ScrollBars.Vertical;
            textBox1.ReadOnly = false;
            textBox1.Font = new Font("Arial", 9);

            // Настройка openFileDialog1
            openFileDialog1.Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
            openFileDialog1.Title = "Выберите файл для проверки email адресов";

            // Добавление элементов на форму
            this.Controls.AddRange(new Control[] {
                button1, button2, label1, textBox1
            });

            // Подписка на события
            button1.Click += Button1_Click;
            button2.Click += Button2_Click;
        }

        private void Button1_Click(object? sender, EventArgs e)
        {
            try
            {
                // Диалог выбора файла
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    // Очистка textBox1 перед новой проверкой
                    textBox1.Clear();
                    
                    // Регулярное выражение для проверки email
                    string pattern = @"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$";
                    
                    int validEmails = 0;
                    int invalidEmails = 0;
                    int lineNumber = 0;

                    // Открытие выбранного файла
                    using (StreamReader f = new StreamReader(openFileDialog1.FileName))
                    {
                        string? s;
                        Regex r = new Regex(pattern);

                        // Чтение выбранного файла по строкам
                        while ((s = f.ReadLine()) != null)
                        {
                            lineNumber++;
                            string trimmedLine = s.Trim();

                            // Пропускаем пустые строки
                            if (string.IsNullOrEmpty(trimmedLine))
                                continue;

                            // Проверка email с помощью регулярного выражения
                            bool isValid = r.IsMatch(trimmedLine);

                            if (isValid)
                            {
                                validEmails++;
                                textBox1.AppendText($"✓ Строка {lineNumber}: '{trimmedLine}' - ВАЛИДНЫЙ email{Environment.NewLine}");
                            }
                            else
                            {
                                invalidEmails++;
                                textBox1.AppendText($"✗ Строка {lineNumber}: '{trimmedLine}' - НЕВАЛИДНЫЙ email{Environment.NewLine}");
                            }
                        }
                    }

                    // Добавляем итоговую статистику
                    textBox1.AppendText($"{Environment.NewLine}=== РЕЗУЛЬТАТ ПРОВЕРКИ ==={Environment.NewLine}");
                    textBox1.AppendText($"Всего строк обработано: {lineNumber}{Environment.NewLine}");
                    textBox1.AppendText($"Валидных email: {validEmails}{Environment.NewLine}");
                    textBox1.AppendText($"Невалидных email: {invalidEmails}{Environment.NewLine}");
                    textBox1.AppendText($"Файл: {openFileDialog1.FileName}{Environment.NewLine}");
                }
            }
            catch (FileNotFoundException ex)
            {
                MessageBox.Show($"Файл не найден: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (DirectoryNotFoundException ex)
            {
                MessageBox.Show($"Директория не найдена: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (IOException ex)
            {
                MessageBox.Show($"Ошибка ввода-вывода: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (UnauthorizedAccessException ex)
            {
                MessageBox.Show($"Нет доступа к файлу: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Произошла непредвиденная ошибка: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Button2_Click(object? sender, EventArgs e)
        {
            // Очистка textBox1
            textBox1.Clear();
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