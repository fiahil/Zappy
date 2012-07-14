using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;

namespace PhoneViewer
{
    public class Infos
    {
        private static Infos infos = new Infos();
        public static Infos GetInstance()
        {
            if (infos == null)
                infos = new Infos();
            return infos;
        }

        private Infos() { }

        public string host = null;
        public string port = null;
    }

    public partial class MainPage : PhoneApplicationPage
    {
        // Constructeur
        public MainPage()
        {
            InitializeComponent();
        }

        // Le bouton Cliquez sur le gestionnaire d’événements permet de passer à la seconde page
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Infos.GetInstance().port = this.Port.Text;
            Infos.GetInstance().host = this.Host.Text;
            NavigationService.Navigate(new Uri("/GamePage.xaml", UriKind.Relative));
        }
    }
}
