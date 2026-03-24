using System;
using System.Drawing;
using System.Windows.Forms;

namespace ArrayApp
{
    public partial class Form1 : Form
    {
        // Глобальные переменные
        private int[]? a;
        private int[]? sortedArray;
        private int n;

        // Элементы управления
        private Label? label1;
        private Label? label2;
        private Label? label3;
        private TextBox? textBox1;
        private TextBox? textBox2;
        private TextBox? textBox3;
        private TextBox? textBox4;
        private Button? button1;
        private Button? button2;
        private Button? button3;

        public Form1()
        {
            InitializeComponent();

            this.BackgroundImage = Image.FromFile("mememe.png");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка основной формы
            this.Text = "Максимальный среди четных элементов массива + сортировка";
            this.Size = new Size(500, 500);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.BackColor = Color.LightBlue;

            // Label "Количество элементов"
            label1 = new Label();
            label1.Text = "Количество элементов:";
            label1.Location = new Point(20, 20);
            label1.Size = new Size(150, 20);
            label1.Font = new Font("Arial", 9, FontStyle.Regular);
            label1.BackColor = Color.Transparent;
            this.Controls.Add(label1);

            // TextBox для ввода количества элементов
            textBox1 = new TextBox();
            textBox1.Location = new Point(180, 20);
            textBox1.Size = new Size(100, 20);
            textBox1.Font = new Font("Arial", 9, FontStyle.Regular);
            this.Controls.Add(textBox1);

            // Кнопка "Очистить"
            button1 = new Button();
            button1.Text = "Очистить";
            button1.Location = new Point(300, 20);
            button1.Size = new Size(80, 25);
            button1.BackColor = Color.LightCoral;
            button1.Font = new Font("Arial", 8, FontStyle.Bold);
            button1.Click += button1_Click;
            this.Controls.Add(button1);

            // Кнопка "Заполнить"
            button2 = new Button();
            button2.Text = "Заполнить";
            button2.Location = new Point(390, 20);
            button2.Size = new Size(80, 25);
            button2.BackColor = Color.LightGreen;
            button2.Font = new Font("Arial", 8, FontStyle.Bold);
            button2.Click += button2_Click;
            this.Controls.Add(button2);

            // Label "Исходный массив"
            label2 = new Label();
            label2.Text = "Исходный массив:";
            label2.Location = new Point(20, 60);
            label2.Size = new Size(120, 20);
            label2.Font = new Font("Arial", 9, FontStyle.Bold);
            label2.BackColor = Color.Transparent;
            this.Controls.Add(label2);

            // Многострочное TextBox для вывода исходного массива
            textBox2 = new TextBox();
            textBox2.Location = new Point(20, 85);
            textBox2.Size = new Size(450, 100);
            textBox2.Multiline = true;
            textBox2.ScrollBars = ScrollBars.Vertical;
            textBox2.Font = new Font("Arial", 9, FontStyle.Regular);
            textBox2.BackColor = Color.White;
            textBox2.ReadOnly = true; // Запрещаем ввод
            this.Controls.Add(textBox2);

            // Label "Массив после сортировки"
            label3 = new Label();
            label3.Text = "Массив после сортировки:";
            label3.Location = new Point(20, 200);
            label3.Size = new Size(200, 20);
            label3.Font = new Font("Arial", 9, FontStyle.Bold);
            label3.BackColor = Color.Transparent;
            this.Controls.Add(label3);

            // Многострочное TextBox для вывода отсортированного массива
            textBox3 = new TextBox();
            textBox3.Location = new Point(20, 225);
            textBox3.Size = new Size(450, 100);
            textBox3.Multiline = true;
            textBox3.ScrollBars = ScrollBars.Vertical;
            textBox3.Font = new Font("Arial", 9, FontStyle.Regular);
            textBox3.BackColor = Color.LightYellow;
            textBox3.ReadOnly = true; // Запрещаем ввод
            this.Controls.Add(textBox3);

            // Label "Максимальный среди четных элементов массива"
            Label label4 = new Label();
            label4.Text = "Максимальный среди четных элементов:";
            label4.Location = new Point(20, 340);
            label4.Size = new Size(250, 20);
            label4.Font = new Font("Arial", 9, FontStyle.Regular);
            label4.BackColor = Color.Transparent;
            this.Controls.Add(label4);

            // TextBox для вывода результата
            textBox4 = new TextBox();
            textBox4.Location = new Point(280, 340);
            textBox4.Size = new Size(100, 20);
            textBox4.ReadOnly = true; // Запрещаем ввод
            textBox4.Font = new Font("Arial", 9, FontStyle.Bold);
            textBox4.ForeColor = Color.DarkRed;
            textBox4.BackColor = Color.LightCyan;
            this.Controls.Add(textBox4);

            // Кнопка "Найти максимальный среди четных"
            button3 = new Button();
            button3.Text = "Найти максимальный среди четных";
            button3.Location = new Point(150, 380);
            button3.Size = new Size(250, 30);
            button3.BackColor = Color.Gold;
            button3.Font = new Font("Arial", 9, FontStyle.Bold);
            button3.Click += button3_Click;
            this.Controls.Add(button3);
        }

        // Кнопка "Очистить"
        private void button1_Click(object? sender, EventArgs e)
        {
            textBox2?.Clear();
            textBox3?.Clear();
            textBox4?.Clear();
        }

        
        private void button2_Click(object? sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(textBox1?.Text))
                {
                    MessageBox.Show("Введите количество элементов!", "Ошибка", 
                                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                n = Convert.ToInt32(textBox1.Text);
                a = new int[n];
                Random rand = new Random();
                
                textBox2!.Clear();
                textBox3!.Clear();
                textBox4!.Clear();
                
                
                for (int i = 0; i < n; ++i)
                {
                    a[i] = rand.Next(1, 101); 
                    textBox2.Text += Convert.ToString(a[i]) + (char)13 + (char)10;
                }

                sortedArray = new int[n];
                Array.Copy(a, sortedArray, n);
                
                // Сортировка методом выбора
                SelectionSort(sortedArray);
                
                // Выводим отсортированный массив
                for (int i = 0; i < n; ++i)
                {
                    textBox3.Text += Convert.ToString(sortedArray[i]) + (char)13 + (char)10;
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Введите корректное число!", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBox1?.Focus();
                textBox1?.SelectAll();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        // Метод сортировки выбором
        private void SelectionSort(int[] array)
        {
            int n = array.Length;
            
            for (int i = 0; i < n - 1; i++)
            {
                
                int minIndex = i;
                for (int j = i + 1; j < n; j++)
                {
                    if (array[j] < array[minIndex])
                    {
                        minIndex = j;
                    }
                }
                
                
                int temp = array[minIndex];
                array[minIndex] = array[i];
                array[i] = temp;
            }
        }

        // Кнопка "Найти максимальный среди четных"
        private void button3_Click(object? sender, EventArgs e)
        {
            try
            {
                if (a == null || a.Length == 0)
                {
                    MessageBox.Show("Сначала заполните массив!", "Ошибка", 
                                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                int maxEven = int.MinValue; // Начальное значение - минимальное возможное
                bool foundEven = false;

                for (int i = 0; i < n; ++i)
                {
                    if (a[i] % 2 == 0) // Если элемент четный
                    {
                        if (a[i] > maxEven)
                        {
                            maxEven = a[i];
                            foundEven = true;
                        }
                    }
                }

                if (foundEven)
                {
                    textBox4!.Text = Convert.ToString(maxEven);
                }
                else
                {
                    textBox4!.Text = "Четных элементов нет";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка: {ex.Message}", "Ошибка", 
                              MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }

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