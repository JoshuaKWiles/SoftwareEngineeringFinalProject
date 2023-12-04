using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FinalProjectGUI
{
    /// <summary>
    /// Interaction logic for EventInfo.xaml
    /// </summary>
    public partial class EventInfo : Page
    {
        public bool editing = false;
        public EventInfo()
        {
            InitializeComponent();
        }

        bool changeColor(Rectangle rect)
        {
            if (rect.Fill == Brushes.White)
            {
                rect.Fill = Brushes.Black;
                return true;
            }
            else if (rect.Fill == Brushes.Black)
            {
                rect.Fill= Brushes.White;
                return false;
            }
            else
            {
                return false;
            }
        }

        private void whiteboardButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(WhiteboardBox);
        }

        private void projectorButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(ProjectorBox);
        }

        private void speakerButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(SpeakerBox);
        }

        private void microphoneButton_Click(object sender, RoutedEventArgs e)
        {
            changeColor(MicrophoneBox);
        }
    }
}
