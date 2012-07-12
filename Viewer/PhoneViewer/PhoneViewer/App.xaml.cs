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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace PhoneViewer
{
    public partial class App : Application
    {
        /// <summary>
        /// Fournit un accès simplifié à la structure racine de l’application de téléphone.
        /// </summary>
        /// <returns>Trame racine de l’application de téléphone.</returns>
        public PhoneApplicationFrame RootFrame { get; private set; }

        /// <summary>
        /// Fournit un accès à un ContentManager pour l’application.
        /// </summary>
        public ContentManager Content { get; private set; }

        /// <summary>
        /// Fournit un accès à un GameTimer défini pour pomper le FrameworkDispatcher.
        /// </summary>
        public GameTimer FrameworkDispatcherTimer { get; private set; }

        /// <summary>
        /// Fournit un accès au AppServiceProvider pour l’application.
        /// </summary>
        public AppServiceProvider Services { get; private set; }

        /// <summary>
        /// Constructeur pour l’objet Application.
        /// </summary>
        public App()
        {
            // Gestionnaire global pour les exceptions non détectées. 
            UnhandledException += Application_UnhandledException;

            // Initialisation Silverlight standard
            InitializeComponent();

            // Initialisation téléphonique
            InitializePhoneApplication();

            // Initialisation XNA
            InitializeXnaApplication();

            // Afficher les informations de profil des graphiques pendant le débogage.
            if (System.Diagnostics.Debugger.IsAttached)
            {
                // Affiche les compteurs de fréquence d’images.
                Application.Current.Host.Settings.EnableFrameRateCounter = true;

                // Afficher les zones de l’application qui vont être redessinées dans chaque trame.
                //Application.Current.Host.Settings.EnableRedrawRegions = true;

                // Activez le mode de visualisation de l’analyse de non-production, 
                // qui affiche les zones d’une page qui sont remises au GPU avec superposition de couleur.
                //Application.Current.Host.Settings.EnableCacheVisualization = true;

                // Désactivez la détection de l’inactivité de l’application en affectant la valeur Désactivé à la propriété UserIdleDetectionMode de
                // l’objet PhoneApplicationService de l’application.
                // Attention : - À utiliser uniquement en mode débogage. L’application qui désactive la détection de l’inactivité de l’utilisateur continue de s’exécuter
                // et de consommer de l’énergie alors que le téléphone est inactif.
                PhoneApplicationService.Current.UserIdleDetectionMode = IdleDetectionMode.Disabled;
            }
        }

        // Code à exécuter lors du lancement de l’application (p. ex. à partir de Démarrer)
        // Ce code ne s’exécute pas lorsque l’application est réactivée
        private void Application_Launching(object sender, LaunchingEventArgs e)
        {
        }

        // Code à exécuter lorsque l’application est activée (mise à l’avant-plan)
        // Ce code ne s’exécute pas lors du premier lancement de l’application
        private void Application_Activated(object sender, ActivatedEventArgs e)
        {
        }

        // Code à exécuter lorsque l’application est désactivée (envoyée à l’arrière-plan)
        // Ce code ne s’exécute pas lorsque l’application se ferme
        private void Application_Deactivated(object sender, DeactivatedEventArgs e)
        {
        }

        // Code à exécuter lors de la fermeture de l’application (p. ex. l’utilisateur a appuyé sur Retour)
        // Ce code ne s’exécute pas lorsque l’application est désactivée
        private void Application_Closing(object sender, ClosingEventArgs e)
        {
        }

        // Code à exécuter en cas d’échec de la navigation
        private void RootFrame_NavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            if (System.Diagnostics.Debugger.IsAttached)
            {
                // Échec de la navigation ; passage au débogueur
                System.Diagnostics.Debugger.Break();
            }
        }

        // Code à exécuter en cas d’exceptions non gérées
        private void Application_UnhandledException(object sender, ApplicationUnhandledExceptionEventArgs e)
        {
            if (System.Diagnostics.Debugger.IsAttached)
            {
                // Une exception non gérée s’est produite ; passage au débogueur
                System.Diagnostics.Debugger.Break();
            }
        }

        #region Phone application initialization

        // Éviter la double initialisation
        private bool phoneApplicationInitialized = false;

        // Ne pas ajouter d’autre code à cette méthode
        private void InitializePhoneApplication()
        {
            if (phoneApplicationInitialized)
                return;

            // Créez la trame sans la définir en tant que RootVisual, pour que l’écran
            // de démarrage reste actif jusqu’à ce que le rendu de l’application soit prêt.
            RootFrame = new PhoneApplicationFrame();
            RootFrame.Navigated += CompleteInitializePhoneApplication;

            // Gérer les échecs de navigation
            RootFrame.NavigationFailed += RootFrame_NavigationFailed;

            // S’assurer de ne plus initialiser
            phoneApplicationInitialized = true;
        }

        // Ne pas ajouter d’autre code à cette méthode
        private void CompleteInitializePhoneApplication(object sender, NavigationEventArgs e)
        {
            // Définir la racine visuelle pour autoriser le rendu par l’application
            if (RootVisual != RootFrame)
                RootVisual = RootFrame;

            // Supprimer ce gestionnaire puisqu’il n’est plus nécessaire
            RootFrame.Navigated -= CompleteInitializePhoneApplication;
        }

        #endregion

        #region XNA application initialization

        // Effectue l’initialisation des types XNA nécessaires pour l’application.
        private void InitializeXnaApplication()
        {
            // Créer le fournisseur de services
            Services = new AppServiceProvider();

            // Ajouter le SharedGraphicsDeviceManager aux services en tant que IGraphicsDeviceService pour l’application
            foreach (object obj in ApplicationLifetimeObjects)
            {
                if (obj is IGraphicsDeviceService)
                    Services.AddService(typeof(IGraphicsDeviceService), obj);
            }

            // Créer ContentManager pour que l’application puisse charger les éléments précompilés
            Content = new ContentManager(Services, "Content");

            // Créer un GameTimer pour pomper le XNA FrameworkDispatcher
            FrameworkDispatcherTimer = new GameTimer();
            FrameworkDispatcherTimer.FrameAction += FrameworkDispatcherFrameAction;
            FrameworkDispatcherTimer.Start();
        }

        // Gestionnaire d’événements qui fournit chaque image au FrameworkDispatcher.
        // FrameworkDispatcher est obligatoire pour de nombreux événements XNA et
        // pour certaines fonctions comme la lecture SoundEffect.
        private void FrameworkDispatcherFrameAction(object sender, EventArgs e)
        {
            FrameworkDispatcher.Update();
        }

        #endregion
    }
}
