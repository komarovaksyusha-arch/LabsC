using System;
using System.Drawing;
using System.Windows.Forms;

namespace SumDigitsApp
{
    public partial class Form1 : Form
    {
        private Label? labelTitle;
        private Label? labelInput;
        private TextBox? textBox1;
        private TextBox? textBox2;
        private Button? button1;
        private Label? labelResult;

        public Form1()
        {
            InitializeComponent();

            this.BackgroundImage = Image.FromFile("з.jpg");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка основной формы
            this.Text = "Сумма цифр натурального числа";
            this.Size = new Size(400, 250);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.BackColor = Color.LightBlue;

            // Заголовок
            labelTitle = new Label();
            labelTitle.Text = "Сумма цифр натурального числа";
            labelTitle.Location = new Point(20, 20);
            labelTitle.Size = new Size(350, 25);
            labelTitle.Font = new Font("Arial", 12, FontStyle.Bold);
            labelTitle.ForeColor = Color.White;
            labelTitle.TextAlign = ContentAlignment.MiddleCenter;
            labelTitle.BackColor = Color.Transparent;
            this.Controls.Add(labelTitle);

            // Label для ввода числа
            labelInput = new Label();
            labelInput.Text = "Введите число:";
            labelInput.Location = new Point(20, 60);
            labelInput.Size = new Size(100, 20);
            labelInput.Font = new Font("Arial", 9, FontStyle.Regular);
            labelInput.ForeColor = Color.White;
            labelInput.BackColor = Color.Transparent;
            this.Controls.Add(labelInput);

            // TextBox для ввода числа
            textBox1 = new TextBox();
            textBox1.Location = new Point(130, 60);
            textBox1.Size = new Size(200, 20);
            textBox1.Font = new Font("Arial", 9, FontStyle.Regular);
            textBox1.KeyPress += textBox1_KeyPress; // Обработчик ввода только цифр
            this.Controls.Add(textBox1);

            // Кнопка вычисления
            button1 = new Button();
            button1.Text = "Найти сумму цифр";
            button1.Location = new Point(130, 100);
            button1.Size = new Size(140, 30);
            button1.BackColor = Color.LightGreen;
            button1.Font = new Font("Arial", 9, FontStyle.Bold);
            button1.Click += button1_Click;
            this.Controls.Add(button1);

            // Label для результата
            labelResult = new Label();
            labelResult.Text = "Сумма цифр числа:";
            labelResult.Location = new Point(20, 150);
            labelResult.Size = new Size(150, 20);
            labelResult.Font = new Font("Arial", 9, FontStyle.Regular);
            labelResult.BackColor = Color.Transparent;
            this.Controls.Add(labelResult);

            // TextBox для результата
            textBox2 = new TextBox();
            textBox2.Location = new Point(180, 150);
            textBox2.Size = new Size(150, 20);
            textBox2.ReadOnly = true;
            textBox2.Font = new Font("Arial", 9, FontStyle.Bold);
            textBox2.ForeColor = Color.DarkRed;
            textBox2.BackColor = Color.LightYellow;
            this.Controls.Add(textBox2);
        }

        private void button1_Click(object? sender, EventArgs e)
        {
            try
            {
                // Проверяем, что поле не пустое
                if (string.IsNullOrEmpty(textBox1?.Text))
                {
                    MessageBox.Show("Пожалуйста, введите число!", "Ошибка ввода", 
                                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                int n = Convert.ToInt32(textBox1.Text);
                int s = 0;
                
                // Вычисляем сумму цифр числа
                while (n != 0)
                {
                    s = s + n % 10;  // Добавляем последнюю цифру
                    n = n / 10;      // Убираем последнюю цифру
                }
                
                textBox2!.Text = Convert.ToString(s);
            }
            catch (FormatException)
            {
                MessageBox.Show("Пожалуйста, введите корректное число!", "Ошибка ввода", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBox1?.Focus();
                textBox1?.SelectAll();
            }
            catch (OverflowException)
            {
                MessageBox.Show("Число слишком большое!", "Ошибка ввода", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBox1?.Focus();
                textBox1?.SelectAll();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Произошла ошибка: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void textBox1_KeyPress(object? sender, KeyPressEventArgs e)
        {
            // Разрешаем только цифры и управляющие клавиши (Backspace, Delete и т.д.)
            if (!(e.KeyChar >= '0' && e.KeyChar <= '9') && !char.IsControl(e.KeyChar))
            {
                e.Handled = true; // Игнорируем ввод
            }
        }
    }

    // Класс Program для запуска приложения
    internal static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}