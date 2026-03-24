using System;
using System.Drawing;
using System.Windows.Forms;

namespace TrigonometryApp
{
    public partial class Form1 : Form
    {
        private TextBox? textBox1;
        private TextBox? textBox2;
        private Button? button1;
        private Label? label1;
        private Label? label2;
        private Label? labelFormula;

        public Form1()
        {
            InitializeComponent();
            
            this.BackgroundImage = Image.FromFile("meow.jpg");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка основной формы
            this.Text = "Вычисление тригонометрической функции";
            this.Size = new Size(450, 300);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;

            // Сделаем фон немного темнее для лучшей читаемости
            this.BackColor = Color.LightBlue;

            // Label с формулой
            labelFormula = new Label();
            labelFormula.Text = "z₁ = sin(π/2 + 3α) / (1 - sin(3α - π))";
            labelFormula.Location = new Point(20, 20);
            labelFormula.Size = new Size(400, 25);
            labelFormula.Font = new Font("Arial", 10, FontStyle.Bold);
            labelFormula.ForeColor = Color.White;
            labelFormula.BackColor = Color.Transparent;
            this.Controls.Add(labelFormula);

            // Label для ввода alpha
            label1 = new Label();
            label1.Text = "Введите значение α (рад):";
            label1.Location = new Point(20, 60);
            label1.Size = new Size(180, 20);
            label1.ForeColor = Color.White;
            label1.BackColor = Color.Transparent;
            this.Controls.Add(label1);

            // TextBox для ввода alpha
            textBox1 = new TextBox();
            textBox1.Location = new Point(200, 60);
            textBox1.Size = new Size(200, 20);
            textBox1.ForeColor = Color.Blue;
            textBox1.BackColor = Color.LightYellow;
            this.Controls.Add(textBox1);

            // Кнопка вычисления
            button1 = new Button();
            button1.Text = "Вычислить";
            button1.Location = new Point(20, 100);
            button1.Size = new Size(100, 30);
            button1.BackColor = Color.LightGreen;
            button1.ForeColor = Color.DarkRed;
            button1.Font = new Font("Arial", 9, FontStyle.Bold);
            button1.Click += button1_Click;
            this.Controls.Add(button1);

            // Label для результата
            label2 = new Label();
            label2.Text = "Результат z₁:";
            label2.Location = new Point(20, 150);
            label2.Size = new Size(120, 20);
            label2.ForeColor = Color.White;
            label2.BackColor = Color.Transparent;
            this.Controls.Add(label2);

            // TextBox для результата
            textBox2 = new TextBox();
            textBox2.Location = new Point(150, 150);
            textBox2.Size = new Size(250, 20);
            textBox2.ReadOnly = true;
            textBox2.ForeColor = Color.DarkGreen;
            textBox2.BackColor = Color.LightCyan;
            textBox2.Font = new Font("Arial", 9, FontStyle.Bold);
            this.Controls.Add(textBox2);
        }

        private void button1_Click(object? sender, EventArgs e)
        {
            try
            {
                // Получаем значение alpha из текстового поля
                double a = Convert.ToDouble(textBox1?.Text);
                
                // Вычисляем числитель: sin(π/2 + 3α)
                double numerator = Math.Sin(Math.PI/2 + 3 * a);
                
                // Вычисляем знаменатель: 1 - sin(3α - π)
                double denominator = 1 - Math.Sin(3 * a - Math.PI);
                
                // Проверяем, чтобы знаменатель не был равен нулю
                if (Math.Abs(denominator) < 1e-10)
                {
                    textBox2!.Text = "Ошибка: знаменатель равен нулю!";
                    return;
                }
                
                // Вычисляем результат
                double z = numerator / denominator;
                
                // Выводим результат
                textBox2!.Text = z.ToString("F6");
            }
            catch (FormatException)
            {
                MessageBox.Show("Пожалуйста, введите корректное числовое значение для α.", 
                              "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBox1?.Focus();
                textBox1?.SelectAll();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Произошла ошибка: {ex.Message}", 
                              "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
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