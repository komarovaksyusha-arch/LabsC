using System;
using System.Drawing;
using System.Windows.Forms;

namespace MatrixShiftApp
{
    public partial class Form1 : Form
    {
        // Размеры матрицы и сама матрица
        private int m, n;
        private int[,]? A;

        // Элементы управления
        private Label? label1;
        private Label? label2;
        private Label? label4;
        private Label? label5;
        private Label? label7;
        private TextBox? textBox1;
        private TextBox? textBox2;
        private DataGridView? dataGridView1;
        private DataGridView? dataGridView2;
        private Button? button1;
        private Button? button2;
        private Button? button3;

        public Form1()
        {
            InitializeComponent();

            this.BackgroundImage = Image.FromFile("pimpum.jpg");
            this.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void InitializeComponent()
        {
            // Настройка основной формы
            this.Text = "Циклический сдвиг матрицы";
            this.Size = new Size(800, 600);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.LightBlue;

            // Надпись "m" (строки)
            label4 = new Label();
            label4.Text = "m (строки):";
            label4.Location = new Point(20, 20);
            label4.Size = new Size(70, 20);
            this.Controls.Add(label4);

            // Окно ввода m
            textBox1 = new TextBox();
            textBox1.Location = new Point(95, 20);
            textBox1.Size = new Size(50, 20);
            this.Controls.Add(textBox1);

            // Надпись "n" (столбцы)
            label5 = new Label();
            label5.Text = "n (столбцы):";
            label5.Location = new Point(150, 20);
            label5.Size = new Size(80, 20);
            this.Controls.Add(label5);

            // Окно ввода n
            textBox2 = new TextBox();
            textBox2.Location = new Point(235, 20);
            textBox2.Size = new Size(50, 20);
            this.Controls.Add(textBox2);

            // Кнопка "Создание матрицы"
            button1 = new Button();
            button1.Text = "Создание матрицы";
            button1.Location = new Point(300, 18);
            button1.Size = new Size(120, 25);
            button1.BackColor = Color.LightGreen;
            button1.Click += button1_Click;
            this.Controls.Add(button1);

            // Надпись "Исходная матрица А"
            label1 = new Label();
            label1.Text = "Исходная матрица А:";
            label1.Location = new Point(20, 60);
            label1.Size = new Size(120, 20);
            label1.Font = new Font("Arial", 9, FontStyle.Bold);
            this.Controls.Add(label1);

            // DataGridView для матрицы A
            dataGridView1 = new DataGridView();
            dataGridView1.Location = new Point(20, 85);
            dataGridView1.Size = new Size(350, 200);
            dataGridView1.BackgroundColor = Color.White;
            this.Controls.Add(dataGridView1);

            // Надпись "Матрица после сдвига"
            label2 = new Label();
            label2.Text = "Матрица после сдвига:";
            label2.Location = new Point(400, 60);
            label2.Size = new Size(140, 20);
            label2.Font = new Font("Arial", 9, FontStyle.Bold);
            this.Controls.Add(label2);

            // DataGridView для результата
            dataGridView2 = new DataGridView();
            dataGridView2.Location = new Point(400, 85);
            dataGridView2.Size = new Size(350, 200);
            dataGridView2.BackgroundColor = Color.LightYellow;
            this.Controls.Add(dataGridView2);

            // Кнопка "Проверка корректности ввода"
            button2 = new Button();
            button2.Text = "Проверка корректности ввода";
            button2.Location = new Point(20, 300);
            button2.Size = new Size(180, 30);
            button2.BackColor = Color.LightGoldenrodYellow;
            button2.Click += button2_Click;
            this.Controls.Add(button2);

            // Кнопка "Циклический сдвиг"
            button3 = new Button();
            button3.Text = "Циклический сдвиг";
            button3.Location = new Point(220, 300);
            button3.Size = new Size(150, 30);
            button3.BackColor = Color.Gold;
            button3.Click += button3_Click;
            this.Controls.Add(button3);

            // Надпись для сообщений об ошибках
            label7 = new Label();
            label7.Text = "";
            label7.Location = new Point(20, 350);
            label7.Size = new Size(500, 40);
            label7.ForeColor = Color.Red;
            label7.Font = new Font("Arial", 8, FontStyle.Regular);
            this.Controls.Add(label7);
        }

        // Кнопка "Создание матрицы"
        private void button1_Click(object? sender, EventArgs e)
        {
            try
            {
                m = Convert.ToInt32(textBox1?.Text);
                n = Convert.ToInt32(textBox2?.Text);

                if (m <= 0 || n <= 0)
                {
                    MessageBox.Show("Размеры матрицы должны быть положительными числами!", "Ошибка");
                    return;
                }

                A = new int[m, n];

                // Очистка DataGridView
                dataGridView1?.Columns.Clear();
                dataGridView1?.Rows.Clear();
                dataGridView2?.Columns.Clear();
                dataGridView2?.Rows.Clear();

                // Добавление столбцов
                AddColumns(n, dataGridView1!);
                AddColumns(n, dataGridView2!);

                // Добавление строк
                AddRows(m, dataGridView1!);
                AddRows(m, dataGridView2!);

                // Заполнение случайными числами
                Random rand = new Random();
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        A[i, j] = rand.Next(1, 100); // Случайные числа от 1 до 99
                        dataGridView1!.Rows[i].Cells[j].Value = A[i, j].ToString();
                    }
                }

                label7!.Text = "Матрица создана и заполнена случайными числами";
            }
            catch (FormatException)
            {
                MessageBox.Show("Введите корректные размеры матрицы!", "Ошибка ввода");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка: {ex.Message}", "Ошибка");
            }
        }

        // Добавление столбцов в DataGridView
        private void AddColumns(int n, DataGridView dgw)
        {
            for (int i = 0; i < n; i++)
            {
                DataGridViewColumn column = new DataGridViewTextBoxColumn();
                column.Width = 40;
                column.HeaderText = (i + 1).ToString();
                dgw.Columns.Add(column);
            }
        }

        // Добавление строк в DataGridView
        private void AddRows(int m, DataGridView dgw)
        {
            for (int i = 0; i < m; i++)
            {
                dgw.Rows.Add();
                dgw.Rows[i].HeaderCell.Value = (i + 1).ToString();
            }
        }

        // Кнопка "Проверка корректности ввода"
        private void button2_Click(object? sender, EventArgs e)
        {
            if (A == null || dataGridView1 == null)
            {
                MessageBox.Show("Сначала создайте матрицу!", "Ошибка");
                return;
            }

            string elem = "";

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    try
                    {
                        elem = dataGridView1.Rows[i].Cells[j].Value?.ToString() ?? "";
                        A[i, j] = Convert.ToInt32(elem);
                        dataGridView1.Rows[i].Cells[j].Style.BackColor = Color.White;
                    }
                    catch (Exception)
                    {
                        dataGridView1.Rows[i].Cells[j].Style.BackColor = Color.LightCoral;
                        label7!.Text = $"Значение элемента A[{i + 1},{j + 1}] не корректно. Повторите ввод";
                        dataGridView1.Rows[i].Cells[j].Selected = true;
                        return;
                    }
                }
            }

            label7!.Text = "Все элементы корректны!";
        }

        // Кнопка "Циклический сдвиг"
        private void button3_Click(object? sender, EventArgs e)
        {
            if (A == null || dataGridView2 == null)
            {
                MessageBox.Show("Сначала создайте матрицу!", "Ошибка");
                return;
            }

            try
            {
                // Создаем копию матрицы для результата
                int[,] shiftedMatrix = new int[m, n];

                // Выполняем циклический сдвиг каждой строки на 2 элемента вправо
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        // Вычисляем новую позицию после сдвига
                        int newPosition = (j + 2) % n;
                        shiftedMatrix[i, newPosition] = A[i, j];
                    }
                }

                // Выводим результат
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        dataGridView2.Rows[i].Cells[j].Value = shiftedMatrix[i, j].ToString();
                    }
                }

                label7!.Text = "Циклический сдвиг на 2 элемента вправо выполнен!";
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при выполнении сдвига: {ex.Message}", "Ошибка");
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